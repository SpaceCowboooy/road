#include "pch.h"
#include "CppUnitTest.h"
#include "../road/road.cpp"
#include <sstream>
#include <iostream>
#include <streambuf>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RoadSimulatorTests
{
	TEST_CLASS(UtilityFunctionsTests)
	{
	public:
		TEST_METHOD(ToLower_WorksCorrectly)
		{
			Assert::AreEqual(std::string("test"), toLower("TeSt"));
		}

		TEST_METHOD(ContainsHelp_WorksCorrectly)
		{
			Assert::IsTrue(containsHelp("please HELP me"));
			Assert::IsFalse(containsHelp("nothing here"));
		}
	};

	TEST_CLASS(VehicleTests)
	{
	public:
		TEST_METHOD(Car_Move)
		{
			Car car(10, 0);
			car.move(1);
			Assert::AreEqual(20, car.getPosition());
		}

		TEST_METHOD(Truck_Move)
		{
			Truck truck(5, 0);
			truck.move(2);
			Assert::AreEqual(10, truck.getPosition());
		}

		TEST_METHOD(Motorbike_Move)
		{
			Motorbike bike(4, 0);
			bike.move(2);
			Assert::AreEqual(24, bike.getPosition());
		}
	};

	TEST_CLASS(RoadTests)
	{
	private:
		class CinRedirect
		{
			std::streambuf* old;
		public:
			CinRedirect(std::istringstream& iss)
			{
				old = std::cin.rdbuf(iss.rdbuf());
			}
			~CinRedirect()
			{
				std::cin.rdbuf(old);
			}
		};

	public:
		TEST_METHOD(Road_Creation_And_AddVehicle)
		{
			std::istringstream input("100\n2\n50\n");
			CinRedirect redirect(input);

			Road road;

			road.addVehicle(std::make_unique<Car>(30, 0));
			Assert::IsFalse(road.isEmpty());
		}

		TEST_METHOD(Road_SpeedLimit_Exceeded)
		{
			std::istringstream input("100\n2\n40\n"); // speed limit = 40
			CinRedirect redirect(input);

			Road road;
			road.addVehicle(std::make_unique<Truck>(50, 0));

			std::ostringstream oss;
			std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

			road.updateTraffic(1);

			std::cout.rdbuf(oldCout);

			std::string output = oss.str();
			Assert::IsTrue(output.find("over the speed limit") != std::string::npos);
		}
	};
}