#ifndef INTERFACE_H_
#define INTERFACE_H_

#include"Database.h"
#include <iostream>
#include <iomanip>
#include "User.h"
#include "Trip.h"
#include <windows.h>
#include <conio.h>
#include <string>
/**
 * Classe que gere toda a interface da agencia
 */
class Interface {
private:
	Database db;
	User* loggedUser;
	int loggedUserindex;
	string loggedtype;
public:
	Interface() {
	}
	;
	Interface(Database database) {
		db = database;
	}
	;
	Database getDatabase() const;

	//General Interface

	/**
	 * Mostra o menu de boas-vindas
	 */
	void showInitialScreen();

	/**
		 * Mostra o menu principal, com as opcoes mais "generalizadas"
		 */
	void showMainMenu();
	/**
		 * Mostra o menu de registo
		 */
	void showSignUpMenu();
	/**
		 * Mostra o menu de oferta de servicoes, sao expostos aqui os servicos que agencia oferece
		 */
	void showOfferedServices();
	/**
		 * Mostra o menu onde as informacoes de contacto sao mostradas
		 */
	void showContactUs();
	/**
		 * Mostra o menu de login
		 */
	void showLogin();

	//Costumer Interface

	/**
		 * Mostra o menu geral do cliente
		 */
	void showCostumerMenu();

	/**
		 * Mostra o menu de compra para o cliente com as varias opcoes de compra
		 */
	void showBuyMenu();

	/**
		 * Mostra o menu de compra dos pacotes pre-definidos
		 */
	void showDefaultPkg();

	/**
			 * Mostra o menu de compra dos pacotes pre-definidos
			 */
	void showPromoPkg();

	/**
			 * Mostra o menu de compra dos pacotes promocionais
			 */
	void showPastTrips();

	/**
			 * Mostra o menu que mostra as compras que o cliente fez
			 */
	void showAllPkgs();

	/**
			 * Mostra o menu de compra de pacotes customizados
			 */
	void showIndvPkgs();

	/**
			 * Mostra o menu que remove o cliente da agencia
			 */
	void showUnsubscribe();

	/**
			 * Mostra o menu de compra de um pacote, pesquisando por pais
			 */
	void showSearchByCountry();

	/**
			 * Mostra o menu de compra individual, nomeadamente a seccao de origem
			 */
	string showIndvOrigin(Trip & tp);

	/**
				 * Mostra o menu de compra individual, nomeadamente a seccao de destino
				 */
	unsigned int showIndvDestination(Trip & tp, string origin);

	/**
				 * Mostra o menu de compra individual, nomeadamente a seccao de destino, mas so para opcao de alojamento unico
				 */
	unsigned int showIndvDestinationforAcc(Trip & tp);

	/**
				 * Mostra o menu de compra individual, nomeadamente a seccao de transporte
				 */
	unsigned int showIndvTransportation(Trip & tp, unsigned int destination);

	/**
					 * Mostra o menu de compra individual, nomeadamente a seccao de alojamento
					 */
	void showIndvAccommodation(Trip & tp, unsigned int destination,
			unsigned int peopleNumber);

	//Admin Interface

	/**
	 * Mostra o menu geral de Admin
	 */
	void showAdminMenu();

	/**
			 * Mostra a tabela de clientes
			 */
	void showCostumers();

	/**
			 * Mostra o menu com a opcao de adicionar uma viagem a um cliente
			 */
	void showAddTripToCostumer();

	/**
			 * Mostra o menu com a opcao de adicionar um novo cliente
			 */
	void showAddCostumer();

	/**
			 * Mostra o menu com a opcao de remover um novo cliente
			 */
	void showRemoveCostumer();

	/**
				 * Mostra o menu com a opcao de adicionar um destino a database
				 */
	void showAddDestination();

	/**
				 * Mostra o menu com a opcao de adicionar um novo pacote de viagem a database
				 */
	void showAddNewPackage();

	/**
			 * Mostra o menu de clientes para o admin
			 */
	int showAllCostumers(); // return option

	/**
			 * Mostra o menu com a tabela de pacotes
			 */
	void showPackages();

	/**
			 * Mostra o menu de compra dos pacotes, mostrando os pre-definidos ou os promocionais
			 */
	int showPackages(int); //1 - default, 2 - promotionals
};

#endif
