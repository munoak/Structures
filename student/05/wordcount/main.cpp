#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>


using namespace std;

std::vector<std::string> split(const std::string &line,
                               const char sep,
                               bool ignore_empty = false)
{
    std::vector<std::string> parts = {};
    std::string part = "";

    for(char c : line )
    {
        if (c == sep)
        {
            if(!(part.empty() && ignore_empty))
        {
                parts.push_back(part);
            }
            part.clear();

        }
        else {
            part += c;
        }
}
    parts.push_back(part);
    return parts;

}

void print_data(pair<string, set<int>> const &word)
{
    uint total_row_number = word.second.size();
    cout << word.first<< ' ' << total_row_number << ':';

    for(set<int>::iterator iter = word.second.begin(); iter != word.second.end(); iter++ )
    {
        cout << ' ' << *iter;
        if(++iter != word.second.end())
        {
            cout<< ',';

        }
        iter--;
    }
    cout <<endl;

}

int main()
{
    string ch;
    string f1;
    cout << "Input file: ";
    getline(cin, f1);
    // opening file to read the content
    ifstream f1_object(f1);
    if (!f1_object)
    {
        cout << "Error! The file " << f1 << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    map<string, set<int>> words;
    string line;
    vector<string> line_words;
    vector<string>::iterator words_itr;
    uint line_counter = 1;

    while(getline(f1_object, line))
    {
        line_words = split(line, ' ', true);
        words_itr = line_words.begin();
        while(words_itr !=line_words.end())
        {
            if(words.find(*words_itr) == words.end())
            {
                words.insert({*words_itr, {}});
            }
            words.at(*words_itr).insert(line_counter);
            ++words_itr;
        }
        ++line_counter;
    }

    for(pair<string, set<int>> const &word_data : words)
    {
        print_data(word_data);
    }
    // closing the files
    f1_object.close();
    return 0;
}
