//
// Created by zalia on 3/21/2023.
//

#include "Cell.h"
#include <iostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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

class Cell : public Gene {
private:
    int n; //number of coromozom
    vector<string> coromozoms;
    bool isPalindrome(string s){
        int n = s.length();
        for(int i=0; i<n/2; i++){
            if(s[i] != s[n-i-1]){
                return false;
            }
        }
        return true;
    }
public:

    void setN(int n1) { n = n1; }

    int getN() { return n; }

    //----------------------------------------------------------------------------
    void setCoromozom(string arr[]) {
        for (int i = 0; i < n; ++i) {
            coromozoms.push_back(arr[i]);
        }

    }

    void getCoromozom() { //برای راحتی چاپ میکنه
        for (int i = 0; i < n; ++i) {
            cout << coromozoms[i] << '\t';
        }
    }

    //----------------------------------------------------------------------------
    void celldeath(int n1) { //اون کرموزومی که قراره چکش کنه
        string m;
        int n2;
        m = coromozoms[n1];
        n2 = m.length() - 5;
        for (int i = 0; i < n2; ++i) {
            for (int j = i; j < i + 5; ++j) {
                int pos1 = 0, pos2 = 0;
                string r = m.substr(i, 5);
                size_t found1 = r.find('AT');
                size_t found2 = r.find('CG');
                if (found1 != string::npos) {
                    pos1 += 1;
                } else if (found2 != string::npos) {
                    pos2 += 1;
                }
                if (pos1 + pos2 == 0) {
                    coromozoms[n1] = '0';
                    break;
                }
            }
        }
        //اینجا میاد تو دوتا حلقه تو در تو 5 تا 5 تا نگاه میکنه که ایا اون دوتا پیوند تو اون تقسیم بندیه هست یا نه اگه هیچ کدوم نبود
        // که در این صورت جمعشون برابر با صفر میشه و میاد یریک میکنه و اون دی ان ای رو برابر با صفر میذاره
        //  صفر میذاره چون اگه از دستور ایریس یا پاک کردن برای وکتور ها استفاده میکرد تعداد کروموزوم ها تغییر میکرد
        //----------------------------------------------------------------------------
        // count AT in dna
        int count = 0;
        for (int i = 0; i < m.length() - 1; i++) {
            if (m.substr(i, 2) == "AT") {
                count++;
            }
        }
        //----------------------------------------------------------------------------
        //count CG in dna
        int count2 = 0;
        for (int i = 0; i < m.length() - 1; i++) {
            if (m.substr(i, 2) == "CG") {
                count2++;
            }
        }
        //----------------------------------------------------------------------------
        if (count > (3 * count2)) {
            coromozoms[n1] = '0';
        }
    }

    //end of celldeath
    //----------------------------------------------------------------------------
    //متود جهش بزرگ را بازنویسی کنید. )همنام با متود جهش بزرگ در کلاس
    //Gene)
    void BigMutationDna(string ss1, int nn, string ss2, int mm) {
        string c1;
        string c2;
        string s1 = ss1;
        c1 = coromozoms[nn];
        c2 = coromozoms[mm];
        int x1, y1; // x1 = first char of ss1 in c1 , y1 = length ss1
        x1 = c1.find(ss1);
        y1 = ss1.length();
        int x2, y2; // x2 = first char of ss2 in c2 , y2 = length ss2
        x2 = c2.find(ss2);
        y2 = ss2.length();
        //-------------------
        c1.replace(x1,y1,ss2);
        c2.replace(x2,y2,ss1);
        //-------------------
        cout << c1 << "\t" << make_Dna(c1)<< "\n" << c2 << "\t" <<make_Dna(c2)<<endl;
    }
    //----------------------------------------------------------------------------
    //متود جهش کوچک را بازنویسی کنید.

    //----------------------------------------------------------------------------
    //متود جهش معکوس را بازنویسی کنید
    void reverseSubstring(string substring, int n) {
        string str = coromozoms[n];
        int start = str.find(substring);
        if (start == string::npos) {
            cout << "Substring not found in string" << endl;
            return;
        }

        int end = start + substring.length() - 1;
        while (start < end) {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }
        cout << str <<endl;
        coromozoms[n] = str;
    }

    //----------------------------------------------------------------------------
    //متودی برای پیدا کردن پالیندروم
    string findLongestPalindrome(int n) {
        string s;
        s = coromozoms[n];
        int n2 = s.length();
        string longestPalindrome = "";

        for (int i = 0; i < n2; i++) {
            for (int j = i + 2; j <= n2; j++) {
                string substring = s.substr(i, j - i);
                if (isPalindrome(substring) && substring.length() > longestPalindrome.length()) {
                    longestPalindrome = substring;
                }
            }

        }
        return longestPalindrome;

    }




};

