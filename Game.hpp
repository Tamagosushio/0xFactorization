# pragma once
# include <Siv3D.hpp>



class GAME {
	private:
		// 選択肢となる素因数
		const Array<int> choices = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
		// 選択肢が選ばれる確率の調整
		DiscreteDistribution& distribution;

		// 選択肢用のフォント
		const Font& font_choices;
		// 詳細表示用のフォント
		const Font& font_details;
		// 問題表示用のフォント
		const Font& font_q;
		// 進数切り替えボタン用のフォント
		const Font& font_button;

		// 正解用SE
		const Audio correct_se{ Resource(U"audio/QuizCorrect.mp3") };
		// 不正解用SE
		const Audio wrong_se{ Resource(U"audio/QuizIncorrect.mp3") };

		// 当たり判定用の図形
		Array<Rect> hit_rect;

		// 正解数
		long long correct_cnt = 0;
		// ミス数
		long long miss_cnt = 0;
		// 問題
		long long q_num = 1;

		// 記録用のストップウォッチ
		Stopwatch stopwatch;

		// ウィンドウサイズ
		Size WindowSize;

		// 16進,10進切り替え
		bool is16 = true;

		// 背景画像
		const Texture background{ Resource(U"image/purple_back.jpg") };



		// 選択肢の位置決め
		Vec2 choices_pos(size_t i, Size WindowSize) {
			return { (i % 3) * 100 + (WindowSize.x - 500), (i / 3) * 100 + 150 };
		}

		// log2の計算
		int log2(int x);

	public:
		// コンストラクタ
		GAME(DiscreteDistribution& _distribution, const Font& _font_choices, const Font& _font_details, const Font& _font_q, const Font& _font_button) :
			distribution(_distribution),
			font_choices(_font_choices),
			font_details(_font_details),
			font_q(_font_q),
			font_button(_font_button) {
		};


		// ウィンドウサイズを設定
		void SetWindowSize(void);
		// 選択肢の当たり判定用四角形を設定
		void SetChoicesRect(void);

		// 問題となる数字を設定
		void SetQnum(void);
		// 背景画像の描画
		void DrawBackground(void);
		// 10進16進を切り替えるボタンを描画
		void DrawButton(void);
		// 問題の表示
		void DisplayQnum(void);
		// 詳細表示
		void DisplayDetails(void);
		// 選択肢と当たり判定用図形の描画
		void DrawChoices(void);
		// マウス操作の処理
		void MouseOperation(void);

		// ゲームを実行
		void Execute();

};
