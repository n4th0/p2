#ifndef _SONG_H_
#define _SONG_H_

#include <iostream>
#include <string>
using namespace std;

class Song {
	private:
		string name;
		string artist;
		unsigned int duration;
	public:
		Song(string name, string artist, unsigned int duration);
		string getName()const ;
		string getArtist()const ;
		unsigned int getDuration()const ;
	friend ostream& operator<<(ostream &os, const Song &song);

};

#endif
