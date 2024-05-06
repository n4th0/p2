#include <iostream>
#include "Song.h"
#include "User.h"
#include "Playlist.h"
using namespace std;

int main(){

	Song *s1 = new Song("help", "the beatles", 180);
	Song *s2 = new Song("hey jude", "the beatles", 431);
	Song *s3 = new Song("tumbling dice", "roling", 210);
	// Playlist p("");

	User user;
	user.createPlaylist("Oldies");


	return 0;
}


