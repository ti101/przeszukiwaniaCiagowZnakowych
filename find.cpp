#include "find.h"
#include <cmath>


Find::Find(string sample, string source)
{
    this -> sample = sample;
    this -> source = source;
}


void Find::PrintResult(string fileName)
{
    ofstream result (fileName);
    result<<"information:_____________________________________"<<endl;
    result<<"\nsearch string \" "<<sample<<" \"";
    result<<" \nnumber of symbols - "<<source.length();
    result<<"\nnumber of comparisons - "<<numberOfComparisons<<endl;
    result<<"adresses: ";
    for (auto v : adresses)
        result << v << " ";
    result<<"\n_________________________________________________"<<endl<<endl;

    if(!adresses.empty())
    {
        unsigned int o = 0;
        bool open = false;
        list<int>::iterator it = adresses.begin();
        for(unsigned int i = 0; i < source.length(); ++i)
        {
            if(i == *it)
            {
                result<<" [ ";
                open = true;
                advance(it, 1);
            }
            result<<source[i];
            if(open == true)
            {
                o++;
                if(o == sample.length())
                {
                    result<<" ] ";
                    o = 0;
                    open = false;
                }
            }
        }
    }
    else
        result<<"\""<< sample <<"\" not Found"<<endl;
    result.close();
}

void Naive::GetAdresses()
{
    for(unsigned int i = 0; i < source.length(); ++i)
    {
        for(int k = 0; k < sample.length(); ++k)
        {
            numberOfComparisons++;
            if(sample[k] != source[k + i])break;
            if(k == sample.length() - 1)
            {
                 adresses.push_back(i);
            }
        }
    }
}



int RKFind::h(string source)
{
    int revers_i = source.length() - 1;
    int PrimeNumber = 23;
    int result = 0;
    for(unsigned int i = 0; i < source.length(); ++ i)
    {
        result += source[i] * pow(SymbolNumbers,revers_i);
        revers_i--;
    }
    result %= PrimeNumber;
    return result;
}

void RKFind::GetAdresses()
{
    int length = sample.length();
    int HashText = h(sample);
    unsigned int position = 0;
    int HashSource = h(source.substr(position,length));

    while(true)
    {
        numberOfComparisons++;
        if(HashText == HashSource)
        {
            for(int k = 0; k < sample.length(); ++k)
            {
                numberOfComparisons++;
                if(sample[k] != source[k + position])break;
                if(k == sample.length() - 1)
                {
                     adresses.push_back(position);
                }
            }
        }
        position++;
        if(position == source.length() - length + 1) break;
        HashSource = h(source.substr(position,length));
    }
}



void KMPFind::KMPArrGenerate()
{
    KMPArr = new int[sample.length()];
    int b = -1;
    KMPArr[0] = -1;

    for(unsigned int i = 1; i <= sample.length(); ++i)
    {
        while((b > -1) && (sample[b] != sample[i - 1]))
        {
            b = KMPArr[b];
        }
        ++b;
        if(i == sample.length() || sample[i] != sample[b])
            KMPArr[i] = b;
        else
            KMPArr[i] = KMPArr[b];
    }
}

void KMPFind::GetAdresses()
{
    int b = 0;
    int position = 0;

    for(unsigned int i = 0; i < source.length(); ++i)
    {
        if((b == -1) || (sample[b] == source[i]))
            numberOfComparisons++;
        while((b > -1) && (sample[b] != source[i]))
        {
            b = KMPArr[b];
            numberOfComparisons++;
        }
        b++;
        if(b == sample.length())
        {
            position = i - b + 1;
            adresses.push_back(position);
            b = KMPArr[b];
        }
    }
}


void BMFind::BMArrGenerate()
{
    BMArr = new int[sample.length() + 1];
    int length = sample.length();
    int Pi[length + 1];
    for(int i = 0; i <= length; i++)
        BMArr[i] = 0;

    int i = length;
    int b = length + 1;
    Pi[i] = b;

    while(i > 0)
    {
        while((b <= length) && (sample[i- 1] != sample[b - 1]))
        {
            if(BMArr[b] == 0)
                BMArr[b] = b - i;
            b = Pi[b];
        }
        Pi[--i] = --b;
    }

    b = Pi[0];
    for(int i = 0; i <= length; i++)
    {
        if(BMArr[i] == 0)
            BMArr[i] = b;
        if(i == b)
            b = Pi[b];
    }
}

void BMFind::GetAdresses()
{
    int asciiRangeMin = 32; // space
    int asciiRangeMax = 126; // ~

    int Last[asciiRangeMax - asciiRangeMin + 1];
    for(int i = 0; i <= asciiRangeMax - asciiRangeMin; ++i)
        Last[i] = -1;
    for(unsigned int i = 0; i < sample.length(); ++i)
        Last[sample[i] - asciiRangeMin] = i;

    int i = 0;
    while(i <= source.length() - sample.length())
    {
        int j = sample.length() - 1;

        if((j == -1 ) || (sample[j] != source[i + j]))
            numberOfComparisons++;


        while((j > -1 ) && (sample[j] == source[i + j]))
        {
            numberOfComparisons++;
            j--;
        }

        if(j == -1)
        {
            adresses.push_back(i);
            i += BMArr[0];
        }
        else
            i += max(BMArr[j + 1], j - Last[source[i+j] - asciiRangeMin]);
    }
}

void Sunday::posGenerate()
{
    SymbolNumbers = alph.length();
    pos = new int*[2];
    for(int i = 0; i < 2; ++i)
    {
        pos[i] = new int[SymbolNumbers];
    }
    for(int i = 0; i < SymbolNumbers; ++i)
    {
        pos[0][i] = (int)alph[i];
    }

    for(int i = 0; i < SymbolNumbers; ++i)
    {
        int j = sample.length();
        while(pos[0][i] != (int)sample[j])
        {
            j--;
            if(j == -1)
            {
                break;
            }
        }
        if(j >= 0)
            pos[1][i] = sample.length() - j;
        else
            pos[1][i] = sample.length() + 1;
    }
}


void Sunday::GetAdresses()
{
    int startAdresses = 0;
    while(startAdresses < source.length())
    {
        int si = 0;
        for(int i = startAdresses; i < sample.length() + startAdresses; ++i)
        {
            numberOfComparisons++;
            if(source[i] != sample[si]) break;
            si++;
        }

        if(si == sample.length())
            adresses.push_back(startAdresses);

        int next = 0;
        if(startAdresses + sample.length() < source.length())
        {
            for(int i = 0; i < SymbolNumbers; ++i)
            {
                if(source[startAdresses + sample.length()] == (char)pos[0][i])
                {
                    next = pos[1][i];
                    break;
                }
            }
            startAdresses += next;
        }
        else
            break;
    }
}

