/*************************************************************************
Main - Fichier principal de l'application contenant le main
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
const string DEFAULT_DICTIONNARY_FILE = "./dictionnaire.dico";

void afficherUsage() {
	cout << "Manual :" << endl
		<< "./DNAnalyserServer [-dico <fileName>] [-port <serverPort>]" << endl
		<< "./DNAnalyserServer help" << endl;
}
void afficherSyntaxError(string erreurText) {
	cout << "Invalid command : " << erreurText << endl;
	afficherUsage();
}
void afficherAide() {
	afficherUsage();
	cout << "Help : " << endl
		<< "  Parameters             Alias            Comment" << endl
		<< endl
		<< "  -port <Port>          -p <Port>         Set the listening server's port" << endl
		<< "                                          Default port is " << to_string(DEFAULT_PORT) << endl
		<< endl
		<< "  -dictionnary <file>   -d <file>         Set the dictonnary file to load" << endl
		<< "                        -dico <file>      Default dictionnary file is " << DEFAULT_DICTIONNARY_FILE << endl;
}

int main(int argc, char** argv)
{
	unsigned int portNumber = DEFAULT_PORT;
	string dicoFile = DEFAULT_DICTIONNARY_FILE;

	for (int i = 1; i < argc; i++) {
		string arg(argv[i]);
		if (!arg.empty()) {
			if (arg[0] == '-') {
				if (arg == "-d" || arg == "-dico" || arg == "-dictionnary") {
					i++;
					if (i == argc) {
						afficherSyntaxError("Filename required after " + arg);
						exit(10);
					}
					dicoFile = argv[i];
				}
				else if (arg == "-p" || arg == "-port") {
					i++;
					if (i == argc) {
						afficherSyntaxError("Port number required after " + arg);
						exit(20);
					}
					try {
						size_t st;
						string arg_port(argv[i]);
						portNumber = stoi(arg_port, &st);
						if (st != arg_port.length()|| portNumber<1|| portNumber>65535) {
							afficherSyntaxError("Port number " + arg + " must be a number 1 and 65536");
							exit(21);
						}
					}
					catch (const invalid_argument &e) {
						afficherSyntaxError("Port number " + arg + " must be a number 1 and 65536");
						exit(21);
					}
					 
				}
				else {
					afficherSyntaxError("Unknown " + arg + " argument");
					exit(1);
				}
			}
			else { // Pour les futures paramètres obligatoires (aucun pour nous)
				if (arg == "help" && i == 1) {
					afficherAide();
					exit(0);
				}
				afficherSyntaxError("Unknown " + arg + " argument");
				exit(1);
			}
		}
	}

	std::cout << "Dictionnary loading :  " << dicoFile << std::endl;
	try {
		Dictionnaire::ObtenirInstance().ChargerFichier(dicoFile);
	}
	catch (runtime_error const& e) {
		std::cout << "Error during dictionnary loading" << endl;
		std::cout << "ERROR : impossible to open the dictionnary file" << endl;
		exit(11);
	}
	catch (invalid_argument const& e) {
		std::cout << "Error during dictionnary loading" << endl;
		std::cout << "ERROR : dictionnary file is syntaxically incorrect" << endl;
		exit(12);
	}
	std::cout << "Dictionnary loaded (" << to_string(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size()) << " diseases)" << std::endl;
	std::cout << "DNAnalyzer Server starting on port " << to_string(portNumber) << std::endl;
	try {
		Communication::ObtenirInstance().Ecouter(portNumber);
	}
	catch (runtime_error const& e) {
		std::cout << "Error during server starting" << endl;
		std::cout << "ERROR : " << e.what() << endl;
		exit(30);
		
	}

	return 0;
}

