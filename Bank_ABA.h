#ifndef Bank_ABA
#define Bank_ABA
#include<iostream>
#include<limits>
using namespace std;
class Bank{
	private:
		string name,id;
		float balance;
	public:
		friend class ATM;
		Bank(){};
		Bank(string name,string id,float balance){
			this->name=name;
			this->id=id;
			this->balance=balance;
		}
		void input(){
			cout<<"\tName: ";
			getline(cin,name);
			cout<<"\tID: ";
			getline(cin,id);
			cout<<"\tBalance: ";
			cin>>balance;
			cout<<"You have successfully to created an account."<<endl;
			cout<<"Your account has balance "<<balance<<"$\n";
			cout<<"You have also recieved for an ATM Card."<<endl;
		}
		string setID(string id){
			this->id=id;
		}
		string getID(){
			return id;
		}
		string getName(){
			return name;
		}
		float setBalance(float amt){
			balance=amt;
		}
		float getBalance(){
			return balance;
		}
		void showBalance(){
			cout<<"Your balance: "<<balance;
		}
		void withdraw(float amt){
			balance-=amt;
		}
	//=====ATM Card=====
	class ATM{
		private:
			string ATM_pw,withdraw_pw;
			float amount;
		public:
			Bank &bank;
			ATM(Bank &b):bank(b){};
			void display_ATM(){
				cout<<"\nYour ATM number is "<<bank.getID()<<endl;
				cout<<"Password: "<<ATM_pw<<endl;
			}
			void ATM_input(){
				cout<<"\tCreate your password here: ";cin>>ATM_pw;
			}
			void withdraw(){
				cout<<"\nEnter the amount: ";
				cin>>amount;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if(amount<=bank.getBalance()){
					cout<<"Enter your password: ";
					getline(cin,withdraw_pw);
					if(ATM_pw==withdraw_pw){
						cout<<"Verified!"<<endl;
						cout<<amount<<" have been successfully withdrawn from "<<bank.getID()<<endl;
						bank.balance-=amount;
					}
					else 
						cout<<"\tIncorrect password"<<endl;
				}
				else
					cout<<"\tYou do not have enough cash"<<endl;
			}
				
	};
	//=====Visa Card=====
	class Visa{
		private:
			int day,month,year,cvv;
			string visa_id,tmp;
			int pay_day,pay_month,pay_year,pay_cvv;
			string pay_id;
			float amount;
			int check;
		public:
			Bank &bank;
			Visa(Bank &b):bank(b){
				check=0;
			};
			void input_visa(){
				cout<<"\n\tFill in your account numebr to create Visa Card."<<endl;
				cout<<"\tAccount number: ";
				cin.ignore();
				getline(cin,tmp);
				
				if(tmp==bank.getID()){
					cout<<"\tAccount verified!"<<endl;
					cout<<"Visa ID: ";
					getline(cin,visa_id);
					cout<<"\t---Set D/M/Y & CVV u have create your Visa Card---\n";
					cout<<"Day: ";
					cin>>day;
					cout<<"Month: ";
					cin>>month;
					cout<<"Year(2***): ";
					cin>>year;
					cout<<"CVV: ";
					cin>>cvv;
					cout<<"\tYour Visa Card has been successfully created on "<<day<<"/"<<month<<"/"<<year<<endl;
					year=year+2;
					displayVisa_info();
				}
				else
					cout<<"\tIncorrect account number";
			}
			void displayVisa_info(){
				cout<<"\n\t---This your Visa Card information---"<<endl;
				cout<<"\tName: "<<bank.getName()<<endl
					<<"\tVisa ID: "<<visa_id<<endl
					<<"\tExpired date: "<<day<<"/"<<month<<"/"<<year<<endl
					<<"\tCVV: "<<cvv<<endl;
			}
			void payment(){
				if(check!=1){
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout<<"\n\tPlease fill in your card information to proceed"<<endl;
					cout<<"Visa Card ID: ";
					getline(cin,pay_id);
					cout<<"Day: ";
					cin>>pay_day;
					cout<<"Month: ";
					cin>>pay_month;
					cout<<"Year: ";
					cin>>pay_year;
					cout<<"CVV: ";
					cin>>pay_cvv;
					if(visa_id==pay_id)
						if(pay_day==day)
							if(pay_month==month)
								if(pay_year==year)
									if(pay_cvv==cvv){
										cout<<"\tVerified!"<<endl;
										cout<<"Please input the amount: ";
										cin>>amount;
										if(bank.getBalance()>=amount){
											cout<<amount<<" is paid from "<<bank.getID()<<endl;
											bank.withdraw(amount);
											bank.showBalance();
											check++;
										}
										else 
											cout<<"\tNot enough cash"<<endl;
									}
									else
										cout<<"\tIncorrect CVV"<<endl;
								else
									cout<<"\tIncorrect Year"<<endl;
							else 
								cout<<"\tIncorrect month"<<endl;
						else 
							cout<<"\tIncorrect day"<<endl;
					else
						cout<<"\tIncorrect ID"<<endl;
				}
				else{
					cout<<"\tPlease input the amount: ";
					cin>>amount;
					if(bank.getBalance()>=amount){
					cout<<amount<<" is paid from "<<bank.getID()<<endl;
					bank.withdraw(amount);
					bank.showBalance();
					}
					else
						cout<<"\tNot enough cash!"<<endl;
				}
			}
	};
	//=====Credit Card=====
	class Credit{
		private:
			int day,month,year,cvv;
			string credit_id,tmp;
		public: 
			Bank &bank;
			Credit(Bank &b):bank(b){};
			friend class SpendCredit;
			void input_credit(){
				cout<<"\n\tFill in your accound number to create Credit Card."<<endl;
				cout<<"Account number: ";
				cin.ignore();
				getline(cin,tmp);
				
				if(tmp==bank.getID()){
					cout<<"\tAccount verified!"<<endl;
					cout<<"Credit ID: ";
					getline(cin,credit_id);
					cout<<"Day: ";
					cin>>day;
					cout<<"Month: ";
					cin>>month;
					cout<<"Year: ";
					cin>>year;
					cout<<"CVV: ";
					cin>>cvv;
					cout<<"\tYour Credit Card has been successfully created on "<<day<<"/"<<month<<"/"<<year<<endl;
					year=year+2;
					displayCredit_info();
				}
				else
					cout<<"\tIncorrect account number";
			}
			void displayCredit_info(){
				cout<<"\n\t---This your Credit Card information---"<<endl;
				cout<<"Name: "<<bank.getName()<<endl
					<<"Credit ID: "<<credit_id<<endl
					<<"Expired date: "<<day<<"/"<<month<<"/"<<year<<endl
					<<"CVV: "<<cvv<<endl;
				cout<<"\tYour limit amount to spend: $10000"<<endl;
			}
			//=======Spending Proccess=======
			class SpendCredit{
				private:
				static const float limit=10000;
				int spending[100],amt,spentAmt;
				int spendCount,check;
				int pay_day,pay_month,pay_year,pay_cvv;
				string pay_id;
				public:
					Credit &credit;
					SpendCredit(Credit &c):credit(c){
						spendCount=0;
						spentAmt=0;
						check=0;
					}
					void verifying(){
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						if(check!=1){
							cout<<"\n\tPlease fill in your card information to proceed"<<endl;
							cout<<"Credit Card ID: ";
							getline(cin,pay_id);
							if(pay_id==credit.credit_id){
								cout<<"Day: ";
								cin>>pay_day;
								cout<<"Month: ";
								cin>>pay_month;
								cout<<"Year: ";
								cin>>pay_year;
							}
							else{
								cout<<"\tIncorrect ID"<<endl;
								return;
							}
								
							if(pay_day==credit.day)
								if(pay_month==credit.month)
									if(pay_year==credit.year){
										cout<<"CVV: ";
										cin>>pay_cvv;
									}
									else{
										cout<<"\tIncorrect date"<<endl;
										return;
									}
								else{
									cout<<"\tIncorrect date"<<endl;
									return;
								}
							else{
								cout<<"\tIncorrect date"<<endl;
								return;
							}
							if(pay_cvv==credit.cvv){
								cout<<"\tVerified"<<endl;
								check++;
								spend();
							}
							else{
								cout<<"\tIncorrect CVV"<<endl;
								return;
							}
						}	
						else
							spend();
					}
					void spend(){
						cout<<"Input amount: ";
						cin>>amt;
						if(amt<0){
							cout<<"\tInvalid input!"<<endl;
							return;
						}
						if(spentAmt+amt>limit)
						cout<<"\tYou have reached the limit"<<endl;
						else{
							spending[spendCount]=amt;
							spendCount++;
							spentAmt+=amt;
							cout<<"\t\tYou have spent: "<<amt<<endl;
						}
					}
					void show(){
						int i;
						cout<<"\tMoney have been spending: "<<endl;
						for(i=0;i<spendCount;i++)
							cout<<"-"<<spending[i]<<endl;
						cout<<"\tRemaining: "<<limit-spentAmt;
					}
			};	
	};
};
#endif
