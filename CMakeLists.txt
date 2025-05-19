cmake_minimum_required(VERSION 4.0.2)
project(GameTemplate)
set(CMAKE_CXX_STANDARD 20)

include_directories("include/DxLib")
include_directories("src") # src ディレクトリ以下をすべてインクルードパスに追加
link_directories("lib/DxLib")

# src ディレクトリ以下のすべての .cpp ファイルを再帰的に検索
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(GameTemplate ${SOURCES})

target_link_libraries(GameTemplate DxLib DxUseCLib DxDrawFunc jpeg png zlib tiff theora_static vorbis_static vorbisfile_static ogg_static bulletdynamics bulletcollision bulletmath opusfile opus silk_common celt ws2_32 winmm gdi32)
