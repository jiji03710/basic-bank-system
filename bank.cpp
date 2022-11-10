#include "bank.h"


//--------------------------------------------------------------------------------
//filepath for 'account','amount'and 'accountloss'
const string account_filepath = "account.txt";
const string amount_filepath = "amount.txt";
const string loss_filepath = "loss.txt";
//ps: personal file(to storage personal withdraw & deposit records)
//will be created after a person finish the register (in line205)

//--------------------------------------------------------------------------------
//create vector array to storage info
vector<Account> account;
vector<Amount> amount;
vector<Loss> loss;

//--------------------------------------------------------------------------------
// Constructor for Account object
Account::Account(string input_id, string input_name, string input_password) :
    id(input_id),
    name(input_name),
    password(input_password) {}

// get id
string Account::getID() {
    return id;
}

//get name
string Account::getName() {
    return name;
}

//get password
string Account::getPassword() {
    return password;
}

//--------------------------------------------------------------------------------
// Constructor for Account object
Amount::Amount(string input_id) :
    id(input_id),
    amount("0") {}// set the default of amount to 0

Amount::Amount(string input_id, string amount) :
    id(input_id),
    amount(amount) {}

//get the amount
string Amount::getAmount() {
    return amount;
}

//get the id 
string Amount::getID() {
    return id;
}

//set the amount
void Amount::setAmount(string input_amount) {
    this->amount = input_amount;
}

//--------------------------------------------------------------------------------
// Constructor for AccountLoss object
Loss::Loss(string input_id) :
    id(input_id) {}

//get the id
string Loss::getID() {
    return id;
}


//--------------------------------------------------------------------------------
void AccountCreation() {

    ofstream account_fout(account_filepath, ios::out | ios::app);
    ofstream amount_fout(amount_filepath, ios::out | ios::app);

    cout << "\nSTARTING ACCOUNT CREATION" << endl;

    //the function called "return_to_menu1" is defined in line 707
    //it will return to the menu when user input '0' at any time
    cout << "(enter 0 to return to the menu at any time)" << endl;

    string input_id, input_name, input_password, input_password_check;

    //let user enter the identity card number
    cout << "\nPLEASE ENTER YOUR IDENTITY CARD NUMBER" << endl;
    cout << "(please insure that the id is a 18-digit number)" << endl;
    cout << "(for example: ******20030710****) " << endl;
    getline(cin, input_id);
    return_to_menu1(input_id); //(if input==0, return to the menu)

    // check whether the input is a Chinese Identity Card Number
    //if not, the system outputs the error and gets another input
    while (is_ID(input_id) == false)
    {
        cout << "\nINVALID ID\nplease enter again: " << endl;
        getline(cin, input_id);
        return_to_menu1(input_id);//(if input==0, return to the menu)
        is_ID(input_id);
    }

    // check whether the id has already been registered, 
    //if so, the system will see it as an input error and let user input again
    while (is_ID_existent(input_id)) {
        cout << "\nERROR: ID ALREADY EXIST\nPlease input your ID again" << endl;
        getline(cin, input_id);
        return_to_menu1(input_id);//(if input==0, return to the menu)

        // check whether the input is a Chinese Identity Card Number
        //if not, the system outputs the error and gets another input
        while (is_ID(input_id) == false)
        {
            cout << "\nINVALID ID\nplease enter again: " << endl;
            getline(cin, input_id);
            is_ID(input_id);
            return_to_menu1(input_id);//(if input==0, return to the menu)
        }

        is_ID_existent(input_id);
    }


    //let user input the name
    cout << "\nPLEASE ENTER YOUR NAME:" << endl;
    getline(cin, input_name);
    return_to_menu1(input_name);//(if input==0, return to the menu)

    //let user input the password
    cout << "\nPLEASE SET YOUR PASSWORD" << endl;
    cout << "enter a passsword of 6 numbers: " << endl;
    getline(cin, input_password);
    return_to_menu1(input_password);//(if input==0, return to the menu)

    //check whether the input password is a 6-digit-number
    //if not, let the user input again 
    while (!is_password(input_password)) {
        cout << "invaid password, please enter again: " << endl;
        getline(cin, input_password);
        return_to_menu1(input_password);//(if input==0, return to the menu)
    }

    //let user enter the password again to confirm
    cout << "\nPLEASE ENTER THE PASSWORD AGAIN TO CONFIRM:" << endl;
    getline(cin, input_password_check);
    return_to_menu1(input_password_check);//(if input==0, return to the menu)

    //if the two inputs do not match
    //let user enter 1 to confirm the password again or enter 2 to set the password again
    while (check_password(input_password, input_password_check) == false) {
        cout << "\nCONFIRMATION FAIL"
            << "\nplease type 1 to confirm again and 2 to set the password again : " << endl;
        
        //let user enter 1 to confirm the password again or enter 2 to set the password again
        string temp_number;
        getline(cin, temp_number);
        return_to_menu1(temp_number);//(if input==0, return to the menu)
        
        //if user inputs neither 1 nor 2
        //report error and let the user input again
        while (temp_number != "1" && temp_number != "2") {
            cout << "\nERROR INVALID INPUT"
                << "\nPlease enter 1 to confirm again and 2 to set the password again: " << endl;
            getline(cin, temp_number);
            return_to_menu1(temp_number);//(if input==0, return to the menu)
        }

        //if user inputs 1, check passwords until they match
        if (temp_number == "1") {
            cout << "\nPLEASE ENTER THE PASSWORD AGAIN TO CONFIRM:" << endl;
            getline(cin, input_password_check);
            return_to_menu1(input_password_check);//(if input==0, return to the menu)
            check_password(input_password, input_password_check);
        }

        //if user inputs 2, reset the password and check passwords until they match 
        if (temp_number == "2") {
            cout << "\nPLEASE SET YOUR PASSWORD" << endl;
            cout << "enter a passsword of 6 numbers: " << endl;
            getline(cin, input_password);
            return_to_menu1(input_password);//(if input==0, return to the menu)

            while (!is_password(input_password)) {
                cout << "invaid password, please enter again: " << endl;
                getline(cin, input_password);
                return_to_menu1(input_password);//(if input==0, return to the menu)
            }

            cout << "\nPLEASE ENTER THE PASSWORD AGAIN TO CONFIRM:" << endl;
            getline(cin, input_password_check);
            return_to_menu1(input_password_check);//(if input==0, return to the menu)
            check_password(input_password, input_password_check);
        }
    }

    //input account info in 'account.txt'
    account_fout << left << setw(25) << input_id << left << setw(25)
        << input_name << left << setw(25) << input_password << endl;
    account_fout.close();

    //Create personal txt file for storaging withdraw & deposit info later
    string personal_filepath = input_id + ".txt";//create a personal filepath
    ofstream personal_fout;
    personal_fout.open(personal_filepath, ios::app);
    personal_fout << right << setw(20) << "ID" << ": " << input_id << "'s BALANCE\n" << endl;
    personal_fout << left << setw(25) << "TIME" << left << setw(35)
        << "WITHDRAW & DEPOSIT" << left << setw(25) << "HISTORY BALANCE " << endl;
    personal_fout.close();

    // Creates temp_account object and then puts it in into account vector
    Account temp_account(input_id, input_name, input_password);
    account.push_back(temp_account);

    // Creates temp_amount object and then puts it in into amount vector
    Amount temp_amount(input_id);
    amount.push_back(temp_amount);

    //input amount info in 'amount.txt'
    amount_fout << left << setw(25) << input_id << left << setw(25) << temp_amount.getAmount() << endl;
    amount_fout.close();

    cout << "\nACCOUNT SUCCESSFULLY CREATED\n" << endl;
}

//--------------------------------------------------------------------------------
void AccountLogIn() {

    // start the account log in function
    cout << "\nSTARTING ACCOUNT LOG IN" << endl;
    cout << "(enter 0 to return to the menu at any time)\n" << endl;

    //find the id in the system with its corresponding password
    //if id is not found, let user enter the id again 
    string input_id;
    string password;
    bool id_exist = false;//set the default of 'id_exist' to be FLASE
   
    while (id_exist == false) {
        cout << "please input your id to log in:" << endl;
        getline(cin, input_id);
        return_to_menu1(input_id); //(if input == 0, return to the menu)

        for (auto it = account.begin(); it != account.end(); it++) {
            if (it->getID() == input_id) {
                id_exist = true;

                //get the corresponding password
                password = it->getPassword();
                
                //let user input the password 
                //if the password does not match, let user input again 
                cout << "\nPLEASE INPUT YOUR PASSWORD: " << endl;
                string input_password_1;
                getline(cin, input_password_1);
                return_to_menu1(input_password_1);//(if input == 0, return to the menu)

                while (password != input_password_1) {
                    cout << "\nWRONG PASSWORD"
                        << "\nplease enter your password again " << endl;
                    getline(cin, input_password_1);
                    return_to_menu1(input_password_1);//(if input == 0, return to the menu)
                }

                cout << "\nSUCCESSFULLY LOG IN\n" << endl;

                //enter a number to invoke the function in personal service page 
                string start_number = "1";
                while (start_number == "1" || start_number == "2" || start_number == "3" ||
                    start_number == "4" || start_number == "5")
                {
                    //print the personal service page
                    print_personal_service_page();
                    cout << "\nPLEASE ENTER AN NUMBER TO CONTINUE" << endl;
                    getline(cin, start_number);
                    while (start_number != "1" && start_number != "2" && start_number != "3" &&
                        start_number != "4" && start_number != "5" && start_number != "0" && start_number != "6") {
                        cout << "\nERROR: INVALID INPUT\nPlease enter a valid number:\n";
                        cin >> start_number;
                    }
                    start_operation2(input_id, start_number);
                }
                
            }
            
        }
        cout << "\nERROR: ID DOES NOT EXIST" << endl;
    }

}

//--------------------------------------------------------------------------------
void AccountDelete(string input_id) {

    // start the account delete function
    cout << "\nSTARTING ACCOUNT DELETE" << endl;
    cout << "please enter your password to confirm and delete the account" << endl;
    cout << "(enter 0 to return to the personal service page at any time)" << endl;
    
    for (auto it = account.begin(); it != account.end(); it++) {
        if (it->getID() == input_id) {
            
            //get the correct password in the system
            string password;
            password = it->getPassword();
            
            //let the user enter the password to confirm
            string input_password;
            getline(cin, input_password);
            return_to_menu2(input_id, input_password);//(if input == 0, return to the personal service page)

           //if password does not match, let the user input till it matches
            while (input_password != password) {
                cout << "ERROR: WRONG PASSWORD" << endl;
                cout << "please enter the password again" << endl;
                getline(cin, input_password);
                return_to_menu2(input_id, input_password); //(if input == 0, return to the personal service page)
            }
            break;
        }       
    }

    //the definition of the delete_account function is in line**
    delete_account(account, amount, loss, input_id);
    cout << "\nACCOUNT SUCCESSFULLY DELETE" << endl;

    update_file();

    cout << "\nSYSTEM CLOSED" << endl;
    exit(0);

}

//--------------------------------------------------------------------------------
//report the loss status of an account
void AccountLoss(string input_id) {
    
    // start the account loss function
    cout << "\nSTART THE ACCOUNT LOSS SERVICE" << endl;
    cout << "please enter your password to confirm and report the loss" << endl;
    cout << "(enter 0 to return to the personal service page at any time)" << endl;

    for (auto it = account.begin(); it != account.end(); it++) {
        if (it->getID() == input_id) {
           
            //get the correct password in the system
            string password;
            password = it->getPassword();

            //let the user enter the password to confirm
            string input_password;
            getline(cin, input_password);
            return_to_menu2(input_id, input_password);//(if input == 0, return to the personal service page)

            //if password does not match, let the user input till it matches
            while (input_password != password) {
                cout << "ERROR: WRONG PASSWORD" << endl;
                cout << "please enter the password again" << endl;
                getline(cin, input_password);
                return_to_menu2(input_id, input_password);//(if input == 0, return to the personal service page)
            }
            break;
        }
    }

    //save the info in class object and vector array
    Loss temp_loss(input_id);
    loss.push_back(temp_loss);

    //save the info in loss.txt
    ofstream loss_fout(loss_filepath, ios::out | ios::app);
    loss_fout << input_id << endl;
    loss_fout.close();

    cout << "\nSUCCESSFULLY REPORT THE LOSS\n" << endl;

}

//--------------------------------------------------------------------------------
void AccountBalance(string input_id) {
   
    //show the account amount as well as the personal withdraw & deposit records
    for (auto it = amount.begin(); it != amount.end(); it++) {
        if (it->getID() == input_id) {
            cout << "\nYOUR CURRENT BALANCE IS: " << it->getAmount() << endl;
            cout << "(the balance detail is as follows)\n" << endl;
        }
    }

    //output withdraw & deposit info through personal filepath 
    string personal_filepath = input_id + ".txt";
    ifstream fin(personal_filepath);
    string str;
    while (getline(fin, str)) {
        cout << str << endl;
    }
    fin.close();
    print_success();

}

//--------------------------------------------------------------------------------
void MoneyDeposit(string input_id) {
    
    //if the account is lost, money deposit service will be limited
    if (is_lost(input_id)) {
        cout << "\nTHIS ACCOUNT IS FROZEN" << endl;
        cout << "money deposit limited\n" << endl;
        return_to_menu2(input_id, "0");
    }

    //if the account is not lost, start the money deposit service
    else {

        for (auto it = amount.begin(); it != amount.end(); it++) {
            if (it->getID() == input_id) {

                //show the current balance and start the withdraw function 
                cout << "\nSTART MONEY DEPOSIT, YOUR CURRENT BALANCE IS: " << it->getAmount() << endl;
                cout << "please input the amount you want to deposit: " << endl;
                cout << "(the amout should be a positive number no more than 10000 and at most with 2 decimals)" << endl;
                cout << "(enter 0 to return to the personal service page at any time)" << endl;

                string input_money;
                getline(cin, input_money);
                return_to_menu2(input_id, input_money);//(if input == 0, return to the personal service page)

                //check whether the input_money is a positive number no more than 10000 and at most with 2 decimals
                //The 'is_money' function is defined in line***
                while (!is_money(input_money)) {
                    cout << "\nERROR,PLEASE INPUT AGAIN " << endl;
                    cout << "(the amout should be a positive number no more than 10000 and at most with 2 decimals)" << endl;
                    getline(cin, input_money);
                    return_to_menu2(input_id, input_money);//(if input == 0, return to the personal service page)
                }

                //create 'temp_amount1' to temporarily storge the balance info 
                string temp_amount1;
                temp_amount1 = it->getAmount();

                //change the data type into double and transmit info to 'temp_amount2'(type: double)
                double temp_amount2 = stof(temp_amount1);

                //calculate the balance
                temp_amount2 += stof(input_money);

                //change the data type into string
                stringstream ss;
                string temp_amount3;
                ss << temp_amount2;
                ss >> temp_amount3;
                it->setAmount(temp_amount3);

                //print 'successfully withdraw' and show the current balance
                cout << "\nSUCCESSFULLY DEPOSIT" << endl;
                cout << "YOUR CURRENT BALANCE IS: " << it->getAmount() << endl;

                //name the variable that will be storage in personal txt file
                string money_deposit = "+" + input_money;
                string money_left = it->getAmount();
                string time = current_time();

                //open the personal txt file to storage money deposit record
                string personal_filepath = input_id + ".txt";
                ofstream fout(personal_filepath, ios::app);
                fout << left << setw(25) << time
                    << left << setw(35) << money_deposit
                    << left << setw(25) << money_left << endl;
                fout.close();

                //print "operation successfully completed"
                print_success();

            }
        }
    }  
}

//--------------------------------------------------------------------------------
void MoneyWithdraw(string input_id) {
   
    //if the account is lost, money withdraw service will be limited
    if (is_lost(input_id)) {
        cout << "\nTHIS ACCOUNT IS FROZEN" << endl;
        cout << "money withdraw limited\n" << endl;
        return_to_menu2(input_id, "0");
    }
    
    //if the account is not lost, start the money withdraw service
    else {
       
        for (auto it = amount.begin(); it != amount.end(); it++) {
            if (it->getID() == input_id) {

                //show the current balance and start the withdraw function 
                cout << "\nSTART AMOUNT WITHDRAW, YOUR CURRENT BALANCE IS: " << it->getAmount() << endl;
                cout << "please input the amount you want to withdraw: " << endl;
                cout << "(the amout should be a positive number no more than 10000 and at most with 2 decimals)" << endl;
                cout << "(enter 0 to return to the personal service page at any time)" << endl;
                string input_money;
                getline(cin, input_money);
                return_to_menu2(input_id, input_money);//(if input == 0, return to the personal service page)

                //The is_money function check whether the input_money is a positive number no more than 10000 and at most with 2 decimals
                //The is_money is defined in line***
                while (!is_money(input_money)) {
                    cout << "\nERROR,PLEASE INPUT AGAIN " << endl;
                    cout << "(the amout should be a positive number no more than 10000 and at most with 2 decimals)" << endl;
                    getline(cin, input_money);
                    return_to_menu2(input_id, input_money);//(if input == 0, return to the personal service page)
                }

                //create 'temp_amount1' to temporarily storge the balance info 
                string temp_amount1;
                temp_amount1 = it->getAmount();

                //change the data type into double and transmit info to 'temp_amount2'(type: double)
                double temp_amount2 = stof(temp_amount1);

                //check if the input amount is larger than total balance, if so, continue to input. 
                while (temp_amount2 < stof(input_money)) {
                    cout << "\nSORRY,NO SUFFICIENT BALANCE\nyour account balance is: " << it->getAmount()
                        << ", please enter the amount to withdraw again: " << endl;
                    cout << "(the amout should be a positive number no more than 10000 and at most with 2 decimals)" << endl;
                    getline(cin, input_money);
                    return_to_menu2(input_id, input_money);//(if input == 0, return to the personal service page)
                    while (!is_money(input_money)) {
                        cout << "\nERROR,PLEASE INPUT AGAIN " << endl;
                        cout << "(the amout should be a positive number no more than 10000 and at most with 2 decimals)" << endl;
                        getline(cin, input_money);
                        return_to_menu2(input_id, input_money);//(if input == 0, return to the personal service page)
                    }
                }

                //calculate the balance left
                temp_amount2 -= stof(input_money);

                //change the data type into string
                stringstream ss;
                string temp_amount3;
                ss << temp_amount2;
                ss >> temp_amount3;
                it->setAmount(temp_amount3);

                //print 'successfully withdraw' and show the current balance
                cout << "\nSUCCESSFULLY WITHDRAW" << endl;
                cout << "YOUR CURRENT BALANCE IS: " << it->getAmount() << endl;

                //name the variable that will be storage in personal txt file
                string money_withdraw = "-" + input_money;
                string money_left = it->getAmount();
                string time = current_time();

                //open the personal txt file to storage money withdraw record
                string personal_filepath = input_id + ".txt";
                ofstream fout(personal_filepath, ios::app);
                fout << left << setw(25) << time
                    << left << setw(35) << money_withdraw
                    << left << setw(25) << money_left << endl;
                fout.close();

                //print "operation successfully completed"
                print_success();

            }
        }
    }    
}
//--------------------------------------------------------------------------------


//secondary functions


//check the Chinese identity card number
bool is_ID(string input_id) {
    int a[18] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };
    char b[18] = { '1','0','X','9','8','7','6','5','4','3','2' };
    int sum = 0;
    int i;
    for (int j = 0; j < 1; j++) {
        for (i = 0; i < 17; i++) {
            if (input_id[i] >= '0' && input_id[i] <= '9') {
                sum += (input_id[i] - '0') * a[i];
            }
            else {
                return false;
                break;
            }

        }
        if (i == 17 && b[sum % 11] != input_id[17]) {
            return false;
            break;
        }
        return true;
    }

}

//--------------------------------------------------------------------------------
// Check whether the ID exists in the System
bool is_ID_existent(string input_id) {
    for (auto it = account.begin(); it != account.end(); it++) {
        if (it->getID() == input_id) return true;
    }
    return false;
}

//--------------------------------------------------------------------------------
// Check whether the account is lost
bool is_lost(string input_id) {
    for (auto it = loss.begin(); it != loss.end(); it++) {
        if (it->getID() == input_id) return true;
    }
    return false;
}
//--------------------------------------------------------------------------------
void print_register_and_login_page() {
    cout << "|-------------WELCOME TO THE BANK SYSTEM-------------|" << endl;
    cout << "|----------------------------------------------------|" << endl;
    cout << "|                1.Account Creation                  |" << endl;
    cout << "|                2.Account Log In                    |" << endl;
    cout << "|                                          0.QUIT    |" << endl;
    cout << "|----------------------------------------------------|" << endl;
    cout << "PLEASE ENTER AN NUMBER TO START" << endl;
}

//--------------------------------------------------------------------------------
void start_operation1(string number) {
    if (number == "1") {
        AccountCreation();
    }
    if (number == "2") {
        AccountLogIn();
    }
    if (number == "0") {
        cout << "EXIT THE SYSTEM" << endl;
        update_file();
        exit(0);
    }
}

//--------------------------------------------------------------------------------
void print_personal_service_page() {

    cout << "|------------------PERSONAL PAGE---------------------|" << endl;
    cout << "|----------------------------------------------------|" << endl;
    cout << "|                1.Account Loss                      |" << endl;
    cout << "|                2.Account Balance                   |" << endl;
    cout << "|                3.Account Delete                    |" << endl;
    cout << "|                4.Money Deposit                     |" << endl;
    cout << "|                5.Money Withdraw                    |" << endl;
    cout << "|                6.Return To The Menu                |" << endl;
    cout << "|                                          0.QUIT    |" << endl;
    cout << "|----------------------------------------------------|" << endl;

}

//--------------------------------------------------------------------------------
void start_operation2(string input_id, string start_number) {

    if (start_number == "1") {
        AccountLoss(input_id);
    }
    if (start_number == "2") {
        AccountBalance(input_id);
    }
    if (start_number == "3") {
        AccountDelete(input_id);
    }
    if (start_number == "4") {
        MoneyDeposit(input_id);
    }
    if (start_number == "5") {
        MoneyWithdraw(input_id);
    }
    if (start_number == "6") {

        cout << "\nSUCCESSFULLY RETURN TO THE MENU\n" << endl;

        string start_number = "1";
        while (start_number == "1" || start_number == "2")
        {
            print_register_and_login_page();
            getline(cin, start_number);
            while (start_number != "1" && start_number != "2" && start_number != "0") {
                cout << "\nERROR: INVALID INPUT\nPlease enter a valid number:\n";
                getline(cin, start_number);
            }
            start_operation1(start_number);
        }
    }

    if (start_number == "0") {
        cout << "EXIT THE SYSTEM" << endl;
        update_file();
        exit(0);
    }
}


//--------------------------------------------------------------------------------
//return to the register and log in page
void return_to_menu1(string input_number) {

    while (input_number == "0") {

        cout << "\nSUCCESSFULLY RETURN TO THE MENU\n" << endl;

        string start_number = "1";
        while (start_number == "1" || start_number == "2")
        {
            print_register_and_login_page();
            getline(cin, start_number);
            while (start_number != "1" && start_number != "2" && start_number != "0") {
                cout << "\nERROR: INVALID INPUT\nPlease enter a valid number:\n";
                getline(cin, start_number);
            }
            start_operation1(start_number);
        }
        break;
    }
}

//--------------------------------------------------------------------------------
//return to the personal service page
void return_to_menu2(string input_id, string str) {

    while (str == "0") {

        cout << "\nSUCCESSFULLY RETURN TO THE PERSONAL SERVICE PAGE\n" << endl;

        string start_number = "1";
        while (start_number == "1" || start_number == "2" || start_number == "3" ||
            start_number == "4" || start_number == "5")
        {
            //print the personal service page
            print_personal_service_page();
            cout << "\nPLEASE ENTER AN NUMBER TO CONTINUE" << endl;
            getline(cin, start_number);
            while (start_number != "1" && start_number != "2" && start_number != "3" &&
                start_number != "4" && start_number != "5" && start_number != "0" && start_number != "6") {
                cout << "\nERROR: INVALID INPUT\nPlease enter a valid number:\n";
                cin >> start_number;
            }
            start_operation2(input_id, start_number);
        }
        break;
    }
        
}

//--------------------------------------------------------------------------------
// print SUCCESSFULLY COMPLETED
void print_success() {
    cout << "\nOPERATION SUCCESSFULLY COMPLETED\n" << endl;
}

//--------------------------------------------------------------------------------
// get the current time(including year & month & day & hour & minute & second)
string current_time() {
    time_t t;
    time(&t);
    struct tm* p;
    p = localtime(&t);
    string year = to_string(p->tm_year + 1900);
    string month = to_string(p->tm_mon + 1);
    string day = to_string(p->tm_mday);
    string hour = to_string(p->tm_hour);
    string min = to_string(p->tm_min);
    string sec = to_string(p->tm_sec);
    string str[] = { year, month, day, hour, min, sec };
    string time;
    time.append(year + "/" + month + "/" + day + "/" + hour + ":" + min + ":" + sec);
    return time;
}

//--------------------------------------------------------------------------------
// Check whether the money is a positive number no more than 10000 with at most 2 decimals
inline bool is_money(string input_money) {
    if (regex_match(input_money, regex("([0-9]{1,4})")) == true) {
        return true;
    }
    else if (regex_match(input_money, regex("([0-9]{1,4})((\\.)([0-9]{0,2}){0,1})")) == true) {
        return true;
    }
    else if (regex_match(input_money, regex("10000")) == true) {
        return true;
    }
    else if (regex_match(input_money, regex("10000.0")) == true) {
        return true;
    }
    else if (regex_match(input_money, regex("10000.00")) == true) {
        return true;
    }
    else return false;
}

//--------------------------------------------------------------------------------
//Check whether the input password consists of 6 numbers
inline bool is_password(string input_password) {
    return regex_match(input_password, regex("([0-9]{6})"));
}

//--------------------------------------------------------------------------------
//Check whether the two input passwords are the same 
bool check_password(string input_password, string input_password_check) {
    if (input_password != input_password_check) {
        return false;
    }
    else {
        return true;
    }
}

//--------------------------------------------------------------------------------
void delete_account(vector<Account>& account_info, vector<Amount>& amount_info, vector<Loss>& loss_info, string input_id) {

    //delete account info in vector array 'account'
    for (auto it = account_info.begin(); it != account_info.end(); it++) {
        if (it->getID() == input_id) {
            account_info.erase(it);
            break;
        }
    }

    //delete account info in vector array 'amount'
    for (auto it = amount_info.begin(); it != amount_info.end(); it++) {
        if (it->getID() == input_id) {
            amount_info.erase(it);
            break;
        }
    }

    //delete account info in vector array 'loss'
    for (auto it = loss_info.begin(); it != loss_info.end(); it++) {
        if (it->getID() == input_id) {
            loss_info.erase(it);
            break;
        }
        break;
    }

    //delete personal txt file
    string personal_filepath = input_id + ".txt";
    const char* path = personal_filepath.data();
    remove(path);

    update_file();

}

//--------------------------------------------------------------------------------
void update_file() {

    //update info in 'account.txt'
    ofstream account_fout(account_filepath, ios::out);
    for (auto it = account.begin(); it != account.end(); it++) {
        account_fout << left << setw(25) << it->getID() << left << setw(25)
            << it->getName() << left << setw(25) << it->getPassword() << endl;
    }
    account_fout.close();

    //update info in 'amount.txt'
    ofstream amount_fout(amount_filepath, ios::out);
    for (auto it = amount.begin(); it != amount.end(); it++) {
        amount_fout << left << setw(25) << it->getID() << left << setw(25)
            << it->getAmount() << endl;
    }
    amount_fout.close();

    //update info in 'loss.txt'
    ofstream loss_fout(loss_filepath, ios::out);
    for (auto it = loss.begin(); it != loss.end(); it++) {
        loss_fout << it->getID() << endl;
    }
    loss_fout.close();

}

//--------------------------------------------------------------------------------
//import info from txt file to the system
void initialize_variables() {

    //put account info into the system
    ifstream account_fin;
    account_fin.open(account_filepath);
    string temp1;
    while (true) {
        getline(account_fin, temp1);
        if (account_fin.eof()) break;
        stringstream ss(temp1);
        string input_id, input_name, input_password;
        ss >> input_id >> input_name >> input_password;
        Account temp_account(input_id, input_name, input_password);
        account.push_back(temp_account);
    }

    //put amount info into the system
    ifstream amount_fin;
    amount_fin.open(amount_filepath);
    string temp2;
    while (true) {
        getline(amount_fin, temp2);
        if (amount_fin.eof()) break;
        stringstream ss(temp2);
        string input_id, input_amount;
        ss >> input_id >> input_amount;
        Amount temp_amount(input_id, input_amount);
        amount.push_back(temp_amount);
    }

    //put loss info into the system
    ifstream loss_fin;
    loss_fin.open(loss_filepath);
    string temp3;
    while (true) {
        getline(loss_fin, temp3);
        if (loss_fin.eof()) break;
        stringstream ss(temp3);
        string input_id;
        ss >> input_id;
        Loss temp_loss(input_id);
        loss.push_back(temp_loss);
    }

    account_fin.close();
    amount_fin.close();
    loss_fin.close();
}


//--------------------------------------------------------------------------------
int main()
{
    system("color F0");

    ofstream account_fout(account_filepath, ios::out | ios::app);
    ofstream amount_fout(amount_filepath, ios::out | ios::app);
    ofstream loss_fout(loss_filepath, ios::out | ios::app);

    initialize_variables();

    string start_number = "1";

    while (start_number == "1" || start_number == "2")
    {
        print_register_and_login_page();
        getline(cin, start_number);
        while (start_number != "1" && start_number != "2" && start_number != "0") {
            cout << "\nERROR: INVALID INPUT\nPlease enter a valid number:\n";
            getline(cin, start_number);
        }
        start_operation1(start_number);
    }

    update_file();

    account_fout.close();
    amount_fout.close();
    loss_fout.close();


    return 0;
}


