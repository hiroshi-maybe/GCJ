class CombRule

  attr_reader :in_1, :in_2, :out

  def initialize(input)
    rule = input.split //
    @in_1 = rule.shift
    @in_2 = rule.shift
    @out = rule.shift
  end
end

class OppRule

  attr_reader :in_1, :in_2

  def initialize(input)
    rule = input.split //
    @in_1 = rule.shift
    @in_2 = rule.shift
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

open("./B-large.in") do |file|
  lines = file.readlines
  testnum = lines.shift.chomp

  lines.each_with_index do |n,case_index|
    dats = n.chomp.split " "
    comb_num = dats.shift.to_i

    comb_rule_list = Array.new
    comb_num.times do |i|
      comb_rule_list.push(CombRule.new dats.shift)
    end

    comb = Hash.new
    comb_rule_list.each do |n|
      comb[n.in_1] = Array.new if !comb.has_key? n.in_1
      comb[n.in_2] = Array.new if !comb.has_key? n.in_2
      comb[n.in_1].push [n.in_2, n.out]
      comb[n.in_2].push [n.in_1, n.out]
    end
    # "Q" -> [["R","Z"],["E","X"]]
    
    opp_num = dats.shift.to_i
    opp_rule_list = Array.new
    opp_num.times do |j|
      opp_rule_list.push(OppRule.new dats.shift)
    end

    opp = Hash.new
    opp_rule_list.each do |n|
      opp[n.in_1] = Array.new if !opp.has_key? n.in_1
      opp[n.in_2] = Array.new if !opp.has_key? n.in_2
      opp[n.in_1].push n.in_2
      opp[n.in_2].push n.in_1
    end

    dats.shift
    base_chars = dats.shift
    base = base_chars.split //
    
    opp_cand_list = Array.new
    
    result = Array.new

    delete_num = 0
    base.each_with_index do |n,i|
#p i.to_s+"#####"+n if case_index==24
#p opp_cand_list if case_index==24
#p result if case_index==24

      if result.length>0 && comb.has_key?(n) then
        # combine
        if (idx=comb[n].index {|el| el[0]==result[-1]})!=nil then
          deleted = result[-1]
          result[-1] = comb[n][idx][1]
          if opp.has_key? deleted then
            opp[deleted].length.times do
              opp_cand_list.pop
            end
          end
#p "combine"  if case_index==24
          next
        end
      end

      if opp.has_key?(n) && opp_cand_list.include?(n) then
        # cleard
        result.clear
        opp_cand_list.clear
#p "clear" if case_index==24
        next
      else
        result.push n
        if opp.has_key? n then
          opp[n].each do |op|
            opp_cand_list.push op
          end
        end
      end
    end
#p result
    puts "Case #"+(case_index+1).to_s+": ["+result.join(", ")+"]"
  end
end
