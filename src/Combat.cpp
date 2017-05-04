#include <string>
#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include "Combat.h"

//generate a Combat handler with the given Player and Monster
Combat::Combat(Player *currentplayer, Monster *currentmonster) {
	_player = currentplayer;
	_monster = currentmonster;
	_turn = true;
}

Combat::~Combat() {
}

/**
Player turn options are received with cin
Users can choose several options from attacking to passing the turn
*/
void Combat::playerTurn(std::ostream& ostr) {
	std::string action = "";
	ostr << "Player Turn!" << std::endl;
	ostr << "What will you do?" << std::endl
	     << "Show info [u]" << std::endl
	     << "Use skill [i]" << std::endl
	     << "Procrastinate [o]" << std::endl
	     << "Pass turn [p]" << std::endl;
	while (true) {
		std::cin >> action;
		if (action == "u") {
			ostr << _player->getNonBasicInfo(ostr);
		}
		else if (action == "i") {
			std::string skillChoice;
			int skillIndex;
			//loop until the player enters a valid skill name that they possess
			while (true) {
				ostr << "What skill (type the name of one of your skills)?" << std::endl;
				std::getline(std::cin, skillChoice);
				std::cout << skillChoice << std::endl;
				skillIndex = _player->skillIndex(skillChoice);
				if (skillIndex != -1) {
					break;
				}
			}
	
			int damage = _player->useSkill(skillIndex);

			_monster->updateStamina(-damage);
			if (_monster->getStamina() <= 0) {
				break;
			}
		}
		else if (action == "o") {
			ostr << "Took a break :)" << std::endl;
		}
		else if (action == "p"){
			ostr << "Giving up???" << std::endl;
			break;
		}
		else {
			ostr << "What?" << std::endl;
			continue;
		}
	}
	return;
}

/**
Monster turns are managed by the game as weighted random selection of skills
Monster objects cannot use Item
*/
void Combat::monsterTurn(std::ostream& ostr) {
	ostr << "Monster Turn!" << std::endl;
}

/**
Engage combat function called by Dungeon when the Player chooses to fight
Alternates turns for Player and Monster calling the respective turn function

Returns true when the Player wins and false if the Monster wins
*/
bool Combat::engageCombat(std::ostream& ostr) {
	while ((_player->getStamina() > 0) && (_monster->getStamina() > 0)) {
		if (_turn) {
			ostr << "hi!" << std::endl;
			playerTurn(ostr);
			if (_monster->getStamina() <= 0) {
				ostr << "You won the fight!" << std::endl;
				return true;
			}
			_turn = false;
		}
		else {
			monsterTurn(ostr);
			_turn = true;
		}
	}
	ostr << "You lost the fight :(, you will suffer a grade penalty for this!" << std::endl;
	return false;
}

void Combat::setMonster(Monster* newMonster){
	_monster = newMonster;
}
