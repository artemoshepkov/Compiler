#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "commands.h"

using namespace std;

struct machineWord
{
    int address = 0;
    int command = 0;
    int operand = 0;
};

void split(string str, char separator, vector<string>& array) {
    string buffer;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ';') {
            break;
        }
        if (str[i] != separator) {
            buffer += str[i];
        }
        else {
            array.push_back(buffer);
            buffer = "";
        }
    }
    if (buffer != "") {
        array.push_back(buffer);
    }
}

int stringToInt(string word) {
    int num;
    num = stoi(word);
    return num;
}

int findInCommands(string command) {
    it = commands.find(command);
    return it->second;
}

int fromWordToInt(machineWord word) {
    if (word.command == 0x7F) {
        return word.operand + (1 << 14);
    }
    return word.command << 7 | word.operand;
}

machineWord decodeLine(string line){
    machineWord currentWord;
    vector<string> words;
    split(line, ' ', words);

    currentWord.address = stringToInt(words[0]);
    currentWord.command = findInCommands(words[1]);
    currentWord.operand = stringToInt(words[2]);

    return currentWord;
}

int main(int argc, char* argv[])
{
    cout << "Start translator" << endl;
    
    if (argc < 2) {
        return -1;
    }
    
    ifstream in(argv[1]); // окрываем файл для чтения
    if (!in.is_open()) {
        return -1;
    }

    ofstream out(argv[2], ios::binary);
    if (!out.is_open())
    {
        return -1;
    }

    vector<machineWord> app;
    string line;
    
    while (getline(in, line)){

        machineWord currentWord = decodeLine(line);
        app.push_back(currentWord);
    }

    machineWord tmp;
    for (int i = 0; i < app.size(); i++) {
        for (int j = i + 1; j < app.size(); j++) {
            if (app[i].address > app[j].address) {
                tmp = app[i];
                app[i] = app[j];
                app[j] = tmp;
            }
        }
    }

    int num = 0;
    int count = 0;
    for (int i = 0; i < 100; i++) {
        num = 0;
        if (i == app[count].address) {
            num = fromWordToInt(app[count]);
            if (count < app.size() - 1) {
                count++;
            }
        }
        out.write((char*)&num, sizeof(num));
    }

    in.close();     // закрываем файл

    cout << "End Translator" << endl;

    return 0;
}