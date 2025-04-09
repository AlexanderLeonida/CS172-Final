# User Manual for Final_Project_Octogon
Noah Dunham and Alex Leonida

## Troubleshooting
If you follow the manual and at any point you feel that you are at the wrong step 
    1. Reread the last instruction in the manual. Did you miss something?  
    2. Make sure you pressed enter after your previous input. There will always be a prompt after your input. If you do not see the prompt, press enter. DO NOT PRESS ENTER TWICE.  
    3. Follow the directions in the terminal  
    4. If you are really stuck, press "fn" + "c" to end process and try running again (step 7)  


## Section 1 - Files
### Setup
*"testing file" and the file that we want to classify are used interchangebly in this document*
1. If you have not already, read the [documentation](./documentation.md) file. 
2. Decide what catagories you want to classify documents into. The default catagories are Environment, Food, and Sports. Note that all documents in the testing phase will be classified as exactly one of these catagories. The program can not classify a document as "dog" if you do not train the catagory "dog".
### Training files
3. If you are using the default catagories and default training files, skip to step 5.
4. For each of the catagories identified in step 2, find training files to train the model off of.
    * All files must be in the Final_Project_Octogon folder. We recommend creating a subfolder in "training files" for consistency.
    * All files should be a .txt file.
    * If you wish to use a default catagory, there are 40 training files for each catagory pulled from npr.com in the folder Final_Project_Octogon/training files/\<catagory> training test files/\<int 1 - 40>.txt  
    Read the documentation closely if you wish to use these files.
    * It is highly recommended to use as many different files as possible for training. The default catagories have 40 files each.
    * Make sure that your files are representative of a catagory. If you wish to classify a file as a sports article and only train the program against baseball articles, it may fail to classify a football article.
    * Note that all words with capital letters are ignored, and all special characters are removed.
    * It is recommended to use training documents that have a similar style to the documents you wish to classify. For example, this could be the same author or same website.
### Testing files 
5. If you are using default catagories and wish to use the default testing files, skip to Section 2.
6. Testing files are technically optional. You do not need testing files for all the catagories you trained. For all the documents you do wish to classify, make sure that:
    * All files must be in the Final_Project_Octogon folder. We recommend creating subfolders in testing files for consistency.
    * All files should be a .txt file.
    * If you wish to use a default catagory, there are 10 ten files for each catagory pulled from npr.com in the folder Final_Project_Octogon/training files/\<catagory> testing test files/\<int 1 - 10>.txt  
    Read the documentation closely if you wish to use these files.
    * Note that all words with capital letters are ignored, and all special characters are removed.
## Section 2 - Running the Program
7. Compile and run the program
* The prompts in terminal are very explanatory, you may follow these prompts and then skip to Section 3 if you feel the prompts are enough to run the program properly
### Training
8. If you wish to use default training, type 1 and skip to step 12. If not, type 0.
9. You will be prompeted if you want to wish to train another file. If you still have files from step 4 that you have not trained, type 1. Otherwise, type 0 and skip to the Testing section (step 12).
10. You will be prompted for the classification of the file. This should be one of the catagories from step 2. 
    * If this is a classification that you have not entered yet, you will be prompted if you wish to create a new classification. 
    * If you respond yes, this implies that this new classification is intented to be distinct from the rest. For example "dog" should not be a classification you intend to create if you have already created "Dog".
    * If prompted, type "1" if you want to create this classification. Procede to step 11.
    * If you do not, type "0", and return to step 9. The classification you typed is not stored, and you still have the opportunity to train more files.
11. Enter the file path for the file you wish to train. 
    * File paths should be relative starting in ./
    * If you do not understand relative file paths, see https://web.stanford.edu/class/archive/cs/cs107/cs107.1206/resources/paths
    * If you followed our advice and put the training files in the training files folder, paths should start ./training files/\<rest of the path>
    * For example, a valid file path is "./training files/food training text files/1.txt"
    * If you enter a file path that doesn't exist or a file path that you have already trained against, a message will appear saying "Training aborted ..."  
    Nothing you entered in step 10 or step 11 will be saved
    * Regardless of if the training was successful, go back to step 9.
### Testing
* *Note that the verbs "test" and "classify" are used interchangebly both in this document and in the terminal prompts*
12. 
    * A message saying "The classifier has finished training" should have just appeared. If not, refer to the troubleshooting guide at the top of this document.
13. If you wish to use default tests, type 1 and procede to Section 3. If not, type 0.
    * If you did NOT train the default sections it is highly recommended to NOT use default tests. 
    * If you use default tests, you can not run induvidual tests as well.
    * If you do not use default tests now, you will NOT have the option to later.
14. You will be prompted if you want to wish to test another file. If you still have files from step 6 that you have not classified, type 1. Otherwise, type 0 and skip to Section 3.
15. Enter the file path for the file you wish to classify. 
    * File paths should be relative starting in ./
    * If you followed our advice and put the training files in the training files folder, paths should start ./testing files/\<rest of the path>
    * For example, a valid file path is "./testing files/food testing text files/1.txt"
    * If you enter a file path that doesn't exist, a message will appear saying "Testing aborted ...". This does NOT end the program, you will have an opportunity to fix your error.
    * If the classification was succesful, a message starting with "------------------"  will appear. You can either ignore this or skip to Section 3 and come back.
    * Regardless of if the tesing was successful, go back to step 14.
## Section 3 - Interpreting Results

The program should have terminated. If not, press "fn" + "c" (or end the terminal task some other way).  
Throughout the testing phase and/or when the program ended, messages starting with "--------------" appear in the terminal. These are the results of the classification. There may be several different results, so make sure to scroll through the terminal to find them all. If you used default testing, proceed to the "Default" header. If you did not, proceed to the "Custom" header. Thank you for using our program.

### Default

Your output should look like this:
```markdown
-------------------
Tested ./testing files/food testing text files/1.txt
Expected result: food
Actual result: food
Points in the order [environment,sports,food]: 
[0.698768,0.686859,1.49175]
```
The first line tells you the path of the file that was tested. 
   
The second line tells you which catagory the document actually was.  

The third line tells you which catagory the program classified this file into.  
  
The fourth and fifth lines work together. The fourth line tells you all the catagories in the program. The numbers in the fifth line tell you the "score" of each catagory. These are matched by index, so the catagory "environment" got a score of "0.698768". The higher the score, the more similar the words in the tested article were compared to the training articles of that catagory. The highest score, therfore, is what the file is classified as (in this case food had the highest score, so food was the result of the classification). The closer two scores are, the likely the document shares elements from both catagories. This means that words that appear in food documents and environment documents appeared in the testing file at a similar frequency (.698768 is close to .686859). Additionaly, these values can be used to detect ambivalence as to what the document is. If you test a document that is about both cooking and sports, they will likely have similar, high scores.  
  
While there are no set ranges on possible scores aside from a min of 0 and some maximum, the typical range of tested articles from our testing files is between .5 and 2. A result of a gap greater than .5+ is typically pretty conclusive.

### Custom

Your output should look like this:
```markdown
-------------------
Tested ./testing files/food testing text files/1.txt  
Result: food  
Points in the order [environment,sports,food]:  
[0.698768,0.686859,1.49175]
```

The first line tells you the path of the file that was tested. 
   
The second line tells you which catagory the program classified this file into.  
  
The third and fourth lines work together. The third line tells you all the catagories in the program. The numbers in the fourth line tell you the "score" of each catagory. These are matched by index, so the catagory "environment" got a score of "0.698768". The higher the score, the more similar the words in the tested article were compared to the training articles of that catagory. The highest score, therfore, is what the file is classified as (in this case food had the highest score, so food was the result of the classification). The closer two scores are, the likely the document shares elements from both catagories. This means that words that appear in food documents and environment documents appeared in the testing file at a similar frequency (.698768 is close to .686859). Additionaly, these values can be used to detect ambivalence as to what the document is. If you test a document that is about both cooking and sports, they will likely have similar, high scores.  
  
While there are no set ranges on possible scores aside from a min of 0 and some maximum, the typical range of tested articles from our testing files is between .5 and 2. A result of a gap greater than .5+ is typically pretty conclusive. 