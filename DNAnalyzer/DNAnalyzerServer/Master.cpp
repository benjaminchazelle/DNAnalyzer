/*************************************************************************
Master - Classe qui gére la communication entre un client et le service demandé
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//------- Réalisation de la classe <Master> (fichier Master.cpp) -------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
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
	LOG(T_DEBUG) << "[Master] c:"<<&thread<<" call InterpreterRequete";
	// En-tête de requête
	string header = thread.LireLigne();
	if (header != "MA v1.0") {
		LOG(T_WARN) << "[Master] c:" << &thread << " Requette non valide, invalide header";
		LOG(T_DEBUG) << "[Master] c:" << &thread << " header : "<< header;
		repondreErreurRequete("Invalid syntax", thread);
		thread.FermerConnexion();
		return;
	}

	string serviceName = thread.LireLigne();
	LOG(T_DEBUG) << "[Master] c:" << &thread << " header : " << header << " serviveName : " << serviceName;

	// Routage du service demandé
	if (serviceName == "CHECK DISEASE" || serviceName == "CHECK DESEASE")
	{
		LOG(T_INFO) << "[Master] c:" << &thread << " demande le service CHECK DISEASE";
		LOG(T_DEBUG) << "[Master] c:" << &thread << " recuperation de la maladie";
		string maladie = thread.LireLigne();

		LOG(T_DEBUG) << "[Master] c:" << &thread << " recuperation du genome";
		string genome = thread.LireLigne();

		LOG(T_DEBUG) << "[Master] c:" << &thread << " routage vers CHECK DISEASE";
		analysePrecise(maladie, genome, thread);
	}
	else if (serviceName == "CHECK ALL")
	{
		LOG(T_INFO) << "[Master] c:" << &thread << " demande le service CHECK ALL";
		LOG(T_DEBUG) << "[Master] c:" << &thread << " recuperation du genome";
		string genome = thread.LireLigne();

		LOG(T_DEBUG) << "[Master] c:" << &thread << " routage vers CHECK ALL";
		analyseGlobale(genome, thread);
	}
	else if (serviceName == "GET DISEASES" || serviceName == "GET DESEASES")
	{
		LOG(T_INFO) << "[Master] c:" << &thread << " demande le service GET DISEASES";
		LOG(T_DEBUG) << "[Master] c:" << &thread << " recuperation de la dérnière ligne (ligne vide)";
		string crlf = thread.LireLigne();

		if (crlf == "") {
			LOG(T_DEBUG) << "[Master] c:" << &thread << " routage vers GET DISEASES";
			obtenirListeMaladies(thread);
		}
		else {
			LOG(T_WARN) << "[Master] c:" << &thread << " requête de syntaxe invalide  (service GET DISEASES)";
			LOG(T_DEBUG) << "[Master] c:" << &thread << " ligne suplementaire non permise : \""<<crlf<<"\"";
			repondreErreurRequete("Invalid syntax", thread);
		}
	}
	else
	{
		LOG(T_WARN) << "[Master] c:" << &thread << " Demande de service inconu";
		repondreErreurRequete("Unknown service", thread);
	}

	LOG(T_DEBUG) << "[Master] c:" << &thread << " traitement de la requete fini fermeture de la connexion";

	thread.FermerConnexion();

	LOG(T_DEBUG) << "[Master] c:" << &thread << " end InterpreterRequete";
}

//----------------------------------------------------------------- PRIVEE

void Master::analysePrecise(const string & nomMaladie, const string & genome, CommunicationThread & thread)
{
	// Analyse précise
	LOG(T_DEBUG) << "[Master] c:" << &thread << " call analysePrecise(" << nomMaladie << ", un genome, " << &thread << ")";

	string response = "MA v1.0\r\n";
	
	unordered_set<string> genomeSet;

	try {
		LOG(T_DEBUG) << "[Master] c:" << &thread << " lecture du genome";
		genomeSet = encoderGenome(genome);
	}
	catch (invalid_argument const& e) {
		UNREFERENCE_PARAMETER(e);
		LOG(T_WARN) << "[Master] c:" << &thread << " genome incorrect";

		repondreErreurRequete("Invalid genome", thread);
		return;
	}

	try {

		LOG(T_DEBUG) << "[Master] c:" << &thread << " lecture de la maladie";
		const Maladie* maladie = Dictionnaire::ObtenirInstance().ObtenirMaladie(nomMaladie);

		LOG(T_DEBUG) << "[Master] c:" << &thread << " lancement de l'analyse precise";
		bool result = Analyse::AnalysePrecise(genomeSet, *maladie);

		response += "DISEASE " + nomMaladie;
		response += "\r\n";
		response += result ? "1" : "0";
		response += "\r\n\r\n";

		LOG(T_DEBUG) << "[Master] c:" << &thread << " repond au client";
		thread.Repondre(response);
	}
	catch (range_error const& e) { // Si la maladie est inconnue
		UNREFERENCE_PARAMETER(e);

		LOG(T_WARN) << "[Master] c:" << &thread << " demande une maladie non répértoriée";
		repondreErreurRequete("Unknown disease", thread);

	}
	LOG(T_DEBUG) << "[Master] c:" << &thread << " end analysePrecise";

}

void Master::analyseGlobale(const string & genome, CommunicationThread & thread)
{
	LOG(T_DEBUG) << "[Master] c:" << &thread << " call analyseGlobale(un genome, " << &thread << ")";
	// Analyse globale

	string response = "MA v1.0\r\n";

	unordered_set<string> genomeSet;

	try {
		LOG(T_DEBUG) << "[Master] c:" << &thread << " lecture du genome";
		genomeSet = encoderGenome(genome);
	}
	catch (invalid_argument const& e) {
		UNREFERENCE_PARAMETER(e);

		LOG(T_WARN) << "[Master] c:" << &thread << " genome incorrect";
		repondreErreurRequete("Invalid genome", thread);
		return;
	}

	LOG(T_DEBUG) << "[Master] c:" << &thread << " lancement de l'analyse globale";
	for (const auto& resultatMaladie : Analyse::AnalyseGlobale(encoderGenome(genome))) {

		response += "DISEASE ";
		response += resultatMaladie->nom + "\r\n";

	}

	response += "\r\n";

	LOG(T_DEBUG) << "[Master] c:" << &thread << " repond au client";
	thread.Repondre(response);
	LOG(T_DEBUG) << "[Master] c:" << &thread << " end analyseGlobale";
}

void Master::obtenirListeMaladies(CommunicationThread & thread)
{
	// Obtenir la liste des maladies
	LOG(T_DEBUG) << "[Master] c:" << &thread << " call obtenirListeMaladies("<<&thread<<")";

	string response = "MA v1.0\r\n";

	response += "DISEASES\r\n";

	for (const auto& maladie : Dictionnaire::ObtenirInstance().ObtenirNomsMaladies()) {
		response += maladie + "\r\n";
	}

	response += "\r\n";

	LOG(T_DEBUG) << "[Master] c:" << &thread << " repond au client";
	thread.Repondre(response);
	LOG(T_DEBUG) << "[Master] c:" << &thread << " end obtenirListeMaladies";
}

void Master::repondreErreurRequete(const string & error, CommunicationThread & thread)
{
	// Répondre une erreur
	LOG(T_DEBUG) << "[Master] c:" << &thread << " call repondreErreurRequete("<< error <<", " << &thread << ")";

	string response = "MA v1.0\r\n";
	response += "ERROR " + error;
	response += "\r\n\r\n";

	LOG(T_DEBUG) << "[Master] c:" << &thread << " repond au client";
	thread.Repondre(response);
	LOG(T_DEBUG) << "[Master] c:" << &thread << " end repondreErreurRequete";
}

unordered_set<string> Master::encoderGenome(const string & genome)
{
	// Conversion d'un génome de string à unordered_set<string>

	if (genome.find_first_not_of("ATCG;") != std::string::npos) {
		throw invalid_argument("Invalid genome");
	}

	unordered_set<string> set;
	unsigned int pos = -1;

	// On lit les mots un à un, séparé par ";"
	do {
		unsigned int startPos = pos + 1;
		for (pos = startPos; pos < genome.length() && genome[pos] != ';'; pos++);
		if (pos != startPos) {
			set.insert(genome.substr(startPos, pos - startPos));
		}

	} while (pos < genome.length());

	return set;
}
