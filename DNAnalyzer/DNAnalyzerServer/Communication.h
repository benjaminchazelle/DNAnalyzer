/*************************************************************************
Communication - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Communication> (fichier Communication.h)  ----------//

#if ! defined ( COMMUNICATION_H )
#define COMMUNICATION_H

//--------------------------------------------------- Interfaces utilisées

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Communication>
//  La classe Communication permet [...
//  ...]
//------------------------------------------------------------------------


class Communication
{
protected:

	static Communication* instanceCommunication;
	// Description : Instance singleton de Communication

public:
	static Communication& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Communication

	Communication & operator = (const Communication &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Communication(const Communication &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	Communication();
	// Mode d'emploi : constructeur

	virtual ~Communication();
};

#endif