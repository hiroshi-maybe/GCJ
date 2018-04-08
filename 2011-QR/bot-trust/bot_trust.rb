class Button

  attr_reader :bot, :but_i

  def initialize(input)
    @bot = input.shift
    @but_i = input.shift
  end
end

def tokenize(num, dat, to_int)
  result = Array.new
  while !dat.empty? do
    token = Array.new
    num.times do |i|
      val = dat.shift
      val = val.to_i if to_int[i] == true
      token.push val
    end
    result.push token
  end
  return result
end

open("./A-large.in") do |file|
  lines = file.readlines
  testnum = lines.shift.chomp

  lines.each_with_index do |n,i|
    dats = n.chomp.split " "
    n = dats.shift.to_i
    result = tokenize 2, dats, [false, true]

    buttonSeq = Array.new
    result.each do |b|
      buttonSeq.push(Button.new b)
    end
    
    change = true
    init = true
    sec = 0
    pos=Hash.new
    pos["O"] = 1
    pos["B"] = 1
    free_sec = 0
    current = ""
    buttonSeq.each_with_index do |n,j|

      if init then
        sec += (n.but_i - pos[n.bot]).abs + 1
        free_sec += (n.but_i - pos[n.bot]).abs + 1
        init = false
      elsif change then
        thissec = free_sec - (n.but_i - pos[n.bot]).abs >= 0 ? 1 : ((n.but_i - pos[n.bot]).abs - free_sec).abs + 1
        sec += thissec
        free_sec = thissec
      else
        free_sec += (n.but_i - pos[n.bot]).abs + 1
        sec += (n.but_i - pos[n.bot]).abs + 1
      end

      pos[n.bot] = n.but_i
      current = n.bot
      if j != buttonSeq.length-1 then
        change = current != buttonSeq[j+1].bot ? true : false
      end

#p j.to_s + ":" + sec.to_s + ":" + free_sec.to_s + ":" + change.to_s
#p n

    end
    puts "Case #"+(i+1).to_s+": "+sec.to_s
  end
end
