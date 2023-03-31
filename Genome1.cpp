#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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
    // Constructor
    Genome(string _DNA, string _RNA): DNA(_DNA) , RNA(_RNA){}

    // Here we define the setters and getters for DNA and RNA
    /*void SetRNA(string s){
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
    } */

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
    int number_of_chromozoms;
    vector <string> chromozoms;

    // Here we define a function type boolean which will be used later on in the program
    bool isPalindrome(string s){
        int n = s.length();
        for(int i = 0; i < n / 2 ; i++){
            if(s[i] != s[n - i - 1])
                return false;
        }
        return true;
    }

public:

    void SetNumberOfChromozoms(int n){
        number_of_chromozoms = n; 
    }

    int GetNumberOfChromozoms(){ 
        return number_of_chromozoms; 
    }

    void SetChromozom(string arr[]){
        for (int i = 0; i < number_of_chromozoms; ++i)
            chromozoms.push_back(arr[i]);
    }

    void GetChromozom(){
        for (int i = 0; i < number_of_chromozoms; ++i)
            cout << chromozoms[i] << '\t' << endl;
    }

    // Cell Death function is based on the chromozom that is being tested
    void CellDeath(int n1);

    // In this section we redefine DNA mutations
    void BigMutationDNA(string ss1, int nn, string ss2, int mm);
    void SmallMutationDNA(char a, char b, int n, int m);
    void reverseSubstring(string substring, int n);
    void findLongestPalindrome(int n);
};

// Here are the methods of class Genome
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

    cout << "The DNA threads after small mutations: " << DNA << '\t' << Supplement(DNA) << endl;
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
        cout << "The DNA threads after big mutations: " <<  ans << '\t' << Supplement(ans) << endl;
    
    else
        cout << "The DNA threads after big mutations: " << anss << '\t' << Supplement(anss) << endl;
}

void Genome::ReverseMutationRNA(string& s1){
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
    // the substring in the string from the given starting position 
    int x = RNA.find(s1);
    int y = s1.length();

    // Replaces y characters from xth index by Reversed_s
    RNA.replace(x, y, Reversed_s);

    cout << "The RNA thread after reverse mutation: "<< RNA << endl;

}

void Genome::ReverseMutationDNA(string& s1){
    string Reversed_s = reverse(s1);
    string Reversed_supplement_s = reverse(Supplement(s1));

    // In this section we use the find funtion which will return the index of the first occurance of 
    // the substring in the string from the given starting position 
    int y = s1.length();
    int x = DNA.find(s1);

    // Replaces y characters from xth index by Reversed_s
    DNA.replace(x, y, Reversed_s);

    // Replaces y characters from xth index by Reversed_supplement_s
    Supplement(DNA).replace(x, y, Reversed_supplement_s);

    cout << "The DNA threads after reverse mutation: " << DNA << '\t' << Supplement(DNA) << endl;
}

// Here are the methods of class Cell
void Cell::CellDeath(int n1){
    string m = chromozoms[n1];
        int n2 = m.length() - 5;

        for (int i = 0; i < n2; ++i){
            for (int j = i; j < i + 5; ++j){
                int pos1 = 0, pos2 = 0;
                string r = m.substr(i, 5);
                size_t found1 = r.find("AT");
                size_t found2 = r.find("CG");

                if (found1 != string::npos)
                    pos1 += 1;

                else if (found2 != string::npos)
                    pos2 += 1;

                if (pos1 + pos2 == 0){
                    chromozoms[n1] = '0';
                    break;
                }
            }
        }

        //اینجا میاد تو دوتا حلقه تو در تو 5 تا 5 تا نگاه میکنه که ایا اون دوتا پیوند تو اون تقسیم بندیه هست یا نه اگه هیچ کدوم نبود
        // که در این صورت جمعشون برابر با صفر میشه و میاد یریک میکنه و اون دی ان ای رو برابر با صفر میذاره
        //  صفر میذاره چون اگه از دستور ایریس یا پاک کردن برای وکتور ها استفاده میکرد تعداد کروموزوم ها تغییر میکرد
        // count AT in dna
        int count = 0;
        for (int i = 0; i < m.length() - 1; i++){
            if (m.substr(i, 2) == "AT")
                count++;
        }
        
        //count CG in dna
        int count2 = 0;
        for (int i = 0; i < m.length() - 1; i++){
            if (m.substr(i, 2) == "CG")
                count2++;
        }
        
        if (count > (3 * count2))
            chromozoms[n1] = '0';
}

void Cell::BigMutationDNA(string ss1, int nn, string ss2, int mm){
    string c1 = chromozoms[nn];
    string c2 = chromozoms[mm];

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
}

void Cell::SmallMutationDNA(char a, char b, int n, int m){
     string s = chromozoms[m];
        int i = 0;
        int j = 0; //movement step
        while (i <= n) {
            if (s[j] == a) {
                s[j] = b;
                i++;
                j++;
                if (i == n)
                    break;

            else
                j++;
            
            }
        }

        cout << s << '\t' << Supplement(s) << endl;
}

void Cell::reverseSubstring(string substring, int n){
    string str = chromozoms[n];
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
        cout << str << endl;
        cout << Supplement(str)<<endl;
        chromozoms[n] = str;
}

void Cell::findLongestPalindrome(int n){
    string s;
        s = chromozoms[n];
        int n2 = s.length();
        string longestPalindrome = "";

        for (int i = 0; i < n2; i++){
            for (int j = i + 2; j <= n2; j++){
                string substring = s.substr(i, j - i);

                if (isPalindrome(substring) && substring.length() > longestPalindrome.length())
                    longestPalindrome = substring;
            }

        }
        cout << longestPalindrome << '\t' << Supplement(longestPalindrome);
}

int main(){
    Genome genome("ACGGCCTAA", "ATCGATCG");
    genome.SmallMutationDNA('A', 'C', 2);

    



}




