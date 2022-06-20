#include <iostream>
#include <set>
#include <map>

using namespace std;

struct Kartya
{
    string nev;
    set<string> kategoriak;

    Kartya()
    {
        nev = "";
    }
    Kartya(string _nev)
    {
        nev = _nev;
    }

    void kategoria_hozzaad(string kategoria)
    {
        kategoriak.insert(kategoria);
    }
};

class Jatekos
{
    map<string, Kartya> kijatszottak; // map<kategoria, Kartya>
public:
    void kijatszik(Kartya k)
    {
        for(string kategoria: k.kategoriak)
        {
            if(kijatszottak.find(kategoria)!=kijatszottak.end())
            {
                cout << "kidobni: " << kijatszottak[kategoria].nev;
                cout << endl;
            }
            kijatszottak[kategoria]=k;
        }
    }

    void kepesseg_kiir()
    {
        for(pair<string, Kartya> kategoria: kijatszottak)
        {
            cout << kategoria.first << ": " << kategoria.second.nev << ", ";
        }
        cout << endl;
    }
};

int main()
{
    Jatekos j;
    Kartya k1("Csizma");
    k1.kategoria_hozzaad("labbeli");
    Kartya k2("Szandal");
    k2.kategoria_hozzaad("labbeli");
    Kartya k3("Kupak");
    k3.kategoria_hozzaad("sisak");
    Kartya k4("Buvarruha");
    k4.kategoria_hozzaad("sisak");
    k4.kategoria_hozzaad("labbeli");
    j.kijatszik(k1);
    j.kepesseg_kiir(); // labbeli: Csizma
    j.kijatszik(k3);
    j.kepesseg_kiir(); // labbeli: Csizma, sisak: Kupak
    j.kijatszik(k2); // kidobni: Csizma
    j.kepesseg_kiir(); // labbeli: Szandal, sisak: Kupak
    j.kijatszik(k4); // kidobni: Szandal, Kupak
    j.kepesseg_kiir(); // labbeli: Buvarruha, sisak: Buvarruha

    return 0;
}
