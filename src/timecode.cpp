#include "timecode.h"

timecode::timecode()
{
    hh = 0;
    mm = 0;
    ss = 0;
    ff = 0;
}

timecode::timecode(int _fr)
{
    hh = 0;
    mm = 0;
    ss = 0;
    ff = 0;
    fr = _fr;
}

timecode::timecode(const timecode& tc)
{
    hh = tc.hh;
    mm = tc.mm;
    ss = tc.ss;
    ff = tc.ff;
    fr = tc.fr;
}

timecode::timecode(string _tc, int _fr)
{
    // 01234567890
    // 00:12:34:23
    hh = Str2Int( _tc.substr(0,2) );
    mm = Str2Int( _tc.substr(3,2) );
    ss = Str2Int( _tc.substr(6,2) );
    ff = Str2Int( _tc.substr(9,2) );
    fr = _fr;
    if(ff > fr-1)
    {
        cout << "NON-VALID FRAME: frames value is " << ff << " and frame rate is " << fr << endl;
        cout << "Setting frame value to 00" << endl;
        ff = 0;
    }

}

timecode timecode::GetDuration(timecode& tcIn)
{
    int framesIn = tcIn.TC2Frames();
    int framesOut = TC2Frames();
    int framesDur = framesOut-framesIn;
    timecode ret(fr);
    for(int i = 0; i < framesDur; i++)
    {
        ret.addOneFrame();
    }
    return ret;
}

int timecode::TC2Frames()
{
    int frames = 0;

    frames += hh * (fr * 60 * 60);
    frames += mm * (fr * 60);
    frames += ss * fr;
    frames += ff;

    return frames;
}

void timecode::suma(timecode& tc)
{
    for(int i = 0; i < tc.TC2Frames(); i++)
    {
        addOneFrame();
    }
}

void timecode::addOneFrame()
{
    int hhMax = 99;
    int mmMax = 59;
    int ssMax = 59;
    int ffMax = fr - 1;

    ff++;
    if(ff > ffMax)
    {
        ff = 0;
        ss++;
        if(ss > ssMax)
        {
            ss = 0;
            mm++;
            if(mm > mmMax)
            {
                mm = 0;
                hh++;
                if(hh > hhMax)
                {
                    hh = 0;
                    mm = 0;
                    ss = 0;
                    ff = 0;

                }
            }
        }
    }
}

string timecode::TC2String()
{
    string ret;
    ret += Int2String(hh,1) + ':'
         + Int2String(mm,1) + ':'
         + Int2String(ss,1) + ':'
         + Int2String(ff,1);
    return ret;
}

void timecode::display()
{
    cout << "### DISPLAY() timecode" << endl
         << "# hh: " << hh << endl
         << "# mm: " << mm << endl
         << "# ss: " << ss << endl
         << "# ff: " << ff << endl
         << "# fr: " << fr << endl;

}
