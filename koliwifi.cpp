#include <iostream>
#include <map>
#include <set>

using namespace std;

class Koli
{
    int eszam;
    int olcso;
    int draga;

    map<int, set<string>> jelentkezettek;

public:
    Koli(int _eszam, int _olcso, int _draga)
    {
        eszam = _eszam;
        olcso = _olcso;
        draga = _draga;
    }

    void dump()
    {
        for(auto emelet: jelentkezettek)
        {
            for(auto ember: emelet.second)
            {
                cout << ember << " " << (draga-olcso)/emelet.second.size() << "Ft" << endl;
            }
        }
    }

    void jelentkezes(int emelet, string nev)
    {
        if(jelentkezettek.find(emelet)==jelentkezettek.end())
        {
            set<string> emberek;
            emberek.insert(nev);
            jelentkezettek[emelet]=emberek;
        }
        else
        {
            jelentkezettek[emelet].insert(nev);
        }
    }

    void megrendeles()
    {
        int dragaszam = 0;
        for(int i=0; i<=eszam; i++)
        {
            if(jelentkezettek.find(i)!=jelentkezettek.end())
            {
                dragaszam+=1;
            }
        }
        cout << "olcso: " << eszam+1-dragaszam << endl;
        cout << "draga: " << dragaszam << endl;
    }

    void visszavon(string nev)
    {
        for(map<int, set<string>>::iterator it = jelentkezettek.begin(); it!=jelentkezettek.end(); it++)
        {
            if(it->second.find(nev)!=it->second.end())
            {
                it->second.erase(it->second.find(nev));
            }
            if(it->second.empty())
            {
                jelentkezettek.erase(it);
            }
        }
    }
};

int main()
{

    Koli k(8, 12000, 58000); //8 emelet (+f�ldszint), 12000 az olcs�, 58000 a dr�ga eszk�z �ra
    k.dump(); // semmi
    k.jelentkezes(3, "Kis Bal�zs");
    k.jelentkezes(4, "Nagy Juli");
    k.jelentkezes(4, "Fekete Zsolt");
    k.dump(); // h�rom t�tel, Kis Bal�zs 46000, Nagy Juli �s Fekete Zsolt fejenk�nt 23000
    k.megrendeles(); // 7 olcs� �s 2 dr�ga
    k.visszavon("Kis Bal�zs");
    k.megrendeles(); // 8 olcs� �s 1 dr�ga

    return 0;
}
