#include <iostream>
#include <string>
#include <cstring>
#include "Chat.h"
#include "Sha1.h"

std::string Chat::chat_processing()
{
    std::string out_message;

    while (!_send_message) {
        if (!_is_current_user) {
            if (_current_menu == "") {
                show_login_menu();
            }
            else if (_current_menu == "loginUser") {
                out_message = login_user();
            }
            else if (_current_menu == "registerUser") {
                out_message = register_user();
            }
            else if (_current_menu == "exitChat") {
                out_message = exit_chat();
            }
        }
        else {
            if (_current_menu == "") {
                show_user_menu();
            }
            else if (_current_menu == "getChat") {
                out_message = get_chat();
            }
            else if (_current_menu == "addMessage") {
                out_message = add_message();
            }
            else if (_current_menu == "getUsers") {
                out_message = get_users();
            }
        }
    }

    return out_message;
}

void Chat::message_processing(std::string server_message)
{
    _vector_from_message = message_to_vector(server_message, ":");

    if (_vector_from_message[0] == "loginUser") {
        check_login();
    }
    else if (_vector_from_message[0] == "registerUser") {
        check_register();
    }
    else if (_vector_from_message[0] == "showChat") {
        show_chat();
    }
    else if (_vector_from_message[0] == "addMessage") {
        check_add_message();
    }
    else if (_vector_from_message[0] == "showUsers") {
        show_users();
    }
}

std::vector<std::string> Chat::message_to_vector(std::string message, std::string delimiter)
{
    std::vector<std::string> result_vector;

    if (!message.empty()) {
        int start = 0;
        do {
            int idx = message.find(delimiter, start);
            if (idx == std::string::npos) {
                break;
            }

            int length = idx - start;
            result_vector.push_back(message.substr(start, length));
            start += (length + delimiter.size());
        } while (true);

        result_vector.push_back(message.substr(start));
    }

    return result_vector;
}

std::string Chat::login_user()
{
    std::string login;
    std::string password;
    std::string out_message;

    _send_message = true;

    std::cout << "login: ";
    std::cin >> login;
    std::cout << "password: ";
    std::cin >> password;

    const char* password_char = password.c_str();

    uint* passHex = sha1(password_char, strlen(password_char));

    out_message = "loginUser:" + login + ":" + to_string(*passHex);

    return out_message;
}

void Chat::check_login()
{
    char operation;
    std::string check_user;
    check_user = _vector_from_message[1];
    _send_message = false;

    if (check_user == "error") {
        _is_current_user = false;
        std::cout << "invalid password or invalid login!/n";
        show_login_menu();
    }
    else if (check_user == "ok") {
        _is_current_user = true;
        _current_menu = "";
        _current_user_name = _vector_from_message[2];
    }
}

std::string Chat::register_user()
{
    std::string login;
    std::string password;
    std::string name;
    std::string out_message;

    _send_message = true;

    std::cout << "login: ";
    do {
        std::cin >> login;
    } while (login == "all");
    std::cout << "password: ";
    std::cin >> password;
    std::cout << "name: ";
    do {
        std::cin >> name;
    } while (login == "all");

    const char* password_char = password.c_str();

    uint* passHex = sha1(password_char, strlen(password_char));

    out_message = "registerUser:" + login + ":" + to_string(*passHex) + ":" + name;

    return out_message;
}

void Chat::check_register()
{
    char operation;
    std::string check_user;
    std::string is_name_or_login;

    check_user = _vector_from_message[1];
    is_name_or_login = _vector_from_message[2];
    _send_message = false;

    if (check_user == "error") {
        _is_current_user = false;
        if (is_name_or_login == "login") {
            std::cout << "login is busy!/n";
        }
        else if (is_name_or_login == "name") {
            std::cout << "name is busy!/n";
        }
        show_login_menu();
    }
    else if (check_user == "ok") {
        _is_current_user = true;
        _current_menu = "";
        _current_user_name = _vector_from_message[2];
    }
}

std::string Chat::exit_chat()
{
    _send_message = true;
    std::cout << "Exiting the chat/n";
    return "exit";
}

void Chat::start_message()
{
    std::cout << "/n";
    std::cout << "Welcome!/n";
}

void Chat::show_login_menu()
{
    char operation;
    _send_message = false;

    std::cout << "/n";
    std::cout << "Login - 1    Registration - 2    Quit - 3 /n";
    std::cout << ">> ";
    std::cin >> operation;

    switch (operation)
    {
    case '1':
        _current_menu = "loginUser";
        break;

    case '2':
        _current_menu = "registerUser";
        break;

    case '3':
        _current_menu = "exitChat";
        break;

    default:
        std::cout << "1 or 2 or 3 /n";
        _current_menu = "";
        break;
    }
}

void Chat::show_user_menu()
{
    char operation;
    string out_message;
    _send_message = false;

    std::cout << "/nShow chat - 1  Add message - 2  Users - 3  Exit - 4 /n";
    std::cout << ">> ";
    std::cin >> operation;

    switch (operation)
    {
    case '1':
        _current_menu = "getChat";
        break;

    case '2':
        _current_menu = "addMessage";
        break;

    case '3':
        _current_menu = "getUsers";
        break;

    case '4':
        _is_current_user = false;
        _current_menu = "";
        break;

    default:
        std::cout << "unknown choice /n";
        _current_menu = "";
        break;
    }
}

std::string Chat::add_message()
{
    std::string from;
    std::string to;
    std::string text;
    std::string out_message;

    _send_message = true;

    from = _current_user_name;

    std::cout << "<name>" << "<all>: ";
    std::cin >> to;
    std::cout << "Text: ";
    std::cin.ignore();
    getline(std::cin, text);

    out_message = "addMessage:" + from + ":" + to + ":" + text;

    return out_message;
}

void Chat::check_add_message()
{
    _send_message = false;
    std::string check_message;
    check_message = _vector_from_message[1];

    if (check_message == "error") {
        _current_menu = "";
        std::cout << "failed to send message to user";
        std::cout << _vector_from_message[2] << ">>>/n";
    }
    else if (check_message == "ok") {
        _current_menu = "";
    }
}

std::string Chat::get_users()
{
    std::string out_message;
    _send_message = true;

    out_message = "showUsers:" + _current_user_name;

    return out_message;
}

std::string Chat::get_chat()
{
    std::string out_message;
    _send_message = true;

    out_message = "showChat:" + _current_user_name + ":showChat";

    return out_message;
}

void Chat::show_chat()
{
    std::string from;
    std::string to;

    _send_message = false;

    std::cout << " Chat /n";

    if (_vector_from_message[1] == "empty") {
        std::cout << "empty/n";
    }
    else {
        int i;
        for (i = 1; i < _vector_from_message.size() - 1; i += 3) {
            std::cout << "Message from " << _vector_from_message[i];
            std::cout << " to " << _vector_from_message[i + 1] << "/n";
            std::cout << "text: " << _vector_from_message[i + 2] << "/n";
        }
    }

    _current_menu = "";
}

void Chat::show_users()
{
    _send_message = false;

    cout << " All users /n";

    int i;
    for (i = 1; i < _vector_from_message.size() - 1; i++) {
        cout << _vector_from_message[i] << endl;
    }

    _current_menu = "";
}
