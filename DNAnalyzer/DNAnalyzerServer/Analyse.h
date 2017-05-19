/*************************************************************************
Analyse - Classe qui analyse la présence de maladies dans un génome
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//------- Interface de la classe <Analyse> (fichier Analyse.h)  --------//

#if ! defined ( ANALYSE_H )
#define ANALYSE_H

//--------------------------------------------------- Interfaces utilisées

#include <unordered_map>
#include "Maladie.h"

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Analyse>
//  La classe Analyse permet d'analyser un génome grâce à 2 méthodes d'analyse.
//  L'un permet de vérifier la présence d'une seule maladie, l'autre de trouver 
//  l'ensemble des potentielles maladies
//------------------------------------------------------------------------


class Analyse
{
public:

	static bool AnalysePrecise(const unordered_set<string> & genome, const Maladie & maladie);
	// Mode d'emploi : Renvoie true si la maladie se trouve dans le génome de taille , sinon false
	//				   Le genome ne doit pas comporter 2 fois le même mot

	static const unordered_set<Maladie *> AnalyseGlobale(const unordered_set<string> & genome);
	// Mode d'emploi : Retourne un tableau associant les maladies avec leur présence (true) ou non (false) dans le génome de taille
	//				   Le genome ne doit pas comporter 2 fois le même mot

	Analyse & operator = (const Analyse &);
	// Mode d'emploi : opérateur d'affectation, non implémenté

	Analyse(const Analyse &);
	// Mode d'emploi : constructeur de copie, non implémenté

protected:

	Analyse();
	// Mode d'emploi : constructeur, non implémenté

	virtual ~Analyse();
	// Mode d'emploi : destructeur, non implémenté
};

#endif