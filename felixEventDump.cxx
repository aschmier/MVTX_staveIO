#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
using namespace std;

void wordHandler(int word_number, int line_number, vector<bitset<8>> vec){
  cout << "   | ";
  bool isRDH = false;
  bool isIHW = false;
  bool isTDH = false;
  bool isTDT = false;
  bool isDDW = false;
  bool isCDW = false;
  bool isMSD = false;

  stringstream check_rdh;
  stringstream check_data;
  stringstream check_msd;
  check_rdh  << hex << vec[1].to_ulong() << vec[5].to_ulong();
  check_data << hex << vec[vec.size()-1].to_ulong();
  check_msd  << hex << vec[0].to_ulong();

  if(check_rdh.str().substr(0,2) == "40" && check_rdh.str().substr(2,2) == "20") isRDH = true;
  if(check_data.str() == "e0") isIHW = true;
  if(check_data.str() == "e8") isTDH = true;
  if(check_data.str() == "f0") isTDT = true;
  if(check_data.str() == "e4") isDDW = true;
  if(check_data.str() == "f8") isCDW = true;
  if(check_msd.str()  == "e0" || check_msd.str() == "e1" || check_msd.str() == "e2" ||
      check_msd.str() == "e3" || check_msd.str() == "e4" || check_msd.str() == "e5" ||
      check_msd.str() == "e6" || check_msd.str() == "e7" || check_msd.str() == "e8") isMSD = true;

  if(line_number == 1 && word_number == 1 && check_data.str() == "0")  cout << "End of data";

  if(line_number != 0 && isRDH) cout << "RDH repeat...";

  // Raw Data Header
  if(line_number == 0 && word_number == 0){
    stringstream header_version;
    stringstream header_size;
    stringstream fee_id;
    stringstream priority_bit;
    stringstream source_id;

    header_version << hex << vec[0].to_ulong();
    header_size    << hex << vec[1].to_ulong();
    fee_id         << hex << vec[3].to_ulong() + vec[2].to_ulong();
    priority_bit   << hex << vec[4].to_ulong();
    source_id      << hex << vec[5].to_ulong();

    cout << "header_version: " << header_version.str() << " // ";
    cout << "header_size: "    << header_size.str()    << " // ";
    cout << "fee_id: "         << fee_id.str()         << " // ";
    cout << "priority_bit: "   << priority_bit.str()   << " // ";
    cout << "source_id: "      << source_id.str();
  }

  if(line_number == 0 && word_number == 1){
    stringstream lhc_bc;
    stringstream gtm_bco;

    lhc_bc  << hex << vec[1].to_ulong() + vec[0].to_ulong();
    gtm_bco << hex << vec[8].to_ulong() << vec[7].to_ulong() << vec[6].to_ulong() << vec[5].to_ulong() << vec[4].to_ulong();

    cout << "lhc_bc: "  << lhc_bc.str() << " // ";
    cout << "gtm_bco: " << gtm_bco.str();
  }

  if(line_number == 0 && word_number == 2){
    stringstream trigger_type;
    stringstream pages_counter;
    stringstream stop_bit;

    trigger_type  << vec[3] << vec[2] << vec[1] << vec[0];
    pages_counter << hex << vec[5].to_ulong() << vec[4].to_ulong();
    stop_bit      << hex << vec[6].to_ulong();

    cout << "trigger_type: "   << trigger_type.str();

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
    cout << "stop_bit: "       << stop_bit.str();
  }

  if(line_number == 1 && word_number == 0){
    stringstream detector_field;
    stringstream par_bit;

    detector_field << hex << vec[3].to_ulong() << vec[2].to_ulong() << vec[1].to_ulong() << vec[0].to_ulong();
    par_bit        << hex << vec[5].to_ulong() << vec[4].to_ulong();

    cout << "detector_field: "  << detector_field.str() << " // ";
    cout << "par_bit: "         << par_bit.str();
  }

  // ITS Header Word
  if(isIHW){
    stringstream IHW_id;
    stringstream active_lanes;

    IHW_id       << hex << vec[9].to_ulong();
    active_lanes << vec[0];

    cout << "IHW_id: "       << IHW_id.str() << " // ";
    cout << "active_lanes: " << active_lanes.str();
  }

  // Trigger Data Header
  if(isTDH){
    stringstream TDH_id;
    stringstream tdh_gtm_bco;
    stringstream tdh_lhc_bc;
    stringstream tdh_error;
    stringstream tdh_trigger_type;

    TDH_id           << hex << vec[9].to_ulong();
    tdh_gtm_bco      << hex << vec[8].to_ulong() << vec[7].to_ulong() << vec[6].to_ulong() << vec[5].to_ulong() << vec[4].to_ulong();
    tdh_lhc_bc       << hex << vec[3].to_ulong() << vec[2].to_ulong();
    tdh_error        << vec[1];
    tdh_trigger_type << vec[1] << vec[0];

    cout << "TDH_id: "           << TDH_id.str()      << " // ";
    cout << "tdh_gtm_bco: "      << tdh_gtm_bco.str() << " // ";
    cout << "tdh_lhc_bc: "       << tdh_lhc_bc.str()  << " // ";

    string tdh_error_split = tdh_error.str().substr(0,4);
    cout << "tdh_error: "        << tdh_error_split;
    if((int)tdh_error_split.at(3) - '0' == 1) cout << " Internal Trigger";
    if((int)tdh_error_split.at(2) - '0' == 1) cout << " No Data";
    if((int)tdh_error_split.at(1) - '0' == 1) cout << " Continuation";
    cout << " // ";

    string tdh_trigger_type_split = tdh_trigger_type.str().substr(4);
    cout << "tdh_trigger_type: " << tdh_trigger_type_split;
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
    cout << "tdt_error: "       << tdt_error.str();
    if((int)tdt_error.str().at(7) - '0' == 1) cout << " lane_starts_violation";
    if((int)tdt_error.str().at(5) - '0' == 1) cout << " transmission_timeout";
    if((int)tdt_error.str().at(4) - '0' == 1) cout << " packet_done";
    cout << " // ";

    cout << "tdt_lane_status: " << tdt_lane_status.str();
    //if((int)tdt_error.at(7) - '0' == 1) cout << " lane_starts_violation";
    //if((int)tdt_error.at(5) - '0' == 1) cout << " transmission_timeout";
    //if((int)tdt_error.at(4) - '0' == 1) cout << " packet_done";
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

    cout << "ddw_lane_status: " << ddw_lane_status.str();
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
    /*
    stringstream CDW_id;
    stringstream cdw_index;
    stringstream cdw_user_fields;

    CDW_id          << hex << vec[9].to_ulong();
    cdw_index       << hex << vec[8].to_ulong() << vec[7].to_ulong() << vec[6].to_ulong();
    cdw_user_fields << hex << vec[5].to_ulong() << vec[4].to_ulong() << vec[3].to_ulong() << vec[2].to_ulong() << vec[1].to_ulong() << vec[0].to_ulong();

    cout << "CDW_id: "          << CDW_id.str()    << " // ";
    cout << "cdw_index: "       << cdw_index.str() << " // ";
    cout << "cdw_user_fields: " << cdw_user_fields.str();
    */
    cout << "MAP sensor data...";
  }
}

int main(int argc, char *argv[]){
  // Open the stream in binary mode
  ifstream binFile(argv[1], std::ios::in | std::ios::binary);
  int sensor;
  if(atoi(argv[2]) == 1) sensor = 8;
  else if(atoi(argv[2]) == 2) sensor = 16;
  else if(atoi(argv[2]) == 3) sensor = 24;
  else{ cout << "Invalid sensor given. Choose 1, 2, or 3." << endl; return 0; }

  if (binFile.is_open())
  {
    vector<uint8_t> vBuf(32);
    int line_number = 0;
    while (binFile.good()) {
      if(line_number == 7) line_number = 0;

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

        for(int word_number = 1; word_number < vBuf.size()+1; word_number++){
          bitset<8> set(vBuf[word_number-1]);
          bitsetVec.push_back(set);
          cout.width(2);
          std::cout << std::hex << set.to_ulong() << ' ';
          if(word_number % 10 == 0){
            wordHandler(word_number/10-1, line_number, bitsetVec);
            bitsetVec.clear();
            cout << endl;
          }
        }
        if( ((bitset<8>)vBuf[vBuf.size()-1]).to_ulong() == sensor) cout << endl;
      }
      cout << endl;
      line_number++;
    }
    binFile.close();
  }

  else cout << "Unable to open file" << endl;

  return 0;
}
