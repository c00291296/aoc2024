#!/bin/sh
grep input -o -e "+[0-9]\+" -e "=[0-9]\+" | grep -o -e "[0-9]\+"
