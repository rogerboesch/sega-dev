#include <genesis.h>
#include "resources.h"
#include <bmp.h>

void drawLine(int x, int color) {
    // A line needs a source coordinate x,y and a destination coordinate x,y along with a pallete colour.
    Line l;
    l.pt1.x = x;
    l.pt1.y = 0;
    l.pt2.x = x;
    l.pt2.y = 159;
    l.col = color;
    l.col |= l.col << 4; // if we do not left shift the colour, we get gaps in the line

    BMP_drawLine(&l);
}

int main() {
    //Initialise the bitmap engine
    BMP_init(TRUE, BG_A, PAL0, FALSE);

    //Set the colour of the line. We are using pallete 0 for the bitmap, so we have 0->15. 15 is used for white text, so we set an unused pallet colour, 14 to blue - RGB 0000FF.
    u16 colour_blue = RGB24_TO_VDPCOLOR(0x0000ff);
    VDP_setPaletteColor(14, colour_blue);

    int x = 0;

	while (1) {      
        BMP_clear();
        BMP_showFPS(TRUE);

        drawLine(x, 14);
        drawLine(x+10, 14);
        drawLine(x+20, 14);
        drawLine(x+30, 14);
        drawLine(x+40, 14);
        drawLine(x+50, 14);
        
        BMP_flip(1);

        if (x >= 255) {
            x = 0;
        }

        x++;
    }
    
	return (0);
}
