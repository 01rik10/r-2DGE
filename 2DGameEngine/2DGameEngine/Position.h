#pragma once
class Position
{
public:
	Position():_x(0),_y(0){}
	void setPosition(float xPos, float yPos) {
		_x = xPos;
		_y = yPos;
	}
	float getX() { return _x; }
	float getY() { return _y; }
private:
	float _x;
	float _y;
};

