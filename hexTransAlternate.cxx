// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main () {
  string line;
  ifstream myfile ("hexdump_example.txt");
  if (myfile.is_open())
  {
    int lineNumber = 0;
    string sensor1;
    string sensor2;
    string sensor3;

    while ( getline (myfile,line) )
    {
      if(lineNumber == 0 || lineNumber%3 == 0){ sensor1.append(line); sensor1 += '\n'; }
      if(lineNumber == 0 || lineNumber%4 == 0){ sensor2.append(line); sensor2 += '\n'; }
      if(lineNumber == 0 || lineNumber%5 == 0){ sensor3.append(line); sensor3 += '\n'; }

      lineNumber++;
    }
    stringstream ss1(sensor1);
    string word;
    int wordNumber = 0;
    string headerVersion;
    string headerSize;
    string feeID;
    string priorityBit;
    string sourceID;

    while(ss1 >> word)
    {

      if(wordNumber == 1) headerVersion = word;
      if(wordNumber == 2) headerSize = word;
      if(wordNumber == 3) feeID = word;
      if(wordNumber == 4) feeID = word + feeID;
      if(wordNumber == 5) priorityBit = word;
      if(wordNumber == 6) sourceID = word;

      wordNumber++;
    }
    cout << "Header Version: " << headerVersion << endl;
    cout << "Header Size: " << headerSize << endl;
    cout << "FEE ID: " << feeID << endl;
    cout << "Priority Bit: " << priorityBit << endl;
    cout << "Source ID: " << sourceID << endl;
    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
