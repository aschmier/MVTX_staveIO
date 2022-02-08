#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include "felixEventDump.cxx"
using namespace std;

int main(int argc, char *argv[]){
  string inputfile = argv[1];
  int sensor = atoi(argv[2]);
  felixEventDump(inputfile,sensor);
}
