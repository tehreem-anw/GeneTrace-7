#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class FileHandler
{
public:

    bool loadGenomeFile(const string& filename, string& genome);

};
