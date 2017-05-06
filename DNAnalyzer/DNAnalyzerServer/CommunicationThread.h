/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <CommunicationThread> (fichier CommunicationThread.h)  ----------//

#if ! defined ( COMMUNICATION_THREAD_H )
#define COMMUNICATION_THREAD_H

//--------------------------------------------------- Interfaces utilisées

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <CommunicationThread>
//  La classe CommunicationThread permet [...
//  ...]
//------------------------------------------------------------------------


class CommunicationThread
{
protected:

public:
	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implementé

	CommunicationThread();
	// Mode d'emploi : constructeur

	virtual ~CommunicationThread();
};

#endif