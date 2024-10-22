/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <string>

using namespace std;

struct Liga{
    
    map<string,set<string>> csapatszemely;
    
    set<string> szemelyek;
    
    void csapat_hozzaad(string csapatnev){
        
        csapatszemely[csapatnev];
        
    }
    
    void jatekos_hozzaad(string szemely){
        
        szemelyek.insert(szemely);
        
    }
    
    void ajanlat(string csapatnev,string szemely){
        
        map<string,set<string>>::iterator fit=csapatszemely.find(csapatnev);
        
        set<string>::iterator fit2=szemelyek.find(szemely);
        
        if(fit==csapatszemely.end()){
            
            cout<<"Ervenytelen csapat: "<<csapatnev<<endl;
            return;
            
        }
        
         if(fit2==szemelyek.end()){
            
            cout<<"Ervenytelen jatekos: "<<szemely<<endl;
            return;
            
        }
        
        for(map<string,set<string>>::iterator it=csapatszemely.begin();it!=csapatszemely.end();it++){
            
            for(set<string>::iterator it2=it->second.begin();it2!=it->second.end();it2++){
                
                if(*it2==szemely){
                    
                    if(it->first!=csapatnev){
                        
                        cout<<"Ervenytelen ajanlat: erre a jatekosra mar van ajanlat ("<<it->first<<")"<<endl;
                        return;
                        
                    }
                    else{
                        
                        cout<<"Ervenytelen ajanlat: erre a jatekosra mar van ajanlat "<<endl;
                        return;
                        
                    }
                    
                }
                
            }
            
            
        }
        
        if(fit->second.size()==3){
            
            cout<<"Ervenytelen ajanlat: adott csapat tett harom ervenyes ajanlatot"<<endl;
            return;
            
        }
        
        csapatszemely.at(csapatnev).insert(szemely);
        
        
    }
    
    void atigazolasok(){
        
        for(map<string,set<string>>::iterator it=csapatszemely.begin();it!=csapatszemely.end();it++){
            
            if(it->second.size()!=0){
                
                cout<<it->first<<": ";        
            
                for(set<string>::iterator it2=it->second.begin();it2!=it->second.end();it2++){
                    
                    cout<<*it2<<", ";
                    
                }
                
                cout<<endl;
                
            }
            
        } 
        
    }
    
};

int main()
{
     Liga liga;

    liga.csapat_hozzaad("FTC");
    liga.csapat_hozzaad("Újpest");
    liga.csapat_hozzaad("Paks");

    liga.jatekos_hozzaad("Bekk Elek");
    liga.jatekos_hozzaad("Bika Béla");
    liga.jatekos_hozzaad("Csuka Ferenc");
    liga.jatekos_hozzaad("Kesztyű Péter");
    liga.jatekos_hozzaad("Pokróc Pál");

    liga.ajanlat("Kispest", "Bekk Elek"); // Ervenytelen csapat: Kispest
    liga.ajanlat("Újpest", "Bodri Kutya"); // Ervenytelen jatekos: Bodri Kutya

    liga.ajanlat("FTC", "Bekk Elek");
    liga.ajanlat("Újpest", "Bekk Elek"); // Ervenytelen ajanlat: erre a jatekosra mar van ajanlat
    liga.ajanlat("FTC", "Bekk Elek"); // Ervenytelen ajanlat: volt mar ilyen ajanlat

    liga.atigazolasok(); // Átigazolások:
                        // FTC: Bekk Elek

    liga.ajanlat("Újpest", "Bika Béla");
    liga.ajanlat("Újpest", "Csuka Ferenc");
    liga.ajanlat("Újpest", "Kesztyű Péter");
    liga.ajanlat("Újpest", "Pokróc Pál"); // Ervenytelen ajanlat: adott csapat tett harom ervenyes ajanlatot
    liga.ajanlat("Paks", "Kesztyű Péter"); // Ervenytelen ajanlat: erre a jatekosra mar van ajanlat

    liga.atigazolasok(); // Átigazolások:
                        // FTC: Bekk Elek
                        // Újpest: Bika Béla, Csuka Ferenc, Kesztyű Péter

    //liga.visszavon("FTC", "Bekk Elek");

    //liga.atigazolasok(); // Átigazolások:
                        // Újpest: Bekk Elek, Bika Béla, Csuka Ferenc
                        // Paks: Kesztyű Péter

    liga.ajanlat("Paks", "Pokróc Pál");

    liga.atigazolasok(); // Átigazolások:
                        // Újpest: Bekk Elek, Bika Béla, Csuka Ferenc
                        // Paks: Kesztyű Péter, Pokróc Pál

    return 0;
}