#include <iostream>
#include <vector>
#include <string>
#include "Song.h"

using namespace std;


Song::Song(string name, string artist, unsigned int duration){
	this->name = name;
	this->artist = artist;
	this->duration = duration;
}

string Song::getName()const {
	return this->name;
}

string Song::getArtist()const {
	return this->artist;
}

unsigned int Song::getDuration()const {
	return this->duration;

}

ostream &operator<<(ostream &os, const Song &song){
	os << song.artist << " - " << song.name << " ("<< song.duration<< "s)";
	return os;
}

