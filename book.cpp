#include <string>
#include "book.h"
using namespace std;

int Book::nextID=100000;
// accessors and mutators
void Book::setAuthor(string a){author = a;}
string Book::getAuthor(){return author;}

void Book::setTitle(string t){title = t;}
string Book::getTitle(){return title;}

void Book::setISBN(long long int i){ISBN=i;}
long long int Book::getISBN(){return ISBN;}

int Book::getID(){return ID;}
void Book::setID( int id){ID=id;}

void Book::setCost( float c){cost=c;}
float Book::getCost(){return cost;}

void Book::setStatus(int s){stat = static_cast <status> (s);}
int Book::getStatus(){return stat;}

//default constructor
Book::Book(){
    author = "na";
    title = "na";
    ISBN= -1;
    cost= -1;
    ID = -1;
    stat = in;
}

//parameterized constructor
Book::Book(string a, string t, long long int i, float c){
author = a;
title = t;
ISBN = i;
cost = c;
ID=nextID;
stat = in;
++nextID;
}