#include "pch.h"
#include "CppUnitTest.h"
#include"../homework2/homework2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int arr[] = { 1,2,3 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int expected = 6;
			int max_sum = max(arr, n);
			Assert::AreEqual(expected,max_sum);
		}
		TEST_METHOD(TestMethod2)
		{
			int arr[] = { -2,11,-4,13,-5,-2 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int expected = 20;
			int max_sum = max(arr, n);
			Assert::AreEqual(expected,max_sum);
		}
		TEST_METHOD(TestMethod3)
		{
			int arr[] = { 5,-1,-3,4,2 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int expected = 7;
			int max_sum = max(arr, n);
			Assert::AreEqual(expected,max_sum);
		}
		TEST_METHOD(TestMethod4)
		{
			int arr[] = { 1,2,3,4,5 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int expected = 15;
			int max_sum = max(arr, n);
			Assert::AreEqual(expected,max_sum);
		}
		TEST_METHOD(TestMethod5)
		{
			int arr[] = { -1,-2,-3 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int expected = 0;
			int max_sum = max(arr, n);
			Assert::AreEqual(expected,max_sum);
		}
	};
}
