#define _CRT_SECURE_NO_WARNINGS
#define NUMERO_TIPI 4
/*
Un ufficio vuole realizzare un sistema per il monitoraggio delle operazioni effettuate.
Le operazioni che possono essere effettuate sono caratterizzate dalle seguenti informazioni
-	Tipo di operazione (un intero compreso tra 0 e 3)
-	Un codice del cliente che effettua l�operazione (una stringa di 7 caratteri utili)
-	Un tempo richiesto per l�operazione espresso in secondi

L�archivio � organizzato con file testo in cui in ogni riga sono inserite separate da spazio bianco
le informazioni relative ad una operazione.

Lo studente implementi un programma ANSI C con un opportuno main in cui sia previsto un menu di scelta
delle operazioni richieste. Tutti i valori necessari al funzionamento devono essere passati utilizzando parametri,
non � permesso l�uso di variabili globali.

Le funzioni 2 e 3 e 4 devono essere implementate utilizzando le informazioni presenti in memoria centrale
1.	Funzione carica:    consente di copiare i dati presenti nel file in un vettore di liste ordinate rispetto
                        al codice del cliente. Ogni lista contiene solo un tipo specifico di operazione.
2. Funzione stampa:    stampa il contenuto della struttura presente in memoria centrale
3. Funzione calcolo_minuti:   restituisce il numero totale di minuti di operazioni relative ad un cliente
                        il cui codice � passato come parametro

4. Funzione lista_operazioni:  restituisce un vettore che contiene le liste delle operazioni effettuate da ciascun
                        cliente. In ogni elemento del vettore sar� quindi presente la lista delle operazioni
                        effettuate da un cliente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definizione struttura dati
typedef struct s_operazione {
    int tipo, durata;
    char codice[8];
} t_operazione;
typedef struct s_nodo {
    t_operazione info;
    struct s_operazione* next;
} t_nodo, * t_lista;

/***** Funzioni primitive per uso lista ******/
//makenullList restituisce la lista vuota
t_lista lista_inizializza() {
    return NULL;
}
//test lista vuota
int lista_vuota(t_lista l) {
    if (l == NULL)
        return 1;
    return 0;
}
/*
    inseririmento in testa di una operazione,
    restituisce 1 se l�operazione � avvenuta con successo, 0 altrimenti
*/
int lista_inserisci(t_lista* pl, t_operazione op) {
    t_lista aux;
    aux = (t_lista)malloc(sizeof(t_nodo));
    if (aux == NULL)
        return 0;
    aux->info = op;
    aux->next = *pl;
    *pl = aux;
    return 1;
}
/*
    funzione inserimento ordinato in lista
    restituisce 1 se l�inserimento a avuto successo 0 altrimenti
*/
int lista_inserisci_ordine(t_lista* pl, t_operazione op) {
    if (lista_vuota(*pl) || (strcmp((*pl)->info.codice, op.codice) < 0))
        return lista_inserisci(pl, op);
    return lista_inserisci_ordine(&((*pl)->next),op);//devo far scorrere la lista fino a quando non entro nell'if
}

//altre funzioni di utilita  // io questa non la metterei....
void stampa_operazione(t_operazione op) {
    printf("\noperazione = % d, cliente % s, durata % d \n", op.tipo, op.codice, op.durata);
}

int menu(void) {
    int scelta;
    printf("\n 1) esegui quesito 1");
    printf("\n 2) esegui quesito 2");
    printf("\n 3) esegui quesito 3");
    printf("\n 4) esegui quesito 4");
    printf("\n 0) esci dal programma\n>> ");
    scanf("%d", &scelta);
    return scelta;
}

// Quesito 1: funzione carica 
void carica(t_lista* vettore_liste, char* nome_file) { 
    //deferenzia la lista, nome file viene passato per puntatore (più leggero, ma sarebbe meglio mettere const affichè non possa essere modificato)
    t_operazione op; // t_lista aux; //potevo dichiarare t_operazione op, anzichè t_lista aux, e sarebbe aux->info = op
    FILE* f;
    f = fopen(nome_file,"r");
    
    if (f == NULL) {
        return 0;
    }
    while (fscanf(f, "%d%s%d", &op.tipo, op.codice, &op.durata) == 3) {

            lista_inserisci_ordine(&vettore_liste[op.tipo], op); 
            // vettore liste è un vettore di 4 elementi in cui organizzo le operazioni per tipo. quindi devo passare tipo
            //ma perchè dentro lista_inserisci_ordine passa &((*pl)->next) ?
    }
    fclose(f);
}

// Quesito 2: funzione stampa
void stampa(t_lista lista) {
    while (lista != NULL) {
        printf("\n Codice cliente %s : operazione tipo %d durata %d ", lista->info.codice, lista->info.tipo, lista->info.durata);
        lista = lista->next;
    }
}

// Quesito 3: calcolo_minuti
int calcolo_minuti(t_lista* vettore_liste, char* codice_cliente) {
    int minuti_tot = 0;
    for (int i = 0; i < NUMERO_TIPI; i++) {
        int minuti = calcolo_minuti_archivio(vettore_liste[i],codice_cliente);
        minuti_tot = minuti_tot + minuti;
    }
    return minuti_tot;
}

int calcolo_minuti_archivio(t_lista lista, char* codice) {
    int minuti = 0;
    while (lista != NULL) {
        if (strcmp(lista->info.codice, codice) == 0) {
            minuti = minuti + lista->info.durata;
        }
        lista = lista->next;
    }
    return minuti;
}

/* Quesito 4: lista_operazioni,
// Funzione che restituisce un vettore che contiene le liste delle operazioni effettuate dai clienti.
// In ogni elemento del vettore sar� presente la lista delle operazioni effettuate da un cliente*/
t_lista* lista_operazioni(t_lista* vettore_liste) {
    //conteggio il numero di elementi contenenti per ogni lista
    // call a conteggi dove scorro le liste cercando il codice
    //alloco il vettore 
}

void stampa_archivio(t_lista archivio[]) {
    for (int i = 0; i < NUMERO_TIPI; ++i)
        stampa(archivio[i]);
}


//main

int main(void) {
    t_lista archivio[NUMERO_TIPI];
    //aggiungere definizione di eventuali altre variabili necessarie ed inizializzazioni
    int scelta;
    char buffer[128];
    int minuti;

    for (int i = 0; i < NUMERO_TIPI; i++) {
        archivio[i] = lista_inizializza();
    }

    do {
        scelta = menu();
        switch (scelta) {
        case 1:     // inserire le istruzioni per l'acquisizione del nome del file, la chiamata della funzione 
                    // del quesito 1 e la stampa dei risultati 
            printf("\nInserire il nome del file:   ");
            scanf("%s", buffer);
            //carica(t_lista *vettore_liste,char *nome_file);
            carica(archivio,buffer); //t_lista è definita come puntatore ed una stringa è un vettore
            printf("L'archivio è stato riempito:\n");
            stampa_archivio(archivio);

            break;
        case 2:     // inserire le istruzioni per l'esecuzione della funzione del quesito 2 
                    // e la stampa dei risultati

            stampa_archivio(archivio); //& non serve perchè un vettore è come un puntatore (come %s in scanf)
            break;
        case 3:     // inserire qua le istruzioni per l'acquisizione del codice cliente, la chiamata della 
                    // funzione del quesito 3 e la stampa dei risultati
            printf("\nInserisci il codice cliente : ");
            scanf("%s", buffer);
            //int calcolo_minuti(t_lista * vettore_liste, char* codice_cliente);
            minuti = calcolo_minuti(archivio, buffer); 
            //passo archivio perchè è richiesto * t_lista, ma t_lista è già definita *, quindi ** = radice
            printf("\nIl cliente codice %s ha un totale di durata operazioni : %d", buffer, minuti);
            break;
        case 4:     //inserire le istruzioni per la chiamata della funzione del quesito 4 e 
                    // la stampa dei risultati
            break;
        }
    } while (scelta != 0);
}

//scrivere di seguito le implementazioni delle funzioni richieste 

