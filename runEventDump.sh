#!/bin/bash

g++ testmain.cxx -o eventDump
./eventDump $1 $2 > $3
#./eventDump rawData/test0070-210818-141012-1.dat 1 > out.txt
rm eventDump
