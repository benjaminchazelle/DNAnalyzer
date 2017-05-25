/*************************************************************************
Service - Classe d'interface des services de traitement distants
-------------------
d�but                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Service> (fichier Service.h)   //

#if ! defined ( SERVICE_H )
#define SERVICE_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//------------------------------------------------------------------------
// R�le de la classe <Service>
//  La classe Service permet d'invoquer les services de traitement distants
//  et de recevoir leur r�ponse
//------------------------------------------------------------------------

class Service
{
public:

	static bool AnalysePrecise(const struct Serveur & serveur, const string & filename, const string & maladie);
	// Mode d'emploi : Requ�te le serveur <serveur>, pour savoir si la maladie <maladie> se trouve dans le fichier genome <filename>
	//                 Retourne un dictionnaire dont la seule entr�e est le nom de la maladie associ�e � sa pr�sence (true) ou non (false) 
	//                 Si la maladie n'est pas connu du serveur, le dictionnaire retourn� ne contient aucune entr�e
	// Exception "invalid_argument" : Si le fichier <filename> ne peut �tre ouvert
	// Exception "runtime_error" : Si un probl�me r�seau survient avec le serveur
	// Exception "logic_error" : Si la r�ponse serveur est incorrecte
	// Exception "domain_error" : Si la requ�te �tait incorrecte

	static unordered_set<string> AnalyseGlobale(const struct Serveur & serveur, const string & filename);
	// Mode d'emploi : Requ�te le serveur <serveur>, pour savoir s'il connait une maladie dans le fichier genome <filename>
	//                 Retourne un dictionnaire dont les entr�es sont le nom des maladies associ�es � leur pr�sence (true) ou non (false) 
	// Exception "invalid_argument" : Si le fichier <filename> ne peut �tre ouvert
	// Exception "runtime_error" : Si un probl�me r�seau survient avec le serveur
	// Exception "logic_error" : Si la r�ponse serveur est incorrecte
	// Exception "domain_error" : Si la requ�te �tait incorrecte

	static unordered_set<string> ObtenirMaladies(const struct Serveur & serveur);
	// Mode d'emploi : Requ�te le serveur <serveur>, pour obtenir l'ensemble des noms de maladies que celui-ci connait
	// Exception "runtime_error" : Si un probl�me r�seau survient avec le serveur
	// Exception "logic_error" : Si la r�ponse serveur est incorrecte
	// Exception "domain_error" : Si la requ�te �tait incorrecte

	Service & operator = (const Service &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Service(const Service &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�


protected:

	static string lireFichier(const string & filename);
	// Moded'emploi : Retourne le contenu d'un fichier <filename>
	// Exception "runtime_error" : Si le fichier ne peut �tre ouvert

	static bool analysePreciseParseur(const string & response);
	// Mode d'emploi : Parse la r�ponse <response> d'une requ�te d'analyse pr�cise
	// Exception "invalid_argument" : Si la r�ponse <response> contient une erreur de syntaxe
	// Exception "runtime_error" : Si la requ�te contenait une erreur

	static unordered_set<string> analyseGlobaleParseur(const string & response);
	// Mode d'emploi : Parse la r�ponse <response> d'une requ�te d'analyse globale
	// Exception "invalid_argument" : Si la r�ponse <response> contient une erreur de syntaxe
	// Exception "runtime_error" : Si la requ�te contenait une erreur

	static unordered_set<string> obtenirMaladiesParseur(const string & response);
	// Mode d'emploi : Parse la r�ponse <response> d'une requ�te de listage des maladies
	// Exception "invalid_argument" : Si la r�ponse <response> contient une erreur de syntaxe
	// Exception "runtime_error" : Si la requ�te contenait une erreur

	static void verifierLigneErreur(const string & line);
	// Mode d'emploi : V�rifie la pr�sence d'une erreur
	// Exception "runtime_error" : Si une erreur est d�t�ct�e

	static void trimCarriageReturn(string & line);
	// Mode d'emploi : Retourne une cha�ne de caract�re sans "\r" final

	Service();
	// Mode d'emploi : Constructeur, non impl�ment�

	~Service();
	// Mode d'emploi : Destructeur, non impl�ment�

};

#endif