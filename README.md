# MusicPlaylist

## Despre

Proiectul simuleaza un playlist cu diverse melodii asupra caruia se pot executa
diferite operatii, cum ar fi:

* de adaugare:
  1. ADD_FIRST <nume melodie> → adaugă o melodie la începutul listei
  2. ADD_LAST <nume melodie> → adaugă o melodie la finalul listei
  3. ADD_AFTER <nume melodie> → adaugă o melodie după cursor

* de eliminare:
  1. DEL_FIRST → șterge melodia de la începutul listei
  2. DEL_LAST → șterge melodia de la finalul listei
  3. DEL_CURR → șterge melodia curentă (melodia către care pointează cursorul)
  4. DEL_SONG <nume melodie> → șterge melodia, dacă aceasta există în listă

* de deplasare cursor:
  1. MOVE_NEXT → mută cursorul la următoarea melodie (dacă s-a ajuns la finalul
listei, comanda este ignorată)
  2. MOVE_PREV → mută cursorul la melodia anterioară (dacă s-a ajuns la începutul
listei,
  3. comanda este ignorată)

* de afisare:
  1. SHOW_FIRST → afișează informații despre melodia de la începutul listei
  2. SHOW_LAST → afișează informații despre melodia de la finalul listei
  3. SHOW_CURR → afișează informații despre melodia curentă (cea pe care este
setat cursorul)
  4. SHOW_PLAYLIST → afișează pentru toate melodiile din listă titlul

Mai multe detalii despre enunt se pot gasi [aici](https://ocw.cs.pub.ro/courses/sd-ca/teme/tema1-2020).

## Continut repo

### Folderele in out ref songs

Asa cum le spune si numele, *in* contine fisierele de input, *out* de output
si *ref* contine rezultatele care ar trebui obtine in urma executiei programului.
Fisierele din folderul *in* contin o serie de comenzi de tipul celor de mai sus.

Folderul *songs* contine fisierele de tip melodii, ce contin diverse informatii
despre acele cantece, cum ar fi *nume*, *autor*, *anul aparitiei*, *album*.

### Rulare

Pentru a rula programul, se folosesc comenzile:

* make - pentru a compila
* ./playlist in/test*number*.in out/test*number*.out - pentru a testa aplicatia
pe testul *number*.
* diff out/test*number*.out ref/test*number*.ref - iar daca nu se obtine niciun
output in terminal, inseamna ca cele doua fisiere sunt identice, deci aplicatia
ruleaza corespunzator.

## Detalii implementare

### Fisierul MainPlaylist.c

Contine main-ul programului. Deschid fisierele de input si output date ca
parametri in linie de comanda. Citesc din fisierul de input toate operatiile
si pastrez comanda in com; si numele fisierului, din care extrag date despre
melodii, in mel.

Pentru fiecare melodie, deschid fisierul corespunzator si extrag datele din 
el (titlu, album, artist, an). Apoi verific ce comanda trebuie sa execute
programul si apelez o functie corespunzatoare din fisierul Playlist.c.

Folosesc o lista dublu inlantuita pe care o aloc si o initializez, iar la
fiecare comanda execut prelucrari asupra ei.


### Fisierele Playlist.c si Playlist.h

Contin functiile utilizate. Fiecare functie add del move si show realizeaza
operatia ceruta; cele in care trebuie afisat ceva, au ca parametru fisierul de
output (aceste functii contin explicatii suplimentare in comentarii pentru
fiecare caz considerat). Folosesc 3 alte functii ajutatoare:

* init - initializeaza lista;

* exist - verifica daca o melodie asupra careia se executa o operatie, exista deja
in playlist

* free_list - elibereaza memoria folosita

