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
#include <unordered_set>

#include "CommunicationThread.h"
using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recupérer les donnée du
//  clientInfo et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(CommunicationThread & thread);
	// Mode d'emploi : Interprete la requête pour invoquer le traitement qui lui est spécifique

	Master & operator = (const Master &);
	// Mode d'emploi : Opérateur d'affectation, non implémenté

	Master(const Master &);
	// Mode d'emploi : Constructeur de copie, non implémenté

protected:

	static void analysePrecise(const string & maladie, const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au clientInfo le résultat de l'analyse précise demandée

	static void analyseGlobale(const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au clientInfo le résultat de l'analyse globale demandée

	static void obtenirListeMaladies(CommunicationThread & thread);
	// Mode d'emploi : Retourne au clientInfo la liste des maladies connues par le serveur

	static void repondreErreurRequete(const string & error, CommunicationThread & thread);
	// Mode d'emploi : Informe le clientInfo que sa requête est syntaxiquement invalide 

	static unordered_set<string> encoderGenome(const string & genome);
	// Mode d'emploi : Retourne l'ensemble des mots d'une génome

	Master();
	// Mode d'emploi : Constructeur, non implémenté

	virtual ~Master();
	// Mode d'emploi : Destructeur, non implémenté
};

#endif