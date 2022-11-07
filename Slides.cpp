# include <Siv3D.hpp>
# include "Slides.hpp"


// 画像を読み込む
void SLIDES::SetImages(void) {
	// slidesディレクトリにあるファイルの絶対パスを取得
	for (int i = 1; i <= 5; i++) {
		// 画像配列に追加していく
		slides << Texture{Resource(U"slides/slide" + ToString(i) + U".png")};
	}
	return;
}


// 画像を描画
void SLIDES::DisplayImages(Size MonitorSize) {
	// スライドの何番目にいるか
	int cnt = 0;
	while (System::Update()) {
		// cnt番目のスライド画像をMonitorSizeに合わせて描画
		slides[cnt].resized(MonitorSize).draw(0,0);
		// 画面が左クリックされたら
		if (Rect{ 0, 0, MonitorSize }.leftClicked()) {
			// スライドを次に進める
			cnt++;
		}
		// 最後のスライドがクリックされたら終了
		if (cnt == slides.size()) {
			break;
		}
	}
	return;
}
