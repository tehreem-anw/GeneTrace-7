#include "VariantTrie.h"

VariantTrie::VariantTrie(){
    root = new TrieNode();
}


int VariantTrie::getIndex(char ch)
{
    ch = toupper(ch);

    if (ch == 'A'){return 0;}
    else if (ch == 'C'){return 1;}
    else if (ch == 'G'){return 2;}
    else if (ch == 'T'){return 3;}
    return -1;
}


void VariantTrie::insertVariant(const string& code, const string& name)
{
    if (code.empty() || name.empty()) {return;}

    string upperCode = code;

    for (int i = 0; i < upperCode.length(); i++){
        upperCode[i] = toupper(upperCode[i]);

        if (getIndex(upperCode[i]) == -1)
        {
            cout << "Invalid DNA code." << endl;
            return;
        }
    }

    TrieNode* curr = root;

    for (int i = 0; i < upperCode.length(); i++){
        int index = getIndex(upperCode[i]);

        if (curr->children[index] == nullptr){
            curr->children[index] = new TrieNode();
        }

        curr = curr->children[index];
    }

    curr->isEndOfCode = true;
    curr->variantName = name;
}


void VariantTrie::collectVariants(TrieNode* node, VariantResultNode*& head, VariantResultNode*& tail){
    if (node == nullptr){
        return;
    }

    if (node->isEndOfCode){
        VariantResultNode* newNode = new VariantResultNode(node->variantName);

        if (head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    for (int i = 0; i < 4; i++){
        collectVariants(node->children[i], head, tail);
    }
}


VariantResultNode* VariantTrie::searchPrefix(const string& prefix)
{
    if (prefix.empty()) {return nullptr;}

    TrieNode* curr = root;

    for (int i = 0; i < prefix.length(); i++)
    {
        char ch = toupper(prefix[i]);
        int index = getIndex(ch);

        if (index == -1){
            return nullptr;
        }

        if (curr->children[index] == nullptr){
            return nullptr;
        }

        curr = curr->children[index];
    }

    VariantResultNode* head = nullptr;
    VariantResultNode* tail = nullptr;

    collectVariants(curr, head, tail);

    return head;
}


void VariantTrie::deleteResults(VariantResultNode* head){
    while (head != nullptr){
        VariantResultNode* temp = head;
        head = head->next;
        delete temp;
    }
}


void VariantTrie::destroyTrie(TrieNode* node){
    if (node == nullptr){
        return;
    }

    for (int i = 0; i < 4; i++){
        destroyTrie(node->children[i]);
    }

    delete node;
}

VariantTrie::~VariantTrie(){
    destroyTrie(root);
}
