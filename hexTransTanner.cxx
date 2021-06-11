// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void printHeader(string str){
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

    wordNumber++;
  }
  cout<< "=======================RDH========================="<<endl;
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

void printIHW(string str){
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  string ActiveLanes;
  string IHWid;


  while(ss >> word){
    if(wordNumber == 43||wordNumber==44||wordNumber ==45) ActiveLanes = word +ActiveLanes;
    else if(wordNumber ==52) IHWid = word + IHWid;
  //cout << word << "\t"<<wordNumber<<"\n";
     wordNumber++;
  }
  cout<< "=======================IHW========================="<<endl;
  cout << "Active lanes: " << stoi(ActiveLanes, 0, 16) << endl;
  cout << "ITS Header Word ID: " << stoi(IHWid, 0, 16) << endl;

  //if(stoi(stopBit, 0, 16) == 0) return 0;
  //if(stoi(stopBit, 0, 16) == 1) return 1;
  //else cout << "Error: Stop bit has undefined value." << endl;
}

void printTDH(string str){
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  string TriggerID;
  string TriggerType;
  string TriggerBC;
  string TriggerOrbit;
  string InternalTrigger;
  string temp;
  while(ss >> word){
    if(wordNumber == 53) temp = word;
    else if(wordNumber == 54) {
      TriggerType = word.substr(1)+temp;
      InternalTrigger = word.substr(0,1);
    }
    else if(wordNumber == 55) temp = word;
    else if(wordNumber == 56) TriggerBC = word.substr(1) + temp;
    else if(wordNumber == 57 || wordNumber == 58 || wordNumber == 59 || wordNumber == 60) TriggerOrbit = word + TriggerOrbit;
    else if(wordNumber == 62) TriggerID = word;

   wordNumber++;
  }
  cout<< "=======================TDH========================="<<endl;
  cout << "ID: " << stoi(TriggerID, 0, 16) << endl;
  cout << "Orbit: " << stoi(TriggerOrbit, 0, 16) << endl;
  cout << "Bunch Crossing: "  << stoi(TriggerBC, 0, 16) << endl;
  cout << "Int. Trigger/Continuation: " << stoi(InternalTrigger, 0, 16) << endl;
  cout << "Type: " << stoi(TriggerType, 0, 16) << endl;
}

void printDATA(string str){
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  string line1;
  string line2;
  string line3;
  string linetitle;
  string datatype;
  string datalineend;
  cout<< "=======================DATA========================"<<endl;
 while(ss >> word){

     if(wordNumber == 65) linetitle = word;
     if(wordNumber == 66) datatype =word;
     if(wordNumber == 67||wordNumber == 68||wordNumber == 69||wordNumber == 70||wordNumber == 71||wordNumber == 72||wordNumber == 73) line1=word+line1;
     if(wordNumber == 74) {
       datalineend=word;
       cout<< "Sensor: " << linetitle <<endl;
       cout << "Data Type: " << datatype<<endl;
       cout<< "Readout: " << line1<< endl;
       cout<< "End word: " << datalineend <<endl;
       cout<< "--------------------------------------------------\n";
     }

     if(wordNumber == 75) linetitle = word;
     if(wordNumber == 76) datatype =word;
     if(wordNumber == 77||wordNumber == 78||wordNumber == 79||wordNumber == 80||wordNumber == 81||wordNumber == 82||wordNumber == 83) line2=word+line2;
     if(wordNumber == 84) {
       datalineend=word;
       cout<< "Sensor: " << linetitle <<endl;
       cout << "Data Type: " << datatype<<endl;
       cout<< "Readout: " << line2<< endl;
       cout<< "End word: " << datalineend <<endl;
       cout<< "--------------------------------------------------\n";
     }
     if(wordNumber == 85) linetitle = word;
     if(wordNumber == 86) datatype =word;
     if(wordNumber == 87||wordNumber==88||wordNumber == 89||wordNumber == 90||wordNumber == 91||wordNumber == 92||wordNumber == 93) line3=word+line3;
     if(wordNumber == 94) {
       datalineend=word;
       cout<< "Sensor: " << linetitle <<endl;
       cout << "Data Type: " << datatype<<endl;
       cout<< "Readout: " << line3<< endl;
       cout<< "End word: " << datalineend <<endl;
       cout<< "--------------------------------------------------\n";
     }
     wordNumber++;





}
}
void printTDT(string str){
  stringstream ss(str);
  string word;
  int wordNumber = 0;
  string tID;
  string stop;
  string readout;

  cout<< "=======================TDT========================"<<endl;
 while(ss >> word){
   if(wordNumber==106||wordNumber ==105) tID =word+tID;
   if (wordNumber==104) stop = word.substr(1);
   if(wordNumber == 102||wordNumber == 101||wordNumber == 100||wordNumber == 99||wordNumber == 98||wordNumber == 97) readout =word+readout;

   wordNumber++;
 }
 cout<< "ID: " << stoi(tID,0,16) <<endl;
 cout << "STOP: " << stoi(stop,0,16) <<endl;
 cout<< "Readout: " << readout<< endl;


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
      printIHW(dataPacket[packetNumber]);
      printTDH(dataPacket[packetNumber]);
      printDATA(dataPacket[packetNumber]);
      printTDT(dataPacket[packetNumber]);
      cout << "===================================================" << endl;
    }

    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
