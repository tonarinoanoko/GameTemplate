cmake_minimum_required(VERSION 3.5.0)
project(GameTemplate)

include_directories("C:/Users/User/Desktop/work/GameTemplate/include/DxLib")
include_directories("src") # src ディレクトリ以下をすべてインクルードパスに追加
link_directories("C:/Users/User/Desktop/work/GameTemplate/lib/DxLib")

# src ディレクトリ以下のすべての .cpp ファイルを再帰的に検索
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(GameTemplate ${SOURCES})

target_link_libraries(GameTemplate DxLib.lib DxLib_d.lib)
