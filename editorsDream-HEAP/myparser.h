#ifndef MYPARSER_H
#define MYPARSER_H
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "heap.h"

using namespace std;

class myParser
{
    public:
        myParser();
        ~myParser();
        myParser(const myParser &other);
        myParser& operator=(const myParser &other);
        void parse(const string &fileName, heap arr[]);
        void parseText(const string &fileName, heap arr[]);
        void getInfo(int &words, int &sentences, int &syllables, int &paragraphs, int &lines);
        double getReadingLevel();
        void printInfo(ostream &out);
        void reset();
        double getReadingEase();

    private:
        bool wasSentence;
        bool firstSentenceOcurred;
        double wordCount, sentenceCount, syllableCount, paragraphCount, lineCount;
        void cleanLine(string &line);
        void processLine(string &line, heap arr[]);
        //void processLine(string &line, heap arr[]);
        void copyData(const myParser &other);
        bool isEndOfSentence(string &toCheck);
        void removeQuotations(string &line);
        size_t getSyllables(string &word);
        void cleanWord(string &word);
        bool isChar(char &toCheck);
};

#endif // MYPARSER_H
