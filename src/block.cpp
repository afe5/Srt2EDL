#include "block.h"


int Str2Int (string s)
{
    istringstream Iss (s);
    int ret;
    Iss >> ret;
    return ret;
}

float Cent2Frames (int cent, float fr)
{
    return cent*(fr/999.0);
}

int FloatFrames2Int (float n)
{
    return (int(n));
}

string Int2String (int n, int cnt)
{
    ostringstream Oss;
    Oss << n;
    string ret = Oss.str();
    if(ret.size() <= cnt)
    {
        ret.insert(0, (cnt+1)-ret.size(), '0');
    }
    return ret;

}

string timeInFromStr(string s, float fr)
{
    string ret = s.substr(0, 8);
    ret += ':';
    string toConvert = s.substr(9,3);
    ret += Int2String(FloatFrames2Int(Cent2Frames(Str2Int(toConvert), fr)), 1);
    return ret;
}

string timeOutFromStr(string s, float fr)
{
    string ret = s.substr(17, 8);
    ret += ':';
    string toConvert = s.substr(26,3);
    ret += Int2String(FloatFrames2Int(Cent2Frames(Str2Int(toConvert), fr)), 1);
    return ret;
}

block::block() {}

block::block(int c, string t, string s, float fr)
{
    cnt = c;
    subt = s;
    timeIn = timeInFromStr(t, fr);
    timeOut = timeOutFromStr(t, fr);
    framer = fr;

    cout << "### BLOCK CREATED" << endl
         << "# cnt = " << cnt << endl
         << "# subt = " << subt << endl
         << "# time = " << t << endl
         << "# timeIn = " << timeIn << endl
         << "# timeOut = " << timeOut << endl;

}

void block::display() // Debug purposes
{
    cout << "### DISPLAY() block n." << cnt << endl
         << "# framerate: " << framer << endl
         << "# subt: " << subt << endl
         << "# timeIn: " << timeIn << endl
         << "# timeOut: " << timeOut << endl;

}
