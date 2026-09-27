#include "bank.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

Account::Account(int account_number, double account_balance, AccountType account_type)
    : account_number(account_number), account_balance(account_balance), account_type(account_type)
{

}

void Account::top_off(double amount) {
    account_balance += amount;
}

User::User(const std::string& username, int user_id, const Account& chequing_account, const Account& savings_account)
    : username(username), user_id(user_id), chequing_account(chequing_account), savings_account(savings_account)
{

}

bool User::deposit_chequing_account(double amount) {
    if (amount < 0) {
        std::cout << "Please enter a valid amount of money to deposit.\n";
        return false;
    }
    chequing_account.top_off(amount);
    return true;
}

bool User::deposit_savings_account(double amount) {
    if (amount < 0) {
        std::cout << "Please enter a valid amount of money to deposit.\n";
        return false;
    }
    savings_account.top_off(amount);
    return true;
}

bool User::withdraw_chequing_account(double amount) {
    if (chequing_account.return_account_balance() - amount < 0) {
        std::cout << "Insufficient funds in chequing account.\n";
        return false;
    }
    chequing_account.top_off(-amount);
    return true;
}

bool User::withdraw_savings_account(double amount) {
    if (savings_account.return_account_balance() - amount < 0) {
        std::cout << "Insufficient funds in savings account.\n";
        return false;
    }
    savings_account.top_off(-amount);
    return true;
}

bool User::transfer_chequing_savings(double amount) {
    if (amount > chequing_account.return_account_balance()) {
        std::cout << "Insufficient funds in chequing account.\n";
        return false;
    }
    chequing_account.top_off(-amount);
    savings_account.top_off(amount);
    return true;
}

bool User::transfer_savings_chequing(double amount) {
    if (amount > savings_account.return_account_balance()) {
        std::cout << "Insufficient funds in chequing account.\n";
        return false;
    }
    savings_account.top_off(-amount);
    chequing_account.top_off(amount);
    return true;
}

bool Bank::user_registration(const std::string& username) {
    for (const User& user : user_database) {
        if (username == user.return_username()) {
            std::cout << "Rejected: username {" << username << "} already exists. Please choose a different username.\n";
            return false;
        }
    }
    static int next_user_id = 1000;
    static int next_chequing_number = 5000;
    static int next_savings_number = 5001;
    Account temp_chequing_account(next_chequing_number, 0.0, AccountType::chequing);
    Account temp_savings_account(next_savings_number, 0.0, AccountType::savings);
    User temp_user(username, next_user_id, temp_chequing_account, temp_savings_account);
    user_database.push_back(temp_user);
    std::cout << "Success!\n";
    next_user_id++;
    next_chequing_number += 2;
    next_savings_number += 2;
    return true;
}

bool Bank::display_information(const std::string& username) {
    for (const User& user : user_database) {
        if (user.return_username() == username) {
            std::cout << "========================================\n";
            std::cout << "            CUSTOMER INFORMATION        \n";
            std::cout << "========================================\n";
            std::cout << '\n';
            std::cout << "Username: " << user.return_username() << '\n';
            std::cout << "User ID: " << user.return_user_id() << '\n';
            std::cout << '\n';
            std::cout << "----------------------------------------\n";
            std::cout << "Chequing Account\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Account number: " << user.return_chequing_account().return_account_number() << '\n';
            std::cout << "Balance: $" << user.return_chequing_account().return_account_balance() << '\n';
            std::cout << '\n';
            std::cout << "----------------------------------------\n";
            std::cout << "Savings Account\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Account Number: " << user.return_savings_account().return_account_number() << '\n';
            std::cout << "Balance: $" << user.return_savings_account().return_account_balance() << '\n';
            std::cout << '\n';
            std::cout << "========================================\n";
            return true;
        }
    }
    std::cout << "Could not find username in our database. Please enter a valid username or register as a new user using option 1.\n";
    return false;
}

int intro_screen() {
    std::string option;
    std::cout << "========================================\n";
    std::cout << "              BANK SYSTEM\n";
    std::cout << "========================================\n";
    std::cout << '\n';
    std::cout << "1. Register new  user\n";
    std::cout << "2. View user information\n";
    std::cout << "3. Deposit\n";
    std::cout << "4. Withdraw\n";
    std::cout << "5. Transfer\n";
    std::cout << "6. Exit\n";
    std::cout << '\n';
    std::cout << "Selection: ";
    std::cin >> option;
    if (option == "1") return 1;
    if (option == "2") return 2;
    if (option == "3") return 3;
    if (option == "4") return 4;
    if (option == "5") return 5;
    if (option == "6") return 6;
    return 0;
}

std::string capture_username() {
    std::string username;
    while (true) {
        std::cout << "Enter username: ";
        if (std::cin >> username) {
            return username;
        }
        std::cout << "Please enter a valid username.\n";
    }
}


int choose_account() {
    int result = 0;
    std::cout << "Please choose an account: \n";
    std::cout << "1. Chequing\n";
    std::cout << "2. Savings\n";
    std::cout << "3. Go back\n";
    std::cin >> result;
    if (!std::cin || result < 0 || result > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    return result;
}

void Bank::deposit_money(const std::string& username) {
    double deposit_amount = 0;
    User* found_user = nullptr;
    for (User& user : user_database) {
        if (user.return_username() == username) {
            found_user = &user;
        }
    }
    if (!found_user) {
        std::cout << "Could not find user in our database. Please enter a valid username or register as a new user option 1.\n";
        return;
    }
    while (true) {
        int account_type = choose_account();
        if (account_type == 3) {
            return;
        }
        std::cout << "Enter a deposit amount: ";
        std::cin >> deposit_amount;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid deposit value.\n";
            continue;
        }
        switch (account_type) {
        case 1: {
            if (!(found_user->deposit_chequing_account(deposit_amount))) {
                continue;
            }
            std::cout << "Successfully deposited " << deposit_amount << " to chequing account.\n";
            break;
        }
        case 2: {
            if (!(found_user->deposit_savings_account(deposit_amount))) {
                continue;
            }
            std::cout << "Successfully deposited " << deposit_amount << " to savings account.\n";
            break;
        }
        default: {
            std::cout << "Nothing happened, this should not fire off. Check logic within deposit_money()\n";
            continue;
        }
        }
        break;
    }

}

void Bank::withdraw_money(const std::string& username) {
    double withdrawal_amount = 0;
    User* found_user = nullptr;
    for (User& user : user_database) {
        if (user.return_username() == username) {
            found_user = &user;
        }
    }
    if (!found_user) {
        std::cout << "Could not find user in our database. Please enter a valid username or register as a new user option 1.\n";
        return;
    }
    while (true) {
        int account_type = choose_account();
        if (account_type == 3) {
            return;
        }
        std::cout << "Enter a withdrawal amount: ";
        std::cin >> withdrawal_amount;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid withdrawal value.\n";
            continue;
        }
        switch (account_type) {
        case 1: {
            if (!(found_user->withdraw_chequing_account(withdrawal_amount))) {
                continue;
            }
            std::cout << "Successfully withdrew " << withdrawal_amount << " from chequing account.\n";
            break;
        }
        case 2: {
            if (!(found_user->withdraw_savings_account(withdrawal_amount))) {
                continue;
            }
            std::cout << "Successfully withdrew " << withdrawal_amount << " from savings account.\n";
            break;
        }
        default: {
            std::cout << "Nothing happened, this should not fire off. Check logic within withdraw_money()\n";
            continue;
        }
        }
        break;
    }
}

void Bank::transfer(const std::string& username) {
    double deposit_amount = 0;
    User* found_user = nullptr;
    for (User& user : user_database) {
        if (user.return_username() == username) {
            found_user = &user;
        }
    }
    if (!found_user) {
        std::cout << "Could not find user in our database. Please enter a valid username or register as a new user option 1.\n";
        return;
    }
    while (true) {
        int account_type = choose_account();
        if (account_type == 3) {
            return;
        }
        std::cout << "Enter amount to transfer: ";
        std::cin >> deposit_amount;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid deposit value.\n";
            continue;
        }
        switch (account_type) {
        case 1: {
            if (!(found_user->transfer_chequing_savings(deposit_amount))) {
                continue;
            }
            std::cout << "Successfully transferred " << deposit_amount << " from chequing to savings.\n";
            break;
        }
        case 2: {
            if (!(found_user->transfer_savings_chequing(deposit_amount))) {
                continue;
            }
            std::cout << "Successfully transferred " << deposit_amount << " from savings to chequing.\n";
            break;
        }
        default: {
            std::cout << "Nothing happened, this should not fire off. Check logic within transfer()\n";
            continue;
        }
        }
        break;
    }

}