/*************************************************************************
Service - Classe d'interface des services de traitement distants
-------------------
d�but                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//      R�alisation de la classe <Service> (fichier Service.cpp)        //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

#include "stdafx.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Service.h"
#include "Serveur.h"

//----------------------------------------------------------------- PUBLIC


unordered_map<string, bool> Service::AnalysePrecise(const Serveur & serveur, const string & filename, const string & maladie)
{
	return unordered_map<string, bool>();
}

unordered_map<string, bool> Service::AnalyseGlobale(const Serveur & serveur, const string & filename)
{
	return unordered_map<string, bool>();
}

unordered_set<string> Service::ObtenirMaladies(const Serveur & serveur)
{
	return unordered_set<string>();
}

