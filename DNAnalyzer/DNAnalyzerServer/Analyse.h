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
struct Maladie {};//TODO : REPLACE TO #include "Maladie.h"

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <Analyse>
//  La classe Analyse permet Permet d'annaliser un g�nome grace a 2 methode
//  d'annalyse. L'une permet de verifier la pr�sence d'une maladie et
//  l'autre de trouver les paladies potentielle
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
	// Mode d'emploi : Renvoit true si la maladie se trouve dans le g�nome de taille , sinon false

	unordered_map<const Maladie&, bool> AnalyseGlobal(unsigned int size, const unsigned char genome[]);
	// Mode d'emploi : Retourne un tableau associant les maladies avec leur pr�sence (true) ou non (false) dans le g�nome de taille

	Analyse & operator = (const Analyse &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Analyse(const Analyse &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	Analyse();
	// Mode d'emploi : constructeur

	virtual ~Analyse();
};

#endif