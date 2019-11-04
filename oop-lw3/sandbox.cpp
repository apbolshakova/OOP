#include <iostream>
#include <string>

class FlightBooking {
public:
	FlightBooking(int id, int capacity, int reserved);
	void printStatus();
	bool reserveSeats(int number_ob_seats);
	bool cancelReservations(int number_ob_seats);
private:
	int id;
	int capacity;
	int reserved;
};
// ...
FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	FlightBooking::id = id;
	FlightBooking::capacity = capacity;
	FlightBooking::reserved = reserved;

	if (reserved * 100 / capacity > 105 || reserved < 0)
	{
		std::cout << "Bad input given. Reserved set to 0." << std::endl;
		FlightBooking::reserved = 0;
	}
}

void FlightBooking::printStatus()
{
	std::cout << "Flight " << FlightBooking::id << " : " << FlightBooking::reserved << " / " 
		<< FlightBooking::capacity << " (" << reserved * 100 / capacity << " % )" 
		<< std::endl;
}

bool FlightBooking::reserveSeats(int number_ob_seats)
{
	// try to add reservations and return 'true' on success
	// keep the limits in mind
	return false;
}

bool FlightBooking::cancelReservations(int number_ob_seats)
{
	// try to cancel reservations and return 'true' on success
	// keep the limits in mind
	return false;
}

int main() {
	int reserved = 0,
		capacity = 0;
	std::cout << "Provide flight capacity: ";
	std::cin >> capacity;

	std::cout << "Provide number of reserved seats: ";
	std::cin >> reserved;

	FlightBooking booking(1, capacity, reserved);

	std::cin.ignore(10000, '\n');
	std::string command = "";
	while (command != "quit")
	{
		booking.printStatus();
		std::cout << "What would you like to do?: ";
		std::getline(std::cin, command);
	}

	return 0;
}