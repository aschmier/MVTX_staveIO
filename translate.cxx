#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;
//string concatenateHistoname(string,string,string,string);
int main(){

  string byte;
  string test;
  ifstream in ("testoutput.txt");
  if (in.is_open()){
    cout<<"check"<<endl;
  }
  else{
    cout<<"bust"<<endl;
    return 0;
  }
  int counter=0;
    while(in>>test){

    if(test.substr(1,1)==":"){
      test.clear();
      counter =0;
    }
    else{
      byte += test + " ";
      counter+=1;
    if (counter==10){
      break;
    }
    }
  }

  cout<<"byte"<< endl;
  in.close();
  return 0;

}
