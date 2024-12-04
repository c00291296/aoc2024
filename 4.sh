#!/bin/sh
#horizontal occurences
h=$(echo "$(cat input) $(rev input)"\
       	 | grep -o -e "XMAS"| wc -l)
horizontals=$(printf "$(cat input)\n$(rev input)"\
	| grep -e "XMAS")
printf $horizontals
h=$(echo $horizontals | grep -o -e "XMAS" | wc -l)
echo "Horizontal occurences:"
echo $h
#vertical occurences
v=0
width=$(head -n 1 input | wc -m)
width=$((width-1))
height=$(cat input | wc -l)
#discount the trailing endline
height=$((height-1))
verticals=$(for i in $(seq 1 $width);
do
	cat input | \
	       	cut -c$i | tr -d '\n';
	printf "\n"
done)
verticals=$(printf "$verticals\n$(echo $verticals | rev)")
echo $verticals
v=$(echo $verticals | grep -o -e "XMAS"| wc -l)
echo "Vertical occurences:"
echo $v
diagonals=$(cat input | ./4.py | echo "$(cat), $(tac input | ./4.py)")
diagonals=$(echo "$diagonals, $(echo $diagonals | rev)");
echo $diagonals
d=$(echo "$diagonals" | grep -o -e "XMAS" | wc -l)
echo "diagonal occurences:"
echo $d
result=$((v+d+h))
echo "Final total: $result"
