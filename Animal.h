//
// Created by zalia on 3/30/2023.
//

#ifndef AP_MIDTERM_ANIMAL_H
#define AP_MIDTERM_ANIMAL_H

#endif //AP_MIDTERM_ANIMAL_H
#include "Cell.h"
#include <iostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Animal : public Cell1 {
private:

public:
    float PGS(vector<string> vec1, vector<string> vec2); //percentage of genetic similarity
    string ORE(vector<string> vec11, vector<string> vec12); //Operator rewrite equall
    vector<string> duplicateStrings(vector<string> input);   //Asexual reproduction
    vector<string> sexual_reproduction(vector<string> a1,vector<string> b1);
};