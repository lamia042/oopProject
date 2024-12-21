#include<bits\stdc++.h>
using namespace std;

class Employee{
    public:
    int id;
    string name;
    double baseSalary;

    public:
    Employee(int id, const string& name, double baseSalary)
    :id(id), name(name), baseSalary(baseSalary){}

    virtual void display(){
        cout<<"ID: "<<id<<", Name: "<<name<<", BaseSalary: "<<baseSalary<<endl;
    }

    virtual double calculateSalary(){
        return baseSalary;
    }

    virtual void promote(double risePercentage){
        baseSalary+=baseSalary*(risePercentage/100);
        cout<<"Employee "<<name<<" promoted with a new salary: $"<<baseSalary<<endl;
    }
};

class Manager:public Employee{
    double bonus;

    public:
    Manager(int id, const string& name, double baseSalary, double bonus)
    :Employee(id, name, baseSalary), bonus(bonus){}

    double calculateSalary()override{
        return baseSalary+bonus;
    }

    void display()override{
        cout<<"ID: "<<id<<", Name: "<<name<<", Position: Manager, Salary with Bonus: $" << calculateSalary() << endl;
    }
};

class Developer:public Employee{
    int projectCount;

    public:
    Developer(int id, const string& name, double baseSalary, int projectCount)
    :Employee(id, name, baseSalary), projectCount(projectCount){}

    double calculateSalary()override{
        return baseSalary+(projectCount*500);
    }

    void display()override{
        cout<<"ID: "<<id<<", Name: "<<name<<", Position: Developer, Salary with Bonus: $" << calculateSalary() << endl;
    }
};

class EmployeeManager {
    vector<Employee *>employees;

    public:
    void loadFromFile(const string &filename){
        ifstream file(filename);
        if(!file.is_open()){
            cout<<"Error: Could not open file!"<<endl;
            return;
        }
        int id;
        string name;
        double baseSalary;
        while(file>>id>>name>>baseSalary){
            employees.push_back(new Employee(id, name, baseSalary));
        }
        file.close();
    }

    void saveToFile(const string &filename){
        ofstream file(filename);
        if(!file.is_open()){
            cout<<"Error: Could not open file."<<endl;
            return;
        }
        for(const auto &employee: employees){
            file<<employee->id<<" "<<employee->name<<" "<<employee->calculateSalary()<<endl;
        }
        file.close();
    }

    void addEmployee(Employee *employee){
        employees.push_back(employee);
        cout<<"Employee added successfully!"<<endl;
    }

    void deleteEmployee(int id){
        for(auto it=employees.begin(); it<employees.end(); it++){
            if((*it)->id==id){
                employees.erase(it);
                cout<<"Employee with ID "<<id<<" deleted successfully!"<<endl;
                return;
            }
        }
        cout<<"Employee with ID "<<id<<" not found!"<<endl;
    }

    void promoteEmployee(int id, double raisePercentage){
        for(auto &employee: employees){
            if(employee->id==id){
                employee->promote(raisePercentage);
                return;
            }
            cout<<"Employee with id "<<id<<" not found!"<<endl;
        }
    }

    void displayEmployees() const {
        cout << "Employee List:" << endl;
        for (const auto &employee : employees) {
            employee->display();
        }
    }
};

int main() {
    EmployeeManager manager;
    int choice, id, projectCount;
    string name;
    double baseSalary, bonus, raisePercentage;

    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Manager\n";
        cout << "2. Add Developer\n";
        cout << "3. Display All Employees\n";
        cout << "4. Promote Employee\n";
        cout << "5. Save Employees to File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Base Salary: ";
                cin >> baseSalary;
                cout << "Enter Bonus: ";
                cin >> bonus;
                manager.addEmployee(new Manager(id, name, baseSalary, bonus));
                break;

            case 2:
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Base Salary: ";
                cin >> baseSalary;
                cout << "Enter Project Count: ";
                cin >> projectCount;
                manager.addEmployee(new Developer(id, name, baseSalary, projectCount));
                break;

            case 3:
                manager.displayEmployees();
                break;

            case 4:
                cout << "Enter Employee ID to Promote: ";
                cin >> id;
                cout << "Enter Raise Percentage: ";
                cin >> raisePercentage;
                manager.promoteEmployee(id, raisePercentage);
                break;

            case 5:
                manager.saveToFile("employees.txt");
                break;

            case 6:
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}