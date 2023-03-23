#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include "Utente.h"
using namespace std;
int main()
{
    ifstream fileQuestAnswer("domandeRisposte.txt");   // apro file di tutte domande risposte
    ifstream fileRisposteGiuste("risposteGiuste.txt"); // apro file di tutte risposte giuste

    //controlle se in file è aperto bene 
    if ((fileQuestAnswer.is_open()) && (fileRisposteGiuste.is_open())) 
    {
        cout << "      =======================================================================================       \n";
        cout << "     //     _______      ______      ___   ____   ___     ___     ______     ___           //      \n";
        cout << "    //    /_    _ /    /  _   /     /  /   |  |  /  /    /  /    / _   /    /  /          //       \n";
        cout << "   //       /  /      / /  / /     /  /    |  | /  /    /  /    / /_/ /    /  /          //        \n";
        cout << "  //       /  /      / /  | |     /  /     |  |/  /    /  /    / / / /    /  /____      //         \n";
        cout << " //       /_ /      /_/   |_|    /__/      |_____/    /__/    /_/ /_/    /_______/     //          \n";
        cout << "//                                                                           c++rsuit //           \n";
        cout << "=======================================================================================                                                                                               \n";
    }
    else
    {
        cout << "noFile" << endl;
    }
    
    //parte il gestionale
    cout << "Inserisci il tuo nome: " << endl;
    string nome;
    cin >> nome;
    int punteggio;

    // apro il file
    ifstream fileUtenti;
    fileUtenti.open("utenti.txt");

    // cerco il nome
    string riga;
    bool nuovo = true;
    while (getline(fileUtenti, riga))
    {
        if (riga == nome)
        {
            // trovato
            nuovo = false;
            getline(fileUtenti, riga);
            punteggio = stoi(riga);
            break;
        }
    }
    fileUtenti.close();

    // se non lo trovo lo creo
    if (nuovo)
    {
        punteggio = 0;
    }

    Utente giocatore = Utente(nome, punteggio);

    //faccio la partita
    srand(time(NULL)); // random sull orario

    bool domandeGiaChieste[30]; // mi serve per non ripetere la stessa domanda

    for (int y = 0; y < 30; y++)
    {
        domandeGiaChieste[y] = false; // tutto l'arrey è inizialmente falso, diventa vero quando faccio una domanda
    }
    // da qui proviamo while giro domande
    int domandeRimaste = 5; // imposto che in gioco finisce dopo 5 domande
    int contaGiuste=0;
    
    while (domandeRimaste > 0)
    {
        ifstream fileQuestAnswer("domandeRisposte.txt");   // riapro il file delle domande
        ifstream fileRisposteGiuste("risposteGiuste.txt"); // riapro il file delle risposte
        int indiceDomanda = 0;                             // mi serve per scegliere un numero per la domanda
        int rigaDomanda = 0;                               // vado a leggere la riga corrispondente nel file domande

        do
        {
            indiceDomanda = rand() % 30;
        } while (domandeGiaChieste[indiceDomanda] == true); // se in quella posizione trovo vero, trova un altro numero random
        
        domandeGiaChieste [indiceDomanda] = true; //imposto quella domanda a true

        rigaDomanda = indiceDomanda * 5 + 1; // il testo delle domande si trova ogni 5 righe+1

        string questAnswer; // file stampato su stringa

        int contatore = 0;  // contatore su righe da stampare
        string risposte[5]; // salvo le possibili risposte il un array di appoggio

        cout << endl;
         cout << "------------------" << endl;
        cout << "Domanda numero " << indiceDomanda + 1 << endl;
        cout << "------------------" << endl;

        while (getline(fileQuestAnswer, questAnswer))
        {
            contatore++;
            if (contatore == rigaDomanda)
            {
                cout << questAnswer << endl;
                cout << endl; // stampo lariga della domanda
            }

            for (int i = 1; i < 5; i++)
            {
                if (contatore == rigaDomanda + i)
                {
                    risposte[i] = questAnswer;
                    cout << i << ". " << questAnswer << endl; // stampo le succhessive 4 righe con le possibili risposte e gli indici
                }
            }
        }
        cout << endl;
        cout << "Seleziona la risposta giusta da 1 a 4: " << endl;
        int numeroRisposta = 0;
        cin >> numeroRisposta;

        while((numeroRisposta<1) || (numeroRisposta>4))
        {
            cout<< " Scegli un numero da 1 a 4. "<< endl;
            cin >> numeroRisposta;
        }

        string risposteGiuste;
        int trovaRiga = 0; // conta le righe fino a indice domanda
        bool seGiusto = false;
        string correzione = "";

        while (getline(fileRisposteGiuste, risposteGiuste))
        {
            trovaRiga++;
            if ((trovaRiga == indiceDomanda + 1) && (risposte[numeroRisposta] == risposteGiuste)) // confronto prima gli indici delle righe e poi se le stringhe sono uguali 
            {
                contaGiuste+=10;
                seGiusto = true;
            }
            else if ((trovaRiga == indiceDomanda + 1) && (risposte[numeroRisposta] != risposteGiuste))
            {
                correzione = risposteGiuste;
            }
        }

        if (seGiusto == true)
        {
            cout << "La risposta e' GIUSTA" << endl;
        }
        else
        {   
            cout << "Purtoppo hai SBAGLIATO" << endl;
            cout << "La risposta corretta e': " << correzione << endl;
        }
        int indiceRiga = 0;
        while (getline(fileRisposteGiuste, risposteGiuste))
        {
            indiceRiga++;
            if (indiceRiga == indiceDomanda + 1)
            {
                cout << risposteGiuste << endl; 
            }
        }

        domandeRimaste--;  // decremento dal numero di domande iniziali
        fileQuestAnswer.close();
        fileRisposteGiuste.close();
    }

    //fine partita 
    giocatore.finePartita();
    // incremento punteggio
    giocatore.incrementaPunteggio(contaGiuste);
    // vedere nome
    cout << "------------------" << endl;
    cout << "Il gioco e' terminato. "<< endl;
    cout << "------------------" << endl;
    cout << giocatore.getNome() << endl;
    // vedere il punteggio
    cout << giocatore.getPunteggio() << endl;
    // vedere partite giocate
    cout << giocatore.getPartite() << endl;
    cout << "------------------" << endl;

    //se ho un nuovo giocatore
    if (nuovo)
    {
        // nuovo giocatore, aggiungo alla fine
        // leggo vecchio file
        ifstream fileUtenti2;
        ofstream fileTemporaneoS; //scrivo il file temporaneo
        fileTemporaneoS.open("utentiTemp.txt"); //file di appoggio
        fileUtenti2.open("utenti.txt");
        while (getline(fileUtenti2, riga)) //leggo tutto il file 
        {
            fileTemporaneoS << riga << endl;
        }
        fileTemporaneoS << giocatore.getNome() << endl; // alla fine aggiungo giocatore nuovo
        fileTemporaneoS << giocatore.getPunteggio() << endl; // e punteggio nuovo 

        fileUtenti2.close();
        fileTemporaneoS.close();

        ifstream fileTemporaneoL; //leggo dal file temporaneo
        ofstream fileUtentiFinal; // riscrivo il file originale

        fileTemporaneoL.open("utentiTemp.txt");
        fileUtentiFinal.open("utenti.txt");

        while (getline(fileTemporaneoL, riga)) //leggo dal file temporaneo 
        {
            fileUtentiFinal << riga << endl; // scrivo nel file utenti
        }

        fileTemporaneoL.close();
        fileUtentiFinal.close();
    }
    else 
    {
        // giocatore con esperienza, modifico il punteggio
        // leggo vecchio file Utenti
        ifstream fileUtenti2;
        ofstream fileTemporaneoS; //scrivo nel file temporaneo
        fileTemporaneoS.open("utentiTemp.txt");
        fileUtenti2.open("utenti.txt");
        
        while (getline(fileUtenti2, riga)) //leggo tutto il file utenti 
        {
            if (riga == giocatore.getNome()) //fino a quando non trovo nome corrispondente
            {
                fileTemporaneoS << riga << endl; //scrivo il nome giocatore (riga)
                fileTemporaneoS << giocatore.getPunteggio() << endl; //modifico il punteggio (punteggio+=contaGiuste)
                getline(fileUtenti2, riga);//vado avanti con le altre righe
            }
            else
            {
                fileTemporaneoS << riga << endl; // se non trovo il nome vado avanti a scrivere le righe
            }
        }

        fileUtenti2.close(); //chiudo tutti i file
        fileTemporaneoS.close();

        ifstream fileTemporaneoL; // riapro il file temporaneo in lettura
        ofstream fileUtentiFinal; //e scrivo nel file Utenti il nuovo punteggio 

        fileTemporaneoL.open("utentiTemp.txt");
        fileUtentiFinal.open("utenti.txt");

        while (getline(fileTemporaneoL, riga))
        {
            fileUtentiFinal << riga << endl;
        }

        fileTemporaneoL.close();
        fileUtentiFinal.close();
    }
}