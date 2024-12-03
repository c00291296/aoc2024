#!/bin/sh
grep -o 'mul(\([0-9]\{1,3\}\),[0-9]\{1,3\})' input | grep -o '[0-9]\{1,3\}' \
	| echo "$(cat) 0sG[*lG+sGz0<C]sClCxlGn" | dc
