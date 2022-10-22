#include <vector>
#include "patrons.h"
#include "books.h"
#include "loan.h"


using namespace std;
class Loans{
	public:
		void checkOut(Patrons &patrons, Books &books, int pi, int bi);
		void checkIn(Patrons &patrons, Books &books, int id);
		Loan findLoan(int id);
		void listOverdue();
		void ListbyPatron(int pi);
		void editLoan(int id, Patrons &patrons, Books &books);
		void editMenu (Loan &L, Patrons &patrons, Books &books);
		void reportLost (int bi, int ci, vector <Patron> &patrons, vector <Book>  &books);
		void reCheck(int id);
		void reportDamaged(int bi, int ci, vector <Patron> &patrons, vector <Book>  &books);
		void updateOverdue();
		void addLoan(Loan L);
		void loanMenu(Books &books, Patrons &patrons, Loans &loans,int choice, int pid, char select, int bid);
		void printLoans();
		vector <Loan> &getList();
		void printLoan(Loan loan);


	private:
		vector <Loan> loanList;
		int count;

};