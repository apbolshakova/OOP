#include <iostream>
#include <string>
#include <conio.h>

class IPAddress
{
	std::string IP;
public:
	IPAddress(std::string IP = nullptr) : IP(IP) {};
	std::string getIP() { return IPAddress::IP; }
};

class Network
{
	int Id;
	IPAddress **address;
	size_t size;
public:
	Network(int Id) : Id(Id), address(nullptr), size(0) {}
	~Network() { delete[] Network::address; }
	void addIPAdress(IPAddress *address);
	void printAdresses();
};

void Network::addIPAdress(IPAddress *address)
{
	if (!Network::address)
	{
		Network::address = new IPAddress *[1];
		Network::address[0] = address;
	}
	else
	{
		IPAddress **old = Network::address;
		Network::address = new IPAddress *[Network::size + 1];
		for (int i = 0; i < Network::size; i++) Network::address[i] = old[i];
		Network::address[Network::size] = address;
		delete[] old;
	}
	Network::size++;
}

void Network::printAdresses()
{
	std::cout << "Network " << Network::Id << ":" << std::endl;
	for (int i = 0; i < Network::size; i++)
	{
		std::cout << Network::address[i]->getIP() << std::endl;
	}
}

int main()
{
	IPAddress el1("1.1.1.1");
	IPAddress el2("2.2.2.2");
	IPAddress el3("3.3.3.3");
	IPAddress el4("4.4.4.4");
	IPAddress el5("5.5.5.5");

	Network net1(1);
	net1.addIPAdress(&el1);
	net1.addIPAdress(&el2);
	net1.addIPAdress(&el3);

	Network net2(2);
	net2.addIPAdress(&el3);
	net2.addIPAdress(&el4);
	net2.addIPAdress(&el5);

	net1.printAdresses();
	net2.printAdresses();

	_getch();
	return 0;
}