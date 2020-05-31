#include "find.h"

int main()
{
    string text;
    string tmp;

    ifstream fileSource ("example_DNA.txt"); // tekst
    if (fileSource.is_open())
    {
        while(getline(fileSource,tmp))
        {
            text+=tmp;
        }
        fileSource.close();
    }
    string searchString = "ATAAAAC"; // szukany ciag

    cout<<"\nNaive:\n";  // algorytm Naivny
    Naive f(searchString,text);
    f.PrintResult("Naive.txt");
    cout<<endl;

    cout<<"\nrkf:\n";  // algorytm Rabina-Karpa
    RKFind rkf(searchString,text);
    rkf.PrintResult("rkf.txt");
    cout<<endl;

    cout<<"\nkmpf:\n";  // Knutha-Morrisa-Pratta
    KMPFind kmpf(searchString,text);
    kmpf.PrintResult("kmpf.txt");
    cout<<endl;

    cout<<"\nbmf:\n"; // Boyera-Moora
    BMFind bmf(searchString,text);
    bmf.PrintResult("bmf.txt");
    cout<<endl;

    cout<<"\nSunday:\n"; // Sunday`a
    Sunday Sun(searchString,text,"ACGT");
    Sun.PrintResult("Sunday.txt");
    cout<<endl;

    return 0;
}
