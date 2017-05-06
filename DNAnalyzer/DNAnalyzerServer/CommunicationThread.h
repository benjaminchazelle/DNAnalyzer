/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <CommunicationThread> (fichier CommunicationThread.h)  ----------//

#if ! defined ( COMMUNICATION_THREAD_H )
#define COMMUNICATION_THREAD_H

//--------------------------------------------------- Interfaces utilis�es

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <CommunicationThread>
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
	// Mode d'emploi : op�rateur d'affectation, non implement�

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	CommunicationThread();
	// Mode d'emploi : constructeur

	virtual ~CommunicationThread();
};

#endif