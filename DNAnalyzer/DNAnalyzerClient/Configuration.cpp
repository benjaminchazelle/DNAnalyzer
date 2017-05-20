/*************************************************************************
Configuration - Classe de lecture d'un fichier de configurations serveurs
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

// Réalisation de la classe <Configuration> (fichier Configuration.cpp) //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Configuration.h"
#include "Serveur.h"

//----------------------------------------------------------------- PUBLIC

Configuration* Configuration::instanceConfiguration = new Configuration();

Configuration & Configuration::ObtenirInstance()
{
	return *instanceConfiguration;
}

void Configuration::RafraichirInstance()
{
	if (instanceConfiguration != nullptr) {
		delete instanceConfiguration;
	}

	instanceConfiguration = new Configuration();
}

vector<struct Serveur> Configuration::ObtenirListeServeur() const
{
	return serveurs;
}

bool Configuration::ChargerFichier(const string & fichierServeurs)
{
	ifstream fichier(fichierServeurs, ios::in);

	if (fichier)
	{
		string line;

		while (getline(fichier, line, '\n')) {

			stringstream linestream;
			linestream << line;

			string hostname;

			getline(linestream, hostname, ':');

			string port;

			getline(linestream, port);

			bool validPort = !port.empty()
				&& port.find_first_not_of("0123456789") == std::string::npos;

			if (!validPort || hostname.empty()) {
				continue;
			}

			Serveur serveur;
			serveur.host = hostname;
			serveur.port = stoi(port);

			if (serveur.port > 65535 || serveur.port == 0) {
				continue;
			}

			serveurs.push_back(serveur);

		}

		fichier.close();

		return true;

	}

	return false;
}

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}
