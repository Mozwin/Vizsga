#include <iostream>
#include <set>
#include <list>
#include <map>

using namespace std;

struct Lepes
{
    int hova_x=0;
    int hova_y=0;
    int x=0;
    int y=0;
    Lepes(int _x, int _y)
    {
        x=_x;
        y=_y;
    }
    void lep (int _x, int _y)
    {
        hova_x=_x;
        hova_y=_y;
    }
    void ugrik(int _x, int _y)
    {
        hova_x=_x;
        hova_y=_y;
    }
};

class Dama
{
    set<pair<int,int>> babuk; //x,y
public:

    bool vanebabu (int x, int y)
    {
        if(babuk.find(make_pair(x,y))!=babuk.end())
        {
            return true;
        }
        return false;
    }

    void uj_babu(int x, int y)
    {
        babuk.insert(make_pair(x,y));
    }
    bool szabalyos_e(Lepes lp)
    {
        if(lp.hova_y>lp.y && vanebabu(lp.x, lp.y))
        {
            if(lp.hova_y == lp.y+1 && lp.hova_x == lp.x-1 && !vanebabu(lp.hova_x, lp.hova_y)) //balra fel
            {
                return true;
            }
            if(lp.hova_y == lp.y+1 && lp.hova_x == lp.x+1 && !vanebabu(lp.hova_x, lp.hova_y)) //jobbra fel
            {
                return true;
            }
            if(lp.hova_y == lp.y+2 && lp.hova_x == lp.x-2 && !vanebabu(lp.hova_x, lp.hova_y) && vanebabu(lp.hova_x+1,lp.hova_y-1)) //balra ugrik
            {
                return true;
            }
            if(lp.hova_y == lp.y+2 && lp.hova_x == lp.x+2 && !vanebabu(lp.hova_x, lp.hova_y) && vanebabu(lp.hova_x-1,lp.hova_y-1)) //jobbra ugrik
            {
                return true;
            }
        }
        return false;
    }
    void meglep(Lepes lp)
    {
        if(szabalyos_e(lp))
        {
            babuk.erase(make_pair(lp.x, lp.y));
            babuk.insert(make_pair(lp.hova_x, lp.hova_y));
        }
    }

};

int main()
{
Dama d;
d.uj_babu(1,1); //x,y koordináták, az y nő az ellenfél felé
d.uj_babu(0,0);
d.uj_babu(2,0);
Lepes lp(1,1); // az 1,1 koordinátán álló bábu akar majd lépni
lp.lep(2,2);
cout << d.szabalyos_e(lp); // "1",  szabályos lépés, egy átlós előre lépés. A szabályosságvizsgálat NEM lépi meg a lépést
Lepes lp2(0,0);
lp2.ugrik(2,2);
cout << d.szabalyos_e(lp2); // "1",  szabályos ugrás, egy saját bábut (1,1) átlós előre átugrás.
d.uj_babu(1,3);
lp2.ugrik(0,4); // lp2 ugrássorozat folytatódik
cout << d.szabalyos_e(lp2); // "1",  szabályos ugrássorozat, az (1,1)-et átugorva (2,2)-re, onnan (1,3)-at átugorva (0,4)-re érkezünk
d.meglep(lp); // az lp lépés megtétele
cout << d.szabalyos_e(lp2); // "0",  szabálytalan ugrássorozat, az (1,1)-et átugorva juthatnánk (2,2)-re, de az (1,1)-en már nincs bábu
Lepes lp3(2,2);
lp3.ugrik(3,3); //szándékosan hibás lépés
cout << d.szabalyos_e(lp3); // "0",  szabálytalan ugrás a szomszéd mező, valamit át kéne ugrani
}
