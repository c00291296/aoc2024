#!/bin/sh
echo "Part 1 answer:"
grep -o 'mul(\([0-9]\{1,3\}\),[0-9]\{1,3\})' input | grep -o '[0-9]\{1,3\}' \
	| echo "$(cat) 0sG[*lG+sGz0<C]sClCxlGn" | dc
echo 
echo "Part 2 answer:"
grep -o -e "mul(\([0-9]\{1,3\}\),[0-9]\{1,3\})" -e "do()" -e "don't()" input |\
       	sed "s/do()/-1/g" | sed "s/don't()/-2/g" |\
       	grep -o -e "-[1-2]" -e "[0-9]\{1,3\}" |\
	echo "$(cat && echo "-3")" | python3 3b.py
#turning the stack upside-down in dc:
#z si [ z :u z 0 <U ] sU lUx li sq [ lq ;u lq 1 -  sq lq 0 <N ] sN lNx f
#draft for adding with dos and don'ts
#[ d _1 =F d _2=T * lG + sG z 0 <D ] sD [ s0 ] sF [ lFx d _1 !=T ] sT lDx lGf
