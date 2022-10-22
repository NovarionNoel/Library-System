#include "loan.h"
#include <ctime>
#include <iostream>
using namespace std;

//accessors and mutators
int  Loan::getID(){return ID;}
void  Loan::setID(int id){ID=id;}

void  Loan::setPatronID(int p){patronID=p;}
int  Loan::getPatronID(){return patronID;}

void  Loan::setBookID(int b){bookID=b;}
int  Loan::getBookID(){return bookID;}

void  Loan::setTime(time_t t){checkout = t;}
time_t  Loan::getTime(){return checkout;}

void   Loan::setDue(time_t t){due = t;}
time_t  Loan::getDue(){return due;}

void  Loan::setStatus(bool s){overdue = s;}
bool  Loan::getStatus(){return overdue;}

void  Loan::setRecheck(bool r){recheck = r;}
bool  Loan::getRecheck(){return recheck;}

int Loan::nextID =100000;

//default constructor
Loan::Loan(){
    patronID = -1;
    bookID  = -1;
    ID = -1;
    checkout = time(0);
    due= time(0)+(10*24*60*60);
    recheck = false;
    overdue = false;
}

//parameterized constructor
Loan::Loan(int pID, int bID){
    patronID=pID;
    bookID = bID;
    ID = nextID;
    nextID++;
    checkout = time(0);
    due = time(0)+(10*24*60*60);
    recheck =false;
    overdue = false;
}

