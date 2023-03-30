#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Genome {
private:
    string RNA;
    string DNA;
    // We define a reverse function which will be used later on
    string reverse(string s){
        string Reversed_s;
        for (int i = s.length() - 1; i >= 0; i--)
            Reversed_s += s[i];

        return Reversed_s;
    }

public:
    //Here we define the setters and getters for DNA and RNA
    void SetRNA(string s){
        RNA = s;
    }

    string GetRNA(){
        return RNA; 
    }
    
    void SetDNA(string s){
        DNA = s;
    }

    string GetDNA(){
        return DNA;
    }

    string Supplement(string s);//Here we define a method for creating the supplement of the given string
                                //With which we can make a DNA out of an RNA as well

    //Here we define the methods neccessary for the different types of mutations
    //for the DNA mutations we have to apply the conditions to both of the DNA threads
    string SmallMutationRNA(char a, char b, int n);
    void SmallMutationDNA(char a, char b, int n);
    void BigMutationRNA(string& s1, string& s2);
    void BigMutationDNA(string& s1, string& s2);

    // In this section we define a funtion that replaces a substring in a string with it's reverse
    // using the reverse function we defined in the beginning of the program 
    void ReverseRNA(string& s1); 
    void ReverseDNA(string& s1);  
};

string Genome::Supplement(string s){
    string y;
    int x = s.length();
    for (int i = 0; i < x; i++) {
        if (s[i] == 'A')
            y += 'T';
         
        else if (s[i] == 'T')
            y += 'A';

        else if (s[i] == 'C') 
            y += 'G';

        else if (s[i] == 'G') 
            y += 'C';
        }
    return y;
}

string Genome::SmallMutationRNA(char a, char b, int n){
    int i = 0;
    int j = 0; //movement step
    while (i <= n){
        if (RNA[j] == a){
            RNA[j] = b;
            i++;
            j++;
            if (i == n)
            break;
        } 

        else 
            j++;
    }
    return RNA;
}

void Genome::SmallMutationDNA(char a, char b, int n){
    int i = 0;
    int j = 0; //movement step
    while (i <= n){
        if (DNA[j] == a){
            DNA[j] = b;
            i++;
            j++;
            if (i == n)
                break;
        }

        else if(Supplement(DNA)[j] == a){
            if(b == 'G')
                DNA[j] = 'C';

            else if (b == 'C')
                DNA[j] = 'G';
            
            else if (b == 'T')
                DNA[j] = 'A';
            
            else if (b == 'A')
                DNA[j] = 'T';

            i++;
            j++;

            if(i == n)
                break;
        }

        else 
            j++;
    }

    cout << DNA << '\t' << Supplement(DNA) << endl;
}

void Genome::BigMutationRNA(string& s1, string& s2){
    string s = RNA;
	string ans = "";
    bool check = true;

    for (int i = 0; i < s.length(); i++){
        int k = 0;
        
        // If the first charactar of string s1 is the same as the given((i + 1)th) character of DNA
        if (s[i] == s1[k] && i + s1.length() <= s.length()){
            int j;
            
            // Whether string s1 completely matches with a substring of DNA or not
            for (j = i; j < i + s1.length(); j++){
                if (s[j] != s1[k])
                    break;

                else
                    k++;
            }
            
            // If string s1 completely matches with a substring of DNA replace the substring with string s2
            if (j == i + s1.length() && check == true){
                ans.append(s2);
                i = j - 1;
                check = false;
            }
 
            else
                ans.push_back(s[i]);
        }
 
        else
            ans.push_back(s[i]);
    }

    // Here we print the string made in the process above
    cout << ans << endl;
}

void Genome::BigMutationDNA(string& s1, string& s2){
    string s = DNA;
    string ss1 = Supplement(s1);
    string ss2 = Supplement(s2);
    string ans = "";
    string anss= "";
    bool check1 = true;
    bool check2;

    // In this section we determine in which one of the DNA threads we will encounter 
    // the given string first
    for (int i = 0; i < s.length(); i++){
        int k = 0;
        int kk = 0;

        // If the first charactar of string s1 is the same as the given((i + 1)th) character of DNA
        if (s[i] == s1[k] && i + s1.length() <= s.length()){
            int j;

            // Whether string s1 completely matches with a substring of DNA or not
            for (j = i; j < i + s1.length(); j++){
                if (s[j] != s1[k])
                    break;

                else
                    k++;
            }

            // If string s1 completely matches with a substring of DNA replace the substring with string s2
            if (j == i + s1.length() && check1 == true){
                ans.append(s2);
                i = j - 1;
                check1 = false;
                check2 = true;
            }
 
            else
                ans.push_back(s[i]);
        }
 
        else
            ans.push_back(s[i]);

        // If the first charactar of string ss1 is the same as the given((i + 1)th) character of SDNA
        if(s[i] == ss1[kk] && i + ss1.length() <= s.length()){
            int jj;

            // Whether string ss1 completely matches with a substring of SDNA or not
            for(jj = i; jj < i + ss1.length(); jj++){
                if (s[jj] != ss1[kk])
                    break;
                
                else
                    kk++;
            }

            // If string ss1 completely matches with a substring of SDNA replace the substring with string ss2
            if(jj == i + ss1.length() && check1 == true){
                anss.append(ss2);
                i = jj - 1;
                check1 = false;
                check2 = false;
            }

            else 
                anss.push_back(s[i]);
        }

        else 
            anss.push_back(s[i]);

    }

    // Here we print the DNA threads to which we append the given string first
    if (check2 == true)
        cout << "1" <<  ans << '\t' << Supplement(ans) << endl;
    
    else
        cout << "2" << anss << '\t' << Supplement(anss) << endl;
}

void Genome::ReverseRNA(string& s1){
    /*string Reversed_s = reverse(s1);
    string s = RNA;
    string ans = "";
    bool check = true;

    for (int i = 0; i < s.length(); i++){
        int k = 0;
        if (s[i] == s1[k] && i + s1.length() <= s.length()){
            int j;
            for (j = i; j < i + s1.length(); j++){
                if (s[j] != s1[k])
                    break;

                else
                    k++;
            }

            if (j == i + s1.length() && check == true){
                ans.append(Reversed_s);
                i = j - 1;
                check = false;
            }
 
            else
                ans.push_back(s[i]);
        }
 
        else
            ans.push_back(s[i]);
    }
    cout << ans << endl; */

    string  Reversed_s = reverse(s1);
    
    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the give starting position 
    int x = RNA.find(s1);
    int y = s1.length();

    // Replaces y characters from xth index by Reversed_s
    RNA.replace(x, y, Reversed_s);

    cout << RNA << endl;

}

void Genome::ReverseDNA(string& s1){
    string Reversed_s = reverse(s1);
    string Reversed_supplement_s = reverse(Supplement(s1));

    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the give starting position 
    int y = s1.length();
    int x = RNA.find(s1);

    // Replaces y characters from xth index by Reversed_s
    RNA.replace(x, y, Reversed_s);

    // Replaces y characters from xth index by Reversed_supplement_s
    Supplement(RNA).replace(x, y, Reversed_supplement_s);

    cout << RNA << '\t' << Supplement(RNA) << endl;
}

int main(){}





