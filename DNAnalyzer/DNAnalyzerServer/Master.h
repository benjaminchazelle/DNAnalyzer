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

//------------------------------------------------------------------------
// R�le de la classe <Master>
//  La classe Master contient diff�rentes m�thodes pour chacun des services
//  propos�s par le serveur. Elle a pour objectif de recup�rer les donn�es
//  du client et de lui repondre
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(CommunicationThread & thread);
	// Mode d'emploi : Interprete la requ�te pour invoquer le traitement qui lui est sp�cifique
	//                 La m�thode re�oit une instance de CommunicationThread <thread> pour formuler la r�ponse

	Master & operator = (const Master &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Master(const Master &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

protected:

	static void analysePrecise(const string & maladie, const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le r�sultat de l'analyse pr�cise de la maladie <maladie> sur une g�nome <genome>
	//                 La m�thode re�oit une instance de CommunicationThread <thread> pour formuler la r�ponse

	static void analyseGlobale(const string & genome, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le r�sultat de l'analyse globale sur une g�nome <genome>
	//                 La m�thode re�oit une instance de CommunicationThread <thread> pour formuler la r�ponse

	static void obtenirListeMaladies(CommunicationThread & thread);
	// Mode d'emploi : Retourne au client la liste des maladies connues par le serveur
	//                 La m�thode re�oit une instance de CommunicationThread <thread> pour formuler la r�ponse

	static void repondreErreurRequete(const string & error, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que sa requ�te contient une erreur <error> 
	//                 La m�thode re�oit une instance de CommunicationThread <thread> pour formuler la r�ponse

	static unordered_set<string> encoderGenome(const string & genome);
	// Mode d'emploi : Retourne l'ensemble des mots d'une g�nome <genome>
	// Exception "invalid_argument" : Si le g�nome <genome> est invalide (autre caract�re que [ATCG;])

	Master();
	// Mode d'emploi : Constructeur, non impl�ment�

	virtual ~Master();
	// Mode d'emploi : Destructeur, non impl�ment�
};

#endif