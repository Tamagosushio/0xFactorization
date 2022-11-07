# include <Siv3D.hpp>
# include "Game.hpp"



// log2の計算
int GAME::log2(int x) {
	int n = 32;
	if (!(x & 0xFFFF0000)) n -= 16, x <<= 16;
	if (!(x & 0xFF000000)) n -= 8, x <<= 8;
	if (!(x & 0xF0000000)) n -= 4, x <<= 4;
	if (!(x & 0xC0000000)) n -= 2, x <<= 2;
	if (!(x & 0x80000000)) n -= 1;
	return n;
}



// ウィンドウサイズを設定
void GAME::SetWindowSize(void) {
	WindowSize = Window::GetState().virtualSize;
}

// 選択肢の当たり判定用四角形を設定
void GAME::SetChoicesRect(void) {
	// 選択肢の数だけ設定
	for (auto i : step(choices.size())) {
		// 図形の中心から描画する
		hit_rect << Rect{ Arg::center((i % 3) * 100 + (WindowSize.x - 500), (i / 3) * 100 + 150), 100 };
	}
}

// 問題の数字を設定
void GAME::SetQnum(void) {
	// 全て割り切ったら
	if (q_num == 1) {
		// log2(正解数+1)だけ素因数を増やしていく
		for (auto i : step(log2(correct_cnt + 1))) {
			// 素因数を抽選
			int factor = DiscreteSample(choices, distribution);
			// 問題となる数字にかけていく
			q_num *= factor;
		}
	}
	return;
}


// 背景画像の描画
void GAME::DrawBackground(void) {
	background.resized(WindowSize).draw(0, 0);
}


// 切り替えボタンの描画
void GAME::DrawButton(void) {
	// 当たり判定用の四角形
	const Rect button_rect = Rect{ (WindowSize.x - 500) / 2,  WindowSize.y - 150, 500, 120 };
	// 枠線表示
	button_rect.draw(ColorF{1.0, 1.0, 1.0, 0.0 }).drawFrame(3, 3, Palette::Darkgrey);
	// 表示するテキストを決定
	String button_str;
	if (is16) {
		button_str = U"10進数に変換";
	}else{
		button_str = U"16進数に変換";
	}
	// テキストを表示
	font_button(button_str).draw(button_rect.stretched(-5), Palette::Black);

	// ボタンにマウスが被さったら
	if (button_rect.mouseOver()) {
		// マウスカーソルを手のアイコンにする
		Cursor::RequestStyle(CursorStyle::Hand);
		// ボタンがクリックされたら
		if (button_rect.leftClicked()) {
			// 反転させる
			is16 ^= true;
		}
	}
	return;
}


// 問題の数字の表示
void GAME::DisplayQnum(void) {
	if (is16) {
		// 16進数表示
		font_q(U"{:X}"_fmt(q_num)).draw(100, 40, Palette::Black);
	}else {
		// 10進数表示
		font_q(U"{}"_fmt(q_num)).draw(100, 40, Palette::Black);
	}
	return;
}


// 詳細表示
void GAME::DisplayDetails(void) {
	// 正解数の表示
	font_details(U"正解数:{}"_fmt(correct_cnt)).draw(100, 150, Palette::Black);
	// ミス数の表示
	font_details(U"ミス数:{}"_fmt(miss_cnt)).draw(100, 250, Palette::Black);
	// 正答率を小数点第2位まで表示
	if (correct_cnt + miss_cnt != 0) {
		font_details(U"正答率:{:.2f}%"_fmt((double)correct_cnt / (double)(correct_cnt + miss_cnt) * 100)).draw(100, 350, Palette::Black);
	}
	// タイムの表示
	if (stopwatch.isRunning()) {
		font_details(U"{}"_fmt(stopwatch.format())).draw(100, 450, Palette::Black);
	}
	return;
}


// 選択肢と当たり判定用図形の描画
void GAME::DrawChoices(void) {
	for (auto i : step(choices.size())) {
		// 選択肢の描画
		if (is16) {
			font_choices(U"{:X}"_fmt(choices[i])).drawAt(choices_pos(i, WindowSize), Palette::Black);
		}else {
			font_choices(U"{}"_fmt(choices[i])).drawAt(choices_pos(i, WindowSize), Palette::Black);
		}
		// 当たり判定用四角形の描画
		hit_rect[i].draw(ColorF{1.0, 1.0, 1.0, 0.0 });
	}
}


// マウス操作の処理
void GAME::MouseOperation(void) {
	// 各選択肢に対して実行
	for (auto i : step(choices.size())) {
		// 選択肢上にマウスが重なったら
		if (hit_rect[i].mouseOver()) {
			// マウスカーソルを手の状態にする
			Cursor::RequestStyle(CursorStyle::Hand);
			// 当たり判定用図形を水色にする
			hit_rect[i].draw(ColorF{ 0.2, 0.2, 0.4, 0.5 });

			// 選択肢を左クリックしたとき
			if (hit_rect[i].leftClicked()) {
				// その選択肢が正しいなら
				if (q_num % choices[i] == 0) {
					// その値で問題の数値を割る
					q_num /= choices[i];

					// その問題が終わったら
					if (q_num == 1) {
						// 正解数を1増やす
						correct_cnt++;
						// 正解用SEを流す
						correct_se.playOneShot();
						// 最初の問題ならタイマーをスタート
						if (correct_cnt == 1) {
							stopwatch.start();
						}
					}
				}
				// 間違っているなら
				else {
					wrong_se.playOneShot();
					miss_cnt++;
				}
			}
		}
	}
}



// ゲームを実行
void GAME::Execute(void) {
	SetWindowSize();
	SetChoicesRect();
	// ゲーム画面
	while (System::Update()) {
		SetQnum();
		DrawBackground();
		DrawButton();
		DisplayQnum();
		DisplayDetails();
		DrawChoices();
		MouseOperation();
	}
}
