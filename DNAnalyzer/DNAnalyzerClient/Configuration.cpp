/*************************************************************************
Mots - Classe de lecture d'un fichier de configurations serveurs
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

// Réalisation de la classe <Configuration> (fichier Configuration.cpp) //

#include "stdafx.h"
#include "Configuration.h"

#include "Serveur.h"

const string Configuration::fichierServeurs = "servers.config";

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

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}
