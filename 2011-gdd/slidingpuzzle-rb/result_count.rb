# ruby 1.8.7
# author: kori39@gmail.com
# problem: slidingpuzzle
# google developer day 2011 devquiz

if ARGV[0].nil? then
  puts "input file name."
else

  open(ARGV[0]) do |file|
    success = 0
    failure = 0
    while l = file.gets
      if l.index("success") then
        success += 1
      else
        failure += 1
      end
    end
    p "sucess:" + success.to_s+", failure:"+failure.to_s
  end

end
