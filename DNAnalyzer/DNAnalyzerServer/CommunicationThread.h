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

	static CommunicationThread* instanceCommunicationThread;
	// Description : Instance singleton de CommunicationThread

public:
	static CommunicationThread& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de CommunicationThread

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	CommunicationThread();
	// Mode d'emploi : constructeur

	virtual ~CommunicationThread();
};

#endif