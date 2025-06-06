#pragma once
#include <ostream>
#include <string>

class Book {
    static unsigned int count;// statyczny licznik obiekt�w klasy Book (ile ksi��ek aktualnie istnieje w bazie danych)
    std::string title;
    std::string loan_date;
    std::string author;
    unsigned short year;
    std::string isbn;

public:
    // Konstruktor parametr�w - inicjalizuje pola ksi��ki i zwi�ksza licznik obiekt�w
    Book(std::string t, std::string l, std::string a, unsigned short y, std::string i) {
        title = t;
        loan_date = l;
        author = a;
        year = y;
        isbn = i;

        count++;// zwi�kszenie licznika ksi��ek
    }
    
    Book() = default;//domy�lny konstruktor
    
    Book(const Book& other);//konstruktor kopiuj�cy - tworzy nowy obiekt na podstawie innego

    ~Book() {
        count--;
    }//destruktor - zmniejsza licznik ksi��ek przy usuwaniu obiektu

    void print_info(std::ostream& out_stream) const;//metoda do wy�wietlania informacji o ksi��ce na podany strumie� wyj�ciowy

    friend std::ostream& operator<<(std::ostream& out_stream, const Book& book);//przeci��ony operator << umo�liwia wypisywanie ksi��ki do strumienia (np. cout)

    friend class LibrarySystem;// Klasa LibrarySystem jest zadeklarowana jako "przyjaciel", dzi�ki czemu ma dost�p do prywatnych p�l klasy Book
};