#pragma once
class Player
{
	char sign;
	int points;
public:
	Player(char sign);
	void addPoint();
	void addPoints(int points);
	int getPoints();
	char getSign();
	void resetPoints();
};

