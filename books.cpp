#include <string>
#include "books.h"
#include <iostream>
using namespace std;

void Books::addBook (Book b){bookList.push_back(b); count=bookList.size();}

void Books::deleteBook(int i){
   Book b = findBook(i);
    for (int a = 0; a<bookList.size(); a++){
    if (b.getID()!= -1 && b.getID()==bookList.at(a).getID()){
        char c = 'f';
        cout << bookList.at(a).getTitle() << " found. Confirm delete? Y/N?" <<endl;
        cin >> c;

        if (c == 'Y' || c== 'y'){
            cout << bookList.at(a).getTitle() << "removed." << endl;
            bookList.erase(bookList.begin()+a);
            count = bookList.size();}
        
        else {cout << bookList.at(a).getTitle() << "not removed." <<endl;}
    }
    else { cout << i << " is not a valid ID." << endl;}
}
}


void Books::editBook(int i){
 Book b = findBook(i);

 if (b.getID()!=-1){
    cout << b.getTitle() << " found. What would you like to edit?" << endl;
    editMenu(b);
 }
 
 else {cout << i << " is not a valid ID."<< endl;}
 }

void Books::editMenu(Book &b){
    float editI;
    string editS;
    char choice = 'z';
    cout << "T - Title" << endl << "A - Author" << endl << "I - ISBN" << endl << "C - COST" << endl;
    cout << "E - Cancel Edit" <<endl;
    cout << "Choice:" << endl;
    cin >> choice;
    
    if (choice == 'T' || choice == 't'){
        cout << "Enter the new title:" << endl;
        getline(cin,editS);
        
        cout << "Is " << editS << " correct? Y/N: " << endl;
        cin >> choice;
        
        if (choice == 'Y' || choice =='y'){
            cout << editS << " set successfully." <<endl;
            b.setTitle(editS);}

        else {cout << "Title not updated."<<endl;}
        
        cout << "Returning to edit menu." << endl;
        editMenu(b);}
    else if (choice == 'A' || choice == 'a'){
        cout << "Enter the new author:" << endl;
        getline(cin, editS);
        cout << "Is " << editS << " correct? Y/N " << endl;
        if (choice == 'Y' || choice =='y'){
            cout << editS << " set successfully." <<endl;
            b.setAuthor(editS);
            }
        else {cout << "Author not updated. " <<endl;}

        cout << " Returning to edit menu." <<endl;
        editMenu(b); }

    else if (choice == 'I' || choice == 'i' ){
        cout << "Enter the new ISBN:" << endl;
        cin >> editI;
        cout << "Is " << editI << " correct? Y/N " << endl;
        if (choice == 'Y' || choice =='y'){
            cout << editI << " set successfully." <<endl;
            b.setISBN(editI);
            }
        else {cout << "ISBN not updated. " <<endl;}

        cout << " Returning to edit menu." <<endl;
        editMenu(b);}

    else if (choice == 'C' || choice == 'c' ){
        cout << "Enter the new cost:" << endl;
        cin >> editI;
        cout << "Is " << editI << " correct? Y/N " << endl;
        if (choice == 'Y' || choice =='y'){
            cout << "$" << editI << " set successfully." <<endl;
            b.setCost(editI);}
        else {cout << "Cost not updated. " <<endl;}

        cout << " Returning to edit menu." <<endl;
        editMenu(b);

    }
    else if (choice == 'E' || choice == 'e'){
        cout << "Returning you to main menu." << endl;
    }
    else{
        cout << "Selection not valid. Try again:" << endl;
        editMenu(b);
    }
}

Book Books::findBook(int i){
    bool found = false;
    Book notFound;
    for(unsigned int a=0; a<bookList.size(); a++){
        if(i == bookList.at(a).getID()){
            found = true;
            return bookList.at(a);}
        }
    if (found == false){
        return notFound;}
    return notFound;
}

void Books::PrintBook(Book b){
if (b.getID()!= -1){
    cout << "Title: " << b.getTitle() << endl;
    cout << "Author: " << b.getAuthor() <<endl;
    cout << "ISBN: " << b.getISBN() << endl;
    cout << "Cost: " << b.getCost()<< endl;
    cout << "Status: " << b.getStatus() << endl;
}

else {cout  << "Book was not found."<< endl;}
}

void Books::PrintBooks(){
   for (int i=0; i<bookList.size(); i++){
    PrintBook(bookList.at(i));
   }
}
vector <Book>  Books::getList(){return bookList;}

Books::Books(){
count = 0;
}