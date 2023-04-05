#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

class Genome {
private:
    string RNA;
    string DNA[2];

public:
    // The main Constructor
    Genome(string dna, string sdna, string rna){
        DNA[0] = dna;
        DNA[1] = sdna;
        RNA = rna;
        if (dna != Supplement(sdna))
            cout << "The DNA threads do not supplement each other." << endl;
    }

    //An empty default constructor which we need since we
    Genome(){}

    //Here we define the getters for RNA and DNA threads
    string GetDNA(){
        return DNA[0];
    }

    string GetSDNA(){
        return DNA[1];
    }

    string GetRNA(){
        return RNA;
    }

    string reverse(string s);

    //A method for creating the DNA threads out of an RNA thread
    void MakeDNAoutofRNA(string s);

    //A method for creating the supplement of the given string
    string Supplement(string s);

    //Here we define the methods neccessary for the different types of mutations
    //for the DNA mutations we have to apply the conditions to both of the DNA threads
    void SmallMutationRNA(char a, char b, int n);
    void SmallMutationDNA(char a, char b, int n);
    void BigMutationRNA(string& s1, string& s2);
    void BigMutationDNA(string& s1, string& s2);

    // In this section we define a funtion that replaces a substring in a string with it's reverse
    // using the reverse function we defined in the beginning of the program 
    void ReverseMutationRNA(string& s1); 
    void ReverseMutationDNA(string& s1);
};

class Cell : public Genome{
private:
    int NumberOfChromozomes;
    vector <Genome> chromozomes;

    // Here we define a function type boolean that determines whether a string is palindrome or not which
    // will be used later on in the program
    

public:

    Cell(int number_of_chromozomes){
        NumberOfChromozomes = number_of_chromozomes;
    }

    int GetNumberOfChromozomes(){ 
        return NumberOfChromozomes; 
    }

    bool isPalindrome(string s);

    void SetChromozomes(){
        for (int i = 0; i < NumberOfChromozomes; i++){
            string s1 = "";
            string s2 = "";
            string s3 = "";

            if ((i + 1) % 10 >= 4)
                cout << "Enter the " << i + 1 << "th chromozome's DNA threads: " << endl;
            else if ((i + 1) % 10 == 3)
                cout << "Enter the " << i + 1 << "rd chromozome's DNA threads: " << endl;
            else if ((i + 1) % 10 == 2)
                cout << "Enter the " << i + 1 << "nd chromozome's DNA threads: " << endl;
            else if ((i + 1) % 10 == 1)
                cout << "Enter the " << i + 1 << "st chromozome's DNA threads: " << endl;
            
            cin >> s1 >> s2;
            Genome chromozome (s1, s2, s3);
            chromozomes.push_back(chromozome);
        }
    }

    void GetChromozomes(){
        for (int i = 0; i < chromozomes.size(); i++){
            if ((i + 1) % 10 >= 4)
                cout << "The " << i + 1 << "th chromozome: " << endl;
            else if ((i + 1) % 10 == 3)
                cout << "The " << i + 1 << "rd chromozome: " << endl;
            else if ((i + 1) % 10 == 2)
                cout << "The " << i + 1 << "nd chromozome: " << endl;
            else if ((i + 1) % 10 == 1)
                cout << "The " << i + 1 << "st chromozome: " << endl;

            cout << chromozomes[i].GetDNA() << '\t' << chromozomes[i].GetSDNA() << '\t' << chromozomes[i].GetRNA() << endl;
        }
    }

    // Cell Death function is based on the chromozome that is being tested
    void CellDeath();

    // In this section we redefine DNA mutations
    void BigMutationDNA(string ss1, int nn, string ss2, int mm);
    void SmallMutationDNA(char a, char b, int n, int m);

    //void reverseSubstring(string substring, int n);
    void ReverseMutationDNA(string s1, int n);
    void FindSupplementPalindromes(int n);
};

// Here are the methods of class Genome

string Genome::reverse(string s){
    string Reversed_s;
    for (int i = s.length() - 1; i >= 0; i--)
        Reversed_s += s[i];

    return Reversed_s;
}

string Genome::Supplement(string s){
    string ss;
    int x = s.length();
    for (int i = 0; i < x; i++) {
        if (s[i] == 'A')
            ss += 'T';
         
        else if (s[i] == 'T')
            ss += 'A';

        else if (s[i] == 'C') 
            ss += 'G';

        else if (s[i] == 'G') 
            ss += 'C';
        }
    return ss;
}

void Genome::MakeDNAoutofRNA(string s){
    string ss;
    int x = s.length();
    for (int i = 0; i < x; i++) {
        if (s[i] == 'A')
            ss += 'T';
         
        else if (s[i] == 'T')
            ss += 'A';

        else if (s[i] == 'C') 
            ss += 'G';

        else if (s[i] == 'G') 
            ss += 'C';
        }
    
    cout << "The DNA threads made out of this RNA thread: " << s << '\t' << ss << endl;
}

void Genome::SmallMutationRNA(char a, char b, int n){
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
    cout << "The RNA thread after small mutation: " << RNA << endl;
}

void Genome::SmallMutationDNA(char a, char b, int n){
    int i = 0, j = 0;
    while (i <= n){
        if (DNA[0][j] == a){
            DNA[0][j] = b;
            i++;
            j++;
            if (i == n)
                break;
        }

        else if(DNA[1][j] == a){
            if(b == 'G')
                DNA[0][j] = 'C';

            else if (b == 'C')
                DNA[0][j] = 'G';
            
            else if (b == 'T')
                DNA[0][j] = 'A';
            
            else if (b == 'A')
                DNA[0][j] = 'T';

            i++;
            j++;

            if(i == n)
                break;
        }

        else 
            j++;
    }

    cout << "The DNA threads after small mutations: " << DNA[0] << '\t' << Supplement(DNA[0]) << endl;
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
    cout << "The RNA thread after big mutation: "<< ans << endl;
}

void Genome::BigMutationDNA(string& s1, string& s2){
    string s = DNA[0];
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
        cout << "The DNA threads after big mutations: " <<  ans << '\t' << Supplement(ans) << endl;
    
    else
        cout << "The DNA threads after big mutations: " << anss << '\t' << Supplement(anss) << endl;
}

void Genome::ReverseMutationRNA(string& s1){
    string  Reversed_s = reverse(s1);
    
    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the given starting position 
    int x = RNA.find(s1);
    int y = s1.length();

    // Replaces y characters from xth index by Reversed_s
    RNA.replace(x, y, Reversed_s);

    cout << "The RNA thread after reverse mutation: "<< RNA << endl;

}

void Genome::ReverseMutationDNA(string& s1){
    string Reversed_s1 = reverse(s1);
    string Reversed_supplement_s1 = reverse(Supplement(s1));

    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the given starting position 
    int y = s1.length();
    int x = DNA[0].find(s1);

    // Replaces y characters from xth index by Reversed_s
    DNA[0].replace(x, y, Reversed_s1);

    // Replaces y characters from xth index by Reversed_supplement_s
    Supplement(DNA[0]).replace(x, y, Reversed_supplement_s1);

    cout << "The DNA threads after reverse mutation: " << DNA[0] << '\t' << Supplement(DNA[0]) << endl;
}

// Here are the methods of class Cell

bool Cell::isPalindrome(string s){
    int n = s.length();
    for(int i = 0; i < n / 2 ; i++){
        if(s[i] != s[n - i - 1])
            return false;
    }
    return true;
}

void Cell::CellDeath(){
    for (int i = 0; i < chromozomes.size(); i++){
        cout << "Round: " << i << endl;
        cout << chromozomes[i].GetDNA() << '\t' << chromozomes[i].GetSDNA() << '\t' << chromozomes[i].GetRNA() << endl;
        bool check = true;
        int count = 0;
        int countAT = 0;
        int countCG = 0;
        string s1 = chromozomes[i].GetDNA();
        string s2 = chromozomes[i].GetSDNA();
        if(check == true){
            for (int j = 0; j < chromozomes[i].GetDNA().length(); j++){
                if (s1[j] != Supplement(s2)[j]){
                    cout << "?" << '\t' << j << '\t' << Supplement(s2)[j] << endl;
                    count++;
                }
            
                if (count > 5){
                    cout << "!" << endl;
                    chromozomes.erase(chromozomes.begin() + i);
                    i--;
                    check = false;
                    break;
                }
            }
        }

        if(check == true){
            for (int k = 0; k < chromozomes[i].GetDNA().length(); k++){
            
                if (s1[k] == 'A' || s1[k] == 'T'){
                    countAT++;
                    cout << "??" << '\t' << k << '\t' << "1" << endl;
                }

                if (s2[k] == 'A' || s2[k] == 'T'){
                    countAT++;
                    cout << "??" << '\t' <<  k << '\t' << "2" << endl;
                }
            
                if (s1[k] == 'C' || s1[k] == 'G'){
                    countCG++;
                    cout << "??" << '\t' << k << '\t' << "3" << endl;
                }

                if (s2[k] == 'C' || s2[k] == 'G'){
                    countCG++;
                    cout << "??" << '\t' << k << '\t' << "4" << endl;;
                }

                if(countAT > 3 * countCG && k == chromozomes[i].GetDNA().length() - 1){
                    cout << countAT << '\t' << countCG << endl;
                    cout << "!!" << endl;
                    chromozomes.erase(chromozomes.begin() + i);
                    i--;
                    check = false;
                    break;
                }
            }
        }
    }
}

/*void Cell::BigMutationDNA(string ss1, int nn, string ss2, int mm){
    string c1 = chromozomes[nn];
    string c2 = chromozomes[mm];

    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the given starting position 
    int x1 = c1.find(ss1);
    int y1 = ss1.length();
    int x2 = c2.find(ss2);
    int y2 = ss2.length();

    // Replaces y1 characters from x1th index by ss2
    c1.replace(x1,y1,ss2);
    // Replaces y2 characters from x2th index by ss1
    c2.replace(x2,y2,ss1);
       
    cout << c1 << '\t' << Supplement(c1)<< '\n' << c2 << '\t' << Supplement(c2)<<endl;
}*/

/*void Cell::BigMutationDNA(string& s1, int n, string& s2, int m){
    string ch1 = chromozomes[n].GetDNA();
    string ch2 = chromozomes[m].GetDNA();
    string ch11 = chromozomes[n].GetSDNA();
    string ch22 = chromozomes[m].GetSDNA();

    string ss1 = Supplement(s1);
    string ss2 = Supplement(s2);

    string ans = "";
    string anss= "";
    bool check1 = true;
    bool check2;

    for (int i = 0; i < )




}*/

void Cell::SmallMutationDNA(char a, char b, int n, int m){
    // We have to minus integer m by 1 because the indexes in vectors start with 0
    // and we want to target the mth chromozome
    cout << "GUTS";
    string s1 = chromozomes[m - 1].GetDNA();
    string s2 = chromozomes[m - 1].GetSDNA();
    int i = 0, j = 0;

    while (i <= n){
        if (s1[j] == a){
            s1[j] = b;
            i++;
            j++;
            if (i == n)
                break;
        }

        else if(s2[j] == a){
            if(b == 'G')
                s1[j] = 'C';

            else if (b == 'C')
                s1[j] = 'G';
            
            else if (b == 'T')
                s1[j] = 'A';
            
            else if (b == 'A')
                s1[j] = 'T';

            i++;
            j++;

            if(i == n)
                break;
        }   

        else
            j++; 
    }
    cout << s1 << '\t' << Supplement(s1) << endl;
}

void Cell::ReverseMutationDNA(string s1, int n){
    string s2 = Supplement(s1);

    // We have to minus integer n by 1 because the indexes in vectors start with 0
    // and we want to target the nth chromozome
    string s3 = chromozomes[n - 1].GetDNA();
    string s4 = chromozomes[n - 1].GetSDNA();
    string Reversed_s1 = reverse(s1);
    string Reversed_s2 = reverse(Supplement(s1));
    
    int y = s1.length();
    int x1 = s3.find(s1);
    int x2 = s4.find(s2);

    if(x1 == string::npos)
        cout << "The given string was not found in the given chromozome's main DNA thread." << endl;

    if(x2 == string::npos)
        cout << "The supplement of the given string was not found int the given chromozome's supplemantary DNA thread." << endl;
    
    else{
        s3.replace(x1, y, Reversed_s1);
        s4.replace(x2, y, Reversed_s2);
    }

    cout << "The DNA threads after reverse mutation: " << s3 << '\t' << s4 << endl;
}   

void Cell::FindSupplementPalindromes(int n){
    string s1 = chromozomes[n - 1].GetDNA();
    string s2 = chromozomes[n - 1].GetSDNA();
    
    

}



int main(){
    // You should initialize the constructor in this order : 1.DNA's main thread 2.DNA's supplemetary thread 3.RNA
    Cell cell(2);
    cell.SetChromozomes();
    cell.GetChromozomes();
    //cell.SmallMutationDNA('A', 'C', 2, 2);
    //cell.ReverseMutationDNA("TCAG", 2);
    cell.FindLongestPalindrome(2);

    
}

//genome.MakeDNAoutofRNA(genome.GetRNA());
    //genome.SmallMutationRNA('A', 'C', 2);
    //genome.SmallMutationDNA('A', 'C', 2);
    //string s1 = "TCAG";
    //string s2 = "ATC";
    //genome.BigMutationRNA(s1, s2);
    //genome.BigMutationDNA(s1, s2);
    //cout << genome.GetDNA() << '\t' << genome.GetSDNA() << endl;
    //genome.ReverseMutationRNA(s1);
    //genome.ReverseMutationDNA(s1);
