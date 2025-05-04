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
	int getPosition()  const { return position; }
	void setPosition(int p) { position = p; }
	
	virtual ~Vehicle() = default;
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
