#include <string>
#include <ctime>
using namespace std;


class Loan {
public:
static int nextID;
int  getID();
void  setID(int id);
void  setPatronID(int p);
int  getPatronID();
void  setBookID(int b);
int  getBookID();
void  setTime(time_t t);
time_t  getTime();
void  setDue (time_t t);
time_t  getDue();
void  setStatus(bool s);
bool  getStatus();
void  setRecheck(bool r);
bool  getRecheck();
void printLoan();

Loan(int pID, int bID);
Loan();

private:
int ID;
int patronID;
int bookID;
time_t checkout;
time_t due;
bool overdue;
bool recheck;
};