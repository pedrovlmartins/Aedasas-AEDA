#include "Trip.h"
////////////////////////////////////////////////////////
////* Implementa��o dos m�todos de Transportation *////
//////////////////////////////////////////////////////

// Construtor da classe Transportation.
Transportation::Transportation(unsigned int dist, string typeTrans,
		unsigned int num, bool firstC) {
	distance = dist;
	type = typeTrans;
	peopleNumber = num;
	firstClass = firstC;

	// Esta sequ�ncia de ifs vai determinar o pre�o para cada tipo de transporte, com base
	// em crit�rios definidos pela ag�ncia, calculados a partir da dist�ncia e do n�mero
	// de pessoas que far�o a viagem.
	if (type == "plane")

		if (firstClass)
			price = (40 + 150 + 25 * (distance / 100)) * num * 2;
		else
			price = (30 + 120 + 25 * (distance / 100)) * num;

	else if (type == "boat")

		if (firstClass)
			price = (300 + 20 * (distance / 100)) * num * 3;
		else
			price = (250 + 15 * (distance / 100)) * num;

	else if (type == "train")
		price = (distance / 8.5) * num;

	else if (type == "bus")
		price = (7 + 1.5 * (distance / 10)) * num;

	else
		price = 0;
}

// Devolve a dist�ncia total que o transporte vai percorrer at� ao destino.
double Transportation::getDistance() const {
	return distance;
}

// Devolve o pre�o total da viagem, calculado a partir de equa��es definidas
// pela pr�pria ag�ncia.
double Transportation::getPrice() const {
	return price;
}

void Transportation::resetPrice() {
	unsigned int num = peopleNumber;

	if (type == "plane")

		if (firstClass)
			price = (40 + 150 + 25 * (distance / 100)) * num * 2;
		else
			price = (30 + 120 + 25 * (distance / 100)) * num;

	else if (type == "boat")

		if (firstClass)
			price = (300 + 20 * (distance / 100)) * num * 3;
		else
			price = (250 + 15 * (distance / 100)) * num;

	else if (type == "train")
		price = (distance / 8.5) * num;

	else if (type == "bus")
		price = (7 + 1.5 * (distance / 10)) * num;

	else
		price = 0;
}

// Devolve o n�mero de pessoas que far�o a viagem.
unsigned int Transportation::getPeopleNumber() const {
	return peopleNumber;
}

// Devolve o tipo de transporte (avi�o, barco, camioneta ou comboio).
string Transportation::getType() const {
	return type;
}

// Devolve o estatuto da viagem (true = classe alta, false = classe econ�mica).
// Viagens de classe alta t�m custos mais elevados.
bool Transportation::isFirstClass() const {
	return firstClass;
}

// Atribui o valor passado como argumento � dist�ncia a percorrer.
void Transportation::setDistance(unsigned int dist) {
	distance = dist;
}

// Atribui um pre�o ao transporte. Este set � usado para definir pre�os promocionais,
// que n�o n�o calculados usando as f�rmulas definidas pela ag�ncia.
void Transportation::setPrice(unsigned int cost) {
	price = cost;
}

// Atribui o valor passado como argumento ao n�mero de pessoas que far�o a viagem.
void Transportation::setPeopleNumber(unsigned int num) {
	if (num < 0 || num > 500)
		throw InvalidNumPeople();
	peopleNumber = num;
}

// Atribui o valor passado como argumento ao tipo de transporte a utilizar.
void Transportation::setType(string transType) {
	if (transType != "plane" && transType != "boat" && transType != "bus"
			&& transType != "train")
		throw InvalidTransportationType();

	type = transType;
}

// Atribui o booleano passado como argumento � defini��o da classe do transporte.
void Transportation::setClass(bool first) {
	firstClass = first;
}

////////////////////////////////////////////////////////
/////* Implementa��o dos m�todos de Accomodation */////
//////////////////////////////////////////////////////

// Construtor da classe Accomodation.
Accomodation::Accomodation(string localType, unsigned int num, double pri) {
	type = localType;
	peopleNumber = num;
	price = pri * peopleNumber;
}

// Devolve o pre�o da hospedagem.
unsigned int Accomodation::getPrice() const {
	return price;
}

// Devolve o n�mero de pessoas que ir�o fazer parte da mesma hospedagem.
unsigned int Accomodation::getPeopleNumber() const {
	return peopleNumber;
}

// Devolve o tipo de hospedagem. Poder� ser um hotel, um motel, uma casa alugada
string Accomodation::getType() const {
	return type;
}

// Atribui o custo da hospedagem, passado como argumento.
// Este set � usado aquando de hospedagens promocionais.
void Accomodation::setPrice(unsigned int cost) {
	price = cost * peopleNumber;
}

// Atribui o n�mero de pessoas �quele passado como argumento.
void Accomodation::setPeopleNumber(unsigned int num) {
	if (num < 0 || num > 500)
		throw InvalidNumPeople();
	peopleNumber = num;
}

// Atribui um tipo de hospedagem, passado como argumento.
void Accomodation::setType(string localType) {
	if (localType != "hotel" && localType != "aparthotel"
			&& localType != "hostel")
		throw InvalidAccomodationType(localType);

	type = localType;
}

////////////////////////////////////////////////////////
/////////* Implementa��o dos m�todos de Date */////////
//////////////////////////////////////////////////////

// Construtor sem par�metros da classe Date.
Date::Date() {
	time_t rawtime; // Cria uma vari�vel do tipo time_t.
	struct tm * timeinfo; // Estrutura alocada estaticamente com a informa��o do tempo.

	time(&rawtime);
	timeinfo = localtime(&rawtime); // Guarda no pointer a informa��o de rawtime.

	day = timeinfo->tm_mday; // tm_day � apontado por timeinfo: corresponde ao dia.
	month = timeinfo->tm_mon + 1; // tm_mon � apontado por timeinfo: corresponde ao mes.
	year = timeinfo->tm_year + 1900; // tm_year � apontado por timeinfo: corresponde ao ano.
}

// Construtor parametrizado da classe Date.
// Atribui uma data espec�fica, com valores passados como argumentos.
Date::Date(unsigned int d, unsigned int m, unsigned int y) {
	day = d;
	month = m;
	year = y;
}

// Devolve o dia.
unsigned int Date::getDay() const {
	return day;
}

// Devolve o m�s.
unsigned int Date::getMonth() const {
	return month;
}

// Devolve o ano.
unsigned int Date::getYear() const {
	return year;
}

// Atribui o dia passado como argumento
void Date::setDay(unsigned int day) {
	if (day < 0 || day > 31)
		throw InvalidDay();
	this->day = day;
}

// Atribui o m�s passado como argumento.
void Date::setMonth(unsigned int month) {
	if (month < 0 || month > 12)
		throw InvalidMonth();
	this->month = month;
}

// Atribui o ano passado como argumento.
void Date::setYear(unsigned int year) {
	if (year < 1910 || year > 2011)
		throw InvalidYear();
	this->year = year;
}

// Overload do operador ==, que verifica se duas datas s�o iguais.
bool Date::operator==(const Date& d1) {
	return (day == d1.getDay() && month == d1.getMonth() && year == d1.getYear());
}

// Overload do operador >, que verifica se uma data ocorreu � mais tempo do que
// outra passada como argumento.
bool Date::operator>(const Date& d1) {
	return (year > d1.getYear()
			|| (year == d1.getYear() && month > d1.getMonth())
			|| (year == d1.getYear() && month == d1.getMonth()
					&& day > d1.getDay()));
}

// Overload do operador <, que verifica se uma data ocorreu � menos tempo do que
// outra passada como argumento.
bool Date::operator<(const Date& d1) {
	return (year < d1.getYear()
			|| (year == d1.getYear() && month < d1.getMonth())
			|| (year == d1.getYear() && month == d1.getMonth()
					&& day < d1.getDay()));
}

// Overload do operador de soma (+). Este certifica que, ao somar um inteiro passado
// como argumento, devolve uma data v�lida.
Date Date::operator+(int n) {

	Date res = (*this);

	res.day += n; // Soma o valor ao dia.

	// Condi��o verifica a situa��o dos meses com 31 dias.
	if (res.month == 1 || res.month == 3 || res.month == 5 || res.month == 7
			|| res.month == 8 || res.month == 10) {
		if (res.day > 31) { // S� caso a soma exceda os 31 dias.
			res.day -= 31; // Acerta o dia.
			res.month++; // Incrementa o m�s.
			return res; // Devolve a data, j� validada.
		}
	}

	// Faz a verifica��o para as situa��es em que h� necessidade de mudar de ano.
	else if (res.month == 12) {
		if (res.day > 31) { // Muda apenas caso tenhamos a vari�vel day acima de 31.
			res.day -= 31;
			res.month = 1;
			res.year++;
			return res;
		}
	}

	// Caso espec�fico para o m�s de Fevereiro.
	else if (res.month == 2) {
		if (res.day > 28) {
			res.day -= 28;
			res.month++;
			return res;
		}
	}

	// Verifica para os meses com 30 dias.
	else if (res.month == 4 || res.month == 6 || res.month == 9
			|| res.month == 11) {
		if (day > 30) { // S� caso a soma exceda os 30 dias.
			res.day -= 30;
			res.month++;
			return res;
		}
	}

	return res;
}

// Overload do operador de igualdade. Devolve uma refer�ncia para o objecto,
// o que permite mais opera��es sobre esse objecto.
Date & Date::operator=(const Date &dt) {
	day = dt.getDay();
	month = dt.getMonth();
	year = dt.getYear();

	return (*this);
}

// Overload do operador <<, certificando-se de fazer display da data no
// formato DD/MM/YYYY.
ostream& operator <<(ostream& os, const Date& d) {
	os << left << d.getDay() << "/" << d.getMonth() << "/" << d.getYear();
	return os;
}
////////////////////////////////////////////////////////
/////////* Implementa��o dos m�todos de Trip */////////
//////////////////////////////////////////////////////

// Construtor da classe Trip.
Trip::Trip(const Date &dt, const Accomodation &acco,
		const Transportation &transp, string ori, string dest, int dur,
		int num) {
	init_dt = dt;
	tp = transp;
	ac = acco;
	numPeople = num;
	origin = ori;
	destination = dest;
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * dur; // Pre�o total.
	duration = dur;
	end_dt = init_dt + dur; // Faz uso do overload do operador + da classe Date.
	promotion = false;

	tp.setPeopleNumber(num);
	ac.setPeopleNumber(num);

}

// Devolve a origem da viagem.
string Trip::getOrigin() const {
	return origin;
}

// Devolve o destino da viagem.
string Trip::getDestination() const {
	return destination;
}

// Devolve a dura��o da viagem.
int Trip::getDuration() const {
	return duration;
}

// Devolve o n�mero de pessoas que v�o participar na viagem.
int Trip::getNumPeople() const {
	return numPeople;
}

// Devolve o pre�o total da viagem.
unsigned int Trip::getPrice() const {
	return totalPrice;
}

// Devolve a data a que a viagem se inicia.
Date Trip::getInitialDate() const {
	return init_dt;
}

// Devolve a data a que a viagem termina.
Date Trip::getEndDate() const {
	return end_dt;
}

// Devolve a hospedagem relativa a este pacote.
Accomodation Trip::getAccomodation() const {
	return ac;
}

// Devolve o transporte relativo a este pacote.
Transportation Trip::getTransportation() const {
	return tp;
}

// Atribui o valor passado como argumento � origem.
void Trip::setOrigin(const string &ori) {
	origin = ori;
}

// Atribui o valor passado como argumento ao destino.
void Trip::setDestination(const string &dest) {
	destination = dest;
}

// Atribui a dura��o, passada como argumento.
// Actualiza tamb�m a data final da viagem.
void Trip::setDuration(int dur) {
	duration = dur;
	end_dt = init_dt + dur; // Faz uso do overload do operador + da classe Date.
}

// Atribui uma data inicial, passada como argumento.
void Trip::setInitialDate(const Date &dt) {
	if (dt.getDay() < 0 || (dt.getMonth() == 2 && dt.getDay() > 28)
			|| ((dt.getMonth() == 4 || dt.getMonth() == 6 || dt.getMonth() == 9
					|| dt.getMonth() == 11) && dt.getDay() > 30)
			|| ((dt.getMonth() == 1 || dt.getMonth() == 3 || dt.getMonth() == 5
					|| dt.getMonth() == 7 || dt.getMonth() == 8
					|| dt.getMonth() == 10 || dt.getMonth() == 12)
					&& dt.getDay() > 31) || dt.getYear() < 1910
			|| dt.getYear() > 2011)
		throw InvalidDate();
	init_dt = dt;

	end_dt = init_dt + duration;
}

// Calcula o novo pre�o do pacote, ap�s actualiza��o da hospedagem passada como argumento.
void Trip::setAccomodation(const Accomodation &acco) {
	ac = acco;
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * duration;
}

// Calcula o novo pre�o do pacote, ap�s actualiza��o do transporte passado como argumento.
void Trip::setTransportation(const Transportation &transp) {
	tp = transp;
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * duration;
}

// Aplica uma promo��o, a partir do desconto passado como argumento.
void Trip::setPromotion(double discount) {
	if (discount < 0 || discount > 1)
		throw InvalidDiscount();
	promotion = true;
	totalPrice -= totalPrice * discount;
}

// Atribui o pre�o total, por meio de actualiza��o.
void Trip::setPrice() {
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * duration;
}

// Atribui o n�mero de pessoas que v�o participar na viagem, passado como argumento.
void Trip::setNumPeople(int n) {
	numPeople = n;
}

// Verifica se o pacote em quest�o � promocional ou n�o.
bool Trip::isPromotional() const {
	return promotion;
}

// Verifica a exist�ncia de transporte para este pacote. Devolve falso caso este n�o exista.
bool Trip::hasTransportation() const {
	return (!(!tp.getDistance() && tp.getType() == "" && !tp.getPeopleNumber()));
}

// Verifica a exist�ncia de hospedagem para este pacote. Caso n�o exista, devolve falso.
bool Trip::hasAccomodation() const {
	return (!(!ac.getPeopleNumber() && !ac.getPrice() && ac.getType() == ""));
}

void Trip::setPriceVar(int var) {
	totalPrice *= var;
}

bool Trip::operator ==(const Trip& t) {
	return (origin == t.getOrigin() && destination == t.getDestination()
			&& duration == t.getDuration() && totalPrice == t.getPrice()
			&& numPeople == t.getNumPeople() && promotion == t.isPromotional()
			&& init_dt == t.getInitialDate() && end_dt == t.getEndDate());
}
