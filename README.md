# 大浦版FFT(一次元DFT/DCT) C++ラッパーライブラリ
## 使用方法
以下のヘッダをインクルードします。
```cpp
#include <fftsg/fftsg.hpp>
```

### 離散フーリエ変換: `FFTEngine`クラス
```cpp
// コンストラクタ: フレームサイズ(サンプル数)を指定。Nは2^nの値で指定すること。
fftsg::FFTEngine<float> fftEngine(N);

// FFT
fftEngine.fft(samples);

// IFFT
fftEngine.ifft(samples);
```
※ `samples` には `std::vector<std::complex<float>>`(要素数N) または `std::vector<float>`(実部と虚部を交互に並べたもの、要素数2N) を指定します

### 離散フーリエ変換(実数バージョン): `RFFTEngine`クラス
```cpp
// コンストラクタ: フレームサイズ(サンプル数)を指定。Nは2^nの値で指定すること。
fftsg::RFFTEngine<float> rfftEngine(N);

// FFT
rfftEngine.rfft(samples);

// IFFT
rfftEngine.irfft(samples);
```
※ `samples` には `std::vector<float>`(実部のみ、要素数N) を指定します

### 離散コサイン変換: `DCTEngine`クラス
```cpp
// コンストラクタ: フレームサイズ(サンプル数)を指定。Nは2^nの値で指定すること。
fftsg::DCTEngine<float> dctEngine(N);

// DCT
dctEngine.dct(samples);

// IDCT
dctEngine.idct(samples);
```
※ `samples` には `std::vector<float>`(実部のみ、要素数N) を指定します

## Cコードの改変部分
`fftsg.c`のうち、以下の部分を改変しています。

- (C++の場合)コード全体を`fftsg`名前空間内に入れるように
    - それに伴い、コード中の`#include`は先頭の名前空間外に移動
- double型をfloat型に置き換えたものを追加(`fftsg_float.c`)
    - float版は関数名の末尾に`f`を追加(C言語はオーバーロードできないため)
    - float版は実数値に`f`のサフィックスを付けてfloat型に
    - float版では数学関数に`sinf()`などのfloat用関数を使うよう変更(C言語の数学関数はオーバーロードされないため)
    - (C++の場合)オーバーロードでdouble型とfloat型の関数を同じ関数名で使用できるように
- 内部の計算に使用する関数は`static`を付けて内部リンケージにするように
    - そのままだとリンク時にdouble版とfloat版の関数名が衝突するため
    - それに伴って関数の宣言順などを変更

## 注意点
- 離散サイン変換は個人的に利用する機会がなく動作テストできていないので除外しています
- 各メンバ関数には`const`が付いていません
    - 初回のみsin/cosテーブル構築の副作用が発生するためです
        - TODO: コンストラクタで行うよう変更することで改善する予定
    - そのため、FFTを利用するクラスを作成したい場合は`FFTEngine`をメンバ変数として持たせるのではなく、クラスの各メンバ関数の引数に`FFTEngine`の参照を取るなどして外部から渡すことをお勧めします
        - こうすることで、利用クラス側のメンバ関数は`const`にできます
        - また、利用クラスの複数のインスタンスで同じ`FFTEngine`を使い回せるようにもなります

## ライセンス
- このラッパーライブラリ自体のコードのライセンスは「Unlicense」です
- ただし、`src/fftsg.c`および`src/fftsg_float.c`は大浦版FFTのライセンスに準拠します
    - そのため、使用の際はラッパーライブラリ上でコードの修正が行われていることを必ず明記してください

## 大浦版FFTについて
### 配布ページ
- http://www.kurims.kyoto-u.ac.jp/~ooura/fft-j.html

### README原文
- [readme_fftsg.txt](readme_fftsg.txt)

### ライセンス原文
```
Copyright Takuya OOURA, 1996-2001

このソースコードはフリーソフトです．商用目的を含め，このコードの使用， コピー，修正及び配布は自由に行って結構です．ただし，このコードの修正を 行った場合は，そのことを明記してください．
```
