#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Genome {
private:
    string RNA;
    string DNA[2];

public:
    // The Constructor
    Genome(string dna, string sdna, string rna){
        // The main DNA thread
        DNA[0] = dna;

        // The supplementary DNA thread
        DNA[1] = sdna;

        // The RNA thread
        RNA = rna;
        if (dna != Supplement(sdna))
            cout << "The DNA threads do not supplement each other." << endl;
    }

    // An empty default constructor which we need since we ''''''complete''''''
    Genome(){}

    // Here we define the getters for RNA and DNA threads
    string GetDNA(){
        return DNA[0];
    }

    string GetSDNA(){
        return DNA[1];
    }

    string GetRNA(){
        return RNA;
    }

    // A method that reverses the given string 
    string reverse(string s);

    // A method for creating the DNA threads out of an RNA thread
    void MakeDNAoutofRNA(string s);

    // A method for creating the supplement of the given string
    string Supplement(string s);

    // Here we define the methods neccessary for the different types of mutations
    // for the DNA mutations we have to apply the conditions to both of the DNA threads
    void SmallMutationRNA(char a, char b, int n);
    void SmallMutationDNA(char a, char b, int n);
    void BigMutationRNA(string s1, string s2);
    void BigMutationDNA(string s1, string s2);

    // In this section we define a funtion that replaces a substring in a string with it's reverse
    // using the reverse function we defined in the beginning of the program 
    void ReverseMutationRNA(string s1); 
    void ReverseMutationDNA(string s1);
};

class Cell : public Genome{
protected:
    int NumberOfChromozomes;
    vector <Genome> chromozomes;    

public:
    // The Constructor
    Cell(int number_of_chromozomes){
        this -> NumberOfChromozomes = number_of_chromozomes;

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

    // Here we define the getters
    int GetNumberOfChromozomes(){ 
        return NumberOfChromozomes; 
    }

    void GetChromozomes(){
        for (int i = 0; i < chromozomes.size(); i++){
            if ((i + 1) % 10 >= 4 || (i + 1) % 10 == 0)
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
    
    // A method for finding the supplementary palindrome substrings in a given string
    bool isSupplementaryPalindrome(string s);

    // A method for deleting Cell's object if cell were to die in the program
    void DeleteThis();

    // Cell Death method is based on the chromozome that is being tested
    void CellDeath(Cell* cell);

    // In this section we redefine DNA mutations
    void BigMutationDNA(string s1, int n, string s2, int m);
    void SmallMutationDNA(char a, char b, int n, int m);
    void ReverseMutationDNA(string s1, int n);

    void FindSupplementaryPalindromes(int n);
};

class Animal : public Cell{

private:

};

// Here are the methods of class Genome
string Genome::reverse(string s){
    string Reversed_s;
    
    // We simply start from the last element of the given string and proceed to the first element and
    // insert each element in an empty string
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
        // In this if statement we check the supplementary DNA thread as well because we search for the given 
        // character in both of the DNA threads in a parallel manner:
        // for example: DNA[0]:   (A)GCCG T
        //              DNA[1]:    T CGGC(A)
        // we found 2 'A's in the DNA threads 
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

/*void Genome::BigMutationRNA(string& s1, string& s2){
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
}*/

/*void Genome::BigMutationDNA(string s1, string s2){
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
}*/

void Genome::BigMutationRNA(string s1, string s2){
    int x = RNA.find(s1);

    RNA.erase(x, s1.length());
    RNA.insert(x, s2);
    
    cout << "The RNA thread after big mutation: " << RNA << endl;
}

void Genome::BigMutationDNA(string s1, string s2){
    string ss1 = Supplement(s1);
    string ss2 = Supplement(s2);

    int x1 = DNA[0].find(s1);
    int x2 = DNA[0].find(ss1);

    if(x1 < x2){
        DNA[0].erase(x1, s1.length());
        DNA[0].insert(x1, s2);
    }

    else{
        DNA[0].erase(x2, s1.length());
        DNA[0].insert(x2, ss2);
    }

    cout << "The DNA threads after big mutations: " <<  DNA[0] << '\t' << Supplement(DNA[0]) << endl;
}

void Genome::ReverseMutationRNA(string s1){
    string  Reversed_s = reverse(s1);
    
    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the given starting position 
    int x = RNA.find(s1);
    int y = s1.length();

    // Replaces y characters from xth index by Reversed_s
    RNA.replace(x, y, Reversed_s);

    cout << "The RNA thread after reverse mutation: "<< RNA << endl;

}

void Genome::ReverseMutationDNA(string s1){
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
bool Cell::isSupplementaryPalindrome(string s){
    int n = s.length();
    if(n > 3 && n % 2 == 0){
        for(int i = 0; i < n / 2 ; i++){
            if(s[i] == 'A' && s[n - i - 1] != 'T')
                return false;
        
            if(s[i] == 'T' && s[n - i - 1] != 'A')
                return false;
            
            if(s[i] == 'G' && s[n - i - 1] != 'C')
                return false;
            
            if(s[i] == 'C' && s[n- i - 1] != 'G')
                return false;
        }
    }

    else 
        return false;

    return true;
}

void Cell::DeleteThis(){
    delete this;
     cout << "The cell has died." << endl;
}

void Cell::CellDeath(Cell* cell){
    for (int i = 0; i < chromozomes.size(); i++){
        bool check = true;
        int count = 0, countAT = 0, countCG = 0;
        string s1 = chromozomes[i].GetDNA();
        string s2 = chromozomes[i].GetSDNA();

        if(check == true){
            for (int j = 0; j < chromozomes[i].GetDNA().length(); j++){
                if (s1[j] != Supplement(s2)[j])
                    count++;
            
                if (count > 5){
                    cout << "A broken chromozome has been detected!" << endl;
                    cout << "The broken chromozome is: " << endl;
                    cout << chromozomes[i].GetDNA() << '\t' << chromozomes[i].GetSDNA() << '\t' << chromozomes[i].GetRNA() << endl;
                    check = false;
                    break;
                }
            }
        }

        if(check == true){
            for (int k = 0; k < chromozomes[i].GetDNA().length(); k++){
            
                if (s1[k] == 'A' || s1[k] == 'T')
                    countAT++;

                if (s2[k] == 'A' || s2[k] == 'T')
                    countAT++;
            
                if (s1[k] == 'C' || s1[k] == 'G')
                    countCG++;

                if (s2[k] == 'C' || s2[k] == 'G')
                    countCG++;

                if(countAT > 3 * countCG && k == chromozomes[i].GetDNA().length() - 1){
                    cout << "A broken chromozome has been detected!" << endl;
                    cout << "The broken chromozome is: " << endl;
                    cout << chromozomes[i].GetDNA() << '\t' << chromozomes[i].GetSDNA() << '\t' << chromozomes[i].GetRNA() << endl;
                    check = false;
                    break;
                }
            }
        }

        if(check == false){
            delete this;
            cout << "The cell has died." << endl;
            break;
        }
    }
}

void Cell::SmallMutationDNA(char a, char b, int n, int m){
    // We have to minus integer m by 1 because the indexes in vectors start with 0
    // and we want to target the mth chromozome
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
    if(m % 10 >= 4 || m % 10 == 0)
        cout << "The " << m << "th chromozome's DNA threads after small mutation: " << endl << s1 << '\t' << Supplement(s1) << endl;
    else if(m % 10 == 3)
        cout << "The " << m << "rd chromozome's DNA threads after small mutation: " << endl << s1 << '\t' << Supplement(s1) << endl;
    else if(m % 10 == 2)
        cout << "The " << m << "nd chromozome's DNA threads after small mutation: " << endl << s1 << '\t' << Supplement(s1) << endl;
    else if(m % 10 == 1)
        cout << "The " << m << "st chromozome's DNA threads after small mutation: " << endl << s1 << '\t' << Supplement(s1) << endl;
}

void Cell::BigMutationDNA(string s1, int n, string s2, int m){
    string ch1 = chromozomes[n - 1].GetDNA();
    string ch2 = chromozomes[m - 1].GetDNA();
    string ss1 = Supplement(s1);
    string ss2 = Supplement(s2);

    int x1 = ch1.find(s1);
    int x11 = ch1.find(ss1);
    int x2 = ch2.find(s2);
    int x22 = ch2.find(ss2);

    if(x1 < x11 || x11 == -1){
        ch1.erase(x1, s1.length());
        ch1.insert(x1, s2);
    }

    else{
        ch1.erase(x11, s1.length());
        ch1.insert(x11, ss2);
    }


    if(x2 < x22 || x22 == -1){
        ch2.erase(x2, s2.length());
        ch2.insert(x2, s1);
    }

    else{
        ch2.erase(x22, s2.length());
        ch2.insert(x22, ss1);
    }

    cout << "The given chromozomes after big mutation: " << endl;
    cout << ch1 << '\t' << Supplement(ch1) << endl;
    cout << ch2 << '\t' << Supplement(ch2) << endl;
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

    if(n % 10 >= 4 || n % 10 == 0)
        cout << "The " << n << "th chromozome's DNA threads after reverse mutation: " << endl << s3 << '\t' << s4 << endl;
    else if(n % 10 == 3)
        cout << "The " << n << "rd chromozome's DNA threads after reverse mutation: " << endl  << s3 << '\t' << s4 << endl;
    else if(n % 10 == 2)
        cout << "The " << n << "nd chromozome's DNA threads after reverse mutation: " << endl << s3 << '\t' << s4 << endl;
    else if(n % 10 == 1)
        cout << "The " << n << "st chromozome's DNA threads after reverse mutation: " << endl << s3 << '\t' << s4 << endl;

}   

void Cell::FindSupplementaryPalindromes(int n){
    string s1 = chromozomes[n - 1].GetDNA();
    string s2 = chromozomes[n - 1].GetSDNA();

    string isSupplementaryPalindrome1 = "";
    if(n % 10 >= 4 || n % 10 == 0)
        cout << "The supplementary palindrome substrings in the" << n << "th chromozome: " << endl;
    else if (n % 10 == 3)
        cout << "The supplementary palindrome substrings in the" << n << "rd chromozome: " << endl;
    else if (n % 10 == 2)
        cout << "The supplementary palindrome substrings in the" << n << "nd chromozome: " << endl;
    else if (n % 10 == 1)
        cout << "The supplementary palindrome substrings in the" << n << "st chromozome: " << endl;

    for (int i = 0; i < s1.length(); i++){
        for (int j = i + 2; j <= s1.length(); j++){
            string substring = s1.substr(i, j - i);
            if (isSupplementaryPalindrome(substring)){
                isSupplementaryPalindrome1 = substring;
                cout << isSupplementaryPalindrome1 << '\t';
            }       
        }
    }
} 

int main(){
    Genome genome ("AAGTCTCAGT", "TTCAGAGTCA", "TTCAGAGTCA");
    genome.BigMutationRNA("TCAG", "ATC");

}

// REmider: in the menu we could possibly give an address instead of a string 
// You should initialize the constructor in this order : 1.DNA's main thread 2.DNA's supplemetary thread 3.RNA