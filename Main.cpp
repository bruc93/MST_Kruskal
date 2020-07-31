#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "Edge.h"
#include <sstream>


void ReadValuesFromFile(const std::string& filepath, std::vector<std::string> &nodes, std::vector<std::string> &edges)
{
	std::ifstream file(filepath);
	std::string info;
	bool foundSpace = false;

	while (std::getline(file, info))
	{
		if(info.empty())
		{
			foundSpace = true;
		}
		else if (!foundSpace)
		{
			nodes.push_back(info);
		}
		else
		{
			edges.push_back(info);
		}
	}
}

void WriteValuesToFile(const std::vector<int>& numbers, const std::string& filepath = "Answer.txt")
{
	std::ofstream file(filepath);

	for (std::vector<int>::size_type i = 0; i < numbers.size() - 1; ++i)
		file << numbers[i] << std::endl;

	file << numbers.back();
}

Edge* CreateEdge(std::string _edges){

	std::cout << "i am here" << std::endl;

	std::istringstream ss(_edges);

	std::string substr;

	std::string point1;
	std::string point2;
	int cost = -999;

	int index = 0;
	while (getline(ss, substr, '\t'))
	{
		std::cout << substr << '\n' << std::endl;
		if (index == 0)
		{
			point1 = substr;
		}
		else if (index == 1)
		{
			point2 = substr;
		}
		else if (index == 2)
		{
			std::stringstream value(substr);

			value >> cost;
		}

		index++;
	}

	Edge *edge = new Edge(point1, point2, cost);

	return edge;
}

int main(int argc, char** argv)
{
	if (argc < 0)
	{
		std::cout << "To few arguments" << std::endl;
		return -1;
	}

	std::vector<std::string> edges;
	std::vector<std::string> nodes;

	ReadValuesFromFile(argv[1], nodes, edges);

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < nodes.size(); i++)
	{
		std::cout << nodes[i] << std::endl;
	}

	for (int i = 0; i < edges.size(); i++)
	{
		std::cout << edges[i] << std::endl;
	}


	Edge* edge1 = CreateEdge(edges[1]);

	std::cout << "Edges cost = " << edge1->getCost() << std::endl;
	std::cout << "Edges point1 = " << edge1->getP1() << std::endl;
	std::cout << "Edges point2 = " << edge1->getP2() << std::endl;

	/*
	switch (argv[2][0])
	{
	case '1':
		std::cout << "Running MergeSort...\n";
		funcSort.mergeSort(numbers);
		WriteValuesToFile(numbers, "OutputFile1.txt");
		break;
	case '2':
		std::cout << "Running HeapSort...\n";
		funcSort.heapSort(numbers);
		WriteValuesToFile(numbers, "OutputFile2.txt");
		break;
	case '3':
		std::cout << "Running Quicksort...\n";
		funcSort.quickSort(numbers);
		WriteValuesToFile(numbers, "OutputFile3.txt");
		break;
	default:
		std::cout << "Incorrect argument for choosing the sorting algorithm!" << std::endl;
		std::cout << "Aborting process!" << std::endl;
		return -1;
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Sorting took: " << elapsed_seconds.count() << " seconds" << std::endl;
	*/

	return 0;
}

