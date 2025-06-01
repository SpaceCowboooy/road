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
    std::cout << "\n=== Help Menu ===\n";
    std::cout << "Step-by-step instructions to use the simulator:\n";
    std::cout << "  1. create road             -> Create a new road (required before anything else)\n";
    std::cout << "  2. add [car|truck|motorbike] [speed] -> Add a vehicle with specified speed\n";
    std::cout << "  3. step                    -> Move all vehicles by given distance (based on their type and speed)\n";
    std::cout << "  4. show                    -> Show current vehicle positions on the road (visualized)\n";
    std::cout << "  5. exit                    -> Quit the program\n";
    std::cout << "\nVehicle multipliers:\n";
    std::cout << "  Car: speed * distance * 2\n";
    std::cout << "  Truck: speed * distance * 1\n";
    std::cout << "  Motorbike: speed * distance * 3\n";
    std::cout << "====================\n\n";
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
    int lanes;
    int speedLimit;
    std::vector<std::unique_ptr<Vehicle>> vehicles;

public:
    Road()
    {
        length = getValidatedInput("Enter road length: ");
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
                int oldPos = vehicle->getPosition();
                vehicle->move(distance);
                int newPos = vehicle->getPosition();

                std::cout << vehicle->getType() << " moved from " << oldPos << " to " << newPos << ".\n";

                if (newPos > length)
                {
                    std::cout << vehicle->getType() << " reached the end of the road and stopped.\n";
                    vehicle->setPosition(length);
                }
            }
            else
            {
                std::cout << vehicle->getType() << " is over the speed limit! (" << vehicle->getSpeed()
                    << " > " << speedLimit << ")\n";
            }
        }
    }


    void displayVehicles() const
    {
             for (const auto& vehicle : vehicles)
            {
                std::string line(length + 1, '-');
                int pos = std::min(vehicle->getPosition(), length);
                if (pos >= 0 && pos <= length)
                {
                    line[pos] = vehicle->getType()[0];
                }
                std::cout << vehicle->getType() << ": " << line << "\n";
            }
            std::cout << "===========================\n\n";      std::cout << "\n=== Road Visualization ===\n";
     
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

    int getLength() const { return length; }
	bool isEmpty() const { return vehicles.empty(); }
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
            if (road->isEmpty()) {
                std::cout << "No vehicles on the road. Add some first.\n";
                continue;
            }

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
