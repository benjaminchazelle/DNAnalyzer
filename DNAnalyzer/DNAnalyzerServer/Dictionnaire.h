/*************************************************************************
Dictionnaire - Classe de stockage des donn�es de maladies
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Dictionnaire> (fichier Dictionnaire.h)  ----------//

#if ! defined ( DICTIONNAIRE_H )
#define DICTIONNAIRE_H

//--------------------------------------------------- Interfaces utilis�es

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Maladie.h"

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <Dictionnaire>
//  La classe Dictionnaire permet d'ax�der aux information des maladies 
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
	// Mode d'emploi : r�initialise l'instance singleton

	const Maladie & ObtenirMaladie(const string name);
	// Mode d'emploi : renvoit la Maladie correspondant au nom donn� en param�tre
	// Exception "range_error" : si la maladie demand�e n'existe pas

	const unordered_set<Maladie *> ObtenirMaladies(const unsigned int indexMot);
	// Mode d'emploi : renvoit les Maladie contenant le mot pass� en param�tre
	//                 Si il n'y a pas de maladie renvoit un unordered_set vide
	// Contrat d'utilisation : le mot pass� en param�tre doit bien correspondre � un Mot

	const unordered_set<string> ObtenirNomsMaladies();
	// Mode d'emploi : renvoit la liste des noms de toutes les maladie du dictionnaire

	Dictionnaire & operator = (const Dictionnaire &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Dictionnaire(const Dictionnaire &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	Dictionnaire(const string path_dictionnaire);
	// Mode d'emploi : constructeur

	virtual ~Dictionnaire();
};

#endif