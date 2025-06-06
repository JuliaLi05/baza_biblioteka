//program napisamy w standardzie C++20 - jest to baza danych do zarządzania biblioteką
#include "LibrarySystem.hpp"
#include "User.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

//klasa z wyliczeniami - opcje menu
enum class MenuChoice {
    CREATE_BOOK = 1,
    LIST_BOOKS,
    FIND_BOOK,
    CREATE_USER,
    LIST_USERS,
    UPDATE_USER,
    DELETE_USER,
    UPDATE_BOOK,
    DELETE_BOOK,
    EXIT,
};

//deklaracje funkcji pomocniczych
void display_menu(); 
inline void flush_stream();
inline void clear_screen();
LibrarySystem::SearchOption choose_search_criteria();


int main() {
    //ustawienie kodowania konsoli na UTF-8 (tylko dla Windows)
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    //wyświetlenie menu głównego
    display_menu();
    return 0;
}
//czyszczenie buforu wejściowego po użyciu cin
inline void flush_stream() {
    std::cin.ignore();
}
//uzależnione od systemu czyszczenie ekranu konsoli
inline void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef __unix__
        system("clear");
    #endif
}

//funkcja wyświetlająca i obsługująca główne menu
void display_menu() {
    MenuChoice choice;//przechowywanie wybranej opcji menu
    int int_choice = 0;//zmienna przechowywująca wartość wprowadzoną przez użytkownika do wyboru opcji w menu
    LibrarySystem system;//obiekt systemu bibliotecznego
    std::string username;//nazwa użytkownika
    std::string isbn;//numer isbn
    std::optional<User> potential_user;//warunkowa obsługa tworzenia użytkownika
    std::optional<Book> potential_book;//warunkowa obsługa tworzenia książki

    do {
        //wyświetlanie menu
        clear_screen();
        std::cout << "==========MENU==========\n";
        std::cout << "1. Dodaj książkę\n";
        std::cout << "2. Lista książek\n";
        std::cout << "3. Wyszukaj książkę\n";
        std::cout << "4. Rejestracja użytkownika\n";
        std::cout << "5. Lista użytkowników\n";
        std::cout << "6. Aktualizacja użytkownika\n";
        std::cout << "7. Usuń użytkownika\n";
        std::cout << "8. Zaktualizuj książkę\n";
        std::cout << "9. Usuń książkę\n";
        std::cout << "10. Wyjdź\n";
        std::cout << "Wybór: ";
        std::cin >> int_choice;
        //przechowywanie wybranej opcji menu
        choice = static_cast<MenuChoice>(int_choice);
        flush_stream();
        clear_screen();
        //zmienna służąca do przechowywania wybranego przez użytkownika kryterium wyszukiwania książki
        LibrarySystem::SearchOption search_option;
        switch(choice) {
            case MenuChoice::CREATE_BOOK:
                system.create_book();//tworzenie książki
                break;
            case MenuChoice::LIST_BOOKS:
                system.print_all_books();//lista książek
                break;
            case MenuChoice::CREATE_USER:
                system.create_user();//tworzenie użytkownika
                break;
            case MenuChoice::LIST_USERS:
                system.print_all_users();//lista użytkowników
                break;
            case MenuChoice::FIND_BOOK:
                search_option = choose_search_criteria();//przypisanie kryterium wyszukiwania
                if (search_option != LibrarySystem::SearchOption::NONE) {
                    std::cout << "Podaj frazę do wyszukania: ";
                    std::string search_term;
                    std::getline(std::cin, search_term); //odczytanie linii tekstu wpisanej przez użytkownika jako frazę wyszukiwania
                   system.find_book(search_option, search_term);//szukanie książki - metoda find_book klasy LibrarySystem
                }
            break;
            case MenuChoice::UPDATE_USER:
                std::cout << "Podaj nazwę użytkownika do zmiany: ";
                std::getline(std::cin, username);//odczytanie linii tekstu - nazwy użytkownika
                //próba utworzenia nowego obiektu użytkownika, ale bez dodawania go od razu do bazy danych (flaga false)
                potential_user = system.create_user(false);
                if (!potential_user.has_value())
                    throw std::runtime_error("Błąd w trakcie nadpisywania użytkownika!");//obsługa wyjątków 
                system.update_user(username, potential_user.value());//aktualizowanie użytkownika
            break;
            case MenuChoice::UPDATE_BOOK:
                std::cout << "Podaj ISBN książki: ";
                std::getline(std::cin, isbn);//odczytanie isbn
                //próba utworzenia nowego obiektu ksiązki, ale bez dodawania go od razu do bazy danych (flaga false)
                potential_book = system.create_book(false);
                if (!potential_book.has_value())
                    throw std::runtime_error("Błąd w trakcie nadpisywania użytkownika!");//obsługa wyjątków

                system.update_book(isbn, potential_book.value());//aktualizowanie książki
                break;
            case MenuChoice::DELETE_USER:
                std::cout << "Podaj nazwę użytkownika: ";
                std::getline(std::cin, username);
                system.remove_user(username);//usuwanie użytkownika
            break;
            case MenuChoice::DELETE_BOOK:
                std::cout << "Podaj numer ISBN: ";
                std::getline(std::cin, isbn);
                system.remove_book(isbn);//usuwanie książki
            break;
            case MenuChoice::EXIT:
                std::cout << "Do widzenia!\n";
                break;
        }
        LibrarySystem::console_pause();//oczekiwanie na ENTER po wywołaniu akcji
    } while(choice != MenuChoice::EXIT);

}
//funkcja pomocnicza – pozwalająca użytkownikowi wybrać kryterium wyszukiwania książki
LibrarySystem::SearchOption choose_search_criteria() {
    int int_choice = 0;//zmienna przechowywująca wartość wprowadzoną przez użytkownika do wyboru opcji w menu
    constexpr int MAX_OPTION = 4;//największa możliwa liczba do wybrania
    constexpr int MIN_OPTION = 1;//najmniejsza możliwa liczba do wybrania

    do {
        std::cout << "Podaj kryterium wyszukiwania:\n";
        std::cout << "1. Tytuł\n";
        std::cout << "2. Autor\n";
        std::cout << "3. ISBN\n";
        std::cout << "4. Wyjdź\n";
        std::cout << "Wybór: ";
        std::cin >> int_choice;
        flush_stream();
    }while(int_choice < MIN_OPTION || int_choice > MAX_OPTION);//obsługa wybierania kryterium wyszukiwania książki
    //rzutowanie liczby całkowitej na wybrane kryterium wyszukiwania
    return static_cast<LibrarySystem::SearchOption>(int_choice);
}