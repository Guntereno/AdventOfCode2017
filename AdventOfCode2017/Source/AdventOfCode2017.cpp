#include "Puzzles\Day1.h"
#include "Puzzles\Day2.h"
#include "Puzzles\Day3.h"

#include <iostream>

using namespace std;


template <class TPuzzle>
void Solve(int number)
{
    TPuzzle puzzle;
	std::cout << "Day " << number << endl;
    std::cout << puzzle.Solve() << endl;
	std::cout << endl;
}

#define SOLVE(n) Solve<Day ## n>(n);

int main()
{
    SOLVE(1)
	SOLVE(2)
	SOLVE(3)
	system("pause");
    return 0;
}

