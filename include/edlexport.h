#ifndef EDLEXPORT_H
#define EDLEXPORT_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include "block.h"
#include "timecode.h"
using namespace std;

class edlexport
{
    private:
        string title;
        string clipname;
        int fr;
    public:
        edlexport();
        edlexport(vector<block> _v, string _cn, int _fr);

        void testexport();

};


#endif // EDLEXPORT_H
