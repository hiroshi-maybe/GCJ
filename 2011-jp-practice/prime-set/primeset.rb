require 'mathn'

open("./B-large.in") do |file|
  lines = file.readlines
  testnum = lines.shift.chomp

  lines.each_with_index do |n,i|
    dats = n.chomp.split " "
    a = dats.shift.to_i
    b = dats.shift.to_i
    p = dats.shift.to_i

    all_var = Hash.new
    prime = Hash.new

    # get related rime
    prime_master = Array.new
    pp = Prime.new
    while (1) do
      ptemp = pp.succ
      if ptemp >= p then
        prime_master.push ptemp
      end
      if ptemp > b then
        break
      end        
    end

    # related prime search
    (a..b).each do |x|

#      max_search_num = Math::sqrt(x).prec_i+1
      prime[x]=Array.new

      prime_master.each do |try|
        if x%try==0 then
          prime[x].push try
          all_var[try] = Array.new if !all_var.has_key? try
          all_var[try].push x
        end
      end
      if prime[x].empty? then
        prime[x].push x
        all_var[x] = Array.new if !all_var.has_key? x
        all_var[x].push x
      end
    end

    deleted_key = Hash.new

#p prime
#p all_var
    
    all_var.each_pair do |b_prime,primeinc_num_list|
      # b_prime=3, primeinc_num_list=(12,15,18)

      # deleted check
      if !deleted_key.has_key? b_prime then
      
        scan_list = Array.new primeinc_num_list

        while !scan_list.empty? do
#p scan_list
          merge_search_num = scan_list.shift
          prime[merge_search_num].each do |search_prime|
            # delete if not self key
            if (search_prime != b_prime) && !deleted_key.has_key?(search_prime) then
#p "merge_search_num:"+merge_search_num.to_s
#p "search:"+search_prime.to_s + ",b_prime:" + b_prime.to_s
              deleted_key[search_prime]=true
              all_var[search_prime].each do |merge_num_list|
                scan_list.push merge_num_list
              end
            end
          end
        end
      end
    end
    result = all_var.keys.length - deleted_key.keys.length
    puts "Case #"+(i+1).to_s+": "+result.to_s
  end
end
