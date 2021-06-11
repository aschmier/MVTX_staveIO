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
    if(wordNumber == 52 && word == "e0") isITSheader = true;
    wordNumber++;
  }
  if(isReserved == true && isITSheader == true) return true;
  else return false;

}

void printOut(string headerVersion, string headerSize, string feeID, string priorityBit, string sourceID, string beamCounter,
              string orbit, string triggerType, string pagesCounter, string stopBit, string detectorField, string parBit)
{
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
  headerVersion.clear();
  headerSize.clear();
  feeID.clear();
  priorityBit.clear();
  sourceID.clear();
  beamCounter.clear();
  orbit.clear();
  triggerType.clear();
  pagesCounter.clear();
  stopBit.clear();
  detectorField.clear();
  parBit.clear();
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
    if(wordNumber == 33 || wordNumber == 34 || wordNumber == 35 || wordNumber == 36) detectorField = word + detectorField;
    if(wordNumber == 37 || wordNumber == 38) parBit = word + parBit;
    if(wordNumber == 39)
    {
      printOut(headerVersion, headerSize, feeID, priorityBit, sourceID, beamCounter,
               orbit, triggerType, pagesCounter, stopBit, detectorField, parBit);
      cout << "Checking for MVTX specific data..." << endl;
      isData = checkITSspecific(str);
      cout << endl;
      if(isData) cout << "MVTX data found. Reading..." << endl;
      else cout << "No MVTX data found. Reading closing RDH..." << endl;

      headerVersion.clear();
      headerSize.clear();
      feeID.clear();
      priorityBit.clear();
      sourceID.clear();
      beamCounter.clear();
      orbit.clear();
      triggerType.clear();
      pagesCounter.clear();
      stopBit.clear();
      detectorField.clear();
      parBit.clear();
    }
    if(wordNumber > 39 && !isData)
    {
      if(wordNumber == 65) headerVersion = word;
      if(wordNumber == 66) headerSize = word;
      if(wordNumber == 67 || wordNumber == 68) feeID = word + feeID;
      if(wordNumber == 69) priorityBit = word;
      if(wordNumber == 70) sourceID = word;
      if(wordNumber == 75 || wordNumber == 76) beamCounter = word + beamCounter;
      if(wordNumber == 79 || wordNumber == 80 || wordNumber == 81 || wordNumber == 82) orbit = word + orbit;
      if(wordNumber == 85 || wordNumber == 86 || wordNumber == 87 || wordNumber == 88) triggerType = word + triggerType;
      if(wordNumber == 89 || wordNumber == 90) pagesCounter = word + pagesCounter;
      if(wordNumber == 91) stopBit = word;
      if(wordNumber == 98 || wordNumber == 99 || wordNumber == 100 || wordNumber == 101) detectorField = word + detectorField;
      if(wordNumber == 102 || wordNumber == 103) parBit = word + parBit;
    }
    if(wordNumber == 104 && !isData) printOut(headerVersion, headerSize, feeID, priorityBit, sourceID, beamCounter,
                                   orbit, triggerType, pagesCounter, stopBit, detectorField, parBit);
    wordNumber++;
  }

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
      cout << "Reading RDH for packet " << packetNumber+1 << " of " << dataPacket.size() << endl;
      printHeader(dataPacket[packetNumber]);
      cout << "===================================================" << endl;
    }

    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
