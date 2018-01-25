#ifndef _TEST_CASES_HPP
#define _TEST_CASES_HPP

#include <functional>
#include <string>
#include <vector>

class TestCases
{
	public:
		static void runTestCases();

		static bool testPalindromeCase1();
		static bool testPalindromeCase2();
		static bool testWordSymmetricCase1();
		static bool testWordSymmetricCase2();
		static bool testSumCase1();
		static bool testSumCase2();
		static bool testMinCase1();
		static bool testMinCase2();
		static bool testSortCase1();
		static bool testSortCase2();


	private:
		static void runTest(std::function<bool(void)> testCase, std::string label);

};

extern std::string collapseSpaces(std::string s);
extern std::vector<std::string> split(std::string s);
extern bool isPalindrome(std::string word, int start, int end);
extern bool isWordSymmetric(const std::vector<std::string>& words, int start, int end);
extern long vectorSum(const std::vector<int>& data, unsigned int position);
extern int vectorMin(const std::vector<int>& data, unsigned int position);
extern void quickSort(std::vector<int>& data, int start, int end);

#endif // _TEST_CASES_HPP
