#include "Trip.h"
////////////////////////////////////////////////////////
////* Implementação dos métodos de Transportation *////
//////////////////////////////////////////////////////

// Construtor da classe Transportation.
Transportation::Transportation(unsigned int dist, string typeTrans,
		unsigned int num, bool firstC) {
	distance = dist;
	type = typeTrans;
	peopleNumber = num;
	firstClass = firstC;

	// Esta sequência de ifs vai determinar o preço para cada tipo de transporte, com base
	// em critérios definidos pela agência, calculados a partir da distância e do número
	// de pessoas que farão a viagem.
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

// Devolve a distância total que o transporte vai percorrer até ao destino.
double Transportation::getDistance() const {
	return distance;
}

// Devolve o preço total da viagem, calculado a partir de equações definidas
// pela própria agência.
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

// Devolve o número de pessoas que farão a viagem.
unsigned int Transportation::getPeopleNumber() const {
	return peopleNumber;
}

// Devolve o tipo de transporte (avião, barco, camioneta ou comboio).
string Transportation::getType() const {
	return type;
}

// Devolve o estatuto da viagem (true = classe alta, false = classe económica).
// Viagens de classe alta têm custos mais elevados.
bool Transportation::isFirstClass() const {
	return firstClass;
}

// Atribui o valor passado como argumento à distância a percorrer.
void Transportation::setDistance(unsigned int dist) {
	distance = dist;
}

// Atribui um preço ao transporte. Este set é usado para definir preços promocionais,
// que não não calculados usando as fórmulas definidas pela agência.
void Transportation::setPrice(unsigned int cost) {
	price = cost;
}

// Atribui o valor passado como argumento ao número de pessoas que farão a viagem.
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

// Atribui o booleano passado como argumento à definição da classe do transporte.
void Transportation::setClass(bool first) {
	firstClass = first;
}

////////////////////////////////////////////////////////
/////* Implementação dos métodos de Accomodation */////
//////////////////////////////////////////////////////

// Construtor da classe Accomodation.
Accomodation::Accomodation(string localType, unsigned int num, double pri) {
	type = localType;
	peopleNumber = num;
	price = pri * peopleNumber;
}

// Devolve o preço da hospedagem.
unsigned int Accomodation::getPrice() const {
	return price;
}

// Devolve o número de pessoas que irão fazer parte da mesma hospedagem.
unsigned int Accomodation::getPeopleNumber() const {
	return peopleNumber;
}

// Devolve o tipo de hospedagem. Poderá ser um hotel, um motel, uma casa alugada
string Accomodation::getType() const {
	return type;
}

// Atribui o custo da hospedagem, passado como argumento.
// Este set é usado aquando de hospedagens promocionais.
void Accomodation::setPrice(unsigned int cost) {
	price = cost * peopleNumber;
}

// Atribui o número de pessoas àquele passado como argumento.
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
/////////* Implementação dos métodos de Date */////////
//////////////////////////////////////////////////////

// Construtor sem parâmetros da classe Date.
Date::Date() {
	time_t rawtime; // Cria uma variável do tipo time_t.
	struct tm * timeinfo; // Estrutura alocada estaticamente com a informação do tempo.

	time(&rawtime);
	timeinfo = localtime(&rawtime); // Guarda no pointer a informação de rawtime.

	day = timeinfo->tm_mday; // tm_day é apontado por timeinfo: corresponde ao dia.
	month = timeinfo->tm_mon + 1; // tm_mon é apontado por timeinfo: corresponde ao mes.
	year = timeinfo->tm_year + 1900; // tm_year é apontado por timeinfo: corresponde ao ano.
}

// Construtor parametrizado da classe Date.
// Atribui uma data específica, com valores passados como argumentos.
Date::Date(unsigned int d, unsigned int m, unsigned int y) {
	day = d;
	month = m;
	year = y;
}

// Devolve o dia.
unsigned int Date::getDay() const {
	return day;
}

// Devolve o mês.
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

// Atribui o mês passado como argumento.
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

// Overload do operador ==, que verifica se duas datas são iguais.
bool Date::operator==(const Date& d1) {
	return (day == d1.getDay() && month == d1.getMonth() && year == d1.getYear());
}

// Overload do operador >, que verifica se uma data ocorreu à mais tempo do que
// outra passada como argumento.
bool Date::operator>(const Date& d1) {
	return (year > d1.getYear()
			|| (year == d1.getYear() && month > d1.getMonth())
			|| (year == d1.getYear() && month == d1.getMonth()
					&& day > d1.getDay()));
}

// Overload do operador <, que verifica se uma data ocorreu à menos tempo do que
// outra passada como argumento.
bool Date::operator<(const Date& d1) {
	return (year < d1.getYear()
			|| (year == d1.getYear() && month < d1.getMonth())
			|| (year == d1.getYear() && month == d1.getMonth()
					&& day < d1.getDay()));
}

// Overload do operador de soma (+). Este certifica que, ao somar um inteiro passado
// como argumento, devolve uma data válida.
Date Date::operator+(int n) {

	Date res = (*this);

	res.day += n; // Soma o valor ao dia.

	// Condição verifica a situação dos meses com 31 dias.
	if (res.month == 1 || res.month == 3 || res.month == 5 || res.month == 7
			|| res.month == 8 || res.month == 10) {
		if (res.day > 31) { // Só caso a soma exceda os 31 dias.
			res.day -= 31; // Acerta o dia.
			res.month++; // Incrementa o mês.
			return res; // Devolve a data, já validada.
		}
	}

	// Faz a verificação para as situações em que há necessidade de mudar de ano.
	else if (res.month == 12) {
		if (res.day > 31) { // Muda apenas caso tenhamos a variável day acima de 31.
			res.day -= 31;
			res.month = 1;
			res.year++;
			return res;
		}
	}

	// Caso específico para o mês de Fevereiro.
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
		if (day > 30) { // Só caso a soma exceda os 30 dias.
			res.day -= 30;
			res.month++;
			return res;
		}
	}

	return res;
}

// Overload do operador de igualdade. Devolve uma referência para o objecto,
// o que permite mais operações sobre esse objecto.
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
/////////* Implementação dos métodos de Trip */////////
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
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * dur; // Preço total.
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

// Devolve a duração da viagem.
int Trip::getDuration() const {
	return duration;
}

// Devolve o número de pessoas que vão participar na viagem.
int Trip::getNumPeople() const {
	return numPeople;
}

// Devolve o preço total da viagem.
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

// Atribui o valor passado como argumento à origem.
void Trip::setOrigin(const string &ori) {
	origin = ori;
}

// Atribui o valor passado como argumento ao destino.
void Trip::setDestination(const string &dest) {
	destination = dest;
}

// Atribui a duração, passada como argumento.
// Actualiza também a data final da viagem.
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

// Calcula o novo preço do pacote, após actualização da hospedagem passada como argumento.
void Trip::setAccomodation(const Accomodation &acco) {
	ac = acco;
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * duration;
}

// Calcula o novo preço do pacote, após actualização do transporte passado como argumento.
void Trip::setTransportation(const Transportation &transp) {
	tp = transp;
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * duration;
}

// Aplica uma promoção, a partir do desconto passado como argumento.
void Trip::setPromotion(double discount) {
	if (discount < 0 || discount > 1)
		throw InvalidDiscount();
	promotion = true;
	totalPrice -= totalPrice * discount;
}

// Atribui o preço total, por meio de actualização.
void Trip::setPrice() {
	totalPrice = tp.getPrice() * 2 + ac.getPrice() * duration;
}

// Atribui o número de pessoas que vão participar na viagem, passado como argumento.
void Trip::setNumPeople(int n) {
	numPeople = n;
}

// Verifica se o pacote em questão é promocional ou não.
bool Trip::isPromotional() const {
	return promotion;
}

// Verifica a existência de transporte para este pacote. Devolve falso caso este não exista.
bool Trip::hasTransportation() const {
	return (!(!tp.getDistance() && tp.getType() == "" && !tp.getPeopleNumber()));
}

// Verifica a existência de hospedagem para este pacote. Caso não exista, devolve falso.
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
