// Copyright [2020] IGNAT Andrei-Horia 314CA

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#define SONG_TITLE 30
#define SONG_ARTIST 30
#define SONG_ALBUM 30
#define SONG_YEAR 4
#define COMMAND 15
#define MELODY 100
#define DIRECTORY 10

// structura cu informatiile unei melodii
struct Info {
	char title[SONG_TITLE];
	char artist[SONG_ARTIST];
	char album[SONG_ALBUM];
	char year[SONG_YEAR];
};

struct Node {
	struct Info data;
	struct Node *next, *prev;
};

struct LinkedList {
	struct Node *head, *tail, *cursor;
	int size;
};

// initializeaza o lista alocata deja
void init(struct LinkedList *list);

// verifica daca melodia cu datele new_data exista in playlist
// si intoare nodul din lista, altfel intoarce NULL
struct Node* exist(struct LinkedList *list, struct Info new_data);

void add_first(struct LinkedList *list, struct Info new_data);

void add_last(struct LinkedList *list, struct Info new_data);

void add_after(struct LinkedList *list, struct Info new_data);

void del_first(struct LinkedList *list, FILE *out);

void del_last(struct LinkedList *list, FILE *out);

void del_curr(struct LinkedList *list, FILE *out);

void del_song(struct LinkedList *list, struct Info old_data, FILE *out);

void move_next(struct LinkedList *list, FILE *out);

void move_prev(struct LinkedList *list, FILE *out);

void show_first(struct LinkedList *list, FILE *out);

void show_last(struct LinkedList *list, FILE *out);

void show_curr(struct LinkedList *list, FILE *out);

void show_playlist(struct LinkedList *list, FILE *out);

// elibereaza toata memoria folosita de playlist
void free_list(struct LinkedList *list);

#endif  // PLAYLIST_H_
