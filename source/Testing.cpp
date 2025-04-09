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

#include "../headers/Testing.h"     
    

Testing::Testing(vector<Training> data){
    this->data = data;
    for(int i = 0; i < data.size(); i++){
        //pre populates points vector with all 0.0 floats so it's the same size as the data vector filled with training data
        points.push_back(0.0);
    }
}

vector<float> Testing::classify(string filePath){
    for(int i = 0; i < points.size(); i++){
        //resets all of the points vector just in case something was changed from the constructor, like a previous run
        points.at(i) = 0.0;
    }
    Training test = Training("");
    //trains filepath
    test.train(filePath);
    //total word count of trained model
    int totalWords = getTotalWords();
    int totalCountOfWord;
    string word;
    //loop for each unique word in words
    for(int wordI = 0; wordI < test.getUniqueWords(); wordI++){
        //unique word
        word = test.getWordAtIndex(wordI);
        //total count of that word from values vector
        totalCountOfWord = getTotalCountOfWord(word);
        //loop for each item in data
        for(int clas = 0; clas < data.size(); clas++){
            //adds the value of likeliness to classification. this is the output part that looks something like, [1.238, 2.239, 3.4012]
            points.at(clas) += getValue(word, test,data[clas], totalWords, totalCountOfWord);
        }
    }
    return points;
}

int Testing::getTotalCountOfWord(string word) const{
    //keeps track of total count of word per training point
    int count = 0;
    for(int clas = 0; clas < data.size(); clas++){
        //add number of count of each individual word to count
        count += data[clas].getValueForWord(word);
    }
    return count;
}

int Testing::getTotalWords() const{
    int totalWords = 0;
    for(int i = 0; i < data.size(); i++){
        //adds total number of words from each training point to total words
        totalWords += data[i].getCount();
    }
    return totalWords;
}

float Testing::getValue(string word, Training test, Training trained, int totalWords, int totalCountOfWord) const{
    if(totalCountOfWord == 0){
        return 0.0;
    }
    //this is the algorithm used to calculate the likeliness of classification. it is the total number of words * total number of classification words * the value of that word / the count of classification of that word / total count of words of that classification / count of words
    return 1.0 * test.getValueForWord(word) * trained.getValueForWord(word) * totalWords / trained.getCount() / totalCountOfWord / test.getCount();
}

string Testing::classifyToString() const{
    int max = findMax(points,points.size());
    //returns the name of the maximum value found in data. this is the name of the highest likeliness classification
    return data[max].getName();
}

string Testing::getNameList() const{
    string str;
    for(int i = 0; i < data.size(); i++){
        //adds each name in data training object to str variable formatted seperated by commas
        str += data[i].getName();
        str += ",";
    }
    //gets ride of the last comma in the string, unless the size of str is 0, in which case there is no comma to get rid of
    if(data.size() != 0){
        str.pop_back();
    }
    return str;
}

int Testing::findMax(vector<float> arr, int arrSize) const{
    int maxIndex = 0;
    //loops through arr usig arrSize
    for(int i = 1; i < arrSize; i++){
        //compares value of index to value of arr current max index 
        if(arr[i] > arr[maxIndex]){
            //if it is larger, set maxindex to new max index
            maxIndex = i;
        }
    }
    return maxIndex;
}
