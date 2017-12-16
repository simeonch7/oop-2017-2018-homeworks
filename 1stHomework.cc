#include <cmath>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <iterator>
#include <exception>
#include <algorithm>

using namespace std;

int main()
{
    double max;
    double min;
    double sum;
    vector<string> everything;
    vector<double> parsedNumbers;
    string input;
    int count = 0;

    try {
        do {
            getline(cin, input);
            
            string curr;
            stringstream parse(input);

            while (parse >> curr && input != "END") {
                everything.push_back(curr);
            }

        } while (!cin.eof() && input != "END");

        vector<string>::iterator i = everything.begin();
        while (i != everything.end()) {
            double current;
            istringstream temp_stream(*i);
            if (*everything.begin() == "strict") {
                temp_stream >> current;
                cout.precision(4);
                if (temp_stream.fail() && i != everything.begin()) {
                    throw "ERR: PROVIDE ONLY NUMBERS";
                }
            }
            else if (*everything.begin() == "integers-only") {
                temp_stream >> current;
                cout << fixed << setprecision(0);
            }
            else if (*everything.begin() == "strict:integers-only" || *everything.begin() == "integers-only:strict") {
                temp_stream >> current;
                if (current != (int)current) {
                    throw "ERR: PROVIDE ONLY INTEGERS";
                }
                cout << fixed << setprecision(0);
                if (temp_stream.fail() && i != everything.begin()) {
                    throw "ERR: PROVIDE ONLY NUMBERS";
                }
            }

            else {
                cout.precision(4);
                temp_stream >> current;
            }
            if (temp_stream.eof() && !temp_stream.fail()) {
                parsedNumbers.push_back(current);
                if (count == 0) {
                    min = parsedNumbers[count];
                    max = parsedNumbers[count];
                    sum = 0.0;
                }
                if (parsedNumbers[count] > max)
                    max = parsedNumbers[count];

                if (parsedNumbers[count] < min)
                    min = parsedNumbers[count];

                sum += parsedNumbers[count];
                count++;
            }
            ++i;
        }
        int num = parsedNumbers.size();
        if (num == 0) {
            throw "ERR: PROVIDE AT LEAST ONE NUMBER";
        }
        else {
            double avg = sum / num;
            cout << min << " " << max << " " << avg << endl;
        }
    }
    catch (const char* e) {
        cout << e << endl;
    }
    return 0;
}
