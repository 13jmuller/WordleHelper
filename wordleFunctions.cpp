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
    inFile.open("wordlePrompts.txt");
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

void Wordle::suggestFirstC()
{
    double magLet = 0;
    vector<double> max;
    max.resize(5, -1);
    vector<int> maxi;
    maxi.resize(5, 1);
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
        for(int j = 0; j < 5; ++j)
        {
            if(entry > max[j])
            {
                size_t idx = findMin(max);
                max[idx] = entry;
                maxi[idx] = i;
            }
            break;
        }

    }
    cout << "--------------------Top 5 First Guesses--------------------\n";
    for(int i = 0; i < 5; ++i)
    {
        cout << "Word: " << wordList[maxi[i]].wd << " ----------- Cosine Similarity: " << max[i] << "\n";
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
    while(wd.length() != 5)
    {
        cout << "Not a 5-letter word, try again!\n";
        cout << "Enter your guess: ";
        cin >> wd;
    }
    cout << "Enter squares ('y' for Yellow, 'g' for Green, '-' for Wrong Letter): ";
    cin >> squares;
    //while loop error check 5 chars and all y/g/-
    guess = wd;
    guessColors = squares;
}

void Wordle::playWordle()
{
    while(round < 7)
    {
        userInput();
        //process and suggest
        ++round;
    }
    cout << "Sorry, you lose!\n";
}
