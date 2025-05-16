cmake_minimum_required(VERSION 3.0.0)
project(MyGame)

# DxLib のインクルードディレクトリとライブラリディレクトリを指定
# (DxLib のインストール場所に合わせてパスを修正してください)
include_directories("C:/Users/User/Desktop/work/GameTemplate/include/DxLib")
link_directories("C:/Users/User/Desktop/work/GameTemplate/lib/DxLib")

# src ディレクトリ内のすべての .cpp ファイルを検索して変数に格納
file(GLOB SOURCES "src/*.cpp")

# 実行可能ファイルを作成
add_executable(GameTemplate ${SOURCES})

# DxLib のライブラリをリンク
target_link_libraries(GameTemplate DxLib.lib DxLib_d.lib) # デバッグ版もリンクしておくと便利です
