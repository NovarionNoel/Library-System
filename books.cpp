#include <string>
#include "books.h"
#include <iostream>
using namespace std;

//adds books to booklist vector
void Books::addBook (Book b){bookList.push_back(b); count=bookList.size();}

//removes a book from the vector after checking to make sure the book id is valid and not checked out
void Books::deleteBook(int i){
   Book b = findBook(i);
   //searches vector for the book
   for (int a = 0; a<bookList.size(); a++){
        if (b.getID()!= -1 && b.getID()==bookList.at(a).getID() && b.getStatus()!=1){
            char c = 'f';
            cout << bookList.at(a).getTitle() << " found. Confirm delete? Y/N" <<endl;
            cin >> c;
			//confirms removal and then removes
            if (!cin.fail()&&(c == 'Y' || c== 'y')){
                cout << bookList.at(a).getTitle() << " removed." << endl;
                bookList.erase(bookList.begin()+a);
                count = bookList.size();
            }
            else {cout << bookList.at(a).getTitle() << " not removed." <<endl;}
        }
    }	
	//displays failure reason
    if (b.getID() == -1) {cout << i << " is not a valid ID." << endl;}
	if (b.getStatus()== 1) {cout << "Book checked out. Cannot remove." << endl;}
}

//menu option to initialize editing of a book object
void Books::editBook(int i){
     Book b = findBook(i);

     if (b.getID()!=-1){
        cout << b.getTitle() << " found. What would you like to edit?" << endl;
        editMenu(b);
     }
 
     else {cout << i << " is not a valid ID."<< endl;}
}

//recursive menu function to allow continuous editing of a book object
void Books::editMenu(Book &b){
    float editI;
    long long int editISBN;
    string editS;
    int locb;
	
	//locator to match book to id in vector. edits done on a temporary book object first for confirmation purposes.
    for (int i = 0; i < bookList.size(); i++) {
        if (b.getID() == bookList.at(i).getID()) {
            locb = i;
            break;
        }
    }

    char choice = 'z';
	//menu option list
    cout << "T - Title" << endl << "A - Author" << endl << "I - ISBN" << endl << "C - COST"<< endl << "S - STATUS" <<endl;
    cout << "E - Cancel Edit" <<endl;
    cout << "Choice:" << endl;
    cin >> choice;
	
    if (!cin.fail()) {
		//edits the title 
		if (choice == 'T' || choice == 't') {
            cout << "Enter the new title:" << endl;
            cin.ignore();
            getline(cin, editS);
            if (!cin.fail()) {
                cout << "Is " << editS << " correct? Y/N: " << endl;
                cin >> choice;
            
			//confirmation before changing title
            if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
                cout << editS << " set successfully." << endl;
                bookList.at(locb).setTitle(editS);
            }

            else { cout << "Title not updated." << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(b);
			}
		}
		
		//edits the author
        else if (choice == 'A' || choice == 'a') {
            cout << "Enter the new author:" << endl;
            cin.ignore();
            getline(cin, editS);
            if (!cin.fail()) {
                cout << "Is " << editS << " correct? Y/N " << endl;
                cin >> choice;
            }
			//confirmation before changing the author name
            if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
                cout << editS << " set successfully." << endl;
                bookList.at(locb).setAuthor(editS);
            }

            else { cout << "Author not updated. " << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(b);
        }
		
		//edits the ISBN
        else if (choice == 'I' || choice == 'i') {
            cout << "Enter the new ISBN:" << endl;
            cin >> editISBN;
            if (!cin.fail()) {
                cout << "Is " << editISBN << " correct? Y/N " << endl;
                cin >> choice;
            }
			//confirmation before changing the ISBN
            if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
                cout << editISBN << " set successfully." << endl;
                bookList.at(locb).setISBN(editISBN);
            }

            else { cout << "ISBN not updated. " << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(b);
        }
		//edits the cost of replacing the book
        else if (choice == 'C' || choice == 'c') {
            cout << "Enter the new cost:" << endl;
            cin >> editI;
            if (!cin.fail()) {
                cout << "Is " << editI << " correct? Y/N " << endl;
                cin >> choice;
            }
			//confirmation before changing cost
            if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
                cout << "$" << editI << " set successfully." << endl;
                bookList.at(locb).setCost(editI);
            }

            else { cout << "Cost not updated. " << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(b);
        }
		//changes the status of a book 
        else if (choice == 'S' || choice == 's') {
            bool fail = true;
			//loops until a valid status is received.
			while(fail){
				cout << "Enter the new status. In/Out/Repair/Lost" << endl;
				cin >> editS;
				if (!cin.fail()) {
					cout << "Is " << editS << " correct? Y/N " << endl;
					cin >> choice;
				}
				//confirmation before attempting to set new status
			   
			   if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
					
						if (editS.compare("in") == 0 || editS.compare("In") == 0) {
							editI = 0;
							fail = false;
						}

						else if (editS.compare("out") == 0 || editS.compare("Out") == 0) {
							editI = 1;
							fail = false;
						}

						else if (editS.compare("Repair") == 0 || editS.compare("repair") == 0) {
							editI = 2;
							fail = false;
						}

						else if (editS.compare("lost") == 0 || editS.compare("Lost") == 0) {
							editI = 3;
							fail = false;
						}
						
						if (!fail) {
							cout << "Status " << editS << " set successfully." << endl;
							bookList.at(locb).setStatus(editI);
						}
						
						else { cout << "Not a valid status. Try again. Options are In/Out/Repair/Lost." << endl; }
				  
				}
				else { cout << "Status not updated. " << endl; break;}
		   }

            

            cout << "Returning to edit menu." << endl;
            editMenu(b);
        }
		//Exits menu recursion, back to main.
        else if (choice == 'E' || choice == 'e') { cout << "Returning you to main menu." << endl; }
    }
    else{
        cout << "Selection not valid. Try again:" << endl;
        editMenu(b);
    }

}

//searchs for a book and returns a copy
Book Books::findBook(int i){
    bool found = false;
    Book notFound;
    
    for(unsigned int a=0; a<bookList.size(); a++){
        if(i == bookList.at(a).getID()){
            found = true;
            return bookList.at(a);
        }
    }

    if (found == false){ return notFound;}
    
    return notFound;
}

//prints the data associated with a book
void Books::PrintBook(Book b){
    
    if (b.getID()!= -1){
        cout << "ID: " << b.getID() << endl;
        cout << "Title: " << b.getTitle() << endl;
        cout << "Author: " << b.getAuthor() <<endl;
        cout << "ISBN: " << b.getISBN() << endl;
        cout << "Cost: $" << b.getCost()<< endl;
        string curr;
        
        if (b.getStatus() == 0) {
            curr = "In";
        }
        
        else if (b.getStatus() == 1) {
            curr = "Out";
        }
        
        else if (b.getStatus() == 2) {
            curr = "Repair";
        }
        
        else if (b.getStatus() == 3) {
            curr = "Lost";
        }
        
        cout << "Status: " << curr << endl <<endl;
    }

    else {cout  << "Book was not found."<< endl;}
}

//prints all books in the bookList vector
void Books::PrintBooks(){
   for (int i=0; i<bookList.size(); i++){
       PrintBook(bookList.at(i));
   }
}

//returns booklist vector by reference for editing
vector <Book>&  Books::getList(){return bookList;}

Books::Books(){
    count = 0;
}