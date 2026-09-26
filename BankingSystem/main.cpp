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
    double balance;
    AccountType account_type;
public:
    Account(int account_number, double balance, AccountType account_type);
};

Account::Account(int account_number, double balance, AccountType account_type)
    : account_number(account_number), balance(balance), account_type(account_type)
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

};

User::User(const std::string& username, int user_id, const Account& chequing_account, const Account& savings_account)
    : username(username), user_id(user_id), chequing_account(chequing_account), savings_account(savings_account)
{

}

class Bank {
private:
    std::vector<User> user_database;
public:
    void user_registration(const std::string& username);
    void display_information(const std::string& username);
};

void Bank::user_registration(const std::string& username) {
    static int next_user_id = 1000;
    static int next_chequing_number = 5000;
    static int next_savings_number = 5001;
    Account temp_chequing_account(next_chequing_number, 0.0, AccountType::chequing);
    Account temp_savings_account(next_savings_number, 0.0, AccountType::savings);
    User temp_user(username, next_user_id, temp_chequing_account, temp_savings_account);
    user_database.push_back(temp_user);
    next_user_id++;
    next_chequing_number += 2;
    next_savings_number += 2;
}

void Bank::display_information(const std::string& username) {
    for (const User& user : user_database) {
        if (user.return_username() == username) {

            std::cout << "========================================\n";
            std::cout << "            CUSTOMER INFORMATION        \n";
            std::cout << "========================================\n";
            std::cout << "\n";
            std::cout << "Username: " << user.return_username();
            std::cout << "User ID: " << user.return_user_id();
            std::cout << "\n";
            //std::cout << "----------------------------------------\n";
            //std::cout << "Chequing Account\n";
            //std::cout << "----------------------------------------\n";
            //std::cout << "Account number: " << user.
            
        }
    }
}


int main()
{
    Bank bank;

    bank.user_registration("Andy");
    bank.display_information("Andy");

    return 0;
}
