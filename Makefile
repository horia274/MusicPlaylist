CC=gcc
CFLAGS=-Wall -Wextra

build: playlist

playlist: Playlist.o MainPlaylist.o
	$(CC) $(CFLAGS) Playlist.o MainPlaylist.o -o playlist

Playlist.o: Playlist.c Playlist.h
	$(CC) $(CFLAGS) -c Playlist.c

MainPlaylist.o: MainPlaylist.c
	$(CC) $(CFLAGS) -c MainPlaylist.c

run:
	./playlist

pack: Makefile README Playlist.c Playlist.h MainPlaylist.c
	zip 314CA_IgnatAndreiHoria_Tema1.zip Makefile README *.c *.h

clean:
	rm *.o
	rm playlist
