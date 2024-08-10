using LibDeflate

if(length(ARGS) == 0)
  @info "code in test mode";
end

@enum Chunk_Type begin
  IHDR = 1
  PLTE
  IDAT
  IEND 
  bKGD 
  cHRM
  cICP
  dSIG  
  eXIf 
  gAMA
  hIST
  iCCP 
  iTXt 
  pHYs
  sBIT
  sPLT 
  sRGB 
  sTER
  tEXt
  tIME
  tRNS 
  zTXt
end
str_to_chunk_type =  let inst = instances(Chunk_Type);
    Dict(zip(string.(inst), inst))
end
data_functions = Dict{Chunk_Type,Function}();

mutable struct Chunk
  l::Int32
  type::Chunk_Type
  data::Any
  CRC::Union{Vector{UInt8}, Nothing}
  function Chunk(l,t,d,c)
    data = haskey(data_functions,t) ? data_functions[t](d,l) : d;
    return new(l,t,data,c)
  end
end

function decode_IDAT(data::Vector{UInt8})
#= 
  The data have the folowing structure:
  
  [CMF] [FLAG] [DICT ID (if present)] [n byte compressed data] [ADLER32 check]
  in particular CMF*256 + FLAG must be divisibile by 31 (0x001f)
=#
  check = reinterpret(UInt16,[data[2],data[1]])[1]%0x001f
  if check != 0x0000
    error("ERROR: Corrupted data. aborting")
  end
 
  # the first byte is 
  # 8 7 6 5 | 4 3 2 1
  # CINFO   | CM
  # where CM must be 0x08.  (COMPRESSION METHOD AS ZLIB)
  # to extract CM we take byte%0x10
  
  CM = data[1]%0x10;
  if CM != 0x08
    error("ERROR: The data in IDAT are not compressed with the Deflation Method. Aborting")
  end
  
  CINFO = div((data[1]-CM),0x10);
  if CINFO>0x07
    error("ERROR: LZ77 window too large. Aborting")
  end
  window = 2^(Int32(CINFO)+8)
  #the second bit
  # 8 7    | 6     | 5 4 3 2 1
  # FLEVEl | FDICT | FCHECK 
  # where
  # - FCHECK ensure thata CM*256+FM is divisibileby 31.
  # - FDICT  is set, a Dict identifier follow immediately follow The Flag byte
  # - FLEVEL is the compression level 
  
  FDICT = (data[2]>>5)%0x02

  if FDICT != 0
    error("ERROR: Preset Dictionary specified in the compressed data.")
  end
  decompressor = Decompressor()
  decoded = Vector{UInt8}(undef,12000);
  n = decompress!(decompressor,decoded,data[3:end-4])

  return decoded[1:n];
end

function decode_IDAT(chunk::Chunk)
  data = decode_IDAT(chunk.data)
  return Chunk(chunk.l,IDAT,data,chunk.CRC)
end

function decode_IDAT(chunks::Vector{Chunk})
  l = sum(getfield.(chunks,:l))
  data = decode_IDAT(vcat(getfield.(chunks,:data)...))
  return Chunk(l,IDAT,data,nothing);
end


mutable struct PNG_chunks
  chunks::Vector{Chunk};
  has_PLTE::Bool; 
  function PNG_Chunks(c::Vector{Chunk})
    types = getfield.(c,:type);
    idx = sortperm(types);
    c = c[idx];
    types = types[idx];
    has_PLTE = PLTE in types

    idx = findall(x->x==IDAT,types);
    D = decode_IDAT(c[idx]);
    filter!(x->x.type!=IDAT,c)
    insert!(c,has_PLTE ? 3 : 2, D)
    w,h,bit_depth,ct,cm,fm,im  = c[1].data
    
    pixel = read_pixels(data::Vector{UInt8},bit_depts::Int32,);
    

    return new(c,has_PLTE)
  end
end
  
  
function __IHDR(d::Vector{UInt8},l::Int32)
  if l!=13
    error("ERROR: IHDR is not standard, aborting")
  end
  output = Vector{Int32}(undef,7);
  output[1] = bswap(reinterpret(Int32,d[1:4])...)
  output[2] = bswap(reinterpret(Int32,d[5:8])...)
  output[3:end] = Int32.(d[9:end]);
  return output;
end

function __pHYs(d::Vector{UInt8},l::Int32)
  if l!=9 
    if l<9
      error("ERROR: pHYs is non standard and data is unsufficient, aborting")
    end
    @warn "WARNING: pHYs is non standard, may break"
  end
  x = bswap(reinterpret(Int32,d[1:4])...)
  y = bswap(reinterpret(Int32,d[5:8])...)
  u = Int32(d[9])
  return(x = x, y=y, us = u);
end
function __tEXt(d::Vector{UInt8},l::Int32)
  I =findfirst(x->x==0x00,d);
  
  if isnothing(I)
    error("ERROR: tEXt is non standard: null-char not found. Aborting")
  end
  if I==l
    error("ERROR: tEXT is non standard: missing value. Aborting")
  end
  if I>79
    @warn "WARNING: tEXt is non standard: key longer then expected"
  end
  println(I);
  key = String(Char.(d[1:I-1]))
  val = String(Char.(d[I+1:l]))
  return key=>val
end

function __PLTE(d::Vector{UInt8},l::Int32)
  if l%3!=0
    error("ERROR: PLTE is not standard: length is not divisibile by 3. Aborting")
  end
  n = div(l,3)
  
  o = Vector{}();
  for i in 1:n
    rbg = Int32.(d[3*i-2:3*i])
    push!(o,rbg);
  end
  return o;
end


data_functions[IHDR] = __IHDR;
data_functions[PLTE] = __PLTE;
data_functions[IEND] = (d,l)->nothing;
data_functions[pHYs] = __pHYs; 
data_functions[tEXt] = __tEXt; 


PNG_header::Vector{UInt8} = [0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A]

function check_header(file::IOStream)
  header = Vector{UInt8}(undef,8)
  read!(file,header);
  if any(header.!=PNG_header) 
    return false
  end
  return true
end

function read_int32(file::IOStream)
  aux = Vector{UInt8}(undef,4);
  read!(file,aux);
  return bswap(reinterpret(Int32,aux)...)
end

function read_string(file::IOStream,n::Int64)
  aux = Vector{UInt8}(undef,n);
  read!(file,aux);
  return String(Char.(aux))
end

function read_chunk(file::IOStream)
  l = read_int32(file);
  type = str_to_chunk_type[read_string(file,4)];
  data = Vector{UInt8}(undef,l);
  read!(file,data);
  crc = Vector{UInt8}(undef,4);
  read!(file,crc);
  return Chunk(l,type,data,crc);
end

function read_all_chunk(file::IOStream)
  output = Vector{Chunk}();
  has_PLTE,has_IDAT,has_mIDAT = false,false,false; 
   while true
    push!(output, read_chunk(file))
    if output[end].type == PLTE
      if has_PLTE 
        error("CRITICAL ERROR: multiple PLTE chunks")
      end
      has_PLTE = true;
      continue;
    elseif output[end].type == IDAT
      if !has_IDAT
        has_IDAT=true
        if has_PLTE && output[end-1].type !=IDAT
          error("CRITICAL ERROR: PLTE does not preceed IDAT")
        end
        continue;
      end
      if output[end-1].type!= IDAT
        error("CRITICAL ERROR: IDAT chunks are not consecutive")       
      end
      has_mIDAT=true
    elseif output[end].type == IEND
      break;
    end
  end
  
  if !has_mIDAT
    return output[sortperm(getfield.(output,:type))];
  end
  idx = findall(x->x.type == IDAT,output)
  L = sum(getfield.(output[idx],:l))
  data = vcat(getfield.(output[idx],:data))
  new_output = vcat(output[findall(x->x.type !=IDAT,output)],Chunk(L,IDAT,data,nothing));
  return new_output[sort_by_vect(getfield.(new_output,:type),order)];
end


function read_PNG(filename::String)
  file = open(filename,"r");
  if !check_header(file)
    @warn "check header failed, skipping file"
    return 
  end
  return  read_all_chunk(file);
end

