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
    comb_cand = nil
    
    # deep copy
    result = Marshal.load(Marshal.dump(base));

    delete_num = 0
    base.each_with_index do |n,i|
#p i.to_s+"#####"+n
#p comb_cand
#p opp_cand_list
#p result
      if comb_cand != nil && !comb_cand.empty? then
        
        hit = false
        comb_cand.each do |x|
          if x[0]==n then
            comb_cand = nil
            result[i-delete_num] = x[1]
            deleted = result[i-delete_num-1]
            result.delete_at(i-delete_num-1)
            
            opp_cand_list.pop if opp.has_key? deleted
            delete_num += 1
            
            hit = true
            break
          end
        end
        if hit then
          next
        else
          comb_cand = nil
        end
      end
      if comb.has_key? n then
        comb_cand = comb[n]
      end
      del_index = nil
      opp_cand_list.each_with_index do |m,j|
        hit = false
        m[0].each do |y|
          if n == y then
#            start = result.index m[1]
            start=0
#p start
#p i
#p delete_num
            result.slice! start..(i-delete_num)
            delete_num += i-delete_num-start+1
            del_index = j
            comb_cand = nil
#p result
            hit = true
            break
          end
        end
        break if hit
      end
#p result
      if del_index != nil then
#p del_index
        opp_cand_list.slice! del_index, opp_cand_list.length-del_index
      else
        if opp.has_key? n then
          opp_cand_list.push [opp[n],n]
        end
      end
    end
#p result
    puts "Case #"+(case_index+1).to_s+": ["+result.join(", ")+"]"
  end
end
