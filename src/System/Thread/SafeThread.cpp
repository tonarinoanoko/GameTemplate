#include "SafeThread.h"

template <typename Function, typename... Args>
SafeThread::SafeThread(Function&& func, Args&&... args) {
    _thread = std::make_unique<std::thread>(std::forward<Function>(func), std::forward<Args>(args)...);
}

// デストラクタでjoinを呼び出す
SafeThread::~SafeThread() {
    if (isFinished() == false) {
        _thread->join();  // スレッドがjoinableならjoin
    }
}

// スレッドが終了したかどうかを確認するメソッド
bool SafeThread::isFinished() const {
    return _thread == nullptr || _thread->joinable() == false; // スレッドが無効か、終了している場合
}
