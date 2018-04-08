
open("/Users/kori/Projects/gdd2011/提出/1116/result.txt") do |file|

  lines = file.readlines

  answer = 0
  te = {}
  te["R"]=te["L"]=te["U"]=te["D"]=0
  lines.each {|e|
    l=e.chomp
    if (l!="") then
      answer+=1
    end

    tes=e.split //
    tes.each {|t|
      te[t]=te[t].to_i+1
    }
  }
  p "answer:"+answer.to_s
  p "LRUD:"+te["L"].to_s+","+te["R"].to_s+","+te["U"].to_s+","+te["D"].to_s
end
