#include <iostream> // This line includes iostream

#include "Hex.h"
// Our main program
int main(){

	// Here we set the number of rows of our game, and wether we are using pie rule or not!
	Hex_Game Game1(7,true);

	Game1.Game();

	int pause;

	cin >> pause;

	// Or final line!
	return 0;
};