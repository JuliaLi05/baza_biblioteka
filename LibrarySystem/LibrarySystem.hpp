#pragma once
#include "Book.hpp"
#include <memory>
#include <optional>
#include <vector>
#include <list>
#include <algorithm>
#include "User.hpp"

class LibrarySystem {
    std::vector<Book> book_repository;//kontener przechowuj¹cy ksi¹¿ki
    std::list<std::shared_ptr<User>> users; //lista u¿ytkowników – przechowywanych jako wskaŸniki z wykorzystaniem polimorfizmu

    std::string get_password();//wczytywanie has³a z klawiatury

public:
   static void console_pause();//zatrzymanie programu do momentu wciœniêcia Enter
   //szablon funkcji do pobierania danych dowolnego typu od u¿ytkownika
   template<typename T>
   static void get_field(std::string prompt);
   //klasa z wyliczeniami - opcje wyszukiwania
   enum class SearchOption {
    BY_TITLE = 1,
    BY_AUTHOR,
    BY_ISBN,
    NONE
   };
   //deklaracje funkcji dla ksi¹¿ek
   std::optional<Book> create_book(bool add_to_db = true);//tworzenie ksi¹¿ki
   void remove_book(std::string isbn);//usuniêcie ksi¹zki
   void update_book(std::string isbn, const Book& other);//aktualizacja ksi¹¿ki
   void print_book(std::string isbn);//wyœwietlenie informacji o ksi¹¿ce
   void find_book(SearchOption option, std::string& search_term);//wyszukiwanie ksi¹¿ek po tytule, autorze lub ISBN
   void print_all_books();//wypisanie informacji o wszystkich ksi¹¿kach
   //deklaracje funkcji dla u¿ytkowników
   std::optional<User> create_user(bool add_to_db = true);//tworzenie u¿ytkownika
   void print_all_users();//wyœwietlanie wszystkich u¿ytkowników
   void update_user(std::string username, const User& other);//aktualizacja u¿ytkownika
   void remove_user(std::string username);//usuwanie u¿ytkownika
   //sprawdzenie, czy u¿ytkownik o danej nazwie ju¿ istnieje w systemie
   bool doesUserExist(std::string username) {
    return std::find_if(users.begin(), users.end(), [username](const auto& user) {
        return user->get_username() == username;
    }) != users.end();
   }
};