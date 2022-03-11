// Outlines the functions used for processing
 #include <cmath>
 #include <iostream>
 #include <fstream>
 #include <algorithm>
 #include <vector>
 #include <string>

using namespace std;

struct word
{
    string wd;
    int freq[26];
};

struct rightPos
{
    char letter;
    int pos;
};

struct wrongPos
{
    char letter;
    int wrongPos[5];
};

class Wordle
{
  private:
    vector<word> wordList;
    string guess;
    vector<rightPos> rightLetters;
    vector<wrongPos> wrongPosLetters;
    vector<char> wrongLetters;
    vector<string> guesses;
    
  public:
    void errorCheck();
    
    void readList();

    void readFreq();

    void readPos();
};
