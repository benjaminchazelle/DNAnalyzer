/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <CommunicationThread> (fichier CommunicationThread.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel

#include "CommunicationThread.h"

//----------------------------------------------------------------- PUBLIC


CommunicationThread & CommunicationThread::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((CommunicationThread*) nullptr);
}

//----------------------------------------------------------------- PRIVEE


CommunicationThread::CommunicationThread()
{
}


CommunicationThread::~CommunicationThread()
{
}
