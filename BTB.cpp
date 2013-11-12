#include "BTB.h"
#include "CommonFunctions.cpp"
using namespace std;


BTB::BTB() {
  BTBuffer = new string * [ROW];
  for(int i=0; i<ROW; i++){
    BTBuffer[i] = new string[COL];
  } 
  LRU0 = new char[3];
  LRU1 = new char[3];
  LRU2 = new char[3];
  LRU3 = new char[3];
}

void BTB::ChangeBit(int remainder, char *LRU){
  //use line 0
  if(remainder == 0){
    LRU[0] = '1';
    LRU[1] = '1';
  }
  //use line 1
  else if(remainder == 1){
    LRU[0] = '1';
    LRU[1] = '0';
  }
  //use line 2
  else if(remainder == 2){
    LRU[0] = '0';
    LRU[2] = '1';
  }
  //use line 3
  else if(remainder == 3){
    LRU[0] = '0';
    LRU[2] = '0';
  }
}
void BTB::ChangeLRU(int insaddr){
  string temp = ItoS(insaddr);
  for(int i=0; i<ROW; i++){
    if(BTBuffer[i][0].compare(temp)){
      int result = i/4;
      int remainder = i % 4;
      // line 0-3
      if(result == 0){
        ChangeBit(remainder, LRU0);
      }
      // line 4-7
      else if(result == 1){
        ChangeBit(remainder, LRU1);
      }
      //line 8-11
      else if(result == 2){
        ChangeBit(remainder, LRU2);
      }
      // line 12-15
      else if(result == 3){
        ChangeBit(remainder, LRU3);
      }
    } 
  }
}

string BTB::CheckPredictor(int insaddr){
  string temp = ItoS(insaddr);
  for(int i=0; i<ROW; i++){
    //ins addr exists
    if (BTBuffer[i][0].compare(temp)){
      return BTBuffer[i][2];
    }
   //ins addr not exist 
    else {
      string s = "NO";
      return s;
    }
  }
}

int BTB::CheckTargetAddr(int insaddr){
  string temp = ItoS(insaddr);
  for(int i=0; i<ROW; i++){
    //ins addr exists and predicted taken
    if (BTBuffer[i][0].compare(temp) && BTBuffer[i][2] == "1"){
      int targetaddr = StoI(BTBuffer[i][1]);
      return targetaddr;
    } 
    //ins addr doesn't exist
    else {
      return -1;
    }
  }
}

void BTB::ChangePredictor(int insaddr){
  string temp = ItoS(insaddr);
  for(int i=0; i<ROW; i++){
    if(BTBuffer[i][0].compare(temp)&& BTBuffer[i][2].compare("1")){
      BTBuffer[i][2] = '0';
    }
    else if (BTBuffer[i][0].compare(temp) && BTBuffer[i][2].compare("0")){
      BTBuffer[i][2] = '1';
    }
  }
}


int BTB::GetLRULineinSet(char * LRU){
  if(LRU[0] == '0' && LRU[1] == '0'){
    return 0;
  }
  else if(LRU[0] == '0' && LRU[1] == '1'){
    return 1;
  }
  else if(LRU[0] == '1' && LRU[1] == '0'){
    return 2;
  }
  else if(LRU[0] == '1' && LRU[1] == '1'){
    return 3;
  }
}

int BTB::GetLRULine(int insaddr){
  //set 0
  int set = insaddr/4;
  int line;
  if(set == 0){
    line = GetLRULineinSet(LRU0);
  }
  else if(set == 1){
    line = GetLRULineinSet(LRU1) + 4;
  }
  else if(set == 2){
    line = GetLRULineinSet(LRU0) + 8;
  }
  else if(set == 3){
    line = GetLRULineinSet(LRU0) + 12;
  }
}

void BTB::AddPredictor(int insaddr, int targetaddr, string predictor){
  int linenumber = GetLRULine(insaddr);
  string ins = ItoS(insaddr);
  string target = ItoS(targetaddr);
  BTBuffer[linenumber][0] = ins;
  BTBuffer[linenumber][1] = target;
  BTBuffer[linenumber][2] = predictor;
}

BTB::~BTB(){
  for(int i=0; i<ROW; i++){
    delete [] BTBuffer[i];
  }
  delete [] BTBuffer;
}
