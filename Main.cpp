#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "Edge.h"
#include <sstream>
#include "Disjset.h"


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

Edge CreateEdge(std::string _edges){
	std::istringstream ss(_edges);

	std::string substr;

	std::string point1;
	std::string point2;
	int cost = -999;

	int index = 0;
	while (getline(ss, substr, '\t'))
	{
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

	Edge edge = Edge(point1, point2, cost);

	return edge;
}

int main(int argc, char** argv)
{
	if (argc < 0)
	{
		std::cout << "To few arguments" << std::endl;
		return -1;
	}

	std::vector<std::string> edgesString;
	std::vector<std::string> nodes;

	ReadValuesFromFile(argv[1], nodes, edgesString);

	auto start = std::chrono::steady_clock::now();

	std::vector<Edge> edges;

	for (int i = 0; i < (int)edgesString.size(); i++)
	{
		edges.push_back(CreateEdge(edgesString[i]));
	}

	for (int i = 0; i < (int)edges.size(); i++)
	{
		std::cout << "Point1; " << edges[i].getP1() << "   " << "Point2; " << edges[i].getP2() << "  Cost: " << edges[i].getCost() << std::endl;
	}


	Disjset ds;


	for (int i = 0; i < nodes.size(); i++)
	{
		ds.add_element(nodes[i], nodes[i]);
	}






	std::cout << "parent for node 1 : " << ds.find_set(nodes[1]) << std::endl;
	ds.union_sets(nodes[1], nodes[3]);
	std::cout << "parent for node 1 : " << ds.find_set(nodes[1]) << std::endl;
	std::cout << "element count : " << ds.getSetCount() << std::endl;

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

