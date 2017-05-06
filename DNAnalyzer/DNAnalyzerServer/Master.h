/*************************************************************************
Master - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Master> (fichier Master.h)  ----------//

#if ! defined ( MASTER_H )
#define MASTER_H

//--------------------------------------------------- Interfaces utilisées

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Master>
//  La classe Master permet [...
//  ...]
//------------------------------------------------------------------------


class Master
{
protected:

	static Master* instanceMaster;
	// Description : Instance singleton de Master

public:
	static Master& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Master

	Master & operator = (const Master &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Master(const Master &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	Master();
	// Mode d'emploi : constructeur

	virtual ~Master();
};

#endif