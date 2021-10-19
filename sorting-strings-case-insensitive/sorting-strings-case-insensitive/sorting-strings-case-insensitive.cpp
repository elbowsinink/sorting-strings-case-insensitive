#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int main()
{
    vector <string> words;
    string input_string;
    string input_file = "..\\input.txt";
    string output_file = "..\\output.txt";
    ifstream file(input_file);
    if (file.is_open())
    {
        while (getline(file, input_string)) {
            if (!input_string.empty()) {
                regex rgx("[^A-zА-яё]");
                sregex_token_iterator iter(
                    input_string.begin(), //start of the processed sequence
                    input_string.end(), //end of the processed sequence
                    rgx, //regular expression
                    -1); //–1 - for processing parts of a string that do not match a regular expression
                sregex_token_iterator end;
                for (; iter != end; ++iter)
                {
                    if (*iter != "") {
                        words.push_back(*iter);
                    }
                }
                sort(words.begin(), words.end(),
                    [](const auto& sequence_one, const auto& sequence_two) {
                        //mismatch - compares two sequences and finds the first position where the elements are different
                        const auto result = mismatch(sequence_one.begin(), sequence_one.end(), sequence_two.begin(), sequence_two.end(),
                            [](const auto& sequence_one, const auto& sequence_two)
                            {
                                //tolower - converts uppercase letters to lowercase
                                return tolower(sequence_one) == tolower(sequence_two);
                            }
                        );
                        return (result.second != sequence_two.end()) &&
                            (
                                (result.first == sequence_one.end()) || (tolower(*result.first) < tolower(*result.second))
                                );
                    });
            }
        }
    }
    file.close();
    ofstream out(output_file);
    if (out.is_open())
        for (auto i : words)
            out << i << endl;
    out.close();
    return 0;
}