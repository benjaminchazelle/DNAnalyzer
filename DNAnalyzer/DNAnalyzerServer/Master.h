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
#include <unordered_set>

#include "CommunicationThread.h"
using namespace std;

enum Route {ANALYSE_PRECISE, ANALYSE_GLOBALE, LISTE_MALDIES, SERVICE_INCONNU, ERREUR_SYNTAXE};

//------------------------------------------------------------------------
// R�le de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recup�rer les donn�e du
//  clientInfo et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(CommunicationThread & thread);
	// Mode d'emploi : Interprete la requ�te pour invoquer le traitement qui lui est sp�cifique

	Master & operator = (const Master &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Master(const Master &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

protected:

	static Route routerRequete(const string & serviceLigne);
	// Mode d'emploi : Renvoie le traitement � invoquer en fonction de la requ�te

	static void analysePrecise(const string & maladie, const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au clientInfo le r�sultat de l'analyse pr�cise demand�e

	static void analyseGlobale(const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au clientInfo le r�sultat de l'analyse globale demand�e

	static void obtenirListeMaladies(CommunicationThread & thread);
	// Mode d'emploi : Retourne au clientInfo la liste des maladies connues par le serveur

	static void repondreErreurRequete(const string & error, CommunicationThread & thread);
	// Mode d'emploi : Informe le clientInfo que sa requ�te est syntaxiquement invalide 

	Master();
	// Mode d'emploi : Constructeur, non impl�ment�

	virtual ~Master();
	// Mode d'emploi : Destructeur, non impl�ment�
};

#endif