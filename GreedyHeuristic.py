import math
from tabnanny import verbose 
def split_str_to_char(str):
    return [char for char in str]

class Greedy(object):
    def __init__(self, WORDSFILE, hard_mode = False, Verbose = False):
        self.WORDSFILE = WORDSFILE
        self.hard_mode = hard_mode
        self.Verbose = Verbose
        self.squares = ["-","-","-","-","-"]
        self.guess = ""
        self.stage = 1
        self.gamelist = self.get_list(WORDSFILE).copy()
        self.wordf = self.get_list(WORDSFILE).copy()
        self.previouslistlen = 0
        self.list_size = 0
        self.exhausted_letters = []
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
        if(self.hard_mode and input not in self.gamelist):
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
        #returns true or false game end - updates squares list with user input representing wordle squares/game state
        while(True):
            inp = input("Enter squares ('y' for Yellow, 'g' for Green, '-' for Wrong Letter): ")
            if(self.check_squares_valid(inp)):
                break
            else:
                print("Invalid input, try again")
        self.squares = split_str_to_char(inp)
        if("y" not in self.squares and "-" not in self.squares):
            return True
        return False

    '''
    process
    '''
    def generate_square_perms(self):
        sq = ["g", "y", "-"]
        sqperms = []
        perm = "" 
        for a in sq:
            for b in sq:
                for c in sq:
                    for d in sq:
                        for e in sq:
                            perm = a+b+c+d+e
                            sqperms.append(perm)        
        sqperms.remove('ggggg')
        sqperms.remove('ggggy')
        sqperms.remove('gggyg')
        sqperms.remove('ggygg')
        sqperms.remove('gyggg')
        sqperms.remove('ygggg')
        return sqperms

    def reset_game(self):
        self.squares = ["-","-","-","-","-"]
        self.guess = ""
        self.stage = 1
        self.gamelist = self.wordf.copy()
        self.previouslistlen = 0
        self.list_size = 0
        self.exhausted_letters = []

    def remaining_words(self):
        #returns a list of strings - remaining guessable words
        rem = self.gamelist
        self.previouslistlen = len(rem)
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
                elif(self.squares[i] == "-" and split_str_to_char(self.guess)[i] not in self.exhausted_letters):
                    self.exhausted_letters.append(split_str_to_char(self.guess)[i])
                elif(self.squares[i] == "-" and split_str_to_char(self.guess)[i] in word_letters):
                    remove=True
                elif(word_letters[i] in self.exhausted_letters):
                    remove=True
            if(remove): rem.remove(word)
        self.gamelist = rem
        self.stage += 1
        return rem

    def remaining_words_lite(self):
        #returns number of remaining guessable words
        ct = 1
        self.gamelist.remove(self.guess)
        for word in self.gamelist:
            remove = False
            word_letters = split_str_to_char(word)
            for i in range(5):
                if(self.squares[i] == "g" and word_letters[i]!=split_str_to_char(self.guess)[i]):
                    remove=True
                elif(self.squares[i] == "y" and split_str_to_char(self.guess)[i] not in word_letters):
                    remove=True
                elif(self.squares[i] == "y" and word_letters[i]==split_str_to_char(self.guess)[i]):
                    remove=True
                elif(self.squares[i] == "-" and split_str_to_char(self.guess)[i] not in self.exhausted_letters):
                    self.exhausted_letters.append(split_str_to_char(self.guess)[i])
                elif(self.squares[i] == "-" and split_str_to_char(self.guess)[i] in word_letters):
                    remove=True
                elif(word_letters[i] in self.exhausted_letters):
                    remove=True
            if(remove): ct += 1
        return 12966-ct

    def expectedinfo(self):
        p = len(self.gamelist)/self.previouslistlen
        if p==0:
            return 0
        return p*math.log(1/p,2)

    def expectedinfo_lite(self, n):
        p = n/12966
        if p==0:
            return 0
        return p*math.log(1/p,2)
    def probsum(self, n):
        p = n/12966
        if p==0:
            return 0
        return p
    """
    wordle game
    """

    def wordle_helper(self):
        #eventually - enter word, enter game state, suggest list of words
        while True:
            self.read_input_word()
            if(self.read_input_squares() or self.stage == 6):
                print("End")
                break
            remwords = self.remaining_words()
            if(self.Verbose):
                print("Exhausted letters: ")
                print(self.exhausted_letters)
                print("Game List Size: ")
                print(len(self.gamelist))
                print("Previous List Size: ")
                print(self.previouslistlen)
                print("Probability: ")
                print(len(self.gamelist)/self.previouslistlen)
                print("Expected Information Value: ")
                print(self.expectedinfo())
    
    def generate_greedy_ranks(self):
        sqperms = self.generate_square_perms()
        ranks = []
        ct = 1
        for word in self.gamelist[:]:
            E = 0
            for perm in sqperms:
                self.guess = word
                self.squares = perm
                n = self.remaining_words_lite()
                E += self.expectedinfo_lite(n)
                self.reset_game()
            print(ct)
            print(word)
            print(E)
            ct += 1
            ranks.append([word, E])

        with open('GreedyHeuristicRank.txt', 'w') as f:
            for item in ranks:
                f.writelines(item[0] + ", " + str(item[1]) + "\n")

        
if __name__ == "__main__":
    greedygame = Greedy(WORDSFILE = "wordleFullList.txt", Verbose=True)
    greedygame.generate_greedy_ranks()


