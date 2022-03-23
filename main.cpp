// Driver Function
 #include <cmath>
 #include <iostream>
 #include <fstream>
 #include <algorithm>
 #include <vector>
 #include <string>
 #include <getopt.h>

 #include "wordleFunctions.h"

using namespace std;

int main(int argc, char **argv)
{
  Wordle wdl;
  wdl.get_options(argc, argv);
  wdl.readList();
  wdl.suggestFirstC();
  wdl.playWordle();
  // prompts user for what gamemode they want (helper or solver)

  // prompts user to pick what list they are playing with (from given choices)
  
  // prompts user for initial guess or gives user best guess

  // prompts user for intial guess results

  // loop starts here  

  // outputs suggested guess
  // this suggested guess is based on the narrowed down list from the previous guess' result

  // prompts user for suggested guess result
  return 0;
}
