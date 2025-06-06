#include "User.hpp"
#include <iostream>
//wyświetlanie informacji o użytkowniku
void User::display_info() const {
    std::cout << "==========INFORMACJE O UŻYTKOWNIKU==========\n";
    std::cout << "Nazwa użytkownika: " << name << std::endl;
    std::cout << "Adres email: " << email << std::endl;
    std::cout << "Wypożyczone książki: " << books_borrowed << std::endl;
}