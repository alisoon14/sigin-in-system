#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

class Password {
public:
    void sign() {
        cout << "Регистрация нового пользователя:\n";
        Enter();
    }

private:
    string email;
    string phone_number;
    string name;
    string password;

    void Enter() {
        cout << "Введите ваше имя: ";
        getline(cin, name);
        while (!name_is_valid()) {
            cout << "Некорректное имя. Пожалуйста, введите снова: ";
            getline(cin, name);
        }

        cout << "Введите ваш email: ";
        getline(cin, email);
        while (!email_is_valid()) {
            cout << "Некорректный email. Пожалуйста, введите снова: ";
            getline(cin, email);
        }

        cout << "Введите ваш номер телефона: ";
        getline(cin, phone_number);
        while (!phone_is_valid()) {
            cout << "Некорректный номер телефона. Пожалуйста, введите снова: ";
            getline(cin, phone_number);
        }

        cout << "Введите ваш пароль: ";
        getline(cin, password);
        while (!password_is_valid()) {
            cout << "Пароль должен содержать минимум 5 символов и только английские буквы. Пожалуйста, введите снова: ";
            getline(cin, password);
        }

        save_to_file();
        cout << "Регистрация завершена успешно!\n";
    }

    void save_to_file() {
        ofstream file("db.txt", ios::app);
        if (file.is_open()) {
            file << "Имя: " << name << ", Email: " << email << ", Телефон: " << phone_number << ", Пароль: " << password << endl;
            file.close();
            cout << "Данные успешно сохранены\n"; // Отладочное сообщение
        }
        else {
            cout << "Ошибка при открытии файла!" << endl;
        }
    }

    bool email_is_valid() {
        regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z]{2,}$");
        return regex_match(email, email_pattern);
    }

    bool phone_is_valid() {
        if (phone_number.length() == 11 && phone_number[0] == '8') {
            regex phone_pattern("^8\\d{10}$");
            return regex_match(phone_number, phone_pattern);
        }
        else if (phone_number.length() == 12 && phone_number.substr(0, 2) == "+7") {
            regex phone_pattern("^\\+7\\d{10}$");
            return regex_match(phone_number, phone_pattern);
        }
        return false;
    }

    bool password_is_valid() {
        regex password_pattern("^[a-zA-Z]{5,}$");
        return regex_match(password, password_pattern);
    }

    bool name_is_valid() {
        regex name_pattern("^[^!@#$%^&*()_+=-]*$");
        return regex_match(name, name_pattern);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Password registration;
    registration.sign();
    return 0;
}