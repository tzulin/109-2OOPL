/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	// tutorial_4_step2_addClassCPractice
	class CPractice {
	public:
		CPractice();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};

	//yueh practice
	class yueh_practice {
	public:
		yueh_practice();
		void LoadBitmap();
		void onMove();
		void onShow();
	private:
		CMovingBitmap test;
		int x, y;
	};

	class CBouncingBall;
	// tutorial_5_step2_addClassCGameMap
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();							// 載入地圖
		void OnShow();								// 顯示地圖
		void OnMove();								// tutorial_6_step3_播放彈跳球的動畫
		void OnKeyDown(UINT);							// tutorial_6_step3_處理按鍵按下後CGameMap的反應
		void RandomBouncingBall();					// tutorial_6_step3_隨機彈跳球的個數加入到map中
		void InitializeBouncingBall(int, int, int);	// tutorial_6_step3_初始化彈跳球
		~CGameMap();								// tutorial_6_step3_解構子
	private:
		CMovingBitmap blue, green;	// 建立藍和綠色地圖
		int map[4][5];				// 建立一個矩陣的index
		const int X, Y;				// 大地圖的左上角x, y座標
		const int MW, MH;			// 每張小地圖的寬高度
		CBouncingBall* bballs;		// tutorial_6_step3_CBouncingBall指標
		int random_num;				// tutorial_6_step3_隨機個數
	};

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit(); 									// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖

		CMovingBitmap   test2;		//yueh test2 bitmap
		CMovingBitmap   test;		//yueh test bitmap
		yueh_practice	test3;		//yueh test3

		CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		CEraser			eraser;		// 拍子
		CInteger		hits_left;	// 剩下的撞擊數
		CBouncingBall   bball;		// 反覆彈跳的球

		CMovingBitmap	kirby;	// tutorial_2a_step2_declareBitmapObject
		/*
		CMovingBitmap	practice2;	// tutorial_2b_step2_declareBitmapObject
		int				picX, picY;	// tutorial_3_step2_declareCoordinateOfPractice
		*/
		CPractice		c_practice;	// tutorial_4_step4
		CGameMap		gamemap;	// tutorial_5_step4_宣告地圖
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}