//---------------------------------------------------------------------------------
#ifndef _hal_eightinput_h_
#define _hal_eightinput_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------
// ボタン単体ID
#define KEY_X0		0x01
#define KEY_X1		0x02
#define KEY_Y0		0x04
#define KEY_Y1		0x08

#define BTN_A		0x10
#define BTN_B		0x20
#define BTN_CTR		0x40
#define BTN_ESC		0x80

#define KEY_XY		0x0F
#define BTN_AB		0x30

// ボタン動作ID
#define PUSH_AI		0x01
#define PUSH_BI		0x02
#define PUSH_AX		0x04
#define PUSH_BX		0x08
// AB情報
#define AB_A		0x00
#define AB_B		0x01
#define AB_AB		0x02
// クロス打ち(4)
#define AB4_AI		0x00
#define AB4_BI		0x01
#define AB4_AX		0x02
#define AB4_BX		0x03
// クロス打ち(6)
#define AB6_AII		0x00
#define AB6_BII		0x01
#define AB6_ABA		0x02
#define AB6_BAB		0x03
#define AB6_ABB		0x04
#define AB6_BAA		0x05

#define NO_ACTION	-1

// "クロス打ち" とは?!
// ABボタン のみの打ち分けで、最大6までの分岐を可能にする仕組み。
// クロス打ち(4) の場合
// case 0 ... Aボタン押して離す
// case 1 ... Bボタン押して離す
// case 2 ... Aボタン押しつつB押す
// case 3 ... Bボタン押しつつA押す

// クロス打ち(6) の場合
// case 0 ... Aボタン押して離す
// case 1 ... Bボタン押して離す
// case 2 ... Aボタン押しつつ、B押してB離す
// case 3 ... Bボタン押しつつ、A押してA離す
// case 4 ... Aボタン押しつつ、B押して "A"を離す
// case 5 ... Bボタン押しつつ、A押して "B"を離す

typedef struct _BUTTON_INFO_ {
	// 初期設定
	unsigned int x0, x1, y0, y1, a, b, ctr, esc; // sortinfo
	// ボタン関連
	unsigned int b0;				// new (押している間)
	unsigned int b1, b2;			// 押したとき、離したとき
	unsigned int b_old;				// old
	// 方向関連
	unsigned int k0, k1, k2, k_old;	// 方向キー単体の情報
	int			 key_8;				// ↑を 0 とした 7 までの 角度。
	int 		 f_key;				// ファーストキー。最初に押した方向。ななめ無視。
	int  		 f_key_flag;		// 最初に押したフレームか
	int			 f_key_move;		// 傾け量。1(←) ~ 4(中) ~ 7(→)。0(逆)
	// AB関連
	unsigned int ab0, ab1, ab2, ab_old; // ABボタン単体の情報
	int			 ab_3;				// 0 ~ 3 までの AB情報。
	int			 f_ab;				// ファーストAB。最初に押したABがどちらか。(A : 0, B : 1, 無・同時 : -1)
	int			 f_ab_flag;			// 最初に押したフレームか
	int			 f_ab4_action;		// クロス打ち(4)した瞬間。(アクション有り : 0 ~ 3, 無 : -1)
	int			 f_ab6_action;		// クロス打ち(6)した瞬間。(アクション有り : 0 ~ 5, 無 : -1)
	// 他
	unsigned int k12_stage;
} BUTTON_INFO, *PBUTTON_INFO;

// ボタンの並びを設定。
extern void halInitKeys(BUTTON_INFO* btn, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1, unsigned int a, unsigned int b, unsigned int ctr, unsigned int esc);
// ボタンを送信。
extern void halSetKeys(BUTTON_INFO* btn, int src);
// 1 ~ 16 の 数値を出力。
extern int  halKeyToNum(BUTTON_INFO* btn);
extern int  halKeyAB(BUTTON_INFO* btn);
extern int  halKey20(BUTTON_INFO* btn);
extern int  halKeyCtr4(BUTTON_INFO* btn);
extern int  halKeyCtr8(BUTTON_INFO* btn);
extern int  halKeyCtr12(BUTTON_INFO* btn);
extern int  halKeyCtr20(BUTTON_INFO* btn);
extern int  halKey8(BUTTON_INFO* btn);

extern int  halAB4(BUTTON_INFO* btn);

extern int  halIsA(BUTTON_INFO* btn);
extern int  halIsB(BUTTON_INFO* btn);
extern int  halIsB_hold(BUTTON_INFO* btn);
extern int  halIsAB(BUTTON_INFO* btn);
extern int  halIsAB_hold(BUTTON_INFO* btn);
extern int  halIsAB_rrse(BUTTON_INFO* btn);
extern int  halIsAB_diff(BUTTON_INFO* btn);
extern int  halIsAxB(BUTTON_INFO* btn);

extern int  halIsKey(BUTTON_INFO* btn);
extern int  halIsKey_hold(BUTTON_INFO* btn);
extern int  halIsFirstKey( BUTTON_INFO* btn );

#ifdef __cplusplus
	}	   // extern "C"
#endif
#endif