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

class Animal : public Cell{
private:
    // A function which we use in the needleman_wunsch_score function in order to
    // calculate the total score using MATCH_SCORE and MISMATCH_SCORE
    int score(char a, char b);

    // Returns the global alignment score of two string sequences using the Needleman-Wunsch algorithm 
    int needleman_wunsch_score(string x, string y);

    // Returns the percent similarity between two string sequences
    double percent_similarity(string x, string y);

public:
    // Constructor
    Animal(int number_of_chromozomes) : Cell(number_of_chromozomes){}

    // In this method we check the similarity percentage of the two given animals' chromozomes
    double Similarity(Animal animal);

    // Redefinition of the == operator
    bool operator== (Animal animal);

    // The Asexual reproduction method
    Animal AsexualReproduction();
    void AsexualReproductionDisplay();

    // Redefintion of the + operator
    void operator+ (Animal animal2);

    // A method which erases the broken chromozomes of an animal's cell
    void AnimalChromozomesDeath();

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

};

// Here are the methods of class Animal

int Animal::score(char a, char b){ 
    // Returns MATCH_SCORE if the two aligned characters match else returns MISMATCH_SCORE
    if (a == b)
        return MATCH_SCORE; 
	else
        return MISMATCH_SCORE; 
}

int Animal::needleman_wunsch_score(string x, string y){
    int n = x.length();
    int m = y.length();

	int dp[n + m + 1][n + m + 1];

	// Crerating a table (dp)
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
    // Divides the alingment_score in the max lenght of the 2 given strings
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
    // The two given animals are of the same type if they have above 70 % similarity and have 
    // the same number of chromozomes
    if (Similarity(animal) > 0.7 && (NumberOfChromozomes == animal.GetNumberOfChromozomes()))
        return true;
    
    else 
        return false;
}

Animal Animal::AsexualReproduction(){
    // The animal that will be aseuxally reproduced
    Animal animal2(0);
    // Creating two vetors in order to create random numbers
    vector <int> RandIndex1;
    vector <int> RandIndex2;
    // An integer random number generator which produces non-deterministic random numbers.
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
    cout << "The asexually reporoduced animal's chromozomes are: " << endl;
    AsexualReproduction().GetChromozomes();
}

void Animal::AnimalChromozomesDeath(){
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
                    NumberOfChromozomes--;
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
                    NumberOfChromozomes--;
                    check = false;
                    break;
                }
            }
        }
    }
}

void Animal::operator+ (Animal animal){
    // The animal that will be seuxally reproduced
    Animal animal3(0);
    Animal animal1 = AsexualReproduction();
    Animal animal2 = animal.AsexualReproduction();
    
    if(animal1 == animal2 && animal1.GetNumberOfChromozomes() % 2 == 0){
        // Creating two vetors in order to create random numbers
        vector <int> RandIndex1;
        vector <int> RandIndex2;
        // Creating two vetors in order to create random numbers
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
	int n = arr.size();

	// Taking the first word from an array as reference
	string s = arr[0].GetDNA();
	int len = s.length();

	string res = "";

	for (int i = 0; i < len; i++){
		for (int j = i + 1; j <= len; j++){
			// Generating all possible substrings
			// of our reference string arr[0]

			string stem = s.substr(i, j);
			int k = 1;
			for (k = 1; k < n; k++){
				// Check if the generated stem is common to all words
				if (Zsearch(arr[k].GetDNA(), stem) == std::string::npos)
					break;
			}

			// If the current substring is present in all the given strings and its 
            // length is greater than the current result
			if (k == n && res.length() < stem.length())
				res = stem;
		}
	}

	return res;
}

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
