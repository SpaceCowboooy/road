#include <iostream>
#include <vector>

class Vehicle
{
private:
	int type;
	int speed;
	int position;
public:
};

class Car : public Vehicle
{
};

class Truck : public Vehicle
{
};

class Motorbike : public Vehicle
{
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
