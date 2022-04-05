// this is for generating the csv files for the python script


 #include <iostream>
 #include <fstream>
 #include <vector>
 #include <string>
 using namespace std;
 vector<double> ranks;
 vector<string> word;

int main()
{
    ifstream inFile;
    ofstream outFile;
    string wd;
    inFile.open("Copod_starting_words.txt");
         if(!inFile.is_open())
    {
        cout << "Could not open word bank! Exiting program.\n";
        exit(1);
    }
     while(inFile >> wd){
         word.push_back(wd);
     }
    outFile.open("CopodStarting.csv");
    for( size_t i = 0; i < word.size(); i++){
    outFile <<"\""<< word.at(i) << "\", ";
    }
    inFile.close();
    outFile.close();

    ifstream rankinFile;
    ofstream rankoutFile;
    double rank;
    rankinFile.open("CopodRanks.txt");
         if(!rankinFile.is_open())
    {
        cout << "Could not open word bank! Exiting program.\n";
        exit(1);
    }
     while(rankinFile >> rank){
         ranks.push_back(rank);
     }
    rankoutFile.open("CopodStartingRanks.csv");
    for( size_t i = 0; i < ranks.size(); i++){
    rankoutFile << ranks.at(i) << ", ";
    }
    rankinFile.close();
    rankoutFile.close();



}
