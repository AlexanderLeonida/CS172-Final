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
#include "Training.h"

class Testing{
    private:
        vector<Training> data;
        vector<float> points;

        // returns the index of the highest value in arr
        //param int arrSize is the size of arr
        int findMax(vector<float> arr, int arrSize) const;
        // returns the sum of the word count of each Training object in 'data'
        int getTotalWords() const;
        // returns the sum of the occureces of 'word' in all the Training objects in 'data'
        int getTotalCountOfWord(string word) const;
        //param word - the word that we want the point score for
        //param test - the Training object representing the file that is to be classified (word is in this object)
        //param trained - the Training object representing all the files of a specific classification. The returned points are for this classification
        //param totalWords - the number of words in ALL the files that were trained against, regardless of classification
        //param totalCountOfWord - the number of times 'word' appears in ALL the files that were trained against, regardless of classification
        //return - "points" for 'word' for the catagory represented by 'trained'
        float getValue(string word, Training test, Training trained, int totalWords, int totalCountOfWord) const;

    public:
        //constructor which takes in a data vector of training points
        Testing(vector<Training> data);
        
        // modifies 'points' to represent the "score" of the corresponding classification in data
        // the "score" represent the "closness" to an env, sprt, or food in that order
        // string filePath is the filePath we are classifying
        vector<float> classify(string filePath);

        // expects a call to 'classify()' before a call to this
        // returns the name of the most likely classification 
        // ex: "sports"
        string classifyToString() const;

        //gets the list of names of each data training object and returns a string seperated by commas
        string getNameList() const;

};