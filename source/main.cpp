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
#include "../headers/Testing.h"
#include <iostream>

//trains every text file in every default category (environment, food, sports) into model
//param vec holds training items in a vector which are what is being trained in the model
void defaultVectors(vector<Training> &vec);

//function allows the user whether or not they want to train more/different classificaions of type training to be added into their training vector
//within this method the user must provide a valid filepath to the file they wish to be trained into the model
// returns false if the user is done filling in the classifications + paths 
// returns true if the user fails to enter a new classification for any reason, or wishes to enter a new classification after entering one previously
bool userTrain(vector<Training> &vec);

//allows user to test against other files
//in context of this function, if this function ever returns 0, the program will end
//returns false if the user doesn't want to test against any other files
//if the function returns true, it will rerun the method. 
bool userTest(Testing test);

//tests trained model against test files which are arbibtrarily chosen and put into the ./tests file
//test param is a testing object that the trained model is being tested agaist based on the three categories inside of the ./testing files file
void defaultTest(Testing test);

//asks the user whether they want to use the default training withthree categories with 40 text files each from the ./testing files folder
//returns true if they do
//returns false if they don't
bool isDefaultTrain();

//asks user whether they want to use default testing against three categories with 10 text files each from the ./testing files folder
//returns true if they do
//returns false if they don't
bool isDefaultTest();

//prints out each of the elements in param vec in formatted string ["1", "2", "3"] or [1, 2, 3]
template <typename Type>
void printVector(vector<Type> vec);


int main(){
    vector<Training> classes;
    //file path below to copy and paste into terminal for testing if prompted to enter a filepath if you didn't enter one yourself
    //./testing files/food testing text files/1.txt

    //asks user if they want to train using the default training model we set up
    if(isDefaultTrain()){
        defaultVectors(classes);
    } else { //if not, they are prompted whether they want to train their model using files that they have inserted
        //loop runs until the user does not want to train the model with any more files
        while(userTrain(classes)){}
    }
    //variable test holds the trained model from above in a testing object
    Testing test = Testing(classes);
    //asks user if they want to test their model against defaulted test files in ./testing files
    if(isDefaultTest()){
        //this will tell you how well you're trained model did against the default testing testing files 
        defaultTest(test);
    } else { //if not, they are prompted to enter files they want the model to be tested against. 
        //this will tell the user how well you're trained model did against the testing files you entered
        //loop ends when the user doesn't want to test the trained model against anything else
        while(userTest(test)){}
    }

    return 0;
}

void defaultTest(Testing test){
    //clas = name of one of three default classifications 
    string clas;
    //name of the file path to a specific classifictation's text file
    string filePath;
    //vector of floats that holds the values of how likely the testing model is a classification based on the trained model
    vector<float> score;
    for(int j = 1; j <=3; j++){
        //changes the clas variable each time the for loop iterates to a new classification name
        switch(j){
            case 1:
                clas = "environment";
                break;
            case 2:
                clas = "sports";
                break;
            case 3:
                clas = "food";
        }
        //instantiates file path name to one of ten test text file per classification
        for(int i = 1; i < 11; i++){
            filePath = "./testing files/" + clas + " testing text files/" + to_string(i) + ".txt";
            //classifies filepath from tested default text files
            score = test.classify(filePath);
            cout << "-------------------" << endl;
            //prints out what was tested, and what the expected classification is
            cout << "Tested " << filePath << endl;
            cout << "Expected result: " << clas << endl;
            //prints out what the trained model predicted the test file classification to be
            cout << "Actual result: " << test.classifyToString() << endl;
            //prints out the categories that were tested against
            cout << "Points in the order [" << test.getNameList() << "]:" << endl;
            printVector(score);
            cout << endl;
        }
    }
}

bool isDefaultTest(){
    //asks user if they want to test their trained model against default test files. 
    //this means the user has finished their trained model and cannot continue training it
    cout << "The classifier has finished training. Do you want to use the default tests? 1 = yes, 0 = no" << endl;
    int a;
    cin >> a;
    //returns true if the user enters anything but a 0
    if(a != 0){
        return true;
    }
    //returns false if the user enters a 0
    return false;
}

void defaultVectors(vector<Training> &vec){
    //clear the vector beforehand just in case it was prepopulated
    //if it was prepopulated, it isn't running a default test with specifically 3 categories and our code will break, so instead we preclear it
    vec.clear();
    //add the three default categories to the vector to be trained
    vec.push_back(Training("environment"));
    vec.push_back(Training("sports"));
    vec.push_back(Training("food"));

    //trains each of 40 training files in each of 3 categories from the prepopulated /training files folder
    for(int i = 0; i <=2; i++){
        for(int j = 1; j <=40; j++){
            vec[i].train("./testing files/" + vec[i].getName() + " testing text files/" + to_string(j) + ".txt");
        }
    }
}

bool isDefaultTrain(){
    //asks user if they want to use default training process where the model is trained using 3 categories with 40 text files each in the ./training files folder
    cout << "Do you want to use the default training? 1 = yes, 0 = no" << endl;
    int a;
    cin >> a;
    //returns true if user inputs anything other than a 0
    if(a != 0){
        return true;
    }
    //returns false if user inputs 0
    return false;
}

template <typename Type>
void printVector(vector<Type> vec){
    //prints out each of the elements in param vec
    cout << "[";
    //prints empty brackets and returns if there's nothing in the vector []
    if(vec.size()==0){
        cout << "]";
        return;
    }
    for (int i = 0; i < vec.size() -1 ; i++){
        //prints out every element of the vector but the last element
        cout << vec.at(i) << ",";
    }
    //prints out the last element of the vector
    cout << vec.at(vec.size()-1) << "]" << endl;
}


bool userTest(Testing test){
    //asks user if they want to test against another file, if they enter anything but a 1, method returns false and program will effectively ends
    cout << "Do you wish to test against another file? 1 = yes, 0 = no" << endl;
    int con;
    cin >> con;
    if(con != 1){
        return false;
    }

    cout << "Please enter a relative file path. Assume we are currently in folder \"Final_Project_octagon\"." << endl;
    //variable path holds the relative file path in string form
    string path;
    // Resources used: Lex aka. "@lexvalkyrie" on discord. 
    // explanation: she recommended the use of a cin.ignore statement to someone else on the cs172 discord channel
    // after looking at the cpp documentation for both getline and cin.ignore, we found that the terminal inputs a \n after every getline call, in this case we discard the defaulted 1 character value to grab whatever is inputted by the user in the getline method call
    cin.ignore();
    getline(cin,path);
    //check the file path to see if it exists
    if(!Training::checkFilePath(path)){
        cout << "Testing aborted, please try again" << endl;
        cout << "Reason: Failed to open the file path you entered" << endl;
    } else { //if file path exists, we can test against the trained model. 
        vector<float> score = test.classify(path);
        cout << "-------------------" << endl;
        cout << "Tested " << path << endl;
        cout << "Result: " << test.classifyToString() << endl;
        //prints the names of the categories
        cout << "Points in the order [" << test.getNameList() << "]:" << endl;
        //prints the likeliness of each score relating to each category
        printVector(score);
        cout << endl;
    }
    return true;
}

bool userTrain(vector<Training> &vec){
    //asks user if they want to train against an additional file. If they don't want to, return false, and move onto model testing stage
    //note: you can't train any more files once this returns false at any point
    cout << "Do you wish to train another type of file? 1 = yes, 0 = no" << endl;
    int con;
    cin >> con;
    //if the user inputs anything but a 1, return false. We prompt a 1 or a 0, but if the user inputs a letter for example, it'll return false as well when the string converts into an integer value
    if(con != 1){
        return false;
    }
    
    cout << "Please enter the classification (ex: \"sports\") of the file" << endl;
    //name of clas is arbitrary. the name of the classification can be anything you want it to be, because you're creating one
    //clas holds the value of the name of the classification you're checking. if there was a default train method called before this, it's highly reccomended not to name the new classification as one that's previously been entered into the vector
    //if you do enter the same name, the loop immediately exists as shown below where we increment through each element in the vector checking against current names of classifications inside
    string clas;
    cin >> clas;
    bool exists = false;
    int i = 0;
    while(i < vec.size() && !exists){
        //compares what the user entered to each name in vector
        if(clas == vec[i].getName()){
            //if what user entered is the same as a name in the vector, exit the loop and set exists varialbe to true so that a  new classification isn't created below
            exists = true;
        } else {
            i++;
        }
    }
    //if it doesn't already exist, we add it to the vector of training objects. 
    //note: push_back implicitly increases the size of the vector when needed so we don't need to manually adjust that
    //if this conditional fails, exists is true which means that the classification prompted by the user already exists within the vector
    if(!exists){
        //have the user enter 1 to confirm the addition of the a new classifciation of training object to the vector
        cout << "Are you sure you want to create a new classification \"" + clas + "\"? 1 = yes, 0 = no" << endl;
        int a;
        cin >> a;
        if(a == 1){
            vec.push_back(Training(clas));
        } else{
            //if the user made a mistake, anything besides a 1 entered will terminate the function call and will return true
            //Because the function returns true, it will reprompt the user at the top of this method if they want to train another file 
            cout << "Training aborted, please try again" << endl;
            cout << "Reason: Terminated by user" << endl;
            return true;
        }
    }

    cout << "Please enter a relative file path. Assume we are currently in folder \"Final_Project_octagon\"." << endl;
    string path;
    // Resources used: Lex aka. "@lexvalkyrie" on discord. 
    // explanation: she recmomended the use of a cin.ignore statement to someone else on the cs172 discord channel
    // after looking at the cpp documentation for both getline and cin.ignore, we found that the terminal inputs a \n after every getline call, in this case we discard the defaulted 1 character value to grab whatever is inputted by the user in the getline method call
    cin.ignore(); 
    getline(cin,path);

    //train method implicitly calls the checkfilepath method and checks if the filepath has been trained already, so if both are untrue, it returns true
    //in which case the training is successful, and we return true which goes back to the top of this function to reprompt the user
    if(vec[i].train(path)){ 
        cout << "Training succesful" << endl;
        return true;
    }
    //if previous conditional failed, either the filepath doesn't exist or it already has been trained. 
    //either way, it failed to train because we don't want to retrain a file which has already been trained and we can't train a file that doesn't exist
    cout << "Training aborted, please try again" << endl;

    //checks if filepath exists or not. if it doesn't we know it can only be the other problem which is that it's already been trained
    if(!Training::checkFilePath(path)){
        cout << "Reason: Failed to open the file path you entered" << endl;
    } else {
        cout << "Reason: You have already trained this classification using this file" << endl;
    }
    //default returns true for the user in case anything goes wrong for them. in this case, they'll have the option to continue entering file paths to train and don't have to start over
    //if we default returned false, it would immediately go to the testing phase which is not useful for the user who failed to insett their own training file clasification
    return true;

}