#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

ifstream fin("/Users/gravity/Downloads/ISIC-images/metadata.txt");
ofstream fout("/Users/gravity/Downloads/ISIC-images/mod_metadata.txt");

ifstream fin2("/Users/gravity/Downloads/ISIC-images/mod_metadata.txt");
ofstream fout2("/Users/gravity/Downloads/ISIC-images/mod2_metadata.txt");

ifstream fin3("/Users/gravity/Downloads/ISIC-images/mod2_metadata.txt");

string str, str2;

int main() {
    // initial .csv renamed to .txt
    while (!fin.eof()) {
        fin >> str;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ',') {
                str[i] = ' ';
            }
        }
        fout << str << endl;
    }
    fin.close();
    fout.close();
    // metadata file with commas removed
    while (!fin2.eof()) {
        fin2 >> str;
        if (str.substr(0, 4) == "5aaf") {
            fin2 >> str2;
            str2 += ' ';
            for (;;) {
                fin2 >> str;
                if (str == "benign") {
                    str2 += str;
                    break;
                } else if (str == "malignant") {
                    str2 += str;
                    break;
                }
            }
            str2 += "\n";
            if (str2[str2.length() - 2] != ' ') {
                fout2 << str2;
            }
        }
    }
    fin2.close();
    fout2.close();
    // moving photos to their respective folders
    while (!fin3.eof()) { // currently rename not working
        fin3 >> str >> str2;
        char before[62] = "/Users/gravity/Downloads/ISIC-images/HAM10000/";
        for (int i = 0; i < str.length(); i++) {
            before[46 + i] = str[i];
        }
        before[58] = '.'; before[59] = 'j'; before[60] = 'p'; before[61] = 'g';
        if (str2 == "benign") {
            char after[66] = "/Users/gravity/Downloads/ISIC-images/Train/Benign/";
            for (int i = 0; i < str.length(); i++) {
                after[50 + i] = str[i];
            }
            after[62] = '.'; after[63] = 'j'; after[64] = 'p'; after[65] = 'g';
            rename(before, after);
        } else {
            char after[69] = "/Users/gravity/Downloads/ISIC-images/Train/Malignant/";
            for (int i = 0; i < str.length(); i++) {
                after[53 + i] = str[i];
            }
            after[65] = '.'; after[66] = 'j'; after[67] = 'p'; after[68] = 'g';
            rename(before, after);
        }
    }
    fin3.close();
    return 0;
}
