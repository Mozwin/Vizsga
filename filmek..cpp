#include <iostream>
#include <map>
#include <set>

using namespace std;

class Valasztek
{
    map<string, set<string>> filmek; //map<filmcim, set<tipus>>
    set<set<string>> aliasok;

public:
    void uj(string filmcim)
    {
        filmek[filmcim];
    }

    void uj_cimke(string filmcim, string tipus)
    {
        filmek[filmcim].insert(tipus);
    }

    void mindent_kiir()
    {
        for(map<string, set<string>>::iterator it = filmek.begin(); it!=filmek.end(); it++)
        {
            cout << it->first << ": ";
            for(set<string>::iterator it2 = it->second.begin(); it2!=it->second.end(); it2++)
            {
                cout << "[ ";
                bool van_aliasa = false;
                for(set<set<string>>::iterator it3=aliasok.begin(); it3!=aliasok.end(); it3++)
                {
                    if(it3->find(*it2)!=it3->end())
                    {
                        for(set<string>::iterator it4=it3->begin(); it4!=it3->end(); it4++)
                        {
                            cout << " " << *it4;
                        }
                        van_aliasa = true;
                    }
                }
                if(!van_aliasa)
                {
                    cout << *it2;
                }
                cout << " ]";
            }
            cout << ", ";
        }
        cout << endl;
    }

    bool hasonlit(string filmcim1, string filmcim2)
    {
        for(string tipus1: filmek[filmcim1])
        {
            if(filmek[filmcim2].find(tipus1)!=filmek[filmcim2].end())
            {
                return true;
            }
            for(set<string> alias_csoport: aliasok)
            {
                if(alias_csoport.find(tipus1)!=alias_csoport.end())
                {
                    for(string alias_cim: alias_csoport)
                    {
                        if(filmek[filmcim2].find(alias_cim)!=filmek[filmcim2].end())
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    void alias(string tipus1, string tipus2)
    {
        for(set<set<string>>::iterator it=aliasok.begin(); it!=aliasok.end(); it++)
        {
            if(it->find(tipus1)!=it->end())
            {
                set<string> regi_aliasok = *it;
                aliasok.erase(it);
                regi_aliasok.insert(tipus2);
                aliasok.insert(regi_aliasok);
                return;
            }
            if(it->find(tipus2)!=it->end())
            {
                set<string> regi_aliasok = *it;
                aliasok.erase(it);
                regi_aliasok.insert(tipus1);
                aliasok.insert(regi_aliasok);
                return;
            }
        }
        set<string> uj_alias;
        uj_alias.insert(tipus1);
        uj_alias.insert(tipus2);
        aliasok.insert(uj_alias);
    }


    void unalias(string tipus1, string tipus2)
    {
        for(set<set<string>>::iterator it=aliasok.begin(); it!=aliasok.end(); it++)
        {
            if(it->find(tipus1)!=it->end())
            {
                if(it->find(tipus2)!=it->end())
                {
                    set<string> regi_aliasok = *it;
                    regi_aliasok.erase(tipus2);
                    aliasok.erase(it);
                    aliasok.insert(regi_aliasok);
                    return;
                }
            }
        }
    }
};

int main()
{
    Valasztek v;
    v.uj("Casablanca");
    v.uj("Titanic");
    v.uj("The Guns of Navarone");
    v.uj_cimke("Casablanca", "romantic");
    v.uj_cimke("Casablanca", "war");
    v.uj_cimke("Titanic", "romance");
    v.uj_cimke("The Guns of Navarone", "war");
    v.uj("Hirado"); // nincs cimke
    v.mindent_kiir(); // Casablanca: [ romantic ] [ war ] , Hirado: , The Guns of Navarone: [ war ] , Titanic: [ romance ]
    cout << v.hasonlit("Casablanca", "The Guns of Navarone") << endl; // 1;
    cout << v.hasonlit("Casablanca", "Titanic") << endl; // 0;
    v.alias("romantic", "romance");
    v.mindent_kiir(); //Casablanca: [ romance romantic ] [ war ] , Hirado: , The Guns of Navarone: [ war ] , Titanic: [ romance romantic ]
    cout << v.hasonlit("Casablanca", "The Guns of Navarone") << endl; // 1;
    cout << v.hasonlit("Casablanca", "Titanic") << endl; // 1;
    cout << v.hasonlit("The Guns of Navarone", "Titanic") << endl; // 0;
    v.unalias("romantic", "romance");
    cout << v.hasonlit("Casablanca", "Titanic") << endl; // 0;
    cout << v.hasonlit("Hirado","Casablanca") << endl; // 0
    v.mindent_kiir(); // Casablanca: [ romantic ] [ war ] , Hirado: , The Guns of Navarone: [ war ] , Titanic: [ romance ]

    return 0;
}
