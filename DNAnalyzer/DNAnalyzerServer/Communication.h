/*************************************************************************
Communication - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Communication> (fichier Communication.h)  ----------//

#if ! defined ( COMMUNICATION_H )
#define COMMUNICATION_H

//--------------------------------------------------- Interfaces utilis�es

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <Communication>
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
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Communication(const Communication &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	Communication();
	// Mode d'emploi : constructeur

	virtual ~Communication();
};

#endif