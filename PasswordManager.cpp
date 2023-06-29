#include "PasswordManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <list>
#include <chrono>
#include <sstream>

// Struktura przechowująca dane hasła
struct PasswordData {
    std::string name;
    std::string password;
    std::string category;
};

std::vector<PasswordData> passwordData;

auto writeTimestampToFile(const std::string &filePath) -> void {
    std::ofstream file(filePath, std::ios::app);  // Otwórz plik w trybie dodawania (append)

    if (!file.is_open()) {
        std::cout << "Nie można otworzyć pliku." << std::endl;
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    struct std::tm *timeInfo;
    char timeBuffer[80];

    timeInfo = std::localtime(&currentTime);

    // Zapisz godzinę w przedostatniej linii
    std::strftime(timeBuffer, sizeof(timeBuffer), "%H", timeInfo);
    file << "\n" << timeBuffer << std::endl;

    // Zapisz minuty w ostatniej linii
    std::strftime(timeBuffer, sizeof(timeBuffer), "%M", timeInfo);
    file << timeBuffer << std::endl;

    file.close();
    std::cout << "\nTimestamp zostal zapisany do pliku." << std::endl;
}

auto savePasswordToFile(const std::string &kodDostepu, const std::string &filePath) -> void {

    std::list<char> characterSet;

    PasswordData newPassword;

    std::cout << "Nazwa hasla: ";
    std::cin >> newPassword.name;

    std::cout << "Kategoria: ";
    std::cin >> newPassword.category;

    std::cout << "Haslo: ";
    std::cin >> newPassword.password;

    // Przekształcenie ciągu znaków na zbiór znaków
    for (char c: newPassword.password) {
        characterSet.push_back(c);
    }

    // Otwarcie pliku w trybie zapisu
    std::ofstream file(filePath);
    if (file.is_open()) {

        for (const PasswordData &e: passwordData) {
            file << e.password << std::endl;
        }

        for (char c: characterSet) {
            int difference = c - kodDostepu[0];
            file << difference << '.';
            newPassword.password += difference + '.';
        }

        file.close();
        std::cout << "zapisano haslo do pliku." << std::endl;
    } else {
        std::cout << "Nie mozna otworzyc pliku." << std::endl;
    }
    writeTimestampToFile(filePath);

    passwordData.push_back(newPassword);
}

auto decryptPasswordsFromFile(const std::string kodDostepu, const std::string &filePath) -> std::vector<std::string> {
    std::vector<std::string> decryptedPasswords;

    // Otwarcie pliku w trybie odczytu
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string encryptedPassword;
            std::string decryptedPassword;

            // Odczytanie zaszyfrowanego hasła jako ciągu liczb oddzielonych kropkami
            while (std::getline(ss, encryptedPassword, '.')) {
                int number = std::stoi(encryptedPassword);
                char character = number + kodDostepu[0];
                decryptedPassword += character;
            }

            decryptedPasswords.push_back(decryptedPassword);
        }

        file.close();
        std::cout << "Hasla zostaly odszyfrowane z pliku." << std::endl;
    } else {
        std::cout << "Nie mozna otworzyc pliku." << std::endl;
    }

    for (auto haslo: decryptedPasswords) {
        std::cout << haslo << std::endl;
    }

    writeTimestampToFile(filePath);
    return decryptedPasswords;
}


//Funkcja do wczytania danych z pliku źródłowego
auto loadData(const std::string &filePath, const std::string &password) -> std::string {
    std::ifstream file(filePath);
    std::string encryptedData;

    if (file.is_open()) {
        std::getline(file, encryptedData);
        file.close();
    } else {
        std::cout << "Nie mozna otworzyc pliku." << std::endl;
        return "";
    }

    std::string decryptedData;
    // decryptData(password, encryptedData, decryptedData);

    writeTimestampToFile(filePath);
    return decryptedData;
}


// Funkcja do generowania losowego hasła
auto generatePassword(int length) -> std::string {
    std::string randomString;

    return randomString;
}


// Funkcja obsługująca edycję istniejącego hasła
auto editPassword(const std::string &filePath) -> void {
    std::string passwordId;

    std::cout << "Podaj nazwe hasla do edycji: ";
    std::cin >> passwordId;

    auto iter = std::find_if(passwordData.begin(), passwordData.end(), [passwordId](const PasswordData &password) {
        return password.name == passwordId;
    });

    if (iter != passwordData.end()) {
        std::cout << "Nazwa hasla: ";
        std::cin >> iter->name;

        std::cout << "Haslo: ";
        std::cin >> iter->password;

        std::cout << "Kategoria: ";
        std::cin >> iter->category;

        std::cout << "Haslo zostało zaktualizowane^^" << std::endl;
    } else {
        std::cout << "Haslo o podanym identyfikatorze nie istnieje :( " << std::endl;
    }

    writeTimestampToFile(filePath);
}


// Funkcja obsługująca usuwanie hasła
auto deletePassword(const std::string &filePath) -> void {
    std::string passwordName;

    std::cout << "Podaj nazwe hasla do usuniecia: ";
    std::cin >> passwordName;

    auto iter = std::remove_if(passwordData.begin(), passwordData.end(), [passwordName](const PasswordData &password) {
        return password.name == passwordName;
    });

    if (iter != passwordData.end()) {
        passwordData.erase(iter, passwordData.end());
        std::cout << "Haslo zostalo usuniete." << std::endl;
    } else {
        std::cout << "Haslo o podanym identyfikatorze nie istnieje." << std::endl;
    }

    writeTimestampToFile(filePath);

}


// Funkcja obsługująca wyszukiwanie haseł
auto searchPasswords(const std::string &filePath) -> void {
    std::string searchQuery;

    std::cout << "Wpisz fraze do wyszukania: ";
    std::cin >> searchQuery;

    std::cout << "Wyniki wyszukiwania:" << std::endl;
    for (const auto &password: passwordData) {
        if (password.name.find(searchQuery) != std::string::npos ||
            password.category.find(searchQuery) != std::string::npos) {
            std::cout << "Nazwa: " << password.name << std::endl;
            std::cout << "Haslo: " << password.password << std::endl;
            std::cout << "Kategoria: " << password.category << std::endl;
            std::cout << "-----------------------" << std::endl;
        }
    }

    writeTimestampToFile(filePath);
}


auto main() -> int {
    std::string filePath;
    std::string password;

    std::string inputString;
    std::string kodDostepu;

    std::cout << "Podaj kod dostepu: ";
    std::getline(std::cin, kodDostepu);

    std::cout << "Podaj sciezke do pliku: ";
    std::getline(std::cin, filePath);

//    std::cout << "Podaj haslo: ";
//    std::getline(std::cin, inputString);

    // Wczytanie danych z pliku źródłowego
    //std::string data = loadData(filePath, kodDostepu);

    // Główna pętla programu
    bool exitProgram = false;
    while (!exitProgram) {
        std::cout << "========== MENU ==========" << std::endl;
        std::cout << "1. Dodaj haslo" << std::endl;
        std::cout << "2. Edytuj haslo" << std::endl;
        std::cout << "3. Usun haslo" << std::endl;
        std::cout << "4. Wyszukaj hasla" << std::endl;
        std::cout << "5. Rozszyfruj hasla" << std::endl;
        std::cout << "6. Wyjscie" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Wybierz opcje: ";
        int option;
        std::cin >> option;

        switch (option) {
            case 1 :
                savePasswordToFile(kodDostepu, filePath);
                break;
            case 2:
                editPassword(filePath);
                break;
            case 3:
                deletePassword(filePath);
                break;
            case 4:
                searchPasswords(filePath);
                break;
            case 5:
                decryptPasswordsFromFile(kodDostepu, filePath);
                break;
            case 6:
                exitProgram = true;
                break;
            default:
                std::cout << "Nieprawidlowa opcja. Sprobuj ponownie." << std::endl;
                break;
        }
    }

    return 0;


}
