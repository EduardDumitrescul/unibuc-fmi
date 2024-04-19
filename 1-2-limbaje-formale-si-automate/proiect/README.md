# DFA & NFA 
> implemented in C++

---

## Contents
### DFA class 
- void readFromFile(string) -> builds the current DFA with data provided from file
- bool checkWord(string) -> return true if the current word is accepted by the DFA
- vector<int> checkWordPrintPath(word) -> returns the states path which accepts the current word, or an empty array if the word is rejected
### NFA class
- void readFromFile(string( -> builds the current N FA with data provided from file
- bool checkWord(string) -> return true if the current word is accepted by the NFA
- vector<vector <int>> checkWordReturnPaths(string) -> return all the states paths which accept the word
- DFA asDFA() -> return an DFA equivalent with the current NFA

---

### Input Format
For DFA and NFA
```
number_of_states initials_tate
number_of_final_states final_state_1 final_state_2 ...
number_of_transiotions
source_state_1 letter destination_state_1
source_state_2 letter destination_state_2
.....
```
