#include "InputManager.h"

void InputManager::start()
{
	for (bool key : _keys) {
		key = false;
	}
}

void InputManager::keyPressed(int key)
{
	_keys[key] = true;
}

void InputManager::keyReleased(int key)
{
	_keys[key] = false;
}

bool InputManager::isKeyPressed(int key)
{
	return _keys[key];
}

void InputManager::addKeyAttribute(KEYBOARD_ATTRIB attrib, int key)
{
	switch (attrib) {
	case KEY_ONCE_AT_A_TIME:
		attrib0[key] = true;
	}
}
