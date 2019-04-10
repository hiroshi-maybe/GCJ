T=STDIN.gets
T.chop!

T.to_i.times { |i|
  s=STDIN.gets
  ns=s.split(' ')
  N=ns[0].to_i,L=ns[1].to_i
  s=STDIN.gets
  ns=s.split(' ').map(&:to_i)
  k=-1;
  ns.each_with_index { |n,i|
    k=i+1
    break if ns[i]!=ns[i+1]
  }
  X=Array.new(L+1)
  X[k]=ns[k-1].gcd(ns[k])
  
  #  puts k, X[k]
  (0..k-1).each { |i|
    j=k-i-1
    #    puts j, ns[j], X[j+1]
    X[j]=ns[j]/X[j+1]
  }
  (k..L-1).each { |i|
    X[i+1]=ns[i]/X[i]
  }
  #  puts X.length
  C=X.uniq.sort
  M=Hash.new
  C.each_with_index { |n,i| M[n]=i }
  res=X.map { |a| "A".ord()+M[a] }.pack("c*")
  STDOUT.puts "Case #"+(i+1).to_s+": "+res
}
