#include <iostream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Konfig
{
    map<string,set<string>> pc; //map<kategoria,set<tipus>>
    public:
    void uj_kategoria(string tipus)
    {
        pc[tipus];
    }
    void uj_elem(string tipus, string ertek)
    {
        pc[tipus].insert(ertek);
    }
    bool egyertelmu_e(string tipus1, string tipus2, string tipus3)
    {
        vector<string> v;
        vector<string> volt;
        v.push_back(tipus1);
        v.push_back(tipus2);
        v.push_back(tipus3);
        int hattertar=0;
        int proci=0;
        int monitor=0;
        for(int i=0; i<v.size(); i++)
        {
            if(find(volt.begin(), volt.end(), v[i])== volt.end())
            {
                volt.push_back(v[i]);

                if(pc["hattertar"].find(v[i])!=pc["hattertar"].end())
                {
                    hattertar++;
                }
                if(pc["processzor"].find(v[i])!=pc["processzor"].end())
                {
                    proci++;
                }
                if(pc["monitor"].find(v[i])!=pc["monitor"].end())
                {
                    monitor++;
                }
            }
        }
        cout<<hattertar<<"; "<<proci<<"; "<<monitor<<endl;
        if(hattertar + proci + monitor >= 5)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

int main()
{
 Konfig k;
    k.uj_kategoria("hattertar");
    k.uj_kategoria("processzor");
    k.uj_kategoria("monitor");
    k.uj_elem("hattertar","Sandisk");
    k.uj_elem("hattertar","Samsung");
    k.uj_elem("hattertar","Toshiba");
    k.uj_elem("hattertar","WD");
    k.uj_elem("processzor","Intel");
    k.uj_elem("processzor","AMD");
    k.uj_elem("monitor","Samsung");
    k.uj_elem("monitor","LG");
    k.uj_elem("monitor","Toshiba");
    cout << k.egyertelmu_e("Samsung","Samsung","AMD") << endl; // 1
    cout << k.egyertelmu_e("Intel","Samsung","WD") << endl; // 1
    cout << k.egyertelmu_e("AMD","Samsung","Toshiba") << endl; // 0
}
