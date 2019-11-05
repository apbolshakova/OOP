#include <iostream>
#include <string>
#include <exception> 
#include <stdexcept>
#include <vector>

class TowersDomainError : public std::domain_error {
public:
	explicit TowersDomainError(const std::string &msg);
};

TowersDomainError::TowersDomainError(const std::string &msg = "Invalid tower number.") : 
	std::domain_error(msg) {};

class IncorrectMoveError : public std::logic_error {
public:
	explicit IncorrectMoveError(const std::string &msg);
};

IncorrectMoveError::IncorrectMoveError(const std::string &msg = "Incorrect move.") :
	std::logic_error(msg) {};

class EmptyTowerError : public std::logic_error {
public:
	explicit EmptyTowerError(const std::string &msg);
};

EmptyTowerError::EmptyTowerError(const std::string &msg = "Source tower is empty.") :
	std::logic_error(msg) {};

class Tower
{
	std::vector<int> diskVector;
public:
	Tower(int diskNum);
	bool isEmpty() { return Tower::diskVector.empty(); }
	void addDisk(int disk);
	int peekDisk();
	void removeDisk();
	void printContent();
};

Tower::Tower(int diskNum = 0)
{
	for (int i = diskNum; i > 0; i--) Tower::diskVector.push_back(i);
}

void Tower::addDisk(int disk)
{
	if (!Tower::isEmpty() && Tower::diskVector.back() < disk) throw IncorrectMoveError();
	Tower::diskVector.push_back(disk);
}

int Tower::peekDisk()
{
	if (Tower::isEmpty()) throw EmptyTowerError();
	int disk = Tower::diskVector.back();
	return disk;
}

void Tower::removeDisk()
{
	if (Tower::isEmpty()) throw EmptyTowerError();
	Tower::diskVector.pop_back();
}

void Tower::printContent()
{
	if (Tower::isEmpty())
	{
		std::cout << " empty";
	}
	else
	{
		for (int i = 0; i < Tower::diskVector.size(); i++)
			std::cout << " " << Tower::diskVector[i];
	}
}

class Hanoi
{
	const int numOfDisks = 3;
	const int numOfTowers = 3;
	std::vector<Tower> tower;
public:
	Hanoi();
	void moveTower(int from, int to);
	void printTowers();
};

Hanoi::Hanoi()
{
	Hanoi::tower.push_back(Tower(Hanoi::numOfDisks));
	for (int i = 0; i < numOfTowers - 1; i++)
	{
		Hanoi::tower.push_back(Tower());
	}
}

void Hanoi::moveTower(int from, int to)
{
	if (from < 0 || numOfTowers <= from || to < 0 || numOfTowers <= to) 
		throw TowersDomainError();
	Hanoi::tower[to].addDisk(Hanoi::tower[from].peekDisk());
	Hanoi::tower[from].removeDisk();
}

void Hanoi::printTowers()
{	for (int i = 0; i < numOfTowers; i++)
	{
		std::cout << "tower_" << i + 1 << ":";
		Hanoi::tower[i].printContent();
		std::cout << std::endl;
	}
}

int main(void)
{
	Hanoi hanoi;

	std::string move = "";
	while (true)
	{
		hanoi.printTowers();
		try
		{
			std::getline(std::cin, move);
			if (move.size() < 2) throw std::invalid_argument("Invalid input.");
			hanoi.moveTower(move[0] - '0' - 1, move[1] - '0' - 1);
		}
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}