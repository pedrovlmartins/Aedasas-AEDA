#include"Database.h"

using namespace std;

Database::Database() {
	Admin joao("PedroM", "aeda1");
	Admin pedroM("JoaoL", "aeda2");
	Admin pedroA("PedroA", "aeda3");
	admins.push_back(joao);
	admins.push_back(pedroM);
	admins.push_back(pedroA);
}

void Database::saveData() {
	ofstream out_f1("particulars.txt");
	ofstream out_f2("commercials.txt");
	ofstream out_f3("admins.txt");
	ofstream out_f4("packages.txt");
	ofstream out_f5("destinations.txt");
	ofstream out_f6("accomodations.txt");
	ofstream out_f7("transportations.txt");

	boost::archive::text_oarchive out_arch1(out_f1);
	boost::archive::text_oarchive out_arch2(out_f2);
	boost::archive::text_oarchive out_arch3(out_f3);
	boost::archive::text_oarchive out_arch4(out_f4);
	boost::archive::text_oarchive out_arch5(out_f5);
	boost::archive::text_oarchive out_arch6(out_f6);
	boost::archive::text_oarchive out_arch7(out_f7);

	save1(out_arch1);
	save2(out_arch2);
	save3(out_arch3);
	save4(out_arch4);
	save5(out_arch5);
	save6(out_arch6);
	save7(out_arch7);

	out_f1.close();
	out_f2.close();
	out_f3.close();
	out_f4.close();
	out_f5.close();
	out_f6.close();
	out_f7.close();
}

void Database::loadData() {
	ifstream in_f1("particulars.txt");
	ifstream in_f2("commercials.txt");
	ifstream in_f3("admins.txt");
	ifstream in_f4("packages.txt");
	ifstream in_f5("destinations.txt");
	ifstream in_f6("accomodations.txt");
	ifstream in_f7("transportations.txt");

	if (in_f1) {
		boost::archive::text_iarchive in_arch1(in_f1);
		load1(in_arch1);
	}
	if (in_f2) {
		boost::archive::text_iarchive in_arch2(in_f2);
		load2(in_arch2);
	}
	if (in_f3) {
		boost::archive::text_iarchive in_arch3(in_f3);
		load3(in_arch3);
	}
	if (in_f4) {
		boost::archive::text_iarchive in_arch4(in_f4);
		load4(in_arch4);
	}
	if (in_f5) {
		boost::archive::text_iarchive in_arch5(in_f5);
		load5(in_arch5);
	}
	if (in_f6) {
		boost::archive::text_iarchive in_arch6(in_f6);
		load6(in_arch6);
	}
	if (in_f7) {
		boost::archive::text_iarchive in_arch7(in_f7);
		load7(in_arch7);
	}

	in_f1.close();
	in_f2.close();
	in_f3.close();
	in_f4.close();
	in_f5.close();
	in_f6.close();
	in_f7.close();
}

/**/
bool ascendingNameP(Particular u1, Particular u2) {
	return u1.getName() < u2.getName();
}

bool descendingNameP(Particular u1, Particular u2) {
	return u1.getName() > u2.getName();
}

bool ascendingNameC(Commercial u1, Commercial u2) {
	return u1.getName() < u2.getName();
}

bool descendingNameC(Commercial u1, Commercial u2) {
	return u1.getName() > u2.getName();
}

/**/

void Database::addParticular(Particular p) {
	part.push_back(p);
}

vector<Particular> Database::getParticular() const {
	return part;
}

void Database::addCommercial(Commercial c) {
	comme.push_back(c);
}

vector<Commercial> Database::getCommercial() const {
	return comme;
}


void Database::addPromotion(unsigned int opt, double pro) {
	vector<Trip> part;
	for (unsigned int i = 0; i < packages.size(); i++)
		if (!packages[i].isPromotional())
			part.push_back(packages[i]);

	part[opt].setPromotion(pro);

	packages = part;
}

void Database::addTrip(const Trip& trip) {
	packages.push_back(trip);
}

void Database::addTripToUser(int mode, int pos, const Trip& t) {
	if (mode == 1)
		part[pos].addTrip(t);
	else
		comme[pos].addTrip(t);
}

void Database::addAdmin(const Admin& admin) {
	admins.push_back(admin);
}

void Database::addDestination(const string& s) {
	destinations.push_back(s);
}

void Database::addAccomodation(const string& s, const Accomodation& a) {
	accomodations[s].push_back(a);
}

void Database::removeParticular(const Particular& p) {
	for (size_t i = 0; i < part.size(); i++)
		if (part[i] == p)
			part.erase(part.begin() + i);
}

void Database::removeParticular(int num) {

	part.erase(part.begin() + num);

}

void Database::removeParticular(const string& s) {
	for (size_t i = 0; i < part.size(); i++)
		if (part[i].getName() == s)
			part.erase(part.begin() + i);
}

void Database::removeCommercial(const Commercial& c) {
	for (size_t i = 0; i < comme.size(); i++)
		if (comme[i] == c)
			comme.erase(comme.begin() + i);
}

void Database::removeCommercial(int num) {
	comme.erase(comme.begin() + num);
}

void Database::removeCommercial(const string& s) {
	for (size_t i = 0; i < comme.size(); i++)
		if (comme[i].getName() == s)
			comme.erase(comme.begin() + i);
}




void Database::sortCostumersByName(int mode, int type) {

	if (type) {
		if (mode)
			sort(comme.begin(), comme.end(), descendingNameC);
		else
			sort(comme.begin(), comme.end(), ascendingNameC);
	} else {
		if (mode)
			sort(part.begin(), part.end(), descendingNameP);
		else
			sort(part.begin(), part.end(), ascendingNameP);
	}
}


vector<Admin> Database::getAdmins() const {
	return admins;
}

vector<Trip> Database::getPackages() const {
	return packages;
}

vector<string> Database::getDestinations() const {
	return destinations;
}

map<string, vector<Accomodation> > Database::getAccomodations() const {
	return accomodations;
}

vector<Particular> Database::particularsByDestination(
		string destination) const {

	vector<Particular> vec;

	for (size_t i = 0; i < part.size(); i++)
		if (part[i].hasGoneTo(destination) != -1)
			vec.push_back(part[i]);

	return vec;
}

vector<Commercial> Database::commercialsByDestination(
		string destination) const {

	vector<Commercial> vec;

	for (size_t i = 0; i < comme.size(); i++)
		if (comme[i].hasGoneTo(destination) != -1)
			vec.push_back(comme[i]);

	return vec;
}

void Database::clearDatabase(int mode) {
	switch (mode) {
	case 1:
		part.clear();
		break;
	case 2:
		comme.clear();
		break;
	case 3:
		packages.clear();
		break;
	case 4:
		destinations.clear();
		break;
	case 5:
		accomodations.clear();
		break;
	default:
		part.clear();
		comme.clear();
		packages.clear();
		destinations.clear();
		accomodations.clear();
		admins.clear();
		transp.clear();
	}
}

void Database::setTrip(Trip tdest, Trip tsource) {

	for (unsigned int i = 0; i < packages.size(); i++) {
		if ((packages[i].getOrigin() == tsource.getOrigin())
				&& (packages[i].getPrice() == tsource.getPrice())
				&& (packages[i].getAccomodation().getPrice()
						== tsource.getAccomodation().getPrice())) {

			packages[i] = tdest;
			cout << endl << endl << i << endl << endl;
			cout << packages[i].isPromotional();
			system("Pause");

			break;

		}

		cout << tdest.isPromotional();

		system("Pause");

	}

}

void Database::addTransportation(const Transportation& t) {
	transp.push_back(t);
}

vector<Transportation> Database::getTransportations() const {
	return transp;
}
