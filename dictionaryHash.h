//Filename: dictionaryHash.h
//Author: Daniel Kruze
//Create Date: 11/15/21
//Compile Date: 11/16/21

// make sure this header and included headers are defined once and only once
#ifndef DICTIONARYHASH_H
#define DICTIONARYHASH_H
#endif

#include <iostream> // cin, cout
#include <bits/stdc++.h> // everything else
#include "TimeInterval.h" // timer functions

using namespace std; // standard namespace

vector<string> suggestions; // global vector for holding spelling suggestions

/*
* This is the class for a simple, chained hash table (minus a removal method)
* This class has a linked list member for holding linked-lists of repeat values, and a member for the size of that list
* It has a method to insert into the table as well as a function to search and display inserted values
* It also includes a multiplicative hashing function, as well as a display and search function (the latter with user input)
* Finally, it has a method to return suggested words for similarities between searched words and the first two letters of existing words, as wella s a method to suggest similarly spelled words
* It is initialized to have its size specified during runtime
*/
class chainTable {
    list<string> *chain; // doubly-linked list of strings
    int size; // integer size of the list above

    public:
        chainTable(int); // constructor, accepts an int that will be the size
        ~chainTable(); // destructor
        int hashMethod(int); // multiplicative hashing function
        void insert(string, int); // insert into the hash table
        void remove(string); // remove from the hash table
        void display(); // display the hash table's words, with chains
        bool search(string); // search for the given word
        void suggest(string); // suggest similar words
        string spellCheck(string); // check spelling
};

/*
* Construct the table of variable size, then let the user know it exists
* Expected input: integer for size of list
* Expected output: hash table with chains of size specified by main program
*/
chainTable::chainTable(int _size) {
    cout << "Table initialized!" << endl; // let the user know the table exists
    this->size = _size; // let the size of the linked-list be the given argument of this constructor
    this->chain = new list<string>[this->size]; // initialize linked-list with size specified above
};

/*
* Destroy the table when it exits scope
* Expected input: table with existing linked-list chain
* Expected output: n/a
*/
chainTable::~chainTable() {
    chain->clear(); // remove and dereference all members in the linked list
    delete chain; // delete the linked list reference itself
    cout << "Table annihilated!" << endl;
};

/*
* A multiplicative hashing function for finding keys to insert values into
* Expected input: integer _key given at runtime
* Expected output: integer hashed key computed from argument
*/
int chainTable::hashMethod(int _key) { // accept an integer key as a parameter
    srand(time(NULL)); // seed the rng
    float A = (float)rand()/RAND_MAX; // let A be a random float between 0 and 1
    int hashedKey = abs((chain->size()) * fmod((_key * A), 1.0)); // the hashed key is given by a multiplicative hash formula using the current size of the linked list as a bound
    return hashedKey; // return this key for insertion
};

/*
* Inserts a hashed key into the table by giving it a spot in the linked list and pushing it into that spot
* This includes a call to the hashing function method
* Expected input: string to hold at a slot in the table, integer index that the string will be held at
* Expected output: new value in the hash table--also a member of a linked list
*/
void chainTable::insert(string _word, int _key) { // accept an integer _key as a parameter
    int index = hashMethod(_key); // let an integer hold the hashed key for the given string
    chain[index].push_back(_word); // push that string onto the table at a spot given by the hashed key
};

/*
* Removes a word the table by searching for it until its located, then iterating to it until it can be removed
* This function sort through every element of the linked list by iterating through everything being pointed to by each element's head
* If a pointer to the word is located, that particular element is iterated through again until its precise position is found
* Expected input: string that may or may not be contained in the dictionary
* Expected output: empty,dereferenced spot where given string used to be
*/
void chainTable::remove(string _word) { // accept user input parameter
    bool valueFound = false; // boolean that determines what will be printed
    string temp; // temporary string for holding unparsed strings
    for (int i = 0; i < chain->size(); i++) { // iterate this->size times
        for (auto x : chain[i]) { // for every variable x of the same type as a member of a linked list at index i (string)
            temp = x; // word in the dictionary is stored as-is before being parsed (into lowercase)
            for (int j = 0; j < x.length(); j++) { // for every character in the word being evaluated on this pass
                char c = x[j]; // let a character hold the current character in the given word
                x[j] = (tolower(c)); // the word's current character is replaced by the lowercase version of its previous self
            }
            if (x != _word) { // if the current slot is not the word to be removed
                x = temp; // the word in the dictionary is restored to its unparsed self
                temp = ""; // temporary string is emptied
                continue; // move on to the next pass
            }
            else { // when the specified word has been found
                valueFound = true; // flag for later that will be used for printing
                list<string>::iterator itChain = chain[i].begin(); // create an iterator for the chain member where the given word was found
                while (*itChain != _word) { // until the iterator is pointing to the position of the word to be removed
                    advance(itChain, 1); // move the iterator forward 1
                }
                chain->erase(itChain); // dereference the word at the iterator's position, since it is the word to be removed
                cout << "\"" << _word << "\" was successfully removed from dictionary!" << endl; // notify the user that their word has been removed
                break; // end the loop, the value has been found
            }
        }
    }
    if (valueFound == false) { // if no slot containing _word was ever found (the flag was not set)
        cout << "\"" << _word << "\" was not found in the dictionary!" << endl; // let the user know the search was empty
    }
}

/*
* Display the table and its included linked lists by iterating through the table
* This prints out a number for each spot in the linked list and indicates linked-lists of repeat values with an arrow -->
* If the repeat values are the same, do not keep printing them--this removes repeat values from the display
* Expected input: hash table of this->size
* Expected output: this->size lines on the command line representing slots in a table
*/
void chainTable::display() {
    string previous; // let an string hold the previously printed value (for a linked list)
    for (int i = 0; i < chain->size(); i++) { // iterate this->size times
    cout << i + 1; // print out a number representing one of the slots in the table
    for (auto x : chain[i]) { // for a variable x of the same type as a member of a linked list at index i
        if (x == previous) { // if this member is the same as the previous member (repeat value)
            break; // stop printing this linked list
        }
        cout << " --> " << x; // print an arrow then the member of the list, indicating a linked list
        previous = x; // let the string previous hold the value that was just printed
    }
    cout << endl; // line break
  }
};

/*
* Search for a string in the table and print the word that matches
* This iterates through every member of the hash table and through their linked values (should they have them)
* When the slot is at the value containing the given word or a reference to it, notify the user
* If applicable, provide suggestions for words similar by their first two letters to the searched word
* Additionally, use included timer functions to print the execution time of the search
* Expected input: string value of _word
* Expected output: message that the string does or does not exist, with applicable suggestions
*/
bool chainTable::search(string _word) { // accept user input parameter
    string temp; // temporary string for holding unparsed strings
    TimeInterval timer; // instance of a timer class
    timer.start(); // begin timing execution
    for (int i = 0; i <= chain->size(); i++) { // iterate this->size times
        for (auto x : chain[i]) { // for a variable x of the same type as a member of a linked list at index i (string)
            temp = x; // word in the dictionary is stored as-is before being parsed (into lowercase)
            for (int j = 0; j < x.length(); j++) { // for every character in the word being evaluated on this pass
                char c = x[j]; // let a character hold the current character in the given word
                x[j] = (tolower(c)); // the word's current character is replaced by the lowercase version of its previous self
            }
            if (x != _word) { // if the current slot is not the word to be removed
                x = temp; // the word in the dictionary is restored to its unparsed self
                temp = ""; // temporary string is emptied
                continue; // move on to the next pass
            }
            else { // when at a slot containing _word
                x = temp; // the word in the dictionary is restored to its unparsed self
                temp = ""; // temp variable is emptied
                cout << "\"" << x << "\" is valid in the dictionary!" << endl; // notify the user that their string exists in the table
                suggest(_word); // generate suggestions
                if (suggestions.size() > 0) { // if suggestions have been found
                    cout << "Similar words include:\n" << endl; // begin printing suggestions
                    for (int j = 0; j < suggestions.size(); j++) { // for every suggestion
                        cout << suggestions[j] << endl; // print current suggestion
                    }           
                }
                else { // if no suggestions were found
                    cout << "No similar words found...sorry!" << endl; // notify the user that no suggestions exist
                }
                timer.stop(); // stop timing execution
                cout << "Execution time: " << timer.GetInterval() << "microseconds" << endl; // display the execution time
                return true; // end function
            }
        }
    }
    cout << "\"" << _word << "\" was not found in the dictionary!" << endl; // let the user know the search was empty since the function has not returned
    string suggestSpell = spellCheck(_word); // let a string hold an attempt to generate a spelling suggestion
    if (suggestSpell != "nothing") { // if the word has a spelling suggestion
        string response; // let a string hold user input
        bool sentrySuggest = true; // sentry for the following while loop
        while (sentrySuggest) { // while sentry = true
            cout << "Did you perhaps mean: \"" << suggestSpell << "?\"" << endl; // provide spelling suggestion
            cout << "Please answer \"yes\" or \"no.\"" << endl; // directions for response
            getline(cin, response); // string response = user input
            if (cin.fail()){ // if the user enters a non-string
                cin.clear(); // clear the error flag that cin throws
                cin.ignore(100000, '\n'); // ignore up to 100,000 entered characters (technically, an input of 100,001 characters could break this program)
                cout << "Invalid input!" << endl; // warn the user their input is invalid, let them try again
            }
            else if (!cin.fail()) { // if the user enters a string
                int length = response.length(); // let an integer hold the length of the given string
                for (int k = 0; k < length; k++) { // for as many characters are in the given string
                    char c = response[k]; // let a character hold the current character of the string
                    response[k] = (tolower(c)); // the current character of the string is now the lowercase version of its previous self
                }
                if (response == "yes") { // if the string happens to have a space in it
                    suggest(suggestSpell); // generate suggestions based off of corrected word
                    sentrySuggest = false; // end loop
                }
                else if (response == "no") { // if the user enters a valid string
                    suggest(_word); // generate suggestions based off of user word
                    sentrySuggest = false; // end loop
                }
                else {
                    cout << "Invalid Input!" << endl; // warn the user their input is invalid, let them try again
                }
            }
        }
    }
    if (suggestions.size() > 0) { // if suggestions have been found
        cout << "Similar words include:\n" << endl; // begin printing suggestions
        for (int j = 0; j < suggestions.size(); j++) { // for every suggestion
            cout << suggestions[j] << endl; // print current suggestion
        } 
    }
    else { // if no suggestions were found
        cout << "No similar words found...sorry!" << endl; // notify the user that no suggestions exist
    }
    timer.stop(); // stop timing execution
    cout << "Execution time: " << timer.GetInterval() << "microseconds" << endl; // display the execution time
    return false; // end function
};

/*
* Search for similar words to a given string, based off the first two letters
* When similar words are found, place them in the suggestions vector
* Expected input: string value of _word
* Expected output: values in the global vector
*/
void chainTable::suggest(string _word) {
    suggestions.clear();
    string firstLettersW = "  "; // let a string represent the first two letters of the given string
    firstLettersW[0] = _word[0]; // letter 1 = _word[0]
    firstLettersW[1] = _word[1]; // letter 2 = _word[1]
    for (int i = 0; i < chain->size(); i++) { // iterate this->size times
        for (auto x : chain[i]) { // for every variable x of the same type as a member of a linked list at index i (string)
            string firstLettersX = "  "; // let a string represent the first two letters of the current string
            firstLettersX[0] = x[0]; // letter 1 = x[0]
            firstLettersX[1] = x[1]; // letter 2 = x[1]
            if (firstLettersX != firstLettersW) { // if the first letter of a given word isn't the same as the first letter of the current dictionary word
                continue; // move on to the next pass
            }
            else { // when a letter match for the specified word has been found
                list<string>::iterator itChain = chain[i].begin(); // create an iterator for the chain member where the given word was found
                while (*itChain != x) { // until the iterator is pointing to the position of the word that matched
                    advance(itChain, 1); // move the iterator forward 1
                }
                string temp = *itChain; // let a string represent the string to which the iterator points
                if (temp != _word) { // if the string we have found is not the same as what we have already searched
                    temp = temp + "\n"; // add a line break to the end of the string
                    suggestions.push_back(temp); // push that string onto the vector for suggestions
                }
            }
        }
    }
};

/*
* Provide a suggestion based off of the first letter of a given word
* The first word that shares a letter in common with the given string is returned
* Expected input: string value of _word
* Expected output: word in the dictionary with a similar first letter, should one exist
*/
string chainTable::spellCheck(string _word) {
    char firstLetterW = _word[0]; // let a char represent the first letter of the given string
    bool valueFound = false; // boolean that determines what will be printed
    for (int i = 0; i < chain->size(); i++) { // iterate this->size times
        for (auto x : chain[i]) { // for every variable x of the same type as a member of a linked list at index i (string)
            char firstLetterX = x[0]; // let a char represent the first letter of the current string
            if (firstLetterX != firstLetterW) { // if the first letter of a given word isn't the same as the first letter of the current dictionary word
                continue; // move on to the next pass
            }
            else { // when a letter match for the specified word has been found
                valueFound = true; // flag for later that will be used for printing
                list<string>::iterator itChain = chain[i].begin(); // create an iterator for the chain member where the given word was found
                while (*itChain != x) { // until the iterator is pointing to the position of the word that matched
                    advance(itChain, 1); // move the iterator forward 1
                }
                return *itChain; // the string to which the iterator points will be returned
            }
        }
    }
    if (valueFound == false) { // if no slot containing _word was ever found (the flag was not set)
        return "nothing"; // return a default string
    }
};