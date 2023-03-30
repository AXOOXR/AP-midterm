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

};
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
string Animal::ORE(vector<string> vec11, vector<string> vec12) {
    if (Animal::PGS(vec11, vec12) > 70.00) {
        return "True";
    } else {
        return "False";
    }
};
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


