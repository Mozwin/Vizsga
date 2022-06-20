#include <iostream>#include <iostream>
#include <set>
#include <list>
#include <map>
#include <vector>

using namespace std;

class Projekt
{
  map<string, set<string>> feladatok;  //map<feladat, set<ember>>
  set<pair<string, int>> talalkozok; //feladat, mikor
  map<string, set<int>> idopont; //map<ember,set< mikor>>
  public:
      void uj_reszfeladat(string feladat)
      {
            feladatok[feladat];
      }
      void kulcsember(string feladat, string ember)
      {
            feladatok[feladat].insert(ember);
      }
      void uj_talalkozo(string feladat, int mikor)
      {
            for(string a : feladatok[feladat]) //a-ember
            {
                if(idopont[a].find(mikor)!=idopont[a].end())
                {
                    cout<<a<<" nem er ra"<<endl;
                    return; //ez utan sehova megyek
                }
            }
            talalkozok.insert(make_pair(feladat,mikor));
            for(string a : feladatok[feladat])
            {
                idopont[a].insert(mikor);
            }
      }
      void teljes_naptar_kiir()
      {
          for(pair<string,int> b : talalkozok) //b-feladat-mikor
        {
            cout<<b.first<<": "<<b.second<<endl;
            for(string ember: feladatok[b.first])
            {
                cout << " - " << ember << endl;
            }
        }
      }
};

int main()
{
   Projekt p;

p.uj_reszfeladat("karbantartas");
p.uj_reszfeladat("tervezes");
p.uj_reszfeladat("marketing");
p.kulcsember("karbantartas","Tibi");
p.kulcsember("tervezes","Tibi");
p.kulcsember("tervezes","Zsofi");
p.kulcsember("marketing","Lajos");
p.uj_talalkozo("tervezes", 12);
p.uj_talalkozo("marketing", 12);
p.uj_talalkozo("tervezes", 13);
p.uj_talalkozo("karbantartas", 13); //Ne jegyezze fel, írjon ki hibaüzenetet a kulcsember nevével. Maxpontért visszatérési értékben is jelezni kell a sikerességet, de anélkül is érvényes
p.teljes_naptar_kiir(); //megjelenik valamilyen formaban, hogy melyik nap mi tortenik
}

