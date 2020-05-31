#ifndef FIND
#define FIND

#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

class Find
{
protected:
    string sample;
    string source;
    list<int>adresses;
    int numberOfComparisons = 0;
public:
    Find(string,string);
    virtual ~Find() = default;
    void PrintResult(string fileName);
};

class Naive : public Find
{
public:
    Naive(string sample,string source) : Find(sample, source) {GetAdresses();}
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
    ~Naive() = default;
};

class RKFind : public Find
{
    int SymbolNumbers;
public:
    RKFind(string sample,string source,int SymbolNumbers = 94 ) : Find(sample, source) {this -> SymbolNumbers = SymbolNumbers; GetAdresses();}
    int h(string);
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
    ~RKFind() = default;
};

class KMPFind : public Find
{
    int *KMPArr;
public:
    KMPFind(string sample,string source) : Find(sample, source) {KMPArrGenerate(); GetAdresses();}
    void KMPArrGenerate();
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
    ~KMPFind() = default;
};

class BMFind : public Find
{
   int *BMArr;
public:
    BMFind(string sample,string source) : Find(sample, source) {BMArrGenerate(); GetAdresses();}
    void BMArrGenerate();
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
    ~BMFind() = default;
};

class Sunday : public Find
{
    int **pos;
    string alph;
    int SymbolNumbers = 0;
public:
    Sunday(string sample,string source,string alph = "10") : Find(sample, source)
                            {this -> alph = alph; posGenerate(); GetAdresses();}
    void posGenerate();
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
    ~Sunday() = default;
};

#endif // FIND
