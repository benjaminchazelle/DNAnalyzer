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
#include "Log.h"

#define UNREFERENCE_PARAMETER(P) (P)

//------------------------------------------------------------------- MAIN

using namespace std;

const int DEFAULT_PORT = 8282;
const string DEFAULT_DICTIONNARY_FILE = "./dictionnaire.dico";

structlog LOGCFG;

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
		<< "                        -dico <file>      Default dictionnary file is " << DEFAULT_DICTIONNARY_FILE << endl
		<< endl
		<< "  -log <logLevel>                         Set the level of a log. logLevel must" << endl
		<< "                                          be DEBUG, INFO, WARNING or ERROR" << endl
		<< "                                              Default log level is INFO" << endl;
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
						if (st != arg_port.length() || portNumber<1 || portNumber>65535) {
							afficherSyntaxError("Port number " + arg + " must be a number 1 and 65536");
							exit(21);
						}
					}
					catch (const invalid_argument &e) {
						UNREFERENCE_PARAMETER(e);

						afficherSyntaxError("Port number " + arg + " must be a number 1 and 65536");
						exit(21);
					}

				}else if(arg == "-log") {
					i++;
					if (i == argc) {
						afficherSyntaxError("log level required after " + arg);
						exit(40);
					}
					else {
						string logLevelArg = argv[i];
						if (logLevelArg == "DEBUG") {
							LOGCFG.level = T_DEBUG;

						}
						else if (logLevelArg == "INFO") {
							LOGCFG.level = T_INFO;
						}
						else if (logLevelArg == "WARNING") {
							LOGCFG.level = T_WARN;
						}
						else if (logLevelArg == "ERROR") {
							LOGCFG.level = T_ERROR;
						}
						else {
							afficherSyntaxError(logLevelArg + "is not a valide log level (DEBUG, INFO, WARNING, ERROR)");
							exit(41);

						}
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

	LOG(T_INFO) << "[MAIN] Dictionnary loading :  " << dicoFile;
	try {
		Dictionnaire::ObtenirInstance().ChargerFichier(dicoFile);
	}
	catch (runtime_error const& e) {
		UNREFERENCE_PARAMETER(e);

		LOG(T_ERROR) << "[MAIN] Error during dictionnary loading";
		LOG(T_ERROR) << "[MAIN] Impossible to open the dictionnary file" ;
		exit(11);
	}
	catch (invalid_argument const& e) {
		UNREFERENCE_PARAMETER(e);

		LOG(T_ERROR) << "[MAIN] Error during dictionnary loading";
		LOG(T_ERROR) << "[MAIN] ERROR : dictionnary file is syntaxically incorrect";
		exit(12);
	}
	LOG(T_INFO) << "[MAIN] Dictionnary loaded (" << to_string(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size()) << " diseases)";
	LOG(T_INFO) << "[MAIN] DNAnalyzer Server starting on port " << to_string(portNumber);
	try {
		Communication::ObtenirInstance().Ecouter(portNumber);
	}
	catch (runtime_error const& e) {
		LOG(T_ERROR) << "[MAIN] Error during server starting";
		LOG(T_ERROR) << "[MAIN] ERROR : " << e.what();
		exit(30);
		
	}

	return 0;
}

