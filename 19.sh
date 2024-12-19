#!/bin/sh
constraints=$(grep -e "^.*,.*$" input | \
              echo "^\($(sed -e 's/, /\\|/g')\)\+$")
echo $constraints

grep -e $(echo $constraints) input | wc -l
