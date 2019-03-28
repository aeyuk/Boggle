# Boggle
Cate Yuk

## Description
This project is the game of Boggle coded in C. The implementation involves a dictionary read in through a file, with the words being stored in a trie. Valid words are found using a Depth First Search. A user finds words against a computer.

## Link to Project Video
[Boggle Demonstration](https://www.youtube.com/watch?v=u_twsVHbKwY&feature=youtu.be)

## General Implementation Notes

### Dictionary File:
This implementation uses the built in words unix file found in the /usr/share/dict/words path. Proper nouns are skipped, as well as any words containing non-alpha characters (Example: "a-ok").

### Board Size:
The board is of arbitrary square size (but at least size 2x2), depending on user input. Error messages will occur if the inputted board size is not an integer greater than or equal to 2. It should be noted that larger board sizes can inhibit the view of the board, as well as the board's formatting. Around size 60 will almost guarantee the user having to scroll to view the board in its entirety. **Using fullscreen mode is strongly encouraged.** Q will appear as Qu in all cases.
 
### Difficulty:
A player plays against a computer. The computer finds all possible words on the board, but difficulty can be selected to limit the percentage and complexity (word length) of words found. Difficulty levels include levels 1 through 5, with 5 being the most difficult. Error messages will occur if the inputted board size is not 1, 2, 3, 4, or 5.

### Computer Finding Words:
The computer finds and stores all valid words on the board using a Depth First Search, with valid words being searched in the trie, and valid prefixes continuing in the DFS. Valid words are at least 3 letters long. Duplicate words will not be stored more than once. The maximum amount of word the computer can find is assumed to be all the words in the dictionary.

### User Finding Words:
The user will be able to enter words found. In order to be a valid word, the word must be found in the trie, and the word must be on the board (meaning the computer previously found it). If the user finds a word, that word is marked as playerFound. The max word size entered is assumed to be the length of 47, assuming the longest word in the dictionary is 47 characters long. Input of invalid non-alpha characters will cause an "Invalid characters" error message. Invalid words will receive an "Invalid word" error message. Users can input duplicate words, but in the end, these will only be scored as having earned points on the first enter. The user has a time limit of 3 minutes to find as many words as possible. Once time has run out, **the user has the chance to enter a word one more time.** This guarantees the user having at least one attempt at a word. If the user wishes, the round can be ended early on the input of 'q'.

### Scoring System
The scoring system complies with the traditional rules of boggle. Words the computer and user have both found will cancel out points. These words will still be displayed, but will be marked by two X's. Duplicate words will only be counted once. The winner of the round will gain a point on the overall game score, which will be stored as long as the player wishes to keep the match going. After a round is over, the user has the chance to see all the words they did not find on the board, when prompted. Entering 'y' will show the words. Any other input will skip the option. When prompted, if the user wishes to continue the match with the computer, any key can be entered and the match will continue. If 'q' is entered, the match will end. 
 
 
