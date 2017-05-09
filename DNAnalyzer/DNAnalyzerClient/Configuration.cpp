/*************************************************************************
Configuration - Classe de lecture d'un fichier de configurations serveurs
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

// R�alisation de la classe <Configuration> (fichier Configuration.cpp) //

#include "stdafx.h"
#include "Configuration.h"

#include "Serveur.h"

Configuration & Configuration::ObtenirInstance()
{
	// TODO: instance singleton

	return *((Configuration*) nullptr);
}

void Configuration::RafraichirInstance()
{
}

vector<struct Serveur> Configuration::ObtenirListeServeur()
{
	return vector<struct Serveur>();
}

bool Configuration::ChargerFichier(string fichierServeurs)
{
	return false;
}

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}
