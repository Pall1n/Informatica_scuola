/*
Realizzare un programma che permetta di simulare la gestione di un ATM (Automated Teller Machine).
L'ATM ha una disponibilità iniziale di: 6000€;
L'utente può effettuare sia prelievi che versamenti;
Il limite giornaliero di prelievo è di: 250€;
Per ogni transazione è necessario indicare il PIN.
*/

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <string>

using namespace std;

string username[] = {"Paolo", "Mario", "Salvador", "Marco", "Gennaro", "Mortadella", "Francesca", "Chiara"};
string password[] = {"Ciao", "12345", "Spagna", "Rapina", "Poesia", "Pancetta", "Francia", "Mare"};
int soldi_user[] = {7000, 2000, 4500, 3800, 9000, 2700, 5100, 8400};
int limite_ritiro[] = {250,300,600,250,200,400,150,250};
int soldi_disponibili = 6000;
int lunghezza_informazioni = sizeof(username)/sizeof(username[0]);

class Atm{
    public:
    void clear(){
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
    
    void homepage(int i){
        string scelta;
        while(true){
            sleep(1);
            clear();
            cout<<"Benvenuto, "<<username[i]<<", hai "<<soldi_user[i]<< "€ e l'ATM dispone di "<<soldi_disponibili<<"€.\n\n"
            "Scegli cosa vuoi fare: \n"
            "1) Preleva (limite di "<<limite_ritiro[i]<<"€ possibile);\n"
            "2) Deposita;\n"
            "3) Esci.\n\n"
            "Scelta: ";
            cin>>scelta;
            if(scelta == "1") soldi_user[i] -= ritiro(i);
            else if(scelta == "2") soldi_user[i] += deposito();
            else if(scelta == "3") break;
            else{
                cout<<"Scelta non valida, riprova.\n";
                sleep(1);
            }
        }
    }
    
    int ritiro(int i){
        string PIN = verify_pin(), stringa_ritiro;
        int soldi_ritiro;
        while(limite_ritiro[i] > 0 && PIN == "Ok"){
            sleep(1);
            clear();
            cout<<"Quanto vuoi ritirare? ";
            cin>>stringa_ritiro;
            for(char carattere : stringa_ritiro){
                if(isdigit(carattere))continue;
                else{
                    cout<<"\nValore non valido, ritorno alla homepage...\n";
                    sleep(1);
                    return 0;
                }
            }
            soldi_ritiro = stoi(stringa_ritiro);
            if(soldi_ritiro > 0 && soldi_ritiro <= soldi_user[i] && limite_ritiro[i] - soldi_ritiro >= 0 && soldi_disponibili - soldi_ritiro >= 0){
                limite_ritiro[i] -= soldi_ritiro;
                soldi_disponibili -= soldi_ritiro;
                return soldi_ritiro;
            }
            else if(soldi_ritiro == 0){
                cout<<"\nTorno alla homepage...\n";
                return 0;
            }
            else if(soldi_ritiro < 0) cout<<"\nNon puoi valori negativi, riprova.\n";
            else if(limite_ritiro[i] - soldi_ritiro < 0){
                cout<<"\nRitiro non accettato, è necessario ritirare un valore minore per non superare il limite, riprova.\n";
                sleep(1);
            }
            else if(soldi_disponibili - soldi_ritiro < 0){
                cout<<"\nRitiro non accettato, l'ATM non dispone dei soldi richiesti, riprova con un valore minore.\n";
                sleep(1);
            }
        }
        if(PIN != "Ok") return 0;
        cout<<"\nHai superato il limite di ritiro, ritorno alla homepage...\n";
        sleep(2);
        clear();
        return 0;
    }

    int deposito(){
        string PIN = verify_pin(), stringa_deposito;
        int soldi_deposito;
        while(PIN == "Ok"){
            sleep(1);
            clear();
            cout<<"Quanto vuoi depositare? ";
            cin>>stringa_deposito;
            for(char carattere : stringa_deposito){
                if(isdigit(carattere))continue;
                else{
                    cout<<"\nValore non valido, ritorno alla homepage...\n";
                    sleep(1);
                    return 0;
                }
            }
            soldi_deposito = stoi(stringa_deposito);
            if(soldi_deposito > 0){
                soldi_disponibili += soldi_deposito;
                return soldi_deposito;
            }
            else if(soldi_deposito == 0){
                cout<<"\nTorno alla homepage...\n";
                return 0;
            }
            else cout<<"\nNon puoi depositare valori negativi, riprova.\n";
        }
        return 0;
    }
    
    int login(){
        string username_login, password_login;
        while(true){
            sleep(1);
            clear();
            cout<<"Inserisci username: ";
            cin>>username_login;
            cout<<"Inserisci password: ";
            cin>>password_login;
            
            for(int i = 0; i < lunghezza_informazioni; i++){
                if(username[i] == username_login && password[i] == password_login) return i;
                else continue;
            }
            cout<<"\nUsername e/o password non riconosciuti, riprova.\n";
        }
    }
    
    string verify_pin(){
        string PIN;
        char consonante;
        int somma = 0, consonanti = 0;
        const char alfabeto[27] = {'0','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        cout<<"Inserisci il PIN: ";
        cin>>PIN;
        for(char carattere : PIN){
            if(isdigit(carattere)) somma += carattere - '0';
            else if(consonanti != 0) return "Nope";
            else{
                consonanti += 1;
                consonante = carattere;
            }
        }
        if(alfabeto[somma] == consonante && somma > 0 && PIN.length() == 4) return "Ok";
        else{
            cout<<"\nPIN errato, ritorno alla homepage...\n";
            sleep(1);
            return "Nope";
        }
    }
};

Atm atm;

int main(){
    int i = atm.login();
    atm.homepage(i);
    return 0;
}