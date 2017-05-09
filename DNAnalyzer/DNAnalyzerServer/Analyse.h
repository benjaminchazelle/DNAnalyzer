/*************************************************************************
Analyse - Classe qui analyse la présence de maladies dans un génome
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Analyse> (fichier Analyse.h)  ----------//

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
protected:

	static Analyse* instanceAnalyse;
	// Description : Instance singleton de Analyse

public:
	static Analyse& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Analyse

	bool AnalysePrecise(unsigned int size,const unsigned char genome[], const Maladie maladie);
	// Mode d'emploi : Renvoit true si la maladie se trouve dans le génome de taille , sinon false

	unordered_map<Maladie, bool> AnalyseGlobal(unsigned int size, const unsigned char genome[]);
	// Mode d'emploi : Retourne un tableau associant les maladies avec leur présence (true) ou non (false) dans le génome de taille

	Analyse & operator = (const Analyse &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Analyse(const Analyse &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	Analyse();
	// Mode d'emploi : constructeur

	virtual ~Analyse();
};

#endif