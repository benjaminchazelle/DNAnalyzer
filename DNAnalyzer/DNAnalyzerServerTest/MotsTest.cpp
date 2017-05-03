#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Mots.h"
#include <exception>
#include <cstring>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(MotsTest)
	{
	public:

		//ObtenirInstance
		TEST_METHOD(ObtenirInstance_NotNull)
		{
			// L'instance retournée ne doit pas être null
			Assert::AreNotEqual(&(Mots::ObtenirInstance()), (Mots*) nullptr);

		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retournée doit toujours être la même
			Assert::AreEqual(&(Mots::ObtenirInstance()), &(Mots::ObtenirInstance()));

		}

		//InsererMot
		TEST_METHOD(InsererMot_NullArgument)
		{
			// Envoyer un mot null doit lever une exception "invalid_argument"

			bool invalidArgumentException = false;

			try {
				Mots::ObtenirInstance().InsererMot(nullptr);
				Assert::Fail();
			}
			catch (invalid_argument const& e) {
				invalidArgumentException = true;
			}

			Assert::IsTrue(invalidArgumentException);

		}


		TEST_METHOD(InsererMot_KnownWord)
		{
			// Ajouter un mot déjà connu doit lever une exception "overflow_error"
			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			try {
				Mots::ObtenirInstance().InsererMot(mot);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}

			bool overflowErrorException = false;

			try {
				Mots::ObtenirInstance().InsererMot(mot);
				Assert::Fail();
			}
			catch (overflow_error const& e) {
				overflowErrorException = false;
			}

			Assert::IsTrue(overflowErrorException);
		}


		TEST_METHOD(InsererMot_UnkownWord)
		{
			// Ajouter un mot inconnu ne doit pas lever d'exception

			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			try {
				Mots::ObtenirInstance().InsererMot(mot);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
		}

		TEST_METHOD(InsererMot_GoodIndex)
		{
			// Inserer un mot inconnu doit renvoyer le bon index

			const unsigned int nombreMots = 3;

			char mots[nombreMots][5] = {
				{ 'A', 'C', 'G', 'T', '\0' },
				{ 'C', 'A', 'G', 'T', '\0' },
				{ 'C', 'A', 'T', 'G', '\0' }
			};

			for (unsigned int i = 0; i < nombreMots; i++) {

				try {
					unsigned int index = Mots::ObtenirInstance().InsererMot(mots[i]);

					Assert::AreEqual(index, i);
				}
				catch (std::exception const& e) {
					Assert::Fail();
				}

			}
		}

		//RecupererMot
		TEST_METHOD(RecupererMot_KnownWord)
		{
			// Un mot préalablement inseré, récupéré  par son index doit être le bon

			const unsigned int nombreMots = 3;

			char mots[nombreMots][5] = {
											{ 'A', 'C', 'G', 'T', '\0' },
											{ 'C', 'A', 'G', 'T', '\0' },
											{ 'C', 'A', 'T', 'G', '\0' }
			};

			for (unsigned int i = 0; i < nombreMots; i++) {

				try {
					Mots::ObtenirInstance().InsererMot(mots[i]);
				}
				catch (std::exception const& e) {
					Assert::Fail();
				}

			}

			for (unsigned int i = 0; i < nombreMots; i++) {

				try {
					char* motRecupere = Mots::ObtenirInstance().RecupererMot(i);

					Assert::IsTrue(strcmp(mots[i], motRecupere) == 0);
				}
				catch (std::exception const& e) {
					Assert::Fail();
				}

			}
		}

		TEST_METHOD(RecupererMot_UnkownWord)
		{
			// Récupérer un mot d'un index inconnu doit lever une exception "range_error"

			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			bool rangeErrorException = false;

			try {
				char* motRecupere = Mots::ObtenirInstance().RecupererMot(0);

				Assert::Fail();
			}
			catch (range_error const& e) {
				rangeErrorException = true;
			}

			Assert::IsTrue(rangeErrorException);
		}

		//ObtenirNombreMots
		TEST_METHOD(ObtenirNombreMots_Initial)
		{
			// Le nombre de mots connu d'une instance de Mots fraiche doit être égal à 0

			Assert::AreEqual(Mots::ObtenirInstance().ObtenirNombreMots(), (unsigned int)0);
		}

		TEST_METHOD(ObtenirNombreMots_AddUnkownWord)
		{

			// Le nombre de mots connu doit s'incrémenter si l'on ajoute un mot inconnu

			Assert::AreEqual(Mots::ObtenirInstance().ObtenirNombreMots(), (unsigned int)0);

			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			try {
				Mots::ObtenirInstance().InsererMot(mot);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}

			Assert::AreEqual(Mots::ObtenirInstance().ObtenirNombreMots(), (unsigned int)1);

		}


		TEST_METHOD(ObtenirNombreMots_AddKnownWord)
		{
			// Le nombre de mot doit rester le même si l'on ajoute un mot déjà connu

			Assert::AreEqual(Mots::ObtenirInstance().ObtenirNombreMots(), (unsigned int)0);

			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			try {
				Mots::ObtenirInstance().InsererMot(mot);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}

			Assert::AreEqual(Mots::ObtenirInstance().ObtenirNombreMots(), (unsigned int)1);

			try {
				Mots::ObtenirInstance().InsererMot(mot);
				Assert::Fail();
			}
			catch (std::exception const& e) {

			}

			Assert::AreEqual(Mots::ObtenirInstance().ObtenirNombreMots(), (unsigned int)1);

		}

		//ObtenirIndex
		TEST_METHOD(ObtenirIndex_NullArgument)
		{
			// Obtenir un mot via un index null doit lever une eception "invalid_argument"

			bool invalidArgumentException = false;

			try {
				Mots::ObtenirInstance().ObtenirIndex(nullptr);
				Assert::Fail();
			}
			catch (invalid_argument const& e) {
				invalidArgumentException = true;
			}

			Assert::IsTrue(invalidArgumentException);

		}

		TEST_METHOD(ObtenirIndex_UnkownWord)
		{
			// Obtenir l'index d'un mot inconnu doit lever une exception "range_error"

			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			bool rangeErrorException = false;

			try {
				Mots::ObtenirInstance().ObtenirIndex(mot);
				Assert::Fail();
			}
			catch (range_error const& e) {
				rangeErrorException = true;
			}

			Assert::IsTrue(rangeErrorException);
		}

		TEST_METHOD(ObtenirIndex_KnownWord)
		{
			// Obtenir l'index d'un mot connu ne doit pas lever d'exception

			char mot[] = { 'A', 'C', 'G', 'T', '\0' };

			try {
				Mots::ObtenirInstance().InsererMot(mot);
			}
			catch (std::exception const& e) {
				Assert::Fail();
			}

			try {
				Mots::ObtenirInstance().ObtenirIndex(mot);

			}
			catch (std::exception const& e) {
				Assert::Fail();
			}
		}

	};
}