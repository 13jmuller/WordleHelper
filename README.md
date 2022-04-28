# WordleHelper #
The purpose of this is to act as a helper for solving the game Wordle. This program takes in your initial guess and the results of the guess to suggest a next best guess. In the following rounds, the user will input the results of the guess to narrow down the word list.  
In our application, we have created two different WordleHelper funcationalities. The first one is Rank Your Starter Word which runs each algorithm on the User's input word. It then outputs the ranks that each algorithm gives the word along with the words immediately above and below it so the User can see what words are of similar rank. This process can be repeated for as many words as the User desires as long as the word exists in the Word list, which is the NYT allowed guesses.  
The second functionality is the Wordle Helper itself. It is integrated into an embedded wordle game which you play side by side with the Helper. We have imported our code from C++ into JavaScript in order to run the same algorithms on the website. The User starts by selecting the specific algorithm that they want to use from the drop down menu. At this time, we have 4 to choose from: Cosine Similarity, Cosine Similarity w/ Position Frequency, Copula Based Outlier Detection, and Greedy Heuristic. After this step, our code will recommend the top 5 starting words of that algorithm. Here, the User has a choice to use one of them or just use one of their own. The embedded Wordle game is right next to these recommendations so the User can start to play the Wordle. After each guess, they will write their guess into both the Wordle game and the code on the right. The code will then present the word in blocks that can be toggled to match the output of the Wordle. The User will then repeat this process for the sequencial guesses until they get the correct answer. We got our data from https://gist.github.com/cfreshman/cdcdf777450c5b5301e439061d29694c and https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b which are the solutions and allowed guesses, respectively. We combined these lists to get the full list that we thin out as you guess.

# Using our Code #
All of the results of our code can be utilized by the embedded algorithms and Wordle game. However, in the event that you want to download our files to see other results, we will explain that here.  
First you should download the zip file, which you already have done to access this README.md file. Next, you will open them in an IDE, we used VS Code so we recommend that. In our code, we utilized command line arguments to change between different algorithms. The Cosine Similarity code and driver is in C++ while the Copula Outlier Detection and Greedy Heuristics is in Python. Therefore, the setup process is slightly different.  
## Cosine Similarity ##
To run the Cosine Similarity UI, you must be using a Linux environment or WSL. Otherwise, the code will not compile due to the getopt function library only being available on Linux. To compile, run the command ```g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -g3 -DDEBUG  main.cpp wordleFunctions.cpp -o wordle -lm```. This should add a file called "wordle" to your present working directory. To run the program there are two options. You can choose to run it using the regular Cosine Similarity algorithm, or you can choose to run it using the positional Cosine Similarity algorithm. For either algorithm you will run the program by adding a flag to the command line "-m" or "--method". After this flag, you will then type the characters "c" for regular Cosine Similarity or "p" for positional Cosine Similarity. When put all together, the command to run the program would look like ```./wordle -m c ``` or ```./wordle -m p ``` for either method.

Once the program is running, it should prompt you with the top 5 guesses based on the algorithm chosen. It will also prompt you with what word you want to guess. You are free to enter any word as long as it is five letters and valid according to the word bank. If the word is invalid, the program will prompt you to reenter the word. Next, the program will prompt you to enter the correctness of each letter. For a letter not in the word, enter a "-". For a letter in the word and in the wrong place, enter a "y". For a letter in the word and in the correct place, enter a "g". For example, for a guess that has the first letter in the wrong place and in the word, the second letter in the word and in the right place, and all other letters not found in the word, you would enter the string "yg---". This should then cause the UI to prompt you with 5 new top guesses. Repeat this process until you get the right word or lose.

Note: type "ggggg" when you win for the program to congratulate you :)

## Copule Outlier Detection ##
First you want to activate the virtual enviornment with ``` source venv/bin/activate ```. You should then see the bash terminal change to accomodate this by having (venv) prior to your normal bash. Then you will run ``` python3 copod.py ```. The results of this will produce a variety of frequency analysis graphs that show letter frequency. Additionally, there will be a graph that shows the Distribution analysis to find the best starter word. Lastly, the top ranked words will be output to show the User the best first guesses. One thing to make note of is that this code only shows the best first guess. The code on the website implements the whole game by eliminating words from the potential guess list. 

## Greedy Heuristics ##
The final program is simply one that runs the greedy heuristic to generate the expected value scores for each word. Same as the COPOD python file, you will want to activate the virtual enviornment with ``` source venv/bin/activate ```. Then, you simply need to navigate to the directory containing GreedyHeuristic.py. Then you will run ``` python3 GreedyHeuristic.py ```. This program will then compute the expected value summation for each of the 12,966 words, which may take a while (approximately 36 hours). At the end, the program will create a new .txt file containing each word and its expected value, comma separated. During the processing, the program will also concurrently print the word in progress, along with its expected value once it's done with the summation. The completed .txt file containing each word and score is "GreedyHeuristicRank.txt".
