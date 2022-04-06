import math 
def split_str_to_char(str):
    return [char for char in str]

class Greedy(object):
    def __init__(self, WORDSFILE, hard_mode = False, Verbose = False):
        self.WORDSFILE = WORDSFILE
        self.hard_mode = hard_mode
        self.Verbose = Verbose
        self.squares = ["-","-","-","-","-"]
        self.guess = ""
    
    """
    read from files
    """

    def get_list(self, list):
        result = []
        with open(list) as fp:
            result.extend([word.strip() for word in fp.readlines()])
        return result

    """
    user input
    """

    def check_word_valid(self, input):
        valid = False
        if(len(input) != 5):
            return False
        for word in self.get_list(self.WORDSFILE):
            if (input.lower()==word):
                valid = True
        return valid

    def check_squares_valid(self, input):
        valid = True
        if(len(input) != 5):
            return False
        for c in input:
            if (c.lower()!="g" and c.lower()!="y" and c.lower()!="-"):
                valid = False
        return valid

    def read_input_word(self):
        #returns string - user input for guessed word
        while(True):
            inp = input("Enter word: ")
            if(self.check_word_valid(inp)):
                break
            else:
                print("Invalid input, try again")
        self.guess = inp

    def read_input_squares(self):
        #returns a list of characters - user input representing wordle squares/game state
        while(True):
            inp = input("Enter squares ('y' for Yellow, 'g' for Green, '-' for Wrong Letter): ")
            if(self.check_squares_valid(inp)):
                break
            else:
                print("Invalid input, try again")
        self.squares = split_str_to_char(inp)
    
    def remaining_words(self):
        #returns a list of strings - remaining guessable words (WIP)
        rem = self.get_list(self.WORDSFILE)
        rem.remove(self.guess)
        for word in rem[:]:
            remove = False
            word_letters = split_str_to_char(word)
            for i in range(5):
                if(self.squares[i] == "g" and word_letters[i]!=split_str_to_char(self.guess)[i]):
                    remove=True
                elif(self.squares[i] == "y" and split_str_to_char(self.guess)[i] not in word_letters):
                    remove=True
                elif(self.squares[i] == "y" and word_letters[i]==split_str_to_char(self.guess)[i]):
                    remove=True
            if(remove): rem.remove(word)

        return rem

    """
    wordle game
    """

    def wordle_helper(self):
        #eventually - enter word, enter game state, suggest list of words
        self.read_input_word()
        self.read_input_squares()
        print(self.remaining_words())
    
    def sim():
        return False

        
if __name__ == "__main__":
    greedygame = Greedy(WORDSFILE = "wordleFullList.txt")
    greedygame.wordle_helper()


