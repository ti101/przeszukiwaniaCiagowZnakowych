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
public:
    Find(string,string);
    virtual ~Find() = default;
    void PrintResult(string fileName);
};

class Native : public Find
{
public:
    Native(string sample,string source) : Find(sample, source) {GetAdresses();}
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
};

class HashFind : public Find
{
public:
    HashFind(string sample,string source) : Find(sample, source) {GetAdresses();}
    int h(string);
    void GetAdresses();
    void PrintResult(string fileName) {Find::PrintResult(fileName);}
    ~HashFind() = default;
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

#endif // FIND
