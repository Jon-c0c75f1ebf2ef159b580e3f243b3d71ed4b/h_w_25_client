#pragma once
#include <string>
#include <vector>
#include <exception>
#include <memory>

class Chat {
public:
    std::string chat_processing();
    void message_processing(std::string serverMessage);
    void start_message();

private:
    bool _send_message = false;
    bool _is_current_user = false;
    std::string _current_user_name;
    std::string _current_menu = "";
    std::vector<std::string> _vector_from_message;

    void show_login_menu();
    std::string login_user();
    std::string register_user();
    void check_register();
    void check_login();
    std::string exit_chat();

    void show_user_menu();
    std::string get_chat();
    std::string add_message();
    std::string get_users();
    void show_chat();
    void check_add_message();
    void show_users();

    std::vector<std::string> message_to_vector(std::string message, std::string delimiter);
};
