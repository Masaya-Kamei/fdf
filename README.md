# 42 fdf

## 概要

平行投影の一種である等角投影を使った3Dプロジェクション

- マップファイルを読み込む
- マップの回転やズームが可能
- 3次元の点をxy平面に正射影して基底変換する

## Demo

![fdf](https://user-images.githubusercontent.com/50983708/153358359-3cae0d77-476d-481e-b254-cf85210f0178.gif)

## Usage

```zsh
git clone https://github.com/Masaya-Kamei/fdf.git --recursive
cd fdf
make
./fdf [map_file]
```

- 回転: 矢印キー
- ズーム: マウスホイール

map_file の例: `maps/42.fdf`

```txt
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

## キーワード

`C`,`3Dプロジェクション`,`平行投影`,`等角投影`,`ベクトル`,`正射影`,`基底変換`,`軸周りの回転` 

## Tool

- [my libft](https://github.com/Masaya-Kamei/libft) (42 useful functions)
- [42 minilibx_macos](https://git.hexanyn.fr/42-bocal/minilibx/-/tree/master/minilibx_macos) (42 simple graphics library)
- [42 minilibx-linux](https://github.com/42Paris/minilibx-linux) (42 simple graphics library)
- [Github Actions](https://docs.github.com/ja/actions) (CI/CD tool)
