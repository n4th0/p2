#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_
#include <string>
#include <iostream>
#include <vector>
#include "Song.h"
using namespace std;

class Playlist{
	private:
		string name;
		vector<Song *> songs;
	public:
		Playlist(string name);
		string getName() const ;
		unsigned int const totalDuration();
		void addSong(Song *S);
	friend ostream& operator<<(ostream& os, const Playlist &Playlist);
		// friend function
};
#endif
