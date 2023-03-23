#ifndef UTENTE_H
#define UTENTE_H

using namespace std;

class Utente
{
private: 
    // attributi 
    string nome;   
    int punteggio;
    int partite;

public:
    //metodi
    // costruttore
    Utente(string n, int p)
    {
        nome = n;
        punteggio = p;
        partite = 0;
    }

    string getNome() // stampa a schermo il nome
    {
        return nome;
    }
    int getPunteggio()  // stampa a schermo il punteggio
    {
        return punteggio;
    }
    void incrementaPunteggio(int punti) //serve a incrementare il punteggio 
    {
        punteggio += punti;
    }
    void finePartita()  // incrementa la partuita
    {
        partite++;
    }
    int getPartite()    // stampa a schermo il numero di partite 
    {
        return partite;
    }
};
#endif