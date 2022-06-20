#include<iostream>
#include<map>
#include<set>
#include<list>

using namespace std;

class Ceg
{
    map<string, string> alkalmazottak; //dolgozo, fonok
    map<string, set<string>> munkacsoportok; //csoport dolgozo

public:
    void uj_munkacsoport(string csoport)
    {
        munkacsoportok[csoport];
    }
    void uj_dolgozo(string csoport, string nev)
    {
        munkacsoportok[csoport].insert(nev);
    }
    void fonoke(string ki, string kinek)
    {
        alkalmazottak[kinek]=ki;
    }
    void nincs_hierarchiaban()
    {
        for(pair<string, set<string>>a : munkacsoportok) //a-munkacsopi, dolgozo
        {
            for(string b : a.second)
            {
                bool megvan=false;
                for(pair<string, string> c : alkalmazottak)
                {
                   if(b == c.second || b == c.first)
                   {
                       megvan=true;
                   }
                }
                if(!megvan)
                {
                    cout<<b<<endl;
                }
            }
        }
        cout<<endl;
    }
    string csoportleker(string nev)
    {
        for (pair<string,set<string>> e : munkacsoportok)
        {
            if(e.second.find(nev)!=e.second.end())
            {
                return e.first;
            }
        }
    }

    bool vane_beosztott (string nev)
    {
        bool megvan=false;
        for(string b : munkacsoportok[csoportleker(nev)])
            {
                for(pair<string, string> c : alkalmazottak)
                {
                   if(b == c.second)
                   {
                       megvan=true;
                   }
                }
                if(megvan)
                {
                    return megvan;
                }
            }
            return megvan;
    }

    void munkacsoportvezetok()
    {
        string max_embi="";
        for(pair<string,set<string>> e : munkacsoportok)
        {
            max_embi=*(e.second.begin());
            if(!vane_beosztott(max_embi))
            {
                continue; //fort eggyel előrébb lépteti
            }
           // cout<<(alkalmazottak.find(max_embi) != alkalmazottak.end())<<" , " <<(csoportleker(max_embi) == csoportleker(alkalmazottak[max_embi]))<< ", "<< (vane_beosztott(alkalmazottak[max_embi])) <<endl;
            while(alkalmazottak.find(max_embi) != alkalmazottak.end() && csoportleker(max_embi) == csoportleker(alkalmazottak[max_embi]) && vane_beosztott(alkalmazottak[max_embi]))
            {
                max_embi=alkalmazottak[max_embi];
            }
            cout<<max_embi<<"("<< e.first <<")"<<endl;
        }
        cout<<endl;
    }
};

using namespace std;

int main()
{
    Ceg c;
    c.uj_munkacsoport("Dev");
    c.uj_munkacsoport("MGMT");
    c.uj_munkacsoport("Accounting");
    c.uj_dolgozo("Dev","Coder Peti");
    c.uj_dolgozo("Dev","Hekker Panni");
    c.uj_dolgozo("MGMT","BigBoss");
    c.uj_dolgozo("MGMT","Jozsi");
    c.uj_dolgozo("Accounting","Andras");
    c.uj_dolgozo("Accounting","Bela");
    c.fonoke("BigBoss", "Jozsi");
    c.fonoke("BigBoss", "Andras");
    c.fonoke("Jozsi", "Coder Peti");
    c.fonoke("Hekker Panni", "Coder Peti");
    c.nincs_hierarchiaban(); //kiirja:Bela
    c.fonoke("BigBoss", "Bela");
    c.nincs_hierarchiaban(); //nem ir ki semmit
    c.munkacsoportvezetok(); //kiirja: Coder Peti (Dev) BigBoss(MGMT) , mert ok egy munkacsoporton belüli hierarchiaban mindenkinek a fonokei, Accountingon belül nincs ilyen szerkezet
    c.uj_dolgozo("Dev", "Junior");
    c.fonoke("Hekker Panni", "Junior");
    c.munkacsoportvezetok(); //kiirja: Coder Peti(Dev) BigBoss (MGMT) , mert munkacsopin belül õk mindenkinek a fõnõkei ha nem is közvetlenül
    c.uj_dolgozo("Accounting", "Cecil");
    c.munkacsoportvezetok(); //kiirja: Coder Peti(Dev) BigBoss (MGMT) , mert munkacsopin belül õk mindenkinek a fõnõkei ha nem is közvetlenül
    c.fonoke("Andras", "Cecil");
    c.munkacsoportvezetok(); //kiirja: Coder Peti(Dev) BigBoss (MGMT) , mert munkacsopin belül õk mindenkinek a fõnõkei ha nem is közvetlenül
    c.fonoke("Andras", "Bela"); //nem uj, hanem modositas
    c.munkacsoportvezetok();//kiirja: Andras(Accounting) Coder Peti(Dev) BigBoss(MGMT)
}
