#pragma once
#include <thread>
#include <memory>


// デストラクタでjoinを行う比較的安全なスレッド処理
// System::SafeThread thread(関数, 引数);を呼び出しだらスレッド処理が開始される。
// 終了チェック時にisFinishedを呼ぶことで安全に終了したかをチェックできるので、確実に終了が約束されていない処理がある場合はチェックをしてから次に進むこと。
class SafeThread {
public:
    // コンストラクタでスレッドを作成
    template <typename Function, typename... Args>
    explicit SafeThread(Function&& func, Args&&... args);

    // デストラクタでjoinを呼び出す
    ~SafeThread();

    // スレッドが終了したかどうかを確認するメソッド
    bool isFinished() const;

private:
    std::unique_ptr<std::thread> _thread;
};
