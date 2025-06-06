#pragma once
#include <ostream>
#include <string>

class Book {
    static unsigned int count;// statyczny licznik obiektów klasy Book (ile ksi¹¿ek aktualnie istnieje w bazie danych)
    std::string title;
    std::string loan_date;
    std::string author;
    unsigned short year;
    std::string isbn;

public:
    // Konstruktor parametrów - inicjalizuje pola ksi¹¿ki i zwiêksza licznik obiektów
    Book(std::string t, std::string l, std::string a, unsigned short y, std::string i) {
        title = t;
        loan_date = l;
        author = a;
        year = y;
        isbn = i;

        count++;// zwiêkszenie licznika ksi¹¿ek
    }
    
    Book() = default;//domyœlny konstruktor
    
    Book(const Book& other);//konstruktor kopiuj¹cy - tworzy nowy obiekt na podstawie innego

    ~Book() {
        count--;
    }//destruktor - zmniejsza licznik ksi¹¿ek przy usuwaniu obiektu

    void print_info(std::ostream& out_stream) const;//metoda do wyœwietlania informacji o ksi¹¿ce na podany strumieñ wyjœciowy

    friend std::ostream& operator<<(std::ostream& out_stream, const Book& book);//przeci¹¿ony operator << umo¿liwia wypisywanie ksi¹¿ki do strumienia (np. cout)

    friend class LibrarySystem;// Klasa LibrarySystem jest zadeklarowana jako "przyjaciel", dziêki czemu ma dostêp do prywatnych pól klasy Book
};