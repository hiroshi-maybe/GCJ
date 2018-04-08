open("./A-large.in") do |file|
  lines = file.readlines
  testnum = lines.shift.chomp

  lines.each_with_index do |n,i|
    dats = n.chomp.split " "
    n = dats.shift.to_i
    k = dats.shift.to_i

    result = k<n ? 1 : (k+1)%(2**n)
    resultstr = result==0 ? "ON" : "OFF"

    puts "Case #"+(i+1).to_s+": "+resultstr
  end
end
