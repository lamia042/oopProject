#include<bits/stdc++.h>
using namespace std;

class User{
    public:
    string name;
    string accountNumber;
    double balance;


    public:
    virtual void displayDetails()=0;
    virtual void modifyDetails()=0;
};

class Customer: public User{
    public:
    Customer(string n, string accNum, double bal){
        name=n;
        accountNumber=accNum;
        balance=bal;
    }

    void deposit(double amount){
        balance+=amount;
        cout<<"Deposited "<<amount<<" successfully"<<endl;
    }

    void withDraw(double amount){
        if(amount>balance){
            cout<<"Insufficient balance."<<endl;
        }
        else{
            balance-=amount;
            cout<<"Withdraw "<< amount<<" successfully"<<endl;
        }
    }

    void balanceCheck(){
        cout<<"Current balance "<<balance<<endl;
    }

    void displayDetails()override{
        cout<<"Name: "<<name<<endl;
        cout<<"Account Number: "<<accountNumber<<endl;
        cout<<"Balance: "<<balance<<endl;
    }

    void modifyDetails()override{
        cout<<"Modify name: "; 
        cin.ignore();
        getline(cin, name);
        cout<<"Details updated successfully."<<endl;
    }
};  

class Admin:public User{
    vector<Customer>customers;

    public:
    void displayDetails()override{
        cout<<"Displaying admin details.\n";
    }

    void modifyDetails()override{
        cout<<"Modifying admin details.\n";
    }
    void addCustomer(string n, string accNum, double bal){
        customers.push_back(Customer(n,accNum,bal));
        cout<<"Customer added successfully"<<endl;
    }

    void viewAllAccounts(){
        cout<<"Displaying all accounts: "<<endl;
        for(auto &it: customers){
            it.displayDetails();
            cout<<"----------------"<<endl;
        }
    }

    void modifyCustomer(string accNum){
        for(auto &it: customers){
            if(it.accountNumber==accNum){
                it.modifyDetails();
                return;
            }
        }
        cout<<"Account not found!"<<endl;
    }

    void saveDataToFile(){
        ofstream file("account.txt");//write+open
        for(auto &it: customers){
            file<<it.name<<","<<it.accountNumber<<","<<it.balance<<endl;
        }
        file.close();
        cout<<"Data saved to file"<<endl;
    }

    void loadDataFromFile(){
        ifstream file("account.txt");//read+open  
        string line, name, accNum;
        double bal;

        while(getline(file, line)){
            stringstream ss(line);
            if(getline(ss, name, ',') && getline(ss, accNum, ',') && ss>>bal){
                customers.push_back(Customer(name, accNum, bal));
            }
            else{
                cout<<"Error loading data for one of the accounts"<<endl;
            }
        }
        file.close();
        cout<<"Data loaded from file"<<endl;
    }

    // Function to find a customer by account number
    Customer* findCustomerByAccount(string accNum) {
        for (auto &it : customers) {
            if (it.accountNumber == accNum) {
                return &it;
            }
        }
        return nullptr;
    }
};

int main(){
    Admin admin;
    admin.loadDataFromFile();

    int choice;
    do{
        cout<<"Bank Management System"<<endl;
        cout<<"1. AddCustomer\n";
        cout<<"2. View all Accounts\n";
        cout<<"3. Modify customer\n";
        cout<<"4. Save data\n";
        cout<<"5. Deposit\n";
        cout<<"6. WithDraw\n";
        cout<<"7. Balance check\n";
        cout<<"5. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:{
                string name, accNum;
                double balance;
                cout<<"Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout<<"Enter account number: ";
                cin>>accNum;
                cout<<"Enter initial balance: ";
                cin>>balance;
                admin.addCustomer(name, accNum, balance);
                break;
            }

            case 2:
            admin.viewAllAccounts();
            break;

            case 3:{
                string accNum;
                cout<<"Enter account number to modify: ";
                cin>>accNum;
                admin.modifyCustomer(accNum);
                break;
            }

            case 4: 
            admin.saveDataToFile();
            break;

            case 5:{
                string accNum;
                double amount;
                cout << "Enter account number: ";
                cin >> accNum;
                Customer* customer = admin.findCustomerByAccount(accNum);
                if (customer) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    customer->deposit(amount);
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }

            case 6:{
                string accNum;
                double amount;
                cout << "Enter account number: ";
                cin >> accNum;
                Customer* customer = admin.findCustomerByAccount(accNum);
                if (customer) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    customer->withDraw(amount);
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }

            case 7:{
                string accNum;
                cout << "Enter account number: ";
                cin >> accNum;
                Customer* customer = admin.findCustomerByAccount(accNum);
                if (customer) {
                    customer->balanceCheck();
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }

            case 8:
                cout << "Exiting....\n";
                break;


            default:
            cout<<"Invalid choice\n";
        }
    }while (choice!=8);
    return 0;
}  