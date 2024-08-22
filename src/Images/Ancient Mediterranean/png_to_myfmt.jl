using FileIO, Colors

if(length(ARGS) == 0)
  @info "code in test mode";
end

for filename in ARGS 
  basename,ex = splitext(filename);
  if ex != ".png"
    @warn "$filename is not a png file, conversion skipped"
    continue;
  end
  @info "converting $filename"
  
  pixels = gray.(load(filename));
  bits = [a==1 ? 2 : 1 for a in pixels];
  for i in axes(bits,1)
    for j in axes(bits,2)
      if bits[i,j] == 2 
        bits[i,j] = 0
      elseif bits[i,j] ==1
        break
      end
    end
    for j in axes(bits,2)[end:-1:1]
      if bits[i,j] == 2 
        bits[i,j] = 0
      elseif bits[i,j] ==1
        break
      end
    end
  end
  file =open(basename*".txt","w")
  for r in eachrow(bits)
    println(file,r...)
  end
  close(file);
end