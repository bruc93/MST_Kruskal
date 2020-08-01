#pragma once
#include <map>
#include <string>
#include <iostream>


class Disjset
{
private:
	struct NodeElement
	{
		std::string value;
		std::string parent;
		int rank;

		NodeElement(const std::string _value, std::string _parent)
			:value(_value), parent(_parent), rank(0)
		{}
	};

	mutable std::map<std::string, NodeElement> m_elements;
	int forestSetCount;

	NodeElement& getElement(std::string x) const
	{
		typename std::map<std::string, NodeElement>::iterator it = m_elements.find(x);
		if (it != m_elements.end())
		{
			return it->second;
		}
		else 
		{
			try
			{
				throw 20;
			}
			catch (int e)
			{
				std::cout << "An exception occurred. No such element :" << x << '\n';
			}
		}
	}

	void bind(std::string node1, std::string node2)
	{
		NodeElement& elementNode1 = getElement(node1);
		NodeElement& elementNode2 = getElement(node2);
		int& rankNode1 = elementNode1.rank;
		int& rankNode2 = elementNode2.rank;
		if (rankNode1 > rankNode2)
		{
			elementNode2.parent = node1;
		}
		else
		{
			elementNode1.parent = node2;
			if (rankNode1 == rankNode2) ++rankNode2;
		}
		--forestSetCount;
	}

public:
	Disjset();
	explicit Disjset(const std::map<std::string, std::string>& initialElements);
	void addElement(const std::map<std::string, std::string>&);
	void addElement(std::string x, const std::string& value);
	int amountOfNodeElements() const;
	std::string findParentForNode(std::string node) const;
	int getSetCount() const;
	void unionSets(std::string x, std::string y);
};

