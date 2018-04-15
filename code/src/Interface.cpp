#include "Interface.h"
#include <cctype>
#include <locale>

const char CPPKEYUP = 72;
const char CPPKEYLEFT = 75;
const char CPPKEYRIGHT = 77;
const char CPPKEYDOWN = 80;

void gotoxy(int x, int y) {
	static HANDLE hStdout = NULL;
	COORD coord;

	coord.X = x;
	coord.Y = y;

	if (!hStdout) {
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(hStdout, coord);
}

Database Interface::getDatabase() const {
	return db;
}
/*********************/
/**General Interface**/
/*********************/

void Interface::showInitialScreen() {
	int ytemp;
	int xtemp;

	for (int i = 0; i < 5; i++) {

		xtemp = 1 + 2 * i;
		ytemp = 1 + 2 * i;

		for (; xtemp < 77 - 2 * i; xtemp++) {
			gotoxy(xtemp, ytemp);
			cout << (char) 205;
			gotoxy(xtemp, ytemp + 22 - 4 * i);
			cout << (char) 205;
			Sleep(3);
		}

		xtemp = 1 + 2 * i;

		for (; ytemp < 24 - 2 * i; ytemp++) {
			gotoxy(xtemp, ytemp);
			cout << (char) 186;
			gotoxy(xtemp + 76 - 4 * i, ytemp);
			cout << (char) 186;
			Sleep(3);
		}

		ytemp = 1 + 2 * i;
		gotoxy(xtemp, ytemp);
		cout << (char) 205;

		gotoxy(xtemp + 76 - 4 * i, ytemp);
		cout << (char) 187;

		gotoxy(xtemp, ytemp + 22 - 4 * i);
		cout << (char) 200;

		gotoxy(xtemp + 76 - 4 * i, ytemp + 22 - 4 * i);
		cout << (char) 188;

	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | FOREGROUND_RED);

	gotoxy(28, 12);
	cout << "W";
	Sleep(100);
	cout << "E";
	Sleep(100);
	cout << "L";
	Sleep(100);
	cout << "C";
	Sleep(100);
	cout << "O";
	Sleep(100);
	cout << "M";
	Sleep(100);
	cout << "E";
	Sleep(100);
	cout << " ";
	Sleep(100);
	cout << "T";
	Sleep(100);
	cout << "O";
	Sleep(100);
	cout << " ";
	Sleep(100);
	cout << "A";
	Sleep(100);
	cout << "E";
	Sleep(100);
	cout << "D";
	Sleep(100);
	cout << "A";
	Sleep(100);
	cout << "S";
	Sleep(100);
	cout << "A";
	Sleep(100);
	cout << "S";
	Sleep(200);
	cout << "!";
	Sleep(200);
	cout << "!";

	SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY
					| BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED
					| BACKGROUND_BLUE);

	Sleep(2000);
	showMainMenu();

}

void Interface::showMainMenu() {

	db.loadData();
	system("cls");

	cout << endl << endl << setfill(' ');
	cout << setw(5) << " " << (char) 180 << " New user " << (char) 195 << endl
			<< endl;
	cout << setw(2) << " " << "1. Signup" << endl;
	cout << setw(2) << " " << "2. About" << endl << endl << endl;
	cout << setw(5) << " " << (char) 180 << " Registered users " << (char) 195
			<< endl << endl;
	cout << setw(2) << " " << "3. Login" << endl << endl << endl;
	cout << setw(5) << "4. Exit app" << endl << endl;

	gotoxy(2, 4);

	int temp;
	temp = 1;

	char Arrow = 0;
	Arrow = _kbhit();

	while (true) {
		Arrow = _getch();

		if (Arrow == '\r') {
			switch (temp) {
			case 1:
				showSignUpMenu();
				break;
			case 2:
				showOfferedServices();
				showMainMenu();
				break;
			case 3:
				showLogin();
				break;
			case 4:
				system("cls");
				db.saveData();
				exit(0);
				break;
			}
		}

		switch (Arrow) {

		case 49:
			showSignUpMenu();
			break;
		case 50:
			showOfferedServices();
			showMainMenu();
			break;

		case 51:
			showLogin();
			break;

		case 52:
			system("cls");
			exit(0);
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;
			else if (temp == 2) {
				gotoxy(2, 4);
				temp = 1;
				break;
			} else if (temp == 3) {
				gotoxy(2, 5);
				temp = 2;
				break;
			} else if (temp == 4) {
				gotoxy(2, 10);
				temp = 3;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(2, 5);
				temp = 2;
				break;
			} else if (temp == 2) {
				gotoxy(2, 10);
				temp = 3;
				break;
			} else if (temp == 3) {
				gotoxy(0, 13);
				temp = 4;
				break;
			}
		}
	}
}

void Interface::showSignUpMenu() {

	system("cls");
	unsigned short int option = 0;

	cout << "What type of costumer are you? " << endl << endl;
	cout << "1: Particular" << endl << "2: Commercial\n\n";

	gotoxy(0, 2);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case 49:
			option = 1;
			break;
		case 50:
			option = 2;
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(0, 2);
				temp = 1;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(0, 3);
				temp = 2;
				break;
			}

		}

	}

	system("cls");

	bool done = false;
	bool valid = false;

	while (!done) {

		switch (option) {

		case 1: {
			Particular part;
			string generic;
			string pw;

			cout << "-Particular-\n\n";

			while (!valid) {
				cout << "Name: ";
				getline(cin, generic);
				try {
					part.setName(generic);
				} catch (InvalidName) {
					cerr
							<< "The name you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			valid = false;
			unsigned int d, m, y;
			char temp = '/';
			char temp1 = temp;
			while (!valid) {
				cout << "Birth Date(dd/mm/yyyy): ";
				cin >> d >> temp >> m >> temp1 >> y;

				if (d <= 0 || d >= 31 || m <= 0 || m > 12 || y < 1910
						|| y > 2011 || temp != '/' || temp1 != '/') {
					cerr << "Invalid date input. Try again.\n";
					cin.ignore(1000, '\n');
					cin.clear();
					continue;
				}

				Date dt(d, m, y);

				try {
					part.setDate(dt);
				} catch (InvalidDate) {
					cerr << "Invalid date input. Try again.\n";
					continue;
				}

				valid = true;
			}

			cin.ignore(1000, '\n');
			cin.clear();
			valid = false;
			while (!valid) {
				cout << "E-mail: ";
				getline(cin, generic);

				try {
					part.setEmail(generic);
				} catch (InvalidEmail) {
					cerr
							<< "The e-mail you wrote is not valid. It must have a @. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			valid = false;
			while (!valid) {
				cout << "Phone Number: ";
				getline(cin, generic);
				try {
					part.setPhoneNumber(generic);
				} catch (InvalidPhoneNumber) {
					cerr
							<< "The phone number you wrote is not valid. It must have 9 digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			cout << "Address: ";
			getline(cin, generic);
			part.setAddress(generic);
			valid = false;
			while (!valid) {
				cout << "Zip Code: ";
				getline(cin, generic);
				try {
					part.setZipCode(generic);
				} catch (InvalidZipCode) {
					cerr
							<< "The Zip Code you wrote is not valid. It must only contain digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;

			}
			valid = false;
			while (!valid) {
				cout << "Country: ";
				getline(cin, generic);
				try {
					part.setCountry(generic);
				} catch (InvalidCountry) {
					cerr
							<< "The country you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}

			valid = false;
			while (!valid) {
				cout << "\nSet your login data\n\n";
				cout << "Username: ";
				getline(cin, generic);
				cout << "Password: ";
				getline(cin, pw);
				try {
					part.changeLogin(generic, pw);
				} catch (InvalidLogin) {
					cerr
							<< "The login data you inserted is not valid. Try Again\n";
					generic.clear();
					pw.clear();
					continue;
				}
				valid = true;
			}
			db.addParticular(part);
			loggedUser = &part;
			done = true;
			break;
		}

		case 2: {
			Commercial comme;
			string generic;
			unsigned int generic2;
			string pw;
			valid = false;

			cout << "-Commercial-\n\n";
			while (!valid) {
				cout << "Company Name: ";
				getline(cin, generic);
				try {
					comme.setName(generic);
				} catch (InvalidName) {
					cerr
							<< "The name you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}

			valid = false;
			while (!valid) {

				cout << "Number of People: ";
				cin >> generic2;
				cin.ignore(1000, '\n');
				cin.clear();
				try {
					comme.setNumPeople(generic2);
				} catch (InvalidNumPeople) {
					cerr
							<< "The number of people you wrote is not valid. It must be between 1 - 500 Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			valid = false;
			while (!valid) {
				cout << "Phone Number: ";
				getline(cin, generic);
				try {
					comme.setPhoneNumber(generic);
				} catch (InvalidPhoneNumber) {
					cerr
							<< "The phone number you wrote is not valid. It must have 9 digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			cout << "Address: ";
			getline(cin, generic);
			comme.setAddress(generic);
			valid = false;
			while (!valid) {
				cout << "Zip Code: ";
				getline(cin, generic);
				try {
					comme.setZipCode(generic);
				} catch (InvalidZipCode) {
					cerr
							<< "The Zip Code you wrote is not valid. It must only contain digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;

			}
			valid = false;
			while (!valid) {
				cout << "Country: ";
				getline(cin, generic);
				try {
					comme.setCountry(generic);
				} catch (InvalidCountry) {
					cerr
							<< "The country you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}

			valid = false;
			while (!valid) {
				cout << "\nSet your login data\n\n";
				cout << "Username: ";
				getline(cin, generic);
				cout << "Password: ";
				getline(cin, pw);
				try {
					comme.changeLogin(generic, pw);
				} catch (InvalidLogin) {
					cerr
							<< "The login data you inserted is not valid. Try Again\n";
					generic.clear();
					pw.clear();
					continue;
				}
				valid = true;
			}
			db.addCommercial(comme);
			done = true;
			break;
		}

		default:
			break;

		}

	}

	db.saveData();
	showCostumerMenu();
}

void Interface::showOfferedServices() {
	system("cls");
	cout.fill(' ');
	cout << setw(30) << "- About -" << endl << endl;
	cout << "This travel agency has an offer of " << db.getPackages().size()
			<< " packages, available to a total of "
			<< db.getCommercial().size() + db.getParticular().size()
			<< " costumers." << endl;
	cout
			<< "There are currently "
			<< User::getNumOfUsers()
			<< " users who run this application, of which "
			<< db.getAdmins().size()
			<< " are administrators.\n\n\n"
			<< "This application has been entirely made by Joao Leal, Pedro Alves and Pedro Martins, "
			<< "students at the Faculty of Engineering of the University of Porto. All rights reserved.";

	getch();
}

/**********************/
/**Costumer Interface**/
/**********************/

void Interface::showCostumerMenu() {
	system("cls");

	cout << endl << endl;
	cout << setfill(' ');

	cout << setw(9) << " " << "- Costumer Area -";
	cout << endl << endl;
	cout << setw(5) << " ";
	cout << "-Buy New Product-" << endl << endl;
	cout << setw(2) << " ";
	cout << "1: Default Packages";
	cout << endl;
	cout << setw(2) << " ";
	cout << "2: Promotional Packages";
	cout << endl;
	cout << setw(2) << " ";
	cout << "3: Individual Services";
	cout << endl << endl << endl;

	cout << setw(2) << " " << "4: See Packages";
	cout << endl;
	cout << setw(2) << " " << "5: See Past Trips";
	cout << endl;
	cout << setw(2) << " ";
	cout << "6: Unsubscribe";
	cout << endl << endl << endl;

	cout << setw(5) << "7: Logout";
	cout << endl;
	cout << setw(5) << "8: Exit app";
	cout << endl << endl;

	int ytemp = 7;

	gotoxy(41, 6);

	cout << "   -Logged User -";
	gotoxy(40, ytemp);

	for (unsigned int i = 40; i < 61; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(40, ytemp);
	cout << (char) 201;
	gotoxy(60, ytemp);
	cout << (char) 187;
	ytemp++;

	gotoxy(40, ytemp);
	cout << (char) 186;
	gotoxy(60, ytemp);
	cout << (char) 186;

	gotoxy(41, ytemp);
	cout << loggedUser->getLogin();
	ytemp++;

	for (unsigned int i = 40; i < 61; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(40, ytemp);
	cout << (char) 200;
	gotoxy(60, ytemp);
	cout << (char) 188;

	gotoxy(2, 6);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {
			switch (temp) {
			case 1:
				showDefaultPkg();
				break;
			case 2:
				showPromoPkg();
				break;
			case 3:
				showIndvPkgs();
				break;
			case 4:
				showPackages();
				break;
			case 5:
				showPastTrips();
				break;
			case 6:
				showUnsubscribe();
				break;
			case 7:
				db.saveData();
				showMainMenu();
				break;
			case 8:
				exit(0);
				break;

			}
		}

		switch (Arrow) {

		case 49:
			showDefaultPkg();
			break;
		case 50:
			showPromoPkg();
			break;
		case 51:
			showIndvPkgs();
			break;
		case 52:
			showPackages();
			break;
		case 53:
			showPastTrips();
			break;
		case 54:
			showUnsubscribe();
			break;
		case 55:
			db.saveData();
			showMainMenu();
			break;
		case 56:
			exit(0);
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(2, 6);
				temp = 1;
				break;
			}

			else if (temp == 3) {
				gotoxy(2, 7);
				temp = 2;
				break;
			}

			else if (temp == 4) {
				gotoxy(2, 8);
				temp = 3;
				break;
			}

			else if (temp == 5) {
				gotoxy(2, 11);
				temp = 4;
				break;
			}

			else if (temp == 6) {
				gotoxy(2, 12);
				temp = 5;
				break;
			}

			else if (temp == 7) {
				gotoxy(2, 13);
				temp = 6;
				break;
			}

			else if (temp == 8) {
				gotoxy(0, 16);
				temp = 7;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(2, 7);
				temp = 2;
				break;
			}

			else if (temp == 2) {
				gotoxy(2, 8);
				temp = 3;
				break;
			}

			else if (temp == 3) {
				gotoxy(2, 11);
				temp = 4;
				break;
			}

			else if (temp == 4) {
				gotoxy(2, 12);
				temp = 5;
				break;
			}

			else if (temp == 5) {
				gotoxy(2, 13);
				temp = 6;
				break;
			}

			else if (temp == 6) {
				gotoxy(0, 16);
				temp = 7;
				break;
			}

			else if (temp == 7) {
				gotoxy(0, 17);
				temp = 8;
				break;
			}

			else if (temp == 8)
				break;

		}
	}

}

void Interface::showLogin() {

	int c;
	string password;
	string user;
	bool found = false;
	int tries = 3;

	while (tries > 0 && !found) {

		system("cls");
		cout << setfill(' ');

		cout << "Put your username and password below to login" << endl << endl;

		cout << setw(10) << " ";
		cout << "User: ";
		cin >> user;

		cout << setw(10) << " ";
		cout << "Password: ";

		do {
			c = _getch();

			switch (c) {
			case 0:
				_getch();
				break;
			case '\b':
				if (password.length()) {
					cout << "\b \b";
					password.erase(password.end() - 1);
				}
				break;
			default:
				if (isalnum(c) || ispunct(c)) {
					cout << "*";
					password.push_back(c);
				}
			}
		} while (c != '\r');

		for (unsigned int i = 0; i < db.getAdmins().size(); i++) {
			if ((db.getAdmins()[i].getLogin() == user)
					&& (db.getAdmins()[i].getPassword() == password)) {
				found = true;
				loggedUser = &(db.getAdmins()[i]);
				loggedUserindex = i;
				loggedtype = "Admin";
				showAdminMenu();
			} else
				continue;
		}

		for (unsigned int i = 0; i < db.getParticular().size(); i++) {
			if ((db.getParticular()[i].getLogin() == user)
					&& (db.getParticular()[i].getPassword() == password)) {
				found = true;
				loggedUser = &(db.getParticular()[i]);
				loggedUserindex = i;
				loggedtype = "Particular";
				showCostumerMenu();
			} else
				continue;
		}

		for (unsigned int i = 0; i < db.getCommercial().size(); i++) {
			if ((db.getCommercial()[i].getLogin() == user)
					&& (db.getCommercial()[i].getPassword() == password)) {
				found = true;
				loggedUser = &(db.getCommercial()[i]);
				loggedUserindex = i;
				loggedtype = "Commercial";
				showCostumerMenu();
			} else
				continue;
		}

		if (!found) {
			system("cls");
			password.clear();
			user.clear();
			tries--;
			if (tries == 1)
				cout << "Invalid Login or Password. You have " << tries
						<< " more try.";
			else if (!tries)
				cout << "You have no more tries available. ";
			else if (tries == 2)
				cout << "Invalid Login or Password. You have " << tries
						<< " more tries.";
			Sleep(1000);
		}
	}

	showMainMenu();

}

void Interface::showDefaultPkg() {
	system("cls");

	cout << endl << endl;
	cout << setfill(' ');

	cout << setw(9) << " " << "- What option do you want? -";
	cout << endl << endl;
	cout << setw(2) << " ";
	cout << "1: Show all packages";
	cout << endl;
	cout << setw(2) << " ";
	cout << "2: Search by Country";
	cout << endl << endl << endl;

	cout << setw(5) << "3: Return to costumer menu";
	cout << endl;
	cout << setw(5) << "4: Exit app";
	cout << endl << endl;
	gotoxy(2, 4);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {
			switch (temp) {
			case 1:
				showAllPkgs();
				break;
			case 2:
				showSearchByCountry();
				break;
			case 3:
				showCostumerMenu();
				break;
			case 4:
				system("cls");
				exit(0);
				break;
			}
		}

		switch (Arrow) {

		case 49:
			showAllPkgs();
			break;
		case 50:
			showSearchByCountry();
			break;
		case 51:
			showCostumerMenu();
			break;
		case 52:
			system("cls");
			exit(0);
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(2, 4);
				temp = 1;
				break;
			}

			else if (temp == 3) {
				gotoxy(2, 5);
				temp = 2;
				break;
			}

			else if (temp == 4) {
				gotoxy(0, 8);
				temp = 3;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(2, 5);
				temp = 2;
				break;
			}

			else if (temp == 2) {
				gotoxy(0, 8);
				temp = 3;
				break;
			}

			else if (temp == 3) {
				gotoxy(0, 9);
				temp = 4;
				break;
			}

		}
	}
}

void Interface::showAllPkgs() {

	system("cls");
	cout.fill(' ');
	vector<int> index;
	bool existe = false;

	cout << setw(9) << "- Choose the package that you want to buy -" << endl
			<< endl;
	int ytemp = 2;

	for (unsigned int i = 0; i < db.getPackages().size(); i++) {

		if (db.getPackages()[i].isPromotional() == 1)
			continue;
		else
			existe = true;
	}

	if (!existe) {
		cout << " " << setfill(' ') << setw(45) << right
				<< "There are no Packages!" << setw(50) << endl;
		Sleep(1000);
		showDefaultPkg();
	}

	if (!db.getPackages().size()) {
		cout << " " << setfill(' ') << setw(45) << right
				<< "There are no Packages!" << setw(50) << endl;
		Sleep(1000);
	}

	else {

		gotoxy(1, ytemp);
		cout << (char) 201;
		for (int i = 2; i < 79; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}
		gotoxy(78, ytemp);
		cout << (char) 187;

		gotoxy(25, ytemp);
		cout << (char) 203;

		for (unsigned int i = 0; i < db.getPackages().size(); i++) {

			if (db.getPackages()[i].isPromotional() == 1)
				continue;
			else {
				index.push_back(i);
				gotoxy(2, ytemp + 1);
				cout << i + 1 << ".";
				gotoxy(2, ytemp + 4);
				cout << "Destination: " << db.getPackages()[i].getDestination();
				for (int j = ytemp + 1; j < ytemp + 8; j++) {
					gotoxy(1, j);
					cout << (char) 186;
					gotoxy(25, j);
					cout << (char) 186;
					gotoxy(78, j);
					cout << (char) 186;
				}

				ytemp++;
				gotoxy(26, ytemp);
				cout << "Origin: " << db.getPackages()[i].getOrigin();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Duration: " << db.getPackages()[i].getDuration()
						<< " days " << (char) 26 << " "
						<< db.getPackages()[i].getInitialDate() << " - "
						<< db.getPackages()[i].getEndDate();
				ytemp++;
				gotoxy(26, ytemp);
				cout << " ";
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Transport type: "
						<< db.getPackages()[i].getTransportation().getType();

				if (db.getPackages()[i].getTransportation().isFirstClass())
					cout << " " << (char) 26 << " FirstClass";

				ytemp++;
				gotoxy(26, ytemp);
				cout << "Establishment type: "
						<< db.getPackages()[i].getAccomodation().getType();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Total Price (For one person): "
						<< db.getPackages()[i].getPrice();
				ytemp++;

				gotoxy(1, ytemp);
				cout << (char) 204;
				for (int i = 2; i < 79; i++) {
					gotoxy(i, ytemp);
					cout << (char) 205;
				}
				gotoxy(78, ytemp);
				cout << (char) 185;

				gotoxy(25, ytemp);
				cout << (char) 206;
			}

		}

		gotoxy(1, ytemp);
		cout << (char) 200;
		for (int i = 2; i < 79; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}
		gotoxy(78, ytemp);
		cout << (char) 188;

		gotoxy(25, ytemp);
		cout << (char) 202;

		unsigned int temp;
		temp = 1;

		ytemp = 3;
		gotoxy(2, ytemp);

		char Arrow = 0;

		Arrow = _kbhit();

		while (1) {
			Arrow = _getch();

			if (Arrow == '\r') {

				unsigned int people;

				system("cls");

				cout << "How many people will travel?" << endl << endl;
				cout << "Number: ";
				cin >> people;

				Transportation tp;

				tp = db.getPackages()[index[temp - 1]].getTransportation();
				tp.setPeopleNumber(people);
				tp.resetPrice();

				Accomodation ac;

				ac = db.getPackages()[index[temp - 1]].getAccomodation();
				ac.setPeopleNumber(people);
				ac.setPrice(ac.getPrice());

				Trip tmp;

				tmp = db.getPackages()[index[temp - 1]];

				tmp.setTransportation(tp);
				tmp.setAccomodation(ac);

				unsigned int price = tmp.getPrice();

				system("cls");

				cout << " The total price of the Package will be " << price
						<< " euros" << endl
						<< "Are you sure you want to proceed? " << endl << endl;

				cout << "1: Yes" << endl;
				cout << "2: No";

				gotoxy(0, 3);

				temp = 0;

				Arrow = 0;

				Arrow = _kbhit();

				while (1) {
					Arrow = _getch();

					if (Arrow == '\r') {
						switch (temp) {

						case 0:

							if (loggedtype == "Particular") {
								system("cls");
								db.addTripToUser(1, loggedUserindex, tmp);

								cout << " " << setfill(' ') << setw(45) << right
										<< "Process order is completed"
										<< setw(50) << endl;
								Sleep(1000);
								showCostumerMenu();
							} else {
								system("cls");
								db.addTripToUser(0, loggedUserindex, tmp);
								cout << " " << setfill(' ') << setw(45) << right
										<< "Process order is completed"
										<< setw(50) << endl;
								Sleep(1000);
								showCostumerMenu();
							}

							break;
						case 1:
							system("cls");
							cout << "Buy process canceled";
							showCostumerMenu();
							Sleep(1000);
							break;
						}
						break;
					}

					switch (Arrow) {

					case 49:
						if (loggedtype == "Particular") {
							system("cls");
							db.addTripToUser(1, loggedUserindex, tmp);

							cout << " " << setfill(' ') << setw(45) << right
									<< "Process order is completed" << setw(50)
									<< endl;
							Sleep(1000);
							showCostumerMenu();
						} else {
							system("cls");
							db.addTripToUser(0, loggedUserindex, tmp);
							cout << " " << setfill(' ') << setw(45) << right
									<< "Process order is completed" << setw(50)
									<< endl;
							Sleep(1000);
							showCostumerMenu();
						}
						break;
					case 50:
						system("cls");
						cout << "Buy process canceled";
						showCostumerMenu();
						Sleep(1000);
						break;

					case CPPKEYUP:
						if (!temp)
							break;
						else {
							temp = temp - 1;
							gotoxy(0, 3 + temp);
							break;
						}

					case CPPKEYDOWN:
						if (temp == 1)
							break;
						else {
							temp = temp + 1;
							gotoxy(0, 3 + temp);
							break;
						}
					}

				}

				break;
			}

			switch (Arrow) {
			case CPPKEYUP:

				if (temp == 1)
					break;
				else {
					temp = temp - 1;
					ytemp -= 7;
					gotoxy(2, ytemp);
					break;
				}

			case CPPKEYDOWN:
				if (temp == index.size())
					break;
				else {
					temp = temp + 1;
					ytemp += 7;
					gotoxy(2, ytemp);
					break;
				}
			}

		}
	}

}

void Interface::showIndvPkgs() {

	Trip tmp = Trip();
	system("cls");
	cout.fill(' ');
	cout << endl;

	cout << "- What type of individual package do you want? -" << endl << endl;

	cout << setw(2) << " ";
	cout << "1: Customized Package with all options (Trip + Accommodation)";
	cout << endl;
	cout << setw(2) << " ";
	cout << "2: Only Trip";
	cout << endl;
	cout << setw(2) << " ";
	cout << "3: Only Accommodation";
	cout << endl << endl << endl;

	cout << setw(5) << "4: Return to costumer menu";
	cout << endl << endl;

	gotoxy(2, 3);

	int temp;
	temp = 1;
	string origin;
	unsigned int choose;
	unsigned int people = 0;
	bool continua = false;
	unsigned int duration = 0;

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {

		if (continua)
			break;

		Arrow = _getch();

		if (Arrow == '\r') {
			switch (temp) {
			case 1:
				origin = showIndvOrigin(tmp);
				choose = showIndvDestination(tmp, origin);
				people = showIndvTransportation(tmp, choose);

				system("cls");
				cout << "- How many days will you be staying? -" << endl;
				cout << "Number of days: ";
				cin >> duration;

				showIndvAccommodation(tmp, choose, people);
				break;
			case 2:
				origin = showIndvOrigin(tmp);
				choose = showIndvDestination(tmp, origin);
				showIndvTransportation(tmp, choose);

				break;
			case 3:
				system("cls");
				cout << "- How many days will you be staying? -" << endl
						<< endl;
				cout << "Number of days: ";
				cin >> duration;
				cout << endl;
				cout << "- How many people will be accommodated? -" << endl
						<< endl;

				cout << "Number of people: ";
				cin >> people;
				choose = showIndvDestinationforAcc(tmp);
				showIndvAccommodation(tmp, choose, people);
				break;
			case 4:
				showCostumerMenu();
				break;
			}

			break;
		}

		switch (Arrow) {

		case 49:

			origin = showIndvOrigin(tmp);
			choose = showIndvDestination(tmp, origin);
			people = showIndvTransportation(tmp, choose);

			system("cls");
			cout << "- How many days will you be staying? -" << endl;
			cout << "Number of days: ";
			cin >> duration;

			showIndvAccommodation(tmp, choose, people);
			continua = true;
			break;
		case 50:
			origin = showIndvOrigin(tmp);
			choose = showIndvDestination(tmp, origin);
			showIndvTransportation(tmp, choose);
			continua = true;
			break;
		case 51:
			system("cls");
			cout << "- How many days will you be staying? -" << endl << endl;
			cout << "Number of days: ";
			cin >> duration;
			cout << endl;
			cout << "- How many people will be accommodated? -" << endl << endl;

			cout << "Number of people: ";
			cin >> people;

			choose = showIndvDestinationforAcc(tmp);
			showIndvAccommodation(tmp, choose, people);
			continua = true;
			break;
		case 52:
			showCostumerMenu();
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(2, 3);
				temp = 1;
				break;
			}

			else if (temp == 3) {
				gotoxy(2, 4);
				temp = 2;
				break;
			}

			else if (temp == 4) {
				gotoxy(0, 8);
				temp = 3;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(2, 4);
				temp = 2;
				break;
			}

			else if (temp == 2) {
				gotoxy(2, 5);
				temp = 3;
				break;
			}

			else if (temp == 3) {
				gotoxy(0, 8);
				temp = 4;
				break;
			}

		}
	}

	system("cls");

	Transportation tptemp;
	tptemp = tmp.getTransportation();

	tptemp.resetPrice();

	tmp.setTransportation(tptemp);

	tmp.setDuration(duration);

	tmp.setPrice();

	unsigned int price = tmp.getPrice();

	cout << " The total price of the Package will be " << price << " euros"
			<< endl << "Are you sure you want to proceed? " << endl << endl;

	cout << "1: Yes" << endl;
	cout << "2: No";

	gotoxy(0, 3);

	temp = 0;

	Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {
			switch (temp) {

			case 0:
				if (loggedtype == "Particular") {
					system("cls");
					db.addTripToUser(1, loggedUserindex, tmp);

					cout
							<< " "
							<< setfill(' ')
							<< setw(45)
							<< right
							<< "Your choices are confirmed, individual package added to your trips"
							<< setw(50) << endl;
					Sleep(1000);
					showCostumerMenu();
				} else {
					system("cls");
					db.addTripToUser(0, loggedUserindex, tmp);
					cout
							<< " "
							<< setfill(' ')
							<< setw(45)
							<< right
							<< "Your choices are confirmed, individual package added to your trips"
							<< setw(50) << endl;
					Sleep(1000);
					showCostumerMenu();
				}
				break;
			case 1:
				system("cls");
				cout << "Buy process canceled";
				Sleep(1000);
				break;
			}
			break;
		}

		switch (Arrow) {

		case 49:
			db.addTrip(tmp);
			system("cls");
			cout
					<< "Your choices are confirmed, individual package added to your trips";
			Sleep(2);
			break;
		case 50:
			system("cls");
			cout << "Buy process canceled";
			break;

		case CPPKEYUP:
			if (!temp)
				break;
			else {
				temp = temp - 1;
				gotoxy(0, 3 + temp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1)
				break;
			else {
				temp = temp + 1;
				gotoxy(0, 3 + temp);
				break;
			}
		}

	}

	showCostumerMenu();

}

string Interface::showIndvOrigin(Trip & tp) {

	system("cls");
	vector<string> stringtmp;
	int contador = 0;
	int ytemp = 2;

	gotoxy(0, 0);
	cout << "- From what origin do you want travel? -";

	gotoxy(0, ytemp);
	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 201;
	gotoxy(24, ytemp);
	cout << (char) 187;
	ytemp++;

	for (unsigned int i = 0; i < db.getPackages().size(); i++) {

		if (!stringtmp.empty()) {
			for (unsigned int j = 0; j < stringtmp.size(); j++) {
				if (db.getPackages()[i].getOrigin() == stringtmp[j]) {
					contador++;
					continue;

				}
			}
		}

		if (!contador) {
			gotoxy(4, ytemp);
			cout << (char) 186;
			gotoxy(5, ytemp);
			cout << i + 1 << ". " << db.getPackages()[i].getOrigin();
			gotoxy(24, ytemp);
			cout << (char) 186;
			ytemp++;

			for (unsigned int j = 4; j < 25; j++) {
				gotoxy(j, ytemp);
				cout << (char) 205;
			}

			gotoxy(4, ytemp);
			cout << (char) 204;
			gotoxy(24, ytemp);
			cout << (char) 185;

			stringtmp.push_back(db.getPackages()[i].getOrigin());

		}

		else
			contador = 0;

	}

	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 200;
	gotoxy(24, ytemp);
	cout << (char) 188;

	unsigned int temp;
	temp = 0;

	ytemp = 3;
	gotoxy(5, ytemp);
	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {

			tp.setOrigin(stringtmp[temp]);
			return stringtmp[temp];
		}

		switch (Arrow) {

		case CPPKEYUP:
			if (!temp)
				break;
			else {
				temp -= 1;
				ytemp -= 2;
				gotoxy(5, ytemp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == stringtmp.size() - 1)
				break;
			else {
				temp += 1;
				ytemp += 2;
				gotoxy(5, ytemp);
				break;
			}
		}

	}

}

unsigned int Interface::showIndvDestination(Trip & tp, string origin) {

	system("cls");
	vector<int> index;
	vector<string> stringtmp;
	int contador = 0;
	int ytemp = 2;

	cout << setfill(' ');

	gotoxy(0, 0);
	cout << "- For what destination do you want travel? -";

	gotoxy(0, ytemp);
	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 201;
	gotoxy(24, ytemp);
	cout << (char) 187;
	ytemp++;

	for (unsigned int i = 0; i < db.getPackages().size(); i++) {

		if (db.getPackages()[i].getOrigin() == origin) {

			if (!stringtmp.empty()) {
				for (unsigned int j = 0; j < stringtmp.size(); j++) {
					if (db.getPackages()[i].getOrigin() == stringtmp[j]) {
						contador++;
						continue;

					}
				}
			}

			if (!contador) {
				gotoxy(4, ytemp);
				cout << (char) 186;
				gotoxy(5, ytemp);
				cout << i + 1 << ". " << db.getPackages()[i].getDestination();
				gotoxy(24, ytemp);
				cout << (char) 186;
				ytemp++;

				for (unsigned int j = 4; j < 25; j++) {
					gotoxy(j, ytemp);
					cout << (char) 205;
				}

				gotoxy(4, ytemp);
				cout << (char) 204;
				gotoxy(24, ytemp);
				cout << (char) 185;

				stringtmp.push_back(db.getPackages()[i].getOrigin());
				index.push_back(i);

			}
		}

	}

	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 200;
	gotoxy(24, ytemp);
	cout << (char) 188;

	unsigned int temp;
	temp = 0;

	ytemp = 3;
	gotoxy(5, ytemp);

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {

			tp.setDestination(db.getPackages()[index[temp]].getDestination());
			return index[temp];
		}

		switch (Arrow) {

		case CPPKEYUP:
			if (!temp)
				break;
			else {
				temp -= 1;
				ytemp -= 2;
				gotoxy(5, ytemp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == stringtmp.size() - 1)
				break;
			else {
				temp += 1;
				ytemp += 2;
				gotoxy(5, ytemp);
				break;
			}
		}

	}
}

unsigned int Interface::showIndvTransportation(Trip & tp,
		unsigned int destination) {

	system("cls");

	unsigned int people;
	int ytemp = 2;

	gotoxy(0, 0);
	cout << "- How many people will travel? -" << endl << endl;

	cout << "Number: ";
	cin >> people;

	system("cls");

	gotoxy(0, 0);
	cout << "- What kind of transportation do you want? -" << endl << endl;

	gotoxy(0, ytemp);
	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 201;
	gotoxy(24, ytemp);
	cout << (char) 187;
	ytemp++;

	gotoxy(4, ytemp);
	cout << (char) 186;
	gotoxy(24, ytemp);
	cout << (char) 186;

	gotoxy(5, ytemp);
	cout << "1. Aerial";
	ytemp++;

	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 204;
	gotoxy(24, ytemp);
	cout << (char) 185;
	ytemp++;

	gotoxy(4, ytemp);
	cout << (char) 186;
	gotoxy(24, ytemp);
	cout << (char) 186;

	gotoxy(5, ytemp);
	cout << "2. Maritime";
	ytemp++;

	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 204;
	gotoxy(24, ytemp);
	cout << (char) 185;
	ytemp++;

	gotoxy(4, ytemp);
	cout << (char) 186;
	gotoxy(24, ytemp);
	cout << (char) 186;

	gotoxy(5, ytemp);
	cout << "3. Land";
	ytemp++;

	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 200;
	gotoxy(24, ytemp);
	cout << (char) 188;

	unsigned int temp = 0;
	bool continua = false;

	ytemp = 3;
	gotoxy(5, ytemp);

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {

		if (continua)
			break;

		Arrow = _getch();

		if (Arrow == '\r') {
			tp.setTransportation(db.getTransportations()[temp]);
			break;

			break;
		}

		switch (Arrow) {

		case 48:
			tp.setTransportation(db.getTransportations()[0]);
			break;
		case 49:
			tp.setTransportation(db.getTransportations()[1]);
			break;
		case 50:
			tp.setTransportation(db.getTransportations()[2]);
			break;
			continua = true;
			break;

		case CPPKEYUP:

			if (!temp)
				break;
			else {
				temp -= 1;
				ytemp -= 2;
				gotoxy(5, ytemp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == 2)
				break;
			else {
				temp += 1;
				ytemp += 2;
				gotoxy(5, ytemp);
				break;
			}
		}

	}

	system("cls");

	cout << "- Do you want to be in first class? " << endl << endl;

	cout << "1: Yes" << endl;
	cout << "2: No";

	temp = 0;
	continua = false;
	Transportation tptemp = tp.getTransportation();

	gotoxy(0, 2);

	Arrow = 0;

	Arrow = _kbhit();

	while (1) {

		if (continua)
			break;

		Arrow = _getch();

		if (Arrow == '\r') {
			switch (temp) {

			case 0:
				tptemp.setClass(true);
				break;
			case 1:
				tptemp.setClass(false);
				break;
			}

			break;

		}

		switch (Arrow) {

		case 49:
			continua = true;
			tptemp.setClass(true);
			break;
		case 50:
			continua = true;
			tptemp.setClass(false);
			break;

		case CPPKEYUP:
			if (!temp)
				break;
			else {
				temp = temp - 1;
				gotoxy(0, 2 + temp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1)
				break;
			else {
				temp = temp + 1;
				gotoxy(0, 2 + temp);
				break;
			}
		}

	}

	tptemp.setPeopleNumber(people);
	tp.setTransportation(tptemp);

	return people;
}

void Interface::showIndvAccommodation(Trip & tp, unsigned int destination,
		unsigned peopleNumber) {
	system("cls");
	int ytemp = 2;

	string dest = db.getPackages()[destination].getDestination();

	vector<Accomodation> vect = db.getAccomodations()[dest];

	cout << "- What type of Accommodation do you want? -" << endl << endl;

	gotoxy(0, ytemp);
	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 201;
	gotoxy(24, ytemp);
	cout << (char) 187;

	for (unsigned int i = 0; i < vect.size(); i++) {
		ytemp++;
		gotoxy(4, ytemp);
		cout << (char) 186;
		gotoxy(24, ytemp);
		cout << (char) 186;

		gotoxy(5, ytemp);
		cout << i + 1 << ". " << vect[i].getType();
		ytemp++;

		for (unsigned int i = 4; i < 25; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}

		gotoxy(4, ytemp);
		cout << (char) 204;
		gotoxy(24, ytemp);
		cout << (char) 185;
	}

	for (unsigned int i = 4; i < 25; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}

	gotoxy(4, ytemp);
	cout << (char) 200;
	gotoxy(24, ytemp);
	cout << (char) 188;

	unsigned int temp;
	temp = 0;

	ytemp = 3;
	gotoxy(5, ytemp);

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {

			vect[temp].setPeopleNumber(peopleNumber);

			tp.setAccomodation(vect[temp]);
			break;
		}

		switch (Arrow) {

		case CPPKEYUP:
			if (!temp)
				break;
			else {
				temp -= 1;
				ytemp -= 2;
				gotoxy(5, ytemp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == vect.size() - 1)
				break;
			else {
				temp += 1;
				ytemp += 2;
				gotoxy(5, ytemp);
				break;
			}
		}

	}

}

unsigned int Interface::showIndvDestinationforAcc(Trip & tp) {
	system("cls");
	vector<int> index;
	vector<string> stringtmp;
	int contador = 0;

	cout << setfill(' ');

	cout
			<< "- For what destination do you want to see the available accommodations? -"
			<< endl << endl;

	cout << setw(15) << " " << setfill('-') << setw(20) << "-" << endl;

	for (unsigned int i = 0; i < db.getPackages().size(); i++) {
		for (unsigned int j = 0; j < stringtmp.size(); j++) {
			if (db.getPackages()[i].getDestination() == stringtmp[j]) {
				contador++;
				continue;

			}
		}

		if (!contador) {
			int spaceDestination = 18
					- db.getPackages()[i].getDestination().size();

			cout << setfill(' ') << setw(15) << "|" << i + 1 << ": "
					<< db.getPackages()[i].getDestination()
					<< setw(spaceDestination) << "|" << endl;
			stringtmp.push_back(db.getPackages()[i].getDestination());
			index.push_back(i);

		}

	}

	cout << setfill(' ') << setw(15) << " " << setfill('-') << setw(20) << "-"
			<< endl;

	unsigned int temp;
	temp = 0;

	gotoxy(15, 3);

	char Arrow = 0;

	Arrow = _kbhit();

	while (1) {
		Arrow = _getch();

		if (Arrow == '\r') {

			tp.setDestination(db.getPackages()[index[temp]].getDestination());
			return index[temp];
		}

		switch (Arrow) {

		case CPPKEYUP:
			if (!temp)
				break;
			else {
				temp = temp - 1;
				gotoxy(15, 3 + temp);
				break;
			}

		case CPPKEYDOWN:
			if (temp == db.getPackages().size() - 1)
				break;
			else {
				temp = temp + 1;
				gotoxy(15, 3 + temp);
				break;
			}
		}

	}
}

void Interface::showPromoPkg() {
	int ytemp = 2;
	bool vazio = false;
	vector<int> index;
	int contador = 0;

	if (!db.getPackages().size()) {
		system("cls");
		cout << " " << setfill(' ') << setw(45) << right
				<< "There are no Packages!" << setw(50) << endl;
		Sleep(500);
	}

	else {

		for (unsigned int j = 0; j < db.getPackages().size(); j++) {
			if (!db.getPackages()[j].isPromotional())
				vazio = true;
			else
				vazio = false;
		}

		if (vazio) {
			system("cls");
			cout << " " << setfill(' ') << setw(45) << right
					<< "There are no Promotional Packages!" << setw(50) << endl;
			Sleep(500);
			showCostumerMenu();

		}

		else {

			system("cls");
			gotoxy(1, ytemp);
			cout << (char) 201;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 187;

			gotoxy(25, ytemp);
			cout << (char) 203;

			for (unsigned int i = 0; i < db.getPackages().size(); i++) {
				if (db.getPackages()[i].isPromotional()) {
					contador++;
					index.push_back(i);
					gotoxy(2, ytemp + 1);
					cout << contador << ".";
					gotoxy(2, ytemp + 4);
					cout << "Destination: "
							<< db.getPackages()[i].getDestination();
					for (int j = ytemp + 1; j < ytemp + 8; j++) {
						gotoxy(1, j);
						cout << (char) 186;
						gotoxy(25, j);
						cout << (char) 186;
						gotoxy(78, j);
						cout << (char) 186;
					}

					ytemp++;
					gotoxy(26, ytemp);
					cout << "Origin: " << db.getPackages()[i].getOrigin();
					ytemp++;
					gotoxy(26, ytemp);
					cout << "Duration: " << db.getPackages()[i].getDuration()
							<< " days " << (char) 26 << " "
							<< db.getPackages()[i].getInitialDate() << " - "
							<< db.getPackages()[i].getEndDate();
					ytemp++;
					gotoxy(26, ytemp);
					cout << " ";
					ytemp++;
					gotoxy(26, ytemp);
					cout
							<< "Transport type: "
							<< db.getPackages()[i].getTransportation().getType();

					if (db.getPackages()[i].getTransportation().isFirstClass())
						cout << " " << (char) 26 << " FirstClass";

					ytemp++;
					gotoxy(26, ytemp);
					cout << "Establishment type: "
							<< db.getPackages()[i].getAccomodation().getType();
					ytemp++;
					gotoxy(26, ytemp);
					cout << "Total Price (Per person): "
							<< db.getPackages()[i].getPrice();
					ytemp++;

					gotoxy(1, ytemp);
					cout << (char) 204;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 185;

					gotoxy(25, ytemp);
					cout << (char) 206;
				}

			}

			gotoxy(1, ytemp);
			cout << (char) 200;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 188;

			gotoxy(25, ytemp);
			cout << (char) 202;
		}

		unsigned int temp = 1;
		ytemp = 3;
		gotoxy(2, ytemp);

		char Arrow = 0;

		Arrow = _kbhit();

		while (1) {
			Arrow = _getch();

			if (Arrow == '\r') {

				unsigned int people;

				system("cls");

				cout << "How many people will travel?" << endl << endl;

				cout << "Number: ";
				cin >> people;
				//if < 1 throw exception

				Transportation tp;

				Trip tmp;

				tmp = db.getPackages()[index[temp - 1]];

				tmp.setPriceVar(people);

				unsigned int price = tmp.getPrice();

				system("cls");

				cout << " The total price of the Package will be " << price
						<< " euros" << endl
						<< "Are you sure you want to proceed? " << endl << endl;

				cout << "1: Yes" << endl;
				cout << "2: No";

				gotoxy(0, 3);

				temp = 0;

				Arrow = 0;

				Arrow = _kbhit();

				while (1) {
					Arrow = _getch();

					if (Arrow == '\r') {
						switch (temp) {

						case 0:

							if (loggedtype == "Particular") {
								system("cls");
								db.addTripToUser(1, loggedUserindex, tmp);

								cout << " " << setfill(' ') << setw(45) << right
										<< "Process order is completed"
										<< setw(50) << endl;
								Sleep(1000);
								showCostumerMenu();
							} else {
								system("cls");
								db.addTripToUser(0, loggedUserindex, tmp);
								cout << " " << setfill(' ') << setw(45) << right
										<< "Process order is completed"
										<< setw(50) << endl;
								Sleep(1000);
								showCostumerMenu();
							}

							break;
						case 1:
							system("cls");
							cout << "Buy process canceled";
							showCostumerMenu();
							Sleep(1000);
							break;
						}
						break;
					}

					switch (Arrow) {

					case 49:
						if (loggedtype == "Particular") {
							system("cls");
							db.addTripToUser(1, loggedUserindex, tmp);

							cout << " " << setfill(' ') << setw(45) << right
									<< "Process order is completed" << setw(50)
									<< endl;
							Sleep(1000);
							showCostumerMenu();
						} else {
							system("cls");
							db.addTripToUser(0, loggedUserindex, tmp);
							cout << " " << setfill(' ') << setw(45) << right
									<< "Process order is completed" << setw(50)
									<< endl;
							Sleep(1000);
							showCostumerMenu();
						}
						break;
					case 50:
						system("cls");
						cout << "Buy process canceled";
						showCostumerMenu();
						Sleep(1000);
						break;

					case CPPKEYUP:
						if (!temp)
							break;
						else {
							temp = temp - 1;
							gotoxy(0, 3 + temp);
							break;
						}

					case CPPKEYDOWN:
						if (temp == 1)
							break;
						else {
							temp = temp + 1;
							gotoxy(0, 3 + temp);
							break;
						}
					}

				}

				break;
			}

			switch (Arrow) {
			case CPPKEYUP:

				if (temp == 1)
					break;
				else {
					temp = temp - 1;
					ytemp -= 7;
					gotoxy(2, ytemp);
					break;
				}

			case CPPKEYDOWN:
				if (temp == index.size())
					break;
				else {
					temp = temp + 1;
					ytemp += 7;
					gotoxy(2, ytemp);
					break;
				}
			}

		}
	}
}

void Interface::showPastTrips() {
	vector<Trip> history;
	char Arrow = 0;

	system("cls");

	if (loggedtype == "Commercial")
		history = db.getCommercial()[loggedUserindex].getHistory();
	else
		history = db.getParticular()[loggedUserindex].getHistory();

	int ytemp = 2;

	if (!history.size()) {
		system("cls");
		cout << " " << setfill(' ') << setw(45) << right
				<< "There are no past trips!" << setw(50) << endl;
		cout << "Press ENTER to go back to the costumer Menu";
		getch();
		showCostumerMenu();
	}

	else {

		gotoxy(1, ytemp);
		cout << (char) 201;
		for (int i = 2; i < 79; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}
		gotoxy(78, ytemp);
		cout << (char) 187;

		gotoxy(25, ytemp);
		cout << (char) 203;

		for (unsigned int i = 0; i < history.size(); i++) {

			gotoxy(2, ytemp + 1);
			cout << i + 1 << ".";
			gotoxy(2, ytemp + 4);
			cout << "Destination: " << history[i].getDestination();
			for (int j = ytemp + 1; j < ytemp + 7; j++) {
				gotoxy(1, j);
				cout << (char) 186;
				gotoxy(25, j);
				cout << (char) 186;
				gotoxy(78, j);
				cout << (char) 186;
			}

			ytemp++;
			gotoxy(26, ytemp);
			cout << "Origin: " << history[i].getOrigin();
			ytemp++;
			gotoxy(26, ytemp);
			cout << "Duration: " << history[i].getDuration() << " days "
					<< (char) 26 << " " << history[i].getInitialDate() << " - "
					<< history[i].getEndDate();
			ytemp++;
			gotoxy(26, ytemp);
			cout << " ";
			gotoxy(26, ytemp);
			cout << "Transport type: "
					<< history[i].getTransportation().getType();

			if (history[i].getTransportation().isFirstClass())
				cout << " " << (char) 26 << " FirstClass";

			ytemp++;
			gotoxy(26, ytemp);
			cout << "Establishment type: "
					<< history[i].getAccomodation().getType();
			ytemp++;
			gotoxy(26, ytemp);
			cout << " ";
			ytemp++;

			gotoxy(1, ytemp);
			cout << (char) 204;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 185;

			gotoxy(25, ytemp);
			cout << (char) 206;
		}

		gotoxy(1, ytemp);
		cout << (char) 200;
		for (int i = 2; i < 79; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}
		gotoxy(78, ytemp);
		cout << (char) 188;

		gotoxy(25, ytemp);
		cout << (char) 202;

		cout << endl << endl
				<< "- Press Enter to go back to the costumer menu -";

		getch();

		showCostumerMenu();
	}
}

void Interface::showUnsubscribe() {

	if (loggedtype == "Particular")
		db.removeParticular(loggedUserindex);
	else
		db.removeCommercial(loggedUserindex);

	system("cls");

	cout << "Costummer removed completly from the costummer list";

	Sleep(1000);

	db.saveData();

	showMainMenu();

}

void Interface::showSearchByCountry() {

	int ytemp = 2;
	bool vazio = false;
	vector<int> index;
	int contador = 0;
	string option;
	string upper;

	system("cls");
	cout << "- Write your country search option -" << endl << endl;

	cin >> option;

	if (!db.getPackages().size()) {
		system("cls");
		cout << " " << setfill(' ') << setw(45) << right
				<< "There are no Packages!" << setw(50) << endl;

		cout << "Press ENTER to go back to default menu package";
		getch();
		showDefaultPkg();
	}

	else {

		for (unsigned int j = 0; j < db.getPackages().size(); j++) {
			if (!db.getPackages()[j].isPromotional()) {
				if (db.getPackages()[j].getDestination() != option)
					vazio = true;
				else {
					vazio = false;
					break;
				}
			}
		}

		if (vazio) {
			system("cls");
			cout << " " << setfill(' ') << setw(45) << right
					<< "There are no Packages with that destination!"
					<< setw(50) << endl;
			cout << "Press ENTER to go back to default package menu";
			getch();
			showDefaultPkg();

		}

		else {

			system("cls");
			gotoxy(1, ytemp);
			cout << (char) 201;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 187;

			gotoxy(25, ytemp);
			cout << (char) 203;

			for (unsigned int i = 0; i < db.getPackages().size(); i++) {
				if (!db.getPackages()[i].isPromotional()) {
					if (db.getPackages()[i].getDestination() == option) {
						contador++;
						index.push_back(i);
						gotoxy(2, ytemp + 1);
						cout << contador << ".";
						gotoxy(2, ytemp + 4);
						cout << "Destination: "
								<< db.getPackages()[i].getDestination();
						for (int j = ytemp + 1; j < ytemp + 8; j++) {
							gotoxy(1, j);
							cout << (char) 186;
							gotoxy(25, j);
							cout << (char) 186;
							gotoxy(78, j);
							cout << (char) 186;
						}

						ytemp++;
						gotoxy(26, ytemp);
						cout << "Origin: " << db.getPackages()[i].getOrigin();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Duration: "
								<< db.getPackages()[i].getDuration() << " days "
								<< (char) 26 << " "
								<< db.getPackages()[i].getInitialDate() << " - "
								<< db.getPackages()[i].getEndDate();
						ytemp++;
						gotoxy(26, ytemp);
						cout << " ";
						ytemp++;
						gotoxy(26, ytemp);
						cout
								<< "Transport type: "
								<< db.getPackages()[i].getTransportation().getType();

						if (db.getPackages()[i].getTransportation().isFirstClass())
							cout << " " << (char) 26 << " FirstClass";

						ytemp++;
						gotoxy(26, ytemp);
						cout
								<< "Establishment type: "
								<< db.getPackages()[i].getAccomodation().getType();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Total Price (For one person): : "
								<< db.getPackages()[i].getPrice();
						ytemp++;

						gotoxy(1, ytemp);
						cout << (char) 204;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 185;

						gotoxy(25, ytemp);
						cout << (char) 206;
					}

				}

				gotoxy(1, ytemp);
				cout << (char) 200;
				for (int i = 2; i < 79; i++) {
					gotoxy(i, ytemp);
					cout << (char) 205;
				}
				gotoxy(78, ytemp);
				cout << (char) 188;

				gotoxy(25, ytemp);
				cout << (char) 202;
			}

			unsigned int temp = 1;
			ytemp = 3;
			gotoxy(2, ytemp);

			char Arrow = 0;

			Arrow = _kbhit();

			while (1) {
				Arrow = _getch();

				if (Arrow == '\r') {

					unsigned int people;

					system("cls");

					cout << "How many people will travel?" << endl << endl;

					cout << "Number: ";
					cin >> people;

					Trip tmp;

					tmp = db.getPackages()[index[temp - 1]];

					tmp.setPriceVar(people);

					unsigned int price = tmp.getPrice();

					system("cls");

					cout << " The total price of the Package will be " << price
							<< " euros" << endl
							<< "Are you sure you want to proceed? " << endl
							<< endl;

					cout << "1: Yes" << endl;
					cout << "2: No";

					gotoxy(0, 3);

					temp = 0;

					Arrow = 0;

					Arrow = _kbhit();

					while (1) {
						Arrow = _getch();

						if (Arrow == '\r') {
							switch (temp) {

							case 0:

								if (loggedtype == "Particular") {
									system("cls");
									db.addTripToUser(1, loggedUserindex, tmp);

									cout << " " << setfill(' ') << setw(45)
											<< right
											<< "Process order is completed"
											<< setw(50) << endl;
									Sleep(1000);
									showCostumerMenu();
								} else {
									system("cls");
									db.addTripToUser(0, loggedUserindex, tmp);
									cout << " " << setfill(' ') << setw(45)
											<< right
											<< "Process order is completed"
											<< setw(50) << endl;
									Sleep(1000);
									showCostumerMenu();
								}

								break;
							case 1:
								system("cls");
								cout << "Buy process canceled";
								showCostumerMenu();
								Sleep(1000);
								break;
							}
							break;
						}

						switch (Arrow) {

						case 49:
							if (loggedtype == "Particular") {
								system("cls");
								db.addTripToUser(1, loggedUserindex, tmp);

								cout << " " << setfill(' ') << setw(45) << right
										<< "Process order is completed"
										<< setw(50) << endl;
								Sleep(1000);
								showCostumerMenu();
							} else {
								system("cls");
								db.addTripToUser(0, loggedUserindex, tmp);
								cout << " " << setfill(' ') << setw(45) << right
										<< "Process order is completed"
										<< setw(50) << endl;
								Sleep(1000);
								showCostumerMenu();
							}
							break;
						case 50:
							system("cls");
							cout << "Buy process canceled";
							showCostumerMenu();
							Sleep(1000);
							break;

						case CPPKEYUP:
							if (!temp)
								break;
							else {
								temp = temp - 1;
								gotoxy(0, 3 + temp);
								break;
							}

						case CPPKEYDOWN:
							if (temp == 1)
								break;
							else {
								temp = temp + 1;
								gotoxy(0, 3 + temp);
								break;
							}
						}

					}

					break;
				}

				switch (Arrow) {
				case CPPKEYUP:

					if (temp == 1)
						break;
					else {
						temp = temp - 1;
						ytemp -= 7;
						gotoxy(2, ytemp);
						break;
					}

				case CPPKEYDOWN:
					if (temp == index.size())
						break;
					else {
						temp = temp + 1;
						ytemp += 7;
						gotoxy(2, ytemp);
						break;
					}
				}

			}
		}
	}

}

/*******************/
/**Admin Interface**/
/*******************/

void Interface::showAdminMenu() {
	system("cls");
	unsigned short int option = 0;

	cout << "                          -Administrator Menu-" << endl << endl;
	cout << "1. See Costumers" << endl << "2. See Packages" << endl
			<< "3. Add Package to costumer" << endl << "4. Add costumer" << endl
			<< "5. Remove Costumer" << endl << endl;
	cout << "6. Add Destination" << endl;
	cout << "7. Add Package" << endl;
	cout << "8. Logout" << endl << "9. Exit app" << endl;

	gotoxy(0, 2);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case 49:
			option = 1;
			break;
		case 50:
			option = 2;
			break;
		case 51:
			option = 3;
			break;
		case 52:
			option = 4;
			break;
		case 53:
			option = 5;
			break;
		case 54:
			option = 6;
			break;
		case 55:
			option = 7;
			break;
		case 56:
			option = 8;
			break;
		case 57:
			option = 9;
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(0, 2);
				temp = 1;
				break;
			} else if (temp == 3) {
				gotoxy(0, 3);
				temp = 2;
				break;
			} else if (temp == 4) {
				gotoxy(0, 4);
				temp = 3;
				break;
			} else if (temp == 5) {
				gotoxy(0, 5);
				temp = 4;
				break;
			} else if (temp == 6) {
				gotoxy(0, 6);
				temp = 5;
				break;
			} else if (temp == 7) {
				gotoxy(0, 8);
				temp = 6;
				break;
			} else if (temp == 8) {
				gotoxy(0, 9);
				temp = 7;
				break;
			} else if (temp == 9) {
				gotoxy(0, 10);
				temp = 8;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(0, 3);
				temp = 2;
				break;
			} else if (temp == 2) {
				gotoxy(0, 4);
				temp = 3;
				break;
			} else if (temp == 3) {
				gotoxy(0, 5);
				temp = 4;
				break;
			} else if (temp == 4) {
				gotoxy(0, 6);
				temp = 5;
				break;
			} else if (temp == 5) {
				gotoxy(0, 8);
				temp = 6;
				break;
			} else if (temp == 6) {
				gotoxy(0, 9);
				temp = 7;
				break;
			} else if (temp == 7) {
				gotoxy(0, 10);
				temp = 8;
				break;
			} else if (temp == 8) {
				gotoxy(0, 11);
				temp = 9;
				break;
			} else if (temp == 9)
				break;

		}

	}

	system("cls");

	bool done = false;

	while (!done) {

		switch (option) {
		case 1:
			showCostumers();
			done = true;
			showAdminMenu();
			break;
		case 2:
			showPackages();
			done = true;
			showAdminMenu();
			break;
		case 3:
			showAddTripToCostumer();
			done = true;
			showAdminMenu();
			break;
		case 4:
			showAddCostumer();
			done = true;
			showAdminMenu();
			break;
		case 5:
			showRemoveCostumer();
			done = true;
			showAdminMenu();
			break;
		case 6:
			showAddDestination();
			done = true;
			showAdminMenu();
			break;
		case 7:
			showAddNewPackage();
			done = true;
			showAdminMenu();
			break;
		case 8:
			db.saveData();
			showMainMenu();
			done = true;
			break;
		case 9:
			db.saveData();
			exit(0);
		default:
			break;

		}
	}
}

void Interface::showCostumers() {
	system("cls");
	unsigned short int option = 0;

	cout << "\n1. See all costumers" << endl;
	cout << "2. Search costumers by type (Particular/Commercial)" << endl;
	cout << "3. Search costumers by name";

	gotoxy(0, 1);

	db.sortCostumersByName(0, 1);
	db.sortCostumersByName(0, 0);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case 49:
			option = 1;
			break;
		case 50:
			option = 2;
			break;
		case 51:
			option = 3;
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(0, 1);
				temp = 1;
				break;
			} else if (temp == 3) {
				gotoxy(0, 2);
				temp = 2;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(0, 2);
				temp = 2;
				break;
			} else if (temp == 2) {
				gotoxy(0, 3);
				temp = 3;
				break;
			} else if (temp == 3)
				break;

		}

	}

	system("cls");

	bool done = false;

	while (!done) {

		switch (option) {
		case 1: {

			int ytemp = 2;

			if (!db.getParticular().size() && !db.getCommercial().size()) {
				cout << "There are no Users!";
				gotoxy(0, ytemp + 5);
				cout << "Back to Administrator Menu";
				gotoxy(0, ytemp + 5);
			}

			else {

				if (!db.getParticular().size()) {
					cout << "There are no Particular Users!";
					ytemp += 5;
					gotoxy(0, ytemp);
				}

				else {

					cout << setw(50) << right << "-Particular Costumers-"
							<< left << endl << endl;

					gotoxy(1, ytemp);
					cout << (char) 201;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 187;

					gotoxy(25, ytemp);
					cout << (char) 203;

					for (unsigned int i = 0; i < db.getParticular().size();
							i++) {

						gotoxy(2, ytemp + 1);
						cout << i + 1 << ".";
						gotoxy(2, ytemp + 4);
						cout << "Name: " << db.getParticular()[i].getName();
						for (int j = ytemp + 1; j < ytemp + 9; j++) {
							gotoxy(1, j);
							cout << (char) 186;
							gotoxy(25, j);
							cout << (char) 186;
							gotoxy(78, j);
							cout << (char) 186;
						}

						ytemp++;
						gotoxy(26, ytemp);
						cout << "E-mail: " << db.getParticular()[i].getEmail();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Phone Number: "
								<< db.getParticular()[i].getPhoneNumber();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Address: "
								<< db.getParticular()[i].getAddress();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Zip Code: "
								<< db.getParticular()[i].getZipCode();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Country: "
								<< db.getParticular()[i].getCountry();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Birth Date: "
								<< db.getParticular()[i].getBirthDate();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Age: " << db.getParticular()[i].getAge();
						ytemp++;

						gotoxy(1, ytemp);
						cout << (char) 204;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 185;

						gotoxy(25, ytemp);
						cout << (char) 206;
					}

					gotoxy(1, ytemp);
					cout << (char) 200;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 188;

					gotoxy(25, ytemp);
					cout << (char) 202;
				}
				/*Commercial*/

				if (!db.getCommercial().size()) {
					gotoxy(0, ytemp + 5);
					cout << "There are no Commercial Users!";
					gotoxy(0, ytemp + 10);
					cout << "Back to Administrator Menu";
					gotoxy(0, ytemp + 10);
				}

				else {
					ytemp += 3;
					gotoxy(0, ytemp);
					cout << setw(50) << right << "-Commercial Costumers-"
							<< left;
					ytemp += 2;

					gotoxy(1, ytemp);
					cout << (char) 201;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 187;

					gotoxy(25, ytemp);
					cout << (char) 203;

					for (unsigned int i = 0; i < db.getCommercial().size();
							i++) {

						gotoxy(2, ytemp + 1);
						cout << i + 1 << ".";
						gotoxy(2, ytemp + 4);
						cout << "Name: " << db.getCommercial()[i].getName();
						for (int j = ytemp + 1; j < ytemp + 8; j++) {
							gotoxy(1, j);
							cout << (char) 186;
							gotoxy(25, j);
							cout << (char) 186;
							gotoxy(78, j);
							cout << (char) 186;
						}

						ytemp++;
						gotoxy(26, ytemp);
						cout << "E-mail: " << db.getCommercial()[i].getEmail();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Phone Number: "
								<< db.getCommercial()[i].getPhoneNumber();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Address: "
								<< db.getCommercial()[i].getAddress();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Zip Code: "
								<< db.getCommercial()[i].getZipCode();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Country: "
								<< db.getCommercial()[i].getCountry();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Number of People: "
								<< db.getCommercial()[i].getNumPeople();
						ytemp++;

						gotoxy(1, ytemp);
						cout << (char) 204;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 185;

						gotoxy(25, ytemp);
						cout << (char) 206;
					}

					gotoxy(1, ytemp);
					cout << (char) 200;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 188;

					gotoxy(25, ytemp);
					cout << (char) 202;
					gotoxy(0, ytemp + 5);
					cout << "Back to Administrator Menu";
					gotoxy(0, ytemp + 5);
				}
			}
			done = true;
			break;
		}
		case 2: {
			system("cls");
			unsigned short int option2 = 0;

			cout << "What type of costumer do you wish to look for? " << endl
					<< endl;
			cout << "1: Particular" << endl << "2: Commercial\n\n";

			gotoxy(0, 2);

			int temp;
			temp = 1;

			char Arrow = 0;

			Arrow = _kbhit();

			while (option2 == 0) {
				Arrow = _getch();

				if (Arrow == '\r') {
					option = temp;
					break;
				}

				switch (Arrow) {

				case 49:
					option2 = 1;
					break;
				case 50:
					option2 = 2;
					break;

				case CPPKEYUP:
					if (temp == 1)
						break;

					else if (temp == 2) {
						gotoxy(0, 2);
						temp = 1;
						break;
					}

				case CPPKEYDOWN:
					if (temp == 1) {
						gotoxy(0, 3);
						temp = 2;
						break;
					}

				}

			}

			system("cls");

			bool done2 = false;

			while (!done2) {

				switch (option2) {

				case 1: {
					int ytemp = 2;
					if (!db.getParticular().size()) {
						gotoxy(0, ytemp);
						cout << "There are no Particular Users!";
						ytemp += 5;
						gotoxy(0, ytemp);
						cout << "Back to Administrator Menu";
						gotoxy(0, ytemp);
					}

					else {

						cout << setw(50) << right << "-Particular Costumers-"
								<< left << endl << endl;

						gotoxy(1, ytemp);
						cout << (char) 201;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 187;

						gotoxy(25, ytemp);
						cout << (char) 203;

						for (unsigned int i = 0; i < db.getParticular().size();
								i++) {

							gotoxy(2, ytemp + 1);
							cout << i + 1 << ".";
							gotoxy(2, ytemp + 4);
							cout << "Name: " << db.getParticular()[i].getName();
							for (int j = ytemp + 1; j < ytemp + 9; j++) {
								gotoxy(1, j);
								cout << (char) 186;
								gotoxy(25, j);
								cout << (char) 186;
								gotoxy(78, j);
								cout << (char) 186;
							}

							ytemp++;
							gotoxy(26, ytemp);
							cout << "E-mail: "
									<< db.getParticular()[i].getEmail();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Phone Number: "
									<< db.getParticular()[i].getPhoneNumber();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Address: "
									<< db.getParticular()[i].getAddress();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Zip Code: "
									<< db.getParticular()[i].getZipCode();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Country: "
									<< db.getParticular()[i].getCountry();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Birth Date: "
									<< db.getParticular()[i].getBirthDate();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Age: " << db.getParticular()[i].getAge();
							ytemp++;

							gotoxy(1, ytemp);
							cout << (char) 204;
							for (int i = 2; i < 79; i++) {
								gotoxy(i, ytemp);
								cout << (char) 205;
							}
							gotoxy(78, ytemp);
							cout << (char) 185;

							gotoxy(25, ytemp);
							cout << (char) 206;
						}

						gotoxy(1, ytemp);
						cout << (char) 200;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 188;

						gotoxy(25, ytemp);
						cout << (char) 202;
						gotoxy(0, ytemp + 5);
						cout << "Back to Main Menu!";
						gotoxy(0, ytemp + 5);
					}

					done2 = true;
					break;
				}

				case 2: {
					int ytemp = 2;
					if (!db.getCommercial().size()) {
						gotoxy(0, ytemp);
						cout << "There are no Commercial Users!";
						ytemp += 5;
						gotoxy(0, ytemp);
						cout << "Back to Administrator Menu";
						gotoxy(0, ytemp);
					}

					else {
						cout << setw(50) << right << "-Commercial Costumers-"
								<< left << endl << endl;

						gotoxy(1, ytemp);
						cout << (char) 201;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 187;

						gotoxy(25, ytemp);
						cout << (char) 203;

						for (unsigned int i = 0; i < db.getCommercial().size();
								i++) {

							gotoxy(2, ytemp + 1);
							cout << i + 1 << ".";
							gotoxy(2, ytemp + 4);
							cout << "Name: " << db.getCommercial()[i].getName();
							for (int j = ytemp + 1; j < ytemp + 8; j++) {
								gotoxy(1, j);
								cout << (char) 186;
								gotoxy(25, j);
								cout << (char) 186;
								gotoxy(78, j);
								cout << (char) 186;
							}

							ytemp++;
							gotoxy(26, ytemp);
							cout << "E-mail: "
									<< db.getCommercial()[i].getEmail();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Phone Number: "
									<< db.getCommercial()[i].getPhoneNumber();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Address: "
									<< db.getCommercial()[i].getAddress();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Zip Code: "
									<< db.getCommercial()[i].getZipCode();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Country: "
									<< db.getCommercial()[i].getCountry();
							ytemp++;
							gotoxy(26, ytemp);
							cout << "Number of People: "
									<< db.getCommercial()[i].getNumPeople();
							ytemp++;

							gotoxy(1, ytemp);
							cout << (char) 204;
							for (int i = 2; i < 79; i++) {
								gotoxy(i, ytemp);
								cout << (char) 205;
							}
							gotoxy(78, ytemp);
							cout << (char) 185;

							gotoxy(25, ytemp);
							cout << (char) 206;
						}

						gotoxy(1, ytemp);
						cout << (char) 200;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 188;

						gotoxy(25, ytemp);
						cout << (char) 202;
						gotoxy(0, ytemp + 5);
						cout << "Back to Administrator Menu";
						gotoxy(0, ytemp + 5);

					}
					done2 = true;
					break;
				}
				}
			}
			done = true;
			break;
		}

		case 3: {
			string search_st;
			vector<Particular> temp1;
			vector<Commercial> temp2;
			unsigned int found;

			cout << "Write the term you wish to search: ";
			cin >> search_st;
			cin.ignore(1000, '\n');
			cin.clear();

			for (unsigned int i = 0; i < db.getParticular().size(); i++) {
				found = db.getParticular()[i].getName().find(search_st);
				if (found != string::npos)
					temp1.push_back(db.getParticular()[i]);
			}

			for (unsigned int i = 0; i < db.getCommercial().size(); i++) {
				found = db.getCommercial()[i].getName().find(search_st);
				if (found != string::npos)
					temp2.push_back(db.getCommercial()[i]);
			}

			int ytemp = 2;

			if (!temp1.size() && !temp2.size()) {
				cout
						<< endl
						<< endl
						<< setw(45)
						<< right
						<< "There are no Users that correspond to the term you inserted!!";
				gotoxy(0, ytemp + 10);
				cout << "Back to Administrator Menu";
				gotoxy(0, ytemp + 10);
			}

			else {

				if (!temp1.size()) {
					gotoxy(0, ytemp);
					cout
							<< "There are no Particular Users that correspond to the term you inserted!\n";
				}

				else {
					gotoxy(0, ytemp);
					cout << setw(50) << right << "-Particulars Costumers-"
							<< left;
					ytemp += 2;

					gotoxy(1, ytemp);
					cout << (char) 201;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 187;

					gotoxy(25, ytemp);
					cout << (char) 203;

					for (unsigned int i = 0; i < temp1.size(); i++) {

						gotoxy(2, ytemp + 1);
						cout << i + 1 << ".";
						gotoxy(2, ytemp + 4);
						cout << "Name: " << temp1[i].getName();
						for (int j = ytemp + 1; j < ytemp + 9; j++) {
							gotoxy(1, j);
							cout << (char) 186;
							gotoxy(25, j);
							cout << (char) 186;
							gotoxy(78, j);
							cout << (char) 186;
						}

						ytemp++;
						gotoxy(26, ytemp);
						cout << "E-mail: " << temp1[i].getEmail();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Phone Number: " << temp1[i].getPhoneNumber();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Address: " << temp1[i].getAddress();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Zip Code: " << temp1[i].getZipCode();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Country: " << temp1[i].getCountry();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Birth Date: " << temp1[i].getBirthDate();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Age: " << temp1[i].getAge();
						ytemp++;

						gotoxy(1, ytemp);
						cout << (char) 204;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 185;

						gotoxy(25, ytemp);
						cout << (char) 206;
					}

					gotoxy(1, ytemp);
					cout << (char) 200;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 188;

					gotoxy(25, ytemp);
					cout << (char) 202;
				}
				/*Commercial*/

				if (!temp2.size()) {
					gotoxy(0, ytemp + 5);
					cout
							<< "There are no Commercial Users that correspond to the term you inserted!!";
					gotoxy(0, ytemp + 10);
					cout << "Back to Administrator Menu";
					gotoxy(0, ytemp + 10);
				}

				else {
					ytemp += 5;
					gotoxy(0, ytemp);
					cout << setw(50) << right << "-Commercial Costumers-"
							<< left;
					ytemp += 2;

					gotoxy(1, ytemp);
					cout << (char) 201;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 187;

					gotoxy(25, ytemp);
					cout << (char) 203;

					for (unsigned int i = 0; i < temp2.size(); i++) {

						gotoxy(2, ytemp + 1);
						cout << i + 1 << ".";
						gotoxy(2, ytemp + 4);
						cout << "Name: " << temp2[i].getName();
						for (int j = ytemp + 1; j < ytemp + 8; j++) {
							gotoxy(1, j);
							cout << (char) 186;
							gotoxy(25, j);
							cout << (char) 186;
							gotoxy(78, j);
							cout << (char) 186;
						}

						ytemp++;
						gotoxy(26, ytemp);
						cout << "E-mail: " << temp2[i].getEmail();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Phone Number: " << temp2[i].getPhoneNumber();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Address: " << temp2[i].getAddress();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Zip Code: " << temp2[i].getZipCode();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Country: " << temp2[i].getCountry();
						ytemp++;
						gotoxy(26, ytemp);
						cout << "Number of People: " << temp2[i].getNumPeople();
						ytemp++;

						gotoxy(1, ytemp);
						cout << (char) 204;
						for (int i = 2; i < 79; i++) {
							gotoxy(i, ytemp);
							cout << (char) 205;
						}
						gotoxy(78, ytemp);
						cout << (char) 185;

						gotoxy(25, ytemp);
						cout << (char) 206;
					}

					gotoxy(1, ytemp);
					cout << (char) 200;
					for (int i = 2; i < 79; i++) {
						gotoxy(i, ytemp);
						cout << (char) 205;
					}
					gotoxy(78, ytemp);
					cout << (char) 188;

					gotoxy(25, ytemp);
					cout << (char) 202;
					gotoxy(0, ytemp + 5);
					cout << "Back to Administrator Menu";
					gotoxy(0, ytemp + 5);
				}
			}

			done = true;
			break;
		}
		default:
			break;

		}
	}
	getch();

}

void Interface::showAddCostumer() {
	system("cls");
	unsigned short int option = 0;

	cout << "What type of costumer do you wish to create? " << endl << endl;
	cout << "1: Particular" << endl << "2: Commercial\n\n";

	gotoxy(0, 2);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case 49:
			option = 1;
			break;
		case 50:
			option = 2;
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(0, 2);
				temp = 1;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(0, 3);
				temp = 2;
				break;
			}

			else if (temp == 2)
				break;

		}
	}

	system("cls");

	bool done = false;
	bool valid = false;

	while (!done) {

		switch (option) {

		case 1: {
			Particular part;
			string generic;
			string pw;

			cout << "-Particular-\n\n";

			while (!valid) {
				cout << "Name: ";
				getline(cin, generic);
				try {
					part.setName(generic);
				} catch (InvalidName) {
					cerr
							<< "The name you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			valid = false;
			unsigned int d, m, y;
			char temp = '/';
			char temp1 = temp;
			while (!valid) {
				cout << "Birth Date(dd/mm/yyyy): ";
				cin >> d >> temp >> m >> temp1 >> y;

				if (d <= 0 || d >= 31 || m <= 0 || m > 12 || y < 1910
						|| y > 2011 || temp != '/' || temp1 != '/') {
					cerr << "Invalid date input. Try again.\n";
					cin.ignore(1000, '\n');
					cin.clear();
					continue;
				}

				Date dt(d, m, y);

				try {
					part.setDate(dt);
				} catch (InvalidDate) {
					cerr << "Invalid date input. Try again.\n";
					continue;
				}

				valid = true;
			}

			cin.ignore(1000, '\n');
			cin.clear();
			valid = false;
			while (!valid) {
				cout << "E-mail: ";
				getline(cin, generic);

				try {
					part.setEmail(generic);
				} catch (InvalidEmail) {
					cerr
							<< "The e-mail you wrote is not valid. It must have a @. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			valid = false;
			while (!valid) {
				cout << "Phone Number: ";
				getline(cin, generic);
				try {
					part.setPhoneNumber(generic);
				} catch (InvalidPhoneNumber) {
					cerr
							<< "The phone number you wrote is not valid. It must have 9 digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			cout << "Address: ";
			getline(cin, generic);
			part.setAddress(generic);
			valid = false;
			while (!valid) {
				cout << "Zip Code: ";
				getline(cin, generic);
				try {
					part.setZipCode(generic);
				} catch (InvalidZipCode) {
					cerr
							<< "The Zip Code you wrote is not valid. It must only contain digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;

			}
			valid = false;
			while (!valid) {
				cout << "Country: ";
				getline(cin, generic);
				try {
					part.setCountry(generic);
				} catch (InvalidCountry) {
					cerr
							<< "The country you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}

			valid = false;
			while (!valid) {
				cout << "\nSet your login data\n\n";
				cout << "Username: ";
				getline(cin, generic);
				cout << "Password: ";
				getline(cin, pw);
				try {
					part.changeLogin(generic, pw);
				} catch (InvalidLogin) {
					cerr
							<< "The login data you inserted is not valid. Try Again\n";
					generic.clear();
					pw.clear();
					continue;
				}
				valid = true;
			}
			db.addParticular(part);
			done = true;
			break;
		}

		case 2: {
			Commercial comme;
			string generic;
			unsigned int generic2;
			string pw;
			valid = false;

			cout << "-Commercial-\n\n";
			while (!valid) {
				cout << "Company Name: ";
				getline(cin, generic);
				try {
					comme.setName(generic);
				} catch (InvalidName) {
					cerr
							<< "The name you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}

			valid = false;
			while (!valid) {

				cout << "Number of People: ";
				cin >> generic2;
				cin.ignore(1000, '\n');
				cin.clear();
				try {
					comme.setNumPeople(generic2);
				} catch (InvalidNumPeople) {
					cerr
							<< "The number of people you wrote is not valid. It must be between 1 - 500 Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			valid = false;
			while (!valid) {
				cout << "Phone Number: ";
				getline(cin, generic);
				try {
					comme.setPhoneNumber(generic);
				} catch (InvalidPhoneNumber) {
					cerr
							<< "The phone number you wrote is not valid. It must have 9 digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}
			cout << "Address: ";
			getline(cin, generic);
			comme.setAddress(generic);
			valid = false;
			while (!valid) {
				cout << "Zip Code: ";
				getline(cin, generic);
				try {
					comme.setZipCode(generic);
				} catch (InvalidZipCode) {
					cerr
							<< "The Zip Code you wrote is not valid. It must only contain digits. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;

			}
			valid = false;
			while (!valid) {
				cout << "Country: ";
				getline(cin, generic);
				try {
					comme.setCountry(generic);
				} catch (InvalidCountry) {
					cerr
							<< "The country you wrote is not valid. It must only contain alphabetic characters. Try Again\n";
					generic.clear();
					continue;
				}
				valid = true;
			}

			valid = false;
			while (!valid) {
				cout << "\nSet your login data\n\n";
				cout << "Username: ";
				getline(cin, generic);
				cout << "Password: ";
				getline(cin, pw);
				try {
					comme.changeLogin(generic, pw);
				} catch (InvalidLogin) {
					cerr
							<< "The login data you inserted is not valid. Try Again\n";
					generic.clear();
					pw.clear();
					continue;
				}
				valid = true;
			}
			db.addCommercial(comme);
			done = true;
			break;
		}

		default:
			break;
		}
	}
	db.saveData();
}

void Interface::showAddNewPackage() {
	system("cls");
	Trip t;
	Transportation tr;
	Accomodation ac;

	unsigned short int option = 0;
	unsigned int ytemp = 2;
	bool done = false;

	cout << "Pick one of the following option" << endl << endl;
	cout << "1. Add Default Packages" << endl;
	cout << "2. Create a Promotion";

	gotoxy(0, ytemp);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case 49:
			option = 1;
			break;
		case 50:
			option = 2;
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(0, 2);
				temp = 1;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(0, 3);
				temp = 2;
				break;
			} else if (temp == 2) {
				break;
			}

		}

	}

	bool valid = false;

	while (!done) {

		switch (option) {
		case 1: {
			system("cls");
			cout << setw(45) << right << "-New Trip-" << left << endl << endl;

			string generic;
			int generic2;

			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Origin: ";
			getline(cin, generic);
			t.setOrigin(generic);
			cout << "Destination: ";
			getline(cin, generic);
			t.setDestination(generic);

			cout << "\tDuration (in days): ";
			cin >> generic2;
			t.setDuration(generic2);
			cin.ignore(1000, '\n');
			cin.clear();

			valid = false;
			unsigned int d, m, y;
			char temp = '/';
			char temp1 = temp;
			while (!valid) {
				cout << "\tInitial Date(dd/mm/yyyy): ";
				cin >> d >> temp >> m >> temp1 >> y;

				if (d <= 0 || d >= 31 || m <= 0 || m > 12 || y < 1910
						|| y > 2011 || temp != '/' || temp1 != '/') {
					cerr << "Invalid date input. Try again.\n";
					cin.ignore(1000, '\n');
					cin.clear();
					continue;
				}

				Date dt(d, m, y);

				try {
					t.setInitialDate(dt);
				} catch (InvalidDate) {
					cerr << "Invalid date input. Try again.\n";
					continue;
				}

				valid = true;
			}

			t.setNumPeople(1);

			cout << "\nTransportation\n";
			cout << "\tDistance: ";
			cin >> generic2;
			cin.ignore(1000, '\n');
			cin.clear();
			tr.setDistance(generic2);
			valid = false;
			while (!valid) {
				cout << "\tType of transport: ";
				getline(cin, generic);
				try {
					tr.setType(generic);
				} catch (InvalidTransportationType) {
					cerr << "Invalid transportation type\n";
					continue;
				}
				valid = true;
			}
			t.setTransportation(tr);
			valid = false;
			cout << "\nAccomodation\n";
			while (!valid) {
				cout << "\tEstablishment type: ";
				getline(cin, generic);
				try {
					ac.setType(generic);
				} catch (InvalidAccomodationType) {
					cerr << "Invalid accomodation type\n";
				}
				valid = true;
			}
			cout << "\tPrice: ";
			cin >> generic2;
			cin.ignore(1000, '\n');
			cin.clear();
			ac.setPrice(generic2);
			t.setAccomodation(ac);
			tr.resetPrice();
			t.setTransportation(tr);
			t.setPrice();

			db.addTrip(t);
			done = true;
			break;
		}

		case 2: {
			system("cls");

			vector<Trip> part;
			for (unsigned int i = 0; i < db.getPackages().size(); i++)
				if (!db.getPackages()[i].isPromotional())
					part.push_back(db.getPackages()[i]);

			gotoxy(0, 0);
			cout << "Choose the Package you wish to make a promotion";

			ytemp = showPackages(1);

			unsigned int temp2;
			unsigned short int option2 = 0;
			ytemp = 3;
			gotoxy(2, ytemp);

			temp2 = 1;

			Arrow = 0;

			Arrow = _kbhit();

			while (option2 == 0) {

				Arrow = _getch();

				if (Arrow == '\r') {
					option2 = temp2;
					break;
				}

				switch (Arrow) {

				case CPPKEYUP:
					if (temp2 == 1)
						break;

					else if (temp2 > 1 && temp2 <= part.size()) {
						ytemp -= 6;
						gotoxy(2, ytemp);
						temp2 -= 1;
						break;
					}

					break;

				case CPPKEYDOWN:

					if (temp2 == part.size())
						break;

					else if (temp2 < part.size()) {

						ytemp += 6;
						gotoxy(2, ytemp);

						temp2 += 1;
						break;
					}

					break;

				}

			}

			system("cls");
			gotoxy(0, 0);
			double promo;

			cout
					<< "Choose the discount you want to add to the package (0 - 1): ";
			cin >> promo;

			db.addPromotion(option2 - 1, promo);
			done = true;
			break;

		}
		}
	}

	db.saveData();
}

void Interface::showRemoveCostumer() {
	cout << "Choose the User you wish to remove\n\n";

	if (!db.getParticular().size() && !db.getCommercial().size()) {

		cout << " " << setfill(' ') << setw(45) << right
				<< "There are no Users!" << setw(50) << endl;
		gotoxy(0, 10);
		cout << "Back to Administrator Menu";
		gotoxy(0, 10);
		getch();
		showAdminMenu();
	}

	else {

		int option = showAllCostumers();
		bool done = false;

		while (!done) {
			if ((unsigned) option <= db.getParticular().size()) {
				db.removeParticular(option);
				done = true;
			}

			else {
				db.removeCommercial(option - db.getParticular().size());
				done = true;
			}
		}

		db.saveData();
	}
}

int Interface::showAllCostumers() {
	int ytemp = 2;
	gotoxy(1, ytemp);
	cout << (char) 201;
	for (int i = 2; i < 79; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}
	gotoxy(78, ytemp);
	cout << (char) 187;

	gotoxy(25, ytemp);
	cout << (char) 203;

	for (unsigned int i = 0; i < db.getParticular().size(); i++) {

		gotoxy(2, ytemp + 1);
		cout << i + 1 << ".";
		gotoxy(2, ytemp + 4);
		cout << "Name: " << db.getParticular()[i].getName();
		for (int j = ytemp + 1; j < ytemp + 9; j++) {
			gotoxy(1, j);
			cout << (char) 186;
			gotoxy(25, j);
			cout << (char) 186;
			gotoxy(78, j);
			cout << (char) 186;
		}

		ytemp++;
		gotoxy(26, ytemp);
		cout << "E-mail: " << db.getParticular()[i].getEmail();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Phone Number: " << db.getParticular()[i].getPhoneNumber();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Address: " << db.getParticular()[i].getAddress();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Zip Code: " << db.getParticular()[i].getZipCode();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Country: " << db.getParticular()[i].getCountry();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Birth Date: " << db.getParticular()[i].getBirthDate();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Age: " << db.getParticular()[i].getAge();
		ytemp++;

		gotoxy(1, ytemp);
		cout << (char) 204;
		for (int i = 2; i < 79; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}
		gotoxy(78, ytemp);
		cout << (char) 185;

		gotoxy(25, ytemp);
		cout << (char) 206;
	}

	gotoxy(1, ytemp);
	cout << (char) 204;
	for (int i = 2; i < 79; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}
	gotoxy(78, ytemp);
	cout << (char) 185;

	gotoxy(25, ytemp);
	cout << (char) 206;

	/**********/
	/*Costumer*/
	/**********/

	for (unsigned int i = 0; i < db.getCommercial().size(); i++) {

		gotoxy(2, ytemp + 1);
		cout << i + 1 + db.getParticular().size() << ".";
		gotoxy(2, ytemp + 4);
		cout << "Name: " << db.getCommercial()[i].getName();
		for (int j = ytemp + 1; j < ytemp + 8; j++) {
			gotoxy(1, j);
			cout << (char) 186;
			gotoxy(25, j);
			cout << (char) 186;
			gotoxy(78, j);
			cout << (char) 186;
		}

		ytemp++;
		gotoxy(26, ytemp);
		cout << "E-mail: " << db.getCommercial()[i].getEmail();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Phone Number: " << db.getCommercial()[i].getPhoneNumber();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Address: " << db.getCommercial()[i].getAddress();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Zip Code: " << db.getCommercial()[i].getZipCode();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Country: " << db.getCommercial()[i].getCountry();
		ytemp++;
		gotoxy(26, ytemp);
		cout << "Number of People: " << db.getCommercial()[i].getNumPeople();
		ytemp++;

		gotoxy(1, ytemp);
		cout << (char) 204;
		for (int i = 2; i < 79; i++) {
			gotoxy(i, ytemp);
			cout << (char) 205;
		}
		gotoxy(78, ytemp);
		cout << (char) 185;

		gotoxy(25, ytemp);
		cout << (char) 206;
	}

	gotoxy(1, ytemp);
	cout << (char) 200;
	for (int i = 2; i < 79; i++) {
		gotoxy(i, ytemp);
		cout << (char) 205;
	}
	gotoxy(78, ytemp);
	cout << (char) 188;

	gotoxy(25, ytemp);
	cout << (char) 202;

	ytemp = 3;
	gotoxy(2, ytemp);

	unsigned int temp;
	unsigned short int option = 0;
	unsigned int tam = db.getParticular().size() + db.getCommercial().size();

	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case CPPKEYUP:
			if (temp == 1)
				break;
			for (unsigned int i = 2; i <= tam; i++)
				if (temp == i) {
					if (temp <= db.getParticular().size() + 1) {
						ytemp -= 8;
						gotoxy(2, ytemp);
					} else if (temp > db.getParticular().size() + 1) {
						ytemp -= 7;
						gotoxy(2, ytemp);
					}

					temp = i - 1;
					break;
				}

			break;

		case CPPKEYDOWN:

			if (temp == tam)
				break;

			for (unsigned int i = 1; i < tam; i++)
				if (temp == i) {
					if (temp <= db.getParticular().size()) {
						ytemp += 8;
						gotoxy(2, ytemp);
					} else if (temp >= db.getParticular().size() + 1) {
						ytemp += 7;
						gotoxy(2, ytemp);
					}

					temp = i + 1;
					break;
				}

			break;

		}

	}

	return option;

}

void Interface::showPackages() {
	system("cls");
	unsigned short int option = 0;
	unsigned int ytemp = 2;

	cout << "What kind of Packages do you want to see" << endl << endl;
	cout << "1. Default Packages" << endl;
	cout << "2. Promotional Packages";

	gotoxy(0, 2);

	int temp;
	temp = 1;

	char Arrow = 0;

	Arrow = _kbhit();

	while (option == 0) {
		Arrow = _getch();

		if (Arrow == '\r') {
			option = temp;
			break;
		}

		switch (Arrow) {

		case 49:
			option = 1;
			break;
		case 50:
			option = 2;
			break;

		case CPPKEYUP:
			if (temp == 1)
				break;

			else if (temp == 2) {
				gotoxy(0, 2);
				temp = 1;
				break;
			}

		case CPPKEYDOWN:
			if (temp == 1) {
				gotoxy(0, 3);
				temp = 2;
				break;
			} else if (temp == 2) {
				break;
			}

		}

	}

	system("cls");

	ytemp = showPackages(option);

	ytemp += 2;
	gotoxy(0, ytemp);
	cout << "Back to Main Menu";
	gotoxy(0, ytemp);
	getch();

}

int Interface::showPackages(int op) {
	int ytemp = 2;

	vector<Trip> part, promo;
	for (unsigned int i = 0; i < db.getPackages().size(); i++) {
		if (db.getPackages()[i].isPromotional())
			promo.push_back(db.getPackages()[i]);
		else
			part.push_back(db.getPackages()[i]);
	}

	switch (op) {
	case 1: {

		if (!part.size()) {
			gotoxy(0, 1);
			cout << "There are no Default Packages!";
			return ytemp;
		}

		else {
			gotoxy(0, 1);
			cout << setw(40) << right << "-Default Packages-" << left;

			gotoxy(1, ytemp);
			cout << (char) 201;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 187;

			gotoxy(25, ytemp);
			cout << (char) 203;

			for (unsigned int i = 0; i < part.size(); i++) {

				gotoxy(2, ytemp + 1);
				cout << i + 1 << ".";
				gotoxy(2, ytemp + 3);
				cout << "Destination: " << part[i].getDestination();
				for (int j = ytemp + 1; j < ytemp + 7; j++) {
					gotoxy(1, j);
					cout << (char) 186;
					gotoxy(25, j);
					cout << (char) 186;
					gotoxy(78, j);
					cout << (char) 186;
				}

				ytemp++;
				gotoxy(26, ytemp);
				cout << "Origin: " << part[i].getOrigin();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Duration: " << part[i].getDuration() << " days "
						<< (char) 26 << " " << part[i].getInitialDate() << " - "
						<< part[i].getEndDate();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Transport type: "
						<< part[i].getTransportation().getType();

				if (part[i].getTransportation().isFirstClass())
					cout << " " << (char) 26 << " FirstClass";

				ytemp++;
				gotoxy(26, ytemp);
				cout << "Establishment type: "
						<< part[i].getAccomodation().getType();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Total Price (For one person): " << part[i].getPrice();
				ytemp++;

				gotoxy(1, ytemp);
				cout << (char) 204;
				for (int i = 2; i < 79; i++) {
					gotoxy(i, ytemp);
					cout << (char) 205;
				}
				gotoxy(78, ytemp);
				cout << (char) 185;

				gotoxy(25, ytemp);
				cout << (char) 206;
			}

			gotoxy(1, ytemp);
			cout << (char) 200;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 188;

			gotoxy(25, ytemp);
			cout << (char) 202;
		}
		break;

	}

		break;
	case 2: {
		if (!promo.size()) {
			cout << " " << setfill(' ') << setw(45) << right
					<< "There are no Promotional Packages!" << setw(50) << endl;
			return ytemp;
		}

		else {

			cout << setw(50) << right << "-Promotional Packages-" << left
					<< endl << endl;

			gotoxy(1, ytemp);
			cout << (char) 201;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 187;

			gotoxy(25, ytemp);
			cout << (char) 203;

			for (unsigned int i = 0; i < promo.size(); i++) {

				gotoxy(2, ytemp + 1);
				cout << i + 1 << ".";
				gotoxy(2, ytemp + 3);
				cout << "Destination: " << promo[i].getDestination();
				for (int j = ytemp + 1; j < ytemp + 7; j++) {
					gotoxy(1, j);
					cout << (char) 186;
					gotoxy(25, j);
					cout << (char) 186;
					gotoxy(78, j);
					cout << (char) 186;
				}

				ytemp++;
				gotoxy(26, ytemp);
				cout << "Origin: " << promo[i].getOrigin();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Duration: " << promo[i].getDuration() << " days "
						<< (char) 26 << " " << promo[i].getInitialDate()
						<< " - " << promo[i].getEndDate();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Transport type: "
						<< promo[i].getTransportation().getType();

				if (promo[i].getTransportation().isFirstClass())
					cout << " " << (char) 26 << " FirstClass";

				ytemp++;
				gotoxy(26, ytemp);
				cout << "Establishment type: "
						<< promo[i].getAccomodation().getType();
				ytemp++;
				gotoxy(26, ytemp);
				cout << "Total Price (For one person): " << promo[i].getPrice();
				ytemp++;

				gotoxy(1, ytemp);
				cout << (char) 204;
				for (int i = 2; i < 79; i++) {
					gotoxy(i, ytemp);
					cout << (char) 205;
				}
				gotoxy(78, ytemp);
				cout << (char) 185;

				gotoxy(25, ytemp);
				cout << (char) 206;
			}

			gotoxy(1, ytemp);
			cout << (char) 200;
			for (int i = 2; i < 79; i++) {
				gotoxy(i, ytemp);
				cout << (char) 205;
			}
			gotoxy(78, ytemp);
			cout << (char) 188;

			gotoxy(25, ytemp);
			cout << (char) 202;
		}
		break;

	}

	}

	return ytemp;
}

void Interface::showAddTripToCostumer() {
	cout << "Choose the User who's going to buy a Trip\n\n";

	vector<Trip> part, promo;
	for (unsigned int i = 0; i < db.getPackages().size(); i++) {
		if (db.getPackages()[i].isPromotional())
			promo.push_back(db.getPackages()[i]);
		else
			part.push_back(db.getPackages()[i]);
	}

	if (!db.getParticular().size() && !db.getCommercial().size())
		cout << " " << (char) 186 << setfill(' ') << setw(45) << right
				<< "There are no Users!" << setw(50) << (char) 186 << endl;

	else {

		int option = showAllCostumers();

		bool done = false;

		while (!done) {

			system("cls");
			unsigned short int option2 = 0;
			unsigned int ytemp = 2;

			cout << "What kind of Packages does the User want to buy" << endl
					<< endl;
			cout << "1. Default Packages" << endl;
			cout << "2. Promotional Packages";

			gotoxy(0, 2);

			int temp1;
			temp1 = 1;

			char Arrow = 0;

			Arrow = _kbhit();

			while (option2 == 0) {
				Arrow = _getch();

				if (Arrow == '\r') {
					option2 = temp1;
					break;
				}

				switch (Arrow) {

				case 49:
					option2 = 1;
					break;
				case 50:
					option2 = 2;
					break;

				case CPPKEYUP:
					if (temp1 == 1)
						break;

					else if (temp1 == 2) {
						gotoxy(0, 2);
						temp1 = 1;
						break;
					}

				case CPPKEYDOWN:
					if (temp1 == 1) {
						gotoxy(0, 3);
						temp1 = 2;
						break;
					} else if (temp1 == 2) {
						break;
					}

				}

			}

			system("cls");
			cout << "Choose the package ";

			if ((unsigned) option <= db.getParticular().size())
				cout << db.getParticular()[option - 1].getName();
			else
				cout
						<< db.getCommercial()[option - db.getParticular().size()
								- 1].getName();
			cout << " wants to buy\n\n";

			ytemp = showPackages(option2);

			unsigned int temp2;
			unsigned short int option3 = 0;
			unsigned int tam;
			ytemp = 3;
			gotoxy(2, ytemp);

			if (option2 == 1)
				tam = part.size();
			else if (option2 == 2)
				tam = promo.size();

			temp2 = 1;

			Arrow = 0;

			Arrow = _kbhit();

			while (option3 == 0) {
				Arrow = _getch();

				if (Arrow == '\r') {
					option3 = temp2;
					break;
				}

				switch (Arrow) {

				case CPPKEYUP:
					if (temp2 == 1)
						break;
					for (unsigned int i = 2; i <= tam; i++)
						if (temp2 == i) {
							ytemp -= 6;
							gotoxy(2, ytemp);

							temp2 = i - 1;
							break;
						}

					break;

				case CPPKEYDOWN:

					if (temp2 == tam)
						break;

					for (unsigned int i = 1; i < tam; i++)
						if (temp2 == i) {

							ytemp += 6;
							gotoxy(2, ytemp);

							temp2 = i + 1;
							break;
						}

					break;

				}

			}

			if ((unsigned) option <= db.getParticular().size()) {
				if (option2 == 1)
					db.addTripToUser(1, option - 1, part[option3 - 1]);

				else if (option2 == 2)
					db.addTripToUser(1, option - 1, promo[option3 - 1]);
			}

			else {
				if (option2 == 1)
					db.addTripToUser(2, option - 1, part[option3 - 1]);

				else if (option2 == 2)
					db.addTripToUser(2, option - 1, promo[option3 - 1]);
			}

			done = true;
		}
	}

	db.saveData();
}

void Interface::showAddDestination() {
	system("cls");
	string dest;
	Accomodation ac;
	bool valid = false;
	cout << setw(45) << right << "-New Destination-" << left << endl << endl;

	string generic;
	int generic2;

	cin.ignore(1000, '\n');
	cin.clear();
	cout << "Destination: ";
	getline(cin, dest);

	cout << "\nAccomodation\n";
	while (!valid) {
		cout << "\tEstablishment type: ";
		getline(cin, generic);
		try {
			ac.setType(generic);
		} catch (InvalidAccomodationType) {
			cerr << "Invalid accomodation type\n";
			continue;
		}
		valid = true;
	}
	cout << "\tPrice: ";
	cin >> generic2;
	cin.ignore(1000, '\n');
	cin.clear();
	ac.setPrice(generic2);

	db.addAccomodation(dest, ac);

	db.saveData();
}

