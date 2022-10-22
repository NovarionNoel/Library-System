//Nova Lader
//Course: CSCE 1040 Sec 302
//Lab: Sec 314
//Homework 3

#include "loans.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

//saves data from the program into new files
void saveFiles(Books books, Patrons patrons, Loans loans){
    //clears files of old data
	ofstream bstream("books.dat", ofstream::trunc);
    ofstream lstream("loans.dat", ofstream::trunc);
    ofstream pstream("patrons.dat", ofstream::trunc);

    int i;
	//prints book information to books.dat for all entries in bookList
    for (i=0; i<books.getList().size(); i++){
        bstream << books.getList().at(i).getTitle() << ';' ;
        bstream << books.getList().at(i).getAuthor() << ';' ;
        bstream << books.getList().at(i).getISBN() << ';';
        bstream << books.getList().at(i).getID() << ';';
        bstream << books.getList().at(i).getCost() << ';';
        bstream << books.getList().at(i).getStatus() << endl;
    }
	
	//prints loan information to loans.dat for all entries in loanList
    for (i=0; i<loans.getList().size(); i++){
        
        lstream << loans.getList().at(i).getID() << ';' ;
        lstream << loans.getList().at(i).getPatronID() << ';' ;
        lstream << loans.getList().at(i).getBookID() << ';';
        lstream << loans.getList().at(i).getTime() << ';';
        lstream << loans.getList().at(i).getDue() << ';';

        if (loans.getList().at(i).getStatus()){lstream << "true;";}
        else{lstream << "false;";}

        if (loans.getList().at(i).getRecheck()){lstream << "true";}
        else{lstream << "false";}
        
        lstream<<endl;   
    }
	
	//prints patron information to patrons.dat for all entries in patronList
    for (i=0; i<patrons.getList().size(); i++){
        pstream << patrons.getList().at(i).getName() << ';' ;
        pstream << patrons.getList().at(i).getID() << ';' ;
        pstream << patrons.getList().at(i).getFines() << ';';
        pstream << patrons.getList().at(i).getBooksOut() << endl; 
    }

}

//prints the main menu options
void printMenu(){
    cout << "Select an option:" << endl;
    cout << "0 - Loan System (Check In, Checkout, Overdue)" << endl;
    cout << "1 - Patrons (Add, Remove, Edit, Pay Fines)" << endl;
    cout << "2 - Books (Add, Remove, Update Status)" << endl;
    cout << "9 - Exit" << endl;
}


//runs the menu function choices
void mainMenu(int choice, Books  &books, Patrons &patrons, Loans &loans){
    string info;
    char select = 'z';
    int bid;
    long long int bisbn;
    int pid;
    float costs;
	
    switch(choice){
        //enters the loan menu
		case 0:
            loans.loanMenu(books, patrons, loans, choice, pid, select, bid);
            break;
			
		//begins the patron menu system
        case 1:
            cout << "Welcome to the Patron system. Select an option:" <<endl;
            cout << "0 - Add Patron" << endl;
            cout << "1 - Update Patron or Pay Fines" << endl;
            cout << "2 - Remove a Patron." << endl;
            cout << "3 - List all Patrons." << endl;
            cout << "4 - Back to Main Menu." <<endl;
            cin >> choice;

            if (!cin.fail()) {
                if (choice == 0) {
					//until a valid confirmation is received, asks for patron name
					while (select != 'Y' && select != 'y') {
						cout << "Please enter the Patron's Name" << endl;
						cin.ignore();
						getline(cin, info);
						if (cin.fail()) break;
						cout << "Is " << info << " correct? Y/N" << endl;
						cin >> select;
						if (cin.fail()) break;
					}
						
					if (!cin.fail()){
						Patron temp(info);
						patrons.addPatron(temp);
					}
				}
				//enters edit patron menu
				else if (choice == 1) { patrons.editPatron(); }
				
				//enters delete patron menu
				else if (choice == 2) { patrons.deletePatron(); }

				//prints all patrons
				else if (choice == 3) { patrons.printAllPatrons(); }
				//returns to menu
				else if (choice == 4) { cout << "Returning to main menu." << endl; }
				
				else cout << "Not a valid choice. Returning to main menu. "<< endl;
            
			}
			else { cout << "Not a valid choice. Returning to main menu." << endl; }
            
            break;
        //enters book system menu
        case 2:
            cout << "Welcome to the Book System. Select an option:" << endl;
            cout << "0 - Add a Book" << endl;
            cout << "1 - Report Lost" << endl;
            cout << "2 - Report Damaged" << endl;
            cout << "3 - Remove a Book" << endl;
            cout << "4 - Update Book Information" << endl;
            cout << "5 - List all Books" << endl;
            cout << "6 - Return to Main Menu" << endl;
            cin >> choice;

            if (!cin.fail()) {
                if (choice == 0) {
					bool fail = false;
					//begins process to add a book
					//creates a temporary book for confirmation purposes
                    Book temp;
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the book title:" << endl;
                        cin.ignore();
                        std::getline(cin, info);
                        if (cin.fail()) { fail = true; break; }
                        cout << "Is " << info << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) { fail = true; break; }
                    }
					//sets title after successful confirmation
					if (!cin.fail()){
						temp.setTitle(info);
						select = 'z';
					}
					//sets author after successful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the author's name:" << endl;
                        cin.ignore();
                        std::getline(cin, info);
                        if (cin.fail()) {fail = true; break; }
                        cout << "Is " << info << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) {fail = true; break; }
                    }

                    if (!cin.fail()){
						temp.setAuthor(info);
						select = 'z';
					}
					//sets ISBN after successful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the ISBN (13 preferred):" << endl;
                        cin >> bisbn;
                        if (cin.fail()) {fail = true; break; }
                        cout << "Is " << bisbn << " correct?" << endl;
                        cin.ignore();
                        cin >> select;
                        if (cin.fail()) {fail = true; break; }
                    }
					if (!cin.fail()){
						temp.setISBN(bisbn);
						select = 'z';
					}
					//sets cost after successful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the cost:" << endl;
                        cin >> costs;
                        if (cin.fail()) { fail = true; break; }
                        cout << "Is $" << costs << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) { fail = true; break; }
                    }
					
					//if input is valid, creates book with temp's user-assigned values
                    if (!cin.fail()&&!fail){
						temp.setCost(costs);
						Book added(temp.getAuthor(), temp.getTitle(), temp.getISBN(), temp.getCost());
						books.addBook(added);
						cout << "Book added to library." << endl;
					}
					else {cout<< "Book unable to be added. Try again." << endl;}
                }

                else if (choice == 1) {
					//reports a book lost after successful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the Book ID: " << endl;
                        cin >> bid;
                        if (cin.fail()) { break; }
                        cout << "Is Book " << bid << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) { break; }
                    }
					if(!cin.fail()){
						select = 'z';
						Loan L = loans.findLoan(bid);
						pid = L.getPatronID();

						loans.reportLost(bid, pid, patrons.getList(), books.getList());
					}
                }

                else if (choice == 2) {
					//reports a book damaged after succcessful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the Book ID: " << endl;
                        cin >> bid;
                        if (cin.fail()) { break; }
                        cout << "Is Book " << bid << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) { break; }
                    }
					if(!cin.fail()){
						Loan L = loans.findLoan(bid);
						pid = L.getPatronID();
						loans.reportDamaged(bid, pid, patrons.getList(), books.getList());
					}
				}

                else if (choice == 3) {
					//removes a book after successful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the Book ID: " << endl;
                        cin >> bid;
                        if (cin.fail()) { break; }
                        cout << "Is Book " << bid << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) { break; }
                    }
                   if(!cin.fail()){ books.deleteBook(bid);}
                }

                else if (choice == 4) {
					//edits a book after successful confirmation
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the Book ID: " << endl;
                        cin >> bid;
                        if (cin.fail()) { break; }
                        cout << "Is Book " << bid << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) { break; }
                    }
                   if(!cin.fail()){ books.editBook(bid);}
                }
				//prints all books
                else if (choice == 5) { books.PrintBooks(); }
				//exits menu to main menu
                else if (choice == 6) { cout << "Returning to main menu." << endl; }
            }
            else { cout << "Not a valid choice." << endl; }
            break;

		//exits program
        case 9:
            cout << "Shutting down." << endl;
    }    

}
//reads in data from books.dat, patrons.dat, and loans.dat to Books, Loans, and Patrons vectors
void openFiles(Books  &books, Patrons &patrons, Loans  &loans){
    ifstream bstream("books.dat", ios::in);
    ifstream pstream("patrons.dat", ios::in);
    ifstream lstream("loans.dat", ios::in);
    string input;
	
	//makes sure file is open, then checks for end of file before attempting to read in data from books
    if(bstream.is_open()){
        while(!bstream.eof()){
            Book temp;

            getline(bstream,input, ';');
            if (input.compare("") == 0) { break; }
            temp.setTitle(input);
            
            getline(bstream, input, ';');
            temp.setAuthor(input);
            
            getline(bstream, input, ';');
            temp.setISBN(stoll(input,nullptr,10));

            getline(bstream, input, ';');
            temp.setID(stoi(input));

            getline(bstream, input, ';');
            temp.setCost(stof(input));

            getline(bstream, input);
            temp.setStatus(stoi(input));
            
            books.addBook(temp);
            
            if(bstream.eof()){break;}
        }
    }
	
	//makes sure file is open, then checks for end of file  befkre attempting to read in data from patrons
    if (pstream.is_open()){
        while(!pstream.eof()){
            Patron temp;
            
            getline(pstream,input, ';');
            if (input.compare("") == 0) { break; }
            temp.setName(input);          
            
            getline(pstream, input, ';');
            temp.setID(stoi(input));

            getline(pstream, input, ';');
            temp.setFines(stof(input));

            getline(pstream, input);
            temp.setBooksOut(stoi(input));
            
            patrons.addPatron(temp);

            if(pstream.eof()){break;}
        }
    }
	//makes sure file is open, then checks for end of file  befkre attempting to read in data from loans
    if (lstream.is_open()){
        while(!lstream.eof()){
            Loan temp;

            getline(lstream, input, ';');
            if (input.compare("") == 0) { break; }
            temp.setID(stoi(input));

            getline(lstream, input, ';');
            temp.setPatronID(stoi(input));
            
            getline(lstream, input, ';');
            temp.setBookID(stoi(input));

            getline(lstream, input, ';');
            temp.setTime(stoul(input,nullptr,10));

            getline(lstream, input, ';');
            temp.setDue(stoul(input,nullptr,10));

            getline(lstream, input, ';');
            if (input.compare("false")==0){temp.setStatus(false);}   
            else {temp.setStatus(true);}

            getline(lstream, input);
            if (input.compare("false")==0){temp.setRecheck(false);}
            else{temp.setRecheck(true);}
            
            loans.addLoan(temp);
            
            if(lstream.eof()){break;}
        }
    }
    bstream.close();
    lstream.close();
    pstream.close();
}


//run the library system
int main(){
	//object declarations
    Books books;
    Patrons patrons;
    Loans loans;
    
	//reads in the data
    openFiles(books, patrons, loans);
    
	//validates and updates ID values for books, patrons, and loans
    if (books.getList().size()>0) {
        int a;
        a= (books.getList().at(books.getList().size()-1).getID())+1;
        Book::nextID= a;
    }
    
    if (patrons.getList().size()>0){
        int a;
        a= (patrons.getList().at(patrons.getList().size()-1).getID())+1;
        Patron::nextID= a;
    }
    
    if (loans.getList().size()>0){
        int a;
        a= (loans.getList().at(loans.getList().size()-1).getID())+1;
        Loan::nextID= a;
    }
    

    int choice = -1;
    cout << "Welcome to the Library System." << endl;
	
	//until a user exits or causes a crash with invalid input, runs library system menus
    while (choice !=9){
		
        //catches fails from last run of mainMenu
		if (cin.fail()){
			cout << "The program will now shut down." << endl; 
			break;}
        printMenu();
        cin >> choice;
		
        //catches fails when new menu choices are made
        if (!cin.fail()) { mainMenu(choice, books, patrons, loans); }
		
        else {
            cout << "Not a valid option." << endl;
            cout << "The program will now shut down." << endl; 
            break;
        }
    }
    //saves files whether exited intentionally or by input failure to avoid data loss
    saveFiles(books,patrons,loans);
}