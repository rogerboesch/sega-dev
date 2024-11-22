#include <genesis.h>
#include "resources.h"
#include <bmp.h>

void drawLine(int x, int color) {
    Line l;
    l.pt1.x = x;
    l.pt1.y = 0;
    l.pt2.x = x;
    l.pt2.y = 159;
    l.col = color;
    l.col |= l.col << 4; // if we do not left shift the colour, we get gaps in the line

    BMP_drawLine(&l);
}

void test1() {
    // Initialise the bitmap engine
    BMP_init(TRUE, BG_A, PAL0, FALSE);

    // Set the colour of the line. We are using pallete 0 for the bitmap, so we have 0->15. 15 is used for white text, so we set an unused pallet colour, 14 to blue - RGB 0000FF.
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
}

void test2() {
    // Initialise the bitmap engine
    BMP_init(FALSE, BG_A, PAL0, FALSE);
    BMP_setBufferCopy(TRUE); // if we do not do this, the bitmap pixels and lines will flicker when drawing

    // Set the colour of the line. We are using pallete 0 for the bitmap, so we have 0->15. 15 is used for white text, so we set an unused pallet colour, 14 to red - RGB FF0000. We also want a green line, so we set 13 to red - RGB FF0000.... etc etc....
    u16 colour_red = RGB24_TO_VDPCOLOR(0xff0000);
    u16 colour_green = RGB24_TO_VDPCOLOR(0x00ff00);
    u16 colour_blue = RGB24_TO_VDPCOLOR(0x0000ff);
    u16 colour_yellow = RGB24_TO_VDPCOLOR(0xffff00);
    VDP_setPaletteColor(14, colour_red);
    VDP_setPaletteColor(13, colour_green);
    VDP_setPaletteColor(12, colour_blue);
    VDP_setPaletteColor(11, colour_yellow);

    // When we are working in bitmap mode, we must left shift the colours, or we get gaps in pixels drawn
    int pal_red = 14;
    pal_red |= pal_red << 4;

    int pal_green = 13;
    pal_green |= pal_green << 4;

    int pal_blue = 12;
    pal_blue |= pal_blue << 4;

    int pal_yellow = 11;
    pal_blue |= pal_blue << 4;

    // Draw the vertical axis
    Line a;
    a.pt1.x = 0;
    a.pt1.y = 0;
    a.pt2.x = 0;
    a.pt2.y = 160;
    a.col = pal_blue;

    // Draw the horizontal axis
    Line b;
    b.pt1.x = 0;
    b.pt1.y = 80;
    b.pt2.x = 255;
    b.pt2.y = 80;
    b.col = pal_blue;

    while (TRUE) {
        //Draw the graph axes
        BMP_drawLine(&a);
        BMP_drawLine(&b);

        //The loop to draw the sine wave
        int i;
        for (i = 1; i < 255; i ++) {
            BMP_setPixel(i, 80 + sinFix16(i*8), pal_red);

            //We may as well draw cosine while we are here :)
            //BMP_setPixel(i, 80 + cosFix16(i*8), pal_green);

            //...and why not tan - but checking to make sure we don't divide by 0
            if (cosFix16(i*8) != 0){
              //  BMP_setPixel(i, 80 + (fix16Div(sinFix16(i*8), cosFix16(i*8))), pal_yellow);
            }
            BMP_flip(FALSE);
        }

    }
}

void test3() {
    //Initialise the bitmap engine
    BMP_init(FALSE, BG_A, PAL0, FALSE);
    BMP_setBufferCopy(TRUE); // if we do not do this, the bitmap pixels and lines will flicker when drawing

    // Set some palette colours
    u16 colour_red = RGB24_TO_VDPCOLOR(0xff0000);
    u16 colour_green = RGB24_TO_VDPCOLOR(0x00ff00);
    u16 colour_blue = RGB24_TO_VDPCOLOR(0x0000ff);
    VDP_setPaletteColor(12, colour_red);
    VDP_setPaletteColor(13, colour_green);
    VDP_setPaletteColor(14, colour_blue);

    // When we are working in bitmap mode, we must left shift the colours, or we get gaps in pixels drawn
    int pal_red = 12;
    pal_red |= pal_red << 4;

    int pal_green = 13;
    pal_green |= pal_green << 4;

    int pal_blue = 14;
    pal_blue |= pal_blue << 4;

    // Lissajous Variables
    int a = 2;
    int b = 3;
    fix16 delta = 3.14/2;

    // Variables needed for the loop, and drawing of the bitmap pixels
    fix16 i = 0;
    fix16 x = 0;
    fix16 y = 0;

    while (TRUE) {
        // The loop to draw the lissajous curve
        for (i = 0; i < 1024; i++) {
            x = 120 + sinFix16(a*i + delta);
            y = 80 + sinFix16(b*i);
            BMP_setPixel(x, y, pal_green);
            BMP_flip(FALSE);
        }

        break;
    }
}

int main() {
    test3();
}
