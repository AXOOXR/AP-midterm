//
// Created by zalia on 3/30/2023.
//

#include "Animal.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

float Animal::PGS(vector<string> vec1, vector<string> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();

    // Check if the vectors are of the same size
    if (size1 != size2) {
        cout << "Vectors are not of the same size" << endl;
        return 0.0;
    }
    // Check how many strings are the same in the vectors
    int numSame = 0;
    for (int i = 0; i < size1; i++) {
        if (vec1[i] == vec2[i]) {
            numSame++;
        }
    }
    float percentage = (float) numSame / (float) size1 * 100.0;
    return percentage;

}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
string Animal::ORE(vector<string> vec11, vector<string> vec12) {
    if (Animal::PGS(vec11, vec12) > 70.00) {
        return "True";
    } else {
        return "False";
    }
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
vector<string> Animal::duplicateStrings(vector<string> input) {
    vector<string> output;
    vector<string> random;
    int n;
    n = input.size();
    for (const auto &str: input) {
        output.push_back(str);
        output.push_back(str);

    }
    for (int i = 0; i < n; ++i) {
        srand(time(NULL)); // seed the random number generator with the current time
        int random_number = rand() % n + 1; // generate a random number in the range [1, n]
        random[i] = output[random_number];
    }
    return random;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void Animal::sexual_reproduction(vector<string> a1, vector<string> b1) {
    vector<string> output1;
    vector<string> output2;

    vector<string> random;
    int n1;
    n1 = a1.size();
    for (const auto &str: a1) {
        output1.push_back(str);
        output1.push_back(str);
    }
    for (int i = 0; i < n1 / 2; ++i) {
        srand(time(NULL)); // seed the random number generator with the current time
        int random_number = rand() % n1 + 1; // generate a random number in the range [1, n]
        random[i] = a1[random_number];
    }

    for (const auto &str: b1) {
        output2.push_back(str);
        output2.push_back(str);
    }
    int n2;
    n2 = b1.size();
    for (int i = 0; i < n2 / 2; ++i) {
        srand(time(NULL)); // seed the random number generator with the current time
        int random_number = rand() % n2 + 1; // generate a random number in the range [1, n]
        random[i] = b1[random_number];
    }
    if (n1 % 2 != 0) {
        if (n2 % 2 != 0) {
            for (int i = 0; i < random.size(); ++i) {
                cout << random[i]<<endl;
            }
        }else {
            cout << "n is odd im sorry"<<endl;
        }
    } else {
        cout << "n is odd im sorry"<<endl;
    }
}
//------------------------------------------------------------------


