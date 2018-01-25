#include <functional>
#include <string>
#include <vector>

#include "Record.hpp"

bool compareVectors(std::vector<Record*>& one, std::vector<Record*>& two);
bool SortTestCase1(std::function<void(std::vector<Record*>&)> sortFunc);
bool SortTestCase2(std::function<void(std::vector<Record*>&)> sortFunc);
bool FreqTestCase1(std::function<std::vector<Record*>(std::vector<unsigned int>&)> freqFunc);
bool FreqTestCase2(std::function<std::vector<Record*>(std::vector<unsigned int>&)> freqFunc);

void executeSortTest(std::function<bool(std::function<void(std::vector<Record*>&)>)> testCase, std::function<void(std::vector<Record*>&)> sortFunc, std::string label);
void executeFreqTest(std::function<bool(std::function<std::vector<Record*>(std::vector<unsigned int>&)>)> testCase, std::function<std::vector<Record*>(std::vector<unsigned int>&)> sortFunc, std::string label);

void cleanDynamicMemory(std::vector<Record*>& rVector);
