// Outlines the functions used for processing
 #include <cmath>
 #include <iostream>
 #include <fstream>
 #include <algorithm>
 #include <vector>
 #include <string>
 #include <getopt.h>

using namespace std;

struct word
{
    string wd;
    vector<int> freq;
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
    int round;
    char method;
    int numSim;
    int numChars;
    int numWords;
    string guess;
    string guessColors;
    vector<rightPos> rightLetters;
    vector<wrongPos> wrongPosLetters;
    vector<char> wrongLetters;
    vector<string> guesses;
    vector<int> letterFreq;
    vector<vector<int>> posFreq;

  public:
    void errorCheck();

    void playWordle();

    size_t findMin(vector<double> v);

    void get_options(int argc, char **argv);
    
    void readList();

    void suggestFirstC();

    void suggestFirstP();

    void suggestFirst();

    void userInput();
};
