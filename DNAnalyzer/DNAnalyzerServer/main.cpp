/*************************************************************************
Main - Fichier principal de l'application content le main
-------------------
début                :	20/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------------- Réalisation du Main (fichier Main.cpp) ---------------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <string>
#include <iostream>

//------------------------------------------------------ Include personnel

#include "Communication.h"
#include "Dictionnaire.h"

//------------------------------------------------------------------- MAIN

using namespace std;

const int DEFAULT_PORT = 8282;
const string DEFAULT_DICTIONNAIR_FILE = "./dictionnaire.dico";

void afficherUsage() {
	cout << "Usage :" << endl
		<< "./DNAnalyserServer [-dico <fileName>] [-port <serverPort>]" << endl
		<< "./DNAnalyserServer help" << endl;
}
void afficherSyntaxError(string erreurText) {
	cout << "Commande non valide : " << erreurText << endl;
	afficherUsage();
}
void afficherAide() {
	afficherUsage();
	cout << "Aide : " << endl
		<< "  Parametre       Alias                   Commentaire" << endl
		<< "" << endl
		<< "  -port <Port>    -p <Port>               Permet de changer le port d'ecoute du server, le port" << endl
		<< "                                          d'ecoute par default est "<< to_string(DEFAULT_PORT) << endl
		<< "" << endl
		<< "  -dico <file>    -d <file>               Permet de changer le fichier de dictionnaire charger" << endl
		<< "                  -dictionnaire <file>    laur du demarage du server, le fichier charger par" << endl
		<< "                                          defaut est \""+ DEFAULT_DICTIONNAIR_FILE +"\"" << endl;

}

int main(int argc, char** argv)
{
	unsigned int portNumber = 8282;
	string dicoFile = "./dictionnaire.dico";

	int t1 = stoi("test1");
	int t2 = stoi("test");
	int t3 = stoi("3test");
	int t4 = stoi("te4st");


	for (int i = 0; i < argc; i++) {
		string arg(argv[i]);
		if (!arg.empty()) {
			if (arg[0] == '-') {
				if (arg == "-d" || arg == "-dico" || arg == "-dictionnaire") {
					i++;
					if (i == argc) {
						afficherSyntaxError("nom de fichier requis aprés " + arg);
						exit(0);
					}
					dicoFile = argv[i];
				}
				if (arg == "-p" || arg == "-port") {
					i++;
					if (i == argc) {
						afficherSyntaxError("numero de port requis aprés " + arg);
						exit(0);
					}
					dicoFile = argv[i];
				}
				else {
					afficherSyntaxError("argument " + arg + " inconu");
					exit(0);
				}
			}
			else {//pour les paramétres obligatoir (aucun pour nous)
				if (arg == "help" && i == 0) {
					afficherAide();
					exit(0);
				}
				afficherSyntaxError("argument " + arg + " inconu");
				exit(0);
			}
		}
	}

	std::cout << "Chargement du Dictionnaire :  " << dicoFile << std::endl;
	try {
		Dictionnaire::ObtenirInstance().ChargerFichier(dicoFile);
	}
	catch (const exception &e) {
		std::cout << "Erreur lors du chargement di dictionnaire"<<endl;
		std::cout << "ERREUR : " << e.what() << endl;
		exit(0);
	}
	std::cout << "Dictionnaire Charger (" << to_string(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size()) <<" maladies charger)"<< std::endl;
	std::cout << "Demarage du server sur le port " << to_string(portNumber) << std::endl;
	try {
		Communication::ObtenirInstance().Ecouter(portNumber);
	}
	catch (const exception &e) {
		std::cout << "Erreur lors du demarage du server" << endl;
		std::cout << "ERREUR : " << e.what() << endl;
		exit(0);
	}
	std::cout << "Server sart" << std::endl;

	return 0;
}

