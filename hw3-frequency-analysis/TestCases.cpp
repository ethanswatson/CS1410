#include <iostream>

#include "TestCases.hpp"

bool checkOrdered(std::vector<Record*>& input)
{
	bool ret = true;
	Record* pPrev = NULL;

	for (unsigned int i = 0; i < input.size() && ret; i++)
	{
		if ((input[i] == NULL) ||
			(pPrev != NULL && input[i]->getFrequency() < pPrev->getFrequency()))
		{
			ret = false;
		}

		pPrev = input[i];
	}

	return ret;
}

bool compareVectors(std::vector<Record*>& one, std::vector<Record*>& two)
{
	if (one.size() != two.size()) return false;

	bool equal = true;
	auto first = one.begin();
	auto second = two.begin();
	int index = 0;
	while (first != one.end() && equal)
	{
		if ((*first) == NULL || (*second) == NULL
			||(*first)->getFrequency() != (*second)->getFrequency()
			|| (*first)->getNumber() != (*second)->getNumber())
		{
			std::cout << "  Arrays differ at index " << index;

			if ((*first) != NULL && (*second) != NULL)
			{
				std::cout << ": " << (*first)->getNumber() << ", " << (*first)->getFrequency() << " vs " << (*second)->getNumber() << ", " << (*second)->getFrequency();
			}

			std::cout << std::endl;

			equal = false;
		}

		first++;
		second++;
		index++;
	}

	return equal;
}

bool SortTestCase1(std::function<void(std::vector<Record*>&)> sortFunc)
{
	bool passed = true;

	std::vector<Record*> input = {new Record(10), new Record(9, 2), new Record(8, 3), new Record(7, 4), new Record(6, 5), new Record(5, 6), new Record(4, 7), new Record(3, 8), new Record(2, 9), new Record(1, 10)};
	std::vector<Record*> expected = { new Record(1, 10), new Record(2, 9), new Record(3, 8), new Record(4, 7), new Record(5, 6), new Record(6, 5), new Record(7, 4), new Record(8, 3), new Record(9, 2), new Record(10)};

	sortFunc(input);
	passed = compareVectors(input, expected);
	cleanDynamicMemory(input);
	cleanDynamicMemory(expected);

	return passed;
}

bool SortTestCase2(std::function<void(std::vector<Record*>&)> sortFunc)
{
	bool passed = true;

	std::vector<Record*> input = { new Record(6, 4),  new Record(5, 7),  new Record(2, 8),  new Record(10, 9),  new Record(3, 10),  new Record(4, 11),  new Record(1, 12),  new Record(7, 13),  new Record(8, 14),  new Record(9, 15) };
	std::vector<Record*> expected = { new Record(9, 15), new Record(8, 14), new Record(7, 13), new Record(1, 12), new Record(4, 11), new Record(3, 10), new Record(10, 9),  new Record(2, 8), new Record(5, 7), new Record(6, 4) };

	sortFunc(input);
	passed = compareVectors(input, expected);
	cleanDynamicMemory(input);
	cleanDynamicMemory(expected);

	return passed;
}


bool FreqTestCase1(std::function<std::vector<Record*>(std::vector<unsigned int>&)> freqFunc)
{
	bool passed = true;

	std::vector<unsigned int> input = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 7, 6, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 1, 5, 4, 3, 2, 1, 4, 3, 2, 1, 3, 2, 1, 2, 1, 1};
	std::vector<Record*> expected = { new Record(1, 10), new Record(2, 9), new Record(3, 8), new Record(4, 7), new Record(5, 6), new Record(6, 5), new Record(7, 4), new Record(8, 3), new Record(9, 2), new Record(10)};

	std::vector<Record*> result = freqFunc(input);
	passed = compareVectors(result, expected);
	cleanDynamicMemory(result);
	cleanDynamicMemory(expected);

	return passed;
}

bool FreqTestCase2(std::function<std::vector<Record*>(std::vector<unsigned int>&)> freqFunc)
{
	bool passed = true;

	std::vector<unsigned int> input = {8, 10, 9, 7, 7, 8, 9, 7, 10, 7, 8, 3, 5, 6, 7, 9, 8, 9, 10, 6, 6, 7, 9, 8, 4, 4, 4, 4, 10, 8, 1, 1, 5, 9, 1, 7, 1, 2, 8, 1, 9, 8, 3, 7, 1, 9, 10, 5, 2, 8, 4, 3, 3, 3, 9, 1, 5, 3, 2, 3, 9, 4, 9, 3, 8, 4, 1, 10, 10, 7, 5, 9, 3, 2, 1, 7, 7, 4, 1, 8, 3, 5, 5, 8, 8, 2, 6, 10, 9, 7, 1, 8, 1, 4, 2, 9, 2, 7, 4, 10, 4, 9, 2};
	std::vector<Record*> expected = { new Record(1, 12),  new Record(2, 8),  new Record(3, 10),  new Record(4, 11),  new Record(5, 7),  new Record(6, 4),  new Record(7, 13),  new Record(8, 14),  new Record(9, 15),  new Record(10, 9)};

	std::vector<Record*> result = freqFunc(input);
	passed = compareVectors(result, expected);
	cleanDynamicMemory(result);
	cleanDynamicMemory(expected);

	return passed;
}

void executeSortTest(std::function<bool(std::function<void(std::vector<Record*>&)>)> testCase, std::function<void(std::vector<Record*>&)> sortFunc, std::string label)
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

void executeFreqTest(std::function<bool(std::function<std::vector<Record*>(std::vector<unsigned int>&)>)> testCase, std::function<std::vector<Record*>(std::vector<unsigned int>&)> sortFunc, std::string label)
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

void cleanDynamicMemory(std::vector<Record*>& rVector)
{
	//
	// TODO: Need to write the code to correctly clean up
	for (int i = 0; i < rVector.size(); i++)
	{
		delete rVector[i];
		rVector[i] = NULL;
	}
	// the dynamically allocated memory in the vector.
}
