#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include "../DNAnalyzerServer/Mots.h"
#include <exception>
#include <unordered_set>
#include <cstring>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(DictionnaireTest)
	{
	public:
		TEST_METHOD_CLEANUP(CleanUp)
		{
			Mots::RafraichirInstance();
			DictionnaireTest::RafraichirInstance();
		}

		//ObtenirInstance
		TEST_METHOD(ObtenirInstance_NotNull)
		{
			// L'instance retourn�e ne doit pas �tre null
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance())!=(Dictionnaire*) nullptr);
		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retourn�e doit toujours �tre la m�me
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) == &(Dictionnaire::ObtenirInstance()));
		}
		TEST_METHOD(ObtenirMaladie_KnownMaladie) {

		}
		TEST_METHOD(ObtenirMaladie_UnKnownMaladie) {

		}
		TEST_METHOD(ObtenirMaladies_NoMaladies) {
			char motInexistant[] = "ATCGINEXISTANT";
			unsigned int indexMotInexistant = Mots::ObtenirInstance().InsererMot(motInexistant);
			const unordered_set<const Maladie*> resultat = Dictionnaire::ObtenirInstance().ObtenirMaladies(indexMotInexistant);
			Assert::AreEqual(resultat.size, 0);
		}
		TEST_METHOD(ObtenirMaladies_OneMaladies) {

		}
		TEST_METHOD(ObtenirMaladies_TwoMaladies) {

		}
		TEST_METHOD(ObtenirNomMaladies_EmptyDictionnaire) {

		}
		TEST_METHOD(ObtenirNomMaladies_NotEmptyDictionnaire) {

		}
	};
}