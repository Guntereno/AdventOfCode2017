#include "Puzzles\Day10.h"

#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <istream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "Common\CsvParser.h"
#include "Common\Parsing.h"


Day10::Day10()
{

}

Day10::~Day10()
{

}

std::vector<unsigned char> BuildSparseHash(const std::vector<int>& lengths, int listLen, int& current, int& skip)
{
	std::vector<unsigned char> hash(listLen);
	std::iota(hash.begin(), hash.end(), 0);

	for (int length : lengths)
	{
		int numSwaps = length / 2;
		for (int i = 0; i < numSwaps; ++i)
		{
			unsigned char a = (current + i) % listLen;
			unsigned char b = (current + ((length - 1) - i)) % listLen;
			std::swap(hash[a], hash[b]);
		}

		current += length + skip;

		++skip;
	}

	current = current % listLen;

	return hash;
}

static const char* kInputFile = "Day10Input.txt";

std::vector<int> GetLengthsPart1()
{
	std::ifstream input("Day10Input.txt");
	std::vector<int> result;
	
	std::string line;
	while (getline(input, line, ','))
	{
		result.push_back(std::stoi(line));
	}

	return result;
}

std::vector<int> GetLengthsPart2()
{
	//std::ifstream input("Day10Input.txt");
	std::stringstream input("");
	std::vector<int> result;

	char c;
	while (input.get(c))
	{
		result.push_back((int)c);
	}

	std::vector<int> suffix = { 17, 31, 73, 47, 23 };
	result.insert(std::end(result), std::begin(suffix), std::end(suffix));

	return result;
}

std::string BuildDenseHash(const std::vector<unsigned char>& sparseHash)
{
	const int kBlockSize = 16;
	assert((sparseHash.size() % kBlockSize) == 0);
	
	size_t blockCount = sparseHash.size() / kBlockSize;

	std::vector<unsigned char> hash(blockCount);
	for (int curBlock = 0; curBlock < blockCount; ++curBlock)
	{
		hash[curBlock] = sparseHash[kBlockSize * curBlock];
		for (int curBlockMember = 1; curBlockMember < kBlockSize; ++curBlockMember)
		{
			int sparseIndex = (curBlock * kBlockSize) + curBlockMember;
			hash[curBlock] ^= sparseHash[sparseIndex];
		}
	}

	std::stringstream resultStream;
	for (unsigned char ch : hash)
	{
		resultStream << std::setfill('0') << std::setw(2) << std::hex << (int)ch;
	}

	assert(resultStream.str().size() == blockCount * 2);

	return resultStream.str();
}

std::string Day10::Solve()
{
	const int kListSize = 256;
	int solution1 = 0;
	std::string solution2 = "";

	//{
	//	std::vector<int> lengths = GetLengthsPart1();
	//	int current = 0;
	//	int skip = 0;
	//	std::vector<unsigned char> hash = BuildSparseHash(lengths, kListSize, current, skip);
	//	solution1 = hash[0] * hash[1];
	//}

	{
		std::vector<int> lengths = GetLengthsPart2();
		const int kNumRounds = 64;
		int current = 0;
		int skip = 0;
		std::vector<unsigned char> sparseHash;
		for (int i = 0; i < kNumRounds; ++i)
		{
			sparseHash = BuildSparseHash(lengths, kListSize, current, skip);
			std::cout << i << std::endl;
		}

		std::cout << "[";
		for (unsigned char c : sparseHash)
		{
			std::cout << (int)c << ", ";
		}
		std::cout << "]" << std::endl;

		solution2 = BuildDenseHash(sparseHash);
	}

	std::stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << std::endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}
