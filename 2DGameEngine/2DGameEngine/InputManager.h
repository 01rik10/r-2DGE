#pragma once
#include <map>
/*Manages keyboard events*/
class InputManager
{
public:
	enum KEYBOARD_ATTRIB {
		KEY_ONCE_AT_A_TIME
	};
	void start();
	void keyPressed(int key);
	void keyReleased(int key);
	bool isKeyPressed(int key);
	void addKeyAttribute(KEYBOARD_ATTRIB attrib, int key);
private:
	bool _keys[255];
	std::map<int, bool> attrib0;
};

