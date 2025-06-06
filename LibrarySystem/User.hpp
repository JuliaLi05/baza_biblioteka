#pragma once
#include "LibraryMember.hpp"
//deklaracja klasy User dziedzicz�cej publicznie po klasie LibraryMember
class User: public LibraryMember {
    
    unsigned int books_borrowed;//prywatne pole klasy - liczba wypo�yczonych przez u�ytkownika ksi��ek
    // wywo�anie konstruktora klasy bazowej (LibraryMember)
public:
    User(std::string n, std::string e, std::string passwd):
    LibraryMember(n, e, passwd) 
    {}

    User() = default;//domy�lny konstruktor
    ~User() {}//destruktor
    virtual void display_info() const override;// wirtualna metoda nadpisuj�ca metod� z klasy bazowej - umo�liwia polimorficzne wy�wietlanie danych u�ytkownika
    
    std::string get_username() const {
        return name;
    }//getter zwracaj�cy nazw� u�ytkownika
    
    User(const User& other) = default;// Konstruktor kopiuj�cy � domy�lny, automatycznie kopiuje wszystkie pola
};