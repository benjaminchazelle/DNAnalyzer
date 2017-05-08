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
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance())!=(Dictionnaire*) nullptr);
		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retourn�e doit toujours �tre la m�me
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) == &(Dictionnaire::ObtenirInstance()));
		}
		TEST_METHOD(ObtenirMaladie_KnownMaladie) {
			Assert::Fail();// TODO
		}
		TEST_METHOD(ObtenirMaladie_UnKnownMaladie) {
			Assert::Fail();// TODO
		}
		TEST_METHOD(ObtenirMaladies_NoMaladies) {
			char motInexistant[] = "ATCGINEXISTANT";
			unsigned int indexMotInexistant = Mots::ObtenirInstance().InsererMot(motInexistant);
			const unordered_set<Maladie*> resultat = Dictionnaire::ObtenirInstance().ObtenirMaladies(indexMotInexistant);
			Assert::AreEqual((int)resultat.size(), 0);
		}
		TEST_METHOD(ObtenirMaladies_OneMaladies) {
			Assert::Fail();// TODO
		}
		TEST_METHOD(ObtenirMaladies_TwoMaladies) {
			Assert::Fail();// TODO
		}
		TEST_METHOD(ObtenirNomMaladies_EmptyDictionnaire) {
			Assert::Fail();// TODO
		}
		TEST_METHOD(ObtenirNomMaladies_NotEmptyDictionnaire) {
			Assert::Fail();// TODO
		}
	};
}