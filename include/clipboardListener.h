#pragma once

#include <windows.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ClipboardListener {
public:
    ClipboardListener();
    ~ClipboardListener();

    // Call once when you want to start monitoring (ignores old clipboard)
    void start();

    // Blocks until clipboard changes AFTER start()
    std::string waitForChange();
    void stop();

private:
    void threadMain();
    void handleClipboard();

    HWND hwnd_{ nullptr };
    std::thread thread_;

    std::mutex mutex_;
    std::condition_variable cv_;
    std::string latest_;

    std::atomic<bool> running_{ true };
    std::atomic<bool> armed_{ false };
};
