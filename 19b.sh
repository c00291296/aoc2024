#!/bin/sh
constraints=$(grep -e "^.*,.*$" input | \
              echo "^\($(sed -e 's/, /\\|/g')\)\+$")


grep -e "^.*,.*$" input 
echo
grep -e $(echo $constraints) input

