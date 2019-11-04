#include <iostream>
#include <string>

const int maxID = 10;
const std::string invalidMemberName = "member";
const std::string errMessage = "Cannot perform this operation. ";

class Member
{
	bool valid; //to detect whether member exists or not
	std::string name;
	int membershipDuration;
public:
	Member(std::string name, int membershipDuration);
	bool updateMember(std::string name, int membershipDuration);
	bool extendMembership(int addition);
	void cancelMembership();
};

Member::Member(std::string name = invalidMemberName, int membershipDuration = 0)
{
	Member::valid = false;
	Member::name = name;
	Member::membershipDuration = membershipDuration;
	if (name != invalidMemberName)
	{
		Member::valid = true;
	}
}

bool Member::updateMember(std::string name = invalidMemberName, int membershipDuration = 0)
{
	if (Member::valid)
	{
		std::cout << errMessage << "Invalid number of month to add." << std::endl;
		return false;
	}
	//TODO
}

bool Member::extendMembership(int addition)
{
	if (addition < 0)
	{
		std::cout << errMessage << "Invalid number of month to add." << std::endl;
		return false;
	}
	Member::membershipDuration += addition;
	return true;
}

void Member::cancelMembership()
{
	Member::membershipDuration = 0;
}

int main()
{
	Member member[maxID + 1];
	//TODO handling
	return 0;
}