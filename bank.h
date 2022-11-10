#ifndef BANK_H
#define BANK_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <iomanip>
#include <sstream>
#include<Windows.h>

using namespace std;

//--------------------------------------------------------------------------------
//Create the class for 'account'
class Account {
private:
    string id;
    string name;
    string password;

public:
    Account(string input_id, string input_name, string input_password);
    string getID();
    string getName();
    string getPassword();
};

//--------------------------------------------------------------------------------
//Create the class for 'amount'
class Amount {
private:
    string amount;
    string id;
public:
    Amount(string input_id);
    Amount(string input_id, string amount);
    string getAmount();
    string getID();
    void setAmount(string input_amount);
};

//--------------------------------------------------------------------------------
//Create the class for 'account loss'
class Loss {
private:
    string id;
public:
    Loss(string input_id);
    string getID();
};
#endif

//--------------------------------------------------------------------------------
//Main functions
void AccountCreation();
void AccountLogIn();
void AccountDelete(string input_id);
void AccountLoss(string input_id);
void AccountBalance(string input_id);
void MoneyDeposit(string input_id);
void MoneyWithdraw(string input_id);

//--------------------------------------------------------------------------------
//Secondary Functions
bool is_ID(string input_id);
bool is_ID_existent(string ID);
bool is_lost(string input_id);
void print_register_and_login_page();
void start_operation1(string number);
void print_personal_service_page();
void start_operation2(string input_id,string start_number);
void return_to_menu1(string input_number);
void return_to_menu2(string input_id, string str);
void print_success();
string current_time();
inline bool is_money(string input_money);
inline bool is_password(string input_password);
inline bool check_password(string input_password, string input_password_check);
void delete_account(vector<Account>& account_info, vector<Amount>& amount_info, vector<Loss>& loss_info, string input_id);
void update_file();
void initialize_variables();




#pragma once




