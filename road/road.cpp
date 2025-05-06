#include <iostream>
#include <vector>

class Vehicle
{
private:
	int speed;
	int position;
public:
	Vehicle(int s, int p) : speed(s), position(p) {}

	virtual void move(int distance) = 0;
	virtual std::string getType() = 0;

	int getSpeed() const { return speed; }
	int getPosition() const { return position; }
	void setPosition(int p) { position = p; }

	virtual ~Vehicle() = default;
};

class Car : public Vehicle
{
public:
	Car(int s, int p) : Vehicle(s, p) {}

	void move(int distance) override
	{
		setPosition(getPosition() + getSpeed() * distance * 2);
	}

	std::string getType() override
	{
		return "Car";
	}
};

class Truck : public Vehicle
{
public:
	Truck(int s, int p) : Vehicle(s, p) {}

	void move(int distance) override
	{
		setPosition(getPosition() + getSpeed() * distance * 1);
	}

	std::string getType() override
	{
		return "Truck";
	}
};

class Motorbike : public Vehicle
{
public:
	Motorbike(int s, int p) : Vehicle(s, p) {}

	void move(int distance) override
	{
		setPosition(getPosition() + getSpeed() * distance * 3);
	}

	std::string getType() override
	{
		return "Motorbike";
	}
};

class Road
{
private:
	int length;
	int width;
	int lanes;
	int speedLimit;
	std::vector<Vehicle*> vehicles;
public:
	Road(int l, int w, int n, int s) : length(l), width(w), lanes(n), speedLimit(s) {}
	void addVehicle(Vehicle* v)
	{
		if (vehicles.size() < lanes)
		{
			vehicles.push_back(v);
		}
		else
		{
			std::cout << "No more lanes available for new vehicles." << std::endl;
		}
	}

	void updateTraffic(int distance)
	{
		for (auto& vehicle : vehicles)
		{
			if (vehicle->getSpeed() <= speedLimit)
			{
				vehicle->move(distance);
			}
			else
			{
				std::cout << vehicle->getType() << " is over the speed limit!" << std::endl;
			}
		}
	}

	void displayVehicles()
	{
		for (auto& vehicle : vehicles)
		{
			std::cout << vehicle->getType() << " is at position: " << vehicle->getPosition() << std::endl;
		}
	}
	~Road()
	{
		for (auto& vehicle : vehicles)
		{
			delete vehicle;
		}
	}
};

int main()
{

}