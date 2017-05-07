/*************************************************************************
Analyse - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Analyse> (fichier Analyse.h)  ----------//

#if ! defined ( ANALYSE_H )
#define ANALYSE_H

//--------------------------------------------------- Interfaces utilisées

struct Maladie {};//TODO : REPLACE TO "Maladie.h"

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Analyse>
//  La classe Analyse permet Permet d'annaliser un génome grace a 2 methode
//  d'annalyse. L'une permet de verifier la présence d'une maladie et
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
	// Mode d'emploi : [...]

	bool AnalyseGlobal(const unsigned char genome[], const Maladie maladie);
	// Mode d'emploi : [...]

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