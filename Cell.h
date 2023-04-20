#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string reverse(string s){
    int len = s.length();
    int n = len-1;
    int i = 0;

    while(i <= n){
        // Using the swap method to switch values at each index
        // For instance: indexes --> 0 and len - 1 / 1 and len - 2  and so on
        swap(s[i],s[n]);
        n = n-1;
        i = i+1;
    }

    return s;
}

// A boolean function that returns true when s1 is a substring of s2
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

// Fills Z array for given string str[]
// The reason that we break out of the for loop the moment that Z[i] == check
// is that we only aim to find the index of the first time the text occurs in the pattern 
// (the given substring occurs in the string)
void getZarr(string str, int Z[]){
	int n = str.length();
	int L, R, k;
    int check;

    // Finds the length of the pattern
    for (int i = 0; i < n; i++){
        if (str[i] == '$')
            check = i;
    }

	// [L,R] make a window which matches with prefix of s
    // It is apparent that L stands for left and R stands for R

	L = R = 0;

	for (int i = 1; i < n; ++i){
		// if i > R nothing matches so we calculate Z[i] using naive way
		if (i > R){
			L = R = i;

			// R-L = 0 in the start, so it starts
			// checking from the 0th index 
            
            // if str[R - L] == str[R] it means the values are equeal so we proceed and check the next index
            // For example: a b a x a b a b
            // Z values   : X 0 1 0 2 0 2 0
            
			while (R < n && str[R - L] == str[R])
				R++;

			Z[i] = R - L;
			R--;
		}
 
		else{
			// k = i-L so k corresponds to number which
			// matches in [L,R] interval.
			k = i - L;

			// if Z[k] is less than remaining interval then Z[i] will be equal to Z[k]
            // which means if the value doesn't go beyond R (right bound) we can just
            // copy the values

			if (Z[k] < R - i + 1)
				Z[i] = Z[k];

			else{
				// Otherwise the program tries to see if there are more matches
                L = i;
				while (R < n && str[R - L] == str[R])
					R++;

				Z[i] = R - L;
                R--;
			}
		}

        // If the value of Z[i] == check breaks out of the loop
        // check == pattern.length()
        if (Z[i] == check){
            break;
        }
	}
}

// Returns the index of the first occurrence of pattern in the given text using Z algorithm
int Zsearch(string text, string pattern){
	// Create concatenated string "P$T"
    // For this string we could use any alternative character instead of '$' only with the
    // condition that the character is not in neither of the pattern and text string
	string concat = pattern + "$" + text;
	int l = concat.length();

	// Construct Z array
	int Z[l];
	getZarr(concat, Z);

	// we loop through Z array for finding a matching condition
	for (int i = 0; i < l; ++i){

		// If Z[i] (matched region) value is equal to pattern length we got the pattern
		if (Z[i] == pattern.length()){
		    return (i - pattern.length() - 1);
        }
	}

    return -1;
}

class Genome {
protected:
    string RNA;
    string DNA[2];

public:
    // The main constructor
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

    // An empty constructor
    Genome(){}

    // A constructor that we use in Class Virus
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

    // A method for creating the DNA threads out of an RNA thread
    void MakeDNAoutofRNA();

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
    // An empty constructor
    Cell(){};

    // The main Constructor
    Cell(int number_of_chromozomes){
        NumberOfChromozomes = number_of_chromozomes;

        // Initilizing the  given cell's chromozomes
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

            // Each chromozome is an object of Genome (is a variable of type Genome)
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

    // destroys the given cell if it has a broken chromozome
    void CellDeath();

    // In this section we redefine DNA mutations
    void BigMutationDNA(string s1, int n, string s2, int m);
    void SmallMutationDNA(char a, char b, int n, int m);
    void ReverseMutationDNA(string s1, int n);

    // A method for finding supplementary palindormes in the given chromozome
    void FindSupplementaryPalindromes(int n);
    
};

// Here are the methods of class Genome

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

void Genome::MakeDNAoutofRNA(){
    string s = GetRNA();
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
    int i = 0, j = 0;

    while (i < n){
        if (RNA[j] == a){
            RNA[j] = b;
            i++;
            j++;
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
        
            if(i == n)
                break;
        }

        else 
            j++;
    }

    cout << "The DNA threads after small mutations: " << DNA[0] << '\t' << DNA[1] << endl;
}

void Genome::BigMutationRNA(string s1, string s2){
    // Returns the index of the first occurrence of the given string in RNA
    int x = Zsearch(RNA, s1);
    // Deletes s1.length() characters from xth index of RNA
    RNA.erase(x, s1.length());
    // Inserts s2 in RNA starting from xth index of RNA
    RNA.insert(x, s2);
    
    cout << "The RNA thread after big mutation: " << RNA << endl;
}

void Genome::BigMutationDNA(string s1, string s2){
    string Supplement_s1 = Supplement(s1);
    string Supplement_s2 = Supplement(s2);

    // Returns the index of the first occurrence of s1 in DNA[0] and DNA[1]
    int x1 = Zsearch(DNA[0], s1);
    int x2 = Zsearch(DNA[1], s1);

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
    string Reversed_s = reverse(s1);
    
    // Returns the index of the first occurrence of s1 in RNA
    int x = Zsearch(RNA, s1);
    int y = s1.length();

    if (x == string::npos)
        cout << "The given substring does not exist in the given RNA thread, thus the opertation is not possible" << endl;
    

    else{
        // Replaces y characters from xth index by Reversed_s
        RNA.replace(x, y, Reversed_s);
        cout << "The RNA thread after reverse mutation: "<< RNA << endl;
    }

}

void Genome::ReverseMutationDNA(string s1){
    string Reversed_s1 = reverse(s1);
    string Reversed_supplement_s1 = reverse(Supplement(s1));
    string Supplement_s1 = Supplement(s1);
    
    // Returns the index of the first occurrence of s1 in DNA[0] and DNA[1]
    int y = s1.length();
    int x1 = Zsearch(DNA[0], s1);
    int x2 = Zsearch(DNA[1], s1);
    
    if((x1 < x2 || x2 == string::npos) && x1 != string::npos){
        // Replaces y characters from x1th index by Reversed_s1
        DNA[0].replace(x1, y, Reversed_s1);

        // Replaces y characters from x1th index by Reversed_supplement_s1
        DNA[1].replace(x1, y, Reversed_supplement_s1);
    }

    else if((x2 < x1 || x1 == string::npos) && x2 != string::npos){
        // Replaces y characters from x2th index by Reversed_supplement_s1
        DNA[0].replace(x2, y, Reversed_supplement_s1);

        // Replaces y characters from x2th index by Reversed_s1
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
        // We define a boolean so that we don't check whether the given cell has the second 
        // condition of celldeath as well if it were to meet the first condition
        bool check = true;
        int count = 0, countAT = 0, countCG = 0;
        string s1 = chromozomes[i].GetDNA();
        string s2 = chromozomes[i].GetSDNA();

        // The first conditon of celldeath method
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

        // The second condition of celldeath method
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
            // Deletes the given cell
            delete this;
            NumberOfChromozomes = 0;
            cout << "The cell has died." << endl;
            break;
        }
    }
    cout << "The cell didn't die." << endl;
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
    string ch1 = chromozomes[n - 1].GetDNA();
    string ch11 = chromozomes[n - 1].GetSDNA();
    string ch2 = chromozomes[m - 1].GetDNA();
    string ch22 = chromozomes[m - 1].GetSDNA();
    string Supplement_s1 = Supplement(s1);
    string Supplement_s2 = Supplement(s2);

    int x1 = Zsearch(ch1, s1);
    int x11 = Zsearch(ch11, s1);
    int x2 = Zsearch(ch2, s2);
    int x22 = Zsearch(ch22, s2);

    if((x1 < x11 || x11 == string::npos) && x1 != string::npos){
        // Deletes s1.length() characters from x1th index of ch1
        ch1.erase(x1, s1.length());
        // Inserts s2 in ch1 starting from x1th index of ch1
        ch1.insert(x1, s2);
        
        // Deletes s1.length() characters from x1th index of ch11   
        ch11.erase(x1, s1.length());
        // Inserts Supplement_2 in ch11 starting from x1th index of ch11
        ch11.insert(x1, Supplement_s2);
    }

    else if ((x11 < x1 || x1 == string::npos) && x11 != string::npos){
        // Deletes s1.length() characters from x11th index of ch1
        ch1.erase(x11, s1.length());
        // Inserts Supplement_s2 in x11 starting from x11th index of ch1
        ch1.insert(x11, Supplement_s2);

        // Deletes s1.length() characters from x11th index of ch11
        ch11.erase(x11, s1.length());
        // Inserts s2 in ch11 starting from x11th index of ch11
        ch11.insert(x11, s2);
    }


    if((x2 < x22 || x22 == string::npos) && x2 != string::npos){
        // Deletes s2.length() characters from x2th index of ch2
        ch2.erase(x2, s2.length());
        // Inserts s2 in ch2 starting from x2th index of ch2
        ch2.insert(x2, s1);

        // Deletes s2.length() characters from x2th index of ch22
        ch22.erase(x2, s2.length());
        // Inserts Supplement_s2 in ch22 starting from x2th index of ch22
        ch22.insert(x2, Supplement_s1);
    }

    else if ((x22 < x2 || x22 == string::npos) && x22 != string::npos){
        // Deletes s2.length() characters from x22th index of ch2
        ch2.erase(x22, s2.length());
        // Inserts Supplement_s1 in ch2 starting from x22th index of ch2
        ch2.insert(x22, Supplement_s1);

        // Deletes s2.length() characters from x22th index of ch22
        ch22.erase(x22, s2.length());
        // Inserts s1 in ch22 starting from x22th index of ch22
        ch22.insert(x22, s1);
    }

    else
        cout << "This operation is not possible." << endl;

    // Here we set the DNA threads of the given chromozomes
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
    string ch1 = chromozomes[n - 1].GetDNA();
    string ch11 = chromozomes[n - 1].GetSDNA();
    string Reversed_s1 = reverse(s1);
    string Reversed_Supplement_s1 = reverse(Supplement(s1));
    string Supplement_s1 = Supplement(s1);

    // Returns the index of the first occurrence of s1 in ch1 and ch11
    int y = s1.length();
    int x1 = Zsearch(ch1, s1);
    int x2 = Zsearch(ch11, s1);

    if((x1 < x2 || x2 == string::npos) && x1 != string::npos){
        // Replaces y characters from x1th index by Reversed_s1
        ch1.replace(x1, y, Reversed_s1);

        // Replaces y characters from x1th index by Reversed_Supplement_s1
        ch11.replace(x1, y ,Reversed_Supplement_s1);
    }

    else if((x2 < x1 || x1 == string::npos) && x2 != string::npos){
        // Replaces y characters from x2th index by Reversed_Supplement_s1
        ch1.replace(x2, y, Reversed_Supplement_s1);
        
        // Replaces y characters from x2th index by Reversed_s1
        ch11.replace(x2, y, Reversed_s1);
    }

    else
        cout << "This operation is not possbile." << endl;


    // Here we set the DNA threads of the given chromozome
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
        cout << "The supplementary palindrome substrings in the " << n << "th chromozome: " << endl;
    else if (n % 10 == 3)
        cout << "The supplementary palindrome substrings in the " << n << "rd chromozome: " << endl;
    else if (n % 10 == 2)
        cout << "The supplementary palindrome substrings in the " << n << "nd chromozome: " << endl;
    else if (n % 10 == 1)
        cout << "The supplementary palindrome substrings in the " << n << "st chromozome: " << endl;

    for (int i = 0; i < s1.length(); i++){
        for (int j = i + 2; j <= s1.length(); j++){
            string substring = s1.substr(i, j - i);
            // Checks if the given substring is supplementary palindorme
            if (isSupplementaryPalindrome(substring)){
                isSupplementaryPalindrome1 = substring;

                // prints the given substring
                cout << isSupplementaryPalindrome1 << '\t';
            }       
        }
    }
} 
