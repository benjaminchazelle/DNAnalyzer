/*************************************************************************
FileUtil - Classe de manupulation de fichiers
-------------------
début                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <FileUtil> (fichier FileUtil.h)   //

#if ! defined ( FILEUTIL_H )
#define FILEUTIL_H

#include <string>

using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <FileUtil>
//  La classe FileUtil permet d'implémenter la manipulation de fichiers en
//  vue d'une utilisation exclusive par les tests unitaires
//------------------------------------------------------------------------

class FileUtil
{
public:

	static string read(string file);
	// Mode d'emploi : Retourne le contenu d'un fichier <file>

	static bool write(string file, string content);
	// Mode d'emploi : Ecrase le contenu du fichier <file> avec le contenu <content>

	static bool unlink(string file);
	// Mode d'emploi : Supprime le fichier <file>

	static bool exists(string file);
	// Mode d'emploi : Détermine si le fichier <file> existe

protected:

	FileUtil();
	// Mode d'emploi : Constructeur, non implémenté

	~FileUtil();
	// Mode d'emploi : Destructeur, non implémenté
};

#endif