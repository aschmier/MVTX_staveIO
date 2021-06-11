// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool checkITSspecific(string str)
{
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  bool isReserved = false;
  bool isITSheader = false;

  while(ss >> word)
  {
    if(wordNumber == 48 || wordNumber == 49 || wordNumber == 50 || wordNumber == 51 || wordNumber == 52 && word =="00") isReserved = true;
    if(wordNumber == 53 && word == "e0") isITSheader = true;
    wordNumber++;
  }
  if(isReserved == true && isITSheader == true) return true;
  else return false;

}

void printHeader(string str)
{
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  string headerVersion;
  string headerSize;
  string feeID;
  string priorityBit;
  string sourceID;
  string beamCounter;
  string orbit;
  string triggerType;
  string pagesCounter;
  string stopBit;
  string detectorField;
  string parBit;
  bool isData = false;

  while(ss >> word)
  {
    if(wordNumber == 1) headerVersion = word;
    if(wordNumber == 2) headerSize = word;
    if(wordNumber == 3 || wordNumber == 4) feeID = word + feeID;
    if(wordNumber == 5) priorityBit = word;
    if(wordNumber == 6) sourceID = word;
    if(wordNumber == 11 || wordNumber == 12) beamCounter = word + beamCounter;
    if(wordNumber == 15 || wordNumber == 16 || wordNumber == 17 || wordNumber == 18) orbit = word + orbit;
    if(wordNumber == 21 || wordNumber == 22 || wordNumber == 23 || wordNumber == 24) triggerType = word + triggerType;
    if(wordNumber == 25 || wordNumber == 26) pagesCounter = word + pagesCounter;
    if(wordNumber == 27) stopBit = word;
    if(wordNumber == 34 || wordNumber == 35 || wordNumber == 36 || wordNumber == 37) detectorField = word + detectorField;
    if(wordNumber == 38 || wordNumber == 39) parBit = word + parBit;
    if(wordNumber == 40)
    {
      isData = checkITSspecific(str);
      if(isData) cout << "Reading MVTX specific data...";
      else
      {
        if(wordNumber == 67) headerVersion = word;
        if(wordNumber == 68) headerSize = word;
        if(wordNumber == 69 || wordNumber == 70) feeID = word + feeID;
        if(wordNumber == 71) priorityBit = word;
        if(wordNumber == 72) sourceID = word;
        if(wordNumber == 77 || wordNumber == 78) beamCounter = word + beamCounter;
        if(wordNumber == 81 || wordNumber == 82 || wordNumber == 83 || wordNumber == 84) orbit = word + orbit;
        if(wordNumber == 87 || wordNumber == 88 || wordNumber == 89 || wordNumber == 90) triggerType = word + triggerType;
        if(wordNumber == 91 || wordNumber == 92) pagesCounter = word + pagesCounter;
        if(wordNumber == 93) stopBit = word;
        if(wordNumber == 100 || wordNumber == 101 || wordNumber == 102 || wordNumber == 103) detectorField = word + detectorField;
        if(wordNumber == 104 || wordNumber == 105) parBit = word + parBit;
      }
    }

    wordNumber++;
  }
  cout << "Header Version: " << stoi(headerVersion, 0, 16) << endl;
  cout << "Header Size: " << stoi(headerSize, 0, 16) << endl;
  cout << "FEE ID: " << stoi(feeID, 0, 16) << endl;
  cout << "Priority Bit: " << stoi(priorityBit, 0, 16) << endl;
  cout << "Source ID: " << stoi(sourceID, 0, 16) << endl;
  cout << "Beam Counter: " << stoi(beamCounter, 0, 16) << endl;
  cout << "Orbit: " << stoi(orbit, 0, 16) << endl;
  cout << "Trigger Type: " << stoi(triggerType, 0, 16) << endl;
  cout << "Pages Counter: " << stoi(pagesCounter, 0, 16) << endl;
  cout << "Stop Bit: " << stoi(stopBit, 0, 16) << endl;
  cout << "Detector Field: " << stoi(detectorField, 0, 16) << endl;
  cout << "Pause and Recover: " << stoi(parBit, 0, 16) << endl;

  //if(stoi(stopBit, 0, 16) == 0) return 0;
  //if(stoi(stopBit, 0, 16) == 1) return 1;
  //else cout << "Error: Stop bit has undefined value." << endl;
}

bool checkStopBit(string str){
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  string stopBit;
  string reserved0;
  string reserved1;
  string reserved2;
  while(ss >> word)
  {
    if(wordNumber == 7)  reserved0 = word;
    if(wordNumber == 20)  reserved1 = word;
    if(wordNumber == 27) stopBit = word;
    if(wordNumber == 29) reserved2 = word;
    wordNumber++;
  }
  //cout << "Stop bit: " << stoi(stopBit, 0, 16) << endl;
  if(stoi(stopBit, 0, 16) == 0) return 0;
  if(stoi(stopBit, 0, 16) == 1 && reserved0 == "00" && reserved1 == "00" && reserved2 == "00") return 1;
  else return 0;
  //else cout << "Error: Stop bit has undefined value." << endl;
}

int main () {
  string line;
  ifstream myfile ("hexdump_example.txt");
  if (myfile.is_open())
  {
    int packetNumber = 0;
    string singleLine;
    string tempPacket;
    vector<string> dataPacket;
    bool isEnd = false;
    bool newPacket = false;
    while ( getline (myfile,line) )
    {
      singleLine.append(line);
      if(newPacket)
      {
        tempPacket.append(singleLine);
        dataPacket.push_back(tempPacket);
        singleLine.clear();
        tempPacket.clear();
        newPacket = false;
        continue;
      }

      isEnd = checkStopBit(singleLine);
      if(!isEnd) tempPacket.append(singleLine);
      if(isEnd)
      {
        tempPacket.append(singleLine);
        packetNumber++;
        newPacket = true;
      }

      singleLine.clear();
    }

    cout << "Sensor 1: " << endl;
    cout <<   "===================================================" << endl;

    for(int packetNumber=0; packetNumber < dataPacket.size(); packetNumber++){
      printHeader(dataPacket[packetNumber]);
      cout << "===================================================" << endl;
    }

    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
