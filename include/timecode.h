#ifndef TIMECODE_H
#define TIMECODE_H
#include <iostream>
#include "block.h"
using namespace std;

class timecode
{
    private:
        int hh;
        int mm;
        int ss;
        int ff;
        int fr;

    public:
        timecode();
        timecode(int fr);
        timecode(string tc, int fr);
        timecode(const timecode& tc);

        timecode GetDuration(timecode& tcIn);
        void suma(timecode& tc);
        void addOneFrame();
        string TC2String();
        int TC2Frames();

        void display();
};


#endif // TIMECODE_H
