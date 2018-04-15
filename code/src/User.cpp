#include "User.h"
#include "Trip.h"
#include <ctype.h>

////////////////////////////////////////////////////////
////////* Implementa��o dos m�todos de User *//////////
//////////////////////////////////////////////////////

// Inicializa��o da vari�vel est�tica numOfUsers, que conta o
// n�mero total de utilizadores na aplica��o.
int User::numOfUsers = 0;

// M�todo est�tico que devolve o n�mero de utilizadores na aplica��o.
int User::getNumOfUsers() {
	return numOfUsers;
}

// Construtor da classe abstracta User.
User::User(string login, string password) {
	this->login = login;
	this->password = password;
	numOfUsers++; // Aumenta o n�mero de utilizadores no registo,
	regiNumber = numOfUsers; // n�mero esse que lhe ser� atribuido.
}

// Devolve o n�mero de registo desse utilizador.
int User::getNumber() const {
	return regiNumber;
}

// Devolve o login do utilizador.
string User::getLogin() const {
	return login;
}

// Devolve a password do utilizador.
string User::getPassword() const {
	return password;
}

// Este m�todo muda os dados de identifica��o do utilizador para aqueles passados
// como argumentos, verificando antes se estes s�o diferentes dos actuais.
void User::changeLogin(string newLogin, string newPassword) {
	if ((newLogin == login && newPassword == password)
			|| (newLogin == "" || newPassword == ""))
		throw InvalidLogin();
	else {
		login = newLogin;
		password = newPassword;
	}
}

////////////////////////////////////////////////////////
//////* Implementa��o dos m�todos de Costumer *////////
//////////////////////////////////////////////////////

// Construtor da classe abstracta Costumer.
Costumer::Costumer(string login, string password, string name, string email,
		string address, string zipCode, string phoneNumber, string country) :
		User(login, password) {
	this->name = name;
	this->email = email;
	this->address = address;
	this->zipCode = zipCode;
	this->phoneNumber = phoneNumber;
	this->country = country;
}

// Devolve o nome do cliente.
string Costumer::getName() const {
	return name;
}

// Devolve o e-mail do cliente.
string Costumer::getEmail() const {
	return email;
}

// Devolve a morada do cliente.
string Costumer::getAddress() const {
	return address;
}

// Devolve o c�digo postal do cliente.
string Costumer::getZipCode() const {
	return zipCode;
}

// Devolve o n�mero de telefone/telem�vel do cliente.
string Costumer::getPhoneNumber() const {
	return phoneNumber;
}

// Devolve o pa�s do cliente.
string Costumer::getCountry() const {
	return country;
}

// Atribui uma nova morada, passada como argumento.
void Costumer::setAddress(string address) {
	this->address = address;
}

// Atribui um novo e-mail, passado como argumento.
void Costumer::setEmail(string email) {
	size_t found;
	found = email.find("@");
	if (found != string::npos)
		this->email = email;
	else
		throw InvalidEmail();
}

// Atribui um novo nome, passado como argumento.
void Costumer::setName(string name) {
	for (size_t i = 0; i < name.size(); i++)
		if (isdigit(name[i]))
			throw InvalidName();

	this->name = name;
}

// Atribui um novo c�digo postal, passado como argumento.
void Costumer::setZipCode(string zipCode) {
	for (size_t i = 0; i < zipCode.size(); i++)
		if (isalpha(zipCode[i]))
			throw InvalidZipCode();
	this->zipCode = zipCode;
}

// Atribui um novo pa�s, passado como argumento.
void Costumer::setCountry(string country) {
	for (size_t i = 0; i < country.size(); i++)
		if (isdigit(country[i]))
			throw InvalidCountry();

	this->country = country;
}

// Atribui um novo n�mero de telefone/telem�vel, passado como argumento.
void Costumer::setPhoneNumber(string phoneNumber) {
	for (size_t i = 0; i < phoneNumber.size(); i++)
		if (isalpha(phoneNumber[i]) || phoneNumber.size() != 9)
			throw InvalidPhoneNumber();

	this->phoneNumber = phoneNumber;
}

// M�todo que adiciona uma viagem (Trip) ao vector de viagens j� realizadas pelo
// cliente. Esta fun��o � sempre chamada quando o cliente faz alguma viagem, por
// forma a que este vector esteja sempre actualizado.
void Costumer::addTrip(const Trip & trip) {
	for(size_t i = 0 ; i < history.size() ; i++)
		if(history[i] == trip)
			throw RepeatedTrip();

	history.push_back(trip);
}

// Fun��o que, fazendo uso do m�todo de pesquisa sequencial, verifica se o cliente
// j� visitou o destino passado como argumento. Caso a resposta seja afirmativa,
// a fun��o devolve o �ndice no vector dessa viagem. Caso contr�rio, devolve -1.
int Costumer::hasGoneTo(string destination) const {
	for (size_t i = 0; i < history.size(); i++)
		if (history[i].getDestination() == destination)
			return i; // Encontrou. Devolve o �ndice dessa viagem no vector history.

	return -1; // N�o encontrou.
}

// Fun��o que devolve uma viagem (Trip) relativa ao destino passado como argumento.
// Caso esse destino nunca tenha sido parte de nenhuma viagem do cliente, lan�a uma
// excep��o do tipo TripNotFound.
Trip Costumer::getTrip(string destination) const {

	int index = hasGoneTo(destination); // hasGoneTo verifica se destino � v�lido.
	// if (index == -1)
	// throw TripNotFound(destination);
	return history[index];
}

// Devolve o vector de viagens feitas pelo cliente.
vector<Trip> Costumer::getHistory() const {
	return history;
}

////////////////////////////////////////////////////////
/////* Implementa��o dos m�todos de Particular *///////
//////////////////////////////////////////////////////

// Construtor da classe Particular.
Particular::Particular(const Date &birthDate, string login, string password,
		string name, string email, string address, string zipCode,
		string phoneNumber, string country) :
		Costumer(login, password, name, email, address, zipCode, phoneNumber,
				country) {
	this->birthDate = birthDate;

	Date dt;
	int y = dt.getYear() - birthDate.getYear();

	if (dt.getMonth() < birthDate.getMonth()
			|| (dt.getMonth() == birthDate.getMonth()
					&& dt.getDay() < birthDate.getDay()))
		y--;

	this->age = y;
}

// Devolve a idade do cliente particular.
unsigned int Particular::getAge() const {
	return age;
}

// Devolve a data de nascimento (Date) do cliente particular.
Date Particular::getBirthDate() const {
	return birthDate;
}

// Atribui ao cliente particular a idade passada como argumento.
void Particular::setAge(unsigned int age) {
	if (age < 0 || age > 100)
		throw InvalidAge(age);

	this->age = age;
}

// Atribui ao cliente particular a data de nascimento passada como argumento.
void Particular::setDate(const Date & birthDate) {
	this->birthDate = birthDate;

	if (birthDate.getDay() < 0
			|| (birthDate.getMonth() == 2 && birthDate.getDay() > 28)
			|| ((birthDate.getMonth() == 4 || birthDate.getMonth() == 6
					|| birthDate.getMonth() == 9 || birthDate.getMonth() == 11)
					&& birthDate.getDay() > 30)
			|| ((birthDate.getMonth() == 1 || birthDate.getMonth() == 3
					|| birthDate.getMonth() == 5 || birthDate.getMonth() == 7
					|| birthDate.getMonth() == 8 || birthDate.getMonth() == 10
					|| birthDate.getMonth() == 12) && birthDate.getDay() > 31)
			|| birthDate.getYear() < 1910 || birthDate.getYear() > 2011)
		throw InvalidDate();

	Date dt;
	int y = dt.getYear() - birthDate.getYear();

	if (dt.getMonth() < birthDate.getMonth()
			|| (dt.getMonth() == birthDate.getMonth()
					&& dt.getDay() < birthDate.getDay()))
		y--;

	this->age = y;
}


// Fun��o que faz uso do overload do operator == para verificar se dois clientes
// particulares s�o, ou n�o, o mesmo.
bool Particular::operator==(const Particular& p) {
	return (name == p.getName() && email == p.getEmail()
			&& phoneNumber == p.getPhoneNumber() && age == p.getAge()
			&& address == p.getAddress() && zipCode == p.getZipCode()
			&& country == p.getCountry() && birthDate == p.getBirthDate());
}

////////////////////////////////////////////////////////
/////* Implementa��o dos m�todos de Commercial *///////
//////////////////////////////////////////////////////

// Construtor da classe Commercial.
Commercial::Commercial(unsigned int numPeople, string login, string password,
		string name, string email, string address, string zipCode,
		string phoneNumber, string country) :
		Costumer(login, password, name, email, address, zipCode, phoneNumber,
				country) {
	this->numPeople = numPeople;
}

// Devolve o n�mero de pessoas que constituem a entidade comercial.
unsigned int Commercial::getNumPeople() const {
	return numPeople;
}

// Atribui � entidade comercial existente o n�mero de pessoas passado como argumento.
void Commercial::setNumPeople(unsigned int numPeople) {
	if(numPeople < 0 || numPeople > 500)
		throw InvalidNumPeople();

	this->numPeople = numPeople;
}

// Fun��o que faz uso do overload do operator == para verificar se dois clientes
// comerciais s�o, ou n�o, o mesmo.
bool Commercial::operator==(const Commercial& c) {
	return (name == c.getName() && email == c.getEmail()
			&& phoneNumber == c.getPhoneNumber() && address == c.getAddress()
			&& zipCode == c.getZipCode() && country == c.getCountry()
			&& numPeople == c.getNumPeople());
}

////////////////////////////////////////////////////////
////////* Implementa��o dos m�todos de Admin */////////
//////////////////////////////////////////////////////

// Construtor da classe Admin.
Admin::Admin(string login, string password) :
		User(login, password) {
}

string Admin::getTypeOfUser() const {
	return "Admin";
}

// M�todo que permite reconhecer, aquando da utiliza��o de polimorfismo para
// manipular objectos do tipo Costumer, um cliente particular, devolvendo uma
// string que o identifica como tal.
string Particular::getTypeOfUser() const {
	return "Particular";

}

// M�todo que permite reconhecer, aquando da utiliza��o de polimorfismo para
// manipular objectos do tipo Costumer, um cliente comercial, devolvendo uma
// string que o identifica como tal.
string Commercial::getTypeOfUser() const {
	return "Commercial";

}

