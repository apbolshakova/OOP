#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <stack>

class TowersDomainError : public std::domain_error {};
class IncorrectMoveError : public std::logic_error {};
class EmptyTowerError : public std::logic_error {};

class Hanoi
{
	std::vector<std::stack<int>> tower[3];
public:
	//move
	//print
};