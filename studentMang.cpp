#include<bits\stdc++.h>
using namespace std;

class Student{
    public:
    int id;
    string name;
    int age;
    string grade;
    int attendance;

    Student(int id, const string& name, int age, const string& grade, int attendance)//name is a reference to a string.name cannot be modified within the function or constructor where it's used.
        :id(id), name(name), age(age), grade(grade), attendance(attendance){}

    void display()const{
        cout<<"ID: "<<id<<", Name: "<<name
        <<", Age: "<<age<<", Grade: "<<grade<<", Attendance: "<<attendance<<endl;
    }
};

class StudentManager{
    vector<Student>students;

    public:
    void loadFromFile(const string &filename){
        ifstream file(filename);
        if(!file.is_open()){
            cout<<"Error: Could not open file."<<endl;
            return;
        }
        int id, age, attendance;
        string name, grade;
        while(file>>id>>name>>age>>grade>>attendance){
            students.push_back(Student(id, name, age, grade, attendance));
        }
        file.close();
    }

    void saveToFile(const string &filename){
        ofstream file(filename);
        if(!file.is_open()){
            cout<<"Error: Could not open file."<<endl;
            return;
        }
        for(const auto &student: students){
            file<<student.id<<" "<<student.name<<" "<<student.age
            <<" "<<student.grade<<" "<<student.attendance<<endl;
        }
        file.close();
    }

    void addStudent(const Student& student){
        students.push_back(student);
        cout<<"Student added successfully!"<<endl;
    }

    void deleteStudent(int id){
        for(auto it=students.begin(); it<students.end(); it++){
            if(it->id==id){
                students.erase(it);
                cout<<"Student with ID "<<id<<" deleted successfully!"<<endl;
                return;
            }
        }
        cout<<"Student with ID "<<id<<" not found!"<<endl;
    }

    void updateStudent(int id, const string& newName, int newAge, const string& newGrade, int newAttendance){
        for(auto &student: students){
            if(student.id==id){
                student.name=newName;
                student.age=newAge;
                student.grade=newGrade;
                student.attendance=newAttendance;
                cout<<"Student with ID "<<id<<" updated successfully."<<endl;
                return;
            }
        }
        cout<<"Student with ID "<<id<<" not found."<<endl;
    }

    void generateReport(){
        cout<<"Student report:"<<endl;
        for(const auto &student: students){
            student.display();
        }
    }
};

int main(){
    StudentManager manager;
    int id, age, attendance,choice;
    string grade, name;

    manager.loadFromFile("students.txt");

    while(true){
        cout<<"\nStudent managment system\n";
        cout<<"1. Add student: \n";
        cout<<"2. Remove student: \n";
        cout<<"3. Display all students: \n";
        cout<<"4. Save data to file: \n";
        cout<<"5. Uptade student information: \n";
        cout<<"6. Exit\n";

        cout<<"Enter your choice:  ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            cout<<"Enter student id: ";
            cin>>id;
            cin.ignore();//to ignore the newline character
            cout<<"Enter student name: ";
            getline(cin, name);
            cout<<"Enter student age: ";
            cin>>age;
            cin.ignore();// Adding cin.ignore() after integer inputs like id and age ensures
            // that any stray newline characters do not interfere with the subsequent getline() calls for string inputs.
            cout<<"Enter student grade: ";
            getline(cin, grade);
            cout<<"Enter student attendance: ";
            cin>>attendance;
            manager.addStudent(Student(id, name,  age, grade, attendance));
            break;

        case 2:
            cout<<"Enter student id to remove: ";
            cin>>id;
            manager.deleteStudent(id);
            break;

        case 3:
            manager.generateReport();
            break;

        case 4:
            manager.saveToFile("students.txt");
            break;

        case 5:
            cout << "Enter student id to update: ";
            cin >> id;
            cout << "Enter new age: ";
            cin >> age;
            cout << "Enter new attendance: ";
            cin >> attendance;
            cin.ignore();  // Ignore leftover newline after integer input
            cout << "Enter new grade: ";
            getline(cin, grade);
            cout << "Enter new name: ";
            getline(cin, name);
            manager.updateStudent(id, name, age, grade, attendance);
            break;
        case 6:
            return 0;
        
        default:
            cout<<"Invalid choice!\n";
            break;
        }
    }
}