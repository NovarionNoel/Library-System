#include "loans.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void saveFiles(Books books, Patrons patrons, Loans loans){
    ofstream bstream("books.dat", ofstream::trunc);
    ofstream lstream("loans.dat", ofstream::trunc);
    ofstream pstream("patrons.dat", ofstream::trunc);

    int i;

    for (i=0; i<books.getList().size(); i++){
        bstream << books.getList().at(i).getTitle() << ';' ;
        bstream << books.getList().at(i).getAuthor() << ';' ;
        bstream << books.getList().at(i).getISBN() << ';';
        bstream << books.getList().at(i).getID() << ';';
        bstream << books.getList().at(i).getCost() << ';';
        bstream << books.getList().at(i).getStatus() << endl;
    }

    for (i=0; i<loans.getList().size(); i++){
        
        lstream << loans.getList().at(i).getID() << ';' ;
        lstream << loans.getList().at(i).getPatronID() << ';' ;
        lstream << loans.getList().at(i).getBookID() << ';';
        lstream << loans.getList().at(i).getTime() << ';';
        lstream << loans.getList().at(i).getDue() << ';';

        if (loans.getList().at(i).getStatus()){lstream << "true;";}
        else{lstream << "false;";}

        if (loans.getList().at(i).getRecheck()){lstream<<"true";}
        else{lstream << "false";}
        
        lstream<<endl;   
    }

    for (i=0; i<patrons.getList().size(); i++){
        pstream << patrons.getList().at(i).getName() << ';' ;
        pstream << patrons.getList().at(i).getID() << ';' ;
        pstream << patrons.getList().at(i).getFines() << ';';
        pstream << patrons.getList().at(i).getBooksOut() << endl; 
    }

}


void printMenu(){
    cout << "Select an option:" << endl;
    cout << "0 - Loan System (Check In, Checkout, Overdue)" << endl;
    cout << "1 - Patrons (Add, remove, edit, pay fines)" << endl;
    cout << "2 - Books (Add, remove, update status)" << endl;
    cout << "9 - Exit" << endl;
}



void mainMenu(int choice, Books  &books, Patrons &patrons, Loans &loans){
    string info;
    char select = 'z';
    int bid;
    int pid;
    float costs;

    switch(choice){
        case 0:
            cout << "Welcome to the Loan System. Select an option:" << endl;
            cout << "0 - Checkout a Book" << endl;
            cout << "1 - Check In a Book" << endl;   
            cout << "2 - Check Overdue" << endl;
            cout << "3 - Search for Loans" << endl;
            cout << "4 - Change Loan Information" << endl;
            cout << "5 - Back to Main Menu" << endl;
            cin >> choice;
            
       
                if (choice == 0){
                    while (select !='Y' && select !='y'){
                        cout << "Please enter the Patron's ID: " << endl;
                        cin >> pid;
                        cout << "Is Patron " << pid << " correct? Y/N" << endl;
                        cin >> select;
                    }
                    
                    select = 'z';
                        
                    while (select!='Y' && select!='y'){
                        cout << "Please enter the Book ID: " <<endl;
                        cin >> bid;
                        cout << "Is Book " << bid << " correct? Y/N" << endl;
                        cin>> select;
                    }
                   
                    loans.checkOut(patrons, books,pid, bid);    
                }
                else if (choice == 1){
                    while (select!='Y' && select !='y'){
                        cout << "Please enter the Book ID: " << endl;
                        cin >> bid;
                        cout << "Is Book" << bid << " correct? Y/N" << endl;
                        cin>>select;
                    }
                
                    loans.checkIn(patrons, books, bid);
                }
                
                else if (choice == 2){
                    loans.listOverdue();
                    break;
                }
                else if (choice == 3){
                    cout << "Do you want to find loans by book or patron?" << endl;
                    cout << "B - by book" << endl;
                    cout << "P - by patron" << endl;
                    cin >> select;

                    if (select == 'B' || select == 'b'){
                        while (select!='Y' && select !='y'){
                            cout << "Please enter the Book ID: " << endl;
                            cin >> bid;
                            cout << "Is Book" << bid << " correct? Y/N" << endl;
                            cin>>select;
                        }
                        
                        loans.editLoan(bid);
                    }

                    else if (select == 'P' || select == 'p'){
                        while (select!='Y' && select !='y'){
                            cout << "Please enter the Patron's ID: " << endl;
                            cin >> pid;
                            cout << "Is Patron " << pid << " correct? Y/N" << endl;
                            cin >> select;
                        }
                        
                        loans.ListbyPatron(pid);
                    }

                    else{ cout << "Search cancelled." << endl;}
                }

                    else if (choice == 4){
                            while (select!='Y' && select !='y'){
                            cout << "Please enter the Book ID: " << endl;
                            cin >> bid;
                            cout << "Is Book" << bid << " correct? Y/N" << endl;
                            cin>>select;
                        }
                        
                        loans.editLoan(bid);   
                    }

                    else if (choice == 5){
                        cout << "Returning to main menu." << endl;
                    }                   
            
        break;
    
        case 1:
            cout << "Welcome to the Patron system. Select an option:" <<endl;
            cout << "0 - Add Patron" << endl;
            cout << "1 - Update Patron or Pay Fines" << endl;
            cout << "2 - Remove a Patron." << endl;
            cout << "3 - Back to Main Menu." <<endl;
            cin >> choice;
          
                if (choice == 0){
                    while(select!= 'Y' && select!='y'){
                        cout << "Please enter the Patron's Name" << endl;
                        getline(cin, info);
                        cout << "Is " << info << " correct? Y/N" << endl;
                        cin >> select;
                    }

                        Patron temp(info);
                        patrons.addPatron(temp);
                }

                else if (choice == 1){patrons.editPatron();}
    
                else if (choice == 2){patrons.deletePatron();}
                
                else if (choice == 3){cout << "Returning to main menu." << endl;}
            

            break;
        
        case 2:
            cout << "Welcome to the Book System. Select an option:" << endl;
            cout << "0 - Add a Book" << endl;
            cout << "1 - Report Lost" << endl;
            cout << "2 - Report Damaged" << endl;
            cout << "3 - Remove a Book" << endl;
            cout << "4 - Update Book Information" << endl;
            cout << "5 - Return to Main Menu" << endl;
            cin >> choice;
           
            if (choice == 0){
                    Book temp;
                    while (select != 'Y' && select != 'y'){
                        cout << "Please enter the book title:"<< endl;
                        std::getline(cin, info);
                        cout << "Is " << info << " correct? Y/N" << endl;
                        cin >> select;     
                    }
                    
                    temp.setTitle(info);
                    select = 'z';
                    
                    while(select != 'Y' && select != 'y'){
                        cout << "Please enter the author's name:" << endl;
                        std::getline(cin, info);
                        cout << "Is " << info << " correct? Y/N" << endl;
                        cin >> select;
                    }

                    temp.setAuthor(info);
                    select = 'z';

                    while(select != 'Y' && select != 'y'){  
                        cout << "Please enter the ISBN (13 preferred):" << endl;
                        cin >> bid;
                        cout << "Is " << bid << " correct?";
                        cin >> select;
                    }

                    temp.setISBN(bid);
                    select = 'z';

                    while(select != 'Y' && select != 'y'){ 
                        cout << "Please enter the cost:" << endl;
                        cin >> costs;
                        cout << "Is $"<< costs << " correct? Y/N" << endl;
                        cin >> select;
                    }
                    
                    Book added(temp.getAuthor(), temp.getTitle(), temp.getISBN(), temp.getCost());
                    books.addBook(added);
            }
            else if (choice ==1){
                while (select!='Y' && select !='y'){
                    cout << "Please enter the Book ID: " << endl;
                    cin >> bid;
                    cout << "Is Book" << bid << " correct? Y/N" << endl;
                    cin>>select;
                }
                select = 'z';
                while (select!='Y' && select !='y'){
                    cout << "Please enter the Patron ID: " << endl;
                    cin >> pid;
                    cout << "Is Patron" << pid << " correct? Y/N" << endl;
                    cin>>select;
                        }
                vector <Patron> p = patrons.getList();
                vector <Book> b = books.getList();
                loans.reportLost(bid,pid,p, b);
                        
            }
            else if (choice == 2){
                while (select!='Y' && select !='y'){
                    cout << "Please enter the Book ID: " << endl;
                    cin >> bid;
                    cout << "Is Book" << bid << " correct? Y/N" << endl;
                    cin>>select;
                }
                select = 'z';
                while (select!='Y' && select !='y'){
                    cout << "Please enter the Patron ID: " << endl;
                    cin >> pid;
                    cout << "Is Patron" << pid << " correct? Y/N" << endl;
                    cin>>select;
                }
                vector <Patron> p = patrons.getList();
                vector <Book> b = books.getList();
                loans.reportDamaged(bid,pid,p,b);
            }
            else if (choice == 3){
                while (select!='Y' && select !='y'){
                    cout << "Please enter the Book ID: " << endl;
                    cin >> bid;
                    cout << "Is Book" << bid << " correct? Y/N" << endl;
                    cin>>select;
                }
                books.deleteBook(bid);
            }
            else if (choice == 4){ 
                while (select!='Y' && select !='y'){
                    cout << "Please enter the Book ID: " << endl;
                    cin >> bid;
                    cout << "Is Book" << bid << " correct? Y/N" << endl;
                    cin>>select;
                }
                books.editBook(bid);
            }
            else if (choice == 5){cout << "Returning to main menu." << endl;}
                
                    
        break;
        
        case 3: break;
        
        case 4: break;
        
        case 5: break;
        
        case 6: break;
        
        case 7: break;
        
        case 8: break;
        
        case 9:
            cout << "Shutting down." << endl;
    }    

}

void openFiles(Books  &books, Patrons &patrons, Loans  &loans){
    ifstream bstream("books.dat", ios::in);
    ifstream pstream("patrons.dat", ios::in);
    ifstream lstream("loans.dat", ios::in);
    string input;

    if(bstream.is_open()){
        while(!bstream.eof()){
            Book temp;

            getline(bstream,input, ';');
            if(input.compare("")==0)break;
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

    if (pstream.is_open()){
        while(!pstream.eof()){
            Patron temp;
            
            getline(pstream,input, ';');
            if(input.compare("")==0)break;
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

    if (lstream.is_open()){
        while(!lstream.eof()){
            Loan temp;

            getline(lstream, input, ';');
            if(input.compare("")==0)break;
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



int main(){
    Books books;
    Patrons patrons;
    Loans loans;
    
    vector <Patron> p;
    vector <Book> b;
    vector <Loan> l;

    openFiles(books, patrons, loans);
    
    b=books.getList();
    p=patrons.getList();
    l=loans.getList();
    
    if (b.size()>0){
        int a;
        a= b.at(b.size()-1).getID()+1;
        Book::nextID= a;
    }
    
    if (p.size()>0){
        int a;
        a= p.at(p.size()-1).getID()+1;
        Patron::nextID= a;
    }
    
    if (l.size()>0){
        int a;
        a= l.at(l.size()-1).getID()+1;
        Loan::nextID= a;
    }
    int choice = -1;
    cout << "Welcome to the Library System. You may choose 9 from any menu to exit the program." << endl;
    while (choice !=9){
        printMenu();
        cin >> choice;
        mainMenu(choice,books,patrons,loans);
    }
    saveFiles(books,patrons,loans);
}