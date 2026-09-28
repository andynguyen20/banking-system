#pragma once
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
    bool deposit(double amount);
    bool withdraw(double amount);
};

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
    bool withdraw_chequing_account(double amount);
    bool withdraw_savings_account(double amount);
    bool transfer_chequing_savings(double amount);
    bool transfer_savings_chequing(double amount);
};

class Bank {
private:
    std::vector<User> user_database;
public:
    bool user_registration(const std::string& username);
    bool display_information(const std::string& username);
    void deposit_money(const std::string& username);
    void withdraw_money(const std::string& username);
    void transfer(const std::string& username);
    User* find_username(const std::string& username);
    User* find_user_id(int user_id);
    User* find_account_id(int account_id);
};

int intro_screen();
std::string capture_username();
int choose_account();
int capture_user_id();