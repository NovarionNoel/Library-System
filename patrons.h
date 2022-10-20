#include "patron.h"
#include <vector>

using namespace std;
class Patrons{

public:
void addPatron(Patron P);
void editPatron();
void editMenu (Patron &P);
void deletePatron();
Patron findPatron();
void printPatron (Patron P);
void printAllPatrons();
void payFines(float i, Patron &P);
vector <Patron> getList();

private:
vector <Patron> patronList;
int count;

};