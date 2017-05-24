/*************************************************************************
Master - Classe qui g�re la communication entre un client et le service demand�
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//------- R�alisation de la classe <Master> (fichier Master.cpp) -------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel

#include "Master.h"
#include "CommunicationThread.h"
#include "Dictionnaire.h"
#include "Analyse.h"

#define UNREFERENCE_PARAMETER(P) (P)


//----------------------------------------------------------------- PUBLIC

void Master::InterpreterRequete(CommunicationThread & thread)
{
	// En-t�te de requ�te
	if (thread.LireLigne() != "MA v1.0") {
		repondreErreurRequete("Invalid syntax", thread);
		thread.FermerConnexion();
		return;
	}

	string serviceName = thread.LireLigne();

	// Routage du service demand�
	if (serviceName == "CHECK DISEASE")
	{
		string maladie = thread.LireLigne();

		string genome = thread.LireLigne();

		analysePrecise(maladie, genome, thread);
	}
	else if (serviceName == "CHECK ALL")
	{
		string genome = thread.LireLigne();

		analyseGlobale(genome, thread);
	}
	else if (serviceName == "GET DISEASES")
	{
		string crlf = thread.LireLigne();

		if (crlf == "") {
			obtenirListeMaladies(thread);
		}
		else {
			repondreErreurRequete("Invalid syntax", thread);
		}
	}
	else
	{
		repondreErreurRequete("Unknown service", thread);
	}

	thread.FermerConnexion();

}

//----------------------------------------------------------------- PRIVEE

void Master::analysePrecise(const string & nomMaladie, const string & genome, CommunicationThread & thread)
{
	// Analyse pr�cise

	string response = "MA v1.0\r\n";

	try {

		const Maladie* maladie = Dictionnaire::ObtenirInstance().ObtenirMaladie(nomMaladie);

		bool result = Analyse::AnalysePrecise(encoderGenome(genome), *maladie);

		response += "DESEASE " + nomMaladie;
		response += "\r\n";
		response += result ? "1" : "0";
		response += "\r\n\r\n";

		thread.Repondre(response);
	}
	catch (range_error const& e) { // Si la maladie est inconnue
		UNREFERENCE_PARAMETER(e);

		repondreErreurRequete("Unknown disease", thread);

	}

}

void Master::analyseGlobale(const string & genome, CommunicationThread & thread)
{
	// Analyse globale

	string response = "MA v1.0\r\n";

	for (const auto& resultatMaladie : Analyse::AnalyseGlobale(encoderGenome(genome))) {

		response += "DESEASE ";
		response += resultatMaladie->nom + "\r\n";

	}

	response += "\r\n";

	thread.Repondre(response);
}

void Master::obtenirListeMaladies(CommunicationThread & thread)
{
	// Obtenir la liste des maladies

	string response = "MA v1.0\r\n";

	response += "DESEASES\r\n";

	for (const auto& maladie : Dictionnaire::ObtenirInstance().ObtenirNomsMaladies()) {
		response += maladie + "\r\n";
	}

	response += "\r\n";

	thread.Repondre(response);
}

void Master::repondreErreurRequete(const string & error, CommunicationThread & thread)
{
	// R�pondre une erreur

	string response = "MA v1.0\r\n";
	response += "ERROR " + error;
	response += "\r\n\r\n";

	thread.Repondre(response);
}

unordered_set<string> Master::encoderGenome(const string & genome)
{
	// Conversion d'un g�nome de string � unordered_set<string>

	unordered_set<string> set;
	unsigned int pos = -1;

	// On lit les mots un � un, s�par� par ";"
	do {
		unsigned int startPos = pos + 1;
		for (pos = startPos; pos < genome.length() && genome[pos] != ';'; pos++);
		if (pos != startPos) {
			set.insert(genome.substr(startPos, pos - startPos));
		}

	} while (pos < genome.length()); 

	return set;
}
