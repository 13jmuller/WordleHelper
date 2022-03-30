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
    vector<int> rightPos;
    bool allowMore;
    int amountAllowed;
};

struct wrongPos
{
    char letter;
    vector<int> wrongPos;
    bool allowMore;
    int amountAllowed;
};

class Wordle
{
  private:
    vector<word> wordList;
    vector<char> letLU = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
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
    void playWordle();

    size_t findMin(vector<double> v);

    void get_options(int argc, char **argv);
    
    void readList();

    void userInput();

    bool errorCheck(string sq);

    bool findLet(vector<char> v, char c);

    bool findWord(string wd);

    void genList();

    void freqAnalysis();

    void suggestFiveC();

    void suggestFiveP();

    void suggestFive();

    void selectSort(vector<double> &max, vector<int> &maxi);
};