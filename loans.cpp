#include "loans.h"
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//checks out a book to a patron
void Loans::checkOut(Patrons  &patrons, Books  &books, int pi, int bi){
    int i;
    int locp = 0;
    int locb = 0;
    bool fp = false;
    bool fb = false;
	
	//checks for patron id and identifies if it was found
    for (i = 0; i<patrons.getList().size(); i++){
        if (pi == patrons.getList().at(i).getID()){
            fp = true;        
            locp = i;
            break;
        }
    }
	
	//checks for book id and identifies if it was found
    for (i=0; i<books.getList().size(); i++){
        if (bi == books.getList().at(i).getID()){
            fb = true;
            locb = i;
            break;}
    }
	//runs if both the book and patron are found to begin checkout process
    if (fp == true && fb == true){
        bool fail = false;
		//verifies the patron does not owe money before approving checkout
        if (patrons.getList().at(locp).getFines() > 0){ 
            cout << "Checkout failed. " << patrons.getList().at(locp).getName() << " has an outstanding balance of $" << patrons.getList().at(locp).getFines() << endl;
            fail = true;
        }
		//fails if the patron has too many books out.
        if (patrons.getList().at(locp).getBooksOut() >= 6){
            cout << "Checkout failed. " << patrons.getList().at(locp).getName() << " has too many books out." << endl;
            fail = true;
        }
		
		//fails if the book has a status other than In
        if (books.getList().at(locb).getStatus() != 0){
            cout << "Checkout failed. "<< books.getList().at(locb).getTitle() << " is currently unavailable for checkout." << endl;
            fail = true;
        }
		
		//if the checkout process did not fail for any reason, check out the book, create a loan, and update the patron and book objects
        if (fail == false){
            Loan nLoan(pi,bi);
            int a = patrons.getList().at(locp).getBooksOut() + 1;
			
			//Updates patron and book
            patrons.getList().at(locp).setBooksOut(a);
            books.getList().at(locb).setStatus(1);
            
			//adds loan to list and updates size
            loanList.push_back(nLoan);
            count = loanList.size();
            time_t time = nLoan.getDue();
            const time_t *t;
            t = &time;
			//informs user of successful checkout 
            cout << books.getList().at(locb).getTitle() << " checked out to " << patrons.getList().at(locp).getName() << endl;
            cout << "It is due back by: " <<  ctime(t) << endl;
        }    
    }
	
    //displays reason for checkout failures due to ID error
	else if (!fb && !fp) {
        cout << "Checkout failed. Neither book or patron found. Check IDs." << endl;
    }
    else if (fp == false){
        cout << "Checkout failed. Patron not found. Check ID." <<endl;
    }
    
    else if (fb == false){
        cout << "Checkout failed. Book not found. Check ID." <<endl;
    }
    
    
}

//checks a book back in
void Loans::checkIn(Patrons &patrons, Books  &books, int id){
    //returns a copy of the loan to check
	Loan cIn = findLoan(id);
	
	//checks book in if the loan was found
    if (cIn.getID()!=-1){
        int i;
		//finds the book and updates the status to In, gives a message to the user
        for (i=0; i<books.getList().size(); i++){
            if (cIn.getBookID() == books.getList().at(i).getID()){
                books.getList().at(i).setStatus(0);
                cout << books.getList().at(i).getTitle() << " checked back in successfully." << endl;
                break;}
        }

        for (i = 0; i<patrons.getList().size(); i++){
			//finds the patron and removes the book from their out list
            if (cIn.getPatronID() == patrons.getList().at(i).getID()){     
                patrons.getList().at(i).setBooksOut(patrons.getList().at(i).getBooksOut()-1);
				
				//checks if a book is overdue and assigns new fines based on the time overdue
				updateOverdue();
                if (cIn.getStatus()) {
                    int a = ((cIn.getDue() - time(0)) / (24 * 60 * 60)) * (-1);
                    float f = a * .25;
                    patrons.getList().at(i).setFines(f);
                    cout << patrons.getList().at(i).getName() << " has a new fine balance of $" << f << ". Please pay promptly." << endl;
                }
                break;
            }
        }
		//removes loan from the list and updates loan count
        for (i = 0; i<loanList.size(); i++){
            if (cIn.getID()==loanList.at(i).getID()){
                loanList.erase(loanList.begin()+i);
                count = loanList.size();
                break;
            }
        }
    }
	//displays error if loan was not found
    else{ cout << "Check in failed. Loan not found. Check ID." <<endl;}
}
//searches for a loan and returns a copy
Loan Loans::findLoan(int i){
    Loan notFound;
    for (int a = 0; a <loanList.size(); a++){
        if (i == loanList.at(a).getBookID()){
            return loanList.at(a);
        }
    }
    return notFound;
}

//lists all overdue books
void Loans::listOverdue(){
    updateOverdue();
    int c = 0;
	//for each loan that is overdue, it calculates how many days it is overdue before printing the loan.
    for (int i = 0; i<loanList.size(); i++){
        if (loanList.at(i).getStatus()){
            int a = ((time(0) - loanList.at(i).getDue())/(24*60*60));
            printLoan(loanList.at(i));
            cout << "Overdue by " << a << " days."<< endl<< endl; 
            c++;
        }
    }
    cout << "Number of overdue books: " << c << endl;
}

//finds all books checked out to a particular patron
void Loans::ListbyPatron(int pi){
    int i;
    int c=0;
    //prints the loan for each loan that has a matching patron id
	for (i=0; i<loanList.size(); i++){
        if (loanList.at(i).getPatronID()==pi){
            printLoan(loanList.at(i));
            c++;
        }
    }
    if (c!=0){cout << "Patron " << pi << " has " << c << " books checked out." <<endl;}
    else {cout << "Patron " << pi << " has no books checked out." << endl;}
}

//starts the process to edit a loan by finding it and calling the edit menu 
void Loans::editLoan(int id, Patrons &patrons, Books &books){
    Loan temp = findLoan(id);
	
	//if the loan is found, begin running the edit functions
    if (temp.getID()!=-1){
        cout << "Loan " << id << " found." << endl;
        printLoan(temp);
        editMenu(temp, patrons, books);
        }        
    //if not, tells user it failed and exits edit function
    else {cout << "Could not find loan. Check ID." << endl;}
}

//menu to choose how to edit a loan.
void Loans::editMenu(Loan &L, Patrons &patrons, Books &books){
    int editI;
    string editS;
    char choice = 'z';
    int locl;
	int locb;
	int locp;
	//locates the actual loan
    for (int i = 0; i < loanList.size(); i++) {
        if (L.getID() == loanList.at(i).getID()){
            locl=i;
            break;
        }
    }
	//menu options
    cout << "What would you like to edit?" << endl;
    cout << "B - Book" << endl << "P - Patron" << endl << "C - Checkout Time" << endl << "D - Due Date" << endl;
    cout << "R - Recheck Status" << endl;
    cout << "E - Cancel Edit" <<endl;
    cout << "Choice:" << endl;
    cin >> choice;

    if (!cin.fail()) {
		//lets user edit the book id associated with the loan
        if (choice == 'B' || choice == 'b') {
            cout << "Enter the book ID:" << endl;
            cin >> editI;

            if (!cin.fail()) {
                cout << "Is " << editI << " correct? Y/N: " << endl;
                cin >> choice;
            }
            
            if (!cin.fail()) {
			//confirmation before attempting to assign the ID
                if (choice == 'Y' || choice == 'y') {
                   
					bool found = false;
					
					//checks the book id is valid and book is not checked out before reassigning
					for (int i =0; i<books.getList().size(); i++){
					
						if (books.getList().at(i).getID()==editI && books.getList().at(i).getStatus()== 0){
							locb=i;
							found = true;
							break;
						}						
					}
					//if found, reassigns the loan and updates the checkout list
					if (found == true){
						for (int i = 0; i < books.getList().size(); i++) {
							if (L.getBookID() == books.getList().at(i).getID()) {
								books.getList().at(i).setStatus(0);
								break;
							}
						}
						books.getList().at(locb).setStatus(1);
						loanList.at(locl).setBookID(editI);
						cout << editI << " set successfully." << endl;
						cout << "Status of Book " << L.getBookID() << " set to in. If this is not correct, please update in the book system." << endl;
						cout << "Status of Book " << editI << " set to out." << endl;
					}
                }
			}
                    
        
            else { cout << "Book ID not updated." << endl; }
            

            cout << "Returning to edit menu." << endl;
            editMenu(L, patrons, books);
        }
		
		//edits the patron associated with the loan
        else if (choice == 'P' || choice == 'p') {
            cout << "Enter the patron ID:" << endl;
            cin >> editI;
            
			if (!cin.fail()){ 
                cout << "Is " << editI << " correct? Y/N " << endl;
                cin >> choice;
            
            
				if (!cin.fail()) {
					//confirms before attempting to update
					if (choice == 'Y' || choice == 'y') {
						bool found = false;
						//makes sure patron id exists before reassigning
						for (int i=0; i< patrons.getList().size();i++){
							if (patrons.getList().at(i).getID() == editI){
								found = true;
								locp=i;
								break;
							}
						}
						if (found){
							//unassociates original patron with the loan
							for (int i = 0; i < patrons.getList().size(); i++) {
								if (L.getID() == patrons.getList().at(i).getID()) {
									patrons.getList().at(i).setBooksOut(patrons.getList().at(i).getBooksOut() - 1);
									break;
								}
							}
							//associates new patron with the loan. 
							//This is for entry errors, so it is the only place possible to exceed 6 books checked out if a librarian made an error
							patrons.getList().at(locp).setBooksOut(patrons.getList().at(locp).getBooksOut() + 1);
							if (patrons.getList().at(locp).getBooksOut() > 6) {
								cout << "Warning. This Patron has too many books out. Do not issue further loans." << endl;
							}
						   
							
						
						loanList.at(locl).setPatronID(editI);
						cout << "Patron " << editI << " set successfully. They are now associated with this loan." << endl;
						cout << "Patron " << L.getPatronID() << " no longer associated with this loan." << endl;
						}	
					}
				}

            else { cout << "Patron ID not updated. " << endl; }
            }

            cout << "Returning to edit menu." << endl;
            editMenu(L, patrons, books);
		}
			
		//lets you edit the checkout date in case of error or system being down when checkouts need to be made 
		//"reservation" checkout is a placeholder for a reservation system function in future builds
		
        else if (choice == 'C' || choice == 'c') {
            cout << "How would you like to change the checkout date?" << endl;
					//cout << "R - reservation" << endl 
			cout << "A - Earlier" << endl << "N - Now" << endl << "C - Cancel" << endl;
            cin >> choice;
            
					// if (!cin.fail()&&(choice == 'R' || choice == 'r')) {
					//     cout << "How many days in advance to reserve?" << endl;
					//     cin >> editI;
                
					//     if (!cin.fail()) {
					//         cout << "Is " << editI << " correct? Y/N " << endl;
					//         cin >> choice;
					//		}

					 //     if (!cin.fail()&&(choice == 'Y' || choice == 'y')) {
					 //         long int a = L.getTime() + (editI * 24 * 60 * 60);
					//         loanList.at(locl).setTime(a);
					//         loanList.at(locl).setDue(a + (10 * 24 * 60 * 60));
					//         cout << "Resevation set." << endl;
					//			cout << "Checkout and due date updated." << endl;
					//     }
							
					//     else { cout << "Nothing updated." << endl; }
					// }
					
			//earlier checkouts for loans made when system is down
			if (!cin.fail()){	
				if (choice == 'A' || choice == 'a') {
					cout << "How many days sooner was it checked out?" << endl;
					cin >> editI;
					if (!cin.fail()){
						cout << "Is " << editI << " correct? Y/N " << endl;
						cin >> choice;
				

						if (!cin.fail()&&(choice == 'Y' || choice == 'y')) {
							long int a = L.getTime() - (editI * 24 * 60 * 60);
							loanList.at(locl).setTime(a);
							loanList.at(locl).setDue(a + (10 * 24 * 60 * 60));
							cout << "Checkout and due date updated." << endl;
							 time_t time = loanList.at(locl).getTime();
							const time_t* t;
							t = &time;
							
							cout << "New Checkout Date: " << ctime(t) << endl;
							time = loanList.at(locl).getDue();
							cout << "New Due Date: " << ctime(t) << endl;
							cout << "Returning to edit menu." << endl;
							editMenu(L, patrons, books);
						}
					}
                else { cout << "Nothing updated." << endl; }
				}
			
				// sets checkout time to now in cases of librarian error
				else if (choice == 'N' || choice == 'n') {
					loanList.at(locl).setTime(time(0));
					loanList.at(locl).setDue(time(0) + 10 * 24 * 60 * 60);
					cout << "Checkout and due date updated." << endl;
					time_t time = loanList.at(locl).getTime();
					const time_t* t;
					t = &time;
            
					cout << "New Checkout Date: " << ctime(t) << endl;
					time = loanList.at(locl).getDue();
					cout << "New Due Date: " << ctime(t) << endl;
					cout << "Returning to edit menu." << endl;
					editMenu(L, patrons, books);
				}
				
				//exits without editing
				else if (choice == 'C' || choice == 'c') {
                cout << "Returning to edit menu." << endl;
                editMenu(L, patrons, books);
				}
			}	
            else {
                cout << "Not a valid choice." << endl;
                cout << "Returning to edit menu." << endl;
                editMenu(L, patrons, books);
			}
		
		}
            
           
		
		//for manual due date extension if necessary
        else if (choice == 'D' || choice == 'd') {
            cout << "How many more days do you want to extend the due date?" << endl;
            cin >> editI;
            
            if (!cin.fail()) {
                cout << "Is " << editI << " correct? Y/N " << endl;
                cin >> choice;
            

				if (!cin.fail()&&(choice == 'Y' || choice == 'y')) {
					long int a = L.getDue() + (editI * (24 * 60 * 60));
					loanList.at(locl).setDue(a);
					time_t time = loanList.at(locl).getDue();
					const time_t* t;
					t = &time;
					cout << "Due date updated to :" << ctime(t) << endl;
				}
				else {cout << "Due date not updated." << endl;}
			}

            else { cout << "Due date not updated. " << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(L, patrons, books);
        }
		
		//In cases where manual rechecks may need to be allowed, or rechecks should not be allowed for a particular book
        else if (choice == 'R' || choice == 'r') {
        //checks for recheck status    
			if (L.getRecheck()) {
                cout << "Book has been rechecked already. Reset? Y/N" << endl;
                cin >> choice;
                //confirms and sets
                if (!cin.fail()&&(choice == 'Y' || choice == 'y')) {
                    loanList.at(locl).setRecheck(false);
                    cout << "Book can be rechecked again." << endl;
                }
            }
            
            else if (!L.getRecheck()) {
                cout << "Book has not been rechecked. Is this wrong? Y/N" << endl;
                cin >> choice;
                //confirms and sets
                if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
                    loanList.at(locl).setRecheck(true);
                    cout << "Book can no longer be rechecked." << endl;
                }
            }
            cout << "Returning to edit menu." << endl;
            editMenu(L, patrons, books);
        }

        
        else if (choice == 'E' || choice == 'e') {
            cout << "Returning you to main menu." << endl;
        }
    }

    else{
        cout << "Selection not valid. Try again:" << endl;
        editMenu(L,patrons,books);
    }
}

//reports a book lost by updating the patron, book, and loan involved
void Loans::reportLost(int bi, int ci, vector <Patron>& patrons, vector <Book>& books){
    int i;
    int locb=-1;
    int locp;
    float c = 0;
    bool found = false;
	//finds the associated book
    for (i = 0; i < books.size(); i++) {
        if (bi == books.at(i).getID()) {
            locb = i;
            break;
        }
    }
    //if book is not found, end fucntions
    if (locb == -1) {
        cout << "Could not find book. Check ID." << endl;
    }
	//finds associated patron
    for (i = 0; i < patrons.size(); i++) {
        if (ci == patrons.at(i).getID()) {
            locp = i;
            found = true;
            break;
        }
    }
    //only proceeeds if both book and patron were found to update book, loan and patron with fines, new status, and deleting the loan
    if (found && locb!=-1) {
        for (int a = 0; a < loanList.size(); a++) {
            if (bi == loanList.at(a).getBookID()) {
                loanList.erase(loanList.begin() + a);
                count = loanList.size();
                books.at(locb).setStatus(3);
                c = books.at(locb).getCost();
                patrons.at(locp).setFines(patrons.at(locp).getFines() + c);
                patrons.at(locp).setBooksOut(patrons.at(locp).getBooksOut() - 1);
                cout << books.at(locb).getTitle() << " reported lost. Patron " << patrons.at(locp).getName()<< " has been fined for $" << books.at(locb).getCost() << "." << endl;
                break;
            }
        }
    }
    if (!found){
        cout << "Could not find patron. Check ID." << endl;
    }
}

//checks if a book can be rechecked, and if it can, rechecks it.
void Loans::reCheck(int id){
   bool found = false;
   for (int i =0; i<loanList.size(); i++){
        if (id == loanList.at(i).getID()){
            if (loanList.at(i).getRecheck()){
                cout << "Cannot recheck. Book already rechecked once." << endl;
                found = true;
                break;
            }

            else {
                loanList.at(i).setRecheck(true);
                time_t t= time(0)+(10*24*60*60);
                loanList.at(i).setDue(t);
                time_t time = loanList.at(i).getDue();
                const time_t *tim;
                tim = &time;
                cout << "Recheck successful. New due date is: " << ctime(tim) << endl;
                found = true;
                break;
             }
        }
   }
    if (!found){
        cout << "Loan not found. Could not recheck." << endl;
    }
}

//behaves exactly like reportLost. reports a book damaged and updates the book, patron, and associated loan
void Loans::reportDamaged(int bi, int ci, vector <Patron>  &patrons, vector <Book>  &books){
    int i;
    int locb = -1;
    int locp;
    float c = 0;
    bool found = false;
	//locates book
    for (i = 0; i < books.size(); i++) {
        if (bi == books.at(i).getID()) {
            locb = i;
            break;
        }
    }
    if (locb == -1) {
        cout << "Could not find book. Check ID." << endl;
    }
	//locates patron
    for (i = 0; i < patrons.size(); i++) {
        if (ci == patrons.at(i).getID()) {
            locp = i;
            found = true;
            break;
        }
    }
	//proceeds if both are found to update patron with fines, update book status, and remove the loan
    if (found && locb !=-1){
        for (int a = 0; a < loanList.size(); a++) {
            if (bi == loanList.at(a).getBookID()){
                loanList.erase(loanList.begin() + a);
                count = loanList.size();
                books.at(locb).setStatus(2);
                c = books.at(locb).getCost();
                patrons.at(locp).setFines(patrons.at(locp).getFines() + c);
                patrons.at(locp).setBooksOut(patrons.at(locp).getBooksOut() - 1);
                cout << books.at(locb).getTitle() << " reported damaged. Patron " << patrons.at(locp).getName() << " has been fined for $" << books.at(locb).getCost() << "." << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "Could not find patron. Check ID." << endl;
    }
}

//checks if any loans are overdue and updates their status
void Loans::updateOverdue(){
    int i;
    time_t a;
    for (i = 0; i<loanList.size(); i++){
        a = time(0) - loanList.at(i).getDue();
        if (a>0){
            loanList.at(i).setStatus(true);
        }
    }
}

//adds a loan to the loanlist vector
void Loans::addLoan(Loan L){loanList.push_back(L);}

//returns vector by reference for editing in other functions
vector <Loan> &Loans::getList(){return loanList;}

//prints all loans currently made at library
void Loans::printLoans() {
    for (int i = 0; i < loanList.size(); i++) {
        printLoan(loanList.at(i));
		cout<< endl;
	}
	cout << "Total number of loans: " << count << endl << endl;
}


//main loan menu
void Loans::loanMenu(Books& books, Patrons& patrons, Loans& loans, int choice, int pid, char select, int bid) {
 //menu options
	cout << "Welcome to the Loan System. Select an option:" << endl;
    cout << "0 - Checkout a Book" << endl;
    cout << "1 - Check In a Book" << endl;
    cout << "2 - Check Overdue" << endl;
    cout << "3 - Search for Loans" << endl;
    cout << "4 - Change Loan Information" << endl;
    cout << "5 - List all Loans" << endl;
    cout << "6 - Back to Main Menu" << endl;
    cin >> choice;
	
    if (!cin.fail()) {
        //begins checkout process
		if (choice == 0) {
			//after recieving a set of confirmed IDs, runs the checkout process
            while (select != 'Y' && select != 'y') {
                cout << "Please enter the Patron's ID: " << endl;
                cin >> pid;
                if (cin.fail()) break;
                cout << "Is Patron " << pid << " correct? Y/N" << endl;
                cin >> select;
                if (cin.fail()) break;
            }

            select = 'z';

            while (select != 'Y' && select != 'y') {
                cout << "Please enter the Book ID: " << endl;
                cin >> bid;
                if (cin.fail()) break;
                cout << "Is Book " << bid << " correct? Y/N" << endl;
                cin >> select;
                if (cin.fail()) break;
            }
			

            if (!cin.fail()){loans.checkOut(patrons, books, pid, bid);}
        }

        else if (choice == 1) {
			//after receiving a set of confirmed IDs, runs the checkin process
            while (select != 'Y' && select != 'y') {
                cout << "Please enter the Book ID: " << endl;
                cin >> bid;
                if (cin.fail()) break;
                cout << "Is Book " << bid << " correct? Y/N" << endl;
                cin >> select;
                if (cin.fail()) break;
            }

            if (!cin.fail()){loans.checkIn(patrons, books, bid);}
        }
		//lists all overdue books
        else if (choice == 2) { loans.listOverdue(); }

        //finds a particular loan to view its details
		else if (choice == 3) {
            cout << "Do you want to find loans by book or patron?" << endl;
            cout << "B - by book" << endl;
            cout << "P - by patron" << endl;
            cin >> select;
            if (!cin.fail()) {
				//searches loans by book id and prints the loan
                if (select == 'B' || select == 'b') {
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the Book ID: " << endl;
                        cin >> bid;
                        if (cin.fail()) break;
                        cout << "Is Book " << bid << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) break;
                    }

                    if (!cin.fail()) {
                        Loan l = loans.findLoan(bid);

                        if (l.getID() != -1) {
                            printLoan(l);
                        }

                        else cout << "No such loan exists." << endl;
                    }
                }
				//finds all loans associated with the patron and prints them
                else if (select == 'P' || select == 'p') {
                    while (select != 'Y' && select != 'y') {
                        cout << "Please enter the Patron's ID: " << endl;
                        cin >> pid;
                        if (cin.fail()) break;
                        cout << "Is Patron " << pid << " correct? Y/N" << endl;
                        cin >> select;
                        if (cin.fail()) break;
                    }

                    if (!cin.fail()) { loans.ListbyPatron(pid); }
                }

                else { cout << "Search cancelled." << endl; }
            }
        }
		//enters the loan editing menu after confirming ID
        else if (choice == 4) {
            while (select != 'Y' && select != 'y') {
                cout << "Please enter the Book ID: " << endl;
                cin >> bid;
                if (cin.fail()) break;
                cout << "Is Book " << bid << " correct? Y/N" << endl;
                cin >> select;
                if (cin.fail()) break;
            }

            if (!cin.fail()) { loans.editLoan(bid, patrons, books); }
        }
		//prints all loans at the library
        else if (choice == 5) { loans.printLoans(); }
		
		//exits loan menu
        else if (choice == 6) { cout << "Returning to main menu." << endl; }
    }
}

//prints a loan's information
void Loans::printLoan(Loan loan) {
    cout << "Patron: " << loan.getPatronID() << endl;
    cout << "Book: " << loan.getBookID() << endl;
    time_t time = loan.getDue();
    const time_t* t;
    t = &time;
    cout << "Due: " << ctime(t) << endl;
}