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

#include "../headers/Training.h"
#include <fstream>

Training::Training(string name){
    this->name = name;
    //sets total word count to 0
    wordCount = 0;
}

bool Training::train(string inputPath){
    //guard against improper filepath arg
    //checks to see if the file path inputted is valid. If it's not, return false. if it is, continue
    if(!checkFilePath(inputPath)){
        return false;
    }
    //loops around all previously trained filepaths
    for(int i = 0; i < filePaths.size(); i++){
        //checks to see if we have already trained against this filepath. if we have, we don't want to retrain against the same filepath so we return false
        if(inputPath==filePaths.at(i)){
            return false;
        }
    }
    //because we haven't trained against this filepath previously and it exists, train all of the words inside of the file. 
    trainAllWords(inputPath);
    return true;
}

void Training::trainAllWords(string inputPath){
    //sets an input fstream object. yes, it could have just been an istream object but we didn't do that. :)
    fstream in;
    in = fstream(inputPath, ios::in | ios::binary);
    string line;
    while(getline(in,line)){
        //trains each line within the fstream object (we just broke it up for structural purposes). we can assume the inputted filepath works because the only place that it's called is inside of the train method which checks that at the top of its method
        trainLine(line);
    }
    //add the filepath to filePaths because it's now trained. it cannot be trained again. 
    filePaths.push_back(inputPath);
}

void Training::trainLine(string line){
    //trains each word in the line
    //we don't increment any variables within this while loop directly due to the regexSpace method which changes the size of the line that's passed in by reference
    while(line.length() > 0){
        //yes we broke it up further
        //train each word in the line
        trainWord(regexSpace(line));
    }
}

string Training::regexSpace(string &line) const{
    //var space is the integer index of the first found space in a string 
    int space = line.find(' ');
    //check to see if there actually is a space within the line that was passed in
    if(space == string::npos){
        string temp = line;
        //changes the line to "" 
        line = "";
        //return the single word with no spaces inside of it (aka what was passed in)
        return temp;
    } else { //means there was a space found somewhere within the string passed in
        // var first is the first word that appears in param line up until and not including the space that follows it
        string first = line.substr(0,space);
        //changes line to entire line excluding the first variable and the space that follows it so that the line doesn't start with a space at the beginning
        //note: assumption is that there are no double spaced lines. ex. "Hi    there". 
        line = line.substr(space+1);
        //return the word that was removed from the line
        return first;
    }
}

void Training::sanitize(string &word) const{
    //holds the value of the current character being checked within the string
    char cur;
    //moves backwards from the end of the word to the beginning for each character in the word
    for(int i = word.length()-1; i >=0; i--){
        //takes the character of each letter in the string from back to front because a string is a vector of chars
        cur = word.at(i);
        //referenced https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html for ascii table values
        //checks to see if the character has a decimal value of 65 - 90, in which case the character would be a capital letter, and we ignore the word completely
        if(65 <= cur && cur <= 90){
            word = "";
            return;
        }
        //checks to see if the character is not a valid lower case alphabet letter, in which case we take out the character and replace it with nothing
        else if (!(97 <= cur && cur <= 122)){
            word.replace(i,1,"");
        }
    }
}

void Training::trainWord(string word){
    //checks to see if the word is proper lowercase alphabet characters only. if not, either void or change the word
    sanitize(word);
    //variable checks 
    bool prev = true;
    //loops as long as word != a word previously in words instance variable or until all words in words are checked against word.........
    for(int i = 0 ; i < words.size() && prev; i++){
        if(word == words.at(i)){
            //if word == a word that was previously checked in words, increase the value corresponding to that word
            //because values and words values at indexes correspond directly to each other, this should make sense
            /*
            for example, words = ["hi", "there", "bobbert"] values = [1, 2, 3]
            this means the word "hi" has showed up once before, "there" twice and so on. 
            If "hi" is the word being passed in as the argument for this method, if we find "hi" within words, we just increment the number in values at the same index by 1
            words = ["hi", "there", "bobbert"] values = [1, 2, 3] -> words = ["hi", "there", "bobbert"] values = [2, 2, 3]
            */
            values[i]++;
            //because it's in words, we can just break the loop instantly because it won't show up twice in the vector
            prev = false;
        }
    }
    //conditional checks if word has been in words before. if it hasn't, enter conditional
    if(prev){
        //we don't want to add "" to words, because it's not a word obviously
        if(word != ""){
            //because it hasn't made an appearance in words before, add it in 
            words.push_back(word);
            //give it a value of 1 as well because it's the first time it showed up
            values.push_back(1);
            //increment word count which represents the total words
        }
    }
    //increment word count which represents the total words
    wordCount++;
}

bool Training::checkFilePath(string outputPath){
    //create a test fstream object in order to see if opening the file path will work
    fstream test;
    bool out;
    //attempts to open the filepath argument
    test.open(outputPath, ios_base::in);
    //if the file is open, the filepath inputted is valid. if not, the filepath argument is invalid for whatever reason. 
    //if the filepath is open return true
    out = test.is_open();
    //can't return test.is_open() because we need to close the file as well
    test.close();
    //if not return false
    return out;
}

int Training::getValueForWord(string word) const{
    //loops through each index of words aka each index of values
    for(int i = 0; i < words.size(); i++){
        //checks to find the index of word in words
        if(words.at(i) == word){
            //return the value of the index found in values
            //aka the corresponding value of word
            //aka the number of times this word was counted in the training model
            return values.at(i);
        }
    }
    //if nothing was found, word doesn't exist in words and therefore has appeared 0 times. return 0
    return 0;
}

int Training::getCount() const{
    return wordCount;
}
string Training::getName() const{
    return name;
}
string Training::getWordAtIndex(int index) const{
    return words.at(index);
}
int Training::getValueAtIndex(int index) const{
    return values.at(index);
}
int Training::getUniqueWords() const{
    return words.size();
}