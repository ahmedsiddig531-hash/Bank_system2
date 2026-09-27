
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenue();
void ShowUsersMenu();
string ReadUserName();
void Login();
void ATMMainMenuScreen();
void GoBackToMainMenue1();

enum enPermissions
{
    eAll = -1,
    eListClientsPermission = 1,
    eAddClientPermission = 2,
    eDeleteClientPermission = 4,
    eUpdateClientPermission = 8,
    eFindClientPermission = 16,
    eTransactionsPermission = 32,
    eManageUsersPermission = 64
};

enum enQuickWithdraw { ch1 = 1, ch2 = 2, ch3 = 3, ch4 = 4, ch5 = 5, ch6 = 6, ch7 = 7, ch8 = 8, ch9 = 9 };

enum enATM { enQuickWithDraw = 1, enNormalWithDraw = 2, enDeposite = 3, enCheckBlance = 4, enlogout = 5 };

enum enTransactionsMenu
{
    enDeposit = 1, enWithDraw = 2, enTotalBalance = 3, enMainMenu = 4
};

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, enTransactions = 6, eManageUsers = 7, eExit = 8
};

enum enUsersMenuOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
};

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

struct sUsers {
    string UserName;
    string UserPassWord;
    int UserPermessions = 0;
    bool MarkForDelete1 = false;

};

sUsers CurrentUser;
sClient CurrentClient;


vector<sUsers> LoadUsersDataFromFile(string FileName);

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    size_t pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}


void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerformTransactionsOptions(enTransactionsMenu);
void GoBackToTransactionsMenue();
void ShowDepositScreen();
void ShowWithDrawScreen();
void ShowTotalAmountScreen();
void ShowTransactionsMenue();
bool WithDrawUsingAccountNumber(vector<sClient>& vClients);


enTransactionsMenu ReadTransactionsMenueOption()
{
    short Choice = 0;

    do {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);

    return (enTransactionsMenu)Choice;
}

bool DepositUsingAccountNumber(vector<sClient>& vClients)
{
    string AccountNumber;
    sClient Client;

    // Keep asking until a valid account number is entered.
    while (true)
    {
        cout << "Please enter Account Number: ";
        cin >> AccountNumber;

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            break;

        cout << "\nClient with Account Number (" << AccountNumber
            << ") was not found. Please try again.\n\n";
    }

    PrintClientCard(Client);

    double Amount = 0.0;
    while (true)
    {
        cout << "\nPlease enter deposit amount: ";

        if (!(cin >> Amount))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        if (Amount > 0)
            break;

        cout << "\nInvalid amount.\n";
    }

    char Answer;
    cout << "\nAre you sure you want to perform this operation ? (Y/N): ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "\nDeposit completed successfully.\n";
        return true;
    }

    cout << "\nDeposit cancelled.\n";
    return false;
}

void TransactionsRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsTransactioScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            TransactionsRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

double CountTotalAmount() {

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    double TotalAmount = 0;
    for (sClient& Client : vClients)
    {

        TotalAmount += Client.AccountBalance;
    }
    return TotalAmount;
}

void ShowTransactionClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\t Transactions Screen";
    cout << "\n-----------------------------------\n";
    ShowTransactionsMenue();
}

void ShowManageUsersScreen()
{
    ShowUsersMenu();
}

bool WithDrawUsingAccountNumber(vector<sClient>& vClients)
{
    string AccountNumber;
    sClient Client;

    // Keep asking until a valid account number is entered.
    while (true)
    {
        cout << "Please enter Account Number: ";
        cin >> AccountNumber;

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            break;

        cout << "\nClient with Account Number (" << AccountNumber
            << ") was not found. Please try again.\n\n";
    }

    // Show client information.
    PrintClientCard(Client);

    double Amount;

    // Keep asking until a valid withdrawal amount is entered.
    while (true)
    {
        cout << "\nPlease enter withdrawal amount: ";

        if (!(cin >> Amount))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        if (Amount <= 0)
        {
            cout << "\nInvalid amount.\n";
            continue;
        }

        if (Amount > Client.AccountBalance)
        {
            cout << "\nAmount exceeds the balance. "
                << "You can withdraw up to "
                << Client.AccountBalance << ".\n";
            continue;
        }

        break;
    }

    char Answer;
    cout << "\nAre you sure you want to perform this operation? (Y/N): ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                cout << "\nBalance Before: " << C.AccountBalance << endl;

                C.AccountBalance -= Amount;

                cout << "Balance After : " << C.AccountBalance << endl;

                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "\nWithDraw completed successfully.\n";
        return true;
    }

    cout << "\nWithDraw cancelled.\n";
    return false;
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositUsingAccountNumber(vClients);
    GoBackToTransactionsMenue();

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithDraw Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    WithDrawUsingAccountNumber(vClients);
    GoBackToTransactionsMenue();

}

void ShowTotalAmountScreen()
{
    ShowAllClientsTransactioScreen();
    cout << "\n\t\t Total Balance = " << CountTotalAmount();
    cout << endl;
    GoBackToTransactionsMenue();

}

void PerformTransactionsOptions(enTransactionsMenu TransactionsMenu)
{
    switch (TransactionsMenu) {
    case enTransactionsMenu::enDeposit:
        system("cls");
        ShowDepositScreen();
        break;

    case enTransactionsMenu::enWithDraw:
        system("cls");
        ShowWithDrawScreen();

        break;

    case enTransactionsMenu::enTotalBalance:
        system("cls");
        ShowTotalAmountScreen();
        break;

    case enTransactionsMenu::enMainMenu:
        system("cls");
        GoBackToMainMenue();
        break;
    }
}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] WithDraw\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] MainMenu\n";
    cout << "===========================================\n";

    PerformTransactionsOptions((enTransactionsMenu)ReadTransactionsMenueOption());


}


void GoBackToTransactionsMenue()
{

    system("pause>0");
    ShowTransactionsMenue();

}

bool CheckAccess(enPermissions Permission)
{
    if (CurrentUser.UserPermessions == eAll)
        return true;

    return (CurrentUser.UserPermessions & Permission) != 0;
}
void PermissionScreen()
{
    system("cls");
    cout << "\n---------------------------------------\n";
    cout << "Access Denied\nYou Don't Have Permission To Do This,\nPlease Contact Your Admin\n";
    cout << "\n---------------------------------------\n";
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:

        if (!CheckAccess(eListClientsPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eAddNewClient:
        if (!CheckAccess(eAddClientPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        if (!CheckAccess(eDeleteClientPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        if (!CheckAccess(eUpdateClientPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        if (!CheckAccess(eFindClientPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::enTransactions:

        if (!CheckAccess(eTransactionsPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowTransactionClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eManageUsers:
        if (!CheckAccess(eManageUsersPermission))
        {
            PermissionScreen();
            GoBackToMainMenue();
            break;
        }

        system("cls");
        ShowManageUsersScreen();
        break;

    case enMainMenueOptions::eExit:
        Login();
        break;
    }
}

bool FindUserByUserName(string UsersName, vector <sUsers> vUsers, sUsers& User)
{
    for (sUsers U : vUsers)
    {
        if (U.UserName == UsersName)
        {
            User = U;
            return true;
        }
    }
    return false;
}


void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Mangage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}


short ReadUsersMenuOption()
{
    short Choice = 0;

    do
    {
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 6);

    return Choice;
}


void PrintUserCard(sUsers User)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name   : " << User.UserName;
    cout << "\nPassword    : " << User.UserPassWord;
    cout << "\nPermissions : " << User.UserPermessions;
    cout << "\n-----------------------------------\n";
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    sUsers User;
    string UserName = ReadUserName();

    if (FindUserByUserName(UserName, vUsers, User))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "\nUser with UserName [" << UserName
            << "] is not found!";
    }
}

sUsers ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{
    sUsers sUser;
    vector<string>  vUser;
    vUser = SplitString(Line, Seperator);

    sUser.UserName = vUser[0];
    sUser.UserPassWord = vUser[1];
    sUser.UserPermessions = stoi(vUser[2]);

    return sUser;

}

bool UserExistsByUserName(string  UserName, string FileName)
{

    vector <sUsers> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUsers sUser;

        while (getline(MyFile, Line))
        {
            sUser = ConvertUserLinetoRecord(Line);

            if (sUser.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
            vUser.push_back(sUser);
        }

        MyFile.close();

    }
    return false;
}

sUsers ReadNewUser()
{
    sUsers sUser;
    sUser.UserPermessions = 0;
    char FullAccess = 'Y';
    cout << "Enter UserName? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, sUser.UserName);

    while (UserExistsByUserName(sUser.UserName, UsersFileName))
    {
        cout << "\nUser with [" << sUser.UserName << "] already exists, Enter another Username? ";
        getline(cin >> ws, sUser.UserName);
    }

    cout << "Enter Password? ";
    getline(cin, sUser.UserPassWord);

    do {
        cout << "Do you want to give full access?";
        cin >> FullAccess;
    } while (toupper(FullAccess) != 'Y' && toupper(FullAccess) != 'N');

    if (toupper(FullAccess) == 'Y')
    {
        sUser.UserPermessions = eAll;
    }

    else
    {

        char Answer;

        cout << "Do you want to give List Clients permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eListClientsPermission;


        cout << "Do you want to give Add Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eAddClientPermission;


        cout << "Do you want to give Delete Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eDeleteClientPermission;


        cout << "Do you want to give Update Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eUpdateClientPermission;


        cout << "Do you want to give Find Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eFindClientPermission;


        cout << "Do you want to give Transactions permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eTransactionsPermission;


        cout << "Do you want to give Manage Users permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            sUser.UserPermessions |= eManageUsersPermission;

    }

    return sUser;
}

string ConvertUserRecordToLine(sUsers sUser, string Seperator = "#//#")
{

    string UserLine = "";
    UserLine += sUser.UserName + Seperator;
    UserLine += sUser.UserPassWord + Seperator;
    UserLine += to_string(sUser.UserPermessions);

    return UserLine;
}

void AddNewUser()
{
    sUsers sUser;
    sUser = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(sUser));
}

bool MarkUserForDeleteByUserName(string UserName, vector<sUsers>& vUsers)
{
    for (sUsers& U : vUsers)
    {
        if (U.UserName == UserName)
        {
            U.MarkForDelete1 = true;
            return true;
        }
    }

    return false;
}

vector<sUsers> SaveUsersDataToFile(string FileName, vector<sUsers> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (sUsers U : vUsers)
        {
            if (U.MarkForDelete1 == false)
            {
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vUsers;
}

bool DeleteUserByUserName(string UserName, vector<sUsers>& vUsers)
{
    sUsers User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {
        cout << "\n\nUser Information:\n";
        cout << "-----------------------------------\n";
        cout << "User Name   : " << User.UserName << endl;
        cout << "Password    : " << User.UserPassWord << endl;
        cout << "Permissions : " << User.UserPermessions << endl;
        cout << "-----------------------------------\n";

        cout << "\nAre you sure you want to delete this user? Y/N? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUserName(UserName, vUsers);

            SaveUsersDataToFile(UsersFileName, vUsers);

            // Refresh users
            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\nUser Deleted Successfully.";

            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName
            << ") is Not Found!";

        return false;
    }

    return false;
}

sUsers ChangeUserRecord(string UserName)
{
    sUsers User;

    User.UserName = UserName;

    cout << "\nEnter Password? ";
    getline(cin >> ws, User.UserPassWord);

    User.UserPermessions = 0;

    char FullAccess;

    cout << "Do you want to give full access? Y/N? ";
    cin >> FullAccess;

    if (toupper(FullAccess) == 'Y')
    {
        User.UserPermessions = eAll;
    }
    else
    {
        char Answer;

        cout << "Do you want to give List Clients permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eListClientsPermission;


        cout << "Do you want to give Add Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eAddClientPermission;


        cout << "Do you want to give Delete Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eDeleteClientPermission;


        cout << "Do you want to give Update Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eUpdateClientPermission;


        cout << "Do you want to give Find Client permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eFindClientPermission;


        cout << "Do you want to give Transactions permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eTransactionsPermission;


        cout << "Do you want to give Manage Users permission? Y/N? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            User.UserPermessions |= eManageUsersPermission;
    }

    return User;
}

bool UpdateUserByUserName(string UserName, vector<sUsers>& vUsers)
{
    sUsers User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {
        cout << "\n\nUser Information:\n";
        cout << "-----------------------------------\n";
        cout << "User Name   : " << User.UserName << endl;
        cout << "Password    : " << User.UserPassWord << endl;
        cout << "Permissions : " << User.UserPermessions << endl;
        cout << "-----------------------------------\n";

        cout << "\nAre you sure you want to update this user? Y/N? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUsers& U : vUsers)
            {
                if (U.UserName == UserName)
                {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }

            SaveUsersDataToFile(UsersFileName, vUsers);

            cout << "\nUser Updated Successfully.";

            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName
            << ") is Not Found!";

        return false;
    }

    return false;
}

string ReadUserName()
{
    string UserName = "";

    cout << "\nPlease enter UserName? ";
    cin >> UserName;

    return UserName;
}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    string UserName = ReadUserName();

    UpdateUserByUserName(UserName, vUsers);
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    string UserName = ReadUserName();

    DeleteUserByUserName(UserName, vUsers);
}

void ShowNewClientScreen()
{
    cout << "\n----------------------------------\n";
    cout << "\tAdd New Client Screen";
    cout << "\n----------------------------------\n";
}

void ShowNewUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";
}

void AddNewUsers()
{
    char AddMore = 'Y';
    ShowNewUserScreen();
    do
    {
        //system("cls"); 
        cout << "\nAdding New users:\n\n";
        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

vector <sUsers> LoadUsersDataFromFile(string FileName)
{
    vector <sUsers> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUsers sUser;

        while (getline(MyFile, Line))
        {
            sUser = ConvertUserLinetoRecord(Line);
            vUser.push_back(sUser);
        }

        MyFile.close();
    }
    return vUser;
}

void PrintUserRecordLine(sUsers sUser)
{
    cout << "| " << setw(15) << left << sUser.UserName;
    cout << "| " << setw(10) << left << sUser.UserPassWord;
    cout << "| " << setw(40) << left << sUser.UserPermessions;

}

void ShowAllUsersScreen()
{

    vector <sUsers> vUser = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUsers List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUser.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else

        for (sUsers U : vUser)
        {

            PrintUserRecordLine(U);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void ShowLoginScreen()
{
    cout << "\n----------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n----------------------------------\n";
}

void PerformUsersMenuOption(enUsersMenuOptions UsersMenuOption)
{
    switch (UsersMenuOption)
    {
    case enUsersMenuOptions::eListUsers:
        system("cls");
        ShowAllUsersScreen();
        system("pause>0");
        ShowUsersMenu();
        break;

    case enUsersMenuOptions::eAddNewUser:
        system("cls");
        AddNewUsers();
        system("pause>0");
        ShowUsersMenu();
        break;

    case enUsersMenuOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        system("pause>0");
        ShowUsersMenu();
        break;

    case enUsersMenuOptions::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        system("pause>0");
        ShowUsersMenu();
        break;

    case enUsersMenuOptions::eFindUser:
        system("cls");
        ShowFindUserScreen();
        system("pause>0");
        ShowUsersMenu();
        break;

    case enUsersMenuOptions::eMainMenu:
        system("cls");
        ShowMainMenue();
        break;
    }
}

void UpdateClientBalance()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient& Client : vClients)
    {
        if (Client.AccountNumber == CurrentClient.AccountNumber)
        {
            Client.AccountBalance = CurrentClient.AccountBalance;
            break;
        }
    }

    SaveCleintsDataToFile(ClientsFileName, vClients);
}

void ShowUsersMenu()
{
    system("cls");

    cout << "===========================================\n";
    cout << "              Users Menu\n";
    cout << "===========================================\n";
    cout << "[1] List Users\n";
    cout << "[2] Add New User\n";
    cout << "[3] Delete User\n";
    cout << "[4] Update User\n";
    cout << "[5] Find User\n";
    cout << "[6] Main Menu\n";
    cout << "===========================================\n";

    PerformUsersMenuOption(
        (enUsersMenuOptions)ReadUsersMenuOption()
    );
}
double DepositAmount()
{
    double Amount;

    do
    {
        cout << "Enter Deposit Amount: ";
        cin >> Amount;

        if (Amount <= 0)
        {
            cout << "Amount must be greater than zero.\n";
        }

    } while (Amount <= 0);

    return Amount;
}

void Deposit(double Amount)
{
    CurrentClient.AccountBalance += Amount;

    UpdateClientBalance();
}
void ShowATMDepositScreen()
{
    system("cls");

    cout << "===========================================\n";
    cout << "\t\tDeposit Screen\n";
    cout << "===========================================\n";

    cout << "Current Balance: " << CurrentClient.AccountBalance << endl;

    double Amount = DepositAmount();

    Deposit(Amount);

    cout << "\nDeposit completed successfully.\n";
    cout << "New Balance: " << CurrentClient.AccountBalance << endl;

    GoBackToMainMenue1();
}

short ReadATMChoice()
{
    short choice = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 5]?";
        cin >> choice;
    } while (choice < 1 || choice > 5);

    return choice;
}


double WithdrawalAmount()
{
    double Amount = 0;

    while (true)
    {
        cout << "\nPlease enter withdrawal amount: ";

        if (!(cin >> Amount))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        if (Amount <= 0)
        {
            cout << "\nInvalid amount.\n";
            continue;
        }

        if (Amount > CurrentClient.AccountBalance)
        {
            cout << "\nAmount exceeds the balance. "
                << "You can withdraw up to "
                << CurrentClient.AccountBalance << ".\n";
            continue;
        }

        break;
    }

    return Amount;
}

bool WithDraw(double Amount)
{
    char Answer = 'Y';

    cout << "\nAre you sure you want to perform this operation? (Y/N): ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
    {
        CurrentClient.AccountBalance -= Amount;
        UpdateClientBalance();
        return true;
    }
    return false;
}

bool QuickWithdrawalAmount(double Amount)
{
    if (Amount <= 0)
    {
        cout << "\nInvalid amount.\n";
        return false;
    }

    if (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nAmount exceeds the balance. "
            << "You can withdraw up to "
            << CurrentClient.AccountBalance << ".\n";
        return false;
    }

    char Answer = 'Y';

    cout << "\nAre you sure you want to perform this operation? (Y/N): ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
    {
        CurrentClient.AccountBalance -= Amount;
        cout << "\nSuccessfully, New Balance is " << CurrentClient.AccountBalance;
        UpdateClientBalance();
        return true;
    }
    return false;
}

void ShowNormalWithdrawScreen()
{
    cout << "\n===================================\n";
    cout << "\t\tNormal Withdraw";
    cout << "\n===================================\n";

    cout << "\nYour Balance is "
        << CurrentClient.AccountBalance << "\n\n";

    double Amount = WithdrawalAmount();

    if (WithDraw(Amount))
    {
        cout << "\nSuccessfully, New Balance is "
            << CurrentClient.AccountBalance;
    }
    else
    {
        cout << "\nWithdrawal cancelled.";
    }

    GoBackToMainMenue1();
}

enQuickWithdraw QuickWithdrawChoice()
{
    int choice = 0;
    do {
        cout << "Choose what do you want to withdraw? [1 to 9]?";
        cin >> choice;
    } while (choice < 1 || choice > 9);

    return (enQuickWithdraw)choice;

}

void GoBackToMainMenue1()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ATMMainMenuScreen();

}

void PerfromQuickWithDrawOptions(enQuickWithdraw choice)
{
    switch (choice)
    {
    case enQuickWithdraw::ch1:
        QuickWithdrawalAmount(20);
        GoBackToMainMenue1();
        break;

    case enQuickWithdraw::ch2:
        QuickWithdrawalAmount(50);
        GoBackToMainMenue1();
        break;

        // ...

    case enQuickWithdraw::ch8:
        QuickWithdrawalAmount(1000);
        GoBackToMainMenue1();
        break;

    case enQuickWithdraw::ch9:
        ATMMainMenuScreen();
        break;
    }
}

void  ShowQuickWithdrawScreen()
{
    cout << "\n===================================\n";
    cout << "\t\tQuick Withdraw";
    cout << "\n===================================\n";
    cout << "\t[1] 20    \t[2] 50\n";
    cout << "\t[3] 100   \t[4] 200\n";
    cout << "\t[5] 400   \t[6] 600\n";
    cout << "\t[7] 800   \t[8] 1000\n";
    cout << "\t[9] Exit ";
    cout << "\n===================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance << "\n\n";
    PerfromQuickWithDrawOptions(QuickWithdrawChoice());
}

void ShowCheckBalanceScreen()
{
    cout << "\n===================================\n";
    cout << "\tBalance Screen";
    cout << "\n===================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
    GoBackToMainMenue1();
}

void PerfromATmOperations(enATM ATM)
{
    switch (ATM)
    {
    case enATM::enQuickWithDraw:
        system("cls");
        ShowQuickWithdrawScreen();
        break;
    case enATM::enNormalWithDraw:
        system("cls");
        ShowNormalWithdrawScreen();
        break;

    case enATM::enDeposite:
        system("cls");
        ShowATMDepositScreen();
        break;

    case enATM::enCheckBlance:
        system("cls");
        ShowCheckBalanceScreen();
        break;
    case enATM::enlogout:
        system("cls");
        Login();
        break;


    }
}

void ATMMainMenuScreen()
{
    system("cls");
    cout << "\n============================================\n";
    cout << "\tATM Main Menu Screen";
    cout << "\n============================================\n";
    cout << "\t[1] Quick Withdraw\n";
    cout << "\t[2] Normal Withdraw\n";
    cout << "\t[3] Deposite\n";
    cout << "\t[4] Check Balance\n";
    cout << "\t[5] Logout";
    cout << "\n============================================\n";
    PerfromATmOperations(enATM(ReadATMChoice()));
}

void Login()
{
    ShowLoginScreen();

    string  AccountNumber;
    string  PinCode;

    vector<sClient>  vClient = LoadCleintsDataFromFile(ClientsFileName);

    sClient Client;
    bool LoginFailed = false;

    do
    {
        system("cls");
        ShowLoginScreen();

        if (LoginFailed)
        {
            cout << "\nInvalid AccountNumber/Pincode!\n";
        }

        cout << "Enter Account Number ? ";
        cin >> AccountNumber;

        cout << "Enter PinCode ? ";
        cin >> PinCode;

        if (FindClientByAccountNumber(AccountNumber, vClient, Client))
        {
            if (Client.PinCode == PinCode)
            {
                CurrentClient = Client;
                ATMMainMenuScreen();
                break;
            }
        }

        LoginFailed = true;

    } while (true);
}

int main()

{
    Login();

    system("pause>0");
    return 0;
}