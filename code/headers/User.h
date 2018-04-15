#ifndef USER_H_
#define USER_H_

#include <string>
#include <vector>
#include "Trip.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/assume_abstract.hpp>

using namespace std;

/**
 *Classe base: User.
 *Classe que contem a informacao basica de um utilizador generico.
 */


class User {
protected:
	static int numOfUsers;
	int regiNumber;
	string login;
	string password;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & numOfUsers & regiNumber & login & password;
	}

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(User)

public:
	/** Construtor da classe abstracta User.
		 *
		 */
		User() {
		}
		;
		User(string, string);

		//Metodos Get

		/** Metodo estatico que devolve o numero de utilizadores na aplicacao.
		 *
		 */
		static int getNumOfUsers();
		/** Devolve o numero de registo desse utilizador.
		 *
		 */
		int getNumber() const;
		/** Devolve o login do utilizador.
		 *
		 */
		string getLogin() const;
		/** Devolve a password do utilizador.
		 *
		 */
		string getPassword() const;

		/** Este metodo muda os dados de identificacao do utilizador para aqueles passados
		* como argumentos, verificando antes se estes sao diferentes dos actuais.
		*/
		void changeLogin(string, string);

		/**
		 * Costumer e uma classe abstracta.
		 */
		virtual string getTypeOfUser() const = 0;
};

/**
 *Classe derivada de User: Costumer.
 *Classe que contem a informacao generica de um cliente que pode usar os servicos oferecidos
 *pela agencia de viagens.
 */

class Costumer: public User {
protected:
	string name;
	string email;
	string phoneNumber;
	string address;
	string zipCode;
	string country;
	vector<Trip> history;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & boost::serialization::base_object<User>(*this);
		file & name & email & phoneNumber & address & zipCode & country & history;
	}

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(Costumer)

public:
	Costumer() {
	}
	;
	/** Construtor da classe abstracta Costumer.
	 *
	 */
	Costumer(string, string, string, string, string, string, string, string);

	// Metodos Get

	/** Devolve o nome do cliente.
	 *
	 */
	string getName() const;
	/** Devolve o e-mail do cliente.
	 *
	 */
	string getEmail() const;
	/** Devolve a morada do cliente.
	 *
	 */
	string getAddress() const;
	/** Devolve o codigo postal do cliente.
	 *
	 */
	string getZipCode() const;
	/** Devolve o numero de telefone/telemovel do cliente.
	 *
	 */
	string getPhoneNumber() const;
	/** Devolve o pais do cliente.
	 *
	 */
	string getCountry() const;

	// Metodos Set

	/** Atribui uma nova morada, passada como argumento.
	 *
	 */
	void setAddress(string);

	/** Atribui um novo e-mail, passado como argumento.
	 *
	 */
	void setEmail(string);
	/** Atribui um novo nome, passado como argumento.
	 *
	 */
	void setName(string);
	/** Atribui um novo codigo postal, passado como argumento.
	 *
	 */
	void setZipCode(string);
	/** Atribui um novo pais, passado como argumento.
	 *
	 */
	void setCountry(string);
	/** Atribui um novo numero de telefone/telemovel, passado como argumento.
	 *
	 */
	void setPhoneNumber(string);


	/** Metodo que adiciona uma viagem (Trip) ao vector de viagens ja realizadas pelo
	* cliente. Esta funcao e sempre chamada quando o cliente faz alguma viagem, por
	* forma a que este vector esteja sempre actualizado.
	 */
	void addTrip(const Trip &);

	/** Funcao que, fazendo uso do metodo de pesquisa sequencial, verifica se o cliente
	* ja visitou o destino passado como argumento. Caso a resposta seja afirmativa,
	* a funcao devolve o indice no vector dessa viagem. Caso contrario, devolve -1.
	 */
	Trip getTrip(string) const;

	/** Funcao que devolve uma viagem (Trip) relativa ao destino passado como argumento.
	* Caso esse destino nunca tenha sido parte de nenhuma viagem do cliente, lanca uma
	* excepcao do tipo TripNotFound.
	*/
	int hasGoneTo(string) const;

	/** Devolve o vector de viagens feitas pelo cliente.
	 *
	 */
	vector<Trip> getHistory() const;
	/** Devolve o vector de notas do cliente.
	 *
	 */
	string getTypeOfUser(){return "Costumer";}
};

/**
* Classe derivada de Costumer: Particular.
 *Classe que contem informacao especifica de um cliente particular, isto e,
 *de uma pessoa ou de uma entidade nao comercial.
 */

class Particular: public Costumer {
protected:
	unsigned int age;
	Date birthDate;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & boost::serialization::base_object<Costumer>(*this);
		file & age & birthDate;
	}

public:
	/** Construtor da classe Particular.
		 *
		 */
		Particular() {
		}
		;
		Particular(const Date &, string, string, string, string, string, string,
				string, string);

		// Metodos Get

		/** Devolve a idade do cliente particular.
		 *
		 */
		unsigned int getAge() const;
		/** Devolve a data de nascimento (Date) do cliente particular.
		 *
		 */
		Date getBirthDate() const;


		// Metodos Set

		/** Atribui ao cliente particular a idade passada como argumento.
		 *
		 */
		void setDate(const Date &);
		/** Atribui ao cliente particular a data de nascimento passada como argumento.
		 *
		 */
		void setAge(unsigned int);

		/**
		 * Devolve o tipo de utilizador, neste caso particular
		 */
		string getTypeOfUser() const;

		/** Metodo que faz uso do overload do operator == para verificar se dois clientes
		* particulares sao, ou nao, o mesmo.
		*/
		bool operator==(const Particular&);
};

/**
 *Classe derivada de Costumer: Commercial.
 *Classe que contem informacao especifica de um cliente comercial, isto e,
* de uma entidade comercial, tal como uma empresa ou uma companhia.
 */

class Commercial: public Costumer {
protected:
	unsigned int numPeople;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & boost::serialization::base_object<Costumer>(*this);
		file & numPeople;
	}

public:
	Commercial() {
		}
		;
		/** Construtor da classe Commercial.
		 *
		 */
		Commercial(unsigned int, string, string, string, string, string, string,
				string, string);

		/** Devolve o numero de pessoas que constituem a entidade comercial.
		 *
		 */
		unsigned int getNumPeople() const;
		/** Atribui a entidade comercial existente o numero de pessoas passado como argumento.
		 *
		 */
		void setNumPeople(unsigned int);

		/**
		 * Devolve o tipo de utilizador, neste caso comercial
		 */
		string getTypeOfUser() const;

		/** Metodo que faz uso do overload do operator == para verificar se dois clientes
		 * comerciais sao, ou nao, o mesmo
		 */
		bool operator==(const Commercial&);
};

/**
 *Classe derivada de User: Admin.
 *Classe que especifica um administrador. Um administrador e um utilizador que tem controlo
 *(parcial ou total) em toda a database.
 */

class Admin: public User {

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
		file & boost::serialization::base_object<User>(*this);
	}

public:

		/** Construtor da classe Admin.
		 *
		 */
		Admin(string usr = "", string pw = "");

		/**
		 * Devolve o tipo de utilizador, neste caso admin
		 */
		string getTypeOfUser() const;

};

#endif
