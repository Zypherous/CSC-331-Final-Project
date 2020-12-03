#include "BSTree.cpp"
#include "BSTree.h"
#include <cctype>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>



using namespace std;

string processWord(string);
int countCharacters(string);
double averageSentenceLength(ifstream&);
int numberOfWordsInSentence(const string&);

int main()
{
    BSTree<string> T1;
    string item;

    ifstream infile;
    ofstream outfile;


    int wordCount = 0;
    int totalCharacters = 0;
    double averageSentenceLen = 0;
    averageSentenceLen = averageSentenceLength(infile);
    infile.open("Numbers.txt");
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
    

    //T1.printInorder();



    cout << "\n";

    T1.printInorder();
    //cout << "\n\n";
   // T1.printPostorder();
    //cout << "\n\n";
   // T1.printPreorder();
    cout << "\nTotal words = " <<  wordCount;
    cout << "\nUnique words used = " << T1.uniqueWordsUsed();
    cout << "\nTotal Characters for average word length: " << totalCharacters;
    cout << "\nAverage word length by dividing the number of characters by the number of words: ";
    cout << static_cast<float>(totalCharacters) / wordCount << "\n";
    //averageSentenceLen = averageSentenceLength(infile);
    cout << "\nAverage sentence length is: " << averageSentenceLen << "\n";


    for (int i = 0; i < 26; i++) {
        int alphabet = 'a' + i;
        char x = alphabet;
        T1.printInorderIndex(toupper(x));
        cout << "\n";
        cout << setw(15) << setfill('-') << "\n";
    }
    

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