#include "Player.h"

Player::Player(char sign) {
	this->sign = sign;
	this->points = 0;
}

void Player::resetPoints() {
	this->points = 0;
}

void Player::addPoint() {
	this->points++;
}

void Player::addPoints(int points) {
	this->points += points;
}

int Player::getPoints() {
	return this->points;
}

char Player::getSign() {
	return this->sign;
}