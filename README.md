// Copyright \[2020\] IGNAT Andrei-Horia 314CA

		Fisierul MainPlaylist.c

	Contine main-ul programului. Deschid fisierele de input si output date ca
parametri in linie de comanda. Citesc din fisierul de input toate operatiile
si pastrez comanda in com; si numele fisierului, din care extrag date despre
melodii, in mel.

	Pentru fiecare melodie, deschid fisierul corespunzator si extrag datele din 
el (titlu, album, artist, an). Apoi verific ce comanda trebuie sa execute
programul si apelez o functie corespunzatoare din fisierul Playlist.c.

	Folosesc o lista dublu inlantuita pe care o aloc si o initializez, iar la
fiecare comanda execut prelucrari asupra ei.


		Fisierele Playlist.c si Playlist.h

	Contin functiile utilizate. Fiecare functie add del move si show realizeaza
operatia ceruta; cele in care trebuie afisat ceva, au ca parametru fisierul de
output (aceste functii contin explicatii suplimentare in comentarii pentru
fiecare caz considerat). Folosesc 3 alte functii ajutatoare:

init - initializeaza lista;

exist - verifica daca o melodie asupra careia se executa o operatie, exista deja
in playlist

free_list - elibereaza memoria folosita

