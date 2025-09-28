#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

//---------------- Utility ----------------//
// return current date & time as string
string now() {
    time_t t = time(nullptr);
    tm tm{};
#ifdef _WIN32
    localtime_s(&tm,&t);
#else
    localtime_r(&t,&tm);
#endif
    char buf[64];
    strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",&tm);
    return buf;
}

//---------------- Customer ----------------//
class Customer {
    string name, cnic;      // basic customer data
public:
    Customer() = default;
    Customer(string n,string c): name(move(n)), cnic(move(c)) {}
    const string& getName() const { return name; }
    const string& getCnic() const { return cnic; }

    // Prompt user for details
    static Customer createFromInput() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string n,c;
        cout << "Enter full name : ";
        getline(cin,n);
        cout << "Enter CNIC (as ID): ";
        getline(cin,c);
        return Customer(n,c);
    }
};

//------------- Transaction Record ----------//
struct Transaction {
    string type;    // "Deposit" or "Withdraw"
    double amount;
    string time;
};

//---------------- Account ------------------//
class Account {
    Customer cust;
    double balance{};                  // current balance
    vector<Transaction> history;       // all past transactions
    fs::path accountFile;              // file path for storage

    // load data if file exists, otherwise create new file
    void loadOrCreate() {
        ifstream in(accountFile);
        if (!in) { save(); return; }   // create blank if no file

        string key;
        while (in >> key) {
            if (key == "Balance") {
                char colon; in >> colon;
                in >> balance;
            }
        }
        // load previous transactions
        ifstream tin(accountFile.string() + "_tx.txt");
        if(tin){
            Transaction t;
            while(tin >> t.type >> t.amount){
                tin.ignore();
                getline(tin,t.time);
                history.push_back(t);
            }
        }
    }

    // save current data & history to files
    void save() const {
        ofstream out(accountFile);
        out << "Name : "   << cust.getName() << "\n"
            << "CNIC : "   << cust.getCnic() << "\n"
            << "Balance : "<< balance       << "\n";

        ofstream tx(accountFile.string() + "_tx.txt");
        for (auto &h : history)
            tx << h.type << " " << h.amount << " " << h.time << "\n";
    }

    // helper to add a transaction and save
    void record(const string &type,double amt){
        history.push_back({type,amt,now()});
        save();
    }

public:
    explicit Account(Customer c)
        : cust(move(c)),
          accountFile(fs::path("data") / (cust.getCnic() + ".txt"))
    {
        fs::create_directory("data");  // ensure folder exists
        loadOrCreate();
    }

    void deposit(double amt){
        if(amt<=0){ cout<<"Amount must be positive.\n"; return; }
        balance += amt;
        record("Deposit",amt);
        cout<<"Deposited "<<amt<<". New balance: "<<balance<<"\n";
    }

    void withdraw(double amt){
        if(amt<=0){ cout<<"Amount must be positive.\n"; return; }
        if(amt>balance){ cout<<"Insufficient funds.\n"; return; }
        balance -= amt;
        record("Withdraw",amt);
        cout<<"Withdrew "<<amt<<". New balance: "<<balance<<"\n";
    }

    void showDetails() const {
        cout << "\n----- Account Details -----\n"
             << "Name    : " << cust.getName() << "\n"
             << "CNIC    : " << cust.getCnic() << "\n"
             << "Balance : " << balance << "\n";
    }

    void showHistory() const {
        cout << "\n----- Transaction History -----\n";
        if(history.empty()) { cout << "No transactions yet.\n"; return; }
        for (auto &h : history)
            cout << left << setw(10) << h.type
                 << setw(12) << h.amount
                 << h.time << "\n";
    }
};

//---------------- Main --------------------//
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Welcome to Harvard-MIT Bank ===\n";
    Customer c = Customer::createFromInput();
    Account acc(c);

    // simple menu loop
    while(true){
        cout << "\nChoose option:\n"
             << "1. Deposit\n2. Withdraw\n3. Show Balance\n"
             << "4. Transaction History\n5. Exit\n> ";
        int choice; 
        if(!(cin>>choice)) break;

        if(choice==1){
            double amt; cout<<"Enter amount to deposit: "; cin>>amt;
            acc.deposit(amt);
        }
        else if(choice==2){
            double amt; cout<<"Enter amount to withdraw: "; cin>>amt;
            acc.withdraw(amt);
        }
        else if(choice==3){
            acc.showDetails();
        }
        else if(choice==4){
            acc.showHistory();
        }
        else if(choice==5){
            cout<<"Goodbye!\n";
            break;
        }
        else cout<<"Invalid option.\n";
    }
    return 0;
}
