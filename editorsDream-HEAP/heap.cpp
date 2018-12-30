#include "heap.h"

heap::heap()
{
    data.push_back(new node(new string("0"),1,1));
}

heap::~heap()
{
    destroy();
}

heap::heap(const heap &other)
{
    copy(other);
}

heap& heap::operator=(const heap &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

void heap::copy(const heap &other)
{
    data = other.data;
}

void heap::destroy()
{
    for(int i = 0; i < data.size(); ++i)
    {
        delete data[i];
        data[i] = nullptr;
    }
    data.clear();

}

void heap::push(string *d, const int pos, const int para)
{
    data.push_back(new node(d,pos,para));
    reheapifyUp();

}

void heap::pop(node *&ptr)
{
    ptr = data[1];
    data[1] = data[data.size()-1];
    data.pop_back();
    reheapifyDown();
}

void heap::pop(string *&d, int &para, int &line)
{
    d = data[1]->data;
    para = data[1]->paragraph;
    line = data[1]->lineNumber;
    delete data[1];
    data[1] = nullptr;
    data[1] = data[data.size()-1];
    data.pop_back();
    reheapifyDown();

}

void heap::reheapifyDown()
{
    if(data.empty())
        return;
    int currentPos = 1;
    if(data.size() >= 3)
    {
        while( (*(data[currentPos]) > *(data[currentPos*2]) ) ||  (*(data[currentPos]) > *(data[(currentPos*2)+1] )) )
        {
            int toSwap = *(data[currentPos*2]) > *(data[(currentPos*2)+1]) ? (currentPos*2 + 1) : (currentPos*2);
            if(toSwap > data.size())
                break;
            swap(currentPos,toSwap);
            currentPos = toSwap;
            if(currentPos*2 >=  data.size())
                break;
        }
    }
    else
    {
        if(data.size() == 1)
            return;
        if(*(data[1]) < *(data[2]))
            swap(1,2);
    }

}

void heap::reheapifyUp()
{
    int currentPos = data.size()-1;
    if(data.size() >= 3)
    {
        while(currentPos/2 && *(data[currentPos]) < *(data[currentPos/2]))
        {
            swap(currentPos,currentPos/2);
            currentPos = currentPos/2;
        }
    }
}

void heap::swap(int index1, int index2)
{
    node *temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

bool heap::empty() const
{
    return data.size() == 1;
}

unsigned int heap::size() const
{
    return data.size() - 1;
}

void heap::reset()
{
    for(int i = 0; i < data.size(); ++i)
    {
        if( *(data[i]->data) == "0")
        {
            delete data[i];
            data[i] = nullptr;
        }
    }
   // delete data[0];
    data.clear();
   // data.push_back(0);

}

string* heap::peek()
{
    return data[1]->data;
}


void heap::toString()
{
    cout << "the size is: " << data.size() << endl;
    for(int i = 1; i <data.size(); ++i)
        if(data[i] != nullptr)
            cout << "data[" << i << "] holds: " << *(data[i]->data) << endl;

}
