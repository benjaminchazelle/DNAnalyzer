/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- R�alisation de la classe <CommunicationThread> (fichier CommunicationThread.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

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
