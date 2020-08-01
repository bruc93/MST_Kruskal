#include "Disjset.h"



Disjset::Disjset()
	: forestSetCount(0)
{

}

Disjset::Disjset(const std::map<std::string, std::string>& initialElements)
	: forestSetCount(0)
{	
	addElement(initialElements);
}


void Disjset::addElement(const std::map<std::string, std::string>& elements)
{
    for (typename std::map<std::string, std::string>::const_iterator it = elements.begin(), iend = elements.end(); it != iend; ++it)
    {
        m_elements.insert(std::make_pair(it->first, NodeElement(it->second, it->first)));
    }
    forestSetCount += elements.size();
}

void Disjset::addElement(std::string x, const std::string& value)
{
    m_elements.insert(std::make_pair(x, NodeElement(value, x)));
    ++forestSetCount;
}

int Disjset::amountOfNodeElements() const
{
    return static_cast<int>(m_elements.size());
}

std::string Disjset::findParentForNode(std::string node) const
{
    NodeElement& element = getElement(node);
    std::string& parent = element.parent;
    if (parent != node)
    {
        parent = findParentForNode(parent);
    }
    return parent;
}

int Disjset::getSetCount() const
{
    return forestSetCount;
}

void Disjset::unionSets(std::string node1, std::string node2)
{
    std::string setNode1 = findParentForNode(node1);
    std::string setNode2 = findParentForNode(node2);

    if (setNode1 != setNode2)
    {
        bind(setNode1, setNode2);
    }
}


