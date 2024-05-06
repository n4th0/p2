
#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"
#include "Song.h"
#include "User.h"

using namespace std;

unsigned int User::nextId = 1;

User::User(string name){
	this->name = name;
	this->id = nextId;
	nextId++;
}

vector<Playlist> User::getPlaylist() const{
	return this->lists;
}

bool User::createPlaylist(string name){

	for(unsigned int i = 0; i< lists.size(); i++){
		if(lists[i].getName() == name){
			return false;
		}
	}
	// si llega aqui es que no hay playlist duplicadas

	try{
		Playlist playlist(name);
		lists.push_back(playlist);

	}catch(...){ // cualquier excepcion
		return false;
	}

	return true;
}

void User::addSong(string name, Song *song){
	int found = -5;
	for(unsigned int i = 0; i< lists.size(); i++){
		if(lists[i].getName() == name){
			found = i;
		}
	}

	

}

