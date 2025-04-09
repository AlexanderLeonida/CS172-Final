///////////////////////////////////////////////////////////////////////////////////////
//
// Name: Noah Dunham & Alex Leonida
// Date: 12/13/2023
// Course Code: CS-172-2
//
// Collaborators: none
//
// Resources used: See documentation.md file
//
// Code Copyright (C) Noah Dunham & Alex Leonida 2023
// Articles Copyright (C) NPR - you may NOT download, distribute, publish, or any any way claim any file or content within "testing files" nor "training files" to be your own
// NPR in no way is associated with this code, and does not necessarily support it's use
// Link to NPR: https://www.npr.org/
//
////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <vector>
using namespace std;

class Training{
    private:
        // represents total word count of all words. assumes variable can NOT be ""
        int wordCount; 
        // classification of training object
        string name;
        //vector of the different words found within the different text files
        vector<string> words;
        //vector of the number of times each word showed up from the different files used to train the model
        vector<int> values;
        //vector of the different file paths the model trained against. we don't train against the same filepath more than once
        vector<string> filePaths; 

        // trains all words in the file 'inputPath' using trainLine
        // adds inputPath param to filePaths instance variable 
        void trainAllWords(string inputPath);
        // trains an induvidual line in a fail ('line') using trainWord
        void trainLine(string line);
        // trains against the single word 'word'
        void trainWord(string word);
        //removes all non-alpha chars in 'word'
        //if the word includes a capital letter, returns ""
        //assumes param word is a string containing no spaces
        //word param is the word being ridded of all non lowercase alpha characters. if word has a capital letter anywhere, entire word is voided and "" is returned
        void sanitize(string &word) const;
        //returns the substring of line from the start until the first space (non inclusive)
        //line is changed to the substring from the char after the first space until the end
        //if no space exists, returns line and line is set to "" 
        //assumes there are no spaces at the start of the line and that there are no multiple spaced lines as explained in commented in the method
        string regexSpace(string &line) const;

    public:
        // constructor
        // name represents the classification (like "sports")
        // name can NOT be ""
        Training(string name);
        
        // takes a path to a training file ('inputPath')
        // checks if we have already trained against this file
        // also checks if the file exists
        // if we haven't trained against it and it exists, train against it and return true
        // if the traing fails for whatever reason, return false
        bool train(string inputPath);

        //returns true if the file  existed before this call
        //returns false if the file did not exist before this call
        //does not create the file if it did not exist
        //param outputPath is a string of the path attempting to be opened
        static bool checkFilePath(string outputPath);

        //word param represents the word being checked in words vector
        //return the number of times word has appreared in the filepaths 
        int getValueForWord(string word) const;
        //return string word found at index within words vector
        string getWordAtIndex(int index) const;
        //return int value found at index within values vector
        int getValueAtIndex(int index) const;
        //returns the int size found in vector words
        //aka the number of unique words found from all filepaths trained
        int getUniqueWords() const;
        //returns the total word count 
        //aka size of all values summed in values
        //aka wordCount instance var
        int getCount() const;
        //returns instance variable name
        string getName() const;

};