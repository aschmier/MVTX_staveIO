// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void dataHandler(string str)
{
  size_t posIHW = str.find("00 00 00 00 00 e0");
  string str2 = str.substr(posIHW-12);
  int startITSdata = 0;
  int endITSdata = str2.find("01 f0");
  string itsData = str2.substr(startITSdata, (endITSdata - startITSdata)+5);
  string IHW = itsData.substr(0,29);
  string TDH = itsData.substr(31,60-31);
  int startSensorData = 79;
  int endSensorData = itsData.find("01 f0");
  string sensorData = itsData.substr(startSensorData, (endSensorData - startSensorData) - 42);
  string TDT = itsData.substr(endSensorData-24);

  stringstream ssIHW(IHW);
  stringstream ssSensorData(sensorData);
  stringstream ssTDT(TDT);

  string wordIHW, wordTDH, wordSensorData, wordTDT;
  int nIHW = 0, nSD = 0, nTDT = 0;
  string IHWid, activeLanes;

  // ITS Header Word

  while(ssIHW >> wordIHW)
  {
    if(nIHW == 0 || nIHW == 1 || nIHW == 2 || nIHW == 3) activeLanes = wordIHW;
    if(nIHW == 9) IHWid = wordIHW;
    nIHW++;
  }

  // Trigger Data Header

  string TT = TDH.substr(0,4), triggerType, wordTT;
  string ITC = TDH.substr(4,1);
  string TBC = TDH.substr(6,4), triggerBC, wordBC;
  string TO = TDH.substr(12,11), triggerOrbit, wordOrbit;
  string TDHid = TDH.substr(27,2);
  stringstream ssTT(TT);
  stringstream ssBC(TBC);
  stringstream ssOrbit(TO);
  int nTT=0, nBC=0, nO=0;

  while(ssTT >> wordTT)
  {
    if(nTT == 0 || nTT == 1) triggerType = wordTT + triggerType;
    nTT++;
  }

  while(ssOrbit >> wordOrbit)
  {
    if(nO == 0 || nO == 1 || nO == 2 || nO == 3) triggerOrbit = wordOrbit + triggerOrbit;
    nO++;
  }

  while(ssBC >> wordBC)
  {
    if(nBC == 0 || nBC == 1) triggerBC = wordBC + triggerBC;
    nBC++;
  }

  // ITS Sensor Data
  string lane1 = sensorData.substr(0, 29);
  string lane2 = sensorData.substr(31, 29);
  string lane3 = sensorData.substr(62, 29);

  // Trigger Data Trailer
  string laneStatus, TDTerror, TDTid;

  while(ssTDT >> wordTDT)
  {
    if(nTDT == 0 || nTDT == 1 || nTDT == 2 || nTDT == 3 || nTDT == 4 || nTDT == 5 || nTDT == 6) laneStatus = wordTDT + laneStatus;
    if(nTDT == 8) TDTerror = wordTDT + TDTerror;
    if(nTDT == 9) TDTid = wordTDT + TDTid;
    nTDT++;
  }

  cout << "========== MVTX Header Word ==========" << endl;
  cout << "Header word identifier: " << IHWid << endl;
  cout << "Active lanes: " << stoi(activeLanes, 0, 16) << endl;
  cout << endl;

  cout << "========= Trigger Data Header ========" << endl;
  cout << "TDH identifier: " << TDHid << endl;
  cout << "Trigger type: " << stoi(triggerType, 0, 16) << endl;
  cout << "Internal trigger, no data, and continuation: " << stoi(ITC, 0, 16) << endl;
  cout << "Trigger bunch crossing: " << stoi(triggerBC, 0, 16) << endl;
  cout << "Trigger orbit: " << stoi(triggerOrbit, 0, 16) << endl;
  cout << endl;

  cout << "========== MVTX Sensor Data ==========" << endl;
  cout << "Lane 1: " << lane1 << endl;
  cout << "Lane 2: " << lane2 << endl;
  cout << "Lane 3: " << lane3 << endl;
  cout << endl;

  cout << "======== Trigger Data Trailer ========" << endl;
  cout << "TDT identifier:" << TDTid << endl;
  cout << "Lane status: " << laneStatus << endl;
  cout << "Errors: " << TDTerror << endl;
}

bool checkITSspecific(string str)
{
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  bool isReserved = false;
  bool isITSheader = false;

  while(ss >> word)
  {
    if(wordNumber == 47 || wordNumber == 48 || wordNumber == 49 || wordNumber == 50 || wordNumber == 51 && word =="00") isReserved = true;
    if(wordNumber == 52 && word == "e0") isITSheader = true;
    wordNumber++;
  }
  if(isReserved == true && isITSheader == true) return true;
  else return false;

}

void printOut(string headerVersion, string headerSize, string feeID, string priorityBit, string sourceID, string beamCounter,
              string orbit, string triggerType, string pagesCounter, string stopBit, string detectorField, string parBit)
{
  cout << "========== Raw Data Header ===========" << endl;
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
      cout << endl;
      cout << "Checking for MVTX specific data..." << endl;
      isData = checkITSspecific(str);
      if(isData)
      {
        cout << "MVTX data found. Reading..." << endl;
        cout << endl;
        dataHandler(str);
      }
      else cout << "No MVTX data found. Reading closing RDH..." << endl;
      cout << endl;

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
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      cout << "Reading RDH for packet " << packetNumber+1 << " of " << dataPacket.size() << endl;
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      printHeader(dataPacket[packetNumber]);
    }

    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
