#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>


using namespace std;

const int MATCH_SCORE = 1; 
const int MISMATCH_SCORE = 0; 
const int GAP_SCORE = 0; 

bool isSubstring(string s1, string s2){
    int m = s1.length();
    int n = s2.length();
 
    // A loop to slide pat[] one by one
    for (int i = 0; i <= n - m; i++){
        int j;
 
        // For the ith index we check whether string s1 matches a subtring of string s1
        for (j = 0; j < m; j++)
            if (s2[i + j] != s1[j])
                break;
 
        if (j == m)
            return true;
    }
 
    return false;
}

class Genome {
protected:
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

    Genome(string rna){
        RNA = rna;
    }

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

    friend class Cell;
};

class Cell : public Genome{
protected:
    int NumberOfChromozomes;
    vector <Genome> chromozomes;    

public:
    Cell(){};

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
    void CellDeath();

    // In this section we redefine DNA mutations
    void BigMutationDNA(string s1, int n, string s2, int m);
    void SmallMutationDNA(char a, char b, int n, int m);
    void ReverseMutationDNA(string s1, int n);
    void FindSupplementaryPalindromes(int n);

};

class Animal : public Cell{
private:
    // A function which we use in the needleman_wunsch_score function in order to
    // calculate the total score using MATCH_SCORE and MISMATCH_SCORE
    int score(char a, char b);

    // Returns the global alignment score of two sequences using the Needleman-Wunsch algorithm 
    int needleman_wunsch_score(string x, string y);

    // Returns the percent similarity between two sequences
    double percent_similarity(string x, string y);

public:
    // Constructor
    Animal(int number_of_chromozomes) : Cell(number_of_chromozomes){}

    // In this method we check the similarity percentage of the two given animals' chromozomes
    double Similarity(Animal animal);

    // Redifinition of the == operator
    bool operator== (Animal animal);
    Animal AsexualReproduction();
    void AsexualReproductionDisplay();
    void operator+ (Animal animal2);

    void AnimalDeath();
    friend class Virus;
};

class Virus : public Genome{
public:
    // The constructor
    Virus(string rna) : Genome(rna){}

    // A boolean function that returns true when the virus is harmful
    bool isVirusHarmful(Animal animal);

    // A method with which we find the longest common substring (LCS) of all the 
    // given animal's chromozomes
    string findstem(vector <Genome> arr);

    // A boolean function that returns true when s1 is a substring of s2
    //bool isSubstring(string s1, string s2);

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
    while (i < n){
        if (DNA[0][j] == a){
            DNA[0][j] = b;

            if(b == 'G')
                DNA[1][j] = 'C';

            else if (b == 'C')
                DNA[1][j] = 'G';
            
            else if (b == 'T')
                DNA[1][j] = 'A';
            
            else if (b == 'A')
                DNA[1][j] = 'T';

            i++;
            j++;
        }

        // In this if statement we check the supplementary DNA thread as well because we search for the given 
        // character in both of the DNA threads in a parallel manner:
        // for example: DNA[0]:   (A)GCCG T
        //              DNA[1]:    T CGGC(A)
        // we found 2 'A's in the DNA threads 

        else if (DNA[1][j] == a){
            DNA[1][j] = b;
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
        }
        else 
            j++;
    }

    cout << "The DNA threads after small mutations: " << DNA[0] << '\t' << DNA[1] << endl;
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
    string Supplement_s1 = Supplement(s1);
    string Supplement_s2 = Supplement(s2);

    int x1 = DNA[0].find(s1);
    int x2 = DNA[1].find(s1);

    if((x1 < x2 || x2 == string::npos) && x1 != string::npos){
        // Deletes s1.length() characters from x1th index of DNA[0]
        DNA[0].erase(x1, s1.length());
        // Inserts s2 in DNA[0] starting from x1th index of DNA[0]
        DNA[0].insert(x1, s2);

        // Deletes s1.length() characters from x1th index of DNA[1]
        DNA[1].erase(x1, s1.length());
        // Inserts Supplement_s2 in DNA[1] starting from x1th index of DNA[1]
        DNA[1].insert(x1, Supplement_s2);
    }

    else if((x2 < x1 || x1 == string::npos) && x2 != string::npos){
        // Deletes s1.length() characters from x2th index of DNA[0]
        DNA[0].erase(x2, s1.length());
        // Inserts Supplement_s2 in DNA[0] starting from x2th index of DNA[0]
        DNA[0].insert(x2, Supplement_s2);

        // Deletes s1.length() characters from x2th index of DNA[1]
        DNA[1].erase(x2, s1.length());
        // Inserts s2 in DNA[1] starting from x2th index of DNA[1]
        DNA[1].insert(x2, s2);
       
    }

    else
        cout << "This operation is not possible." << endl;

    cout << "The DNA threads after big mutations: " <<  DNA[0] << '\t' << DNA[1] << endl;
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
    string Supplement_s1 = Supplement(s1);
    
    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the given starting position 
    int y = s1.length();
    int x1 = DNA[0].find(s1);
    int x2 = DNA[1].find(s1);
    
    if((x1 < x2 || x2 == string::npos) && x1 != string::npos){
        // Replaces y characters from xth index by Reversed_s
        DNA[0].replace(x1, y, Reversed_s1);

        // Replaces y characters from xth index by Reversed_supplement_s
        DNA[1].replace(x1, y, Reversed_supplement_s1);
    }

    else if((x2 < x1 || x1 == string::npos) && x2 != string::npos){

        DNA[0].replace(x2, y, Reversed_supplement_s1);

        DNA[1].replace(x2, y, Reversed_s1);
    }

    else
        cout << "This operation is not possible." << endl;

    cout << "The DNA threads after reverse mutation: " << DNA[0] << '\t' << DNA[1] << endl;

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

void Cell::CellDeath(){
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
            //chromozomes.clear();
            //delete &chromozomes;
            //delete &NumberOfChromozomes;
            delete this;
            cout << "The cell has died." << endl;
            break;
        }
    }
}

void Cell::SmallMutationDNA(char a, char b, int n, int m){
    // We have to minus integer m by 1 because the indexes in vectors start with 0
    // and we want to target the mth chromozome
    int i = 0, j = 0;
    while (i < n){
        if (chromozomes[m - 1].DNA[0][j] == a){
            chromozomes[m - 1].DNA[0][j] = b;

            if(b == 'G')
                chromozomes[m - 1].DNA[1][j] = 'C';

            else if (b == 'C')
                chromozomes[m - 1].DNA[1][j] = 'G';
            
            else if (b == 'T')
                chromozomes[m - 1].DNA[1][j] = 'A';
            
            else if (b == 'A')
                chromozomes[m - 1].DNA[1][j] = 'T';

            i++;
            j++;
        }

        // In this if statement we check the supplementary DNA thread as well because we search for the given 
        // character in both of the DNA threads in a parallel manner:
        // for example: DNA[0]:   (A)GCCG T
        //              DNA[1]:    T CGGC(A)
        // we found 2 'A's in the DNA threads 

        else if (chromozomes[m - 1].DNA[1][j] == a){
            chromozomes[m - 1].DNA[1][j] = b;
            if(b == 'G')
                chromozomes[m - 1].DNA[0][j] = 'C';

            else if (b == 'C')
                chromozomes[m - 1].DNA[0][j] = 'G';
            
            else if (b == 'T')
                chromozomes[m - 1].DNA[0][j] = 'A';
            
            else if (b == 'A')
                chromozomes[m - 1].DNA[0][j] = 'T';
            i++;
            j++;
        
        }
        else 
            j++;
    }

    if(m % 10 >= 4 || m % 10 == 0)
        cout << "The " << m << "th chromozome's DNA threads after small mutation: " << endl << chromozomes[m - 1].DNA[0] << '\t' << chromozomes[m - 1].DNA[1] << endl;
    else if(m % 10 == 3)
        cout << "The " << m << "rd chromozome's DNA threads after small mutation: " << endl << chromozomes[m - 1].DNA[0] << '\t' << chromozomes[m - 1].DNA[1] << endl;
    else if(m % 10 == 2)
        cout << "The " << m << "nd chromozome's DNA threads after small mutation: " << endl << chromozomes[m - 1].DNA[0] << '\t' << chromozomes[m - 1].DNA[1] << endl;
    else if(m % 10 == 1)
        cout << "The " << m << "st chromozome's DNA threads after small mutation: " << endl << chromozomes[m - 1].DNA[0] << '\t' << chromozomes[m - 1].DNA[1] << endl;
}

void Cell::BigMutationDNA(string s1, int n, string s2, int m){
    string ch1 = chromozomes[n - 1].DNA[0];
    string ch11 = chromozomes[n - 1].DNA[1];
    string ch2 = chromozomes[m - 1].DNA[0];
    string ch22 = chromozomes[m - 1].DNA[1];
    string Supplement_s1 = Supplement(s1);
    string Supplement_s2 = Supplement(s2);

    int x1 = ch1.find(s1);
    int x11 = ch11.find(s1);
    int x2 = ch2.find(s2);
    int x22 = ch22.find(s2);

    if((x1 < x11 || x11 == string::npos) && x1 != string::npos){
        ch1.erase(x1, s1.length());
        ch1.insert(x1, s2);

        ch11.erase(x1, s1.length());
        ch11.insert(x1, Supplement_s2);
    }

    else if ((x11 < x1 || x1 == string::npos) && x11 != string::npos){
        ch1.erase(x11, s1.length());
        ch1.insert(x11, Supplement_s2);

        ch11.erase(x11, s1.length());
        ch11.insert(x11, s2);
    }


    if((x2 < x22 || x22 == string::npos) && x2 != string::npos){
        ch2.erase(x2, s2.length());
        ch2.insert(x2, s1);

        ch22.erase(x2, s2.length());
        ch22.insert(x2, Supplement_s1);
    }

    else if ((x22 < x2 || x22 == string::npos) && x22 != string::npos){
        ch2.erase(x22, s2.length());
        ch2.insert(x22, Supplement_s1);

        ch22.erase(x22, s2.length());
        ch22.insert(x22, s1);
    }

    else
        cout << "This operation is not possible." << endl;

    chromozomes[n - 1].DNA[0] = ch1;
    chromozomes[n - 1].DNA[1] = ch11;
    chromozomes[m - 1].DNA[0] = ch2;
    chromozomes[m - 1].DNA[1] = ch22;
    cout << "The given chromozomes after big mutation: " << endl;
    cout << "The first given chromozome: " << chromozomes[n - 1].DNA[0] << '\t' << chromozomes[n - 1].DNA[1] << endl;
    cout << "The second given chromozome: " << chromozomes[m - 1].DNA[0] << '\t' << chromozomes[m - 1].DNA[1] << endl;
}

void Cell::ReverseMutationDNA(string s1, int n){
    // We have to minus integer n by 1 because the indexes in vectors start with 0
    // and we want to target the nth chromozome
    string ch1 = chromozomes[n - 1].DNA[0];
    string ch11 = chromozomes[n - 1].DNA[1];
    string Reversed_s1 = reverse(s1);
    string Reversed_Supplement_s1 = reverse(Supplement(s1));
    string Supplement_s1 = Supplement(s1);

    int y = s1.length();
    int x1 = ch1.find(s1);
    int x2 = ch11.find(s1);

    if((x1 < x2 || x2 == string::npos) && x1 != string::npos){
        ch1.replace(x1, y, Reversed_s1);
        ch11.replace(x1, y ,Reversed_Supplement_s1);
    }

    else if((x2 < x1 || x1 == string::npos) && x2 != string::npos){
        ch1.replace(x2, y, Reversed_Supplement_s1);
        ch11.replace(x2, y, Reversed_s1);
    }

    else
        cout << "This operation is not possbile." << endl;

    chromozomes[n - 1].DNA[0] = ch1;
    chromozomes[n - 1].DNA[1] = ch11;

    if(n % 10 >= 4 || n % 10 == 0)
        cout << "The " << n << "th chromozome's DNA threads after reverse mutation: " << endl << chromozomes[n - 1].DNA[0] << '\t' << chromozomes[n - 1].DNA[1] << endl;
    else if(n % 10 == 3)
        cout << "The " << n << "rd chromozome's DNA threads after reverse mutation: " << endl  << chromozomes[n - 1].DNA[0] << '\t' << chromozomes[n - 1].DNA[1] << endl;
    else if(n % 10 == 2)
        cout << "The " << n << "nd chromozome's DNA threads after reverse mutation: " << endl << chromozomes[n - 1].DNA[0] << '\t' << chromozomes[n - 1].DNA[1] << endl;
    else if(n % 10 == 1)
        cout << "The " << n << "st chromozome's DNA threads after reverse mutation: " << endl << chromozomes[n - 1].DNA[0] << '\t' << chromozomes[n - 1].DNA[1] << endl;

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

// Here are the methods of class Animal

int Animal::score(char a, char b){ 
    if (a == b)
        return MATCH_SCORE; 
	else
        return MISMATCH_SCORE; 
}

int Animal::needleman_wunsch_score(string x, string y){
    int n = x.length(); // length of the given string x
    int m = y.length(); // length of the given string y

	int dp[n + m + 1][n + m + 1];

	// Table for storing optimal substructure answers
    for (int i = 0; i < n + m + 1; i++){
        for (int j = 0; j < n + m + 1; j++){
            dp[i][j] = 0;
        }
    }

    // Initilizing the table (dp)
	for (int i = 0; i <= n; i++){ 
        dp[i][0] = i * GAP_SCORE; 
    } 

    for (int j = 0; j <= m; j++){ 
        dp[0][j] = j * GAP_SCORE; 
    }

    // Filling the table (dp)
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
			int match_score = score(x[i - 1], y[j - 1]) + dp[i - 1][j - 1]; 
            int gap_x_score = GAP_SCORE + dp[i - 1][j]; 
            int gap_y_score = GAP_SCORE + dp[i][j - 1]; 
            dp[i][j] = max(match_score, max(gap_x_score, gap_y_score)); 
        }
    }

	return dp[n][m];
}

double Animal::percent_similarity(string x, string y) { 
    int alignment_score = needleman_wunsch_score(x, y); 
    double similarity = static_cast<double>(alignment_score) / max(x.length(), y.length()) * MATCH_SCORE;
    return similarity; 
} 

double Animal::Similarity(Animal animal){
    double SimilarityPercentageTotal = 0;
    
    for (int i = 0; i < NumberOfChromozomes; i++){
        double temp1 = 0;
        double temp2 = 0;
        double SimilarityPercentage1 = 0;
        double SimilarityPercentage2 = 0;
        for(int j = 0; j < animal.GetNumberOfChromozomes(); j++){
            temp1 = percent_similarity(chromozomes[i].GetDNA(), animal.chromozomes[j].GetDNA());
            temp2 = percent_similarity(chromozomes[i].GetSDNA(), animal.chromozomes[j].GetSDNA());
            if(SimilarityPercentage1 < ((temp1 + temp2) / 2))
                SimilarityPercentage1 = ((temp1 + temp2) / 2);
        }

    SimilarityPercentageTotal += SimilarityPercentage1;
    }

    SimilarityPercentageTotal /= NumberOfChromozomes;

    return SimilarityPercentageTotal;
}

bool Animal::operator== (Animal animal){
    if (Similarity(animal) > 0.7 && (NumberOfChromozomes == animal.GetNumberOfChromozomes()))
        return true;
    
    else 
        return false;
}

Animal Animal::AsexualReproduction(){
    Animal animal2(0);
    vector <int> RandIndex1;
    vector <int> RandIndex2;
    random_device device;
    mt19937 gen(device());
    

    for (int i = 0; i < (ceil) (0.7 * NumberOfChromozomes); i++)
        RandIndex1.push_back(i);
    
    for (int i = 0; i < 2 * NumberOfChromozomes; i++)
        RandIndex2.push_back(i);

    shuffle(RandIndex1.begin(), RandIndex1.end(), gen);
    shuffle(RandIndex2.begin(), RandIndex2.end(), gen);

    for (int i = 0; i < (ceil) (0.7 * NumberOfChromozomes); i++)
        animal2.chromozomes.push_back(chromozomes[RandIndex1[i]]);
    

    for (int i = 0; i < NumberOfChromozomes; i++)
        chromozomes.push_back(chromozomes[i]);

    for (int i = 0; i < (NumberOfChromozomes - (ceil) (0.7 * NumberOfChromozomes)); i++)
        animal2.chromozomes.push_back(chromozomes[RandIndex2[i]]); 
    
    
    animal2.NumberOfChromozomes = NumberOfChromozomes;
    
    for(int i = 0; i < NumberOfChromozomes; i++)
        chromozomes.pop_back();

    return animal2;
}

void Animal::AsexualReproductionDisplay(){
    cout << "The Asexually reporoduced animal's chromozomes are: " << endl;
    AsexualReproduction().GetChromozomes();
}

void Animal::AnimalDeath(){
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
                    chromozomes.erase(chromozomes.begin() + i);
                    i--;
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
                    chromozomes.erase(chromozomes.begin() + i);
                    i--;
                    check = false;
                    break;
                }
            }
        }
    }
}

void Animal::operator+ (Animal animal){
    Animal animal3(0);
    Animal animal1 = AsexualReproduction();
    Animal animal2 = animal.AsexualReproduction();
    
    if(animal1 == animal2 && animal1.GetNumberOfChromozomes() % 2 == 0){
        vector <int> RandIndex1;
        vector <int> RandIndex2;
        random_device device;
        mt19937 gen(device());

        for (int i = 0; i < animal1.GetNumberOfChromozomes(); i++){
            RandIndex1.push_back(i);            
            RandIndex2.push_back(i);
        }

        while(!(animal3 == animal2 && animal3 == animal1)){
            shuffle(RandIndex1.begin(), RandIndex1.end(), gen);
            shuffle(RandIndex2.begin(), RandIndex2.end(), gen);

            animal3.chromozomes.clear();
            animal3.NumberOfChromozomes = animal1.NumberOfChromozomes;

            for(int i = 0; i < (animal1.GetNumberOfChromozomes() / 2); i++){
                animal3.chromozomes.push_back(chromozomes[RandIndex1[i]]);
                animal3.chromozomes.push_back(animal2.chromozomes[RandIndex2[i]]);
            }
        }
    cout << "check" << endl;
    animal.GetChromozomes();
    cout << "mate" << endl;

    cout << "The sexually reproduced animal from the two given animals is: " << endl;
    animal3.GetChromozomes();
    }

    else if (NumberOfChromozomes % 2 != 0 || animal2.GetNumberOfChromozomes() % 2 != 0)
        cout << "The asexually reproduced animals cells' do not have even number of chromozomes.";

    else
        cout << "The asexually reproduced animals are not of the same type." << endl;
}

// Here are the methods of class Virus

string Virus::findstem(vector <Genome> arr){
	// Determine size of the array
	int n = arr.size();

	// Take first word from array as reference
	string s = arr[0].GetDNA();
	int len = s.length();

	string res = "";

	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j <= len; j++) {
			// generating all possible substrings
			// of our reference string arr[0] i.e s
			string stem = s.substr(i, j);
			int k = 1;
			for (k = 1; k < n; k++) {
				// Check if the generated stem is
				// common to all words
				if (arr[k].GetDNA().find(stem) == std::string::npos)
					break;
			}

			// If current substring is present in
			// all strings and its length is greater
			// than current result
			if (k == n && res.length() < stem.length())
				res = stem;
		}
	}

	return res;
}

/*bool Virus::isSubstring(string s1, string s2){
    int m = s1.length();
    int n = s2.length();
 
    // A loop to slide pat[] one by one
    for (int i = 0; i <= n - m; i++){
        int j;
 
        // For the ith index we check whether string s1 matches a subtring of string s1
        for (j = 0; j < m; j++)
            if (s2[i + j] != s1[j])
                break;
 
        if (j == m)
            return true;
    }
 
    return false;
}*/

bool Virus::isVirusHarmful(Animal animal){
    vector <Genome> DNA;
    for (int i = 0; i < animal.chromozomes.size(); i++)
        DNA.push_back(animal.chromozomes[i]);

    if (isSubstring(findstem(DNA), GetRNA()) == true)
        return true;

    else if (isSubstring(Supplement(findstem(DNA)), GetRNA()) == true)
        return true;
    
    else 
        return false;

}

int main(){
    Animal animal1(2);
    Animal animal2(2);

    //animal1.AsexualReproduction();
    //animal2.AsexualReproduction();
    cout << "check2" << endl;
    animal1.GetChromozomes();
    cout << "mate2" << endl;

    animal1.AsexualReproduction();

    cout << endl;

    cout << "check3" <<endl;

    animal1.GetChromozomes();

    cout << "mate3" << endl;



}

//#include <iostream>
//Cell* cell = new Cell(1);
//cell->CellDeath();

// REmider: in the menu we could possibly give an address instead of a string 
