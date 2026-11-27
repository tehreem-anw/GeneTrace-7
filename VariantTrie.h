#pragma once

#include <iostream>
#include <string>

using namespace std;

struct VariantResultNode{
    string variantName;
    VariantResultNode* next; //one variant points to the next (e.g. alpha->beta->gamma)

    VariantResultNode(string name){
        variantName = name;
        next = nullptr;
    }
};

class VariantTrie{
    struct TrieNode{
        TrieNode* children[4]; // A, C, G, T
        bool isEndOfCode;       // tells if a complete DNA code ends at this node
        string variantName;

        TrieNode(){
            isEndOfCode = false;
            variantName = "";
            for (int i = 0; i < 4; i++){
                children[i] = nullptr;
            }
        }
    };

    TrieNode* root;     // Starting node, not counted in the DNA code

    int getIndex(char ch);
    void collectVariants(TrieNode* node, VariantResultNode*& head, VariantResultNode*& tail);
    void destroyTrie(TrieNode* node);

public:
    VariantTrie();
    ~VariantTrie();

    void insertVariant(const string& code, const string& name);
    VariantResultNode* searchPrefix(const string& prefix);
    void deleteResults(VariantResultNode* head);
};
