#include "Disjset.h"



Disjset::Disjset()
	: m_setCount(0)
{

}

Disjset::Disjset(const std::map<std::string, std::string>& initialElements)
	: m_setCount(0)
{	
	add_element(initialElements);
}


void Disjset::add_element(const std::map<std::string, std::string>& elements)
{
    for (typename std::map<std::string, std::string>::const_iterator it = elements.begin(), iend = elements.end(); it != iend; ++it)
    {
        m_elements.insert(std::make_pair(it->first, Element(it->second, it->first)));
    }
    m_setCount += elements.size();
}

void Disjset::add_element(std::string x, const std::string& value)
{
    m_elements.insert(std::make_pair(x, Element(value, x)));
    ++m_setCount;
}

int Disjset::element_count() const
{
    return static_cast<int>(m_elements.size());
}

std::string Disjset::find_set(std::string x) const
{
    Element& element = get_element(x);
    std::string& parent = element.parent;
    if (parent != x)
    {
        parent = find_set(parent);
    }
    return parent;
}

int Disjset::getSetCount() const
{
    return m_setCount;
}

void Disjset::union_sets(std::string x, std::string y)
{
    std::string setX = find_set(x);
    std::string setY = find_set(y);
    if (setX != setY) link(setX, setY);
}

std::string& Disjset::value_of(std::string x)
{
    return get_element(x).value;
}


