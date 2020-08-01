#pragma once
#include <map>
#include <string>
#include <iostream>


class Disjset
{
private:
	struct Element
	{
		std::string value;
		std::string parent;
		int rank;

		Element(const std::string _value, std::string _parent)
			:value(_value), parent(_parent), rank(0)
		{}
	};

	mutable std::map<std::string, Element> m_elements;
	int m_setCount;

	Element& get_element(std::string x) const
	{
		typename std::map<std::string, Element>::iterator it = m_elements.find(x);
		if (it != m_elements.end()) return it->second;
		else {
			try
			{
				throw 20;
			}
			catch (int e)
			{
				std::cout << "An exception occurred. No such element : . " << x << '\n';
			}
		}
	}

	void link(std::string x, std::string y)
	{
		Element& elementX = get_element(x);
		Element& elementY = get_element(y);
		int& rankX = elementX.rank;
		int& rankY = elementY.rank;
		if (rankX > rankY)
		{
			elementY.parent = x;
		}
		else
		{
			elementX.parent = y;
			if (rankX == rankY) ++rankY;
		}
		--m_setCount;
	}

public:
	Disjset();
	explicit Disjset(const std::map<std::string, std::string>& initialElements);
	void add_element(const std::map<std::string, std::string>&);
	void add_element(std::string x, const std::string& value);
	int element_count() const;
	std::string find_set(std::string x) const;
	int getSetCount() const;
	void union_sets(std::string x, std::string y);
	std::string& value_of(std::string x);


};

