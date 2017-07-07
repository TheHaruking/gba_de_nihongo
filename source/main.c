#include <gba.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mappy.h>
#include "hal_eightinput.h"
#include "chr003.h"
#include "common.h"


//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	BUTTON_INFO  	b;

	// Init
	irqInit();
	irqEnable(IRQ_VBLANK);
	SetMode(0 | BG0_ON | OBJ_ON);
	BGCTRL[0] = MAP_BASE(0)  | CHAR_BASE(3) | BG_SIZE(3);
	BGCTRL[1] = MAP_BASE(4)  | CHAR_BASE(3) | BG_SIZE(3);
	BGCTRL[2] = MAP_BASE(8)  | CHAR_BASE(3) | BG_SIZE(3);
	BGCTRL[3] = MAP_BASE(12) | CHAR_BASE(3) | BG_SIZE(3);
	
	consoleInit(3, 0, 3, NULL, 0, 0);
	dmaCopy(chr003Tiles,	CHAR_BASE_ADR(3),	chr003TilesLen);
	dmaCopy(chr003Pal,		BG_COLORS,		chr003PalLen);

	// Init private
	halInitKeys(&b, 4, 5, 6, 7, 0, 1, 3, 2);

	while (1) {
		// ボタン入力初期化
		scanKeys();
		halSetKeys(&b, keysHeld());
		if (halIsA(&b)) {
			printf("A");
		}


		// 垂直同期待機・書き込み
		VBlankIntrWait();
	}
}


