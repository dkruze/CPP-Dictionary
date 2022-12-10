//Filename: dictionary.cpp
//Author: Daniel Kruze
//Create Date: 11/1/21
//Compile Date: 11/20/21

#include <iostream> // cout, cin
#include <fstream> // input from file
#include <bits/stdc++.h> // non-input related libraries
#include "dictionaryHash.h" // hash table class, reworked from previous assignment

using namespace std; // standard namespace

vector<string> inputContainer; // vector for holding read-in strings
string k; // string for holding user input

/*
* The following function checks a string to make sure it has no spaces in it
* Before it is checked, the given string is permanently parsed to lowercase
* Expected input: string to be checked
* Expected output: false if a space is found, true otherwise
*/
bool spaceCheck(string word) { // accepts a string as an argument
    int length = word.length(); // let an integer hold the length of the given string
    for (int j = 0; j < length; j++) { // for as many characters are in the given string
        char c = word[j]; // let a character hold the current character of the string
        word[j] = (tolower(c)); // the current character of the string is now the lowercase version of its previous self
    }
    for (int i = 0; i < length; i++) { // for as many characters are in the given string
        int letter = word[i]; // let an integer be the index of current character of the given string
        if (isspace(letter)) { // if the character is a space
            return false; // end function
        }
    }
    return true; // end function if no spaces were found
};

int main() {
    ifstream inputDict; // let a variable hold input from an external file
    inputDict.open(("Dictionary.txt")); // read input from Dictionary.txt
    if (inputDict.fail()) { // if input can't be read, like if Dictionary.txt is not in the present directory
        cout << "Stream Error: Dictionary failed to load!\nPlease move \"Dicitonary.txt\" to the current directory and run again." << endl; // ask the user to reorganize Dictionary.txt
        exit(0); // end program
    }
    string word; // let a string represent words from the input file
    int lineCounter; // let an integer represent the number of lines in the input file
    while (getline(inputDict, word)) { // while there is data in the input file to be read
        inputContainer.push_back(word); // push a single word from the input file into the given vector
        lineCounter++; // increase the line count--each line only has one word
    }
    chainTable bryan(lineCounter); // instance of the dictionary table class
    for (int i = 0; i < inputContainer.size(); i++) { // for every word in the vector that holds input words
        bryan.insert(inputContainer[i], i); // hash-insert the current word into the table
    }
    bool sentryMain = true; // sentry for the following while loop
    while (sentryMain) { // while sentry = true
        cout << "To quit, type \"quit.\"\nPlease enter a single word, without spaces:\n>> "; // there are only strings in the table
        getline(cin, k); // string k = user input
        if (cin.fail()){ // if the user enters a non-string
            cin.clear(); // clear the error flag that cin throws
            cin.ignore(100000, '\n'); // ignore up to 100,000 entered characters (technically, an input of 100,001 characters could break this program)
            cout << "Invalid input!" << endl; // warn the user their input is invalid, let them try again
        }
        else if (!cin.fail()) { // if the user enters a string
            bool kk = spaceCheck(k);
            if (!kk) { // if the string happens to have a space in it
                cout << "Invalid Input!" << endl; // warn the user their input is invalid, let them try again
            }
            else if (k == "quit") { // the user opts to stop querying the dictionary
                sentryMain = false; // end the loop
            }
            else { // if the user enters a valid string
                bool wordFound = bryan.search(k); // let a variable hold the boolean result of a search for the user's string (this will run the search and display its results)
                sentryMain = false; // end the loop
            }
        }
    }
    return 0; // end driver
}