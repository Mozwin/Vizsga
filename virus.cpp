#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <set>
#include <map>

using namespace std;



class Pandemic
{
private:
    map<string,string> varosadatok; ///map<varos,virus>
    map<string, set<string>> varoskapcsolatok; ///map<varos, szomszedvaros> //graf
    map<string, map<string,int>> fertozottseg; ///map<varos, map<virus,fertozesszint>
    ///mindehol a varos a kulcs - logikus lenne egy varos struct es abba tenni a tobbit

public:
    void uj_varos(string varos, string virus)
    {
        varosadatok[varos]=virus; ///varosadatokba teszi az uj varos
        varoskapcsolatok[varos];
        fertozottseg[varos];
    }
void uj_kapcsolat(string varos1, string varos2)
    {
        varoskapcsolatok[varos1].insert(varos2);
        varoskapcsolatok[varos2].insert(varos1); ///ezzel oldjuk meg, hogy oda vissza kapcsolat van a varosok kozott
    }
void fertozes(string varos)
    {
        string fertozesnev = varosadatok[varos];
        if(fertozottseg[varos].find(fertozesnev) == fertozottseg[varos].end()) ///find ha hamis a struktúra végével tér vissza
        {
            fertozottseg[varos][fertozesnev] = 1;
        }
        else
        {



            if(fertozottseg[varos][fertozesnev] < 3) ///Flood Fill
             {
                 fertozottseg[varos][fertozesnev]+=1;
             }
             else
             {
                 for(string szomszedvaros : varoskapcsolatok[varos])
                 {
                     fertozottseg[szomszedvaros][fertozesnev]+=1;
                 }
             }
        }

    }




void allapot_kiir()
    {
        for(pair<string, map<string,int>> a : fertozottseg)
        {


            cout<< a.first<<":";
            for(pair<string,int> b : a.second)
            {
                cout<< b.first << "," << b.second<< endl;
            }
        }
    }
void fertozes_kezelese(string varos, string virus)
    {


        fertozottseg[varos][virus]-=1; //továbbterjedes
        if ( fertozottseg[varos][virus] == 0) ///mapban van kulcshoz tartozo torles h a nullazasokat ne irja ki
        {


             fertozottseg[varos].erase(virus);
        }


    }
};

int main()
{
Pandemic p;

p.uj_varos("London", "CODA-45");
p.uj_varos("New York", "H1N1");
p.uj_varos("Budapest", "CODA-45");
p.uj_varos("Peking", "SARS-CoV-2");
p.uj_kapcsolat("London", "Budapest");
p.uj_kapcsolat("London", "New York");
p.uj_kapcsolat("London", "Peking");
p.uj_kapcsolat("Peking", "New York");
p.uj_kapcsolat("Peking", "Budapest");
p.fertozes("Budapest");
p.fertozes("Budapest");
p.fertozes("New York");
p.fertozes("New York");
p.fertozes("New York");
p.allapot_kiir();
//CODA-45 jelenlet> Budapest: 2, London: 0,
//H1N1 jelenlet> New York: 3,
//SARS-CoV-2 jelenlet> Peking: 0,
///vagy
// Budapest> CODA-45: 2,
// New York> H1N1: 3,
p.fertozes("Budapest");
p.allapot_kiir();
//CODA-45 jelenlet> Budapest: 3, London: 0,
//H1N1 jelenlet> New York: 3,
//SARS-CoV-2 jelenlet> Peking: 0,
///vagy
// Budapest> CODA-45: 3,
// New York> H1N1: 3,

p.fertozes("Budapest");
p.fertozes("New York");
p.allapot_kiir();
//CODA-45 jelenlet> Budapest: 3, London: 1, Peking: 1,
//H1N1 jelenlet> London: 1, New York: 3, Peking: 1,
//SARS-CoV-2 jelenlet> Peking: 0,
///vagy
// Budapest> CODA-45: 3,
// London> CODA-45: 1, H1N1: 1,
// New York> H1N1: 3,
// Peking> CODA-45: 1, H1N1: 1,

p.fertozes_kezelese("London", "CODA-45");

p.fertozes_kezelese("New York", "H1N1");

p.allapot_kiir();
//CODA-45 jelenlet> Budapest: 3, London: 0, Peking: 1,
//H1N1 jelenlet> London: 1, New York: 2, Peking: 1,
//SARS-CoV-2 jelenlet> Peking: 0,
///vagy
// Budapest> CODA-45: 3,
// London> H1N1: 1,
// New York> H1N1: 2,
// Peking> CODA-45: 1, H1N1: 1,

    return 0;
}
