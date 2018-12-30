#include "myparser.h"

myParser::myParser()
{
    wordCount = sentenceCount = syllableCount = lineCount = 0;
    paragraphCount = 1;
    firstSentenceOcurred = false;
}

myParser::~myParser()
{
    reset();
}

myParser::myParser(const myParser &other)
{
    copyData(other);
}

myParser& myParser::operator=(const myParser &other)
{
    if(this != &other)
        copyData(other);
    return *this;
}

void myParser::parse(const string &fileName, heap arr[])
{
    string line;
    ifstream toParse(fileName);
    while(getline(toParse,line))
    {
        ++lineCount;
        if(!line.size() && firstSentenceOcurred)
            ++paragraphCount;
        else
        {
            cleanLine(line);
            processLine(line,arr);
        }
    }
}

void myParser::parseText(const string &fileName, heap arr[])
{
    string line;
    ifstream toParse(fileName);
    while(getline(toParse,line))
    {
        ++lineCount;
        if(!line.size() && firstSentenceOcurred)
            ++paragraphCount;
        else
        {
            cleanLine(line);
            processLine(line,arr);
        }
    }
}

void myParser::processLine(string &line, heap arr[])
{
    string word;
    stringstream reader;
    reader<<line;
    while(reader>>word)
    {
        ++wordCount;
        for(size_t i = 0; i < word.size(); ++i)
            word[i] = tolower(word[i]);
        syllableCount += getSyllables(word);
        cleanWord(word);
        if(!word.size())
            continue;
        if(word.size() == 1 && !(isChar(word[0])))
            continue;
        if(word.size() == 1)
        {
            arr['z'-word[0]].push(new string(word),lineCount,paragraphCount);
            continue;
        }
        if(isEndOfSentence(word))
        {
            firstSentenceOcurred = true;
            ++sentenceCount;
            word.erase(word.size()-1,1);
            if(word.size() == 1 && !(isChar(word[0])))
                continue;
            if(word.size() == 1)
            {
                arr['z'-word[0]].push(new string(word),lineCount,paragraphCount);
                continue;
            }
            else
                arr['z'-word[0]].push(new string(word),lineCount,paragraphCount);
        }
        else
        {
            while(word.find("!?.") < word.size())
                word.erase(word.find("!?."),1);
            arr['z'-word[0]].push(new string(word),lineCount,paragraphCount);
        }
    }
}

bool myParser::isEndOfSentence(string &toCheck)
{
    return (toCheck[toCheck.size() - 1] == '.' || toCheck[toCheck.size() - 1] == '!' ||
            toCheck[toCheck.size() - 1] == '?');
}

void myParser::getInfo(int &words, int &sentences, int &syllables, int &paragraphs, int &lines)
{
    words = wordCount;
    sentences = sentenceCount;
    syllables = syllableCount;
    paragraphs = paragraphCount;
    lines = lineCount;
}

bool myParser::isChar(char &toCheck)
{
    return (tolower(toCheck) >= 'a' && tolower(toCheck) <= 'z');
}

double myParser::getReadingLevel()
{
    double avgW = (double)(wordCount/sentenceCount);
    avgW = 0.39 * avgW;
    double avgSy = (double)(syllableCount/wordCount);
    avgSy = 11.8 * avgSy;
    return (avgW + avgSy - 15.59);
}

void myParser::cleanLine(string &line)
{
    while(line.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvywxyz!?. ") < line.size())
        line.erase(line.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvywxyz!?. "),1);
}

void myParser::cleanWord(string &word)
{
    while(word.find_first_of("!?.") < word.size() - 1)
        word.erase(word.find_first_of("!?."),1);
}

void myParser::copyData(const myParser &other)
{
    wordCount = other.wordCount;
    lineCount = other.lineCount;
    paragraphCount = other.paragraphCount;
    sentenceCount = other.sentenceCount;
    syllableCount = other.syllableCount;
}

size_t myParser::getSyllables(string &word)
{
    int ignore = 0, count = 0, temp;
        string neo = word;
        if((neo[neo.size()-1] == 'y') && neo.find_last_of("aeiou") != neo.size()-2)
        {
            neo = neo.substr(0,neo.size()-1);
            ++count;
        }
        if(neo[neo.size()-1] == 'e')
            --count;
        while(neo.find_first_of("aeiouy",ignore) < neo.size())
        {
            temp = neo.find_first_of("aeiouy",ignore); //check to make sure not diphthong or triphthong
            if(neo[temp] == 'y' && (temp - neo.find_first_of("aeiouy",temp+1) > 1))
                ++count;
            if(ignore != temp && neo[temp] != 'y' || !temp)
                ++count;
            ignore = temp+1;
        }
        if(count <= 0)
            count = 1;
        return count;

}

void myParser::printInfo(ostream &out)
{
    out<<"words: "<<wordCount<<endl;
    out<<"lines: "<<lineCount<<endl;
    out<<"paragraphs: "<<paragraphCount<<endl;
    out<<"syllables: "<<syllableCount<<endl;
    out<<"sentences: "<<sentenceCount<<endl;
}

void myParser::reset()
{
    wordCount = sentenceCount = lineCount = paragraphCount = syllableCount = 0;
}

double myParser::getReadingEase()
{
    double avgW = (double)(wordCount/sentenceCount);
    avgW = (1.015 * avgW);
    double avgSy = (double)(syllableCount/wordCount);
    avgSy = (84.6 * avgSy);
    return (206.835 - avgW - avgSy);
}
