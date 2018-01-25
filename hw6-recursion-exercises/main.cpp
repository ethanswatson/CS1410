#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "TestCases.hpp"

std::string collapseSpaces(std::string s);
std::vector<std::string> split(std::string s);
bool isPalindrome(std::string word, int start, int end);
bool isWordSymmetric(const std::vector<std::string>& words, int start, int end);
long vectorSum(const std::vector<int>& data, unsigned int position);
int vectorMin(const std::vector<int>& data, unsigned int position);
void quickSort(std::vector<int>& data, int start, int end);
void selectionSort(std::vector<int>& data, int start);

int main()
{
	TestCases::runTestCases();
}

// ------------------------------------------------------------------
//
// Provided code to remove spaces from a string (and capitalize it)
//
// ------------------------------------------------------------------
std::string collapseSpaces(std::string s)
{
	s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
	std::transform(s.begin(), s.end(), s.begin(), toupper);	// Capitalize all
	return s;
}

// ------------------------------------------------------------------
//
// Solution string split code
//
// ------------------------------------------------------------------
std::vector<std::string> split(std::string s)
{
	std::istringstream is(s);
	std::vector<std::string> words;

	do
	{
		std::string word;
		is >> word;
		if (word.length() > 0)
		{
			words.push_back(word);
		}
	} while (is);

	return words;
}

bool isPalindrome(std::string word, int start, int end)
{
    if (word[start] != word[end])
    {
        return false;
    }
    else if (start >= end)
    {
        return true;
    }
    else
    {
        return isPalindrome(word, start + 1, end - 1);
    }
}

bool isWordSymmetric(const std::vector<std::string>& words, int start, int end)
{
    if (words[start] != words[end])
    {
        return false;
    }
    else if (start >= end)
    {
        return true;
    }
    else
    {
        return isWordSymmetric(words, start + 1, end - 1);
    }
}

long vectorSum(const std::vector<int>& data, unsigned int position)
{
    if (position >= data.size())
    {
        return 0;
    }
    else
    {
        return data[position] + vectorSum(data, position + 1);
    }
}

int vectorMin(const std::vector<int>& data, unsigned int position)
{
    if (position >= data.size())
    {
        return data[0];
    }
    else
    {
        int tmp = vectorMin(data, position + 1);
        if (data[position] <= tmp)
        {
            return data[position];
        }
        else
        {
            return tmp;
        }
    }
}

// ------------------------------------------------------------------
//
// Provided quicksort partition code
//
// ------------------------------------------------------------------
int partition(std::vector<int>& data, int start, int end)
{
	int middle = (start + end) / 2;
	std::swap(data[start], data[middle]);
	int pivotIndex = start;
	int pivotValue = data[start];
	for (int scan = start + 1; scan <= end; scan++)
	{
		if (data[scan] < pivotValue)
		{
			pivotIndex++;
			std::swap(data[scan], data[pivotIndex]);
		}
	}

	std::swap(data[pivotIndex], data[start]);

	return pivotIndex;
}

// ------------------------------------------------------------------
//
// Provided quicksort code
//
// ------------------------------------------------------------------
void quickSort(std::vector<int>& data, int start, int end)
{
    if (data.size() <= 10)
    {
        selectionSort(data, start);
    }
	else if (start < end)
	{
		int pivot = partition(data, start, end);
		quickSort(data, start, pivot - 1);
		quickSort(data, pivot + 1, end);
	}
}

void selectionSort(std::vector<int>& data, int start)
{
    if (start >= data.size() - 1)
    {
        return;
    }

    int smallestIndex = start;

    for (int i = start + 1; i < data.size(); i++)
    {
        if (data[i] < data[smallestIndex])
        {
            smallestIndex = i;
        }
    }

    std::swap(data[start], data[smallestIndex]);

    selectionSort(data, start + 1);
}