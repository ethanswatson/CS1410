// Ethan Watson
// A02225762
// Section 2
// HW2

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <chrono>
#include <cmath>
#include <string>

#include "TestCases.hpp"
#include "SortStats.hpp"

void printVector(std::vector<int> rToPrint)
{
    for(int i = 0; i < rToPrint.size(); i++)
    {
        std::cout << rToPrint[i] << "   ";
    }

    std::cout << std::endl;
}

std::vector<int> generateVector(int size)
{
    std::vector<int> toFill(size);

    for (int i = 0; i < size; i++)
    {
        toFill.push_back(rand());
    }

    return toFill;
}

SortStats bubbleSort(std::vector<int>& rIntsToSort)
{
    SortStats stats;
    stats.compareCount = 0;
    stats.swapCount = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < rIntsToSort.size(); i++)
    {
        for (int j = 0; j < rIntsToSort.size() - 1 - i; j++)
        {
            if (rIntsToSort[j] > rIntsToSort[j + 1])
            {
                std::swap(rIntsToSort[j], rIntsToSort[j + 1]);
                stats.swapCount++;
            }
            stats.compareCount++;
        }
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = endTime - startTime;
    stats.time = totalTime.count();

    return stats;
}

SortStats selectionSort(std::vector<int>& rIntsToSort)
{
    SortStats stats;
    stats.compareCount = 0;
    stats.swapCount = 0;

    int startPos = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    while (startPos < rIntsToSort.size())
    {
        int currentMinIndex = startPos;

        for (int i = startPos; i < rIntsToSort.size(); i++)
        {
            if (rIntsToSort[i] < rIntsToSort[currentMinIndex])
            {
                currentMinIndex = i;
            }
            stats.compareCount++;
        }

        if (startPos != currentMinIndex)
        {
            std::swap(rIntsToSort[startPos], rIntsToSort[currentMinIndex]);
            stats.swapCount++;
        }

        startPos++;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = endTime - startTime;
    stats.time = totalTime.count();

    return stats;
}

// ------------------------------------------------------------------
//
// Run the test cases to help verify the code is correct.
//
// ------------------------------------------------------------------

void runTestCases()
{
	executeTest(testCase1, bubbleSort, "Bubble Sort: 10 items");
	executeTest(testCase2, bubbleSort, "Bubble Sort: 500 items");
	executeTest(testCase3, bubbleSort, "Bubble Sort: 100 to 1000 items");

	executeTest(testCase1, selectionSort, "Selection Sort: 10 items");
	executeTest(testCase2, selectionSort, "Selection Sort: 500 items");
	executeTest(testCase3, selectionSort, "Selection Sort: 100 to 1000 items");

	executeTest(testCaseCompare, bubbleSort, selectionSort, "Sort Compare Test");
}

void runSimulation()
{
    std::cout << "--- Timing Results ---" << std::endl << std::endl;

    for (int i = 100; i <= 1000; i += 100)
    {
        std::vector<int> bubbleSortVector = generateVector(i);
        std::vector<int> selectionSortVector = generateVector(i);

        SortStats bubbleStats = bubbleSort(bubbleSortVector);
        SortStats selectionStats = selectionSort(selectionSortVector);

        std::cout << std::left;
        std::cout << std::setw(20) << "Number of items" << ": " << i << std::endl;
        std::cout << std::setw(20) << "Bubble sort time" << ": " << bubbleStats.time << " seconds"<< std::endl;
        std::cout << std::setw(20) << "Selection sort time" << ": " << selectionStats.time
                  << " seconds" << std::endl << std::endl;
    }
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	runTestCases();
    runSimulation();

	return 0;
}
