#include <string> 
using namespace std;

class Patron {
    public:
    static int nextID;
    void  setName(string n);
    string getName();
    int getID();
    void setID(int id);
    void setFines(float f);
    float getFines();
    void setBooksOut(int b);
    int getBooksOut();
    Patron();
    Patron(string n);
   
    private:
    string name;
    int ID;
    float fines;
    int booksOut;

    };