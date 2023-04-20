#include <iostream>
#include <typeinfo>
#include "Cell.h"
#include "Animal.h"
using namespace std;

int main(){

    do{
        //Enter your choice according to the command list
        cout << endl;
        cout << "Which class do you want to work with?" << endl;
        cout << "1. Genome" << endl;
        cout << "2. Cell" << endl;
        cout << "3. Animal" << endl;
        cout << "4. Virus" << endl;
        cout << "0. Terminate the program." << endl;

        int i = 10;
        int id;
        int choice;

        cin >> choice;
        cout << endl;

        switch (choice){
            case 0: {
                i = 0;
                break;
            }

            case 1: {
                string seq1, seq2, seq3;
                cout << "Enter the DNA and RNA threads of the genome you want to work with." << endl;
                cin >> seq1 >> seq2 >> seq3;
                Genome genome(seq1, seq2, seq3);
                cout << endl;

            do{
                cout << "What do you want to do?" << endl;
                cout << "5. Display the DNA threads." << endl;
                cout << "6. Display the RNA thread." << endl;
                cout << "7. Make DNA threads out of the given RNA thread." << endl;
                cout << "8. Small mutation for the RNA thread." << endl;
                cout << "9. Small mutation for the the DNA threads." << endl;
                cout << "10. Big mutation for the RNA thread." << endl;
                cout << "11. Big mutation for the DNA threads." << endl;
                cout << "12. Reverse mutation for the RNA thread." << endl;
                cout << "13. Reverse mutation for the DNA threads." << endl;
                cout << "29. I want to work with another class." << endl;

                cin >> choice;

                cout << endl;

                switch (choice){
                    case 5: {
                        cout << "The given genome's DNA threads are: " << endl;
                        cout << genome.GetDNA() << '\t' << genome.GetSDNA() << endl;
                        cout << endl;
                        break;
                    }

                    case 6: {
                        cout << "The given genome's RNA thread is: " << endl;
                        cout << genome.GetRNA() << endl;
                        cout << endl;
                        break;
                    }
                
                    case 7: {
                        genome.MakeDNAoutofRNA();
                        cout << endl << endl;
                        break;
                    }

                    case 8: {
                        cout << "The given genome's RNA thread is: " << endl;
                        cout << genome.GetRNA() << endl;
                        cout << endl;

                        char a1, b1;
                        int n1;
                        cout << "Enter the character you want to replace." << endl;
                        cin >> a1;
                        cout << "Enter the character you want to replace the given character with." << endl;
                        cin >> b1;
                        cout << "Enter the number of times you want to excute this task." << endl;
                        cin >> n1;
                        genome.SmallMutationRNA(a1, b1, n1);
                        cout << endl;
                        break;
                    }

                    case 9: {
                        cout << "The given genome's DNA threads are: " << endl;
                        cout << genome.GetDNA() << '\t' << genome.GetSDNA() << endl;
                        cout << endl;

                        char a2, b2;
                        int n2;
                        cout << "Enter the character you want to replace." << endl;
                        cin >> a2;
                        cout << "Enter the character you want to replace the given character with." << endl;
                        cin >> b2;
                        cout << "Enter the number of times you want to excute this task." << endl;
                        cin >> n2;
                        genome.SmallMutationDNA(a2, b2, n2);
                        cout << endl;
                        break;
                    }

                    case 10: {
                        cout << "The given genome's RNA thread is: " << endl;
                        cout << genome.GetRNA() << endl;
                        cout << endl;

                        string s1, s2;
                        cout << "Enter the substring you want to replace." << endl;
                        cin >> s1;
                        cout << "Enter the string you want to replace the given substring with." << endl;
                        cin >> s2;
                        genome.BigMutationRNA(s1, s2);
                        cout << endl;
                        break;
                    }

                    case 11: {
                        cout << "The given genome's DNA threads are: " << endl;
                        cout << genome.GetDNA() << '\t' << genome.GetSDNA() << endl;
                        cout << endl;

                        string s11, s22;
                        cout << "Enter the substring you want to replace." << endl;
                        cin >> s11;
                        cout << "Enter the string you want to replace the given substring with." << endl;
                        cin >> s22;
                        genome.BigMutationDNA(s11, s22);
                        break;
                    }

                    case 12: {
                        cout << "The given genome's RNA thread is: " << endl;
                        cout << genome.GetRNA() << endl;
                        cout << endl;

                        string s;
                        cout << "Enter the substring you want to reverse." << endl;
                        cin >> s;
                        genome.ReverseMutationRNA(s);
                        cout << endl;
                        break;
                    }

                    case 13: {
                        cout << "The given genome's DNA threads are: " << endl;
                        cout << genome.GetDNA() << '\t' << genome.GetSDNA() << endl;
                        cout << endl;

                        string ss;
                        cout << "Enter the substring you want to reverse." << endl;
                        cin >> ss;
                        genome.ReverseMutationDNA(ss);
                        cout << endl;
                        break;
                    }

                    case 29: {
                        i = 1;
                        break;
                    }

                    default: {
                        cout << "Invalid operator input." << endl;
                        break;
                    }
                }
            }while(i != 1);

            break;
            }

            case 2: {
                int n3;
                cout << "Enter the number of chromozomes that your cell has." << endl;
                cin >> n3;
                cout << endl;
                Cell* cell = new Cell(n3);
                cout << endl;

            do{
                cout << "What do you want to do?" << endl;
                cout << "14. Print the given cell's number of chromozomes." << endl;
                cout << "15. Print the given cell's chromozomes." << endl;
                cout << "16. Small mutation for the given chromzomes." << endl;
                cout << "17. Big mutation for the given chromozomes." << endl;
                cout << "18. Reverse mutation for the given chromozomes." << endl;
                cout << "19. Find supplementary palindromes in the given chromozome." << endl;
                cout << "20. Check whether the cell dies or not." << endl;
                cout << "30. I want to work with another class." << endl;

                cin >> choice;
                cout << endl;

                switch (choice){
                    case 14: {
                        cout << "The given cell's number of chromozome(s): " << endl;
                        cout << cell->GetNumberOfChromozomes();
                        cout << endl << endl;
                        break;
                    }

                    case 15: {
                        cout << "The given cell's chromozomes are: " << endl;
                        cell->GetChromozomes();
                        cout << endl;
                        break;
                    }

                    case 16: {
                        char a3, b3;
                        int n4, m1;
                        cout << "The given cell's chromozomes are: " << endl;
                        cell->GetChromozomes();
                        cout << endl;
                        cout << "Enter the character you want to replace." << endl;
                        cin >> a3;
                        cout << "Enter the character you want to replace the given character with." << endl;
                        cin >> b3;
                        cout << "Enter the number of times you want to excute this task." << endl;
                        cin >> n4;
                        cout << "Enter the number of the chromozome you want to perform this task on." << endl;
                        cin >> m1;
                        cell->SmallMutationDNA(a3, b3, n4, m1);
                        cout << endl;
                        break;
                    }

                    case 17: {
                        string s3, s4;
                        int n5, m2;
                        cout << "The given cell's chromozomes are: " << endl;
                        cell->GetChromozomes();
                        cout << endl;
                        if (cell->GetNumberOfChromozomes() < 2){
                            cout << "This operation is not possible." << endl;
                            break;
                        }
                        cout << "Enter the substring from the first chromozome that you want to replace." << endl;
                        cin >> s3;
                        cout << "Enter the substring from the second chromozome that you want to replace." << endl;
                        cin >> s4;
                        cout << "Enter the number of the first chromozome you want to perform this task on." << endl;
                        cin >> n5;
                        cout << "Enter the number of the second chromozome you want to perform this task on." << endl;
                        cin >> m2;
                        cell->BigMutationDNA(s3, n5, s4, m2);
                        cout << endl;
                        break;
                    }

                    case 18: {
                        string s5;
                        int m3;
                        cout << "The given cell's chromozomes are: " << endl;
                        cell->GetChromozomes();
                        cout << endl;
                        cout << "Enter the substring that you wnat to reverse in the given chromozome." << endl;
                        cin >> s5;
                        cout << "Enter the number of the chromozome you want to perforom this task on." << endl;
                        cin >> m3;
                        cell->ReverseMutationDNA(s5, m3);
                        cout << endl;
                        break;
                    }

                    case 19: {
                        int m4;
                        cout << "The given cell's chromozomes are: " << endl;
                        cell->GetChromozomes();
                        cout << endl;
                        cout << "Enter the number of the chromozome you want to perform this task on." << endl;
                        cin >> m4;
                        cell->FindSupplementaryPalindromes(m4);
                        cout << endl;
                        break;
                    }
                    
                    case 20: {
                        cell->CellDeath();
                        cout << endl;
                        break;
                    }

                    case 30: {
                        i = 2;
                        cout << endl;
                        break;
                    }

                    default : {
                        cout << "Invalid operator input." << endl;
                        break;
                    }
                }
            }while(i != 2);
            break;
            }
            
            case 3: {
                int n6, n7;
                cout << "Enter the number of chromozomes that your first animal's cell has." << endl;
                cin >> n6;
                cout << "Enter the number of chromozomes that your second animal's cell has." << endl;
                cin >> n7;

                // In this section you will set the chromzomes of the given animals' cells as well
                Animal animal1(n6);
                Animal animal2(n7);

            do{
                cout << endl;
                cout << "What do you want to do?" << endl;
                cout << "21. Print the given animals' cells' number of chromozomes." << endl;
                cout << "22. Print the given animals' cells' chromozomes." << endl;
                cout << "23. Print the similarity percentage of 2 given animals." << endl;
                cout << "24. Check if the 2 given animals are of the same type." << endl;
                cout << "25. Print the asexually reproduced animals from the given animals." << endl;
                cout << "26. Print the sexually reproduced animal from the given animals." << endl;
                cout << "27. check which chromozomes die after the death animal method has been performed." << endl;
                cout << "31. I want to work with another class." << endl;
                
                cin >> choice;
                cout << endl;
                
                switch(choice){
                    case 21: {
                        cout << "The first animal's number of chromozomes: " << animal1.GetNumberOfChromozomes() << endl;
                        cout << "The second animal's number of chromozomes: " << animal2.GetNumberOfChromozomes() << endl;
                        break;
                    }
                    
                    case 22: {
                        cout << "The first animal's chromozomes are: " << endl;
                        animal1.GetChromozomes();
                        cout << endl;
                        cout << "The second animal's chromozomes are: " << endl;
                        animal2.GetChromozomes();
                        break;
                    }
                    
                    case 23: {
                        cout << "The given animals' similarity percentage is: " << (animal1.Similarity(animal2) * 100) << " %" << endl;
                        break;
                    }

                    case 24: {
                        if(animal1 == animal2)
                            cout << "The given animals are of the same type." << endl;

                        else 
                            cout << "The given animals are not of the same type." << endl;
                        
                        break;
                    }
                    
                    case 25: {
                        cout << "The asexually reproduced animal from the first given animal: " << endl;
                        animal1.AsexualReproductionDisplay();
                        cout << endl;
                        cout << "The asexually reproduced animal from the second given animal: " << endl;
                        animal2.AsexualReproductionDisplay();

                        break;
                    }
                    
                    case 26: {
                        animal1 + animal2;
                        break;
                    }

                    case 27: {
                        cout << "The first animal's chromozomes before the operation: " << endl;
                        animal1.GetChromozomes();
                        cout << endl;
                        cout << "Operation on the first given animal: "<< endl;
                        animal1.AnimalChromozomesDeath();
                        cout << endl; 
                        cout << "The first animal's chromozomes after the operation: " << endl;
                        animal1.GetChromozomes();
                        cout << endl << "----------------------- Grown, eh? -----------------------" << endl;
                        cout << "The second animal's chromozomes before the operation: " << endl;
                        animal2.GetChromozomes();
                        cout << endl;
                        cout << "Operation on the second given animal: "<< endl;
                        animal2.AnimalChromozomesDeath(); 
                        cout << endl;
                        cout << "The second animal's chromozomes after the operation: " << endl;
                        animal2.GetChromozomes();
                        cout << endl;
                        break;
                    }

                    case 31: {
                        i = 3;
                        break;
                    }

                    default : {
                        cout << "Invalid operator input." << endl;
                        break;
                    }
                }
            }while(i != 3);
            break;
            }

            case 4: {
                string seq4;
                int n8;
                cout << "Enter the RNA thread of the virus you want to work with." << endl;
                cin >> seq4;
                cout << "Enter the number of chromozomes that your animal's cell has." << endl;
                cin >> n8;
                Virus virus(seq4);
                Animal animal(n8);


            do{
                cout << "What do you want to do?" << endl;
                cout << "28. Check whther the virus is harmful or not?" << endl;
                cout << "32. I want to work with another class." << endl;

                cin >> choice;
                cout << endl;

                switch(choice){
                    case 28: {
                        if(virus.isVirusHarmful(animal))
                            cout << "The given virus is harmful." << endl;
                        
                        else 
                            cout << "The given virus ain't harmful at all fam." << endl;

                        break;
                    }

                    case 32: {
                        i = 5;
                        break;
                    }

                    default : {
                        cout << "Invlid operator input." << endl;
                        break;
                    }
                }
            }while(i != 5);
            }

            default: {
                cout << "Invalid operator input." << endl;
                break;
            }
        }

        if(i == 0) {
            break;
        }

    }while(1);

    cout << "The program has been terminated." << endl;
}