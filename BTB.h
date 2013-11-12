#include <iostream>
#include <string>
using namespace std;

class BTB {
  public:
    BTB(); //constructori
    void ChangeBit(int remainder, char * LRU);//change LRU bit
    void ChangeLRU(int insaddr); //change LRU line
    string CheckPredictor(int insaddr); //check predictor
    int CheckTargetAddr(int insaddr); //if predicted taken, check target address
    void ChangePredictor(int insaddr); //change predictor
    int GetLRULineinSet(char * LRU); //get line in set
    int GetLRULine(int insaddr); //get line in BTB
    void AddPredictor(int insaddr, int targetaddr, string predictor); // add new predictor
    ~BTB();

  private:
    static const int ROW = 16;//branch target buffer rows = 16
    static const int COL = 3; // branch target buffer column = 3
    string ** BTBuffer;  //BTB 
    char * LRU0, * LRU1, * LRU2, * LRU3;
};
