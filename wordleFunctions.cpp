// Contains the functions
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <getopt.h>

#include "wordleFunctions.h"

using namespace std;

void Wordle::get_options(int argc, char** argv)
{
    int option_index = 0, option = 0;
    method = '\0';
    numSim = -1;
    opterr = false;
    struct option longOpts[] = {{ "method", required_argument, nullptr, 'm' },
                                { "simulate", required_argument, nullptr, 's' },
                                { "help", no_argument, nullptr, 'h' },
                                { nullptr, 0, nullptr, '\0' }};

    while ((option = getopt_long(argc, argv, "m:s:h", longOpts, &option_index)) != -1) {
        switch (option) {
            case 'm':
                method = *optarg;
                if(method != 'c' && method != 'p')
                {
                    cout << "Invalid method entered\n";
                    exit(1);
                }
                break;
            case 's':
                numSim = atoi(optarg);
                if(numSim < 1)
                {
                    cout << "Invalid simulation size\n";
                    exit(1);
                }
                break;        
            case 'h':
                cout << "Wordle Solver\n";
                exit(0);
        }
    }

}

void Wordle::readList()
{
    ifstream inFile;
    string wd;
    round = 1;
    numWords = 0;
    numChars = 0;
    vector<int> z;
    z.resize(5, 0);
    letterFreq.resize(26, 0);
    posFreq.resize(26, z);
    inFile.open("wordleFullList.txt");
    if(!inFile.is_open())
    {
        cout << "Could not open word bank! Exiting program.\n";
        exit(1);
    }
    while(inFile >> wd)
    {
        vector<int> v;
        v.resize(26, 0);
        for(int i = 0; i < 5; ++i)
        {
            ++letterFreq[static_cast<int>(wd[i] - 97)];
            ++posFreq[static_cast<int>(wd[i] - 97)][i];
            ++v[static_cast<int>(wd[i] - 97)];
            ++numChars;
        }
        word w = {wd, v};
        wordList.push_back(w);
        ++numWords;
    }
}

size_t Wordle::findMin(vector<double> v)
{
    double min = 360;
    size_t mini = 0;
    for(size_t i = 0; i < v.size(); ++i)
    {
        if(v[i] < min)
        {
            min = v[i];
            mini = i;
        }
    }
    return mini;
}

void Wordle::userInput()
{
    string wd;
    string squares;
    cout << "Guess Number " << round << "\n";
    cout << "Enter your guess: ";
    cin >> wd;
    while(!findWord(wd))
    {
        cout << "Enter your guess: ";
        cin >> wd;
    }
    cout << "Enter squares ('y' for Yellow, 'g' for Green, '-' for Wrong Letter): ";
    cin >> squares;
    while(!errorCheck(squares))
    {
        cout << "Enter squares ('y' for Yellow, 'g' for Green, '-' for Wrong Letter): ";
        cin >> squares;
    }
    guess = wd;
    guessColors = squares;
    if(squares == "ggggg")
    {
        cout << "Congratulations! You won on round " << round << '\n';
        cout << "The word was: " << wd << '\n';
        exit(0);
    }
    wrongPosLetters.clear();
    rightLetters.clear();
    for(int i = 0; i < 26; ++i)
    {
        vector<int> idx;
        char curLet = letLU[i];
        for(int j = 0; j < 5; ++j)
        {
            if(guess[j] == letLU[i])
            {
                idx.push_back(j);
            }
        }
        int amt = static_cast<int>(idx.size());
        bool allowMore = true;
        vector<int> wp;
        vector<int> rp;
        
        for(size_t j = 0; j < idx.size(); ++j)
        {
            
            if(guessColors[idx[j]] == '-')
            {
                --amt;
                allowMore = false;
            }
            else if(guessColors[idx[j]] == 'y')
            {
                wp.push_back(idx[j]);
            }
            else if(guessColors[idx[j]] == 'g')
            {
                rp.push_back(idx[j]);
            }
        }
        if(wp.size() > 0)
        {
            wrongPos w = {curLet, wp, allowMore, amt};
            wrongPosLetters.push_back(w);
        }
        if(rp.size() > 0)
        {
            rightPos r = {curLet, rp, allowMore, amt};
            rightLetters.push_back(r);
        }
        if(amt == 0 && idx.size() > 0 && !findLet(wrongLetters, curLet))
        {
            wrongLetters.push_back(curLet);
        }
    }
}

bool Wordle::findWord(string wd)
{
    if(wd.length() != 5)
    {
        cout << "Not a 5-letter word, try again!\n";
        return false;
    }
    for(size_t i = 0; i < wordList.size(); ++i)
    {
        if(wd == wordList[i].wd)
        {
            return true;
        }
    }
    cout << "Word entered is not in the word bank, try again!\n";
    return false;
}

bool Wordle::findLet(vector<char> v, char c)
{
    for(size_t i = 0; i < v.size(); ++i)
    {
        if(c == v[i])
        {
            return true;
        }
    }
    return false;
}

bool Wordle::errorCheck(string sq)
{
    if(sq.length() != 5)
    {
        cout << "Invalid length, try again!\n";
        return false;
    }
    for(int i = 0; i < 5; ++i)
    {
        if(sq[i] != 'y' && sq[i] != 'g' && sq[i] != '-')
        {
            cout << "Invalid character detected, try again!\n";
            return false;
        }
    }
    return true;
}

void Wordle::genList()
{
    vector<word> temp;
    temp = wordList;
    wordList.clear();
    bool goodWord;
    for(size_t i = 0; i < temp.size(); ++i)
    {
        goodWord = true;
        for(int j = 0; j < 5; ++j)
        {
            for(size_t k = 0; k < wrongLetters.size(); ++k)
            {
                if(temp[i].wd[j] == wrongLetters[k])
                {
                    goodWord = false;
                    break;
                }
            }
            for(size_t k = 0; k < wrongPosLetters.size(); ++k)
            {
                if(temp[i].freq[static_cast<int>(wrongPosLetters[k].letter - 97)] == 0)
                {
                    goodWord = false;
                    break;
                }
                if(temp[i].wd[j] == wrongPosLetters[k].letter)
                {
                    if((temp[i].freq[static_cast<int>(wrongPosLetters[k].letter - 97)] != wrongPosLetters[k].amountAllowed && !wrongPosLetters[k].allowMore)
                    || (temp[i].freq[static_cast<int>(wrongPosLetters[k].letter - 97)] < wrongPosLetters[k].amountAllowed && wrongPosLetters[k].allowMore))
                    {
                        goodWord = false;
                        break;
                    }
                    for(size_t n = 0; n < wrongPosLetters[k].wrongPos.size(); ++n)
                    {
                        if(j == wrongPosLetters[k].wrongPos[n])
                        {
                            goodWord = false;
                            break;
                        }
                    }
                }
            }
            for(size_t k = 0; k < rightLetters.size(); ++k)
            {
                if(temp[i].freq[static_cast<int>(rightLetters[k].letter - 97)] == 0)
                {
                    goodWord = false;
                    break;
                }
                if(((temp[i].freq[static_cast<int>(rightLetters[k].letter - 97)] != rightLetters[k].amountAllowed && !rightLetters[k].allowMore)
                || (temp[i].freq[static_cast<int>(rightLetters[k].letter - 97)] < rightLetters[k].amountAllowed && rightLetters[k].allowMore)) && temp[i].wd[j] == rightLetters[k].letter)
                {
                    goodWord = false;
                    break;
                }
                if(temp[i].wd[j] == rightLetters[k].letter)
                {
                    for(size_t n = 0; n < rightLetters[k].rightPos.size(); ++n)
                    {
                        if(temp[i].wd[rightLetters[k].rightPos[n]] != rightLetters[k].letter)
                        {
                            goodWord = false;
                            break;
                        }
                    }
                }
            }
        }
        if(goodWord)
        {
            wordList.push_back(temp[i]);
        }
    }
}

void Wordle::freqAnalysis()
{
    for(int i = 0; i < 26; ++i)
    {
        letterFreq[i] = 0;
        for(int j = 0; j < 5; ++j)
        {
            posFreq[i][j] = 0;
        }
    }
    numChars = 0;
    numWords = 0;
    for(size_t i = 0; i < wordList.size(); ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            ++letterFreq[static_cast<int>(wordList[i].wd[j] - 97)];
            ++posFreq[static_cast<int>(wordList[i].wd[j] - 97)][j];
            ++numChars;
        }
        ++numWords;
    }
}

void Wordle::selectSort(vector<double> &max, vector<int> &maxi)
{
    for(int i = 0; i < numWords - 1; ++i)
    {
        int mi = i;
        for(int j = i + 1; j < numWords; ++j)
        {
            if(max[j] > max[mi])
            {
                mi = j;
            }
        }
        swap(max[i], max[mi]);
        swap(maxi[i], maxi[mi]);
    }
}

void Wordle::suggestFiveC()
{
    double magLet = 0;
    vector<double> max;
    max.resize(numWords, -1);
    vector<int> maxi;
    maxi.resize(numWords, 1);
    for(int i = 0; i < 26; ++i)
    {
        magLet += letterFreq[i] * letterFreq[i];
    }
    magLet = sqrt(magLet);
    for(int i = 0; i < numWords; ++i)
    {
        double wordMag = 0;
        double m = 0;
        for(int j = 0; j < 26; ++j)
        {
            m += wordList[i].freq[j] * letterFreq[j];
            wordMag += wordList[i].freq[j] * wordList[i].freq[j];
        }
        wordMag = sqrt(wordMag);
        double entry = m / (wordMag * magLet);
        max[i] = entry;
        maxi[i] = i;
    }
    selectSort(max, maxi);
    cout << "--------------------Top "<< min(5, static_cast<int>(wordList.size())) << " Guesses--------------------\n";
    for(int i = 0; i < min(5, static_cast<int>(wordList.size())); ++i)
    {
        cout << "Word: " << wordList[maxi[i]].wd << " ----------- Cosine Similarity: " << max[i] << "\n";
    }
}

void Wordle::suggestFiveP()
{
    double magLet = 0;
    vector<double> max;
    max.resize(numWords, -1);
    vector<int> maxi;
    maxi.resize(numWords, 1);
    for(int i = 0; i < 26; ++i)
    {
        magLet += letterFreq[i] * letterFreq[i];
    }
    magLet = sqrt(magLet);
    for(int i = 0; i < numWords; ++i)
    {
        double wordMag = 0;
        double m = 0;
        for(int j = 0; j < 5; ++j)
        {
            double add = posFreq[static_cast<int>(wordList[i].wd[j] - 97)][j];
            if(round == 1)
            {
                if(j == 0 && (wordList[i].wd[0] == 'k' || wordList[i].wd[0] == 'y' || wordList[i].wd[0] == 'z'))
                {
                    add /= 2;
                }
                else if(j == 1 && (wordList[i].wd[1] == 'y' || wordList[i].wd[1] == 'z'))
                {
                    add /= 2;
                }
                else if(j == 2 && (wordList[i].wd[2] == 'h' || wordList[i].wd[2] == 'j' || wordList[i].wd[2] == 'k' || wordList[i].wd[2] == 'q' || wordList[i].wd[2] == 'x' || wordList[i].wd[2] == 'y'))
                {
                    add /= 2;
                }
                else if(j == 3)
                {
                    if(wordList[i].wd[3] == 'c')
                    {
                        add *= 2;
                    }
                    else if(wordList[i].wd[3] == 'j' || wordList[i].wd[3] == 'y')
                    {
                        add /= 2;
                    }
                }
                else if(j == 4)
                {
                    if(wordList[i].wd[4] == 'h' || wordList[i].wd[4] == 'k' || wordList[i].wd[4] == 'p')
                    {
                        add *= 2;
                    }
                    else if(wordList[i].wd[4] == 's' || wordList[i].wd[4] == 'u')
                    {
                        add /= 10;
                    }
                    else if(wordList[i].wd[4] == 'i')
                    {
                        add /= 2;
                    }
                }
            }
            m += add;
        }
        wordMag = sqrt(5);
        double entry = m / (wordMag * magLet);
        int gcnt = 0, ycnt = 0;
        if(round > 1)
        {
            for(int j = 0; j < 5; ++j)
            {
                if(guessColors[j] == 'g')
                {
                    ++gcnt;
                }
                else if(guessColors[j] == 'y')
                {
                    ++ycnt;
                }
            }
        }
        if(ycnt < 4 && gcnt < 3 && (gcnt + ycnt) < 5)
        {
            for(int j = 0; j < 26; ++j)
            {
                if(wordList[i].freq[j] > 1)
                {
                    entry /= sqrt(wordList[i].freq[j]);
                }
            }
        }
        max[i] = entry;
        maxi[i] = i;
    }
    selectSort(max, maxi);
    cout << "--------------------Top "<< min(5, static_cast<int>(wordList.size())) << " Guesses--------------------\n";
    for(int i = 0; i < min(5, static_cast<int>(wordList.size())); ++i)
    {
        cout << "Word: " << wordList[maxi[i]].wd << " ----------- Word Score: " << max[i] << "\n";
    }
}

void Wordle::suggestFive()
{
    switch(method)
    {
        case 'c':
            suggestFiveC();
            break;
        case 'p':
            suggestFiveP();
            break;
        default:
            cout << "Invalid method ... exiting\n";
            exit(1);
    }
}

void Wordle::playWordle()
{
    while(round < 7)
    {
        suggestFive();
        userInput();
        genList();
        freqAnalysis();
        ++round;
    }
    cout << "Sorry, you lose!\n";
}
