#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "Edge.h"
#include <sstream>
#include "Disjset.h"
#include <queue>
#include "Main.h"

void writeAnswerFile(std::vector<std::string>& nodes, std::vector<Edge>& mst)
{
	std::ofstream myfile("Answer.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			myfile << nodes[i] << "\n";
		}
		myfile << "\n";
		for (int i = 0; i < mst.size(); i++)
		{
			myfile << mst[i].toString() << "\n";
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}

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

std::vector<Edge> kruskal(std::vector<Edge> edges, std::vector<std::string> nodes)
{
	Disjset ds;
	//init ds with the nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		ds.addElement(nodes[i],nodes[i]);
	}
	

	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

	for (int i = 0; i < edges.size();i++) 
	{
		pq.push(edges[i]);
	}

	std::vector<Edge> mst;

	while (mst.size() != nodes.size()-1)
	{
		Edge e = pq.top();
		std::string p1set = ds.findParentForNode(e.getP1());
		std::string p2set = ds.findParentForNode(e.getP2());

		if(p1set != p2set)
		{
			//Accept the edge!
			mst.push_back(e);
			ds.unionSets(p1set, p2set);
		}

		pq.pop();
	}

	return mst;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "To few arguments" << std::endl;
		return -1;
	}

	auto start = std::chrono::steady_clock::now();
	std::vector<std::string> edgesString;
	std::vector<std::string> nodes;

	ReadValuesFromFile(argv[1], nodes, edgesString);


	std::vector<Edge> edges;

	for (int i = 0; i < (int)edgesString.size(); i++)
	{
		edges.push_back(CreateEdge(edgesString[i]));
	}
	std::vector<Edge> mst = kruskal(edges, nodes);

	writeAnswerFile(nodes, mst);

	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "-------------- MST --------------------" << std::endl;
	std::cout << "MST took: " << elapsed_seconds.count() << " seconds" << std::endl;
	return 0;
}



