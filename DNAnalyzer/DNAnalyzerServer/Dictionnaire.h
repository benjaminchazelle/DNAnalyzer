/*************************************************************************
Dictionnaire - Classe de stockage des données de maladie
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Dictionnaire> (fichier Dictionnaire.h)  ----------//

#if ! defined ( DICTIONNAIRE_H )
#define DICTIONNAIRE_H

//--------------------------------------------------- Interfaces utilisées

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

public:
	static Dictionnaire& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Dictionnaire

	Dictionnaire & operator = (const Dictionnaire &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Dictionnaire(const Dictionnaire &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	Dictionnaire();
	// Mode d'emploi : constructeur

	virtual ~Dictionnaire();
};

#endif