/*************************************************************************
Master - Classe qui permet de gérer le traitement spécifique d'une requête 
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//-------- Interface de la classe <Master> (fichier Master.h)  ---------//

#if ! defined ( MASTER_H )
#define MASTER_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include "CommunicationThread.h"
using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recupérer les donnée du
//  client et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(string & requete, CommunicationThread & thread);
	// Mode d'emploi : interprete la requête pour invoquer le traitement qui lui est spécifique

	Master & operator = (const Master &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Master(const Master &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	static void analysePrecise(string & requete, CommunicationThread & thread);
	// Mode d'emploi : retourne au client le résultat de l'analyse précise demandée

	static void analyseGlobale(string & requete, CommunicationThread & thread);
	// Mode d'emploi : retourne au client le résultat de l'analyse globale demandée

	static void obtenirListeMaladies(string & requete, CommunicationThread & thread);
	// Mode d'emploi : retourne au client la liste des maladies connues par le serveur

	static void repondreServiceInconnu(string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client qu'aucun service n'existe pour traiter sa requête

	static void repondreErreurRequete(string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que sa requête est syntaxiquement invalide 

	Master();
	// Mode d'emploi : Constructeur, non implementé

	virtual ~Master();
	// Mode d'emploi : Destructeur, non implementé
};

#endif