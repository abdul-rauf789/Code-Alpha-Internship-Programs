//============================================================================
// Name        : Bank.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

string getCurrentDateTime() {
    time_t now = time(0);               // Get current time
    char* dt = ctime(&now);             // Convert to string
    return string(dt);                  // Return as C++ string
}

class Customer{
	string name;
	string cnic;

public:
	Customer(){
		cout << "Enter your name : ";
		getline(cin,name);
		cout << "Enter your CNIC : ";
		getline(cin,cnic);

	}

	string getName(){
		return name;
	}
	string getCnic(){
		return cnic;
	}

};

class Accounts{
	Customer user1;
	double balance=0;
	int tran=0;
	string file_user1 = user1.getCnic();

public:

	Accounts(){
		ifstream file(file_user1.c_str());
		float balance = 0;

		if (file.is_open()) {

			string line;
			while (getline(file, line)) {
				size_t pos = line.find("Balance : ");
				if (pos != string::npos) {
					balance = stof(line.substr(pos + 9));
					break;
				}
			}
			file.close();

		}
		else {

			ofstream file(file_user1.c_str());
			if(file.is_open()){
				file << "Name : " << user1.getName() << endl << "CNIC : " << user1.getCnic() << endl << "Balance : " << balance;
				file.close();
			}
			else {
				cout << endl << "Error in Opening the File.";
			}

		}
	}

	Accounts(double bal): tran(0){
		cout << endl <<  "Amount, you entered, was : " << bal << endl;

		ofstream file(file_user1.c_str());
		if(file.is_open()){
			file << "Name : " << user1.getName() << endl << "CNIC : " << user1.getCnic() << endl << "Balance : " << bal;
			file.close();
		}
		else {
			cout << endl << "Error in Opening the File.";
		}

		if(bal>=0){
			balance += bal;
		}
		else{
			cout << endl << "Please write amount greater than 0";
		}

	    ofstream trans("Transactions",ios :: app);
	    trans << endl << "Amount Deposited : " << bal << endl << "Date & Time : " << getCurrentDateTime();
	    trans.close();
	}

	void wdraw(double n) {
	    balance -= n;

	    // UPDATING THE BALANCE TO THE BASIC FILE(named by user_CNIC)


	        string filename = user1.getCnic();
	        ifstream inFile(filename.c_str());
	        ofstream outFile("temp.txt");

	        string line;
	        while (getline(inFile, line)) {
	            if (line.find("Balance : ") != string::npos) {
	                outFile << "Balance : " << balance << endl;
	            } else {
	                outFile << line << endl;
	            }
	        }

	        inFile.close();
	        outFile.close();

	        remove(filename.c_str());
	        rename("temp.txt", filename.c_str());


	    // UPDATING the data to Transaction File

	    ofstream trans("Transactions",ios :: app);
	    trans << endl << "Amount WithDraw : " << n << endl << "Date & Time : " << getCurrentDateTime();
	    trans.close();

	    cout << endl << "Your Current Balance is : " << balance;
	}

	void deposit(double n){
	    balance += n;

	    // UPDATING THE BALANCE TO THE BASIC FILE(named by user_CNIC)


	        string filename = user1.getCnic();
	        ifstream inFile(filename.c_str());
	        ofstream outFile("temp.txt");

	        string line;
	        while (getline(inFile, line)) {
	            if (line.find("Balance:") != string::npos) {
	                outFile << "Balance: " << balance << endl;
	            } else {
	                outFile << line << endl;
	            }
	        }

	        inFile.close();
	        outFile.close();

	        remove(filename.c_str());
	        rename("temp.txt", filename.c_str());


	    // UPDATING the data to Transaction File

	    ofstream trans("Transactions",ios :: app);
	    trans << endl << "Amount Deposited : " << n << endl << "Date & Time : " << getCurrentDateTime();
	    trans.close();

	    cout << endl << "Your Current Balance is : " << balance;

	}

	void display_trans_details(){
		cout << endl << "~~~TRANSACTION DETAILS~~~"<< endl << endl;
		ifstream f("Transactions");
		string line;
		while( getline(f,line) ){
			cout << line << endl;
		}
		f.close();

	}

	void display_user_details(){
		cout << endl << "~~~YOUR DETAILS~~~"<< endl << endl;
		ifstream f3(file_user1);
		string line;
		while( getline(f3,line) ){
			cout << line << endl;
		}
		f3.close();

	}


	~Accounts(){
	//	remove("Transactions");
	//	remove(file_user1.c_str());
	}


};

int main() {

	Accounts a;

	a.display_trans_details();
	a.display_user_details();



	return 0;
}
