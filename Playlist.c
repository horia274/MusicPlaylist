// Copyright [2020] IGNAT Andrei-Horia 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Playlist.h"

// initializeaza o lista alocata deja
void init(struct LinkedList *list) {
	// initializez campurile structurii
	list->head = NULL;
	list->tail = NULL;
	list->cursor = NULL;
	list->size = 0;
}

// verifica daca melodia cu datele new_data exista in playlist
// si intoare nodul din lista, altfel intoarce NULL
struct Node* exist(struct LinkedList *list, struct Info new_data) {
	// parcurg lista de la inceput si daca gasesc melodia
	// in lista returnez nodul, altfel returnez NULL
	struct Node *curr;
	curr = list->head;
	while(curr != NULL) {
		if(strcmp(curr->data.title, new_data.title) == 0)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

void add_first(struct LinkedList *list, struct Info new_data) {
	struct Node *new, *curr;
	if(list == NULL)
		return;
	// daca lista este goala adaug un cantec si actualizez head tail cursor
	if(list->head == NULL) {
		new = malloc(sizeof(struct Node));
		new->data = new_data;
		list->size++;
		list->head = new;
		list->tail = new;
		list->cursor = new;
		new->next = NULL;
		new->prev = NULL;
	} else {
		curr = exist(list, new_data);
		if(curr == NULL) {
			// daca melodia nu exista deja o adaug la inceput si actualizez head
			new = malloc(sizeof(struct Node));
			new->data = new_data;
			list->size++;
			new->next = list->head;
			list->head->prev = new;
			list->head = new;
			new->prev = NULL;
		} else {
			// daca exista verific intai daca este nevoie sa actualizez cursorul
			if(strcmp(curr->data.title, list->cursor->data.title) == 0) {
				if(list->cursor->next != NULL) {
					list->cursor = list->cursor->next;
				} else {
					list->cursor = list->cursor->prev;
				}
			}

			// disting 2 cazuri, in functie de vechea pozitie a melodiei in lista:
			// daca se afla la sfarsitul listei, sau in interiorul ei
			if(strcmp(curr->data.title, list->head->data.title) != 0 &&
			strcmp(curr->data.title, list->tail->data.title) != 0) {
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
			}

			if(strcmp(curr->data.title, list->tail->data.title) == 0) {
				curr->prev->next = NULL;
				list->tail = curr->prev;
			}

			// pentru cazul in care melodia ar fi deja la inceput se actualizeaza doar
			// cursorul mai sus, altfel se refac legaturile celor 2 cazuri precedente
			if(strcmp((curr->data).title, (list->head->data).title) != 0) {
				curr->next = list->head;
				list->head->prev = curr;
				list->head = curr;
				curr->prev = NULL;
			}
		}
	}
}

void add_last(struct LinkedList *list, struct Info new_data) {
	struct Node *new, *curr;
	if(list == NULL)
		return;

	// daca lista este goala adaug un cantec si actualizez head tail cursor
	if(list->head == NULL) {
		new = malloc(sizeof(struct Node));
		new->data = new_data;
		list->size++;
		list->head = new;
		list->tail = new;
		list->cursor = new;
		new->next = NULL;
		new->prev = NULL;
	} else {
		curr = exist(list, new_data);
		if(curr == NULL) {
			// daca melodia nu exista deja o adaug la sfarsit si actualizez tail
			new = malloc(sizeof(struct Node));
			new->data = new_data;
			list->size++;
			new->next = NULL;
			new->prev = list->tail;
			list->tail->next = new;
			list->tail = new;
		} else {

			// daca exista verific intai daca este nevoie sa actualizez cursorul
			if(strcmp(curr->data.title, list->cursor->data.title) == 0) {
				if(list->cursor->next != NULL) {
					list->cursor = list->cursor->next;
				} else {
					list->cursor = list->cursor->prev;
				}
			}

			// disting 2 cazuri, in functie de vechea pozitie a melodiei in lista:
			// daca se afla la inceputul listei, sau in interiorul ei
			if(strcmp(curr->data.title, list->head->data.title) != 0 &&
			strcmp(curr->data.title, list->tail->data.title) != 0) {
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
			}
			if(strcmp((curr->data).title, (list->head->data).title) == 0) {
				curr->next->prev = NULL;
				list->head = curr->next;
			}

			// pentru cazul in care melodia ar fi deja la inceput se actualizeaza doar
			// cursorul mai sus, altfel se refac legaturile celor 2 cazuri precedente
			if(strcmp((curr->data).title, (list->tail->data).title) != 0) {
				curr->prev = list->tail;
				list->tail->next = curr;
				list->tail = curr;
				curr->next = NULL;
			}
		}
	}
}

void add_after(struct LinkedList *list, struct Info new_data) {
	struct Node *new, *curr;

	// elimin cazurile triviale
	// daca nu avem cursor
	if(list == NULL || list->cursor == NULL)
		return;

	// daca melodia care trebuie adaugata are deja cursorul pe ea
	if(strcmp(list->cursor->data.title, new_data.title) == 0)
		return;

	// daca melodia care trebuie adaugata dupa cursor este deja acolo
	if(list->cursor->next != NULL &&
	strcmp(list->cursor->next->data.title, new_data.title) == 0)
		return;

	curr = exist(list, new_data);
	// daca nu exista in lista verific 2 cazuri:
	if(curr == NULL) {
		new = malloc(sizeof(struct Node));
		new->data = new_data;
		list->size++;

		// cazul cand cursorul este la sfarsit unde actualizez tail
		if(strcmp(list->cursor->data.title, list->tail->data.title) == 0) {
			new->next = NULL;
			new->prev = list->tail;
			list->tail->next = new;
			list->tail = new;
		} else {
			// si cand nu e, unde adaug in lista pur si simplu; nu se verifica
			// daca este la inceput pentru ca se incadreaza in al doilea caz
			new->next = list->cursor->next;
			list->cursor->next->prev = new;
			list->cursor->next = new;
			new->prev = list->cursor;
		}
	} else {
		// daca exista deja in playlist
		// studiez pozitia cursorului in doua cazuri
		// daca nu este la finalul listei
		if(strcmp(list->cursor->data.title, list->tail->data.title) != 0) {
			// acum verific in functie de pozitia melodiei deja existente in playlist
			// daca se afla in interior
			if(strcmp(curr->data.title, list->head->data.title) != 0 &&
			strcmp(curr->data.title, list->tail->data.title) != 0) {
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
			}

			// daca se afla la inceput, actualizez head
			if(strcmp(curr->data.title, list->head->data.title) == 0) {
				curr->next->prev = NULL;
				list->head = curr->next;
			}

			// daca se afla la sfarsit, actualizez tail
			if(strcmp(curr->data.title, list->tail->data.title) == 0) {
				curr->prev->next = NULL;
				list->tail = curr->prev;
			}

			curr->next = list->cursor->next;
			list->cursor->next->prev = curr;
			list->cursor->next = curr;
			curr->prev = list->cursor;
		} else {
			// acum sunt in situatia in care cursorul este la final
			// si verific din nou pozitia melodiei care trebuie mutata
			// daca nu este la inceput actualiezez doar tail
			if(strcmp(curr->data.title, list->head->data.title) != 0) {
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
			} else {
				// daca este la inceput, actualiezez si tail si head
				curr->next->prev = NULL;
				list->head = curr->next;
			}

			list->cursor->next = curr;
			curr->prev = list->cursor;
			curr->next = NULL;
			list->tail = curr;
		}
	}
}

void del_first(struct LinkedList *list, FILE *out) {
	struct Node *first;

	if(list == NULL)
		return;

	// verific daca am lista goala
	if(list->head == NULL) {
		fprintf(out, "Error: delete from empty playlist\n");
		return;
	}
	
	// verific daca este nevoie sa mut cursorul
	if(strcmp(list->cursor->data.title, list->head->data.title) == 0) {
		list->cursor = list->head->next;
	}

	// copiez prima melodie in first, si o sterg, eliberand memoria
	// si refac head, daca lista are un singur element, sau mai multe
	first = list->head;

	if(list->head->next != NULL) {
		list->head->next->prev = NULL;
		list->head = list->head->next;
	} else {
		list->head = NULL;
		list->tail = NULL;
	}

	free(first);
	list->size--;
}

void del_last(struct LinkedList *list, FILE *out) {
	struct Node *last;

	if(list == NULL)
		return;

	// verific daca am lista goala
	if(list->tail == NULL) {
		fprintf(out, "Error: delete from empty playlist\n");
		return;
	}

	// verific daca este nevoie sa mut cursorul
	if(strcmp(list->cursor->data.title, list->tail->data.title) == 0) {
		list->cursor = list->tail->prev;
	}

	// copiez ultima melodie in first, si o sterg, eliberand memoria
	// si refac tail, daca lista are un singur element, sau mai multe
	last = list->tail;
	
	if(list->tail->prev != NULL) {
		list->tail->prev->next = NULL;
		list->tail = list->tail->prev;
	} else {
		list->head = NULL;
		list->tail = NULL;
	}

	free(last);
	list->size--;
}

void del_curr(struct LinkedList *list, FILE *out) {
	struct Node *curr;

	if(list == NULL)
		return;

	// verific daca am lista goala
	if(list->cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
		return;
	}

	// mut cursorul
	curr = list->cursor;
	if(curr->next != NULL)
		list->cursor = curr->next;
	else
		list->cursor = curr->prev;
	
	// disting 3 situatii posibile:
	// stergere din interior, de la inceput sau final
	if(curr->next != NULL && curr->prev != NULL) {
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
	} else {
		if(curr->prev == NULL) {
			if(list->head->next != NULL) {
				list->head->next->prev = NULL;
				list->head = list->head->next;
			} else {
				list->head = NULL;
				list->tail = NULL;
			}
		}
		if(curr->next == NULL) {
			if(list->tail != NULL && list->tail->prev != NULL) {
				list->tail->prev->next = NULL;
				list->tail = list->tail->prev;
			}
		}
	}

	free(curr);
	list->size--;
}

void del_song(struct LinkedList *list, struct Info old_data, FILE *out) {
	struct Node *curr;

	if(list == NULL)
		return;

	// verific daca exista melodia in playlist
	curr = exist(list, old_data);
	if(curr == NULL) {
		fprintf(out, "Error: no song found to delete\n");
		return;
	}

	// verific daca este nevoie sa mut cursorul
	if(strcmp((list->cursor->data).title, (curr->data).title) == 0) {
		if(curr->next != NULL)
			list->cursor = curr->next;
		else
			list->cursor = curr->prev;
	}

	// disting 3 situatii posibile:
	// stergere din interior, de la inceput sau final
	if(curr->next != NULL && curr->prev != NULL) {
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
	} else {
		if(curr->prev == NULL) {
			if(list->head->next != NULL) {
				list->head->next->prev = NULL;
				list->head = list->head->next;
			} else {
				list->head = NULL;
				list->tail = NULL;
			}
		}

		if(curr->next == NULL) {
			if(list->tail != NULL && list->tail->prev != NULL) {
				list->tail->prev->next = NULL;
				list->tail = list->tail->prev;
			}
		}
	}

	free(curr);
	list->size--;
}

void move_next(struct LinkedList *list, FILE *out) {
	if(list == NULL)
		return;

	// verific daca am cursor
	if(list->cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
		return;
	}

	// verific daca pot sa il mut inainte
	if(list->cursor->next == NULL)
		return;

	list->cursor = list->cursor->next;
}

void move_prev(struct LinkedList *list, FILE *out) {
	if(list == NULL)
		return;

	// verific daca am cursor
	if(list->cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
		return;
	}

	// verific daca pot sa il mut inapoi
	if(list->cursor->prev == NULL)
		return;

	list->cursor = list->cursor->prev;
}

void show_first(struct LinkedList *list, FILE *out) {
	if(list == NULL)
		return;

	// verific daca am lista goala
	if(list->head == NULL) {
		fprintf(out, "Error: show empty playlist\n");
		return;
	}

	// daca nu afisez prima melodie
	fprintf(out, "Title: %.30s\n", list->head->data.title);
	fprintf(out, "Artist: %.30s\n", list->head->data.artist);
	fprintf(out, "Album: %.30s\n", list->head->data.album);
	fprintf(out, "Year: %.4s\n", list->head->data.year);
}

void show_last(struct LinkedList *list, FILE *out) {
	if(list == NULL)
		return;

	// verific daca am lista goala
	if(list->tail == NULL) {
		fprintf(out, "Error: show empty playlist\n");
		return;
	}

	// daca nu afisez ultima melodie
	fprintf(out, "Title: %.30s\n", list->tail->data.title);
	fprintf(out, "Artist: %.30s\n", list->tail->data.artist);
	fprintf(out, "Album: %.30s\n", list->tail->data.album);
	fprintf(out, "Year: %.4s\n", list->tail->data.year);
}

void show_curr(struct LinkedList *list, FILE *out) {
	if(list == NULL)
		return;

	// verific daca exista cursor
	if(list->cursor == NULL) {
		fprintf(out, "Error: show empty playlist\n");
		return;
	}

	// daca da, afisez melodia curenta
	fprintf(out, "Title: %.30s\n", list->cursor->data.title);
	fprintf(out, "Artist: %.30s\n", list->cursor->data.artist);
	fprintf(out, "Album: %.30s\n", list->cursor->data.album);
	fprintf(out, "Year: %.4s\n", list->cursor->data.year);
}

void show_playlist(struct LinkedList *list, FILE *out) {
	struct Node *curr;

	if(list == NULL)
		return;

	curr = list->head;
	
	// verific daca playlistul nu este gol si afisez toate melodiile
	if(list->head != NULL) {
		fprintf(out, "[");
		while(curr->next != NULL) {
			fprintf(out, "%.30s; ", curr->data.title);
			curr = curr->next;
		}
		fprintf(out, "%.30s]\n", curr->data.title);
	} else {
		fprintf(out, "[]\n");
	}
}

void free_list(struct LinkedList *list) {
	struct Node *curr, *prev;
	
	if(list == NULL)
		return;
	
	// parcurg toata lista si eliberez memoria folosita
	// de fiecare nod si apoi memoria folosita de lista
	
	curr = list->head;
	while(curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}
