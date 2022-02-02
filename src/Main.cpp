#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

// Trie structure
struct Node {
    Node *next[256] = {};
    string value;
};

// Structure to return value, depth of value, key
struct Result {
    Result() {}
    Node *p;
    string key;
    int d;
};

// Trie Class
class Trie {
public:
    // Insertion function
    void insert(string key, string value) {
        root = insert(root, key, value, 0);
    }
    // Search function
    string search(string key, bool isAdd) {
        Result *r = search(root, key, 0);

        if (!r) return "";

        if (!r->p) {
            if (!isAdd) {
                if (r->d == 1) {
                    return "";
                }
                else if (r->d > 1) {
                    return "incorrect";
                }
                else if (r->d <= key.size()) {
                    return "notEnough";
                }
            }
            return "";
        }
        return r->p->value;
    }
    // Deletion state function
    string deletionCheck(string key, bool isAdd) {
        Result *r = search(root, key, 0);

        if (!r->p) {
            if (!isAdd) {
                if (r->d == 1) {
                    return "noRecord";
                }
                else if (r->d > 1) {
                    return "incorrect";
                }
                else if (r->d <= key.size()) {
                    return "notEnough";
                }
            }
        }
        else if (r->p->value == ""){
            return "noRecord";
        }
        return "success";
    }
    // Deletion function
    void deletion(string key) {
        Result *r = search(root, key, 0);
        r->p->value = "";
    }

    void list(){

    }

private:
    // Recursive insert function for each node
    Node *insert(Node *p, string key, string value, int d){
        if (!p) p = new Node();
        if (d == key.size()) {
            p->value = value;
            return p;
        }
        char c = key.at(d);
        p->next[c] = insert(p->next[c], key, value, d+1);

        return p;
    }
    // Recursive search function for each node
    Result *search(Node *p, string key, int d) {
        if (!p) {
            Result *r = new Result();
            r->p = NULL;
            r->key = key;
            r->d = d;
            return r;
        }
        if (d == key.size()) {
            Result *r = new Result();
            r->p = p;
            r->key = key;
            r->d = d;
            return r;
        }
        char c = key.at(d);
        return search(p->next[c], key, d+1);
    }

    Node *root {};
};


// For parsing input file's lines
vector<string> parserFile(string str, char sign){
    vector<string> wordArr;
    string word = "";
    for (auto x : str)
    {
        if (x == sign){
            wordArr.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    wordArr.push_back(word);
    return wordArr;
}

int main(int argc, char** argv) {

    // For reading input file
    ifstream inputFile;
    inputFile.open(argv[1]);

    // Output file
    ofstream outputFile;
    outputFile.open(argv[2]);

    // For holding input lines, keys, values
    string text;
    string key;
    string value;

    // Creating Trie object
    Trie trie;

    // Reading input and processing functions
    while (getline(inputFile, text)) {
        vector<string> wordArr = parserFile(text, '(');

        if (wordArr[0] == "insert") {
            vector<string> wordArr2 = parserFile(wordArr[1], ',');
            key = wordArr2[0];
            value = wordArr2[1].substr(0, wordArr2[1].length()-2);

            if (trie.search(key, true) == ""){
                trie.insert(key, value);
                outputFile << "\"" << key << "\" was added" << endl;
            }
            else if (trie.search(key, true) != "" && trie.search(key, true) == value) {
                outputFile << "\"" << key << "\" already exist" << endl;
            }
            else if (trie.search(key, true) != "" && trie.search(key, true) != value) {
                trie.insert(key, value);
                outputFile << "\"" << key << "\" was updated" << endl;
            }
        }
        else if (wordArr[0] == "search") {
            key = wordArr[1].substr(0, wordArr[1].length() - 2);

            if (trie.search(key, false) != "incorrect" && trie.search(key, false) != "notEnough"
                && trie.search(key, false) != "") {
                outputFile << "\"The English equivalent is " << trie.search(key, false) << "\"" << endl;
            }
            else if (trie.search(key, false) == "incorrect") {
                outputFile << "\"incorrect Dothraki word\"" << endl;
            }
            else if (trie.search(key, false) == "notEnough") {
                outputFile << "\"not enough Dothraki word\"" << endl;
            }
            else {
                outputFile << "\"no record\"" << endl;
            }
        }
        else if (wordArr[0] == "delete") {

            key = wordArr[1].substr(0, wordArr[1].length() - 2);
            if (trie.deletionCheck(key, false) == "noRecord") {
                outputFile << "\"no record\"" << endl;
            }
            else if (trie.deletionCheck(key, false) == "notEnough") {
                outputFile << "\"not enough Dothraki word\"" << endl;
            }
            else if (trie.deletionCheck(key, false) == "incorrect") {
                outputFile << "\"incorrect Dothraki word\"" << endl;
            }
            else if ((trie.deletionCheck(key, false) != "incorrect" && trie.deletionCheck(key, false) != "notEnough"
                      && trie.deletionCheck(key, false) != "noRecord")) {
                trie.deletion(key);
                outputFile << "\"" << key << "\" deletion successful" << endl;
            }
        }
        else { // list
            trie.list();
        }
    }





    return 0;
}
