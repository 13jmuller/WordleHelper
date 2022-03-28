# Implementation of COPOD Machine Learning Algorithm

# Frequency Analysis on Word list
from unittest import result
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import string
import re
from typing import List
from collections import Counter
from tqdm import tqdm
from pyod.models.copod import COPOD


msg = 'hello'
print(msg)
# Read in word list
pd.set_option('display.max_column', None)

# funtion to read in the file of possible words
def readWordList(file_name:str):
    result = []
    with open(file_name) as fp:
        testing = 'code got here'
        print(testing)
        # adds words to end of array and removes the white space
        result.extend([word.strip() for word in fp.readlines()])

    return result

# establishes the alphabet
alpha = list(string.ascii_lowercase)

# reads in the word lists from text files
possibleWordList = readWordList("wordleAllowedGuesses.txt")
solutionWordList = readWordList("wordlePrompts.txt")

# makes dictionary for occurances of each letter
totalWords = ''.join(solutionWordList)
letterOccurances = dict(Counter(totalWords))

# Dataframe for frequency of letter
# loops through each words until the end of the list
letterFreq = {k:v/len(solutionWordList)for k,v in letterOccurances.items()}

# creates dataframe that has letters and frequency on either axis --> sorts them by increasing freqnecy
# keys are the ltters and values are the frequency --> kinda like a map in C++
letterFreq = pd.DataFrame({'Letter':list(letterFreq.keys()), 'Frequency':list(letterFreq.values())}).sort_values('Frequency', ascending=False)
print(letterFreq)
msg2 = "test"
print(msg2)

fig,ax = plt.subplots(figsize= (10,6))
sns.barplot(x = 'Letter', y='Frequency', data=letterFreq)
ax.set_title('Frequency of Letters in all Possible Guesses')

# position frequency
letterFreqCols = []
for letter in alpha:
    for position in range(5):
        letterFreqCols.append(f'{letter}{position}')

# dataframe for the position matrix
letterPositionFreq = pd.DataFrame()

# looping through the accepted guesses
for word in tqdm(solutionWordList):
    # word into letter and position format
    wordPos = ''.join([f"{letter}{pos}" for pos, letter in enumerate(word)])

    # creates counter for position
    letterPositionCounter = {}
    for i in letterFreqCols:
        letterPositionCounter[i] = len(re.findall(i, wordPos))

    tempPosition = pd.DataFrame(letterPositionCounter, index=[word])
    letterPositionFreq = pd.concat([letterPositionFreq, tempPosition])

    letterPositionFreq.head()

# COPOD algorithm






