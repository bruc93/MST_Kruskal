#pragma once
#include <string>
class Edge
{
public:
	Edge(std::string p1, std::string p2, int _cost);
	std::string getP1() const;
	std::string getP2() const;
	int getCost() const;
	bool operator>(const Edge& other) const;
	bool operator<(const Edge& other) const;
	std::string toString();
private:
	std::string point1;
	std::string point2;
	int cost;
};

