#include <string>
using namespace std;


class Book {
    private:
        string author;
        string title;
        long long int ISBN;
        int ID;
        float cost;
        enum status{in,out,repair,lost};
        status stat;
    
    public:
        static int nextID;  
        void  setAuthor(string a);
        string  getAuthor();
        void  setTitle( string t);
        string  getTitle();
        void  setISBN(long long int i);
        long long int  getISBN();
        int  getID();
        void  setID( int id);
        void  setCost( float c);
        float  getCost();
        void  setStatus(int s);
        int getStatus();
        Book();
        Book(string a, string t, long long int i, float c);
};