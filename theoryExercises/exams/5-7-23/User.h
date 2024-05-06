#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"
#include "Song.h"

using namespace std;

class User{
	friend ostream& operator<<(ostream &os, const Song &song);
	private:
		unsigned int id;
		string name;
		static unsigned int nextId;
		vector<Playlist> lists;
	public:
		User(string name = "New User");
		const vector<Playlist> getPlaylist();
		bool createPlaylist(string name);
		void addSong(string name, Song *song);
};
#endif

