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
  wdl.playWordle();
  return 0;
}