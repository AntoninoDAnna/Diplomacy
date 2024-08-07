if(length(ARGS) == 0)
  error("you need to specify a png file")
end

mutable struct Chunk
  l::Int32
  type::String
  data::Any
  CRC::Vector{UInt8}
  function Chunk(l,t,d,c)
    data = data_functions[t](d,l);
    return new(l,t,data,c)
  end
end

function __IHDR(d::Vector{UInt8},l::Int32)
  if l!=13
    error("IHDR is not standard, aborting")
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
      error("pHYs is non standard and data is unsufficient, aborting")
    end
    @warn "pHYs is non standard, may break"
  end
  x = bswap(reinterpret(Int32,d[1:4])...)
  y = bswap(reinterpret(Int32,d[5:8])...)
  u = Int32(d[9])
  return(x = x, y=y, us = u);
end
function __tEXt(d::Vector{UInt8},l::Int32)
  I =findfirst(x->x==0x00,d);
  
  if isnothing(I)
    error("tEXt is non standard: null-char not found. Aborting")
  end
  if I==l
    error("tEXT is non standard: missing value. Aborting")
  end
  if I>79
    @warn "tEXt is non standard: key longer then expected"
  end
  println(I);
  key = String(Char.(d[1:I-1]))
  val = String(Char.(d[I+1:l]))
  return key=>val
end

data_functions = Dict{String,Function}();
data_functions["IHDR"] = __IHDR;
data_functions["PLTE"] = (d,l)->d;
data_functions["IDAT"] = (d,l)->d;
data_functions["IEND"] = (d,l)->nothing;
data_functions["bKGD"] = (d,l)->d;
data_functions["cHRM"] = (d,l)->d; 
data_functions["cICP"] = (d,l)->d; 
data_functions["dSIG"] = (d,l)->d; 
data_functions["eXIf"] = (d,l)->d; 
data_functions["gAMA"] = (d,l)->d; 
data_functions["hIST"] = (d,l)->d; 
data_functions["iCCP"] = (d,l)->d; 
data_functions["iTXt"] = (d,l)->d; 
data_functions["pHYs"] = __pHYs; 
data_functions["sBIT"] = (d,l)->d; 
data_functions["sPLT"] = (d,l)->d; 
data_functions["sRGB"] = (d,l)->d; 
data_functions["sTER"] = (d,l)->d; 
data_functions["tEXt"] = __tEXt; 
data_functions["tIME"] = (d,l)->d; 
data_functions["tRNS"] = (d,l)->d; 
data_functions["zTXt"] = (d,l)->d; 


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
  type = read_string(file,4);
  data = Vector{UInt8}(undef,l);
  read!(file,data);
  crc = Vector{UInt8}(undef,4);
  read!(file,crc);
  return Chunk(l,type,data,crc);
end
function read_all_chunk(file::IOStream)
  output = Vector{Chunk}();
  while true
    push!(output, read_chunk(file))
    if output[end].type =="IEND"
      return output
    end
  end
end

function convert_to_myftm(file::IOStream)
  if !check_header(file)
    @warn "check header failed, skipping file"
    return 
  end
  chunks = read_all_chunk(file);
end

for filename in ARGS 
  _,ex = splitext(filename);
  if ex != ".png"
    @warn "$filename is not a png file, conversion skipped"
    continue;
  end
  @info "converting $filename"

  file = open(filename,"r");
  convert_to_myftm(file);
end
