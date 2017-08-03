#include <gba.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mappy.h>
#include "hal_eightinput.h"
#include "chr003.h"
#include "common.h"
#include "obj_utils.h"

typedef struct {
	char buf[32][32];
	int  curY, curX, curX_real;
	char  line[256];
} NOTEPAD, *PNOTEPAD;

typedef struct {
	int stack[4];
	int stack_p;
} CLEMATIS, *PCLEMATIS;

void notepadInit(NOTEPAD* notepad){
	memset(notepad->buf, '\0', sizeof(notepad->buf));
	notepad->curY = 0;
	notepad->curX = 0;
	notepad->curX_real = 0;
	memset(notepad->line, '\0', sizeof(notepad->line));
}

void notepadMove(NOTEPAD* notepad, BUTTON_INFO* b){
	if(!halIsKey(b))
		return;

	switch (halIsKey(b)){
		case KEY_Y0: notepad->curY--; return;
		case KEY_Y1: notepad->curY++; return;
		case KEY_X0: notepad->curX = notepad->curX_real - 1; return;
		case KEY_X1: notepad->curX = notepad->curX_real + 1; return;
	} 

	notepad->curX &= 0x1F;
	notepad->curY &= 0x1F;
	
	// 行の最後尾を超えていないか確認
	for(int i = 0; i < notepad->curX; i++){
		if(notepad->buf[notepad->curY][i]) {
			continue;
		} else {
			notepad->curX_real = i;
		}
	}
	return;
}

void notepadPut(NOTEPAD* notepad, BUTTON_INFO* b){
}

void notepadUpdateLine(NOTEPAD* notepad){
	printf(CON_POS(0, notepad->curY));
	printf("%s", notepad->buf[notepad->curY]);
}

void clematisInit(CLEMATIS* clematis){

}

char clematisUpdate(CLEMATIS* clematis, const BUTTON_INFO* b){
	char ret;
	ret = '\0';
	return ret;
}


//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	BUTTON_INFO  	b;
	NOTEPAD 		notepad;
	CLEMATIS		clematis;

	// Init
	irqInit();
	irqEnable(IRQ_VBLANK);
	SetMode(0 | BG0_ON | OBJ_ON);
	BGCTRL[0] = MAP_BASE(0)  | CHAR_BASE(3) | BG_SIZE(3);
	BGCTRL[1] = MAP_BASE(4)  | CHAR_BASE(3) | BG_SIZE(3);
	BGCTRL[2] = MAP_BASE(8)  | CHAR_BASE(3) | BG_SIZE(3);
	BGCTRL[3] = MAP_BASE(12) | CHAR_BASE(3) | BG_SIZE(3);
	
	// consoleInit
	// 1. charBase
	// 2. mapBase
	// 3. background
	// 4. font
	// 5. fontsize
	// 6. palette
	consoleInit(3, 0, 3, NULL, 0, 0);
	dmaCopy(chr003Tiles,	CHAR_BASE_ADR(3),	chr003TilesLen);
	dmaCopy(chr003Pal,		BG_COLORS,		chr003PalLen);

	// Init private
	halInitKeys(&b, 4, 5, 6, 7, 0, 1, 3, 2);
	notepadInit(&notepad);
	clematisInit(&clematis);

	while (1) {
		// ボタン入力初期化
		scanKeys();
		halSetKeys(&b, keysHeld());
		
		

		// 垂直同期待機・書き込み
		VBlankIntrWait();
	}
}


