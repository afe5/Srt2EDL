#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "edlexport.h"
#include "timecode.h"

using namespace std;

ostream& operator<<(ostream& o, const vector<string>& v) // To make a cout of a string vector
{
  for(unsigned int i = 0; i < v.size(); i++) {
    o << v[i] << endl;
  }
  return o;
}

ostream& operator<<(ostream& o, const vector<int>& v) // To make a cout of a int vector
{
  for(unsigned int i = 0; i < v.size(); i++) {
    o << v[i] << endl;
  }
  return o;
}

bool LineIsTime(string& s) // Checks whether a line is a Time Line or a String Line.
{                          // Time Lines in SRT format look like this: "00:00:10,950 --> 00:00:14,490"
    if(s.size() > 16)
    {
        return (s[2] == ':' && s[5] == ':' && s.substr(13,3) == "-->");
    }
    else return false;
}

vector<string> FillVecSubfile(fstream& f) //Fills a vector with the entire SRT subtitle file.
{                                         //Every new line will be a cell of the vector.
    cout << "Filling vector with file..." << endl;
    vector<string> ret;
    string line;
    while(!f.eof())
    {
        getline(f, line);
        ret.push_back(line);
    }
    return ret;
}

vector<string> WordsToVectorString(string& _tempLine)
{
    vector<string> ret;
    stringstream stream(_tempLine);
    string wrd;

    while(stream >> wrd)
    {
        ret.push_back(wrd);
    }
    return ret;
}

void setup(vector<string>& _wordsToFind, float& _framerate, string& _filename)
{
    cout << "SRT2EDL: Setting everything up" << endl
         << "------------------------------" << endl;

    cout << "[1/3] SRT filename? (example: Friends_S02E01.SRT) > ";
    getline(cin, _filename);

    cout << "[2/3] Specify video framerate (example: 24.00 / 23.976 / 25.00 / ...) > ";
    cin >> _framerate;

    cout << "[3/3] Specify words to find, separated by spaces (Search is case sensitive!) > ";

    string tempLine;
    cin.ignore(1000, '\n');
    getline(cin, tempLine);
    _wordsToFind = WordsToVectorString(tempLine);

}

int main()
{
    vector<string> wordsToFind;
    float framerate;
    string filename;

    setup(wordsToFind, framerate, filename);

    fstream Fin(filename.c_str());

    if( !Fin.is_open() )
    {
        cout << "Error: File '" << filename << "' cannot be read.\n";
        return 1;
    }

    string filename_noext = filename.substr(0, filename.find('.'));

    vector<string> subfile = FillVecSubfile(Fin);

    vector<int> indexes;
    for(unsigned int i = 0; i < subfile.size(); i++)
    {
        for(unsigned int j = 0; j < wordsToFind.size(); j++)
        {
            if( subfile[i].find(wordsToFind[j]) != string::npos)
            {
                indexes.push_back(i);
            }
        }
    }

    cout << "### Found " << indexes.size() << " matches! ###" << endl;
    for(unsigned int i = 0; i < indexes.size(); i++)
    {
        cout << '#' << indexes[i] << endl
             << subfile[indexes[i]] << endl;
    }

    vector<block> vBlock;
    int cnt = 0;
    for(unsigned int i = 0; i < indexes.size(); i++)
    {
        if( LineIsTime(subfile[indexes[i]-1]) )
        {
            vBlock.push_back( block(cnt, subfile[indexes[i]-1], subfile[indexes[i]], framerate) );
            cnt++;
        }
        else if( LineIsTime(subfile[indexes[i]-2]) )
        {
            vBlock.push_back( block(cnt, subfile[indexes[i]-2], subfile[indexes[i]], framerate) );
            cnt++;
        }
        else cout << "error: Not able to identify if this line is a Time Line or a String Line." << endl;
    }

    // For debug purposes, displays what will be sent to 'edlexport' class.
    /*
    for(unsigned int i = 0; i < vBlock.size(); i++)
    {
        vBlock[i].display();
    }
    */

    edlexport edlfile(vBlock, filename_noext, int(ceil(framerate)));
}
