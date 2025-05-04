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
};

int main()
{

}