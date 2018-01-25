
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "TestCases.hpp"


void TestCases::runTestCases()
{
	std::cout << "[=================]" << std::endl;
	std::cout << "[-----------------] Running tests" << std::endl;
	std::cout << "[-----------------]" << std::endl;

	runTest(testPalindromeCase1, "Palindrome Simple Test");
	runTest(testPalindromeCase2, "Palindrome Complex Test");
	runTest(testWordSymmetricCase1, "Words Symmetric Simple Test");
	runTest(testWordSymmetricCase2, "Words Symmetric Complex Test");
	runTest(testSumCase1, "Vector Sum Simple Test");
	runTest(testSumCase2, "Vector Sum Complex Test");
	runTest(testMinCase1, "Vector Min Test 1");
	runTest(testMinCase2, "Vector Min Test 2");
	runTest(testSortCase1, "Vector Sort Simple Test");
	runTest(testSortCase2, "Vector Sort Complex Test");

	std::cout << "[-----------------]" << std::endl;
	std::cout << "[-----------------] Tests complete" << std::endl;
	std::cout << "[=================]" << std::endl;
}

void TestCases::runTest(std::function<bool(void)> testCase, std::string label)
{
	std::cout << "[ Running         ] " << label << std::endl;
	
	if (testCase())
	{
		std::cout << "[            PASS ]";
	}
	else
	{
		std::cout << "[          FAILED ]";
	}

	std::cout << " " << label << std::endl;
}

bool TestCases::testPalindromeCase1()
{
	std::string value = "radar";
	return isPalindrome(value, 0, value.length() - 1);
}

bool TestCases::testPalindromeCase2()
{
	bool ret = true;

	std::vector<std::pair<std::string, bool>> possiblePallindromes =
	{
		{ "radar", true },
		{ "racecar", true },
		{ "Pull up if I pull up", true },
		{ "No lemon no melon", true },
		{ "A dog a panic in a pagoda", true },
		{ "CS 1410 is my favorite class", false },
		{ "Rats live on no evil star", true },
		{ "My code compiles without bugs", false },
		{ "Never odd or even", true },
		{ "Now I see bees I won", true }
	};

	for (auto test : possiblePallindromes)
	{
		std::string collapsed = collapseSpaces(test.first);
		bool isOne = isPalindrome(collapsed, 0, collapsed.length() - 1);

		if (test.second != isOne)
		{
			std::cout << "  Expected that \"" << test.first << "\"";
			std::cout << ((test.second) ? " was" : " was not");
			std::cout << " a palindrome!" << std::endl;
			ret = false;
			break;
		}
	}

	return ret;
}

bool TestCases::testWordSymmetricCase1()
{
	bool ret = true;
	std::string input = "you are you";
	auto words = split(input);	// Split into words
	bool result = isWordSymmetric(words, 0, words.size() - 1);

	if (!result)
	{
		std::cout << "  Expected that \"" << input << "\"";
		std::cout << " is symmetric!" << std::endl;
		ret = false;
	}

	return ret;
}

bool TestCases::testWordSymmetricCase2()
{
	bool ret = true;
	std::vector<std::pair<std::string, bool>> possibleSymmetric =
	{
		{ "You can cage a swallow can't you but you can't swallow a cage can you", true },
		{ "Fall leaves as soon as leaves fall", true },
		{ "So patient a nurse to nurse a patient so", true },
		{ "I still say cS 1410 is my favorite class", false }
	};

	for (auto test : possibleSymmetric)
	{
		std::transform(test.first.begin(), test.first.end(), test.first.begin(), toupper);	// Capitalize all
		auto words = split(test.first);	// Split into words
		bool isOne = isWordSymmetric(words, 0, words.size() - 1);

		if (test.second != isOne)
		{
			std::cout << "Expected that \"" << test.first << "\"";
			std::cout << ((test.second) ? " was" : " was not");
			std::cout << " symmetric!" << std::endl;
			ret = false;
			break;
		}
	}

	return ret;
}

bool TestCases::testSumCase1()
{
	bool ret = true;
	std::vector<int> vec = {1, 2, 3, 4, 5};
	int expected = 15;
	int actual = vectorSum(vec, 0);

	if (expected != actual)
	{
		std::cout << "Invalid sum." << std::endl << "  Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
		ret = false;
	}

	return ret;
}

bool TestCases::testSumCase2()
{
	bool ret = true;
	std::vector<std::pair<std::vector<int>, int>> data =
	{
		{ { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }, 232 },
		{ { 1 }, 1 },
		{ {}, 0 }
	};

	for (auto&& test : data)
	{
		auto sum = vectorSum(test.first, 0);
		if (test.second != sum)
		{

			std::cout << "Invalid sum." << std::endl << "  Expected: " << test.second << std::endl << "  Actual: " << sum << std::endl;
			ret = false;
			break;
		}
	}

	return ret;
}

bool TestCases::testMinCase1()
{
	bool ret = true;
	std::vector<int> vec = {1, 2, 3, 4, 5};
	int expected = 1;
	int actual = vectorMin(vec, 0);

	if (expected != actual)
	{
		std::cout << "Invalid min." << std::endl << "  Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
		ret = false;
	}

	return ret;
}

bool TestCases::testMinCase2()
{
	bool ret = true;
	std::vector<std::pair<std::vector<int>, int>> data =
	{
		{ { 0, 1, 1, 2, 3, 5, 8, -42, 13, 21, 34, 55, 89 }, -42 },
		{ { 0 }, 0 },
		{ { 1000, 2, 1 }, 1 }
	};

	for (auto&& test : data)
	{
		auto sum = vectorMin(test.first, 0);
		if (test.second != sum)
		{

			std::cout << "Invalid min." << std::endl << "  Expected: " << test.second << std::endl << "  Actual: " << sum << std::endl;
			ret = false;
			break;
		}
	}

	return ret;
}

bool TestCases::testSortCase1()
{
	bool ret = true;
	std::vector<int> input = {5, 4, 3, 2, 1};
	std::vector<int> expected = {1, 2, 3, 4, 5};
	quickSort(input, 0, input.size() - 1);

	if (expected.size() != input.size())
	{
		std::cout << "Invalid sort length." << std::endl << "  Expected: " << expected.size() << std::endl << "  Actual: " << input.size() << std::endl;
		ret = false;
	}
	else
	{
		for (int i = 0; i < input.size() && i < expected.size(); i++)
		{
			if (expected[i] != input[i])
			{
				std::cout << "Invalid sort value at position " << static_cast<uint32_t>(i) << std::endl << "  Expected: " << expected[i] << std::endl;
				std::cout << "  Actual: " << input[i] << std::endl;
				ret = false;
			}
		}
	}

	return ret;
}

bool TestCases::testSortCase2()
{
	bool ret = true;
	std::srand(std::time(NULL));
	std::vector<int> data1(100000);
	std::vector<int> data2(100000);
	std::pair<int, int> extremes;

	extremes.first = std::numeric_limits<int>::max();
	extremes.second = std::numeric_limits<int>::min();

	for (auto&& item : data1)
	{
		item = std::rand();
		//
		// Update the known min/max values
		extremes.first = std::min(extremes.first, item);
		extremes.second = std::max(extremes.second, item);
	}
	for (auto&& item : data2)
	{
		item = std::rand();
	}

	auto start = std::chrono::high_resolution_clock::now();
	quickSort(data1, 0, data1.size() - 1);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeSort = end - start;
	std::cout << "Quicksort sort time    : " << timeSort.count() << " seconds" << std::endl;

	if (extremes.first != data1[0] || extremes.second != data1[data1.size() - 1])
	{
		// Make sure the smallest and largest values are legit.
		std::cout << "Invalid MIN/MAX" << std::endl;
		std::cout << "  Expected min, max: " << extremes.first << ", " << extremes.second;
		std::cout << "  Actual min, max: " << data1[0] << ", " << data1[data1.size() - 1] << std::endl;
	}

	start = std::chrono::high_resolution_clock::now();
	std::sort(data2.begin(), data2.end());
	end = std::chrono::high_resolution_clock::now();
	timeSort = end - start;
	std::cout << "std::sort sort time    : " << timeSort.count() << " seconds" << std::endl;

	return ret;
}
