/*************************************************************************
Configuration - Classe de lecture d'un fichier de configurations serveurs
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

// R�alisation de la classe <Configuration> (fichier Configuration.cpp) //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

#include "stdafx.h"
#include <string>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Configuration.h"
#include "Serveur.h"

//----------------------------------------------------------------- PUBLIC

Configuration & Configuration::ObtenirInstance()
{
	// TODO: instance singleton

	return *((Configuration*) nullptr);
}

void Configuration::RafraichirInstance()
{
}

vector<struct Serveur> Configuration::ObtenirListeServeur() const
{
	return vector<struct Serveur>();
}

bool Configuration::ChargerFichier(const string & fichierServeurs)
{
	return false;
}

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}
