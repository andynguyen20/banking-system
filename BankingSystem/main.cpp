#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
    void top_off(double amount);
};

Account::Account(int account_number, double account_balance, AccountType account_type)
    : account_number(account_number), account_balance(account_balance), account_type(account_type)
{

}

void Account::top_off(double amount) {
    account_balance += amount;
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
    const Account& return_chequing_account() const { return chequing_account; };
    const Account& return_savings_account() const { return savings_account; };
    bool deposit_chequing_account(double amount);
    bool deposit_savings_account(double amount);
};

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

class Bank {
private:
    std::vector<User> user_database;
public:
    bool user_registration(const std::string& username);
    bool display_information(const std::string& username);
    void deposit_money(const std::string& username);
};

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


int choose_deposit_account() {
    int result = 0;
    std::cout << "Please enter an account to deposit money into: \n";
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
    bool found = false;
    double deposit_amount = 0;
    Account chequing_temp(0, 0.0, AccountType::chequing);
    Account savings_temp(0, 0.0, AccountType::savings);
    User user_temp("", 0, chequing_temp, savings_temp);
    for (User& user : user_database) {
        if (user.return_username() == username) {
            user_temp = user;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Could not find user in our database. Please enter a valid username or register as a new user option 1.\n";
        return;
    }
    while (true) {
        int account_type = choose_deposit_account();
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
            user_temp.deposit_chequing_account(deposit_amount);
            std::cout << "Successfully deposited " << deposit_amount << " to chequing account.";
            break;
        }
        case 2: {
            user_temp.deposit_savings_account(deposit_amount);
            std::cout << "Successfully deposited " << deposit_amount << " to savings account.";
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
        case 6: break;
        default: continue;
        }
    } while (option != 6);


    return 0;
}
