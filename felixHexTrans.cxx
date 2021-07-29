// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
using namespace std;

void printActiveLanes(string activeLanes)
{
  // Data line 1
  if(activeLanes == "00000001") cout << "Data line 1: Warning! Only sensor 1 of 1,2,3 active." << endl;
  else if(activeLanes == "00000002") cout << "Data line 1: Warning! Only sensor 2 of 1,2,3 active." << endl;
  else if(activeLanes == "00000003") cout << "Data line 1: Warning! Only sensors 1,2 of 1,2,3 active." << endl;
  else if(activeLanes == "00000004") cout << "Data line 1: Warning! Only sensor 3 of 1,2,3 active." << endl;
  else if(activeLanes == "00000005") cout << "Data line 1: Warning! Only sensors 1,3 of 1,2,3 active." << endl;
  else if(activeLanes == "00000006") cout << "Data line 1: Warning! Only sensors 2,3 of 1,2,3 active." << endl;
  else if(activeLanes == "00000007") cout << "Data line 1: Sensors 1,2,3 all active." << endl;

  // Data line 2
  else if(activeLanes == "00000008") cout << "Data line 2: Warning! Only sensor 4 of 4,5,6 active." << endl;
  else if(activeLanes == "00000010") cout << "Data line 2: Warning! Only sensor 5 of 4,5,6 active." << endl;
  else if(activeLanes == "00000018") cout << "Data line 2: Warning! Only sensors 4,5 of 4,5,6 active." << endl;
  else if(activeLanes == "00000020") cout << "Data line 2: Warning! Only sensor 6 of 4,5,6 active." << endl;
  else if(activeLanes == "00000028") cout << "Data line 2: Warning! Only sensors 4,6 of 4,5,6 active." << endl;
  else if(activeLanes == "00000030") cout << "Data line 2: Warning! Only sensors 5,6 of 4,5,6 active." << endl;
  else if(activeLanes == "00000038") cout << "Data line 2: Sensors 4,5,6 all active." << endl;

  // Data line 3
  else if(activeLanes == "00000040") cout << "Data line 3: Warning! Only sensor 7 of 7,8,9 active." << endl;
  else if(activeLanes == "00000080") cout << "Data line 3: Warning! Only sensor 8 of 7,8,9 active." << endl;
  else if(activeLanes == "000000c0") cout << "Data line 3: Warning! Only sensors 7,8 of 7,8,9 active." << endl;
  else if(activeLanes == "00000100") cout << "Data line 3: Warning! Only sensor 9 of 7,8,9 active." << endl;
  else if(activeLanes == "00000140") cout << "Data line 3: Warning! Only sensors 7,9 of 7,8,9 active." << endl;
  else if(activeLanes == "00000180") cout << "Data line 3: Warning! Only sensors 8,9 of 7,8,9 active." << endl;
  else if(activeLanes == "000001c0") cout << "Data line 3: Sensors 7,8,9 all active." << endl;

  else{ cout << "Invalid bitmap! Returning..." << endl; return; }

}

void getTDHbits(string word)
{
  string binWord = bitset<4>(stoi(word)).to_string();
  cout << "   -Valid Bits: ";
  if((binWord.at(3) - '0') == 1)   cout << " Internal_Trigger " << endl;
  else if((binWord.at(2) - '0') == 1)   cout << " No_Data " << endl;
  else if((binWord.at(1) - '0') == 1)   cout << " Continuation " << endl;
  else cout << "None" << endl;
}

void getTriggerType(string triggerType, bool isTDH = false)
{
  int decBit0_3;
  int decBit4_7;
  int decBit8_11;
  int decBit12_15;
  int decBit16_19;
  int decBit20_23;
  int decBit24_27;
  int decBit28_31;

  string binBit0_3;
  string binBit4_7;
  string binBit8_11;
  string binBit12_15;
  string binBit16_19;
  string binBit20_23;
  string binBit24_27;
  string binBit28_31;

  if(!isTDH)
  {
    decBit0_3   = triggerType.at(7) - '0';
    decBit4_7   = triggerType.at(6) - '0';
    decBit8_11  = triggerType.at(5) - '0';
    decBit12_15 = triggerType.at(4) - '0';
    decBit16_19 = triggerType.at(3) - '0';
    decBit20_23 = triggerType.at(2) - '0';
    decBit24_27 = triggerType.at(1) - '0';
    decBit28_31 = triggerType.at(0) - '0';
  }

  if(isTDH)
  {
    decBit0_3  = triggerType.at(2) - '0';
    decBit4_7  = triggerType.at(1) - '0';
    decBit8_11 = triggerType.at(0) - '0';
  }

  binBit0_3   = bitset<4>(decBit0_3).to_string();
  binBit4_7   = bitset<4>(decBit4_7).to_string();
  binBit8_11  = bitset<4>(decBit8_11).to_string();

  if(!isTDH)
  {
    binBit12_15 = bitset<4>(decBit12_15).to_string();
    binBit16_19 = bitset<4>(decBit16_19).to_string();
    binBit20_23 = bitset<4>(decBit20_23).to_string();
    binBit24_27 = bitset<4>(decBit24_27).to_string();
    binBit28_31 = bitset<4>(decBit28_31).to_string();
  }

  cout << "   -Valid Bits: " << endl;
  if((binBit0_3.at(3) - '0') == 1)   cout << " ORBIT ";
  if((binBit0_3.at(2) - '0') == 1)   cout << " HB ";
  if((binBit0_3.at(1) - '0') == 1)   cout << " HBr ";
  if((binBit0_3.at(0) - '0') == 1)   cout << " HC ";

  if((binBit4_7.at(3) - '0') == 1)   cout << " PhT ";
  if((binBit4_7.at(2) - '0') == 1)   cout << " PP ";
  if((binBit4_7.at(1) - '0') == 1)   cout << " Cal ";
  if((binBit4_7.at(0) - '0') == 1)   cout << " SOT ";

  if((binBit8_11.at(3) - '0') == 1)  cout << " EOT ";
  if((binBit8_11.at(2) - '0') == 1)  cout << " SOC ";
  if((binBit8_11.at(1) - '0') == 1)  cout << " EOC ";
  if((binBit8_11.at(0) - '0') == 1)  cout << " TF ";
  if(!isTDH)
  {
    if((binBit12_15.at(3) - '0') == 1) cout << " FErst ";
    if((binBit12_15.at(2) - '0') == 1) cout << " RT ";
    if((binBit12_15.at(1) - '0') == 1) cout << " RS ";

    if((binBit24_27.at(0) - '0') == 1) cout << " LHCgap1 ";

    if((binBit28_31.at(3) - '0') == 1) cout << " LHCgap2 ";
    if((binBit28_31.at(2) - '0') == 1) cout << " TPCsync ";
    if((binBit28_31.at(1) - '0') == 1) cout << " TPCrst ";
    if((binBit28_31.at(0) - '0') == 1) cout << " TOF ";
  }

  cout << endl;

}

void dataHandler(string str)
{
  size_t posIHW = str.find("00 00 00 00 00 e0");
  string str2 = str.substr(posIHW-12);
  int startITSdata = 0;
  int endITSdata = str2.find("01 f0");
  string itsData = str2.substr(startITSdata, (endITSdata - startITSdata)+5);
  string IHW = itsData.substr(0,29);
  string TDH = itsData.substr(31,60-31);
  int startSensorData = 69;
  int endSensorData = itsData.find("01 f0");
  string sensorData = itsData.substr(startSensorData, (endSensorData - startSensorData));
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
    if(nIHW == 0 || nIHW == 1 || nIHW == 2 || nIHW == 3) activeLanes = wordIHW + activeLanes;
    if(nIHW == 9) IHWid = wordIHW;
    nIHW++;
  }

  // Trigger Data Header

  string TTandError = TDH.substr(0,5), triggerType, wordTT;
  string TBC = TDH.substr(6,4), triggerBC, wordBC;
  string TO = TDH.substr(12,11), triggerOrbit, wordOrbit;
  string TDHid = TDH.substr(27,2);
  stringstream ssTT(TTandError);
  stringstream ssBC(TBC);
  stringstream ssOrbit(TO);
  int nTT=0, nBC=0, nO=0;

  while(ssTT >> wordTT)
  {
    if(nTT == 0 || nTT == 1) triggerType = wordTT + triggerType;
    nTT++;
  }
  string triggerError = triggerType.substr(0,1);
  triggerType = triggerType.substr(1,3);

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
  cout << "Active lanes: ";
  printActiveLanes(activeLanes);
  cout << endl;

  cout << "========= Trigger Data Header ========" << endl;
  cout << "TDH identifier: " << TDHid << endl;
  cout << "Trigger type: " << triggerType << endl;
  getTriggerType(triggerType, true);
  cout << "Internal trigger, no data, and continuation: " << triggerError << endl;
  getTDHbits(triggerError);
  cout << "Trigger bunch crossing (hex): " << triggerBC << endl;
  cout << "Trigger orbit (hex): " << triggerOrbit << endl;
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
    if(wordNumber == 46 || wordNumber == 47 || wordNumber == 48 || wordNumber == 49 || wordNumber == 50 && word =="00") isReserved = true;
    if(wordNumber == 51 && word == "e0") isITSheader = true;
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
  cout << "Orbit (hex): " << orbit << endl;
  cout << "Trigger Type: " << triggerType << endl;
  getTriggerType(triggerType);
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
    if(wordNumber == 0) headerVersion = word;
    if(wordNumber == 1) headerSize = word;
    if(wordNumber == 2 || wordNumber == 3) feeID = word + feeID;
    if(wordNumber == 4) priorityBit = word;
    if(wordNumber == 5) sourceID = word;
    if(wordNumber == 10 || wordNumber == 11) beamCounter = word + beamCounter;
    if(wordNumber == 14 || wordNumber == 15 || wordNumber == 16 || wordNumber == 17) orbit = word + orbit;
    if(wordNumber == 20 || wordNumber == 21 || wordNumber == 22 || wordNumber == 23) triggerType = word + triggerType;
    if(wordNumber == 24 || wordNumber == 25) pagesCounter = word + pagesCounter;
    if(wordNumber == 26) stopBit = word;
    if(wordNumber == 32 || wordNumber == 33 || wordNumber == 34 || wordNumber == 35) detectorField = word + detectorField;
    if(wordNumber == 36 || wordNumber == 37) parBit = word + parBit;
    if(wordNumber == 38)
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
    if(wordNumber > 38 && !isData)
    {
      if(wordNumber == 64) headerVersion = word;
      if(wordNumber == 65) headerSize = word;
      if(wordNumber == 66 || wordNumber == 67) feeID = word + feeID;
      if(wordNumber == 68) priorityBit = word;
      if(wordNumber == 69) sourceID = word;
      if(wordNumber == 74 || wordNumber == 75) beamCounter = word + beamCounter;
      if(wordNumber == 78 || wordNumber == 79 || wordNumber == 80 || wordNumber == 81) orbit = word + orbit;
      if(wordNumber == 84 || wordNumber == 85 || wordNumber == 86 || wordNumber == 87) triggerType = word + triggerType;
      if(wordNumber == 88 || wordNumber == 89) pagesCounter = word + pagesCounter;
      if(wordNumber == 90) stopBit = word;
      if(wordNumber == 97 || wordNumber == 98 || wordNumber == 99 || wordNumber == 100) detectorField = word + detectorField;
      if(wordNumber == 101 || wordNumber == 102) parBit = word + parBit;
    }
    if(wordNumber == 103 && !isData) printOut(headerVersion, headerSize, feeID, priorityBit, sourceID, beamCounter,
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
    if(wordNumber == 6)  reserved0 = word;
    if(wordNumber == 19)  reserved1 = word;
    if(wordNumber == 26) stopBit = word;
    if(wordNumber == 28) reserved2 = word;
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
  ifstream myfile ("tempHexDump.txt");
  if (myfile.is_open())
  {
    int packetNumber = 0;
    string singleLine;
    string singlePacket;
    vector<string> dataPacket;
    bool isEnd = false;
    bool newPacket = false;
    int i = 0;
    while ( getline (myfile,line) )
    {
      singleLine.append(line);
      if(newPacket)
      {
        singlePacket.append(singleLine);
        singlePacket.append("  ");
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Reading RDH for packet " << ++i << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        printHeader(singlePacket);
        singleLine.clear();
        singlePacket.clear();
        newPacket = false;
        continue;
      }

      isEnd = checkStopBit(singleLine);
      if(!isEnd)
      {
        singlePacket.append(singleLine);
        singlePacket.append("  ");
      }
      if(isEnd)
      {
        singlePacket.append(singleLine);
        singlePacket.append("  ");
        packetNumber++;
        newPacket = true;
      }

      singleLine.clear();
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
