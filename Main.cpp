# include <Siv3D.hpp>
# include "Slides.hpp"
# include "Game.hpp"


void Main() {

	// ウィンドウをフルスクリーンにする
	Window::SetFullscreen(true);

	// ウィンドウタイトルの変更
	Window::SetTitle(U"0xFactorization");

	// 選択肢が選ばれる確率の調整
	DiscreteDistribution distribution({ 125, 125, 100, 80, 45, 30, 18, 12, 5, 2, 1, 1 });
	// 選択肢表示用font
	const Font font_choices(75, Typeface::Bold);
	// 詳細表示用font
	const Font font_details(75, Typeface::Bold);
	// 問題表示用font
	const Font font_q(100, Typeface::Heavy);
	// 進数切り替えボタン用font
	const Font font_button(75, Typeface::Heavy);

	// ウィンドウサイズの取得
	Size WindowSize = Window::GetState().virtualSize;
	
	// ゲーム説明部分
	SLIDES Slides;
	Slides.SetImages();
	Slides.DisplayImages(WindowSize);

	// ゲームを開始
	GAME Game(distribution, font_choices, font_details, font_q, font_button);
	Game.Execute();
	

}
