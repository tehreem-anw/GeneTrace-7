#include "MetadataHashTable.h"

MetadataHashTable::MetadataHashTable(){
    for (int i = 0; i < TABLE_SIZE; i++){
        buckets[i] = nullptr;
    }
}

int MetadataHashTable::hashFunction(const string& sampleID) const{
    unsigned long hashValue = 0;

    for (int i = 0; i < sampleID.length(); i++){
        hashValue = (hashValue * 31 + sampleID[i]) % TABLE_SIZE;
    }

    return hashValue;
}

void MetadataHashTable::insertMetadata(const string& sampleID, const string& patientData){
    if (sampleID.empty()){
        cout << "Error: Sample ID cannot be empty." << endl;
        return;
    }
    int index = hashFunction(sampleID);
    HashNode* curr = buckets[index];

    while (curr != nullptr){
        if (curr->sampleID == sampleID){
            curr->patientData = patientData;
            return;
        }

        curr = curr->next;
    }

    HashNode* newNode = new HashNode(sampleID, patientData);
    newNode->next = buckets[index];
    buckets[index] = newNode;
}

string MetadataHashTable::searchMetadata(const string& sampleID) const{
    if (sampleID.empty()){
        return "";
    }

    int index = hashFunction(sampleID);
    HashNode* curr = buckets[index];

    while (curr != nullptr){
        if (curr->sampleID == sampleID){
            return curr->patientData;
        }

        curr = curr->next;
    }

    return "";
}

MetadataHashTable::~MetadataHashTable(){
    for (int i = 0; i < TABLE_SIZE; i++){
        HashNode* curr = buckets[i];
        while (curr != nullptr){
            HashNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        buckets[i] = nullptr;
    }
}
