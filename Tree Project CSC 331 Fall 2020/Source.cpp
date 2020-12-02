#include "BSTree.cpp"
#include "BSTree.h"
#include <cctype>
#include <algorithm>
#include <string>
#include <fstream>


using namespace std;

int main()
{
    BSTree<string> T1;
    string item;

    ifstream infile;

    infile.open("Numbers.txt");

    while (!infile.eof())
    {
        infile >> item;


        int i = 0;
        int len = item.length();
        while (i < len) {
            if (!isalnum(item[i]) || item[i] == ' ' && item[i] != '\'') {
                item.erase(i, 1);
                len--;
            }
            else
                i++;
        }
        if (item != "") {
            transform(item.begin(), item.end(), item.begin(), ::toupper);
            T1.insertItem(item);
            cout << "Inserted: " << item << endl;
        }
    }

    //T1.printInorder();



    cout << "\n";

    T1.printInorder();
    //cout << "\n\n";
   // T1.printPostorder();
    //cout << "\n\n";
   // T1.printPreorder();


    return 0;
}