/******************************************************/
/* Programmer:Jonathan Rosario                        */
/* Date: 12/10/2020                                   */
/* CSC 331 Fall 2020, Professor Anna Salvati          */
/* Purpose:Project 4 Tree Project - Style Checker     */
/*   Reads a file and outputs a style + statistical   */
/*   summary.                                         */
/******************************************************/
#include "BSTree.cpp"
#include "BSTree.h"
#include <cctype>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

// Uncomment if you wish to use shell command to open file location
//#include <Windows.h>



using namespace std;

#pragma region Function Prototypes 
string processWord(string);
int countCharacters(string);
double averageSentenceLength(ifstream&);
int numberOfWordsInSentence(const string&);
#pragma endregion Function prototypes for main found here

int main()
{
#pragma region Necessary variable declarations
    BSTree<string> T1;
    string item;
    string filename, ofile;
    ifstream infile;
    ofstream outfile;

    
    int wordCount = 0;
    int totalCharacters = 0;

    // Variables for average sentence length and average word length
    double averageSentenceLen = 0;
    double averageWordLen = 0;
#pragma endregion Variable declarations for main


#pragma region Input File Processing
    // Prompt for user to enter file name to be analyzed

    cout << "Please enter file name (e.g\"Numbers.txt\") and be sure file is in same location as program:\n";
    cin >> filename;

    
    // Initialization of string holding output file name
    ofile = filename +"Analysis.txt";


    // Opening file to begin processing of information and writing to output
    infile.open(filename);
    if (infile.is_open()) {

        // Looping through file until end reached.
        while (!infile.eof())
        {
            // Reading words from file to be added to tree declared earlier
            infile >> item;

            // Calling function to eliminate characters from word that are not alphanumeric
            item = processWord(item);

            // Taking total characters from processed item and adding to total (0 for blanks)
            totalCharacters += countCharacters(item);

            // Check to see if item is not blank after removal of non alphanumeric characters and then inserting item
            if (item != "") {
                // Converting first letter of each word to capital to account for the different ASCII values betweeen capital/lowercase
                item[0] = toupper(item[0]);
                // Insert item into tree
                T1.insertItem(item);
                // Increase total word count
                wordCount += 1;
            }
        }
    }

    // Close and then reopen file to start from beginning again
    infile.close();
    infile.open("Numbers.txt");

    // Check if file opened
    if (infile.is_open()) {

        // Call function to determine average sentence length and then close file
        averageSentenceLen = averageSentenceLength(infile);
        infile.close();
    }

    // Determine average word length by dividing total characters by number of words
    averageWordLen = static_cast<double>(totalCharacters) / wordCount;
#pragma endregion Input file processing

#pragma region Output file processing
    // Create and open output file
    outfile.open(ofile);
    if (outfile.is_open()) {
        //cout << "\n";
        //T1.printInorder();
        //cout << "\n\n";
       // T1.printPostorder();
        //cout << "\n\n";
       // T1.printPreorder();

        // Formatting and writing to file
        outfile << "FILE NAME: " << filename;
        outfile << "\n\n";
        outfile << right << setw(50) << setfill(' ') << "STATISTICAL SUMMARY\n";
        outfile << "\nTOTAL NUMBER OF WORDS : " << wordCount;
        outfile << "\nTOTAL NUMBER OF “UNIQUE” WORDS : " << T1.uniqueWordsUsedAll();
        outfile << "\nTOTAL NUMBER OF “UNIQUE” WORDS OF MORE THAN THREE LETTERS : " << T1.uniqueWordsUsed();
        outfile << "\nTotal Characters for average word length: " << totalCharacters;
        outfile << "\nAVERAGE WORD LENGTH : " << fixed << setprecision(2)<< averageWordLen << " characters";
        outfile << "\nAVERAGE SENTENCE LENGTH : " << fixed << setprecision(2) << averageSentenceLen << " words";

        outfile << "\n\n";
        outfile << right << setw(50) << setfill(' ') << "STYLE WARNINGS";
        outfile << "\n\n";
        outfile << "WORDS USED TOO OFTEN: (  WORDS OF MORE THAN 3 LETTERS THAT ARE USED MORE THAN 5% OF THE TOTAL NUMBER   OF WORDS OF MORE THAN 3 LETTERS )\n\n";
        T1.printOften(wordCount, outfile);

        // Output that only displays if style warning condition met
        if (averageSentenceLen > 10) {
            outfile << "\nAVERAGE SENTENCE LENGTH TOO LONG - " << averageSentenceLen << " words";
        }
        if (averageWordLen > 5) {
            outfile << "\nAVERAGE WORD LENGTH TOO LONG - " << static_cast<float>(totalCharacters) / wordCount << " characters";
        }

    
        outfile << "\n\n";
        outfile << right << setw(50) << setfill(' ') << "INDEX OF UNIQUE WORDS\n";

        // Loop to print proper formatting for index of words
        for (int i = 0; i < 26; i++) {
            int alphabet = 'a' + i;
            char x = alphabet;
            outfile << "\n";
            T1.printInorderIndex(toupper(x), outfile);
        }

    }

    // Closing file
    outfile.close();
#pragma endregion Output file processing

#pragma region QoL Code
    // Command to open file and save me time from opening it after each run of the program. File path must be edited for use on other computers
    // Unsure of how to detect current file path.
    //ShellExecuteA(NULL, "open", "‪C:\\Users\\JonathanNew\\source\\repos\\Zypherous\\CSC-331-Final-Project\\Tree Project CSC 331 Fall 2020\\Numbers.txtAnalysis.txt", NULL, NULL, 10);
#pragma endregion Line of code to help open file for the lazy

    return 0;
}


#pragma region Function definitions 
// processWord //
//******************************************************************************
// Parameters: String
// Function: Takes an string "item", and removes non alphanumeric characters
//           leaving only the apostrophe character for words such as "They're"
// Returns:  Processed string
//******************************************************************************
string processWord(string item) {
    int i = 0;
    int len = item.length();
    while (i < len) {

        if (item[i] != '\'' && !isalnum(item[i]) || item[i] == ' ') {
            item.erase(i, 1);
            len--;
        }
        else
            i++;
    }
    return item;
}


// countCharacters //
//******************************************************************************
// Parameters: String
// Function: Takes an string "item", and counts characters in it
//
// Returns:  integer holding the character total of item
//******************************************************************************
int countCharacters(string item) {
    int characters = 0;
    for (int i = 0; i < item.length(); i++) {
        if (item[i] != '\'' ) {
            characters += 1;
        }
    }
    return characters;
}

// averageSentenceLength //
//******************************************************************************
// Parameters: ifstream&
// Function: Takes an inputfile streams address and reads it line by line
//
// Returns:  double holding the average length of an sentence
//******************************************************************************
double averageSentenceLength(ifstream &file) {
    string sentence;
    int count = 0;
    int words = 0;
    double averageLength;
    while (getline(file, sentence, '.')) {
        count++;
        words += numberOfWordsInSentence(sentence);
    }

    averageLength = static_cast<double>(words) / count;
    return averageLength;
}

// numberOfWordsInSentence //
//******************************************************************************
// Parameters: const string &
// Function: Takes the address of a const string to cound the number of words
//           by converting it into a string stream and counting the number of
//           entries
// Returns:  integer with numbe of words in sentence stream
//******************************************************************************
int numberOfWordsInSentence(const string &sentence) {
    istringstream stringStream(sentence);
    int count = 0;
    string word;
    while (stringStream >> word) {
        count++;
    }
    return count;
}
#pragma endregion Function definitions