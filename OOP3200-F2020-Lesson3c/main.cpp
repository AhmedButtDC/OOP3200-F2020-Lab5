//Name:             Ahmed Butt, Muzhda Ehsan
//Student ID:       100770449, 100770164
//Last Modified:    October 22, 2020
//File:				OOP3200-F2020-Lab5

#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <vector>


#include "Vector2D.h"

int main()
{
	try
	{
		/************************
		 *	DECLARATIONS
		 ************************/
		std::map<std::string, Vector2D<float>*> vector_map; //I'm the map
		auto* def = new Vector2D<float>(); //default (0, 0) point
		bool notFound = false;
		std::ifstream infile;
		std::string fileName;

		std::cout << "Enter the name of the file you wish to open: ";
		std::cin >> fileName;
		infile.open(fileName.c_str());
		
		if (infile.fail()) //if file doesn't exist
		{
			std::cout << "\n" << fileName << " could not be opened for input. Check that the file exists.\n";
		}
		else if (infile.peek() == std::ifstream::traits_type::eof()) //if file is empty
		{
			std::cout << "\n" << fileName << " is empty. Check that the file contains valid data in the correct format.\n";
		}
		else //file found and opened
		{
			float x, y, totalDistance = 0;
			std::string pointLabel;
			int totalPoints = 0;
			std::vector<std::string> pointLabels;
			
			//Check number of points and find total distance
			while (!infile.fail())
			{
				infile >> pointLabel;
				infile.ignore(1, ' ');
				infile.ignore(1, '(');
				infile >> x;
				infile.ignore(1, ',');
				infile.ignore(1, ' ');
				infile >> y;
				infile.ignore(1, ')');

				if (infile.eof()) //if end of file has been reached (prevent duplicate output and incrementation)
				{
					break;
				}

				//std::cout << pointLabel << " " << "(" << x << ", " << y << ")\n"; //show all points

				totalPoints++; //increment to keep track of total points

				pointLabels.resize(totalPoints);
				pointLabels.push_back(pointLabel);
				
				auto* temp_vector = new Vector2D<float>(x, y);
				vector_map[pointLabel] = temp_vector;
				
				totalDistance += Vector2D<float>::Distance(*def,*temp_vector); //add distances

				def = temp_vector; //change default Vector2D to old Vector2D so next increment finds distance between old and new
			}
			std::cout << "\n" << "The map contains " << totalPoints << " points for a total distance of " << totalDistance << ".\n";
			
			//User input loop
			std::string userInput;
			*def = Vector2D<float>();
			
			while (userInput != "quit")
			{
				std::cout << "\nEnter the label of the point you wish to go to (\"quit\" to end): ";
				std::cin >> userInput;

				for (const auto& current_vector : vector_map)
				{
					if (userInput == current_vector.first)
					{
						const auto x2 = current_vector.second->GetX(), y2 = current_vector.second->GetY();
						const auto distance = Vector2D<float>::Distance(*def,*current_vector.second);
						std::cout << "The distance between AA (0, 0) and " << current_vector.first << " (" << x2 << ", " << y2 << ")" << " is " << distance << ".\n";
						notFound = false;
						break;
					}
					else
					{
						notFound = true;
					}
				}
				if (notFound && userInput != "quit")
				{
					std::cout << "There is no point labeled \"" << userInput << "\" in the map.\n";
				}
			}
		}
	}
	catch(...)  // an exception was thrown
	{
		std::cout << "An error occurred at run-time: ";
	}

	std::cout << "\n--------------------------------------------------------------------";

	// END-OF-PROGRAM
	return 0;
}

