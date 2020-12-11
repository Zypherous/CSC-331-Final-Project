#include "BSTree.cpp"
#include "BSTree.h"
#include <cctype>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>



using namespace std;

string processWord(string);
int countCharacters(string);
double averageSentenceLength(ifstream&);
int numberOfWordsInSentence(const string&);

int main()
{
    BSTree<string> T1;
    string item;
    string filename, ofile;
    
    cout << "Please enter file name (e.g\"Numbers.txt\") and be sure file is in same location as program:\n";
    cin >> filename;

    ifstream infile;
    ofstream outfile;

    ofile = "Output.txt";

    int wordCount = 0;
    
    
    int totalCharacters = 0;
    double averageSentenceLen = 0;
    double averageWordLen = 0;
    averageSentenceLen = averageSentenceLength(infile);
    infile.open(filename);
    if (infile.is_open()) {
        while (!infile.eof())
        {
            infile >> item;
            item = processWord(item);
            totalCharacters += countCharacters(item);
            if (item != "") {
                //transform(item.begin(), item.end(), item.begin(), ::toupper);
                item[0] = toupper(item[0]);
                T1.insertItem(item);
                //cout << "Inserted: " << item << endl;
                wordCount += 1;
            }
        }
    }
    infile.close();
    infile.open("Numbers.txt");
    if (infile.is_open()) {
        averageSentenceLen = averageSentenceLength(infile);
        infile.close();
    }
    outfile.open(ofile);
    if (outfile.is_open()) {
        //T1.printInorder();



        cout << "\n";

        T1.printInorder();
        //cout << "\n\n";
       // T1.printPostorder();
        //cout << "\n\n";
       // T1.printPreorder();




        averageWordLen = static_cast<double>(totalCharacters) / wordCount;

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

        if (averageSentenceLen > 10) {
            outfile << "\nAVERAGE SENTENCE LENGTH TOO LONG - " << averageSentenceLen << " words";
        }
        if (averageWordLen > 5) {
            outfile << "\nAVERAGE WORD LENGTH TOO LONG - " << static_cast<float>(totalCharacters) / wordCount << " characters";
        }

        outfile << "\n\n";
        outfile << right << setw(50) << setfill(' ') << "INDEX OF UNIQUE WORDS\n";
        for (int i = 0; i < 26; i++) {
            int alphabet = 'a' + i;
            char x = alphabet;
            outfile << "\n";
            T1.printInorderIndex(toupper(x), outfile);
            //cout << "\n";
           // cout << setw(15) << setfill('-') << "\n";
        }


        // Perhaps create a function that can take in two parameters, wordcount and node. Will use a similar function to the print in orderindex function
        // it'll then take thet number of words and check to see first if the words length is > than 3 then check how manytimes it was used and compare to
        // the total words used. This means it'll divide that number by total words used to determine the % used. Must also somehow account for numbering of
        // words printed. Internal counter in the function might remedy that. By counting each time something is printed, we can then newline + cout count and ")"
    }

    outfile.close();

    ShellExecuteA(NULL, "open", "C:\\Users\\JonathanNew\\source\\repos\\Zypherous\\CSC-331-Final-Project\\Tree Project CSC 331 Fall 2020\\output.txt", NULL, NULL, 10);
    return 0;
}


void printStats(BSTree<string> tree, int wordCount) {
    cout << wordCount;
    

}

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

int countCharacters(string item) {
    int characters = 0;
    for (int i = 0; i < item.length(); i++) {
        if (item[i] != '\'' ) {
            characters += 1;
        }
    }
    return characters;
}

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


int numberOfWordsInSentence(const string &sentence) {
    istringstream stringStream(sentence);
    int count = 0;
    string word;
    while (stringStream >> word) {
        count++;
    }
    return count;
}