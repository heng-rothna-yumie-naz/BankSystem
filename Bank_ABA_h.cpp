#include<iostream>
#include "Bank_ABA.h"
using namespace std;
int main(){
	//======Account creating======
	Bank myBank;
	Bank::ATM atm(myBank);
	Bank::Visa v(myBank);
	Bank::Credit c(myBank);
	Bank::Credit::SpendCredit spend(c);
	int choice,op;
	//=======Bank Option========
	a:
	do{
		cout<<"_____________Choose your Option_____________\n"
			<<"\t1. Create an account Bank.\n"
			<<"\t2. Exit"<<endl;
		cout<<"Input your option : ";cin>>op;
		cin.ignore();
		system("cls");
		again:
		switch (op){
			case 1:{
				cout<<"_________________Bank Account________________\n";
				cout<<"\tCreating an account..."<<endl;
				myBank.input();
				atm.ATM_input();
				atm.display_ATM();
				system("cls");
				do{
					cout<<"\n-------------------Bank Option-------------------------\n"
						<<"|--------------1. Create Visa Card----------------------|\n"
						<<"|--------------2. Create Credit Card--------------------|\n"
						<<"|--------------3. Withdraw via ATM----------------------|\n"
						<<"|--------------4. Pay with Visa Card--------------------|\n"
						<<"|--------------5. Pay with Credit Card------------------|\n"
						<<"|--------------6. Check balance-------------------------|\n"
						<<"|--------------7. Money spent on credit card------------|\n"
						<<"|--------------8. Exit----------------------------------|\n"
						<<"---------------------------------------------------------\n"<<endl;
					cout<<"Input number from 1-8: ";
					cin>>choice;
	//=======Basically where each option proccess=======
					switch(choice){
						case 1:{
							v.input_visa();					
						}break;
						
						case 2:{
							system("cls");
							c.input_credit();
						}break;
						case 3:{
							system("cls");
							atm.withdraw();
							myBank.showBalance();
						}break;
						case 4:{
							system("cls");
							v.payment();				
						}break;
						case 5:{
							system("cls");
							spend.verifying();
						}break;
						case 6:{
							system("cls");
							myBank.showBalance();
						}break;
						case 7:{
							system("cls");
							spend.show();
						}break;
						case 8:{
						system("cls");
						return 0;
						}break;
						default:
							cout<<"\tInvalid Option"<<endl;
							goto again;
					}
				}while(choice!=8);
			}break;
			case 2:{
				system("cls");
			}break;
			default:
				cout<<"\tInvalid option please choose again...\n";
				goto a;
		}
	}while(op!=2);
	return 0;
}
