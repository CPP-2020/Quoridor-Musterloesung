//
// Created by bened on 23.07.2020.
//
#include <string>

#ifndef HACKATHON_PLAYERID_H
#define HACKATHON_PLAYERID_H


class PlayerId {

public:
	std::string getName();
	int getID();
	void setName(std::string newName);
	void setId(int NewId);

private:
	std::string name;
	int id;




};


#endif //HACKATHON_PLAYERID_H
