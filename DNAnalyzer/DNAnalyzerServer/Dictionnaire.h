/*************************************************************************
Dictionnaire - Classe de stockage des donn�es de maladie
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Dictionnaire> (fichier Dictionnaire.h)  ----------//

#if ! defined ( DICTIONNAIRE_H )
#define DICTIONNAIRE_H

//--------------------------------------------------- Interfaces utilis�es

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

public:
	static Dictionnaire& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Dictionnaire

	Dictionnaire & operator = (const Dictionnaire &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Dictionnaire(const Dictionnaire &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	Dictionnaire();
	// Mode d'emploi : constructeur

	virtual ~Dictionnaire();
};

#endif