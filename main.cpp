// program which sorts images into 2 folders ("Benign" and "Malignant") for training/testing on CreateML
// potential improvement: automatically perform 80-20 split

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

ifstream fin("../ISIC-images/metadata.txt");
ofstream fout("../ISIC-images/mod_metadata.txt");

ifstream fin2("../ISIC-images/mod_metadata.txt");
ofstream fout2("../ISIC-images/mod2_metadata.txt");

ifstream fin3("../ISIC-images/mod2_metadata.txt");

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
    bool carry = false;
    while (!fin2.eof()) {
        if (!carry) {
            fin2 >> str;
        } else {
            carry = false;
        }
        if (str.substr(0, 4) == "5aaf") {
            fin2 >> str2;
            str2 += ' ';
            for (;;) {
                fin2 >> str;
                if (str.substr(0, 4) == "5aaf") {
                    carry = true;
                    break;
                }
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
    while (!fin3.eof()) {
        fin3 >> str >> str2;
        char before[63] = "../ISIC-images/HAM10000/";
        for (int i = 0; i < str.length(); i++) {
            before[46 + i] = str[i];
        }
        before[58] = '.'; before[59] = 'j'; before[60] = 'p'; before[61] = 'g';
        before[62] = '\0';
        if (str2 == "benign") {
            char after[55] = "../Train/Benign/";
            for (int i = 0; i < str.length(); i++) {
                after[38 + i] = str[i];
            }
            after[50] = '.'; after[51] = 'j'; after[52] = 'p'; after[53] = 'g';
            after[54] = '\0';
            cout << before << " " << after << endl;
            rename(before, after);
        } else {
            char after[58] = "../Train/Malignant/";
            for (int i = 0; i < str.length(); i++) {
                after[41 + i] = str[i];
            }
            after[53] = '.'; after[54] = 'j'; after[55] = 'p'; after[56] = 'g';
            after[57] = '\0';
            cout << before << " " << after << endl;
            rename(before, after);
        }
    }
    fin3.close();
    return 0;
}
