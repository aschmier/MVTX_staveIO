#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
using namespace std;

void readMSD(vector<bitset<8>> sensor_data){
  for(int i = 0; i < sensor_data.size(); i++){
    if(sensor_data.at(i).to_string().substr(0,4) == "0010"){ sensor_data.erase(sensor_data.begin()+i); i--; }
  }

  for(int i = 0; i < sensor_data.size(); i++){
    if(sensor_data.at(i).to_string() == "11111111") cout << "IDLE:             " << hex << sensor_data.at(i).to_ulong() << " ";
    if(sensor_data.at(i).to_string() == "11110001") cout << "BUSY ON:          " << hex << sensor_data.at(i).to_ulong() << " ";
    if(sensor_data.at(i).to_string() == "11110000") cout << "BUSY OFF:         " << hex << sensor_data.at(i).to_ulong() << " ";
    if(sensor_data.at(i).to_string().substr(0,4) == "1011"){
      cout << "Chip Trailer:     " << hex << sensor_data.at(i).to_ulong() << "     -> ";
      cout << "Readout Flags: " << hex << bitset<8>(sensor_data.at(i).to_string().substr(4,4)).to_ulong() << " ";
      break;
    }
    if(sensor_data.at(i).to_string().substr(0,3) == "110"){
      cout << "Region Header:    " << hex << sensor_data.at(i).to_ulong() << "     -> ";
      cout << "Region ID:     " << hex << bitset<8>(sensor_data.at(i).to_string().substr(3,5)).to_ulong() << " ";
    }
    if(sensor_data.at(i).to_string().substr(0,4) == "1010"){
      if(i >= sensor_data.size()-2) continue;
      cout << "Chip Header:      " << hex << sensor_data.at(i).to_ulong() << " " << sensor_data.at(i+1).to_ulong() << "  -> ";
      cout << "Bunch Counter: " << hex << bitset<8>(sensor_data.at(i).to_string().substr(4,4)).to_ulong() << bitset<8>(sensor_data.at(i+1).to_string()).to_ulong();
      if(i < sensor_data.size()-2) i++;
    }
    if(sensor_data.at(i).to_string().substr(0,4) == "1110"){
      if(i >= sensor_data.size()-2) continue;
      cout << "Chip Empty Frame: " << hex << sensor_data.at(i).to_ulong() << " " << sensor_data.at(i+1).to_ulong() << "     -> ";
      cout << "Bunch Counter: " << hex << bitset<8>(sensor_data.at(i).to_string().substr(4,4)).to_ulong() << bitset<8>(sensor_data.at(i+1).to_string()).to_ulong();
      if(i < sensor_data.size()-2) i++;
    }
    if(sensor_data.at(i).to_string().substr(0,2) == "01"){
      if(i >= sensor_data.size()-2) continue;
      cout << "Data Short:       " << hex << sensor_data.at(i).to_ulong() << " " << sensor_data.at(i+1).to_ulong() << "     -> ";
      string dsBin = sensor_data.at(i).to_string() + sensor_data.at(i+1).to_string();
      cout << "Encoder ID:    " << hex << bitset<8>(dsBin.substr(2,4)).to_ulong() << " // ";
      cout << "Address:       " << hex << bitset<8>(dsBin.substr(6,10)).to_ulong() << " ";
      if(i < sensor_data.size()-2) i++;
    }
    if(sensor_data.at(i).to_string().substr(0,2) == "00"){
      if(i >= sensor_data.size()-3) continue;
      cout << "Data Long:        " << hex << sensor_data.at(i).to_ulong() << " " << sensor_data.at(i+1).to_ulong() << " " << sensor_data.at(i+2).to_ulong() << " -> ";
      string dlBin = sensor_data.at(i).to_string() + sensor_data.at(i+1).to_string() + sensor_data.at(i+2).to_string();
      cout << "Encoder ID:    " << hex << bitset<8>(dlBin.substr(2,4)).to_ulong() << " // ";
      cout << "Address: " << hex << bitset<8>(dlBin.substr(6,10)).to_ulong() << " // ";
      cout << "Hit Map: " << hex << bitset<8>(dlBin.substr(17,7)).to_ulong() << " ";
      if(i < sensor_data.size()-3) i+=2;
    }
    cout << endl;
  }
}

void wordHandler(int word_number, vector<bitset<8>> vec, bool& MSDpacket, vector<bitset<8>>& lane0data, vector<bitset<8>>& lane1data, vector<bitset<8>>& lane2data){
  if(!MSDpacket)cout << "   | ";
  bool isRDH = false;
  bool isIHW = false;
  bool isTDH = false;
  bool isTDT = false;
  bool isDDW = false;
  bool isCDW = false;
  bool isMSD = false;

  stringstream check_word;

  check_word << hex << vec[9].to_ulong();

  if(check_word.str()  == "0") isRDH = true;
  if(check_word.str() == "e0") isIHW = true;
  if(check_word.str() == "e8") isTDH = true;
  if(check_word.str() == "f0") isTDT = true;
  if(check_word.str() == "e4") isDDW = true;
  if(check_word.str() == "f8") isCDW = true;
  if(check_word.str().substr(0,1)  == "2" && (int)check_word.str().at(0) -'0' > -1 && (int)check_word.str().at(0) - '0' < 9) isMSD = true;

  // Raw Data Header
  if(isRDH && word_number == 0){
    stringstream header_version;
    stringstream header_size;
    stringstream fee_id;
    stringstream source_id;
    stringstream detector_field;

    header_version << hex << vec[0].to_ulong();
    header_size    << hex << vec[1].to_ulong();
    fee_id         << hex << vec[3].to_ulong() + vec[2].to_ulong();
    source_id      << hex << vec[4].to_ulong();
    detector_field << hex << vec[8].to_ulong() + vec[7].to_ulong() + vec[6].to_ulong() + vec[5].to_ulong();

    cout << "header_version: " << header_version.str() << " // ";
    cout << "header_size: "    << header_size.str()    << " // ";
    cout << "fee_id: "         << fee_id.str()         << " // ";
    cout << "source_id: "      << source_id.str()      << " // ";
    cout << "detector_field: " << detector_field.str();
  }

  if(isRDH && word_number == 1){
    stringstream lhc_bc;
    stringstream gtm_bco;

    lhc_bc  << hex << vec[1].to_ulong() + vec[0].to_ulong();
    gtm_bco << hex << vec[8].to_ulong() << vec[7].to_ulong() << vec[6].to_ulong() << vec[5].to_ulong() << vec[4].to_ulong();

    cout << "lhc_bc: "  << lhc_bc.str() << " // ";
    cout << "gtm_bco: " << gtm_bco.str();
  }

  if(isRDH && word_number == 2){
    stringstream trigger_type;
    stringstream pages_counter;
    stringstream stop_bit;
    stringstream priority_bit;

    trigger_type  << vec[3] << vec[2] << vec[1] << vec[0];
    pages_counter << hex << vec[5].to_ulong() << vec[4].to_ulong();
    stop_bit      << hex << vec[6].to_ulong();
    priority_bit  << hex << vec[7].to_ulong();

    cout << "trigger_type:";

    if((int)trigger_type.str().at(31) - '0' == 1) cout << " ORBIT";
    if((int)trigger_type.str().at(30) - '0' == 1) cout << " HB";
    if((int)trigger_type.str().at(29) - '0' == 1) cout << " HBr";
    if((int)trigger_type.str().at(28) - '0' == 1) cout << " HC";
    if((int)trigger_type.str().at(27) - '0' == 1) cout << " PhT";
    if((int)trigger_type.str().at(26) - '0' == 1) cout << " PP";
    if((int)trigger_type.str().at(25) - '0' == 1) cout << " Cal";
    if((int)trigger_type.str().at(24) - '0' == 1) cout << " SOT";
    if((int)trigger_type.str().at(23) - '0' == 1) cout << " EOT";
    if((int)trigger_type.str().at(22) - '0' == 1) cout << " SOC";
    if((int)trigger_type.str().at(21) - '0' == 1) cout << " EOC";
    if((int)trigger_type.str().at(20) - '0' == 1) cout << " TF";
    if((int)trigger_type.str().at(19) - '0' == 1) cout << " FErst";
    if((int)trigger_type.str().at(18) - '0' == 1) cout << " RT";
    if((int)trigger_type.str().at(17) - '0' == 1) cout << " RS";
    if((int)trigger_type.str().at(4)  - '0' == 1) cout << " LHCgap1";
    if((int)trigger_type.str().at(3)  - '0' == 1) cout << " LHCgap2";
    if((int)trigger_type.str().at(2)  - '0' == 1) cout << " TPCsync";
    if((int)trigger_type.str().at(1)  - '0' == 1) cout << " TPCrst";
    if((int)trigger_type.str().at(0)  - '0' == 1) cout << " TOF";

    cout << " // ";
    cout << "pages_counter: "  << pages_counter.str() << " // ";
    cout << "stop_bit: "       << stop_bit.str()      << " // ";
    cout << "priority_bit: "   << priority_bit.str();
  }

  // ITS Header Word
  if(isIHW){
    stringstream IHW_id;
    stringstream active_lanes;

    IHW_id       << hex << vec[9].to_ulong();
    active_lanes << vec[1] << vec[0];

    cout << "IHW_id: "       << IHW_id.str() << " // ";
    cout << "active_lanes: " << active_lanes.str();
  }

  // Trigger Data Header
  if(isTDH){
    stringstream TDH_id;
    stringstream tdh_gtm_bco;
    stringstream tdh_lhc_bc;
    stringstream tdh_status;
    stringstream tdh_trigger_type;

    TDH_id           << hex << vec[9].to_ulong();
    tdh_gtm_bco      << hex << vec[8].to_ulong() << vec[7].to_ulong() << vec[6].to_ulong() << vec[5].to_ulong() << vec[4].to_ulong();
    tdh_lhc_bc       << hex << vec[3].to_ulong() << vec[2].to_ulong();
    tdh_status        << vec[1];
    tdh_trigger_type << vec[1] << vec[0];

    cout << "TDH_id: "           << TDH_id.str()      << " // ";
    cout << "tdh_gtm_bco: "      << tdh_gtm_bco.str() << " // ";
    cout << "tdh_lhc_bc: "       << tdh_lhc_bc.str()  << " // ";

    string tdh_status_split = tdh_status.str().substr(0,4);
    cout << "tdh_status: "        << tdh_status_split;
    if((int)tdh_status_split.at(3) - '0' == 1) cout << " Internal Trigger";
    if((int)tdh_status_split.at(2) - '0' == 1) cout << " No Data";
    if((int)tdh_status_split.at(1) - '0' == 1) cout << " Continuation";
    cout << " // ";

    string tdh_trigger_type_split = tdh_trigger_type.str().substr(4);
    cout << "tdh_trigger_type:";
    if((int)tdh_trigger_type_split.at(11) - '0' == 1) cout << " ORBIT";
    if((int)tdh_trigger_type_split.at(10) - '0' == 1) cout << " HB";
    if((int)tdh_trigger_type_split.at(9)  - '0' == 1) cout << " HBr";
    if((int)tdh_trigger_type_split.at(8)  - '0' == 1) cout << " HC";
    if((int)tdh_trigger_type_split.at(7)  - '0' == 1) cout << " PhT";
    if((int)tdh_trigger_type_split.at(6)  - '0' == 1) cout << " PP";
    if((int)tdh_trigger_type_split.at(5)  - '0' == 1) cout << " Cal";
    if((int)tdh_trigger_type_split.at(4)  - '0' == 1) cout << " SOT";
    if((int)tdh_trigger_type_split.at(3)  - '0' == 1) cout << " EOT";
    if((int)tdh_trigger_type_split.at(2)  - '0' == 1) cout << " SOC";
    if((int)tdh_trigger_type_split.at(1)  - '0' == 1) cout << " EOC";
    if((int)tdh_trigger_type_split.at(0)  - '0' == 1) cout << " TF";
  }

  // Trigger Data Trailer
  if(isTDT){
    stringstream TDT_id;
    stringstream tdt_error;
    stringstream tdt_lane_status;

    TDT_id          << hex << vec[9].to_ulong();
    tdt_error       << vec[8];
    tdt_lane_status << vec[6] << vec[5] << vec[4] << vec[3] << vec[2] << vec[1] << vec[0];

    cout << "TDT_id: "          << TDT_id.str()    << " // ";
    cout << "tdt_error: ";
    if((int)tdt_error.str().at(7) - '0' == 1) cout << " lane_starts_violation";
    if((int)tdt_error.str().at(5) - '0' == 1) cout << " transmission_timeout";
    if((int)tdt_error.str().at(4) - '0' == 1) cout << " packet_done";
    cout << " // ";

    cout << "tdt_lane_status: ";
    string lane_status_string = tdt_lane_status.str();
    bool lsError = false;
    for(int i = 0; i < lane_status_string.length(); i+=2){
      if(lane_status_string.substr(i,2) == "01"){ cout << "WARNING: Lane " << i; lsError = true; }
      if(lane_status_string.substr(i,2) == "10"){ cout << "ERROR: Lane " << i; lsError = true; }
      if(lane_status_string.substr(i,2) == "11"){ cout << "FAULT: Lane " << i; lsError = true; }
    }
    if(!lsError) cout << "OK";
    else lsError = false;
  }

  // Diagnostic Data Word
  if(isDDW){
    stringstream DDW_id;
    stringstream ddw_index;
    stringstream ddw_error;
    stringstream ddw_lane_status;

    DDW_id          << hex << vec[9].to_ulong();
    ddw_index       << hex << vec[8].to_ulong();
    ddw_error       << vec[8];
    ddw_lane_status << vec[6] << vec[5] << vec[4] << vec[3] << vec[2] << vec[1] << vec[0];

    cout << "DDW_id: "          << DDW_id.str()                << " // ";
    cout << "ddw_index: "       << ddw_index.str().substr(0,1) << " // ";

    string ddw_error_split = ddw_error.str().substr(4);
    cout << "ddw_error: "       << ddw_error_split;
    if((int)ddw_error_split.at(0)  - '0' == 1) cout << " lane_starts_violation";
    if((int)ddw_error_split.at(2)  - '0' == 1) cout << " transmission_timeout";
    cout << " // ";

    cout << "ddw_lane_status: ";
    string lane_status_string = ddw_lane_status.str();
    bool lsError = false;
    for(int i = 0; i < lane_status_string.length(); i+=2){
      if(lane_status_string.substr(i,2) == "01"){ cout << "WARNING: Lane " << i; lsError = true; }
      if(lane_status_string.substr(i,2) == "10"){ cout << "ERROR: Lane " << i; lsError = true; }
      if(lane_status_string.substr(i,2) == "11"){ cout << "FAULT: Lane " << i; lsError = true; }
    }
    if(!lsError) cout << "OK";
    else lsError = false;
    cout << endl << endl << "------------------------------------------------------------------" << endl;
  }

  // Calibration Data Word
  if(isCDW){
    stringstream CDW_id;
    stringstream cdw_index;
    stringstream cdw_user_fields;

    CDW_id          << hex << vec[9].to_ulong();
    cdw_index       << hex << vec[8].to_ulong() << vec[7].to_ulong() << vec[6].to_ulong();
    cdw_user_fields << hex << vec[5].to_ulong() << vec[4].to_ulong() << vec[3].to_ulong() << vec[2].to_ulong() << vec[1].to_ulong() << vec[0].to_ulong();

    cout << "CDW_id: "          << CDW_id.str()    << " // ";
    cout << "cdw_index: "       << cdw_index.str() << " // ";
    cout << "cdw_user_fields: " << cdw_user_fields.str();
  }

  // MAP Sensor Data
  if(isMSD){
    stringstream MSDword;
    MSDword << hex << vec[0].to_ulong();
    if(MSDword.str().substr(0,1)  == "a" && word_number == 0){ MSDpacket = true; cout << "Begin sensor data..." << endl; }

    if(MSDpacket){
      for(int i = 0; i < vec.size(); i++){
        if(word_number == 0) lane0data.push_back(vec.at(i));
        if(word_number == 1) lane1data.push_back(vec.at(i));
        if(word_number == 2) lane2data.push_back(vec.at(i));
      }
    }

    for(int i = 0; i < vec.size(); i++){
      if(vec.at(i).to_string() == "10110000" && word_number == 2) MSDpacket = false;
    }

  }
}

void felixEventDump(string inputfile, int sensorIn){
  // Open the stream in binary mode
  ifstream binFile(inputfile, std::ios::in | std::ios::binary);
  int sensor;
  if(sensorIn == 1) sensor = 8;
  else if(sensorIn == 2) sensor = 16;
  else if(sensorIn == 3) sensor = 24;
  else{ cout << "Invalid sensor given. Choose 1, 2, or 3." << endl; return; }

  if (binFile.is_open())
  {
    vector<uint8_t> vBuf(32);
    int line_number = 0;
    bool MSDpacket = false;
    vector<bitset<8>> lane0data;
    vector<bitset<8>> lane1data;
    vector<bitset<8>> lane2data;
    while (binFile.good()) {
      if( binFile.read((char *)&vBuf[0], vBuf.size() ) ){
        if( ((bitset<8>)vBuf[vBuf.size()-1]).to_ulong() != sensor ){
          if( ((bitset<8>)vBuf[vBuf.size()-1]).to_ulong() == 0){
            cout
            << "=================================" << endl
            << "End of packet..." << endl
            << "=================================" << endl
            << endl;
            continue;
          }
          else continue;
        }

        vector<bitset<8>> bitsetVec;
        bool goodLine = false;
        for(int word_number = 1; word_number < vBuf.size()+1; word_number++){
          bitset<8> set(vBuf[word_number-1]);
          bitsetVec.push_back(set);
          cout.fill('0');
          cout.width(2);
          if(word_number % 10 == 0){
            for(int i = 0; i < bitsetVec.size(); i++) if(bitsetVec.at(i) != 0) goodLine = true;
            if(!goodLine){bitsetVec.clear(); continue;}
            else goodLine = false;
            if(!MSDpacket) for(int i = bitsetVec.size()-1; i > -1; i--){cout.width(2); cout << hex << bitsetVec.at(i).to_ulong() << " ";}
            wordHandler(word_number/10-1, bitsetVec, MSDpacket, lane0data, lane1data, lane2data);
            bitsetVec.clear();
            if(!MSDpacket) cout << endl;
          }
        }
      }
      line_number++;
      if(!MSDpacket && lane0data.size() != 0){ cout << "Lane 0:" << endl; readMSD(lane0data); cout << endl << endl; }
      if(!MSDpacket && lane1data.size() != 0){ cout << "Lane 1:" << endl; readMSD(lane1data); cout << endl << endl; }
      if(!MSDpacket && lane2data.size() != 0){ cout << "Lane 2:" << endl; readMSD(lane2data); cout << endl; }
      if(!MSDpacket && lane0data.size() != 0){cout << endl; lane0data.clear(); lane1data.clear(); lane2data.clear();}
    }
    binFile.close();
  }

  else cout << "Unable to open file" << endl;

  return;
}
