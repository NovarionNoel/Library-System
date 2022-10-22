#include <vector>
#include "book.h"
using namespace std;

class Books{
	public:
		void addBook(Book b);
		void deleteBook(int i);
		void editBook(int i);
		Book findBook(int i);
		void PrintBook(Book b);
		void PrintBooks();
		void editMenu(Book &b);
		vector <Book>& getList();
		Books();

	private:
		vector <Book> bookList;
		int count;
};