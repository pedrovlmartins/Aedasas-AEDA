#ifndef TRIP_H_
#define TRIP_H_

#include<string>
#include <stdio.h>
#include <time.h>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include "Exception.h"

using namespace std;

/**
 *Classe Transportation, a responsavel por armazenar a informacao de um transporte. Por
* transporte entende-se o meio escolhido pelo cliente para fazer a viagem. Este transporte
 *pode ser por aviao (plane), por barco (boat), por camioneta (bus) ou por comboio (train).
 */

class Transportation {
	double distance;
	double price;
	unsigned int peopleNumber;
	string type;
	bool firstClass;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & distance & price & peopleNumber & type & firstClass;
	}

public:

	/** Construtor da classe Transportation.
	 *
	 */
	Transportation(unsigned int dist = 0, string transType = "",
			unsigned int num = 0, bool firstC = false);

	/** Devolve a distância total que o transporte vai percorrer ata ao destino.
		 *
		 */
		double getDistance() const;
		/** Devolve o preco total da viagem, calculado a partir de equacoes definidas
		 *pela propria agencia.
		*/
		double getPrice() const;
		/** Devolve o numero de pessoas que farao a viagem.
		 *
		 */
		unsigned int getPeopleNumber() const;
		/** Devolve o tipo de transporte (aviao, barco, camioneta ou comboio).
		 *
		 */
		string getType() const;
		/** Devolve o estatuto da viagem (true = classe alta, false = classe economica).
		 *	Viagens de classe alta tem custos mais elevados.
		 */
		bool isFirstClass() const;

		/** Atribui o valor passado como argumento a distância a percorrer.
		 *
		 */
		void setDistance(unsigned int);

		/** Atribui um preco ao transporte. Este set a usado para definir precos promocionais,
		 *
		* que nao nao calculados usando as formulas definidas pela agencia.
		*/
		void setPrice(unsigned int);

		/** Atribui o valor passado como argumento ao numero de pessoas que farao a viagem.
		 *
		 */
		void setPeopleNumber(unsigned int);

		/** Atribui o valor passado como argumento ao tipo de transporte a utilizar.
		 *
		 */
		void setType(string);

		/** Atribui o booleano passado como argumento a definicao da classe do transporte.
		 *
		 */
		void setClass(bool);

		/** Faz reset ao preco apos mudar algum parametro
		 *
		 */
		void resetPrice();
};

/**
* Classe Accomodation, vai armazenar a informacao relativa a uma hospedagem. Esta hospedagem
 *inclui o preco, o numero total de pessoas que vai albergar bem como o tipo.
 */
class Accomodation {
	double price;
	unsigned int peopleNumber;
	string type;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & price & peopleNumber & type;
	}

public:

	/** Construtor da classe Accomodation.
	 *
	 */
	Accomodation(string localType = "", unsigned int num = 0, double pri = 0);

	/** Devolve o preco da hospedagem.
	 *
	 */
	unsigned int getPrice() const;

	/** Devolve o numero de pessoas que irao fazer parte da mesma hospedagem.
	 *
	 */
	unsigned int getPeopleNumber() const;

	/** Devolve o tipo de hospedagem. Podera ser um hotel, um motel, uma casa alugada
	 *
	 */
	string getType() const;

	/** Atribui o custo da hospedagem, passado como argumento.
	* Este set a usado aquando de hospedagens promocionais.
	*/
	void setPrice(unsigned int);

	/** Atribui o numero de pessoas aquele passado como argumento.
	 *
	 */
	void setPeopleNumber(unsigned int);

	/** Atribui um tipo de hospedagem, passado como argumento
	 *
	 */
	void setType(string);
};

/**
 *Classe Date, a uma classe genarica de armazenamento e manipulacao de datas simples,
 *com dia, mes e ano. Dado que a base de uma agencia de viagens a orientada atravas
 *de datas, toda a restante implementacao faz uso constante desta classe.
 */

class Date {
protected:
	unsigned int day;
	unsigned int month;
	unsigned int year;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & day & month & year;
	}

public:
	Date();
		/** Construtor parametrizado da classe Date.
		 * Atribui uma data especifica, com valores passados como argumentos.
		  */
		Date(unsigned int, unsigned int, unsigned int);

		/** Devolve o dia.
		 *
		 */
		unsigned int getDay() const;
		/** Devolve o mes.
		 *
		 */
		unsigned int getMonth() const;
		/** Devolve o ano.
		 *
		 */
		unsigned int getYear() const;

		/** Atribui o dia passado como argumento.
		 *
		 */
		void setDay(unsigned int);
		/** Atribui o mes passado como argumento.
		 *
		 */
		void setMonth(unsigned int);
		/** Atribui o ano passado como argumento.
		 *
		 */
		void setYear(unsigned int);

		/** Overload do operador ==, que verifica se duas datas sao iguais.
		 *
		 */
		bool operator==(const Date&);
		/** Overload do operador >, que verifica se uma data ocorreu a mais tempo do que
		* outra passada como argumento.
		*/
		bool operator>(const Date&);
		/** Overload do operador <, que verifica se uma data ocorreu a menos tempo do que
		* outra passada como argumento.
		*/
		bool operator<(const Date&);
		/** Overload do operador de soma (+). Este certifica que, ao somar um inteiro passado
		* como argumento, devolve uma data valida.
		*/
		Date operator+(int);
		/** Overload do operador de igualdade. Devolve uma referencia para o objecto,
		* o que permite mais operacoes sobre esse objecto.
		*/
		Date &operator=(const Date &dt);

		/** Overload do operador <<, certificando-se de fazer display da data no
		* formato DD/MM/YYYY.
		*/
		friend ostream& operator <<(ostream&, const Date&);
};

/**
 *Classe Trip, a a classe principal que armazena um pacote de viagens completo, sendo este
 *constituido por uma hospedagem, um meio de transporte, uma data correspondente e um preco
 *total, calculado a partir dos restantes servicos.
 */
class Trip {
	string origin;
	string destination;
	int duration;
	int numPeople;
	double totalPrice;
	bool promotion;
	Date init_dt;
	Date end_dt;
	Accomodation ac;
	Transportation tp;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & totalPrice & origin & destination & duration & promotion
				& init_dt & end_dt & ac & tp;
	}

public:
	/** Construtor da classe Trip.
		 *
		 */
		Trip(const Date &dt = Date(), const Accomodation &acco = Accomodation(),
				const Transportation &transp = Transportation(), string ori = "",
				string dest = " ", int dur = 0, int num = 0);

		/** Devolve a origem da viagem.
		 *
		 */
		string getOrigin() const;
		/** Devolve o destino da viagem.
		 *
		 */
		string getDestination() const;
		/** Devolve a duracao da viagem.
		 *
		 */
		int getDuration() const;
		/** Devolve o numero de pessoas que vao participar na viagem.
		 *
		 */
		int getNumPeople() const;
		/** Devolve o preco total da viagem.
		 *
		 */
		unsigned int getPrice() const;
		/** Devolve a data a que a viagem se inicia.
		 *
		 */
		Date getInitialDate() const;
		/** Devolve a data a que a viagem termina.
		 *
		 */
		Date getEndDate() const;
		/** Devolve a hospedagem relativa a este pacote.
		 *
		 */
		Accomodation getAccomodation() const;
		/** Devolve o transporte relativo a este pacote.
		 *
		 */
		Transportation getTransportation() const;

		/** Atribui o valor passado como argumento a origem.
		 *
		 */
		void setOrigin(const string &);
		/** Atribui o valor passado como argumento ao destino.
		 *
		 */
		void setDestination(const string &);
		/** Atribui a duracao, passada como argumento.
		 * Actualiza tambam a data final da viagem.
		 */
		void setDuration(int);
		/** Atribui uma data inicial, passada como argumento.
		 *
		 */
		void setInitialDate(const Date &date);
		/** Calcula o novo preco do pacote, apos actualizacao da hospedagem passada como argumento.
		 *
		 */
		void setAccomodation(const Accomodation &);
		/** Calcula o novo preco do pacote, apos actualizacao do transporte passado como argumento.
		 *
		 */
		void setTransportation(const Transportation &);
		/** Aplica uma promocao, a partir do desconto passado como argumento.
		 *
		 */
		void setPromotion(double);
		/** Atribui o preco total, por meio de actualizacao
		 *
		 */
		void setPrice();
		/** Atribui o numero de pessoas que vao participar na viagem, passado como argumento.
		 *
		 */
		void setNumPeople(int);

		/**
		 * Faz um reset ao preco
		 */
		void resetPrice();

		/*
		 * Faz um reset ao preco total com um valor a multiplicar
		 */
		void setPriceVar(int);
		/** Verifica se o pacote em questao a promocional ou nao.
		 *
		 */
		bool isPromotional() const;
		/** Verifica a existencia de transporte para este pacote. Devolve falso caso este nao exista.
		 *
		 */
		bool hasTransportation() const;
		/** Verifica a existencia de hospedagem para este pacote. Caso nao exista, devolve falso.
		 *
		 */
		bool hasAccomodation() const;

		/**
		 * Faz overload do operador ==, retorna um booleano e recebe uma Trip.
		 */
		bool operator == (const Trip &);


};

#endif /* TRIP_H_ */
