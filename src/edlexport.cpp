#include "edlexport.h"


edlexport::edlexport() {}

edlexport::edlexport(vector<block> _v, string _cn, int _fr)
{
    clipname = _cn;
    title = _cn;
    fr = _fr;

    ostringstream Oss;
    string filename_edlext = title + ".edl";
    ofstream Fout( filename_edlext.c_str() );
    int cnt = 1;
    timecode currentTc(int(ceil(fr)));

    Oss << "TITLE: " << title << endl << endl;

    for(unsigned int i = 0; i < _v.size(); i++)
    {
        Oss << Int2String(cnt, 2) << "  "
            << "Tape" << "     "
            << "AA/V" << "  "
            << "C" << "        ";
        Oss << _v[i].getTimeInStr() << " "
            << _v[i].getTimeOutStr() << " "
            << currentTc.TC2String() << " ";

        timecode tcOut(_v[i].getTimeOutStr(), int(ceil(fr)));
        timecode tcIn(_v[i].getTimeInStr(), int(ceil(fr)));
        timecode dur = tcOut.GetDuration(tcIn);

        currentTc.suma(dur);

        Oss << currentTc.TC2String() << endl;
        Oss << "* FROM CLIP NAME: " << clipname << endl;
        Oss << "* COMMENT: " << _v[i].getSubtStr() << endl << endl;
        cnt++;
    }
    Fout << Oss.str();
    cout << "\nFile '" << filename_edlext << "' exported successfully!\n" << endl;
}

void edlexport::testexport() //Made for debug purposes. 'textexport()' is not being invoked actually.
{
    title = "TestExport 1";
    clipname = "ClipName 1";
    fr = ceil(24);
    cout << "framerate: " << fr << endl;
    int counter = 1;
    bool eof = false;

    ostringstream Oss;
    Oss << "TITLE: " << title << endl << endl;

    while(!eof)
    {
        Oss << Int2String(counter, 2) << "  "
            << "Tape" << "     "
            << "AA/V" << "  "
            << "C" << "        "
            << "00:00:00:00 00:00:12:12 00:00:00:00 00:00:12:12" << endl
            << "* FROM CLIP NAME: " << clipname << endl << endl;
        eof = true;
    }

    ofstream Fout("out.edl.txt");
    Fout << Oss.str();

}
