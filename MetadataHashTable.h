#pragma once

#include <iostream>
#include <string>

using namespace std;

struct HashNode
{
    string sampleID;
    string patientData;
    HashNode* next;

    HashNode(string id, string data)
    {
        sampleID = id;
        patientData = data;
        next = nullptr;
    }
};

class MetadataHashTable
{
private:

    static const int TABLE_SIZE = 101;

    HashNode* buckets[TABLE_SIZE];

    int hashFunction(const string& sampleID) const;

public:

    MetadataHashTable();

    ~MetadataHashTable();

    void insertMetadata(const string& sampleID, const string& patientData);

    string searchMetadata(const string& sampleID) const;
};
