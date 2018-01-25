#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>
#include <vector>

#include "Record.hpp"
#include "TestCases.hpp"

enum
{
    NOT_FOUND,
    INVALID
};

std::vector<unsigned int> readNumbersFromFile(std::string fileName)
{
    std::ifstream inputStream(fileName);

    if (!inputStream)
    {
        std::exit(EXIT_FAILURE);
    }

    unsigned int numbersToRead;
    inputStream >> numbersToRead;

    std::vector<unsigned int> numbers;
    for (int i = 0; i < numbersToRead; i++)
    {
        unsigned int num;
        inputStream >> num;
        numbers.push_back(num);
    }

    inputStream.close();

    return numbers;
}

int findRecord(std::vector<Record*>& rRecords, unsigned int numToFind)
{
    int begin = 0;
    int end = rRecords.size() - 1;
    int mid;

    while (begin <= end)
    {
        mid = (begin + end) / 2;

        if (rRecords[mid] != NULL)
        {
            if (numToFind == rRecords[mid]->getNumber())
            {
                return mid;
            }
            else if (numToFind > rRecords[mid]->getNumber())
            {
                begin = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
    }

    return NOT_FOUND;
}

bool isValidLocation(int index, int size)
{
    return index >= 0 && index < size;
}

int findIndexToPlace(std::vector<Record*> records, unsigned int numToPlace)
{
    int indexToPlace = 0;
    for (int i = 0; i < records.size(); i++)
    {
        int previous = INVALID;
        if (isValidLocation(i - 1, records.size()))
        {
            previous = records[i - 1]->getNumber();
        }

        int next = INVALID;
        if (isValidLocation(i + 1, records.size()))
        {
            next = records[i + 1]->getNumber();
        }

        if (previous == INVALID)
        {
            if (numToPlace < next)
            {
                indexToPlace = i;
                break;
            }
        }
        else if (next == INVALID)
        {
            if (numToPlace > previous)
            {
                indexToPlace = i;
                break;
            }
        }
        else
        {
            if (numToPlace > previous && numToPlace < next)
            {
                indexToPlace = i;
                break;
            }
        }
    }

    return indexToPlace;
}

std::vector<Record*> createVectorOfRecordsFromVectorOfNumbers(std::vector<unsigned int> numbers)
{
    std::vector<Record*> records;
    std::cout << numbers[55] << std::endl;

    for (int i = 0; i < numbers.size(); i++)
    {
        unsigned int current = numbers[i];
        int existingRecordIndex = findRecord(records, current);

        if (existingRecordIndex == NOT_FOUND)
        {
            int indexToPlace = findIndexToPlace(records, current);
            records.insert(records.begin() + indexToPlace, new Record(current));
        }
        else if (records[i] != NULL)
        {
            records[existingRecordIndex]->incrementFrequency();
        }
    }

    return records;
}

void sortByFrequency(std::vector<Record*>& rRecords)
{
    int startPos = 0;

    while (startPos < rRecords.size())
    {
        int currentMinIndex = startPos;

        for (int i = startPos; i < rRecords.size(); i++)
        {
            if (rRecords[i]->getFrequency() < rRecords[currentMinIndex]->getFrequency())
            {
                currentMinIndex = i;
            }
        }

        if (startPos != currentMinIndex)
        {
            std::swap(rRecords[startPos], rRecords[currentMinIndex]);
        }

        startPos++;
    }
}

void reportFrequencies(std::vector<Record*>& rRecords)
{
    for (int i = 0; i < rRecords.size(); i++)
    {
        printf("%u Numbers with a count of %u\n", rRecords[i]->getFrequency(), rRecords[i]->getNumber());
    }

    printf("There were %lu identified during the frequency analysis.\n", rRecords.size());
}

int main()
{
    std::vector<unsigned int> numbers = readNumbersFromFile("input.txt");
	std::vector<Record*> records = createVectorOfRecordsFromVectorOfNumbers(numbers);

	sortByFrequency(records);
	reportFrequencies(records);
	cleanDynamicMemory(records);	// Function stub found in TestCases.cpp

	// Test cases
	executeFreqTest(FreqTestCase1, createVectorOfRecordsFromVectorOfNumbers, "Frequency Test Case 1");
	executeFreqTest(FreqTestCase2, createVectorOfRecordsFromVectorOfNumbers, "Frequency Test Case 2");
	executeSortTest(SortTestCase1, sortByFrequency, "Sort Test Case 1");
	executeSortTest(SortTestCase2, sortByFrequency, "Sort Test Case 2");
	return 0;
}