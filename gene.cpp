#include <iostream>
#include <string>

using namespace std;

class Gene {
private:
    string RNA;
    string DNA;
    string MDNA; //mokamel DNA



public:
    //RNA
    viod setRna(string r) { RNA = r; } //setter
    string getRna() { return RNA; } //getter
    //DNA
    viod setDna(string d, string md) { //setter
        DNA = d;
        MDNA = md;
    }

    string getDna() { return DNA, MDNA } //getter

    //----------------------------------------------------------------------------

    //method for write Dna from Rna
    string make_Dna(string r1) {
        int x;
        string y;
        x = r1.lenght();
        for (int i = 0; i < x; i++) {
            if (r1[i] == "A") {
                y += "T";
            } else if (r1[i] == "T") {
                y += "A";
            } else if (r1[i] == "C") {
                y += "G";
            } else if (r1[i] == "G") {
                y += "C";
            }

        }

    }

    //method of Mutation of gene in RNA:
    string MutationRna(char a, char b, int n) {
        int i =0;
        int j =0; //movement step
        while (i <= n) {
            if (RNA[j] == a) {
                RNA[j] = b;
                i++;
                j++;
                if (i==n) { break;}
            } else {
                j++;
            }

        }

    }



};
