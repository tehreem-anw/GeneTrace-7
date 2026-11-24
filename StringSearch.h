
#pragma once

#include <iostream>
#include <string>

using namespace std;

class StringSearch
{
private:

    void computeLPS(const string& pattern, int M, int lps[]);

public:

    int* KMP_Search(const string& text, const string& pattern, int& matchCount);

};
