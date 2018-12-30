#include "heap_node.h"

node::node()
{
    lineNumber = 0;
}


node::node(string *d, const int line, const int para)
{
    data = d;
    lineNumber = line;
    paragraph = para;
}

node::~node()
{

}

node::node(const node &other)
{
    copy(other);
}


node& node::operator=(const node &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

void node::copy(const node &other)
{
    data = other.data;
    lineNumber = other.lineNumber;
    paragraph = other.paragraph;
}

bool operator<(const node &x, const node &y)
{
    return *(x.data) < *(y.data);
}

bool operator>(const node &x, const node &y)
{
   return *(x.data) > *(y.data);

}

bool operator>=(const node &x, const node &y)
{
    return *(x.data) >= *(y.data);
}

bool operator<=(const node &x, const node &y)
{
    return *(x.data) <= *(y.data);
}
