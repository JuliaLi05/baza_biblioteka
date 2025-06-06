#pragma once
#include "Book.hpp"
#include <memory>
#include <optional>
#include <vector>
#include <list>
#include <algorithm>
#include "User.hpp"

class LibrarySystem {
    std::vector<Book> book_repository;//kontener przechowuj�cy ksi��ki
    std::list<std::shared_ptr<User>> users; //lista u�ytkownik�w � przechowywanych jako wska�niki z wykorzystaniem polimorfizmu

    std::string get_password();//wczytywanie has�a z klawiatury

public:
   static void console_pause();//zatrzymanie programu do momentu wci�ni�cia Enter
   //szablon funkcji do pobierania danych dowolnego typu od u�ytkownika
   template<typename T>
   static void get_field(std::string prompt);
   //klasa z wyliczeniami - opcje wyszukiwania
   enum class SearchOption {
    BY_TITLE = 1,
    BY_AUTHOR,
    BY_ISBN,
    NONE
   };
   //deklaracje funkcji dla ksi��ek
   std::optional<Book> create_book(bool add_to_db = true);//tworzenie ksi��ki
   void remove_book(std::string isbn);//usuni�cie ksi�zki
   void update_book(std::string isbn, const Book& other);//aktualizacja ksi��ki
   void print_book(std::string isbn);//wy�wietlenie informacji o ksi��ce
   void find_book(SearchOption option, std::string& search_term);//wyszukiwanie ksi��ek po tytule, autorze lub ISBN
   void print_all_books();//wypisanie informacji o wszystkich ksi��kach
   //deklaracje funkcji dla u�ytkownik�w
   std::optional<User> create_user(bool add_to_db = true);//tworzenie u�ytkownika
   void print_all_users();//wy�wietlanie wszystkich u�ytkownik�w
   void update_user(std::string username, const User& other);//aktualizacja u�ytkownika
   void remove_user(std::string username);//usuwanie u�ytkownika
   //sprawdzenie, czy u�ytkownik o danej nazwie ju� istnieje w systemie
   bool doesUserExist(std::string username) {
    return std::find_if(users.begin(), users.end(), [username](const auto& user) {
        return user->get_username() == username;
    }) != users.end();
   }
};