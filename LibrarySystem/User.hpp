#pragma once
#include "LibraryMember.hpp"
//deklaracja klasy User dziedzicz¹cej publicznie po klasie LibraryMember
class User: public LibraryMember {
    
    unsigned int books_borrowed;//prywatne pole klasy - liczba wypo¿yczonych przez u¿ytkownika ksi¹¿ek
    // wywo³anie konstruktora klasy bazowej (LibraryMember)
public:
    User(std::string n, std::string e, std::string passwd):
    LibraryMember(n, e, passwd) 
    {}

    User() = default;//domyœlny konstruktor
    ~User() {}//destruktor
    virtual void display_info() const override;// wirtualna metoda nadpisuj¹ca metodê z klasy bazowej - umo¿liwia polimorficzne wyœwietlanie danych u¿ytkownika
    
    std::string get_username() const {
        return name;
    }//getter zwracaj¹cy nazwê u¿ytkownika
    
    User(const User& other) = default;// Konstruktor kopiuj¹cy – domyœlny, automatycznie kopiuje wszystkie pola
};