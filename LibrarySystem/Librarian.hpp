#pragma once
#include "User.hpp"
//deklaracja klasy Librarian dziedzicz�cej publicznie po klasie User
class Librarian: public User {
   double salary = 3000.00;//prywatne pole klasy - pensja bibliotekarza, domy�lnie ustawiona na 3000.00
   // Konstruktor z parametrami: n - nazwa u�ytkownika, e - email, passwd - has�o, s - pensja
public:
    Librarian(std::string n, std::string e, std::string passwd, double s): User(n, e, passwd) // wywo�anie konstruktora klasy bazowej (User)
    {
        salary = s;// ustawienie pola salary na warto�� przekazan� przez parametr s
        
    }
    
    Librarian() = default;//domy�lny konstruktor (tworzy obiekt z domy�lnymi warto�ciami p�l)
    ~Librarian() {}//destruktor
    
    void display_info() const override; //nadpisanie wirtualnej metody z klasy bazowej User do wy�wietlania danych bibliotekarza
};