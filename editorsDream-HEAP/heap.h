#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <algorithm>
#include <ctime>
#include "heap_node.h"

using namespace std;

enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};

enum HEAP_ERRORS {HEAP_EMPTY};

class heap
{
    public:
        heap();
        ~heap();
        heap(const heap &other);
        heap &operator=(const heap &other);

        void push(string *d, const int pos, const int para);
        void pop(string *&d, int &para, int &line);
        void pop(node *&ptr);
        string* peek();

        bool empty() const;
        unsigned int size() const;
        void reset();
        void toString();



    private:
        vector<node*> data;

        void swap(int index1, int index2);
        void copy(const heap &other);
        void destroy();

        void reheapifyDown();
        void reheapifyUp();
};

#endif // HEAP_H
