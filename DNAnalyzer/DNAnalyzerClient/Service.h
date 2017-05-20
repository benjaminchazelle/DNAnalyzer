/*************************************************************************
Service - Classe d'interface des services de traitement distants
-------------------
début                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Service> (fichier Service.h)   //

#if ! defined ( SERVICE_H )
#define SERVICE_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Service>
//  La classe Service permet d'invoquer les services de traitement distants
//  et de recevoir leur réponse
//------------------------------------------------------------------------

class Service
{
public:

	static unordered_map<string, bool> AnalysePrecise(const struct Serveur & serveur, const string & filename, const string & maladie);
	// Mode d'emploi : Requête le serveur <serveur>, pour savoir si la maladie <maladie> se trouve dans le fichier genome <filename>
	//                 Retourne un dictionnaire dont la seule entrée est le nom de la maladie associée à sa présence (true) ou non (false) 
	//                 Si la maladie n'est pas connu du serveur, le dictionnaire retourné ne contient aucune entrée
	// Exception "invalid_argument" : si le fichier <filename> ne peut être ouvert
	// Exception "runtime_error" : si un problème survient avec le serveur

	static unordered_map<string, bool> AnalyseGlobale(const struct Serveur & serveur, const string & filename);
	// Mode d'emploi : Requête le serveur <serveur>, pour savoir s'il connait une maladie dans le fichier genome <filename>
	//                 Retourne un dictionnaire dont les entrées sont le nom des maladies associées à leur présence (true) ou non (false) 
	// Exception "invalid_argument" : si le fichier <filename> ne peut être ouvert
	// Exception "runtime_error" : si un problème survient avec le serveur

	static unordered_set<string> ObtenirMaladies(const struct Serveur & serveur);
	// Mode d'emploi : Requête le serveur <serveur>, pour obtenir l'ensemble des noms de maladies que celui-ci connait
	// Exception "runtime_error" : si un problème survient avec le serveur

	Service & operator = (const Service &);
	// Mode d'emploi : opérateur d'affectation, non implémenté

	Service(const Service &);
	// Mode d'emploi : constructeur de copie, non implémenté


protected:

	Service();
	// Mode d'emploi : constructeur, non implémenté

	~Service();
	// Mode d'emploi : destructeur, non implémenté

	static string lireFichier(const string & filename);
	// Moded'emploi : retourne le contenu d'un fichier <filename>
	// Exception "runtime_error" : si le fichier ne peut être ouvert

	static unordered_map<string, bool> analysePreciseParseur(const string & response);
	// Mode d'emploi : parse la réponse d'une requête d'analyse précise
	// Exception "invalid_argument" : si la réponse <response> contient une erreur de syntaxe

	static unordered_map<string, bool> analyseGlobaleParseur(const string & response);
	// Mode d'emploi : parse la réponse d'une requête d'analyse globale
	// Exception "invalid_argument" : si la réponse <response> contient une erreur de syntaxe

	static unordered_set<string> obtenirMaladiesParseur(const string & response);
	// Mode d'emploi : parse la réponse d'une requête de listage des maladies
	// Exception "invalid_argument" : si la réponse <response> contient une erreur de syntaxe

};

#endif