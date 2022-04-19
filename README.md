# WordleHelper #
The purpose of this is to act as a helper for solving the game Wordle. This program takes in your initial guess and the results of the guess to suggest a next best guess. In the following rounds, the user will input the results of the guess to narrow down the word list.  
In our application, we have created two different WordleHelper funcationalities. The first one is Rank Your Starter Word which runs each algorithm on the User's input word. It then outputs the ranks that each algorithm gives the word along with the words immediately above and below it so the User can see what words are of similar rank. This process can be repeated for as many words as the User desires as long as the word exists in the Word list, which is the NYT allowed guesses.  
The second functionality is the Wordle Helper itself. It is integrated into an embedded wordle game which you play side by side with the Helper. We have imported our code from C++ into JavaScript in order to run the same algorithms on the website. The User starts by selecting the specific algorithm that they want to use from the drop down menu. At this time, we have 4 to choose from: Cosine Similarity, Cosine Similarity w/ Position Frequency, Copula Based Outlier Detection, and Greedy Heuristic. After this step, our code will recommend the top 5 starting words of that algorithm. Here, the User has a choice to use one of them or just use one of their own. The embedded Wordle game is right next to these recommendations so the User can start to play the Wordle. After each guess, they will write their guess into both the Wordle game and the code on the right. The code will then present the word in blocks that can be toggled to match the output of the Wordle. The User will then repeat this process for the sequencial guesses until they get the correct answer.  

# Using our Code #
All of the results of our code can be utilized by the embedded algorithms and Wordle game. However, in the event that you want to download our files to see other results, we will explain that here.  
First you should download the zip file, which you already have done to access this README.md file. Next, you will open them in an IDE, we used VS Code so we recommend that. In our code, we utilized command line arguments to change between different algorithms. The Cosine Similarity code and driver is in C++ while the Copula Outlier Detection and Greedy Heuristics is in Python. Therefore, the setup process is slightly different.  
## Cosine Similarity ##


## Copule Outlier Detection ##
First you want to activate the virtual enviornment with ``` source venv/bin/activate ```. You should then see the bash terminal change to accomodate this by having (venv) prior to your normal bash. Then you will run ``` python3 copod.py ```.

## Greedy Heuristics ##

