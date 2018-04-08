class Group

  attr_reader :next_index, :onetime_sales #:index #,:people_num
  attr_accessor :times

  def initialize(i, k, dats)
    #@index = i
    #@people_num = num.to_i

    @times=0
    
    my_index = i
    temp_next = i
    temp_sales = 0

    while k-dats[temp_next].to_i>=0 do
      k -= dats[temp_next].to_i
      temp_sales += dats[temp_next].to_i
      temp_next = temp_next >= dats.length-1 ? 0 : temp_next + 1

      break if temp_next == my_index

    end
    @next_index = temp_next#(temp_next == 0 ? dats.length-1 : temp_next-1) + 1
    @onetime_sales = temp_sales
  end

end

open("./C-large.in") do |file|
  lines = file.readlines
  testnum = lines.shift.chomp
    
  case_no = 0
  r=0
  k=0

  lines.each_with_index do |n,i|

    dats = n.chomp.split " "

    if i%2==0 then
      r = dats.shift.to_i
      k = dats.shift.to_i
    else
      groups = Array.new
      dats.each_with_index do |n, i|
        groups.push(Group.new(i, k, dats))
      end

      current_index = 0
      while r>0 do
        r-=1
        groups[current_index].times += 1
        current_index = groups[current_index].next_index
      end

#      p groups

      sales = 0
      groups.each do |g|
        sales += g.onetime_sales * g.times
      end

      case_no += 1
      puts "Case #"+case_no.to_s+": "+sales.to_s

    end
    
  end
end
