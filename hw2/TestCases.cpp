#include <iostream>

#include "TestCases.hpp"

bool checkOrdered(std::vector<int> input)
{
	bool ret = true;

	for (unsigned int i = 0; i < input.size() && ret; i++)
	{
		if (i > 0 && input[i] < input[i - 1])
		{
			ret = false;
		}
	}

	return ret;
}

bool compareVectors(std::vector<int> one, std::vector<int> two)
{
	if (one.size() != two.size()) return false;

	bool equal = true;
	auto first = one.begin();
	auto second = two.begin();
	int index = 0;
	while (first != one.end() && equal)
	{
		if (*first != *second)
		{
			std::cout << "  Arrays differ at index " << index << ": " << *first << " vs " << *second << std::endl;
			equal = false;
		}

		first++;
		second++;
		index++;
	}

	return equal;
}

bool testCase1(std::function<SortStats(std::vector<int>&)> sortFunc)
{
	bool passed = true;

	std::vector<int> input = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	SortStats ss = sortFunc(input);
	passed = compareVectors(input, expected);
	std::cout << " " << printSortStats(ss).c_str() << std::endl;

	return passed;
}

bool testCase2(std::function<SortStats(std::vector<int>&)> sortFunc)
{
	bool passed = true;

	std::vector<int> input(unorderedVec[5]);

	SortStats ss = sortFunc(input);
	passed = checkOrdered(input);
	std::cout << " " << printSortStats(ss).c_str() << std::endl;

	return passed;
}

bool testCase3(std::function<SortStats(std::vector<int>&)> sortFunc)
{
	bool passed = true;
	std::vector<SortStats> statsVec;

	for (int i = 0; i < 10 && passed; i++)
	{
		std::vector<int> input(unorderedVec[i]);
		statsVec.push_back(sortFunc(input));

		if (input.size() != unorderedVec[i].size() || !checkOrdered(input))
		{
			passed = false;
			std::cout << "  Sort failed for count " << unorderedVec[i].size() << std::endl;
		}
	}

	if (passed)
	{
		SortStats prev = {0};

		for (unsigned int i = 0; i < statsVec.size() && passed; i++)
		{
			std::cout << "  " << printSortStats(statsVec[i]).c_str() << ", " << unorderedVec[i].size() << " item count" << std::endl;

			if (i > 0)
			{
				if (prev.time >= statsVec[i].time
					|| prev.compareCount >= statsVec[i].compareCount
					|| prev.swapCount >= statsVec[i].swapCount)
				{
					passed = false;
					std::cout << "  FAILED: values should be greater than previous" << std::endl;
				}
			}

			prev = statsVec[i];
		}
	}

	return passed;
}

bool testCaseCompare(std::function<SortStats(std::vector<int>&)> bubbleSortFunc, std::function<SortStats(std::vector<int>&)> selectSortFunc)
{
	bool passed = true;
	std::vector<SortStats> bsStatsVec;
	std::vector<SortStats> ssStatsVec;

	for (int i = 0; i < 10 && passed; i++)
	{
		std::vector<int> input(unorderedVec[i]);
		bsStatsVec.push_back(bubbleSortFunc(input));

		if (input.size() != unorderedVec[i].size() || !checkOrdered(input))
		{
			passed = false;
			std::cout << "  Sort failed on Bubble Sort for count " << unorderedVec[i].size() << std::endl;
		}
	}

	for (int i = 0; i < 10 && passed; i++)
	{
		std::vector<int> input(unorderedVec[i]);
		ssStatsVec.push_back(selectSortFunc(input));

		if (input.size() != unorderedVec[i].size() || !checkOrdered(input))
		{
			passed = false;
			std::cout << "  Sort failed on Selection Sort for count " << unorderedVec[i].size() << std::endl;
		}
	}

	if (passed)
	{
		for (unsigned int i = 0; i < ssStatsVec.size() && i < bsStatsVec.size() && passed; i++)
		{
			if (ssStatsVec[i].swapCount > bsStatsVec[i].swapCount)
			{
				passed = false;
				std::cout << "  FAILED: Selection Sort (" << ssStatsVec[i].swapCount << ") requires less swapping than Bubble (" << bsStatsVec[i].swapCount << ") with " << unorderedVec[i].size() << " items" << std::endl;
			}
			else
			{
				std::cout << "  Selection Sort (" << ssStatsVec[i].swapCount << "), Bubble (" << bsStatsVec[i].swapCount << ") with " << unorderedVec[i].size() << " items" << std::endl;
			}
		}
	}

	return passed;
}

void executeTest(std::function<bool(std::function<SortStats(std::vector<int>&)>, std::function<SortStats(std::vector<int>&)>)> testCase, std::function<SortStats(std::vector<int>&)> sortFuncA, std::function<SortStats(std::vector<int>&)> sortFuncB, std::string label)
{
	std::cout << "\nTest Case - " << label << ": Running" << std::endl;
	bool result = testCase(sortFuncA, sortFuncB);
	std::cout << "Test Case - " << label << ": ";

	if (result)
	{
		std::cout << "Pass" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void executeTest(std::function<bool(std::function<SortStats(std::vector<int>&)>)> testCase, std::function<SortStats(std::vector<int>&)> sortFunc, std::string label)
{
	std::cout << "\nTest Case - " << label << ": Running" << std::endl;
	bool result = testCase(sortFunc);
	std::cout << "Test Case - " << label << ": ";

	if (result)
	{
		std::cout << "Pass" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}
