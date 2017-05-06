#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include <exception>
#include <cstring>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(DictionnaireTest)
	{
	public:
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
	};
}