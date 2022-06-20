#include <iostream>
#include <set>
#include <list>
#include <map>

using namespace std;

struct Viszony
{
    string leiras="";
    string kezdet="";
    string veg="";
public:
    Viszony()
    {}
    Viszony(string _leiras, string _kezdet, string _veg)
    {
        leiras=_leiras;
        kezdet=_kezdet;
        veg=_veg;
    }
};

struct Forgatokonyv
{
    map<string,map<string, Viszony>> kapcsolatok;//map<szereplo, map<kivel, milyen viszony>

    void uj_szereplo(string nev)
    {
        kapcsolatok[nev];
    }
    void viszony(string ki, string kivel, Viszony viszony)
    {
        kapcsolatok[ki][kivel]=viszony;
        kapcsolatok[kivel][ki]=viszony;
    }
    void allapot(string nev)
    {
        for(pair<string,Viszony> ember : kapcsolatok[nev])
        {
            cout<<nev<<": "<<ember.first<<": "<<ember.second.leiras<< endl;
        }
    }
    void lehetseges_esemenyek(list<Viszony> v)
    {
        for(pair<string,map<string, Viszony>> ki : kapcsolatok)
        {
            cout<<ki.first<<endl;
            for(pair<string, Viszony> kivelmi : ki.second) //nekik tuti van viszonyuk
            {
                cout<<" - "<<kivelmi.first<<" "<<kivelmi.second.veg<<endl;

            }
            for(pair<string,map<string, Viszony>> valaki : kapcsolatok) //a maradek
            {
                if(ki.second.find(valaki.first)== ki.second.end() && ki.first!=valaki.first)
                {
                    for(auto vi: v)
                    {
                        cout<<" - "<<valaki.first<<" "<<vi.kezdet<<endl;
                    }
                }
            }
        }
    }
};

int main()
{
    Viszony baratsag("baratok","osszebaratkoznak","elhidegulnek");
    Viszony szerelem("szerelmesek","egymasba szeretnek","kiabrandulnak egymasbol");
    Viszony ellenseg("ellensegek","osszevesznek","kibekulnek");
    list <Viszony> viszonyok;
    viszonyok.push_back(baratsag);viszonyok.push_back(szerelem);viszonyok.push_back(ellenseg);
    Forgatokonyv f;
    f.uj_szereplo("Esmeralda");
    f.uj_szereplo("Leoncio");
    f.uj_szereplo("Carlos");
    f.uj_szereplo("Carina");
    f.viszony("Esmeralda","Leoncio",szerelem);
    f.viszony("Carlos","Leoncio",ellenseg);
    f.viszony("Esmeralda","Carina",baratsag);
    f.allapot("Esmeralda");
    f.lehetseges_esemenyek(viszonyok);
}
