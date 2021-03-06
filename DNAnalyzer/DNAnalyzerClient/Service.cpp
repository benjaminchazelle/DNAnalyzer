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
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Service.h"
#include "Serveur.h"
#include "Communication.h"
//----------------------------------------------------------------- PUBLIC


bool Service::AnalysePrecise(const Serveur & serveur, const string & filename, const string & maladie)
{
	string request, response;

	// On formule la requ�te

	try {
		request = "MA v1.0\r\n";
		request += "CHECK DISEASE\r\n";
		request += maladie + "\r\n";
		request += lireFichier(filename);
		request += "\r\n\r\n";
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw invalid_argument("Le fichier ne peut �tre ouvert");
	}

	// On r�cup�re la r�ponse

	try {
		response = Communication::EnvoyerMessage(serveur, request);
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Une erreur est survenue avec le serveur");
	}

	// On analyse la r�ponse

	bool results;

	try {
		results = analysePreciseParseur(response);
	}
	catch (invalid_argument const& e) {
		UNREFERENCED_PARAMETER(e);
		throw logic_error("La r�ponse du serveur n'est pas correcte");
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw domain_error(e.what());
	}

	return results;
}

unordered_set<string> Service::AnalyseGlobale(const Serveur & serveur, const string & filename)
{
	string request, response;

	// On formule la requ�te

	try {
		request = "MA v1.0\r\n";
		request += "CHECK ALL\r\n";
		request += lireFichier(filename);
		request += "\r\n\r\n";
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw invalid_argument("Le fichier ne peut �tre ouvert");
	}

	// On r�cup�re la r�ponse

	try {
		response = Communication::EnvoyerMessage(serveur, request);
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Une erreur est survenue avec le serveur");
	}

	// On analyse la r�ponse

	unordered_set<string> results;

	try {
		results = analyseGlobaleParseur(response);
	}
	catch (invalid_argument const& e) {
		UNREFERENCED_PARAMETER(e);
		throw logic_error("La r�ponse du serveur n'est pas correcte");
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw domain_error(e.what());
	}

	return results;
}

unordered_set<string> Service::ObtenirMaladies(const Serveur & serveur)
{
	string response;

	// On r�cup�re la r�ponse de la requ�te

	try {
		response = Communication::EnvoyerMessage(serveur, "MA v1.0\r\nGET DISEASES\r\n\r\n");
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Une erreur est survenue avec le serveur");
	}

	// On analyse la r�ponse

	unordered_set<string> maladies;

	try {
		maladies = obtenirMaladiesParseur(response);
	}
	catch (invalid_argument const& e) {
		UNREFERENCED_PARAMETER(e);
		throw logic_error("La r�ponse du serveur n'est pas correcte");
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw domain_error(e.what());
	}

	return maladies;
}

string Service::lireFichier(const string & filename)
{
	// On lit le contenu d'un fichier

	ifstream fichier(filename, ios::in);

	if (fichier)
	{
		string content((std::istreambuf_iterator<char>(fichier)), istreambuf_iterator<char>());

		fichier.close();

		return content;
	}
	else {

		throw runtime_error("Le fichier ne peut �tre ouvert");
	}

	return "";

}

bool Service::analysePreciseParseur(const string & response)
{
	bool results = false;

	stringstream responseStream;

	responseStream << response;

	// On v�rifie l'en-t�te

	string line;

	getline(responseStream, line, '\n');
	trimCarriageReturn(line);

	if (line != "MA v1.0")
	{
		throw invalid_argument("R�ponse invalide");
	}

	// On v�rifie le d�but de ligne

	getline(responseStream, line, '\n');
	trimCarriageReturn(line);

	try {
		verifierLigneErreur(line);
	}
	catch(runtime_error const &e) {
		throw runtime_error(e.what());
	}

	char lastChar = line.at(line.size() - 1);

	if ((line.find("DISEASE ") != 0 && line.find("DESEASE ") != 0) || lastChar == ' ')
	{
		throw invalid_argument("R�ponse invalide");
	}

	getline(responseStream, line, '\n');


	if (line == "1\r")
	{
		results = true;
	}
	else if (line == "0\r")
	{
		// On ne fait rien ici
	}
	else
	{
		throw invalid_argument("R�ponse invalide");
	}

	return results;
}

unordered_set<string> Service::analyseGlobaleParseur(const string & response)
{
	unordered_set<string> results;

	stringstream responseStream;

	responseStream << response;

	// On v�rifie l'en-t�te

	string line;

	getline(responseStream, line, '\n');
	trimCarriageReturn(line);


	if (line != "MA v1.0")
	{
		throw invalid_argument("R�ponse invalide");
	}

	// On lit les lignes une � une

	const string goodPrefix = "DISEASE ";
	const string retroPrefix = "DESEASE ";

	bool secondLine = true;

	while (getline(responseStream, line, '\n') && line.size() > 1) {
		trimCarriageReturn(line);

		if (secondLine) {
			try {
				verifierLigneErreur(line);
			}
			catch (runtime_error const &e) {
				throw runtime_error(e.what());
			}
			secondLine = false;
		}

		char lastChar = line.at(line.size() - 1);

		if (lastChar == ' ')
		{
			throw invalid_argument("R�ponse invalide");
		}


//		string maladie = line.substr(prefixLength, line.size() - prefixLength +(line.at(line.length()-1)=='\r'?-1:0));

		string maladie;

		if (line.find(goodPrefix) == 0)
		{
			maladie = line.substr(goodPrefix.length(), line.size() - goodPrefix.length());
		}
		else if (line.find(retroPrefix) == 0)
		{
			maladie = line.substr(retroPrefix.length(), line.size() - retroPrefix.length());
		}
		else
		{
			throw invalid_argument("R�ponse invalide");
		}
		
		results.insert(maladie);

	}

	return results;
}

unordered_set<string> Service::obtenirMaladiesParseur(const string & response)
{
	unordered_set<string> maladies;

	stringstream responseStream;

	responseStream << response;

	// On v�rifie l'en-t�te

	string line;

	getline(responseStream, line, '\n');
	trimCarriageReturn(line);

	if (line != "MA v1.0")
	{
		throw invalid_argument("R�ponse invalide");
	}

	getline(responseStream, line, '\n');
	trimCarriageReturn(line);

	try {
		verifierLigneErreur(line);
	}
	catch (runtime_error const &e) {
		throw runtime_error(e.what());
	}

	if (line != "DESEASES" && line != "DISEASES")
	{
		throw invalid_argument("R�ponse invalide");
	}

	// On lit ligne par ligne pour ajouter la maladie � l'ensemble

	while (getline(responseStream, line, '\n') && line.size() > 1) {
		trimCarriageReturn(line);

		maladies.insert(line.substr(0, line.size()));
	}

	return maladies;
}

void Service::verifierLigneErreur(const string & line)
{
	const string errorPrefix = "ERROR ";

	if (line.find(errorPrefix) == 0) {

		string errorDescription = line.substr(errorPrefix.length(), line.length() - errorPrefix.length());

		throw runtime_error(errorDescription);
	}
}

void Service::trimCarriageReturn(string & line)
{
	if (line.at(line.length() - 1) == '\r') {
		line = line.substr(0, line.length() - 1);
	}
}

