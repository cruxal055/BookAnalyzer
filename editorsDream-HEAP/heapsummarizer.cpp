#include "heapsummarizer.h"
#include <QString>

heapSummarize::heapSummarize()
{

}

void heapSummarize::createReport(heap arr[],const int index)
{
    bool alreadyUpdated = false;
    background neo;
    node *ptr;
    int counter = 1;
    arr[index].pop(ptr);
    data.push_back(ptr->data);
    neo.lineNum = ptr->lineNumber;
    neo.paraNum = ptr->paragraph;
    neo.parentPos = 0;
    info.push_back(neo);
    string lastItem = *(ptr->data);
    delete ptr;

    while(!arr[index].empty())
    {
        arr[index].pop(ptr);
        if( *(ptr->data) == lastItem )
        {
            ++counter;
            delete ptr->data;
            alreadyUpdated = false;
        }
        else
        {
            data.push_back(ptr->data);
            lastItem = *(ptr->data); // could make this faster-
            dividers.push_back(counter);
            counter = 1;
            alreadyUpdated = true;
        }
        neo.lineNum = ptr->lineNumber;
        neo.paraNum = ptr->paragraph;
        neo.parentPos = data.size()-1;
        info.push_back(neo);
        delete ptr;
    }
    dividers.push_back(counter);
}



void heapSummarize::getTopTen(vector<word>&compilation)
{
    vector<word> hold;
    word temp;
    for(int i = 0; i < data.size(); ++i)
    {
        temp.set(data[i],dividers[i]);
        hold.push_back(temp);
    }
    std::sort(hold.begin(), hold.end(), [](word &temp1, word &temp2)
    {
        return temp1.occurences > temp2.occurences;
    });
    for(int i = 0; i < 10; ++i)
        compilation.push_back(hold[i]);
}


heapSummarize::~heapSummarize()
{
    reset();
}

void heapSummarize::reset()
{
    for(int i = 0; i < data.size(); ++i)
    {
        delete data[i];
        data[i] = nullptr;
    }
    data.clear();
    dividers.clear();
    info.clear();
}

void heapSummarize::toString()
{
    cout << "the size of dividers is: " << dividers.size() << endl;
    cout << "the size of data is: " << data.size() << endl;
    for(int i = 0; i < data.size(); ++i)
        cout << "data is: " << *(data[i]) << " and occures: " << dividers[i] << " times " << endl;
    cout << "done\n";
}


std::ostream& operator<<(ostream &out, heapSummarize &toOutput)
{
    int counter = 0;
    string temp;
    for(int i = 0; i < toOutput.data.size(); ++i)
    {
        temp = *(toOutput.data[i]);
        out << (char)(toupper(temp[0])) << temp.substr(1) << " with: " << toOutput.dividers[i]  << " occurences " << endl;
        out << "all occurences: \n";
        out << "______________________________________________________________________\n";
        for(int j = 0; j < toOutput.dividers[i]; ++j)
            out << "line: " <<  toOutput.info[counter].lineNum << " paragraph: " << toOutput.info[counter++].paraNum<< endl;
        out << "______________________________________________________________________\n";
        out << endl;
    }
    return out;
}

void heapSummarize::print(QTextEdit *&box)
{
    string temp;
    for(int i = 0; i < data.size(); ++i)
    {
        temp = *(data[i]);
        temp[0] = toupper(temp[0]);
        box->append(QString::fromStdString(temp));
    }
}
