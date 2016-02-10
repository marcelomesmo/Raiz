#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>
#include "InputDefinitions.h"

class Input
{

public:
	void init();
	void free();

	void update();
	void clear();

	// Tells if the keyboard *key* is pressed.
	bool isKeyPressed(SDL_Scancode key);
	// Tells if the keyboard *key* is released.
	bool isKeyReleased(SDL_Scancode key);
	// Tells if the keyboard *key* is currently being pressed.
	bool isKeyDown(SDL_Scancode key);

	// Works both ways, with SDL_Scancode or with KeyboardKey (easier to type)
	bool isKeyPressed(KeyboardKey key);
	bool isKeyReleased(KeyboardKey key);
	bool isKeyDown(KeyboardKey key);

	// Tells if the mouse *button* was pressed just now.
	//bool isMousePressed(uint8_t button);

	// Tells if the mouse *button* was released just now.
	//bool isMouseReleased(uint8_t button);

	// Tells if the mouse *button* is currently being pressed.
	//
	//  ## Possible options are
	//  SDL_BUTTON_LEFT:   left mouse button
	//  SDL_BUTTON_MIDDLE: middle mouse button
	//  SDL_BUTTON_RIGHT:  right mouse button
	//bool isMouseDown(uint8_t button);

	// Tells if the user asked the game to quit
	// (Alt+F4 or close button).
	bool quitRequested();

	// Returns the current mouse X position.
	//int getMouseX();

	// Returns the current mouse Y position.
	//int getMouseY();

	// Tells if the mouse's currently inside the rectangle
	//  specified by #x, #y, #w and #h.
	//bool isMouseInside(int x, int y, int w, int h);
	// TO DO
	//bool isMouseInside(SDL_Rect* box);

private:
	/// Saves SDL internal keyboard state. (DEPRECATED)
	//const uint8_t* keyboard;
	// Saves which keys are currently pressed.
	std::map<SDL_Scancode, bool> keyPressed;
	// Saves which keys are currently released.
	std::map<SDL_Scancode, bool> keyReleased;
	// Saves which keys are currently being pressed down (hold).
	std::map<SDL_Scancode, bool> keyDown;

	// Convertes a KeyboardKey to a SDL_Scancode, based on internal value (decimal, see table)
	SDL_Scancode keyToScanCode;

	/// Saves SDL internal mouse state.
	//uint8_t  mouse;
	/// Current mouse X position.
	//int  mouseX;
	/// Current mouse Y position.
	//int  mouseY;
	/// Saves which mouse buttons are currently up.
	//bool mousePressed[MOUSE_SIZE];
	/// Saves which mouse buttons are currently up.
	//bool mouseReleased[MOUSE_SIZE];

	/// Tells if we must quit the game.
	bool do_quit;
};

#endif