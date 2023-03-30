//
// Created by zalia on 3/30/2023.
//

#ifndef AP_MIDTERM_VIRUS_H
#define AP_MIDTERM_VIRUS_H

#endif //AP_MIDTERM_VIRUS_H

#include "Cell.h"
#include <iostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class VIRUS : public Cell1 {
public:
    //A method to detect the harmfulness of the virus  -> DHV
    //EXTRA POINT
    void DHV(vector<string> input ,string rna);
    //---------------------------------------------------------
};