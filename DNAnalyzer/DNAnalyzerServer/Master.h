/*************************************************************************
Master - Classe qui permet de g�rer le traitement sp�cifique d'une requ�te 
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//-------- Interface de la classe <Master> (fichier Master.h)  ---------//

#if ! defined ( MASTER_H )
#define MASTER_H

//--------------------------------------------------- Interfaces utilis�es

#include <string>
#include "CommunicationThread.h"
using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recup�rer les donn�e du
//  client et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(string & requete, CommunicationThread & thread);
	// Mode d'emploi : interprete la requ�te pour invoquer le traitement qui lui est sp�cifique

	Master & operator = (const Master &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Master(const Master &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	static void analysePrecise(string & requete, CommunicationThread & thread);
	// Mode d'emploi : retourne au client le r�sultat de l'analyse pr�cise demand�e

	static void analyseGlobale(string & requete, CommunicationThread & thread);
	// Mode d'emploi : retourne au client le r�sultat de l'analyse globale demand�e

	static void obtenirListeMaladies(string & requete, CommunicationThread & thread);
	// Mode d'emploi : retourne au client la liste des maladies connues par le serveur

	static void repondreServiceInconnu(string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client qu'aucun service n'existe pour traiter sa requ�te

	static void repondreErreurRequete(string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que sa requ�te est syntaxiquement invalide 

	Master();
	// Mode d'emploi : Constructeur, non implement�

	virtual ~Master();
	// Mode d'emploi : Destructeur, non implement�
};

#endif