#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <sstream> 
#include <stdlib.h>

const int maxID = 10;
const std::string emptyMemberName = "member";
const std::string errMessage = "Cannot perform this operation. ";

class Member
{
	bool exist; // To detect whether member exists or not
	std::string name;
	int membershipDuration;
public:
	Member(std::string name, int membershipDuration);
	void updateMember(std::string name, int membershipDuration);
	void cleanMember();
	void extendMembership(int addition);
	void cancelMembership();
	void printInfo();
	bool isExists();
};

Member::Member(std::string name = emptyMemberName, int membershipDuration = 0)
{
	Member::exist = false;
	Member::name = name;
	Member::membershipDuration = membershipDuration;
	if (name != emptyMemberName)
	{
		Member::exist = true;
	}
}

void Member::updateMember(std::string name = emptyMemberName, int membershipDuration = 0)
{
	if (Member::exist) throw std::exception("Member with specified ID is already exist.");
	Member::exist = true;
	Member::name = name;
	Member::membershipDuration = membershipDuration;
}

void Member::cleanMember()
{
	if (!Member::exist) throw std::exception("Member with specified ID is not exist.");
	Member::exist = false;
	Member::name = emptyMemberName;
	Member::membershipDuration = 0;
}

void Member::extendMembership(int addition)
{
	if (!Member::exist) throw std::exception("Member with specified ID is not exist.");
	if (addition < 0) throw std::exception("Invalid membership duration is given.");
	Member::membershipDuration += addition;
	return;
}

void Member::cancelMembership()
{
	if (!Member::exist) throw std::exception("Member with specified ID is not exist.");
	Member::membershipDuration = 0;
}

void Member::printInfo()
{
	std::cout << Member::name << ", subscription valid for " << Member::membershipDuration << " months" << std::endl;
}

bool Member::isExists()
{
	return Member::exist;
}

std::vector<std::string> split(std::string str, char delimiter, int maxNumOfElements)
{
	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the string into a stream
	std::string tok;
	while (--maxNumOfElements && getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}
	getline(ss, tok);
	internal.push_back(tok);

	return internal;
}

void handleCommand(std::vector<Member>& member, std::string& command)
{
	std::vector<std::string> arg = split(command, ' ', 3);
	std::string action = arg[0];

	if (action == "create")
	{
		if (arg.size() < 3) throw std::exception("Not enough arguments.");
		int id = std::stoi(arg[1]);
		if (id <= 0 || id > maxID) throw std::exception("Invalid member ID is given.");
		std::string name = arg[2];
		member[id].updateMember(name);
	}
	if (action == "delete")
	{
		if (arg.size() < 2) throw std::exception("Not enough arguments.");
		int id = std::stoi(arg[1]);
		if (id <= 0 || id > maxID) throw std::exception("Invalid member ID is given.");
		member[id].cleanMember();
	}
	if (action == "extend")
	{
		if (arg.size() < 3) throw std::exception("Not enough arguments.");
		int id = std::stoi(arg[1]);
		if (id <= 0 || id > maxID) throw std::exception("Invalid member ID is given.");
		int monthsNum = std::stoi(arg[2]);
		member[id].extendMembership(monthsNum);
	}
	if (action == "cancel")
	{
		if (arg.size() < 2) throw std::exception("Not enough arguments.");
		int id = std::stoi(arg[1]);
		if (id <= 0 || id > maxID) throw std::exception("Invalid member ID is given.");
		member[id].cancelMembership();
	}
}

void printMembers(std::vector<Member> member)
{
	bool noMembers = true;
	for (int i = 0; i < member.size(); i++)
	{
		if (member[i].isExists())
		{
			std::cout << "Member " << i << " : ";
			member[i].printInfo();
			noMembers = false;
		}
	}
	if (noMembers) std::cout << "No members in the system" << std::endl;
}

int main()
{
	std::vector<Member> member(maxID + 1);
	std::string command = "";
	do
	{
		printMembers(member);
		std::getline(std::cin, command);
		try 
		{ 
			handleCommand(member, command); 
		}
		catch (std::exception &e)
		{
			std::cout << errMessage << e.what() << std::endl;
		}
		std::cout << std::endl;
	} while (command != "quit");
	return 0;
}
