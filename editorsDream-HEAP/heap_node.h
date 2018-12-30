#ifndef HEAP_NODE_H
#define HEAP_NODE_H
#include <iostream>

using namespace std;

struct node
{

    node(string *d, const int line = 0, const int para = 0);
    node();
    ~node();
    node(const node &other);
    node &operator=(const node &other);


    friend bool operator<(const node &x, const node &y);

    friend bool operator>(const node &x, const node &y);

    friend bool operator>=(const node &x, const node &y);

    friend bool operator<=(const node &x, const node &y);

    string *data;
    int lineNumber, paragraph;

    private:
        void copy(const node &other);

};

#endif // HEAP_NODE_H
