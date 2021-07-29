#!/bin/bash

hexdump -v -e '10/1 "%02x " "  " 10/1 "%02x " "  " 10/1 "%02x " "  "  2/1 "%02x " "\n"' $1  | grep "01$" --no-group-separator | less > tempHexDump.txt

g++ felixHexTrans.cxx -o hexTrans

./hexTrans > output/$2

rm tempHexDump.txt hexTrans
