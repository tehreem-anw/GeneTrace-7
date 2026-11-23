#include "FileHandler.h"

bool FileHandler::loadGenomeFile(const string& filename, string& genome)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Unable to open genome file." << endl;
        return false;
    }

    genome.clear();

    char ch;

    while (file.get(ch))
    {
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
        {
            continue;
        }

        ch = toupper(ch);

        if (ch != 'A' && ch != 'C' && ch != 'G' && ch != 'T')
        {
            cout << "Invalid DNA character: " << ch << endl;

            genome.clear();
            file.close();

            return false;
        }

        genome += ch;
    }

    file.close();

    if (genome.empty())
    {
        cout << "Genome file is empty." << endl;
        return false;
    }

    cout << "Genome loaded successfully!" << endl;
    cout << "Total DNA bases: " << genome.length() << endl;

    return true;
}
