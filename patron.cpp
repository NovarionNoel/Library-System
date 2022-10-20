#include "patron.h"
#include <string>
using namespace std;

//accessors and mutators
void Patron::setName(string n){name = n;}
string Patron::getName(){return name;}

int  Patron::getID(){return ID;}
void  Patron::setID(int id){ID=id;}

void  Patron::setFines(float f){fines = f;}
float  Patron::getFines(){return fines;}

void Patron::setBooksOut(int b){booksOut= b;}
int  Patron::getBooksOut(){return booksOut;}

int Patron::nextID=100000;

//default constructor
Patron::Patron(){
        ID = -1;
        booksOut=0;
        fines=0;
        name = "na";}

//parameterized constructor
Patron::Patron(string n){
        name = n;
        ID = nextID;
        booksOut = 0; 
        fines =0;
        ++nextID;}