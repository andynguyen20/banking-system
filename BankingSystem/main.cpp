#include <iostream>
#include <string>
#include <vector>

enum class AccountType {
    chequing = 0,
    savings
};

class Account {
private:
    int account_number;
    double account_balance;
    AccountType account_type;
public:
    Account(int account_number, double account_balance, AccountType account_type);
    int return_account_number() const { return account_number; };
    double return_account_balance() const { return account_balance; };
};

Account::Account(int account_number, double account_balance, AccountType account_type)
    : account_number(account_number), account_balance(account_balance), account_type(account_type)
{

}

class User {
private:
    std::string username;
    int user_id;
    Account chequing_account;
    Account savings_account;
public:
    User(const std::string& username, int user_id, const Account& chequing_account, const Account& savings_account);
    std::string return_username() const { return username; };
    int return_user_id() const { return user_id; };
    Account return_chequing_account() const { return chequing_account; };
    Account return_savings_account() const { return savings_account; };
};

User::User(const std::string& username, int user_id, const Account& chequing_account, const Account& savings_account)
    : username(username), user_id(user_id), chequing_account(chequing_account), savings_account(savings_account)
{

}

class Bank {
private:
    std::vector<User> user_database;
public:
    bool user_registration(const std::string& username);
    bool display_information(const std::string& username);
    std::vector<User> return_user_database() const { return user_database; };

};

bool Bank::user_registration(const std::string& username) {
    for (const User& user : return_user_database()) {
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
    int option = 0;
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
    if (!std::cin || (option <= 0 && option > 6)) {
        return 0;
    }
    return option;
}

std::string capture_username() {
    std::string username;
    while (true) {
        std::cout << "Enter username: ";
        if (std::cin >> username) {
            return username;
        }
        if (std::cin.eof()) {
            std::cout << "Bad input, please type a valid username.\n";
            std::cin.clear();
            return "";
        }
        std::cout << "Please enter a valid username.\n";
    }
}


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
        case 6: break;
        }
    } while (option != 6);


    return 0;
}
