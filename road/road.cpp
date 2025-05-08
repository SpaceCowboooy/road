#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <sstream>

std::string toLower(const std::string& input)
{
    std::string output = input;
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);
    return output;
}

bool containsHelp(const std::string& input)
{
    std::string lowerInput = toLower(input);
    return lowerInput.find("help") != std::string::npos;
}

void printHelp()
{
    std::cout << "Help Menu:\n";
    std::cout << "First of all create a road!!!\n";
    std::cout << "Commands:\n";
    std::cout << "  create road - Create a new road\n";
    std::cout << "  add [car|truck|motorbike] [speed] - Add a new vehicle\n";
    std::cout << "  step - Move all vehicles by distance\n";
    std::cout << "  show - Show vehicle positions\n";
    std::cout << "  exit - Quit program\n";
}

class Vehicle
{
protected:
    int speed;
    int position;

public:
    Vehicle(int s, int p) : speed(s), position(p) {}

    virtual void move(int distance) = 0;
    virtual std::string getType() const = 0;

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

    std::string getType() const override
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

    std::string getType() const override
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

    std::string getType() const override
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
    std::vector<std::unique_ptr<Vehicle>> vehicles;

public:
    Road()
    {
        length = getValidatedInput("Enter road length: ");
        width = getValidatedInput("Enter road width: ");
        lanes = getValidatedInput("Enter number of lanes: ");
        speedLimit = getValidatedInput("Enter speed limit: ");
        std::cout << "Road created.\n";
    }

    void addVehicle(std::unique_ptr<Vehicle> v)
    {
        if (vehicles.size() < static_cast<size_t>(lanes))
        {
            vehicles.push_back(std::move(v));
        }
        else
        {
            std::cout << "No more lanes available for new vehicles.\n";
        }
    }

    void updateTraffic(int distance)
    {
        for (const auto& vehicle : vehicles)
        {
            if (vehicle->getSpeed() <= speedLimit)
            {
                vehicle->move(distance);
            }
            else
            {
                std::cout << vehicle->getType() << " is over the speed limit!\n";
            }
        }
    }

    void displayVehicles() const
    {
        for (const auto& vehicle : vehicles)
        {
            std::cout << vehicle->getType() << " is at position: " << vehicle->getPosition() << '\n';
        }
    }

    int getValidatedInput(const std::string& prompt)
    {
        int value;
        while (true)
        {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail() || value <= 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a positive integer.\n";
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }
};

int main()
{
    std::cout << "Road Simulation\n";
    std::cout << "Type 'help' for a list of commands.\n";

    std::string input;
    std::unique_ptr<Road> road = nullptr;

    while (true)
    {
        std::getline(std::cin, input);
        if (containsHelp(input))
        {
            printHelp();
        }
        else if (input == "exit")
        {
            break;
        }
        else if (input == "create road")
        {
            if (road)
            {
                std::cout << "Road already exists.\n";
            }
            else
            {
                road = std::make_unique<Road>();
            }
        }
        else if (!road)
        {
            std::cout << "You must create a road first using 'create road'.\n";
        }
        else if (input.find("add") == 0)
        {
            std::istringstream iss(input);
            std::string cmd, type;
            int speed;
            iss >> cmd >> type >> speed;

            if (iss.fail())
            {
                std::cout << "Invalid command format. Use: add [car|truck|motorbike] [speed]\n";
                continue;
            }

            if (type == "car")
            {
                road->addVehicle(std::make_unique<Car>(speed, 0));
            }
            else if (type == "truck")
            {
                road->addVehicle(std::make_unique<Truck>(speed, 0));
            }
            else if (type == "motorbike")
            {
                road->addVehicle(std::make_unique<Motorbike>(speed, 0));
            }
            else
            {
                std::cout << "Invalid vehicle type. Use 'car', 'truck', or 'motorbike'.\n";
            }
        }
        else if (input == "step")
        {
            int distance = road->getValidatedInput("Enter distance to move: ");
            road->updateTraffic(distance);
        }
        else if (input == "show")
        {
            road->displayVehicles();
        }
        else
        {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}
