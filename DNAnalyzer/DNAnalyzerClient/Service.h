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

	static unordered_map<string, bool> AnalysePrecise(const struct Serveur & serveur, const string & filename, const string & maladie);
	// Mode d'emploi : Requ�te le serveur <serveur>, pour savoir si la maladie <maladie> se trouve dans le fichier genome <filename>
	//                 Retourne un dictionnaire dont la seule entr�e est le nom de la maladie associ�e � sa pr�sence (true) ou non (false) 
	//                 Si la maladie n'est pas connu du serveur, le dictionnaire retourn� ne contient aucune entr�e
	// Exception "runtime_error" : si le serveur est injoignable

	static unordered_map<string, bool> AnalyseGlobale(const struct Serveur & serveur, const string & filename );
	// Mode d'emploi : Requ�te le serveur <serveur>, pour savoir s'il connait une maladie dans le fichier genome <filename>
	//                 Retourne un dictionnaire dont les entr�es sont le nom des maladies associ�es � leur pr�sence (true) ou non (false) 
	// Exception "runtime_error" : si le serveur est injoignable

	static unordered_set<string> ObtenirMaladies(const struct Serveur & serveur);
	// Mode d'emploi : Requ�te le serveur <serveur>, pour obtenir l'ensemble des noms de maladies que celui-ci connait
	// Exception "runtime_error" : si le serveur est injoignable

	Service & operator = (const Service &);
	// Mode d'emploi : op�rateur d'affectation, non impl�ment�

	Service(const Service &);
	// Mode d'emploi : constructeur de copie, non impl�ment�


protected:

	Service();
	// Mode d'emploi : constructeur, non impl�ment�

	~Service();
	// Mode d'emploi : destructeur, non impl�ment�
};

#endif