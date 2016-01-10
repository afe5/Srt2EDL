#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int Str2Int (string s);
float Cent2Frames (int cent, float fr);
int FloatFrames2Int (float n);
string Int2String (int n, int cnt);
string timeInFromStr(string s, float fr);
string timeOutFromStr(string s, float fr);


class block {
private:
    int cnt;
    string subt;
    string timeIn;
    string timeOut;
    float framer;

public:
    block();
    block(int c, string t, string s, float fr);

    string getTimeInStr() { return timeIn; }
    string getTimeOutStr() { return timeOut; }
    string getSubtStr() { return subt; }
    void display();

};


#endif // BLOCK_H

