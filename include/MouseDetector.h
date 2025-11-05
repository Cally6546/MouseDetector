#ifndef MOUSE_DETECTOR_H
#define MOUSE_DETECTOR_H

#include <functional>
#include <string>
#include <atomic>
#include <thread>

class MouseDetector {
public:
    std::function<void(const std::string& deviceName)> onMousePlugged;
    std::function<void(const std::string& deviceName)> onMouseRemoved;

    MouseDetector();
    ~MouseDetector();

    void start(); // Start monitoring
    void stop();  // Stop monitoring

private:
    std::atomic<bool> running;
    std::thread monitorThread;

    void detectLoop();
};

#endif
