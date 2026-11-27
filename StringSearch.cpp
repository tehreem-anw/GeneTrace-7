#include "StringSearch.h"

void StringSearch::computeLPS(const string& pattern, int M, int lps[])
{
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < M){
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


int* StringSearch::KMP_Search(const string& text, const string& pattern, int& matchCount){
    matchCount = 0;
    int N = text.length();
    int M = pattern.length();

    if (M == 0 || N == 0 || M > N){
        return nullptr;
    }

    int* lps = new int[M];
    computeLPS(pattern, M, lps);
    int* matches = new int[N];

    int i = 0;
    int j = 0;

    while (i < N){
        if (text[i] == pattern[j]){
            i++;
            j++;
            if (j == M){
                matches[matchCount] = i - j;
                matchCount++;
                j = lps[j - 1];
            }
        }
        else{
            if (j != 0){
                j = lps[j - 1];
            }
            else{
                i++;
            }
        }
    }
    delete[] lps;
    return matches;
}
