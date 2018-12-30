#ifndef HEAPSUMMARIZER_H
#define HEAPSUMMARIZER_H
#include "heap_node.h"
#include "heap.h"
#include <algorithm>
#include <iostream>
#include <QTextEdit>

struct background
{
    int lineNum, paraNum, parentPos;

    background()
    {
        lineNum = paraNum = parentPos = 0;
    }
    background(const background &other)
    {
        copyOther(other);
    }

    background& operator=(const background &other)
    {
       if(this != &other)
           copyOther(other);
       return *this;
    }

    void copyOther(const background &other)
    {
        lineNum = other.lineNum;
        paraNum = other.paraNum;
        parentPos = other.parentPos;
    }
};

struct word
{
    string *data;
    int occurences;

    word()
    {
        data = nullptr;
        occurences = 0;
    }

    word(const word &other)
    {
        copyOther(other);
    }

    word& operator=(const word &other)
    {
        if(this != &other)
            copyOther(other);
        return *this;

    }

    void set(string *nData, int nOccurences)
    {
        data = nData;
        occurences = nOccurences;
    }

    void copyOther(const word &other)
    {
        data = other.data;
        occurences = other.occurences;
    }
};


class heapSummarize
{
    public:
        heapSummarize();
        ~heapSummarize();

        void createReport(heap arr[],const int index);
        void generateSummary();
        void getTopTen(vector<word> &compilation);

        void toString();
        void print(QTextEdit *&box);
        friend std::ostream& operator<<(ostream &out, heapSummarize &toOutput);
        void reset();

    private:
        vector<string*> data;
        vector<background> info;
        vector<int> dividers;

};

#endif // HEAPSUMMARIZER_H
