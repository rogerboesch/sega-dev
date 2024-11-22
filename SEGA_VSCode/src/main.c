#include <genesis.h>
#include "resources.h"

int main() {

    u16 ind = TILE_USER_INDEX;
    PAL_setPalette(PAL0, bg.palette->data, DMA);
    VDP_drawImageEx(BG_B, &bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);

    ind += bg.tileset->numTile;
    PAL_setPalette(PAL1, fg.palette->data, DMA);
    VDP_drawImageEx(BG_A, &fg, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    int bg_hscroll_offset = 0;
    int fg_hscroll_offset = 0;

	while (1) {      
        VDP_setHorizontalScroll(BG_B, bg_hscroll_offset);
        bg_hscroll_offset += 1;

        VDP_setHorizontalScroll(BG_A, fg_hscroll_offset);
        fg_hscroll_offset += 2;

		//VDP_waitVSync();
        SYS_doVBlankProcess();
	}
    
	return (0);
}
