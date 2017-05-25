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
//  La classe Master contient différentes méthodes pour chacun des services
//  proposés par le serveur. Elle a pour objectif de recupérer les données
//  du client et de lui repondre
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(CommunicationThread & thread);
	// Mode d'emploi : Interprete la requête pour invoquer le traitement qui lui est spécifique
	//                 La méthode reçoit une instance de CommunicationThread <thread> pour formuler la réponse

	Master & operator = (const Master &);
	// Mode d'emploi : Opérateur d'affectation, non implémenté

	Master(const Master &);
	// Mode d'emploi : Constructeur de copie, non implémenté

protected:

	static void analysePrecise(const string & maladie, const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le résultat de l'analyse précise de la maladie <maladie> sur une génome <genome>
	//                 La méthode reçoit une instance de CommunicationThread <thread> pour formuler la réponse

	static void analyseGlobale(const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le résultat de l'analyse globale sur une génome <genome>
	//                 La méthode reçoit une instance de CommunicationThread <thread> pour formuler la réponse

	static void obtenirListeMaladies(CommunicationThread & thread);
	// Mode d'emploi : Retourne au client la liste des maladies connues par le serveur
	//                 La méthode reçoit une instance de CommunicationThread <thread> pour formuler la réponse

	static void repondreErreurRequete(const string & error, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que sa requête contient une erreur <error> 
	//                 La méthode reçoit une instance de CommunicationThread <thread> pour formuler la réponse

	static unordered_set<string> encoderGenome(const string & genome);
	// Mode d'emploi : Retourne l'ensemble des mots d'une génome <genome>
	// Exception "invalid_argument" : Si le génome <genome> est invalide (autre caractère que [ATCG;])

	Master();
	// Mode d'emploi : Constructeur, non implémenté

	virtual ~Master();
	// Mode d'emploi : Destructeur, non implémenté
};

#endif