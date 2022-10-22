#include "patrons.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//adds a patron to the patronList vector
void Patrons::addPatron(Patron P){patronList.push_back(P); count=patronList.size();}


//calls the recursive edit menu function to allow patron editing after confirming a valid id
void Patrons::editPatron(){
    //returns a copy of the patron and runs the menu if find successful
    Patron P = findPatron();
    
    if (P.getID()!=-1){
        cout << P.getName() << " found. What would you like to edit?" << endl;
        editMenu(P);
    }

    else {cout << "Patron was not found."<< endl;}
}

//menu and options for editing a given patron's information
void Patrons::editMenu(Patron  &P){
    float editI;
    string editS;
    char choice = 'z';
	//menu options
    cout << "N - Name" << endl << "F - Fines" <<endl << "E - Cancel Edit"<< endl;
    cout << "Choice:" << endl;
    cin >> choice;
    int locp = -1;
	//finds the patron's actual location
    for (int i = 0; i < patronList.size(); i++) {
        if (P.getID() == patronList.at(i).getID()) {
            locp = i;
            break;
        }
    }
	
    if (!cin.fail()) {
		//lets a patron's name be changed. marriage, name changes, typos, etc 
        if (choice == 'N' || choice == 'n') {
            cout << "Enter the new name:" << endl;
            cin.ignore();
            getline(cin, editS);
            if (!cin.fail()) {
                cout << "Is " << editS << " correct? Y/N: " << endl;
                cin >> choice;
            

				if (!cin.fail() && (choice == 'Y' || choice == 'y')) {
					cout << editS << " set successfully." << endl;
					patronList.at(locp).setName(editS);
				}
			}
            else { cout << "Name not updated." << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(P);
        }

        //lets a patron pay fines after confirmation
		else if (choice == 'F' || choice == 'f') {
            cout << "How much was paid?" << endl;
            cin >> editI;
            if (!cin.fail()) {
                cout << "Is " << editI << " correct? Y/N " << endl;
                cin >> choice;
            
				if (!cin.fail() && (choice == 'Y' || choice == 'y')){
					cout << editI << " paid successfully." << endl;
					payFines(editI, patronList.at(locp));
				}
				else { cout << "Fines not updated. " << endl; }
			}
            else { cout << "Fines not updated. " << endl; }

            cout << "Returning to edit menu." << endl;
            editMenu(P);
        }
		//exits back to main menu
        else if (choice == 'E' || choice == 'e') { cout << "Returning you to main menu." << endl; }
		
		//attempts to retrieve a valid selection
		else {
		cout << "Selection not valid. Try again:" << endl;
        editMenu(P);
		}
    }
	//attempts to retrieve a valid selection
	else {
        cout << "Selection not valid. Try again:" << endl;
        editMenu(P);
    }
    
}

//removes a patron after a successful  confirmation
void Patrons::deletePatron(){
    Patron P = findPatron();
    if (P.getID() != -1) { printPatron(P); 
		//if found, proceeds through the delete after confirmation
		char choice = 'z';
		cout << "Would you like to delete this patron? Y/N"<< endl;
		cin >> choice;
		if (!cin.fail()){
			if (choice == 'Y' || choice == 'y'&&P.getBooksOut()==0){
				for (int i=0; i<patronList.size(); i++){
					if (P.getID()==patronList.at(i).getID()){
						patronList.erase(patronList.begin()+i);
						break;
					}
				}
			cout << "Patron removed." <<endl;
			}
			else if (P.getBooksOut()>0){
				cout << "Patron cannot be removed. Still has a book checked out." << endl;
			}
			else {cout << "Patron not removed. Returning to main menu." << endl;}
		}
		else {cout << "Patron not removed. Returning to main menu." << endl;}
	}
	else {cout << "Patron not found. Check ID." << endl;}
}
//performs a find either by name or ID until user exits or successful find is performed
Patron Patrons::findPatron(){
    cout << "How would you like to find this Patron?" << endl;
	//choices to find patron
    cout << "N - Name" << endl << "I - ID" << endl << "E - Exit Find"<< endl;
    char choice = 'z';
    int i;
    Patron P;
    cin >> choice;
    if (!cin.fail()) {
		//begins search by name
        if (choice == 'N' || choice == 'n') {
            string n = "";
            cout << "Enter the name:" << endl;
            cin.ignore();
            getline(cin, n);
            if (!cin.fail()) {
                for (i = 0; i < patronList.size(); i++) {
                    if (n.compare(patronList.at(i).getName()) == 0) { 
                        return patronList.at(i); 
                    }
                }
            }
        }
		//begins search by ID
        else if (choice == 'I' || choice == 'i') {
            cout << "Enter the ID:" << endl;
            int id;
            cin >> id;
            if (!cin.fail()) {
                for (i = 0; i < patronList.size(); i++) {
                    if (id == patronList.at(i).getID()) {
                        return patronList.at(i);
                    }
                }
            }
			cout << "Selection not valid. Try again:" << endl;
			findPatron();
        }

        else if (choice == 'E' || choice == 'e') { 
			cout << "Returning to main menu." << endl; 
			return P;
		}
        else {
            cout << "Selection not valid. Try again:" << endl;
            findPatron();
        }
    }
	else {
		cout << "Selection not valid. Try again:" << endl;
        findPatron();
    }
	//catches edge cases
    return P;
}

//prints a patron's information
void Patrons::printPatron (Patron P){
  cout << "Name: "<< P.getName()<<endl;
  cout << "ID: " << P.getID()<< endl;
  cout << "Fines: $" << P.getFines() << endl;
  cout << "Books Out: " << P.getBooksOut()<<endl<<endl; 
}

//prints a list of all current patrons
void Patrons::printAllPatrons(){
    for (int i =0; i<patronList.size(); i++){
        printPatron(patronList.at(i));
    }
}

//pays fines of a patron
void  Patrons::payFines(float i, Patron  &P){P.setFines(P.getFines()-i);}

//returns patronList by reference for editing in other functions
vector <Patron> &Patrons::getList(){return patronList;}
