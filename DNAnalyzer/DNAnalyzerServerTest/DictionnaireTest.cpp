#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include "../DNAnalyzerServer/Mots.h"
#include <exception>
#include <unordered_set>
#include <cstring>
#include <string>
#include "../TestUtil/FileUtil.h"

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(DictionnaireTest)
	{
	protected:

		const string _dicoTestFile = "data.test.dico";

	public:
		TEST_CLASS_INITIALIZE(initialize) {
			Mots::RafraichirInstance();
			Dictionnaire::RafraichirInstance();
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			Mots::RafraichirInstance();
			Dictionnaire::RafraichirInstance();
		}

		//ObtenirInstance
		TEST_METHOD(ObtenirInstance_NotNull)
		{
			// L'instance retourn�e ne doit pas �tre null
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) != (Dictionnaire*) nullptr);
		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retourn�e doit toujours �tre la m�me
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) == &(Dictionnaire::ObtenirInstance()));
		}

		TEST_METHOD(ChargerFichier_InexistantFile)
		{
			// Un fichier inexistant l�ve une exception "runtime_error"

			FileUtil::unlink(_dicoTestFile);

			bool runtimeErrorException = false;

			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::Fail();
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);

				runtimeErrorException = true;
			}

			Assert::IsTrue(runtimeErrorException);
						
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_OK)
		{
			// Syntaxe de fichier correcte

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);

				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size() == 2);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_EmptyWord)
		{
			// Mots vides ignor�s

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;;AA;CC;;GG;TT;;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);

				for (auto i : NAME.definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}

			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;;AA;CC;;GG;TT\r\nNAME2;AAAA;;;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);

				for (auto i : NAME.definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}

				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size() == 2);

				for (auto i : NAME2.definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_BadHeader)
		{
			// Le header du fichier doit �tre correcte, sinon quoi le fichier n'est pas charg�

			bool invalidArgumentException = false;

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "Mauvais header\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::Fail();				
			}
			catch (invalid_argument const& e) {
				UNREFERENCE_PARAMETER(e);

				invalidArgumentException = true;

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);
			}

			Assert::IsTrue(invalidArgumentException);

			invalidArgumentException = false;

			FileUtil::write(_dicoTestFile, "Mauvais header\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::Fail();
			}
			catch (invalid_argument const& e) {
				UNREFERENCE_PARAMETER(e);

				invalidArgumentException = true;

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);
			}

			Assert::IsTrue(invalidArgumentException);

		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_EndlComma)
		{
			// Les lignes peuvent se finir avec une virgule sans incidence

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT;\r\nNAME2;AAAA;CCCC;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size() == 2);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_NoLastCRLF)
		{
			// La derni�re ligne peut omettre \r\n

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size() == 2);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}
		}



		TEST_METHOD(ObtenirMaladie_KnownMaladie) {

			// Maladie connu

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size() == 4);
				Assert::IsTrue(NAME.nom == "NAME");

				Assert::IsTrue((*(Dictionnaire::ObtenirInstance().ObtenirMaladies(0).find(&NAME)))->nom == "NAME");
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}

		}

		TEST_METHOD(ObtenirMaladie_UnknownMaladie) {

			// Maladie inconnue l�ve une exception "range_error"

			bool rangeErrorException = false;

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				
				Dictionnaire::ObtenirInstance().ObtenirMaladie("MALADIE_INEXISTANTE");

				Assert::Fail();
			}
			catch (range_error const& e) {
				UNREFERENCE_PARAMETER(e);
				
				rangeErrorException = true;

			}
			
			Assert::IsTrue(rangeErrorException);

		}

		TEST_METHOD(ObtenirMaladie_KnownMaladies) {

			// Maladies connues

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);

				unordered_set<Maladie*> maladies = Dictionnaire::ObtenirInstance().ObtenirMaladies(0);

				Assert::IsTrue(maladies.size() == 2);

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME").nom == "NAME");

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2").nom == "NAME2");

			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}
		}
		TEST_METHOD(ObtenirMaladies_NoMaladies) {

			// Aucune maladie

			char motInexistant[] = "ATCGINEXISTANT";
			
			unsigned int indexMotInexistant = Mots::ObtenirInstance().InsererMot(motInexistant);
			const unordered_set<Maladie*> resultat = Dictionnaire::ObtenirInstance().ObtenirMaladies(indexMotInexistant);
			
			Assert::IsTrue(0 == resultat.size());
		}

		TEST_METHOD(ObtenirNomsMaladies_EmptyDictionnaire) {
			
			// Dictionnaire vide

			FileUtil::write(_dicoTestFile, "MA v1.0\r\n");

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			unsigned int inexistantMaladieId = 42;

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladies(inexistantMaladieId).size() == 0);

			FileUtil::write(_dicoTestFile, "");

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladies(inexistantMaladieId).size() == 0);

		}
	

	};
}