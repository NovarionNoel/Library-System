#include "patrons.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

void Patrons::addPatron(Patron P){patronList.push_back(P); count=patronList.size();}

void Patrons::editPatron(){
Patron P = findPatron();
if (P.getID()!=-1){
    cout << P.getName() << " found. What would you like to edit?" << endl;
    editMenu(P);
}

else {cout << "Patron was not found."<< endl;}
}

void Patrons::editMenu(Patron  &P){
    float editI;
    string editS;
    char choice = 'z';
    cout << "N - Name" << endl << "F - fines" <<endl << "E - Cancel Edit";
    cout << "Choice:" << endl;
    cin >> choice;
    
    if (choice == 'N' || choice == 'n'){
        cout << "Enter the new name:" << endl;
        getline(cin,editS);
        
        cout << "Is " << editS << " correct? Y/N: " << endl;
        cin >> choice;
        
        if (choice == 'Y' || choice =='y'){
            cout << editS << " set successfully." <<endl;
            P.setName(editS);}

        else {cout << "Name not updated."<<endl;}
        
        cout << "Returning to edit menu." << endl;
        editMenu(P);}

    else if (choice == 'F' || choice == 'F'){
        cout << "How much did was paid?" << endl;
        cin>> editI;
        cout << "Is " << editI << " correct? Y/N " << endl;
        
        if (choice == 'Y' || choice =='y'){
            cout << editI << " paid successfully." <<endl;
            payFines(editI, P);
            }
        
        else {cout << "Fines not updated. " <<endl;}

        cout << " Returning to edit menu." <<endl;
        editMenu(P); }
   
    else if (choice == 'E' || choice == 'e'){cout << "Returning you to main menu." << endl;}
    else{
        cout << "Selection not valid. Try again:" << endl;
        editMenu(P);
    }}

void Patrons::deletePatron(){
    Patron P = findPatron();
    printPatron(P);
    char choice = 'z';
    cout << "Would you like to delete this patron? Y/N"<< endl;
    cin >> choice;
    if (choice == 'Y' || choice == 'y'){
        for (int i=0; i<patronList.size(); i++){
            if (P.getID()==patronList.at(i).getID()){
                patronList.erase(patronList.begin()+i);
                break;
            }
        }
    cout << "Patron removed." <<endl;
    }
    else {cout << "Patron not removed. Returning to main menu." << endl;}
}

Patron Patrons::findPatron(){
    cout << "How would you like to find this Patron?" << endl;
    cout << "N - Name" << endl << "I - ID" << endl << "E - Exit Find"<< endl;
    char choice = 'z';
    int i;
    Patron P;
    cin >> choice;
    
    if (choice == 'N' || choice == 'n'){
        string n ="";
        cout << "Enter the name:"<<endl;
        getline(cin, n);
        for (i = 0; i<patronList.size(); i++){
            if (n == (patronList.at(i).getName()))
            {return patronList.at(i);}
         else {return P;}}
    }

    else if (choice == 'I' || choice == 'i'){
        cout << "Enter the ID:"<<endl;
        int id;
        cin >> id;
        for (i = 0; i< patronList.size(); i++){
            if (id == patronList.at(i).getID()){return patronList.at(i);}
            else{return P;}
        }
    }
    else if (choice == 'E' || choice == 'e' ){cout << "Returning to main menu." << endl;}
    else { cout << "Selection not valid. Try again:"<<endl;
    findPatron();}
    return P;
}

void Patrons::printPatron (Patron P){
  cout << "Name: "<< P.getName()<<endl;
  cout << "ID: " << P.getID()<< endl;
  cout << "Fines: $" << P.getFines() << endl;
  cout << "Books Out: " << P.getBooksOut()<<endl; 
}

void Patrons::printAllPatrons(){
    for (int i =0; i<patronList.size(); i++){
        printPatron(patronList.at(i));
    }
}

void  Patrons::payFines(float i, Patron  &P){P.setFines(P.getFines()-i);}

vector <Patron> Patrons::getList(){return patronList;}


