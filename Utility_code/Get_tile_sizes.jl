if length(ARGS) ==0
  error(
    """
    No use in scalar mode: 
    try: julia Get_tile_sizes.jl <path1> <path2> ...
    """
  )
end

using XML
function get_child_by_tag(file,tag)
  for c in file.children
    if c.tag ==tag
      return c
    end
  end
  nothing
end
function get_child_by_att(file,att)
  for c in file.children
    for (_,v) in c.attributes
      if v==att 
        return c
      end
    end
  end
  nothing
end
function get_child_by_tag_and_att(file,tag,att)
  for c in file.children
    if c.tag ==tag 
      for (_,v) in c.attributes
        if v==att 
          return c
        end
      end
    end
  end
  nothing
end

function get_child(file; tag::String="",attributes::String="")
  if tag =="" && attributes!=""
    return get_child_by_att(file,attributes)
  end
  if attributes =="" &&tag!=""
   return  get_child_by_tag(file,tag)
  end
  if attributes !="" && tag!=""
    return get_child_by_tag_and_att(file,tag,attributes)
  end
  nothing
end

function find_numbers(path, idx::Int64, n::Int64)
  println("[find_numbers] startig from idx = $idx" )
  vec = Vector{Vector{Float64}}()
  while true
    numbers = zeros(n)
    for i in 1:n
      println("n = $i, idx = $idx, P[idx] = $(path[idx])")
      if !(path[idx]=='-' ||  isdigit(path[idx]))
        println(path)
        println(idx)
        println(path[idx])
        error("[find_numbers] index is wrong")
      end
      aux = findfirst(r"[+-]?([0-9]*[.])?[0-9]+",path[idx:end])
      println("aux = $aux, number = $(path[idx:end][aux])")
      numbers[i] = parse(Float64,path[idx:end][aux])
      idx = idx+length(aux)
      println("idx = $idx")
      println("aux = $aux")
      if idx<length(path) && !(path[idx]==',' || path[idx] ==' ')
        println(path)
        println(idx)
        println(path[idx])
        error("[find_numbers] non valid path")
      end
      idx+=1
    end
    push!(vec,[numbers...]);
    if  idx >= length(path) || !(path[idx]=='-' ||  isdigit(path[idx]))
      return vec,idx
    end
  end
end

function parse_path(path)
  nodes = Vector{NamedTuple}();
  path_length = length(path)
  idx = 1
  while true
    cmm = path[idx]
    println("[parse_path] cmm = $cmm")
    idx+=2
    if any(lowercase(cmm) .==['m','l','t'])
      vec,idx = find_numbers(path,idx,2)
      push!(nodes,(cmm=cmm,vec = vec))
    elseif any(lowercase(cmm) .== ['v','h'])
      vec,idx = find_numbers(path,idx,1)
      push!(nodes,(cmm=cmm ,vec = vec))
    elseif lowercase(cmm) == 'c'
      vec,idx = find_numbers(path,idx,6)
      push!(nodes,(cmm=cmm ,vec = vec))
    elseif any(lowercase(cmm) .== ['s','q'])
      vec,idx = find_numbers(path,idx,4)
      push!(nodes,(cmm=cmm ,vec = vec))
    elseif lowercase(cmm) == 'a'
      vec,idx = find_numbers(path,idx,7)
      push!(nodes,(cmm=cmm ,vec = vec))
    elseif lowercase(cmm) == 'z'
      push!(nodes,(cmm=cmm,vec=nothing))
      return nodes
    else
      println(idx," ", path[idx])
      error("[parse_path non valid path")
    end
    println("[parse_path] idx = $idx")
    if idx > length(path)
      return nodes
    end
  end
end

mutable struct point
  x::Float64
  y::Float64
end

mutable struct box
  x::Float64
  y::Float64
  w::Float64
  h::Float64
  function box(point1,point2)
    x = point1.x
    y = point1.y
    w = point2.x - point1.x
    h = point2.y - point1.y
    return new(x,y,w,h)
  end
  function box(str::String)
    xx  = zeros(4);
    aux = [x for x in eachmatch(r"[+-]?([0-9]*[.])?[0-9]+",str)]
    for i in 1:4
      xx[i] = parse(Float64, aux[i].match)
    end
    return new(xx...)
  end
end
function get_box(path::String)
  nodes = parse_path(path)
  function  update_corner!(corner,P,f::Function)
    if f(P.x,corner.x)
      corner.x=P.x 
    end
    if f(P.y,corner.y)
      corner.y=P.y
    end
  end

  corner1 = point(typemax(Float64),typemax(Float64))
  corner2 = point(typemin(Float64),typemin(Float64))
  
  P = point(0,0);
  for node in nodes 
    if any(node.cmm .== ['M','L'])
      for (x,y) in node.vec
        P.x=x;P.y=y
        update_corner!(corner1,P,<);update_corner!(corner2,P,>);
      end
    elseif any( node.cmm .== ['m','l'])
      for (x,y) in node.vec
        P.x+=x;P.y+=y
        update_corner!(corner1,P,<);update_corner!(corner2,P,>);
      end
    elseif node.cmm =='H'
      for x in node.vec
        P.x=x[1];
        update_corner!(corner1,P,<);update_corner!(corner2,P,>);
      end
    elseif node.cmm =='h'
      for x in node.vec
        P.x+=x[1];
        update_corner!(corner1,P,<);update_corner!(corner2,P,>);
      end
    elseif node.cmm =='V'
      for y in node.vec
        P.y+=y[1];
        update_corner!(corner1,P,<);update_corner!(corner2,P,>);
      end
    elseif node.cmm =='v'
      for y in node.vec
        P.y+=y[1];
        update_corner!(corner1,P,<);update_corner!(corner2,P,>);
      end
    elseif lowercase(node.cmm)=='z'
      break;
    else
      error("command $(node.cmm) not supported yet.")
    end
  end
  return box(corner1,corner2)
end

for xml in ARGS
  file = read(xml, Node)
  svg = get_child(file,tag = "svg")
  if isnothing(svg)
    @warn "file $xml is not svg"
    continue;
  end
  view_box = box(svg.attributes["viewBox"])
  tiles = get_child(svg,attributes="Tiles")
  if isnothing(tiles)
    @warn "file $xml does not have Tiles layer"
  end
  tiles_spec = Vector{NamedTuple}(undef,length(tiles.children))
  for i in eachindex(tiles.children)
    c = tiles.children[i]
    label =c.attributes["inkscape:label"]
    println("tile: $label")
    path = get_child(c,tag="path")
    tiles_spec[i] =(label = label, box = get_box(path.attributes["d"]))
  end
  mkpath("$(dirname(xml))/Tiles/")
  open("$(dirname(xml))/Tiles/tiles.txt","w") do fb
    println(fb,"# view_box")
    println(fb, round(Int64,view_box.x)," ", round(Int64,view_box.y), " ", round(Int64,view_box.w), " ", round(Int64,view_box.w))
    for (label,box)  in tiles_spec 
      println(fb, label,"; ",round(Int64,box.x), " ",round(Int64,box.y)," ", round(Int64,box.w)," ",round(Int64,box.h))
    end
  end 
end