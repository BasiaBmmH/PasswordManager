//
// Created by Basia on 28.05.2023.
//

#ifndef PJC_PASSWORDMANAGER_H
#define PJC_PASSWORDMANAGER_H

#include <string>
#include <vector>

class PasswordManager {

    //Funkcja obsługująca timestamp
    auto writeTimestampToFile(const std::string &filePath) -> void {

    }

//funkcja szyfrowania i zapisywania do pliku hasła
    auto savePasswordToFile(const std::string kodDostepu, const std::string &filePath) -> void {
        // Implementacja szyfrowania danych
    }

// Funkcja do odszyfrowania danych z pliku źródłowego na podstawie hasła głównego
    auto
    decryptPasswordsFromFile(const std::string kodDostepu, const std::string &filePath) -> std::vector<std::string> {

    }

//Funkcja do wczytania danych z pliku źródłowego
    auto loadData(const std::string &filePath, const std::string &password) -> std::string {
    }

// Funkcja do generowania losowego hasła
    auto generatePassword(int length) -> std::string {
        // Implementacja generowania losowego hasła
    }

// Funkcja obsługująca edycję istniejącego hasła
    auto editPassword() -> void {

    }

// Funkcja obsługująca usuwanie hasła
    auto deletePassword() -> void {

    }

// Funkcja obsługująca wyszukiwanie haseł
    auto searchPasswords() -> void {

    }

};


#endif //PJC_PASSWORDMANAGER_H
