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

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Analyse>
//  La classe Analyse permet [...
//  ...]
//------------------------------------------------------------------------


class Analyse
{
protected:

	static Analyse* instanceAnalyse;
	// Description : Instance singleton de Analyse

public:
	static Analyse& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Analyse

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