#include "find.h"
//#include <fstream>

int main()
{
    string text;
    string findString = "Small";

    ifstream fileSource ("source.txt");
    if (fileSource.is_open())
    {
        getline (fileSource,text);
        fileSource.close();
    }

    cout<<"\nNative:\n";
    Native f(findString,text);
    f.PrintResult("Native.txt");
    cout<<endl;

    cout<<"\nhf:\n";
    HashFind hf(findString,text);
    hf.PrintResult("hf.txt");
    cout<<endl;

    cout<<"\nkmpf:\n";
    KMPFind kmpf(findString,text);
    kmpf.PrintResult("kmpf.txt");
    cout<<endl;

    cout<<"\nbmf:\n";
    BMFind bmf(findString,text);
    bmf.PrintResult("bmf.txt");
    cout<<endl;

    return 0;
}
