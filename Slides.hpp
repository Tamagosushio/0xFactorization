# pragma once
# include <Siv3D.hpp>

// 最初の説明用スライド
class SLIDES {
	private:
		// 画像配列
		Array<Texture> slides;
		// 画像があるディレクトリのパス
		const Array<String> slides_path = FileSystem::DirectoryContents(FileSystem::CurrentDirectory() + U"slides/");

	public:
		// 画像を読み込む
		void SetImages(void);
		// 画像を描画
		void DisplayImages(Size MonitorSize);
};
