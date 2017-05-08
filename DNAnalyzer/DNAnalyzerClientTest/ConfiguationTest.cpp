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
			// L'instance retourn�e ne doit pas �tre null

			Assert::IsTrue(&Configuration::ObtenirInstance() != (Configuration*)NULL);

		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retourn�e doit toujours �tre la m�me
			Assert::IsTrue(&(Configuration::ObtenirInstance()) == &(Configuration::ObtenirInstance()));

		}

		//ObtenirListeServeur
		TEST_METHOD(ObtenirListeServeur_Empty)
		{
			FileUtil::write(_fichierServeurs, "");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 0);
		}

		TEST_METHOD(ObtenirListeServeur_FileUnexists)
		{

			Assert::IsFalse(FileUtil::exists(_fichierServeurs));

			Assert::IsFalse(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 0);
		}

		TEST_METHOD(ObtenirListeServeur_NotEmpty)
		{
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
			FileUtil::write(_fichierServeurs, "127.0.0.1");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 0);

		}

		TEST_METHOD(ObtenirListeServeur_CorruptFile2)
		{
			FileUtil::write(_fichierServeurs, "127.0.0.180\n127.0.0.2:8080\n");

			Assert::IsTrue(Configuration::ObtenirInstance().ChargerFichier(_fichierServeurs));

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().size() == 1);

			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).host == "127.0.0.2");
			Assert::IsTrue(Configuration::ObtenirInstance().ObtenirListeServeur().at(0).port == 8080);
		}



	};
}