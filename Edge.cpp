#include "Edge.h"

Edge::Edge(std::string p1, std::string p2, int _cost)
{
	point1 = p1;
	point2 = p2;

	cost = _cost;

}

std::string Edge::getP1() const
{
	return point1;
}

std::string Edge::getP2() const
{
	return point2;
}

int Edge::getCost() const
{
	return cost;
}

bool Edge::operator>(const Edge& other) const
{
	return this->cost > other.getCost();
}

bool Edge::operator<(const Edge& other) const
{
	return this->cost < other.getCost();
}

std::string Edge::toString()
{
	std::string info = this->point1 + "	" + this->point2 + "	" + std::to_string(this->cost);
	return info;
}




