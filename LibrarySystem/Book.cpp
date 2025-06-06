#include "Book.hpp"
#include <iostream>
//inicjalizacja statycznego pola count klasy Book-przechowuje liczbę utworzonych kopii obiektów Book
unsigned int Book::count = 0;
//konstruktor kopiujący klasy Book - kopiuje wszystkie pola z innego obiektu Book (other)
Book::Book(const Book& other) {
    title = other.title;
    loan_date = other.loan_date;
    year = other.year;
    author = other.author;
    isbn = other.isbn;

    count++;
}
//przeciążenie operatora <<, aby umożliwić wygodne wypisywanie obiektu Book do strumienia wyjścia 
std::ostream& operator<<(std::ostream& stream, const Book& book) {
    book.print_info(stream);// wywołanie metody print_info, która wypisuje szczegóły książki
    return stream;//zwrócenie strumienia, aby umożliwić łańcuchowe wywołania operatora <<
}

//metoda klasy Book do wypisywania informacji o książce na podany strumień wyjścia
void Book::print_info(std::ostream& out_stream) const {
    out_stream << "==========INFORMACJE O KSIĄŻCE==========\n";
    out_stream << "Tytuł: " << title << '\n';
    out_stream << "Autor: " << author << '\n';
    out_stream << "ISBN: " << isbn << '\n';
    out_stream << "Rok wydania: " << year << '\n';
    out_stream << "Data wypożyczenia: " << loan_date << '\n';
}