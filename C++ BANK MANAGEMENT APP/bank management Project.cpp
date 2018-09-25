

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	
	void show_account() const;	
	void modify();	// this modify the existing account
	void dep(int);	// this is used to deposit money to the account
	void draw(int);	// this is used to withdraw money from the account
	void report() const;	// display the info of the account 
	int retacno() const;	// return the account number
	int retdeposit() const;	// return the deposite
	char rettype() const;	// return the type of the account
};         

void account::create_account()
{
	cout<<"\n\t\tEnter The account No. : ";
	cin>>acno;
	cout<<"\n\n\t\tEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\tEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	initial:
	cout<<"\n\t\tEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	if((deposit<500 && type=='S') || (deposit<1000 && type=='C'))
	goto initial;
	cout<<"\n\n\n\t\t\tAccount Created..";
}

void account::show_account() const
{
	cout<<"\n\t\tAccount No. : "<<acno;
	cout<<"\n\t\tAccount Holder's Name : ";
	cout<<name;
	cout<<"\n\t\tType of Account : "<<type;
	cout<<"\n\t\tBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\n\t\tAccount No. : "<<acno;
	cout<<"\n\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\tModify Type of Account : ";
	cin>>type;
	type=toupper(type);
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}
	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);	
void display_all();		
void deposit_withdraw(int, int); 
void intro();	



int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t\t\t            *** MAIN MENU***           \n";
		cout<<"\n\n\t\t\t***     01. NEW ACCOUNT                 ***";
		cout<<"\n\n\t\t\t***     02. DEPOSIT AMOUNT              ***";
		cout<<"\n\n\t\t\t***     03. WITHDRAW AMOUNT             ***";
		cout<<"\n\n\t\t\t***     04. BALANCE ENQUIRY             ***";
		cout<<"\n\n\t\t\t***     05. ALL ACCOUNT HOLDER LIST     ***";
		cout<<"\n\n\t\t\t***     06. CLOSE AN ACCOUNT            ***";
		cout<<"\n\n\t\t\t***     07. MODIFY AN ACCOUNT           ***";
		cout<<"\n\n\t\t\t***     08. EXIT                        ***\n";
		cout<<"    \t\t\t*******************************************\n";
		cout<<"    \t\t\t*******************************************\n";                      
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\t**Thank You For Visiting Our Branch**";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}

void write_account() // this is used to create the new account
{
	account ac;	
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


void display_sp(int n)  
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


void intro()
{
	cout<<"\n\n\t\t   ***Bank Management System***";
	cout<<"\n\t\t\t1. Pranav Chopra\n";
	cout<<"\n\t\t    ***Chitkara Uneversity***";
	cout<<"\n\n\t\tPlease enter any alphabt to continue banking management"<<endl;
	cin.get();
}

