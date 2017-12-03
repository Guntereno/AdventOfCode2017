#include "Puzzles\Day1.h"
#include "Puzzles\Day2.h"

#include <iostream>

using namespace std;


template <class TPuzzle>
void Solve()
{
    TPuzzle puzzle;
    std::cout << puzzle.Solve() << endl;
}

int main()
{
    Solve<Day1>();
	Solve<Day2>();
	system("pause");
    return 0;
}

