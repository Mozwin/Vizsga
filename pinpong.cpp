#include <iostream>
#include <map>
#include <set>
#include <vector>

//ujtag
//megtortent egy meccs - utana nincs uj tag
//main csak teszt

//
using namespace std;

struct Bajnoksag
{
    set<pair<string,string>> kikivelnem;
    vector<string> nevek;
public:
    void uj_versenyzo(string nev) //vectorba pakoljuk a nevet
    {
        nevek.push_back(nev);
    }
    void kezdodik()
    {
       for(string a : nevek)
        {
            for (string b : nevek)
            {
                if(a<b) //itt az abc sorrend
                {
                    kikivelnem.insert(make_pair(a,b)); //csinal egy pairt- peldanyt, mindegy milyen tipus (ld fent)
                }
            }
        }
    }
    void jatszott (string ki, string kivel, int ki_pont, int kivel_pont)
    {
       if(ki<kivel)
       {
           kikivelnem.erase(kikivelnem.find(make_pair(ki, kivel)));
       }
       else
        {
            kikivelnem.erase(kikivelnem.find(make_pair(kivel, ki)));
        }
    }
    void ki_kivel_nem_jatszott()
    {
        for (pair<string, string> p : kikivelnem)
        {
            cout << p.first << " " << p.second << endl;
        }
    }
};

int main()
{
    Bajnoksag b;
    b.uj_versenyzo("A");
    b.uj_versenyzo("B");
    b.uj_versenyzo("C");
    b.uj_versenyzo("D");
    b.kezdodik();
    b.jatszott("A", "C", 11, 5);
    b.jatszott("B", "C", 3, 11);
    b.ki_kivel_nem_jatszott();
}
