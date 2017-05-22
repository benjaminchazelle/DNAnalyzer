/*************************************************************************
Service - Classe d'interface des services de traitement distants
-------------------
début                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//      Réalisation de la classe <Service> (fichier Service.cpp)        //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

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

	try {
		request = "MA v1.0\r\n";
		request += "CHECK DISEASE\r\n";
		request += maladie + "\r\n";
		request += lireFichier(filename);
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Le fichier ne peut être ouvert");
	}

	try {
		response = Communication::EnvoyerMessage(serveur, request);
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Une erreur est survenue avec le serveur");
	}

	bool results;

	try {
		results = analysePreciseParseur(response);
	}
	catch (invalid_argument const& e) {
		UNREFERENCED_PARAMETER(e);
		throw invalid_argument("La réponse du serveur n'est pas correcte");
	}

	return results;
}

unordered_set<string> Service::AnalyseGlobale(const Serveur & serveur, const string & filename)
{
	string request, response;

	try {
		request = "MA v1.0\r\n";
		request += "CHECK ALL\r\n";
		request += lireFichier(filename);
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Le fichier ne peut être ouvert");
	}

	try {
		response = Communication::EnvoyerMessage(serveur, request);
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Une erreur est survenue avec le serveur");
	}

	unordered_set<string> results;

	try {
		results = analyseGlobaleParseur(response);
	}
	catch (invalid_argument const& e) {
		UNREFERENCED_PARAMETER(e);
		throw invalid_argument("La réponse du serveur n'est pas correcte");
	}

	return results;
}

unordered_set<string> Service::ObtenirMaladies(const Serveur & serveur)
{
	string response;

	try {
		response = Communication::EnvoyerMessage(serveur, "MA v1.0\r\nGET DISEASES\r\n\r\n");
	}
	catch (runtime_error const& e) {
		UNREFERENCED_PARAMETER(e);
		throw runtime_error("Une erreur est survenue avec le serveur");
	}

	unordered_set<string> maladies;

	try {
		maladies = obtenirMaladiesParseur(response);
	}
	catch (invalid_argument const& e) {
		UNREFERENCED_PARAMETER(e);
		throw invalid_argument("La réponse du serveur n'est pas correcte");
	}

	return maladies;
}

string Service::lireFichier(const string & filename)
{

	ifstream fichier(filename, ios::in);

	if (fichier)
	{
		string content((std::istreambuf_iterator<char>(fichier)), istreambuf_iterator<char>());

		fichier.close();

		return content;
	}
	else {

		throw runtime_error("Le fichier ne peut être ouvert");
	}

	return "";

}

bool Service::analysePreciseParseur(const string & response)
{
	bool results = false;

	stringstream responseStream;

	responseStream << response;

	string line;

	getline(responseStream, line, '\n');

	if (line != "MA v1.0\r")
	{
		throw invalid_argument("Requête incorrecte");
	}

	string prefix = "DESEASE ";
	size_t prefixLength = prefix.length();

	getline(responseStream, line, '\n');

	if (line.size() < prefixLength + 2)
	{
		throw invalid_argument("Requête incorrecte");
	}

	string maladie = line.substr(prefixLength, line.size() - prefixLength - 1);

	getline(responseStream, line, '\n');

	if (line == "1\r")
	{
		results = true;
	}
	else if (line == "0\r")
	{
	}
	else
	{
		throw invalid_argument("Requête incorrecte");
	}

	return results;
}

unordered_set<string> Service::analyseGlobaleParseur(const string & response)
{
	unordered_set<string> results;

	stringstream responseStream;

	responseStream << response;

	string line;

	getline(responseStream, line, '\n');

	if (line != "MA v1.0\r")
	{
		throw invalid_argument("Requête incorrecte");
	}

	const string prefix = "DESEASE ";
	const size_t prefixLength = prefix.length();

	while (getline(responseStream, line, '\n') && line.size() > 1) {

		if (line.size() < prefixLength + 2)
		{
			continue;
		}

		string maladie = line.substr(prefixLength, line.size() - prefixLength - 1);

		results.insert(maladie);

	}

	return results;
}

unordered_set<string> Service::obtenirMaladiesParseur(const string & response)
{
	unordered_set<string> maladies;

	stringstream responseStream;

	responseStream << response;

	string line;

	getline(responseStream, line, '\n');

	if (line != "MA v1.0\r")
	{
		throw invalid_argument("Requête incorrecte");
	}

	getline(responseStream, line, '\n');

	if (line != "DESEASES\r")
	{
		throw invalid_argument("Requête incorrecte");
	}

	while (getline(responseStream, line, '\n') && line.size() > 1) {

		maladies.insert(line.substr(0, line.size() - 1));
	}

	return maladies;
}

