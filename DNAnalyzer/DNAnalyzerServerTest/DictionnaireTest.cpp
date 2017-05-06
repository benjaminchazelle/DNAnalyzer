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
			// L'instance retournée ne doit pas être null
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance())!=(Dictionnaire*) nullptr);
		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retournée doit toujours être la même
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) == &(Dictionnaire::ObtenirInstance()));
		}
	};
}