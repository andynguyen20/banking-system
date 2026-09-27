#include "bank.h"
#include <iostream>


int main()
{
    Bank bank;
    int option = 0;
    do {
        option = intro_screen();
        if (!option) {
            std::cout << "Please choose a valid option.\n";
            continue;
        }
        switch (option) {
        case 1: {
            bool success = false;
            do {
                std::string username = capture_username();
                if (username == "") {
                    continue;
                }
                success = bank.user_registration(username);
            } while (!success);
            break;
        }
        case 2: {
            std::string username = capture_username();
            bank.display_information(username);
            break;
        }
        case 3: {
            std::string username = capture_username();
            bank.deposit_money(username);
            break;
        }
        case 4: {
            std::string username = capture_username();
            bank.withdraw_money(username);
            break;
        }
        case 5: {
            std::string username = capture_username();
            bank.transfer(username);
            break;
        }
        case 6: break;
        default: continue;
        }
    } while (option != 6);


    return 0;
}
