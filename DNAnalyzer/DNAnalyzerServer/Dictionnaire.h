/*************************************************************************
Dictionnaire - Classe de stockage des données de maladies
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

#include "Maladie.h"

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

	static void RafraichirInstance();
	// Mode d'emploi : réinitialise l'instance singleton

	const Maladie & ObtenirMaladie(const string name);
	// Mode d'emploi : renvoit la Maladie correspondant au nom donné en paramètre
	// Exception "range_error" : si la maladie demandée n'existe pas

	const unordered_set<Maladie *> ObtenirMaladies(const unsigned int indexMot);
	// Mode d'emploi : renvoit les Maladie contenant le mot passé en paramètre
	//                 Si il n'y a pas de maladie renvoit un unordered_set vide
	// Contrat d'utilisation : le mot passé en paramètre doit bien correspondre à un Mot

	const unordered_set<string> ObtenirNomsMaladies();
	// Mode d'emploi : renvoit la liste des noms de toutes les maladie du dictionnaire

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