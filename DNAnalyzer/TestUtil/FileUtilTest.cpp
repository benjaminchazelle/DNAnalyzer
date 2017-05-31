#include "stdafx.h"
#include "CppUnitTest.h"
#include "FileUtil.h"

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUtil
{
	TEST_CLASS(FileUtilTest)
	{

	public:
		
		TEST_METHOD(FileUtil)
		{
			// Test de la classe FileUtil

			FileUtil::write("foo", "bar");

			Assert::IsTrue(FileUtil::exists("foo"));

			Assert::IsTrue(FileUtil::read("foo") == "bar");

			FileUtil::write("foo", "qwx");

			Assert::IsTrue(FileUtil::read("foo") == "qwx");

			FileUtil::unlink("foo");

			Assert::IsFalse(FileUtil::exists("foo"));

			Assert::IsTrue(FileUtil::read("foo") == "");

			
		}


	};
}