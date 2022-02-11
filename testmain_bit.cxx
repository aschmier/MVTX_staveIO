#include <iostream>
#include <fstream>
#include <string>
#include "mvtx_decoder.cxx"
using namespace std;

int main(int argc, char *argv[]){
  string inputfile = argv[1];
  int sensor = atoi(argv[2]);
  mvtx_decoder(inputfile,sensor);
}
