//
// Created by zalia on 3/30/2023.
//

#include "VIRUS.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void VIRUS::DHV(vector<string> input, string rna) {
    string rna1;
    rna1 = make_Dna(rna);
    for (int i = 0; i < input.size() ; ++i) {
        string rr;
        rr = input[i];
        size_t index1= rr.find(rna);
        size_t index2 = rr.find(rna1);

        if (index1 == std::string::npos){
            cout<< "False"<<endl;
        } else if (index2 == std::string::npos){
            cout << "False" <<endl;
        } else{
            cout << "True" <<endl;
        }
    }
}
//---------------------------------------------------------
