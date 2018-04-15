#include <iostream>
#include "Database.h"
#include "Interface.h"
#include "Trip.h"
#include "User.h"

using namespace std;

int main() {
	Database db;

	db.addTransportation(Transportation(0,"plane",1,0));
	db.addTransportation(Transportation(0,"boat",1,0));
	db.addTransportation(Transportation(0,"train",1,0));

	db.addAccomodation("EUA",Accomodation("hotel",1,80));
	db.addAccomodation("EUA",Accomodation("motel",1,40));
	db.addAccomodation("Spain",Accomodation("hotel",1,60));

	db.addTrip(
				(Trip(Date(9, 11, 2011),db.getAccomodations()["EUA"][0],
					db.getTransportations()[0], "Portugal", "EUA",4)));

	db.addTrip(Trip(Date(15, 12, 2011), db.getAccomodations()["Spain"][0],
			Transportation(300, "plane", 4, 0), "Portugal", "Spain",7,4));


	Interface it = Interface(db);
	SetConsoleTitle(
			"                                                              ---- Travel Agency ----");

	SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY
					| BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED
					| BACKGROUND_BLUE);



	it.showInitialScreen();

	return 0;
}
