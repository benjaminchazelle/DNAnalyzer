/*************************************************************************
Analyse - Classe qui analyse la pr�sence de maladies dans un g�nome
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//------- Interface de la classe <Analyse> (fichier Analyse.h)  --------//

#if ! defined ( ANALYSE_H )
#define ANALYSE_H

//--------------------------------------------------- Interfaces utilis�es

#include <unordered_map>
#include <unordered_set>
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

	static bool AnalysePrecise(const unordered_set<string> & genome, const Maladie & maladie);
	// Mode d'emploi : Renvoie true si la maladie <maladie> se trouve dans le g�nome <genome> , sinon false

	static const unordered_set<const Maladie *> AnalyseGlobale(const unordered_set<string> & genome);
	// Mode d'emploi : Retourne un tableau associant les maladies avec leur pr�sence (true) ou non (false) dans le g�nome <genome>

	Analyse & operator = (const Analyse &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Analyse(const Analyse &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

protected:

	Analyse();
	// Mode d'emploi : Constructeur, non impl�ment�

	virtual ~Analyse();
	// Mode d'emploi : Destructeur, non impl�ment�
};

#endif