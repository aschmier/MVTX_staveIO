#!/bin/bash

g++ felixEventDump.cxx -o eventDump
./eventDump $1 $2 > $3
rm eventDump
