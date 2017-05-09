/*************************************************************************
Analyse - Classe qui analyse la pr�sence de maladies dans un g�nome
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Analyse> (fichier Analyse.h)  ----------//

#if ! defined ( ANALYSE_H )
#define ANALYSE_H

//--------------------------------------------------- Interfaces utilis�es

#include <unordered_map>
#include "Maladie.h"

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <Analyse>
//  La classe Analyse permet d'analyser un g�nome gr�ce � 2 m�thodes d'analyse.
//  L'un permet de v�rifier la pr�sence d'une seule maladie, l'autre de trouver 
//  l'ensemble des potentielles maladies
//------------------------------------------------------------------------


class Analyse
{
public:

	static bool AnalysePrecise(string & genome, const Maladie maladie);
	// Mode d'emploi : Renvoit true si la maladie se trouve dans le g�nome de taille , sinon false

	static unordered_map<Maladie, bool> AnalyseGlobale(string & genome);
	// Mode d'emploi : Retourne un tableau associant les maladies avec leur pr�sence (true) ou non (false) dans le g�nome de taille

	Analyse & operator = (const Analyse &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Analyse(const Analyse &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	Analyse();
	// Mode d'emploi : constructeur, non implement�

	virtual ~Analyse();
	// Mode d'emploi : destructeur, non implement�
};

#endif