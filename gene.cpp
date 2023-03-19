#include <iostream>
#include <string>

using namespace std;

class Gene{
private:
    string RNA;
    string DNA;
    string MDNA; //mokamel DNA



public:
    //RNA
    viod setRna(string r) {RNA = r;} //setter
    string getRna() {return RNA;} //getter
    //DNA
    viod setDna(string d,string md) { //setter
        DNA = d;
        MDNA = md;
    }
    string getDna() {return DNA,MDNA} //getter

    //----------------------------------------------------------------------------

    



};
