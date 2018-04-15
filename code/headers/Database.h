#ifndef DATABASE_H_
#define DATABASE_H_

#include<fstream>
#include<vector>
#include"User.h"
#include"Trip.h"
#include"User.h"
#include<string>
#include<map>
#include<algorithm>
#include <utility>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<boost/serialization/vector.hpp>
#include<boost/serialization/map.hpp>
#include<boost/serialization/string.hpp>

using namespace std;


/**
	 * Metodo que retorna um booleano que compara de maneira ascendente dois particulars pelo nome
	 */
	bool ascendingNameP(Particular u1, Particular u2) ;

	/**
	 * Metodo que retorna um booleano que compara de maneira descentent dois particulars pelo nome
	 */
	bool descendingNameP(Particular u1, Particular u2) ;

	/**
	 * Metodo que retorna um booleano que compara de maneira ascendente dois commercials pelo nome
	 */
	bool ascendingNameC(Commercial u1, Commercial u2) ;

	/**
	 * Metodo que retorna um booleano que compara de maneira ascendente dois commercials pelo nome
	 */
	bool descendingNameC(Commercial u1, Commercial u2) ;

/**
 * Classe que gere todos as viagens e utilizadores, incluido todos os processos que dai advem
 */
class Database {
	friend class boost::serialization::access;
	vector<Particular> part;
	vector<Commercial> comme;
	vector<Admin> admins;
	vector<Trip> packages;
	vector<Transportation> transp;
	vector<string> destinations;
	map<string, vector<Accomodation> > accomodations;


	/**
	 * Salva o vector de particulares para o ficheiro.
	 */
	void save1(boost::archive::text_oarchive &file) { //changed here
		file << part;
	}

	/**
	 * Salva o vector de comerciais para o ficheiro.
	 */
	void save2(boost::archive::text_oarchive &file) {
		file << comme;
	}

	/**
	 * Salva o vector de admins para o ficheiro.
	 */
	void save3(boost::archive::text_oarchive &file) {
		file << admins;
	}

	/**
	 * Salva o vector de pacotes para o ficheiro.
	 */
	void save4(boost::archive::text_oarchive &file) {
		file << packages;
	}

	/**
	 * Salva o vector de destinos para o ficheiro.
	 */
	void save5(boost::archive::text_oarchive &file) {
		file << destinations;
	}

	/**
	 * Salva o vector de alojamentos para o ficheiro.
	 */
	void save6(boost::archive::text_oarchive &file) {
		file << accomodations;
	}

	/**
	 * Salva o vector de transportes para o ficheiro.
	 */
	void save7(boost::archive::text_oarchive &file) {
		file << transp;
	}

	/**
	 * Guarda o vector de particulares apartir do ficheiro.
	 */
	void load1(boost::archive::text_iarchive &file) {
		file >> part;
	}

	/**
	 * Guarda o vector de comerciais apartir do ficheiro.
	 */
	void load2(boost::archive::text_iarchive &file) {
		file >> comme;
	}

	/**
	 * Guarda o vector de admins apartir do ficheiro.
	 */
	void load3(boost::archive::text_iarchive &file) {
		file >> admins;
	}

	/**
	 * Guarda o vector de pacotes apartir do ficheiro.
	 */
	void load4(boost::archive::text_iarchive &file) {
		file >> packages;
	}

	/**
	 * Guarda o vector de destinos apartir do ficheiro.
	 */
	void load5(boost::archive::text_iarchive &file) {
		file >> destinations;
	}

	/**
	 * Guarda o vector de alojamentos apartir do ficheiro.
	 */
	void load6(boost::archive::text_iarchive &file) {
		file >> accomodations;
	}

	/**
	 * Guarda o vector de transportes apartir do ficheiro.
	 */
	void load7(boost::archive::text_iarchive &file) {
		file >> transp;
	}

	template<class Archive>
	void serialize(Archive &file, const unsigned int ver) {
	}

public:
	/**
	 * Construtor da database
	 */
	Database();

	/**
	 * Metodo que salva os dados nos ficheiros chamando as outras funcoes de save.
	 */
	void saveData();

	/**
	 * Metodo que faz loading dos dados nos ficheiros chamando as outras funcoes de load.
	 */
	void loadData();

	/**
	 * Adiciona um objecto do tipo particular ao vector de particulares.
	 */
	void addParticular(Particular);
	/**
	 * Retorna o vector de particulares da database.
	 */
	vector<Particular> getParticular() const;

	/**
	 * Adiciona um objecto do tipo commercial ao vector de commercials.
	 */
	void addCommercial(Commercial);
	/**
	 * Retorna o vector de commercials da database.
	 */
	vector<Commercial> getCommercial() const;

	/**
	 * Retorna o vector de admins da database.
	 */
	vector<Admin> getAdmins() const;

	/**
	 * Retorna o vector de pacotes da database.
	 */
	vector<Trip> getPackages() const;

	/**
	 * Retorna o vector de destinos da database.
	 */
	vector<string> getDestinations() const;

	/**
	 * Retorna o vector de alojamentos da database.
	 */
	map<string, vector<Accomodation> > getAccomodations() const;

	/**
	 * Retorna o vector de transportes da database.
	 */
	vector<Transportation> getTransportations() const;

	/**
	 * Adiciona ao vector de viagens da database uma viagem
	 */
	void addTrip(const Trip&);

	/**
	 * Adiciona ao vector do historico de viagens do utilizador passado uma viagem
	 */
	void addTripToUser(int, int, const Trip&); //1 - particular,2 -commercial ; position in vector

	/**
	 * Adiciona ao vector de destinos da database um destino
	 */
	void addDestination(const string&);

	/**
	 * Adiciona ao vector de alojamento da database um alojamento
	 */
	void addAccomodation(const string&, const Accomodation&);

	/**
	 * Adiciona ao vector de admins da database um admin
	 */
	void addAdmin(const Admin&);

	/**
     * Adiciona uma promoção ao vector de viagens.
     */

	void addPromotion(const Trip&);
	/**
	 * Actualiza uma viagem, tornando-a promocional.
	 */
	void addPromotion(unsigned int,double);
	/**
	 * Adiciona ao vector de transportes da database um transporte
	 */
	void addTransportation(const Transportation&);

	/**
	 * Remove do vector de particulares um particular passado como argumento
	 */
	void removeParticular(const Particular&);

	/**
	 * Remove do vector de particulares um particular com o indice passado como argumento
	 */
	void removeParticular(int);

	/**
	 * Remove do vector de particulares um particular com o nome do particular passado como argumento
	 */
	void removeParticular(const string&);

	/**
	 * Remove do vector de commercials um commercial
	 */
	void removeCommercial(const Commercial&);

	/**
	 * Remove do vector de commercials um commercial com o indice passado como argumento
	 */
	void removeCommercial(int);

	/**
	 * Remove do vector de commercials um commercial com o nome passado como argumento
	 */
	void removeCommercial(const string&);


	/**
	 *Organiza o vector de costumers por nome
	 */
	void sortCostumersByName(int, int);




	/**
	 * Edita a trip passada como primeiro argumento para a trip no segundo argumento
	 */
	void setTrip(Trip, Trip);

	/**
	 * Devolve o vector de particulares organizado por destinos
	 */

	vector<Particular> particularsByDestination(string) const;
	/**
	 * Devolve o vector de commercials organizado por destinos
	 */
	vector<Commercial> commercialsByDestination(string) const;

	/**
	 * Apaga os dados da database
	 */
	void clearDatabase(int);



};

#endif /* DATABASE_H_ */
