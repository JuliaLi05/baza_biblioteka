#pragma once
#include "User.hpp"
//deklaracja klasy Librarian dziedzicz¹cej publicznie po klasie User
class Librarian: public User {
   double salary = 3000.00;//prywatne pole klasy - pensja bibliotekarza, domyœlnie ustawiona na 3000.00
   // Konstruktor z parametrami: n - nazwa u¿ytkownika, e - email, passwd - has³o, s - pensja
public:
    Librarian(std::string n, std::string e, std::string passwd, double s): User(n, e, passwd) // wywo³anie konstruktora klasy bazowej (User)
    {
        salary = s;// ustawienie pola salary na wartoœæ przekazan¹ przez parametr s
        
    }
    
    Librarian() = default;//domyœlny konstruktor (tworzy obiekt z domyœlnymi wartoœciami pól)
    ~Librarian() {}//destruktor
    
    void display_info() const override; //nadpisanie wirtualnej metody z klasy bazowej User do wyœwietlania danych bibliotekarza
};