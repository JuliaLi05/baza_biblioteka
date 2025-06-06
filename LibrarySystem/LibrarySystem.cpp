#include "LibrarySystem.hpp"
#include "Librarian.hpp"
#include "User.hpp"
#include "Book.hpp"
#include <cctype>
#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <ctime>

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <conio.h>
#endif
//szablon funkcji w języku C++, służący do uniwersalnego przypisywania wartości do pól obiektu dowolnej klasy
// - prompt: komunikat wyświetlany użytkownikowi
// - book: obiekt, którego pole chcemy ustawić
// - field: wskaźnik na pole klasy, do którego przypiszemy wartość
template<typename T, typename Class, typename BaseClass = Class>
static void assign_field(std::string prompt, Class& book, T BaseClass::*field) {
    T temp_value;//tymczasowa zmienna do przechowania wartości odczytanej od użytkownika
    std::cout << prompt << ' ';//wyświetlenie komunikatu 
    if constexpr (std::is_integral<T>::value) {
        std::cin >> temp_value;//wczytywanie wartości
        std::cin.ignore();//usuwanie znaku nowej linii z bufora wejściowego
    }//dla T całkowitego
    if constexpr(std::is_same<T, std::string>::value) {
        std::getline(std::cin, temp_value);//wczytywanie całego wiersza
    }//dla T typu string 
    book.*field = temp_value;//przypisanie wartości do wskazanego pola obiektu
}
//pauza
void LibrarySystem::console_pause() {
    std::cout << "Wciśnij Enter, aby kontynuować...";
    std::cin.get();
}
//szyfrowanie hasła przy wpisywaniu - obsługa dla Linuksja i Windowsa
std::string LibrarySystem::get_password() {
    std::string passwd;
    #ifdef __unix__
        struct termios tty;
        tcgetattr(STDIN_FILENO, &tty);
        tty.c_lflag ^= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);

        std::cin >> passwd;

        tcgetattr(STDIN_FILENO, &tty);
        tty.c_lflag ^= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);

        return passwd;
    #endif
        
    #ifdef _WIN32
        unsigned char ch = 0;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b' && !passwd.empty()) {
                passwd.pop_back();
                std::cout << "\b \b";
            } else {
                passwd.push_back(ch);
                std::cout << '*';
            }
        }
        std::cout << std::endl;
        return passwd;
    #endif
}
//funkcja do pobierania obecnej daty
std::string get_current_date() {
    auto now = std::chrono::system_clock::now();// pobieranie aktualnego czasy systemowego jako punktu w czasie
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);//konwertowanie punktu w czasie do formatu time_t
    std::tm local_time;//struktura przechowująca rozbity czas lokalny
//funkcja konwertująca time_t na lokalny czas - wersja dla Linux i Windows 
#ifdef _WIN32
    localtime_s(&local_time, &now_time);
#endif
#ifdef __unix__
    localtime_r(&now_time, &local_time);
#endif

    std::stringstream oss;//tworzenie strumienia tekstowego
    oss << std::put_time(&local_time, "%Y-%m-%d");//wpisanie daty do tego strumienia
    return oss.str();//zwrócenie daty jako string
}
//funkcja do tworzenia książki
std::optional<Book> LibrarySystem::create_book(bool add_to_db) {
    
    Book new_book;

    assign_field("Podaj tytuł:", new_book, &Book::title);
    assign_field("Podaj autora:", new_book, &Book::author);
    assign_field("Podaj rok wydania:", new_book, &Book::year);
    assign_field("Podaj ISBN:", new_book, &Book::isbn);
    new_book.loan_date = get_current_date();

    if (!add_to_db)
        return new_book;

    book_repository.push_back(new_book);//dodawanie książki do bazy
    std::sort(book_repository.begin(), book_repository.end(),
     [](const Book& a, const Book& b) {
        return a.title < b.title;
     });//sortowanie książek alfabetycznie za pomocą algorytmu sort
    return {};
}
//funkcja do usuwania książki
void LibrarySystem::remove_book(std::string isbn) {
    for(std::vector<Book>::iterator it = book_repository.begin();
        it != book_repository.end(); it++) {
        if (it->isbn == isbn) {
            book_repository.erase(it);
            return;
        }
    }
}
//funkcja do aktualizacji danych książki
void LibrarySystem::update_book(std::string isbn, const Book& other) {
    for(auto& book: book_repository)  {
        if (book.isbn == isbn)
        {
            book = other;//przypisanie nowych danych
            return;
        }
    }
}
//funkcja do wyświetlania informacji o wybranej książce przy pomocy algorytmu find_if
void LibrarySystem::print_book(std::string isbn) {
    auto iterator = std::find_if(book_repository.begin(), book_repository.end(), 
                                [isbn](const Book& value){return value.isbn == isbn;});
    if (iterator != book_repository.end())
        iterator->print_info(std::cout);
}
//funkcja do wyświetlania informacji o książkach
void LibrarySystem::print_all_books() {
    if (book_repository.empty())
        std::cout << "W bazie nie ma obecnie żadnych książek\n";
    for(const auto& book: book_repository) {
        std::cout << book;
    }
}
//tworzenie użytkownika
std::optional<User> LibrarySystem::create_user(bool add_to_db) {
    std::shared_ptr<User> new_user = nullptr;
    //wybór typu użytkownika
    int choice = 0;
    do {
        std::cout << "Podaj rolę (1 - czytelnik, 2 - bibliotekarz): ";
        std::cin >> choice;
        std::cin.ignore();
    }while (choice != 1 && choice != 2);
    
    if (choice == 1)
        new_user = std::make_shared<User>();
    else
        new_user = std::make_shared<Librarian>();
    //dane użytkownika
    do {
        assign_field("Podaj nazwę użytkownika:", *new_user, &User::name);
    }while(doesUserExist(new_user->get_username()));
    assign_field("Podaj adres email:", *new_user, &User::email);

    std::cout << "Podaj hasło: ";
    std::string passwd = get_password();
    new_user->set_password(passwd);
    if (!add_to_db)
        return *new_user;
    
    users.push_back(new_user);
    return {};
}
//funkcja do wypisywania danych użytkownika z wykorzystaniem algorytmu for_each i polimorfizmu
void LibrarySystem::print_all_users() {
    if (users.empty())
        std::cout << "W bazie nie ma obecnie żadnych użytkowników\n";
    std::for_each(users.begin(), users.end(), [](const auto& user) {
        user->display_info();
    });
}
//funkcja do aktualizacji danych użytkownika (algorytm find_if)
void LibrarySystem::update_user(std::string username, const User& other) {
    auto index = std::find_if(users.begin(), users.end(), [&username](const auto& user) {
        return username == user->get_username();
    });
    if (index == users.end())
        throw std::runtime_error("Nie znaleziono użytkownika o nazwie: " + username);//wyjątek typu runtime_error - gdy użytkownik nie istnieje
    **index = other;//przypisanie nowych danych
}
//funkcja do wyszukiwania książek
void LibrarySystem::find_book(LibrarySystem::SearchOption option, std::string& search_term) {
    //pomocnicza funkcja konwertująca string na małe litery (wykorzystanie algorytmu transform)
    const auto to_lower = [](std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
    };
    //generator predykatu do wyszukiwania po danym polu książki (np.tytule)
    const auto predicate_generator = 
    [&to_lower](const std::string Book::* argument, std::string& value) { 
        return [argument, &to_lower, &value](const Book& book) {
            std::cout << book.*argument << '\n'; //wyświetlenie oryginalnej zawartości danego pola książki (np. tytułu)
            std::string lower_argument = book.*argument; // pobranie zawartości pola książki i zapisanie do zmiennej
            to_lower(lower_argument);// konwersja pola książki (np.tytułu) na małe litery
            to_lower(value);// konwersja szukanego hasła na małe litery

            return lower_argument.find(value) != std::string::npos; //sprawdza, czy wpisana fraza jest zawarta w danych książki
        };
    };
    //ustawianie predykatu, po którym będziemy szukać kszoążki
    std::function<bool(const Book&)> predicate;
    switch(option) {
        case LibrarySystem::SearchOption::BY_AUTHOR:
            predicate = predicate_generator(&Book::author, search_term);
        break;
        case LibrarySystem::SearchOption::BY_ISBN:
            predicate = predicate_generator(&Book::isbn, search_term);
        break; 
        case LibrarySystem::SearchOption::BY_TITLE:
            predicate = predicate_generator(&Book::title, search_term);
        break; 
        case LibrarySystem::SearchOption::NONE:
        break;
    }
    //wyszukiwanie pasujących książek przy użyciu algorytmu copy_if
    std::list<Book> found_books;
    std::copy_if(book_repository.begin(), book_repository.end(),
    std::back_inserter(found_books), predicate);
    
    std::cout << "Znaleziono " << found_books.size() << " wyników!\n";
    for(const auto& book: found_books) {
        book.print_info(std::cout);
    }
}
//usuwanie użytkownika po nazwie z wykorzystanie std:erase_if
void LibrarySystem::remove_user(std::string username) {
    auto it = std::erase_if(users,
     [&username](const auto& user) {
        return user->get_username() == username;
    });
}
