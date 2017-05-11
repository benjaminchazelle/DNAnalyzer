#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include "../DNAnalyzerServer/Mots.h"
#include <exception>
#include <unordered_set>
#include <cstring>
#include <string>
#include "../TestUtil/FileUtil.h"

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
			// L'instance retournée ne doit pas être null
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) != (Dictionnaire*) nullptr);
		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retournée doit toujours être la même
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) == &(Dictionnaire::ObtenirInstance()));
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_Cool)
		{
			// Syntaxe de fichier correcte

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size == 2);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_EmptyWord)
		{
			// Mots vides non sauvegardés

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;;AA;CC;;GG;TT;;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);

				for (auto i : NAME.definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}

			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;;AA;CC;;GG;TT\r\nNAME2;AAAA;;;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);

				for (auto i : NAME.definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}

				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size == 2);

				for (auto i : NAME2.definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_IgnoreFirstLine)
		{
			// Pemière ligne du fichier sans importance

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "FIRST LINE IGNORED\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}


			FileUtil::write(_dicoTestFile, "FIRST LINE IGNORED\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size == 2);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}

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
				Assert::IsTrue(NAME.definition.size == 4);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT;\r\nNAME2;AAAA;CCCC;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size == 2);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_NoLastCRLF)
		{
			// La dernière ligne peut omettre \r\n

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}


			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				Maladie NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME.definition.size == 4);
				Maladie NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2.definition.size == 2);
			}
			catch (std::exception const& e) {
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
				Assert::IsTrue(NAME.definition.size == 4);
				Assert::IsTrue(NAME.nom == "NAME");

				Assert::IsTrue((*(Dictionnaire::ObtenirInstance().ObtenirMaladies(0).find(&NAME)))->nom == "NAME");
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
			
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
				Assert::Fail();
			}
		}
		TEST_METHOD(ObtenirMaladies_NoMaladies) {

			// Aucune maladie

			char motInexistant[] = "ATCGINEXISTANT";
			unsigned int indexMotInexistant = Mots::ObtenirInstance().InsererMot(motInexistant);
			const unordered_set<Maladie*> resultat = Dictionnaire::ObtenirInstance().ObtenirMaladies(indexMotInexistant);
			Assert::AreEqual((int)resultat.size(), 0);
		}

		TEST_METHOD(ObtenirNomMaladies_EmptyDictionnaire) {
			
			// Dictionnaire vide

			FileUtil::write(_dicoTestFile, "MA v1.0\r\n");

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladies(42).size() == 0);

			FileUtil::write(_dicoTestFile, "");

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladies(42).size() == 0);

		}
	

	};
}