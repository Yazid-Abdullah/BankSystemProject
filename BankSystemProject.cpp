#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;


//My Bank System ... 


struct stClient {

	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;

};
const string FileName = "BankSystemProject1";

//Base Functions
vector <string > splitString(string statment, string seperator = "/##/") {

	int pos;
	string word = "";
	vector <string> v;

	while ((pos = statment.find(seperator)) != string::npos) {


		word = statment.substr(0, pos);

		if (word != "") {
			v.push_back(word);
		}

		statment.erase(0, pos + seperator.length());


	}


	if (statment != "") {
		v.push_back(statment);
	}



	return v;
}
string convertRecordToLine(stClient client, string seperator = "/##/") {

	string Line = "";

	Line = Line + client.AccountNumber + seperator;
	Line = Line + client.PinCode + seperator;
	Line = Line + client.Name + seperator;
	Line = Line + client.Phone + seperator;
	Line = Line + to_string(client.AccountBalance);

	return Line;

}
stClient convertLineToRecord(string Line, string seperator = "/##/") {

	stClient client;
	vector <string> v = splitString(Line, seperator);

	client.AccountNumber = v[0];
	client.PinCode = v[1];
	client.Name = v[2];
	client.Phone = v[3];
	client.AccountBalance = stod(v[4]);

	return client;

}



// File
vector <stClient> getDataFromFile() {

	string Line;
	stClient client;
	vector <stClient> v;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	while (getline(MyFile, Line)) {

		client = convertLineToRecord(Line);
		v.push_back(client);


	}

	MyFile.close();

	return v;

}


// Client Function
void readClientData(stClient& client) {

	cin.ignore();

	cout << "Enter Pin Code : ";
	getline(cin, client.PinCode);


	cout << "Enter Name : ";
	getline(cin, client.Name);


	cout << "Enter Phone : ";
	getline(cin, client.Phone);

	cout << "Enter Account Balance : ";
	cin >> client.AccountBalance;

}
bool isClientThere(string AccountNumber) {

	vector<stClient> v = getDataFromFile();
	for (stClient& client : v) {

		if (client.AccountNumber == AccountNumber) {
			return true;
		}

	}

	return false;
}
void printClientDetails(stClient Client) {

	cout << "The Following Are Client Details :         " << endl;
	cout << "-------------------------------------------" << endl;
	cout << Client.AccountNumber << endl;
	cout << Client.PinCode << endl;
	cout << Client.Name << endl;
	cout << Client.Phone << endl;
	cout << Client.AccountBalance << endl;
	cout << "-------------------------------------------" << endl;

}




// Main
void showMenuScreen() {
	cout << "---------------------------------------------" << endl;
	cout << "                   Main Menu Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "            [1] Show Client List             " << endl;
	cout << "            [2] Add New Client              " << endl;
	cout << "            [3] Delete Client               " << endl;
	cout << "            [4] Update Client Info              " << endl;
	cout << "            [5] Find Client               " << endl;
	cout << "            [6] Exit             " << endl;
	cout << "---------------------------------------------" << endl;

}
int readUserChoice() {

	int choice;

	do {

		cout << "Choose what do you want to do ? [ 1 to 6 ] ?  ";
		cin >> choice;

	} while (choice <= 0 || choice >= 7);

	return choice;
}
void BackToMenu() {

	cout << "Press any key to go back to main menu ....";
	_getch();
}
void PrintClientRecord(stClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber
		<< "| " << left << setw(15) << Client.PinCode
		<< "| " << left << setw(30) << Client.Name
		<< "| " << left << setw(15) << Client.Phone
		<< "| " << right << setw(15) << Client.AccountBalance
		<< " |" << endl;
}
void showClientList()
{

	system("cls");
	vector<stClient> v = getDataFromFile();
	cout << "\n\t\t\tClient List (" << v.size() << ") Client(s)." << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << left << setw(15) << "PIN Code"
		<< "| " << left << setw(30) << "Client Name"
		<< "| " << left << setw(15) << "Phone"
		<< "| " << right << setw(15) << "Balance"
		<< " |" << endl;

	cout << "------------------------------------------------------------------------------------------" << endl;

	for (stClient& Client : v)
	{
		PrintClientRecord(Client);
	}

	cout << "------------------------------------------------------------------------------------------" << endl;
}


stClient getClientInformationByAccountNumber(string AccountNumber) {

	vector<stClient> v = getDataFromFile();
	for (stClient& client : v) {

		if (AccountNumber == client.AccountNumber) {

			return client;

		}

	}
}
stClient getExistingClient() {







	string AccountNumber;
	cout << "Please enter the Account Number : ";
	cin >> AccountNumber;

	do {

		if (!isClientThere(AccountNumber)) {

			cout << endl;
			cout << endl;
			cout << "Client with [" << AccountNumber << "] is not exist , Enter Another Account Number : ";
			cin >> AccountNumber;

		}


	} while (!isClientThere(AccountNumber));


	return getClientInformationByAccountNumber(AccountNumber);

}

//Add
void addClientToFile(stClient client) {

	string Line = convertRecordToLine(client);
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {

		MyFile << Line << endl;

	}

	MyFile.close();

}
void addNewClients() {

	system("cls");
	cout << "---------------------------------------------" << endl;
	cout << "          Add New Clients Screen            " << endl;
	cout << "---------------------------------------------" << endl;

	string AccountNumber;
	stClient Client;
	char Again = 'f';
	bool notFirst = false;

	do {

		if (notFirst == true) {
			system("cls");
			cout << "---------------------------------------------" << endl;
			cout << "          Add New Clients Screen            " << endl;
			cout << "---------------------------------------------" << endl;
		}
		cout << "Enter Account Number : ";
		cin >> AccountNumber;

		do {

			if (isClientThere(AccountNumber)) {

				cout << endl;
				cout << endl;
				cout << "Client with [" << AccountNumber << "] already exists , Enter Another Account Number : ";
				cin >> AccountNumber;

			}


		} while (isClientThere(AccountNumber));


		Client.AccountNumber = AccountNumber;
		readClientData(Client);
		addClientToFile(Client);
		cout << endl;
		cout << "Client Added Succesefully ... Do you want to add more clients ? (Y / N) ? ";
		cin >> Again;
		notFirst = true;

	} while (toupper(Again) == 'Y');

}

//Find
 
void findClient() {

	system("cls");

	cout << "---------------------------------------------" << endl;
	cout << "          Find Clients Screen            " << endl;
	cout << "---------------------------------------------" << endl;




	stClient client;
	client = getExistingClient();
	cout << endl;
	printClientDetails(client);
	cout << endl;









}

//Delete
void deleteClientByAccountNumber(string AccountNumber) {

	vector <stClient> v = getDataFromFile();
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	for (stClient& client : v) {


		string Line = convertRecordToLine(client);



		if (MyFile.is_open()) {

			if (AccountNumber != client.AccountNumber) {
				MyFile << Line << endl;
			}


		}



	}

	MyFile.close();
}
void deleteClient() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "           Delete Client Screen            " << endl;
	cout << "---------------------------------------------" << endl;

	 
	stClient client;
	char sure = 'f';

	client = getExistingClient();
	printClientDetails(client);
	cout << endl;

	cout << "Are you sure you want to delete this client ? (Y / N) ? ";
	cin >> sure;

	if (toupper(sure) == 'Y') {
		deleteClientByAccountNumber(client.AccountNumber);
		cout << "Client Deleted Succsessfully" << endl;
	}










}

//Update
void updateClientByAccountNumber(string AccountNumber) {


	vector <stClient> v = getDataFromFile();
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	for (stClient& client : v) {


		string Line = convertRecordToLine(client);

		if (MyFile.is_open()) {

			if (AccountNumber == client.AccountNumber) {


				readClientData(client);
				Line = convertRecordToLine(client);
				MyFile << Line << endl;

			}
			else {


				MyFile << Line << endl;
			}

		}



	}
	MyFile.close();
}
void updateClient() {

	system("cls");


	cout << "---------------------------------------------" << endl;
	cout << "           Update Client Screen            " << endl;
	cout << "---------------------------------------------" << endl;
	char sure = 'f';
	stClient client;

	client = getExistingClient();
	printClientDetails(client);
	cout << endl;

	cout << "Are you sure you want to update this client ? (Y / N ) ? ";
	cin >> sure;

	if (toupper(sure) == 'Y') {
		updateClientByAccountNumber(client.AccountNumber);
		cout << "Client Updated Succsessfully" << endl;
	}


}

//Exit
void Exit() {

	system("cls");
	cout << "---------------------------------------" << endl;
	cout << "           Program Ends :)             " << endl;
	cout << "---------------------------------------" << endl;
}

// Main
void runBankSystem() {

	int choice = 0;

	do {

		system("cls");
		showMenuScreen();
		choice = readUserChoice();

		switch (choice) {

		case 1: {

			showClientList();
			BackToMenu();
			break;
		}

		case 2: {

			addNewClients();
			BackToMenu();
			break;
		}

		case 3: {

			deleteClient();
			BackToMenu();
			break;
		}

		case 4: {

			updateClient();
			BackToMenu();
			break;
		}

		case 5: {

			findClient();
			BackToMenu();
			break;
		}

		case 6: {

			Exit();
			return;
		}



		}



	} while (true);
}

int main()
{

	runBankSystem();

}

