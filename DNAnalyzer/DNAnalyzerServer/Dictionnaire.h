/*************************************************************************
Dictionnaire - Classe de stockage des donn�es de maladies
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--  Interface de la classe <Dictionnaire> (fichier Dictionnaire.h)  --//

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

	unordered_map<string,const Maladie*> maladies;
	// Description : Maladies retrouvable depuit son nom

	unordered_map<unsigned int, unordered_set<const Maladie*>> maladiesParMot;
	// Description : Maladies retrouvable depuit un mot qui le compose

public:
	static Dictionnaire& ObtenirInstance();
	// Mode d'emploi : Renvoie l'instance singleton de Dictionnaire

	static void RafraichirInstance();
	// Mode d'emploi : R�initialise l'instance singleton

	void ChargerFichier(const string & fichierDico);
	// Mode d'emploi : Cette m�thode lit le contenu du fichier <fichierDico> pour charger son contenu
	// Exception "runtime_error" : Si le fichier ne peut �tre lu
	// Exception "invalid_argument" : Si le fichier n'est pas valide
	// Fichier valide : 
	//		MA v1.0(\r\n)+
	//		([a-Z0-9_ ]+(;<mot>*)+;?(\r\n)+)*
	//		([a-Z0-9_ ]+(;<mot>*)+;?(\r\n)?)?
	//
	//		Un <mot> diff�rent de /[ATCG]+/ est ignor�

	const Maladie * ObtenirMaladie(const string & nom);
	// Mode d'emploi : Renvoie la Maladie correspondant au nom <nom>
	// Exception "range_error" : Si la maladie demand�e n'existe pas

	const unordered_set<const Maladie *> ObtenirMaladies(const unsigned int indexMot);
	// Mode d'emploi : Renvoie les Maladie contenant le mot d'index <indexMot>.
	//                 Si il n'y a pas de maladie, renvoie un unordered_set vide
	// Contrat d'utilisation : Le mot pass� en param�tre doit bien correspondre � un Mot

	const unordered_set<string> ObtenirNomsMaladies();
	// Mode d'emploi : Renvoie la liste des noms de toutes les maladie du dictionnaire

	Dictionnaire & operator = (const Dictionnaire &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Dictionnaire(const Dictionnaire &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

protected:

	Dictionnaire();
	// Mode d'emploi : Constructeur

	virtual ~Dictionnaire();
	// Mode d'emploi : Destructeur
};

#endif