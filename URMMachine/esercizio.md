Esercizio di valuzione programmatore Embedded (9 Febbraio 2023).

Realizzare una versione molto semplice di una URM (https://it.wikipedia.org/wiki/Macchina_URM), con le seguenti specifiche:

0. URM è un modello in grado di eseguire programmi opportunamente codificati in file di input.
1. il file di input è un file binario che rappresenta un insieme di istruzioni da eseguire (programma).
2. ogni istruzione occupa 4 byte e nel file di ingresso viene codificata in modo che:
 * il primo byte letto è il codice dell'istruzione
 * il secondo byte è il valore del primo argomento
 * il terzo byte è il valore del secondo argomento
 * il quarto byte è il valore del terzo argomento
3. ci sono 4 istruzioni: ZERO, INCR, PROJ, JUMP, descritte nella prossima sezione
4. le istruzioni vanno a modificare il valore di speciali aree di memoria chiamate registri. 
5. la macchina supporta 256 registri numerati da 0 a 255
6. le istruzioni nel file-programma vengono numerate progressivamente in base alla loro posizione nel file, partendo da 0
7. se il file di ingresso termina o si esegue un'istruzione di salto che porta l'esecuzione fuori dal file (vedi istruzione 3 del programma di esempio),
allora URM termina con successo.
8. se URM termina con successo, allora l'output dovrà essere il contento del registro 0
9. se URM trova un istruzione non valida termina con un errore


Le istruzioni ammesse sono:

1. ZERO (codice 0): richiede un solo argomento che è il numero di un registro R. Quando URM legge questa istruzione imposta il valore del registro R a 0
1. INCR (codice 1): richiede un solo argomento che è il numero di un registro R. Quando URM legge questa istruzione incrementa il valore del registro R di uno (R++)
2. PROJ (codice 2): richiede 2 argomenti che sono i registri S D rispettivamente. Quando URM legge questa istruzione copia il valore del registro S in D
3. JUMP (codice 3): richiede 3 argomenti, i primi due sono registri A e B e il terzo è il numero di un'istruzione target T nel file. Quando URM legge questa istruzione ci sono due possibili casi (dove con A e B intediamo il contenuto dei registri A e B):
 a. se A != B allora non succede nulla e URM passa all'istruzione successiva
 b. se A == B allora la macchina passa all'istruzione T

Per esempio, dato il file di ingresso (demo.urm):

	'0x0', '0x0', '0x0', '0x0', 
	'0x0', '0x1', '0x0', '0x0', 
	'0x1', '0x1', '0x0', '0x0', 
	'0x3', '0x0', '0x1', '0xff', 
	'0x1', '0x0', '0x0', '0x0', 
	'0x3', '0x0', '0x0', '0x3'

questo rappresenta il programma seguente (la prima colonna indica il numero dell'istruzione)

```
0   zero 0             # mette R0 = 0
1   zero 1             # mette R1 = 0 (R0 = 0)
2   incr 1             # mette R1 = 1 (R0 = 0)
3   jump 0 1 255       # primo passaggio R1 != R0 quindi passa all'istruzione 4. la seconda volta porta all'istruzione 255, quindi al successo del programma.
4   incr 0             # mette R0 = 1 (R1 = 1)
5   jump 0 0 3         # essendo R0 == R0 sempre vero, salta all'istruzione 3
```

che restituisce 1 come output

Viene fornito anche un semplice compilatore scritto in python `urmc.py` che permette di codificare un file sorgente in file di input per l'urm.
Sono inclusi due programmi di esempio test.urm e demo.urm con i relativi sorgenti test.S e demo.S

Realizzare il progetto in C++ usando solo librerie standard.
Fornire un file README con le istruzioni di compilazione

Il progetto dovrà essere caricato su un repository git (ad esempio usando i servizi github o bitbucket) di cui dovrà essere fornito indirizzo per scaricarlo e compilarlo.

La valutazione prevede l'esecuzione del programma test.urm e di un programma non fornito.
Verrà valutata la presentazione del codice oltre al rispetto delle specifiche.
