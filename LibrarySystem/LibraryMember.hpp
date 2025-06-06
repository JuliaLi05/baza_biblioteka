#pragma once
#include <functional>
#include <string>
#include <type_traits>
#include <stdexcept>
//szablon funkcji setter, który przypisuje wartość do zmiennej, ale najpierw sprawdza, czy wartość nie jest "pusta"
template<typename T>
inline void setter(T& variable, const T& value) {
    T empty_value;// zmienna przechowująca "pustą" wartość domyślną dla typu T
    if constexpr (std::is_same<T, std::string>::value)
        empty_value = "";
    if constexpr (std::is_integral<T>::value)
        empty_value = 0;
    if (value == empty_value)
        throw std::invalid_argument("Wartość do ustawienia nie może być pusta!");
    variable = value;
}

class LibraryMember {
protected:
    std::string name;
    std::string email;
    std::size_t password_hash;
public:
    //konstruktor z inicjalizacją pól i haszowaniem hasła
    LibraryMember(std::string n, std::string e, std::string p) {
        name = n;
        email = e;
        password_hash = std::hash<std::string>{}(p);
    }
    LibraryMember() = default;

    virtual void display_info() const = 0 ;//metoda wirtualna

    void set_name(std::string n) {
        setter(name, n);
    }

    void set_email(std::string e) {
        setter(email, e);
    }
    
    void set_password(std::string p) {
        if (p == "")
            throw std::invalid_argument("Hasło nie może być puste!");
        password_hash = std::hash<std::string>{}(p);
    }

    friend class LibrarySystem;
};