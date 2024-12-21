#include<bits/stdc++.h>
using namespace std;

class Book{
    public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int id, string title, string author){
        this->id=id;
        this->title=title;
        this->author=author;
        this->issued=false;
    }

    void display(){
        cout<<"Book id: "<<id<<endl;
        cout<<"Title: "<<title<<endl;
        cout<<"Author: "<<author<<endl;
        cout<<"Issued: "<<(issued ? "Yes" : "No")<<endl;
    }

    void issueBook(){
        issued=true;
    }

    void returnBook(){
        issued=false;
    }
};

class Library{
    private:
    vector<Book>books;
    const string filename="LibraryData.txt";

    void loadBooks(){
        ifstream file(filename);
        if(file.is_open()){
            int id;
            string title, author;
            bool issued;
            while (file>>id>>ws)
            {
                getline(file,title);
                getline(file, author);
                file>>issued;
                Book book(id, title, author);
                book.issued=issued;
                books.push_back(book);
            }
            file.close();
        }
    }

    void saveBooks(){
        ofstream file(filename);
        for(Book &book: books){
            file<<book.id<<endl;
            file<<book.title<<endl;
            file<<book.author<<endl;
            file<<book.issued<<endl;
        }
        file.close(); 
    }

    public:
    Library(){
        loadBooks();
    }

    ~Library(){
        saveBooks();
    }

    void addBooks(int id, string title, string author){
        books.push_back(Book(id, title, author));
        cout<<"Book added successfully."<<endl;
    }

    void removeBook(int id){
        for(auto it=books.begin(); it!=books.end(); it++){
            if(it->id==id){
                books.erase(it);
                cout<<"Book removed successfully!"<<endl;
                return;
            }
        }
        cout<<"Book not found!"<<endl;
    }

    void displayBook(){
        for(Book &book: books){
            book.display();
            cout<<"---------------------"<<endl;
        }
    }

    void searchBook(string title){
        for(Book &book: books){
            if(book.title==title){
                book.display();
                return;
            }
        }
        cout<<"Book not found!"<<endl;
    }

    void issueBook(int id){
        for(Book &book: books){
             if(book.id==id && !book.issued){
                book.issueBook();
                cout<<"Book issued successfully."<<endl;
                return;
             }
        }
        cout<<"Book not found or not issued";
    }

    void returnBook(int id){
        for(Book &book: books){
            if(book.id==book.issued){
                book.returnBook();
                cout<<"Book return successfully!\n";
                return;
            }
        }
        cout<<"Book not found or not issued!\n";
    }
};

int main(){
    Library lib;
    int choice, id;
    string title, author;

    while(true){
        cout<<"\nLibrary managment system\n";
        cout<<"1. Add book: \n";
        cout<<"2. Remove book: \n";
        cout<<"3. Display all books: \n";
        cout<<"4. Search book by title: \n";
        cout<<"5. Issue book: \n";
        cout<<"6. Return book: \n";
        cout<<"7. Exit\n";

        cout<<"Enter your choice:  ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            cout<<"Enter book id: ";
            cin>>id;
            cin.ignore();//to ignore the newline character
            cout<<"Enter book title: ";
            getline(cin, title);
            cout<<"Enter book author: ";
            getline(cin, author);
            lib.addBooks(id, title,  author);
            break;

        case 2:
            cout<<"Enter book id to remove: ";
            cin>>id;
            lib.removeBook(id);
            break;

        case 3:
            lib.displayBook();
            break;

        case 4:
            cout<<"Enter book title to search: ";
            cin.ignore();
            getline(cin, title);
            lib.searchBook(title);
            break;

        case 5:
            cout<<"Enter book id to issue: ";
            cin>>id;
            lib.issueBook(id);
            break;

        case 6:
            cout<<"Enter book id to return: ";
            cin>>id;
            lib.returnBook(id);
            break;

        case 7:
            return 0;
        
        default:
            cout<<"Invalid choice!\n";
            break;
        }
    }
}