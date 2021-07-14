#include <iostream>
#include <string> 
#include <cstdlib> 
#include <ctime>
using namespace std;
 

void instructions()
{
    cout << "1. Choose any number between 1 -- 10" << endl;
  cout << "2. If you win you will get double of money you bet" << endl;
    cout << "3. If you bet on wrong number you will lose your betting amount" << endl;
}
 
 
 void playgame()
 {
  int dice;
  int guess;
  int amount;
  int bettingAmount;
  string playerName;
  cout << "\t\t\tEnter Your Name : ";
  cin.ignore();
  getline(cin, playerName);
  cout << "\t\t\tAmount you wanna play with: ";
  cin >> amount;
 do
 {
  do
        {
            cout << playerName <<", enter betting ammount: ";
            cin >> bettingAmount;
            if(bettingAmount > amount)
                cout << "Your betting amount is more than your current balance" << endl
                     <<"Please Re-enter data " << endl;
        } while(bettingAmount > amount);

        do
        {
            cout << "Guess your number to bet between 1 to 10: ";
            cin >> guess;
            if(guess <= 0 || guess > 10)
                cout << "Your Number should be between 1 to 10" << endl
                    << "Re-enter data " << endl;
        } while(guess <= 0 || guess > 10);
 
        dice = rand()%10 + 1; 
    
        if(dice == guess)
        {
            cout << "\n\nGood Luck!! You won Rs." << bettingAmount * 2;
            amount = amount + bettingAmount * 2;
        }
        else
        {
            cout << "Bad Luck this time !! You lost "<< bettingAmount <<"$" << endl;
            amount = amount - bettingAmount;
        }
 
        cout << "The winning number was : " << dice << endl;
        cout <<playerName<<", You have: " << amount <<"$ " << endl;
        
        if(amount == 0)
        {
            cout << "You have no money to play ";
            break;
        }
        
    }while(amount > 0);
    
 }
int main()
{
    string playerName;
    int amount, bettingAmount, choice;
    srand(time(0));
    
  system("clear");
    system(" chmod +x ./welcome_casino.sh");
    system("./welcome_casino.sh");
    

    while(1)
    {
        system("clear");
    cout << "\t\t\t1- Play Game" << endl
      << "\t\t\t2- Instructions" << endl
      << "\t\t\t3- Exit" << endl
      << "\t\t\tChoice: ";
     cin >> choice;     
     if (choice == 1)
     {
      playgame(); 
     }
     else if (choice == 2)
     {
      instructions();
     }
     else if (choice == 3)
     {
      cout <<"\t\t\t" << "Press any key to Exit..." << endl;
      cin.get();
      system("./dealloc_resource CASINO");
      exit(0);
       }
  } 
    
        
   
    return 0;
}
