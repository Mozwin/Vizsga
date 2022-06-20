#include <iostream>
#include <set>
#include <list>
#include <map>

using namespace std;

class Nyilvantarto
{
    map<string, set<string>> gyogyszerek; //map<gyogyszer, set<hatoanyag>
    map<string, set<string>> emberek; //map<ember, set<erzekeny_hatoanyag>
    public:
        void uj_gyogyszer(string gy)
        {
            gyogyszerek[gy];
        }
        void hatoanyag(string gy, string h)
        {
            gyogyszerek[gy].insert(h);
        }
        void uj_paciens(string nev)
        {
            emberek[nev];
        }
        void erzekeny(string nev, string gy)
        {
            for(pair<string, set<string>> a : gyogyszerek)
            {
                if(a.first == gy)
                {
                    for(string b:a.second)
                    {
                        emberek[nev].insert(b);
                    }
                }
            }
        }
        string ellenjavallt(string nev, string gy)
        {
            string eredm="";
            for(string a : gyogyszerek[gy]) //a-hatoanyag
            {
                if(emberek[nev].find(a)!=emberek[nev].end())
                {
                    //cout<<eredm<<endl;
                    eredm= eredm + " "+a;
                    //cout<<eredm<<endl;
                }
            }
            if(eredm=="")
            {
                eredm="nem";
            }
            else
            {
                eredm="igen:"+eredm;
            }

            return eredm;
        }
};

int main()
{
   Nyilvantarto n;
n.uj_gyogyszer("gy1");
n.uj_gyogyszer("gy2");
n.uj_gyogyszer("gy3");
n.hatoanyag("gy1", "h1");
n.hatoanyag("gy1", "h2");
n.hatoanyag("gy2", "h2");
n.hatoanyag("gy3", "h1");
n.hatoanyag("gy3", "h3");
n.uj_paciens("Peti");
n.uj_paciens("Vali");
n.erzekeny("Peti", "gy2");
cout << n.ellenjavallt("Peti", "gy3") << endl; // "nem"
cout << n.ellenjavallt("Peti", "gy1") << endl; // "igen: h2"
n.erzekeny("Vali", "gy1");
cout << n.ellenjavallt("Vali", "gy2") << endl; // "igen: h2"
cout << n.ellenjavallt("Vali", "gy3") << endl; // "igen: h1"
cout << n.ellenjavallt("Vali", "gy1") << endl; // "igen: h1 h2", a sorrend mindegy
}
