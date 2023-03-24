#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Gene {
private:
    string RNA;
    string DNA;
    string MDNA; //mokamel DNA
    string reverse1(string str) {
        string rts;
        for (int i = str.length() - 1; i >= 0; i--)
            rts = str[i];
        return rts;
    }


public:
    //RNA
    void setRna(string r) { RNA = r; } //setter
    string getRna() { return RNA; } //getter
    //DNA
    void setDna(string d, string md) { //setter
        DNA = d;
        MDNA = md;
    }

    string getDna() { return DNA, MDNA; } //getter

    //----------------------------------------------------------------------------

    //method for write Dna from Rna
    string make_Dna(string r1) {
        int x;
        string y;
        x = r1.length();
        for (int i = 0; i < x; i++) {
            if (r1[i] == 'A') {
                y += 'T';
            } else if (r1[i] == 'T') {
                y += 'A';
            } else if (r1[i] == 'C') {
                y += 'G';
            } else if (r1[i] == 'G') {
                y += 'C';
            }

        }
        return y;
    }

    //----------------------------------------------------------------------------

    //method of Mutation of gene in RNA:
    string MutationRna(char a, char b, int n) {
        int i = 0;
        int j = 0; //movement step
        while (i <= n) {
            if (RNA[j] == a) {
                RNA[j] = b;
                i++;
                j++;
                if (i == n) { break; }
            } else {
                j++;
            }
        }
        return RNA;
    }

    //----------------------------------------------------------------------------

    //method of Mutation of gene in DNA:

    void MutationDna(char a, char b, int n) {
        int i = 0;
        int j = 0; //movement step
        while (i <= n) {
            if (DNA[j] == a) {
                DNA[j] = b;
                i++;
                j++;
                if (i == n) { break; }
            } else {
                j++;
            }
        }
        cout << DNA << "\t";
        cout << make_Dna(DNA) << endl;
    }

    //----------------------------------------------------------------------------

    //Big  Mutation:
    void BigMutationRna(string r, string t) {
        int x, y;
        x = RNA.find(r);
        y = t.length();
        RNA.replace(x, y, t);
        cout << RNA << endl;
    }

    //----------------------------------------------------------------------------

    void BigMutationDna(string r, string t) {
        int x, y;
        x = RNA.find(r); //ابتدا بازه
        y = t.length(); // انتها بازه
        RNA.replace(x, y, t);  // جای گزینی اون با رشته مد نظر
        cout << RNA << "\n" << make_Dna(RNA) << endl;
    }

    //----------------------------------------------------------------------------

    void ReverseRna(string rt) { //rt ke input function
        int x, y;
        string rrt; //reverse rt

        x = RNA.find(rt); //
        y = rt.length();
        // موقعیت رشته اول اون ورودی مارو بهمون میده که برای راحتی اوی متغییر ذخیره میکنیم
        rrt = reverse1(rt);
        RNA.replace(x, y, rrt);
        cout << RNA << endl;
    }

    //----------------------------------------------------------------------------

    void ReverseDna(string rt) { //rt ke input function
        int x, y;
        string rrt; //reverse rt
        y = rt.length();
        x = RNA.find(rt); //موقعیت رشته اول اون ورودی مارو بهمون میده که برای راحتی اوی متغییر ذخیره میکنیم
        rrt = reverse1(rt);
        RNA.replace(x, y, rrt);
        cout << RNA << "\t";
        cout << make_Dna(RNA) << endl;
        // the gene class finish
        // only debug remain
        //----------------------------------------------------------------------------
        //----------------------------------------------------------------------------
        //----------------------------------------------------------------------------
    }
};

class Cell : public Gene
{
private:
    int n; //number of coromozom
public:
    void celldeath(string q){
        

    }

};