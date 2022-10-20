#include "loans.h"
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void Loans::checkOut(Patrons  &patrons, Books  &books, int pi, int bi){
    int i;
    int locp = 0;
    int locb = 0;
    bool fp = false;
    bool fb = false;

    for (i = 0; i<patrons.getList().size(); i++){
        if (pi == patrons.getList().at(i).getID()){
            fp = true;        
            locp=i;
            break;
        }
    }

    for (i=0; i<books.getList().size(); i++){
        if (bi = books.getList().at(i).getID()){
            fb = true;
            locb =i;
            break;}
    }

    if (fp ==true && fb == true){
        bool fail = false;
        if (patrons.getList().at(locp).getFines() != 0){ 
            cout << "Checkout failed. " << patrons.getList().at(locp).getName() << " has an outstanding balance of $" << patrons.getList().at(locp).getFines() << endl;
            fail = true;
            }

        if (patrons.getList().at(locp).getBooksOut() == 6){
            cout << "Checkout failed. " << patrons.getList().at(locp).getName() << " has too many books out." << endl;
            fail = true;
            }

        if (books.getList().at(locb).getStatus() != 0){
            cout << "Checkout failed. "<< books.getList().at(locb).getTitle() << "is currently unavailable for checkout." << endl;
            fail = true;
            }

        if (fail == false){
            Loan nLoan(pi,bi);
            loanList.push_back(nLoan);
            count = loanList.size();
            time_t time = nLoan.getDue();
            const time_t *t;
            t = &time;
            books.getList().at(locb).setStatus(1);
            patrons.getList().at(locp).setBooksOut(patrons.getList().at(locp).getBooksOut()+1); 
            cout << books.getList().at(locb).getTitle() << " checked out to " << patrons.getList().at(locp).getName() << endl;
            cout << "It is due back by: " <<  ctime(t) << endl;
            }    
    }
    
    else if (fp == false){
        cout << "Checkout failed. Patron not found. Check ID." <<endl;}
    
    else if (fb == false){
        cout << "Checkout failed. Book not found. Check ID." <<endl;}
    
    else {  
        cout << "Checkout failed. Neither book or patron found. Check IDs." << endl;}    
}


void Loans::checkIn(Patrons &patrons, Books  &books, int id){
    Loan cIn = findLoan(id);
    if (cIn.getID()!=-1){
        int i;
        for (i=0; i<books.getList().size(); i++){
            if (cIn.getBookID() == books.getList().at(i).getID()){
                books.getList().at(i).setStatus(0);
                cout << books.getList().at(i).getTitle() << "checked back in successfully." << endl;
                break;}
        }

        for (i = 0; i<patrons.getList().size(); i++){
            if (cIn.getPatronID() == patrons.getList().at(i).getID()){     
                patrons.getList().at(i).setBooksOut(patrons.getList().at(i).getBooksOut()-1);
            
                if (cIn.getStatus()){
                    int a =  ((cIn.getDue() - time(0))/(24*60*60))+1;
                    float f = a*.25;
                    patrons.getList().at(i).setFines(f);
                    cout << patrons.getList().at(i).getName() << "has a new fine balance of $" << f <<". Please pay promptly." << endl;}
                    break;}
        }

        for (i = 0; i<loanList.size(); i++){
            if (cIn.getID()==loanList.at(i).getID()){
                loanList.erase(loanList.begin()+i);
                count = loanList.size();
                break;}
        }
    }
    else{ cout << "Check in failed. Loan not found. Check ID." <<endl;}
}

Loan Loans::findLoan(int i){
    Loan notFound;
    for (int a = 0; a <loanList.size(); a++){
        if (i == loanList.at(a).getBookID()){
            return loanList.at(a);}
    }
    return notFound;
}

void Loans::listOverdue(){
    updateOverdue();
    int c = 0;
    for (int i = 0; i<loanList.size(); i++){
        if (loanList.at(i).getStatus()){
            int a = ((time(0) - loanList.at(i).getDue())/(24*60*60))+1;
            cout << "Patron: " << loanList.at(i).getPatronID() << endl;
            cout << "Book: " << loanList.at(i).getBookID() << endl;
            time_t time = loanList.at(i).getDue();
            const time_t *t;
            t = &time;
            cout << "Due: " << ctime (t) << endl;
            cout << "Overdue by " << a << "days."<< endl<< endl; 
            c++;}
    }
    cout << "Number of overdue books: " << c << endl;
}


void Loans::ListbyPatron(int pi){
    int i;
    int c=0;
    for (i=0; i<loanList.size(); i++){
        if (loanList.at(i).getPatronID()==pi){
            cout << "Book: " << loanList.at(i).getBookID()<<endl;
            time_t time = loanList.at(i).getDue();
            const time_t *t;
            t = &time;
            cout << "Due: " << ctime(t) << endl << endl;
            c++;
        }
    }
    if (c!=0){
    cout << "Patron " << pi << " has " << c << "books checked out." <<endl;}
    else {cout << "Patron " << pi << " has no books checked out." << endl;}
}

void Loans::editLoan(int id){
    Loan temp = findLoan(id);

    if (temp.getID()!=-1){
    cout << "Loan " << id << "found." << endl;
    temp.printLoan();
    editMenu(temp);
    for (int i =0; i<loanList.size(); i++){
        if (id == loanList.at(i).getID()){
            loanList.at(i) = temp;
            break;
        }
    }        
}
    else {cout << "Could not find loan. Check ID." << endl;}
}

void Loans::editMenu(Loan &L){
    int editI;
    string editS;
    char choice = 'z';
    cout << "What would you like to edit?" << endl;
    cout << "B - Book" << endl << "P - Patron" << endl << "C - Checkout Time" << endl << "D - Due Date" << endl;
    cout << "R - Recheck Status" << endl << "O - Overdue Status" << endl;
    cout << "E - Cancel Edit" <<endl;
    cout << "Choice:" << endl;
    cin >> choice;
    
    if (choice == 'B' || choice == 'b'){
        cout << "Enter the book ID:" << endl;
        cin >> editI;
        
        cout << "Is " << editI << " correct? Y/N: " << endl;
        cin >> choice;
        
        if (choice == 'Y' || choice =='y'){
            cout << editI << " set successfully." <<endl;
            L.setBookID(editI);}

        else {cout << "Book ID not updated."<<endl;}
        
        cout << "Returning to edit menu." << endl;
        editMenu(L);}

    else if (choice == 'P' || choice == 'p'){
        cout << "Enter the patron ID:" << endl;
        cin >> editI;
        cout << "Is " << editI << " correct? Y/N " << endl;
        
        if (choice == 'Y' || choice =='y'){
            cout << editI << " set successfully." <<endl;
            L.setPatronID(editI);}
            
        else {cout << "Patron ID not updated. " <<endl;}

        cout << " Returning to edit menu." <<endl;
        editMenu(L); }

    else if (choice == 'C' || choice == 'c' ){
        cout << "How would you like to change the checkout date?" << endl;
        cout << "L - Later" << endl << "A - Earlier" << endl << "N - now" << endl << "C - cancel";
        cin >> choice;
            if (choice == 'L' || choice == 'l'){
                cout << "How many days do you want to add to the checkout time?" << endl;
                cin >> editI;
                cout << "Is " << editI << " correct? Y/N " << endl;
                cin >> choice;
                if (choice == 'Y' || choice =='y'){
                    long int a = L.getTime() + (editI*24*60*60);
                    L.setTime(a);
                    L.setDue(a + (10*24*60*60));
                    cout << "Checkout and due date updated." <<endl;}
                else { cout << "Nothing updated." << endl;}
            }

            else if (choice == 'A' || choice == 'a'){
                cout << "How many days sooner was it checked out?" << endl;
                cin >> editI;
                cout << "Is " << editI << " correct? Y/N " << endl;
                cin >> choice;
                
                if (choice == 'Y' || choice =='y'){
                    long int a = L.getTime() - (editI*24*60*60);
                    L.setTime(a);
                    L.setDue(a + (10*24*60*60));
                    cout << "Checkout and due date updated." <<endl;}
                
                else { cout << "Nothing updated." << endl;}
            }

            else if (choice == 'N' || choice == 'n'){
                L.setTime(time(0));
                L.setDue(time(0)+ 10*24*60*60);
                cout << "Checkout and due date updated." <<endl;}

            else if (choice == 'C'|| choice == 'c'){
                cout << "Returning to edit menu." <<endl;
                editMenu(L);}
            
            else {
                cout << "Not a valid choice." << endl;
                cout << "Returning to edit menu." <<endl;
                editMenu(L);}
            time_t time = L.getTime();
            const time_t *t;
            t = &time;   
            cout << "New Checkout Date: " << ctime(t) << endl;
            time =L.getDue();
            cout << "New Due Date: " << ctime(t)<< endl;
            cout << " Returning to edit menu." <<endl;
            editMenu(L);}

    else if (choice == 'D' || choice == 'd' ){
        cout << "How many more days do you want to extend the due date?" << endl;
        cin >> editI;
        cout << "Is " << editI << " correct? Y/N " << endl;
        if (choice == 'Y' || choice =='y'){
            long int a = L.getDue()+ (editI*(24*60*60));
            L.setDue(a);
            time_t time = L.getDue();
            const time_t *t;
            t = &time;
            cout << "Due date updated to :" << ctime(t) << endl;
            }

        else {cout << "Due date not updated. " <<endl;}

        cout << " Returning to edit menu." <<endl;
        editMenu(L);}

    else if (choice == 'R' || choice =='r'){
        if (L.getRecheck()){
            cout << "Book has been rechecked already. Reset? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y' || choice == 'y'){
                L.setRecheck(false);
                cout << "Book can be rechecked again." << endl;}
        }
        else if (!L.getRecheck()){
            cout << "Book has not been rechecked. Is this wrong? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y' || choice == 'y'){
                L.setRecheck(false);
                cout << "Book can no longer be rechecked." << endl;}   
        }
    cout << "Returning to edit menu."<< endl;
    editMenu(L);}

    else if (choice == 'O' || choice =='o'){
        if (L.getStatus()){
            cout << "Book is overdue. To change, please update due date." << endl;
        }
        if (!L.getStatus()){
            cout << "Book is not overdue. Change? Y/N" <<endl;
            cin >> choice;
            if (choice == 'Y' || choice == 'y'){
                L.setStatus(true);
                cout << "Book now overdue. Please also update due date." <<endl;}
        }
        cout << "Returning to edit menu" << endl;
        editMenu(L);
    }
    else if (choice == 'E' || choice == 'e'){
        cout << "Returning you to main menu." << endl;}

    else{
        cout << "Selection not valid. Try again:" << endl;
        editMenu(L);
    }
}
void Loans::reportLost (int bi, int ci, vector <Patron>  &patrons, vector <Book>  &books){
    int i;
    float c=0;
    bool found = false;
    for (i = 0; i<books.size(); i++){
        if (bi == books.at(i).getID()){
            books.at(i).setStatus(3);
            c = books.at(i).getCost();
            break;}
    }
    if (c==0){
        cout << "Could not find book. Check ID." << endl;
    }

    for (i = 0; i<patrons.size(); i++)
        if (ci == patrons.at(i).getID() && c != 0 ){
            patrons.at(i).setFines(patrons.at(i).getFines() + c);
            found = true;
            for (int a = 0; a<loanList.size(); a++){
                if (bi == loanList.at(a).getBookID()){
                    loanList.erase(loanList.begin() + a);
                    count = loanList.size();
                    break;}
            break;}
        }
    if (!found){
        cout << "Could not find patron. Check ID." << endl;}
}


void Loans::reCheck(int id){
   bool found = false;
   for (int i =0; i<loanList.size(); i++){
    if (id == loanList.at(i).getID()){
        if (loanList.at(i).getRecheck()){
            cout << "Cannot recheck. Book already rechecked once." << endl;
            found = true;
            break;}

        else {
            loanList.at(i).setRecheck(true);
            time_t t= time(0)+(10*24*60*60);
            loanList.at(i).setDue(t);
            time_t time = loanList.at(i).getDue();
            const time_t *tim;
            tim = &time;
            cout << "Recheck successful. New due date is: " << ctime(tim) << endl;
            found = true;
            break;}
            }
   }
    if (!found){
        cout << "Loan not found. Could not recheck." << endl;
    }
}


void Loans::reportDamaged(int bi, int ci, vector <Patron>  &patrons, vector <Book>  &books){
    int i;
    float c=0;
    bool found = false;
    for (i = 0; i<books.size(); i++){
        if (bi == books.at(i).getID()){
            books.at(i).setStatus(2);
            c = books.at(i).getCost();
            break;}
    }
    if (c==0){
        cout << "Could not find book. Check ID." << endl;}

    for (i = 0; i<patrons.size(); i++)
        if (ci == patrons.at(i).getID() && c != 0 ){
            patrons.at(i).setFines(patrons.at(i).getFines() + c);
            found = true;
            for (int a = 0; a<loanList.size(); a++){
                if (bi == loanList.at(a).getBookID()){
                    loanList.erase(loanList.begin() + a);
                    count = loanList.size();
                    break;}
            break;}
        }
    if (!found){
        cout << "Could not find patron. Check ID." << endl;}

}

void Loans::updateOverdue(){
    int i;
    int a;
    for (i = 0; i<loanList.size(); i++){
        a = time(0) - loanList.at(i).getDue();
        if (a>0){
            loanList.at(i).setStatus(true);
        }
    }
}

void Loans::addLoan(Loan L){loanList.push_back(L);}

vector <Loan> Loans::getList(){return loanList;}