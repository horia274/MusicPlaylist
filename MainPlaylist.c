// Copyright [2020] IGNAT Andrei-Horia 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Playlist.h"

int main(int argc, char *argv[]) {
	FILE *in, *out, *song;
	struct LinkedList *list;
	struct Info song_data;
	int i, no_songs;
	char com[COMMAND], mel[MELODY], *name_song;

	// verific numarul de parametrii din linia de comanda
	if(argc != 3) {
		fprintf(stderr, "Error: wrong number of parametres in command line\n");
		return -1;
	}

	// aloc lista si o initializez
	list = malloc(sizeof(struct LinkedList));
	init(list);

	// deshid fisierele de input si output
	if((in = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error: can't open input file\n");
		return -1;
	}

	if((out = fopen(argv[2], "w")) == NULL) {
		fprintf(stderr, "Error: can't open output file\n");
		return -1;
	}

	// citesc numarul de melodii
	fscanf(in, "%d", &no_songs);
	for(i = 0; i < no_songs; i++) {
		// pentru fiecare cantec citesc operatia ce trebuie efectuata
		fscanf(in, "%s", com);

		// verific daca com este un ADD sau DEL_SONG, caci trebuie
		// sa obtin informatiile despre melodii
		if((strstr(com, "ADD") != NULL) || (strstr(com, "DEL_SONG") != NULL)) {
			fscanf(in, " ");

			// citesc melodia
			fgets(mel, MELODY, in);
			mel[strlen(mel)-1] = '\0';

			// formez numele fisierului din care extrag datele despre melodie
			name_song = malloc((strlen(mel) + DIRECTORY)*sizeof(char));
			snprintf(name_song, sizeof(mel), "./songs/%s", mel);

			// deschid aceste fisier
			if((song = fopen(name_song, "rb")) == NULL) {
				fprintf(stderr, "Error: can't open file with song metadata\n");
				return -1;
			}

			// ma mut in fisier astfel incat sa sar peste garbage si antetul "TAG"
			fseek(song, -(SONG_TITLE + SONG_ARTIST + SONG_ALBUM + SONG_YEAR), SEEK_END);
			
			// citesc datele despre fiecare melodie
			fread(song_data.title, sizeof(char), SONG_TITLE, song);
			fread(song_data.artist, sizeof(char), SONG_ARTIST, song);
			fread(song_data.album, sizeof(char), SONG_ALBUM, song);
			fread(song_data.year, sizeof(char), SONG_YEAR, song);
			
			// verific comanda si apelez functia corespunzatoare
			if(strcmp(com, "ADD_FIRST") == 0)
				add_first(list, song_data);
			if(strcmp(com, "ADD_LAST") == 0)
				add_last(list, song_data);
			if(strcmp(com, "ADD_AFTER") == 0)
				add_after(list, song_data);
			if(strcmp(com, "DEL_SONG") == 0)
				del_song(list, song_data, out);
			
			// eliberez memoria si inchid fisierul cu informatii
			free(name_song);
			fclose(song);
		} else {
			if(strcmp(com, "DEL_FIRST") == 0)
				del_first(list, out);
			if(strcmp(com, "DEL_LAST") == 0)
				del_last(list, out);
			if(strcmp(com, "DEL_CURR") == 0)
				del_curr(list, out);
			if(strcmp(com, "MOVE_NEXT") == 0)
				move_next(list, out);
			if(strcmp(com, "MOVE_PREV") == 0)
				move_prev(list, out);
			if(strcmp(com, "SHOW_FIRST") == 0)
				show_first(list, out);
			if(strcmp(com, "SHOW_LAST") == 0)
				show_last(list, out);
			if(strcmp(com, "SHOW_CURR") == 0)
				show_curr(list, out);
			if(strcmp(com, "SHOW_PLAYLIST") == 0)
				show_playlist(list, out);
		}
	}
	
	// eliberez memoria si inchid fisierele de input si output
	free_list(list);
	fclose(in);
	fclose(out);
	return 0;
}
