#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerClient/Configuration.h"
#include "../TestUtil/FileUtil.h"

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerClientTest
{
	TEST_CLASS(ConfigurationTest)
	{
	protected:

		const string _fichierServeurs = "serveurs.test.config";

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			FileUtil::unlink(_fichierServeurs);

			Configuration::RafraichirInstance();
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			FileUtil::unlink(_fichierServeurs);
			
			Configuration::RafraichirInstance();			
		}

		//ObtenirInstance
		TEST_METHOD(ObtenirInstance_NotNull)
		{
			// L'instance retournée ne doit pas être null

			Assert::IsTrue(&Configuration::ObtenirInstance() != (Configuration*)NULL);

		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retournée doit toujours être la même

			Assert::IsTrue(&(Configuration::ObtenirInstance()) == &(Configuration::ObtenirInstance()));

		}

		//ObtenirListeServeur
		TEST_METHOD(ObtenirListeServeur_Empty)
		{
			// Fichier de configuration vide

			FileUtil::write(_fichierServeurs, "");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 0);
		}

		TEST_METHOD(ObtenirListeServeur_FileUnexists)
		{
			// Fichier inexistant

			Assert::IsFalse(FileUtil::exists(_fichierServeurs));

			Assert::IsFalse(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 0);
		}

		TEST_METHOD(ObtenirListeServeur_NotEmpty)
		{
			// Fichier à deux entrées

			FileUtil::write(_fichierServeurs, "127.0.0.1:80\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 2);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.1");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 80);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(1).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(1).port == 8080);
		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile1)
		{
			// Port non renseigné

			FileUtil::write(_fichierServeurs, "127.0.0.1");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 0);

		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile2)
		{
			// Port non renseigné

			FileUtil::write(_fichierServeurs, "127.0.0.180\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 1);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 8080);
		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile3)
		{
			// Port vide

			FileUtil::write(_fichierServeurs, "127.0.0.180:\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 1);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 8080);
		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile4)
		{
			// Port invalide

			FileUtil::write(_fichierServeurs, "127.0.0.180:NOTNUMBER\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 1);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 8080);
		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile5)
		{
			// Port > 65535

			FileUtil::write(_fichierServeurs, "127.0.0.180:9999999\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 1);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 8080);
		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile6)
		{
			// Port == 0

			FileUtil::write(_fichierServeurs, "127.0.0.180:0\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 1);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 8080);
		}


	};
}