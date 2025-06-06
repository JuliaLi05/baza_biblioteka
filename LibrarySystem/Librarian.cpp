#include "Librarian.hpp"
#include "User.hpp"
#include <iostream>
//wyświetlanie informacji o bibliotekarzu
void Librarian::display_info() const {
    User::display_info();
    std::cout << "Rola: Bibliotekarz/Bibliotekarka\n";
    std::cout << "Pensja: " << salary << "zł\n";
}