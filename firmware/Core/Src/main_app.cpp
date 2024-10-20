#include "main_app.h"

// Using the seperate main_app because CubeMX code generation will keep making a new
// main.c and clobbers the main.cpp. Instead this main_app gets called in main.c so 
// CubeMX can happily keep generating code.

int main_app()
{
	/* Initialization */

	while (1)
	{
		/* Super loop */
	}
}