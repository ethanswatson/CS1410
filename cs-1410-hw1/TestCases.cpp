#include <iostream>

#include "TestCases.hpp"

bool compareVectors(std::vector<Bug> one, std::vector<Bug> two)
{
	if (one.size() != two.size()) return false;

	bool equal = true;
	auto first = one.begin();
	auto second = two.begin();
	while (first != one.end())
	{
		if (first->getLegs() != second->getLegs() || first->getMass() != second->getMass())
		{
			equal = false;
		}
		first++;
		second++;
	}

	return equal;
}

bool testCase1(std::vector<Bug> bugs)
{
	std::vector<Bug> expected = {
		Bug(0, 2),
		Bug(8, 1),
		Bug(2, 3),
		Bug(8, 5),
		Bug(2, 7)
	};

	return compareVectors(bugs, expected);
}

bool testCase2(std::vector<Bug> bugs)
{
	std::vector<Bug> expected = {
		Bug(0, 2),
		Bug(8, 1),
		Bug(2, 3),
		Bug(8, 5),
		Bug(2, 7),
		Bug(9, 8),
		Bug(4, 4),
		Bug(0, 1)
	};

	return compareVectors(bugs, expected);
}

bool testCase3(std::vector<Bug> bugs)
{
	std::vector<Bug> expected = {
		Bug(9, 8),
		Bug(2, 7),
		Bug(8, 5),
		Bug(4, 4),
		Bug(2, 3),
		Bug(0, 2),
		Bug(8, 1),
		Bug(0, 1)
	};

	return compareVectors(bugs, expected);
}

bool testCase4(std::vector<Bug> bugs)
{
	std::vector<Bug> expected = {
		Bug(0, 2),
		Bug(8, 1),
		Bug(0, 1)
	};

	return compareVectors(bugs, expected);
}

void executeTest(std::function<bool(std::vector<Bug>)> testCase, std::vector<Bug> bugs, std::string label)
{
	std::cout << "Test Case - " << label << ": ";
	if (testCase(bugs))
	{
		std::cout << "Pass" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}
