#include <iostream>
#include <set>
#include <list>
#include <map>

using namespace std;

struct Festes
{
    map<string, int> elfestett; //festek, meddigvanadoboz%
    void kellBele (string festek, int mennyi)
    {
        elfestett[festek]=mennyi;
    }
};

class Raktar
{
    map<string, pair<int,int>> festekek; //map<festek, pair<doboz db, mddeigvanadoboz %>> //érdemesebb külön szedni?
public:
    void ujFestek(string festek)
    {
       if(festekek.find(festek)==festekek.end())
       {
           festekek[festek]=make_pair(1,100);
       }
       else
       {
           pair<int,int> par = festekek[festek];
           festekek[festek]=make_pair(par.first+1, par.second);
       }
    }
    void dump()
    {
        for(pair<string, pair<int,int>> a : festekek)
        {
            cout<<a.first<<": "<<a.second.second;
            for(int i=0; i<a.second.first-1; i++)
            {
                cout<<" 100";
            }
            cout<<" ";
        }
        cout<<endl;
    }

    bool elegendo(Festes f)
    {
        for(pair<string, int> a : f.elfestett)
        {
            if(festekek[a.first].second < a.second && festekek[a.first].first < 2)
            {
                return false;
            }
        }
        return true;
    }

    void fest(Festes f)
    {
       if(!elegendo(f))
       {
           return;
       }
        for(pair<string, int> a : f.elfestett)
        {
           if(a.second <= festekek[a.first].second)
           {
               pair<int, int> par = festekek[a.first];
               festekek[a.first] = make_pair(par.first, par.second-a.second);
           }
           else
           {
                pair<int, int> par = festekek[a.first];
                int kell = a.second;
                kell-=par.second;
                par=make_pair(par.first-1, 100-kell);
                festekek[a.first] = par;
           }
        }
    }
};


int main()
{
Raktar r;
r.ujFestek("A");
r.ujFestek("A");
r.ujFestek("B");
r.dump(); //A: 100 100   B:100
Festes f1;
f1.kellBele("A", 30);
f1.kellBele("B", 40);
Festes f2;
f2.kellBele("A",60);
f2.kellBele("B",10);
cout << r.elegendo(f1) << endl; //1
r.fest(f1);
r.dump(); //A: 70 100  B:60
cout << r.elegendo(f2) << endl; //1
r.fest(f2);
r.dump(); //A: 10 100  B:50
cout << r.elegendo(f2) << endl; //1
r.fest(f2);
r.dump(); //A: 10 40  B:40
cout << r.elegendo(f2) << endl; //0
cout << r.elegendo(f1) << endl; //1
r.fest(f1);
r.dump(); //A: 10 10  B:0
}
