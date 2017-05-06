/*************************************************************************
Dictionnaire - Classe de stockage des données de maladie
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Dictionnaire> (fichier Dictionnaire.h)  ----------//

#if ! defined ( DICTIONNAIRE_H )
#define DICTIONNAIRE_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include <unordered_map>
#include <unordered_set>
struct Maladie {};//TODO #include <Maladie>

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Dictionnaire>
//  La classe Dictionnaire permet d'axéder aux information des maladies 
//  et de leurs mot charger depuit un fichier
//------------------------------------------------------------------------


class Dictionnaire
{
protected:

	static Dictionnaire* instanceDictionnaire;
	// Description : Instance singleton de Dictionnaire

	unordered_map<string, Maladie*> maladies;
	// Description : Maladies retrouvable depuit son nom

	unordered_map<unsigned int, unordered_set<Maladie*>> maladiesParMot;
	// Description : Maladies retrouvable depuit un mot qui le compose

public:
	static Dictionnaire& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Dictionnaire

	const Maladie ObtenirMaladie(const string name);
	// Mode d'emploi : renvoit la Maladie corespondant au nom donnée en paramétre
	// Exception "range_error" : si la maladie demander n'existe pas

	const unordered_set<const Maladie *> ObtenirMaladies(const unsigned int indexMot);
	// Mode d'emploi : renvoit les Maladie comptenent le mot passer en paramétre
	//				   Si il n'y a pas de maladie renvoit un unordered_set vide
	// Contra d'utilisation : le mot passer en paramétre doit biencorespondre a un Mot

	const unordered_set<string> ObtenirNomsMaladies();
	// Mode d'emploi : renvoit la liste des nom de toutes les maladie du dictionnaire

	Dictionnaire & operator = (const Dictionnaire &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Dictionnaire(const Dictionnaire &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	Dictionnaire(const string path_dictionnaire);
	// Mode d'emploi : constructeur

	virtual ~Dictionnaire();
};

#endif