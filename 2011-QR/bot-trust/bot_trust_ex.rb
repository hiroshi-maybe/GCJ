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
    time=Hash.new
    time["O"] = 0
    time["B"] = 0

    current = ""
    buttonSeq.each_with_index do |n,j|
      sec = [(pos[n.bot]-n.but_i).abs + time[n.bot], sec].max + 1
      pos[n.bot] = n.but_i
      time[n.bot] = sec
    end
    puts "Case #"+(i+1).to_s+": "+sec.to_s
  end
end
