#include "MouseDetector.h"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef __linux__
#include <libudev.h>
#endif

MouseDetector::MouseDetector() : running(false) {}
MouseDetector::~MouseDetector() { stop(); }

void MouseDetector::start() {
    if (running) return;
    running = true;
    monitorThread = std::thread(&MouseDetector::detectLoop, this);
}

void MouseDetector::stop() {
    if (!running) return;
    running = false;
    if (monitorThread.joinable())
        monitorThread.join();
}

void MouseDetector::detectLoop() {
#ifdef __linux__
    struct udev *udev = udev_new();
    if (!udev) return;

    struct udev_monitor *mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "input", NULL);
    udev_monitor_enable_receiving(mon);
    int fd = udev_monitor_get_fd(mon);

    while (running) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        struct timeval tv{1, 0};

        int ret = select(fd + 1, &fds, nullptr, nullptr, &tv);
        if (ret > 0 && FD_ISSET(fd, &fds)) {
            struct udev_device *dev = udev_monitor_receive_device(mon);
            if (dev) {
                const char *action = udev_device_get_action(dev);
                const char *devnode = udev_device_get_devnode(dev);
                if (action && devnode) {
                    std::string name = devnode;
                    if (std::string(action) == "add" && onMousePlugged)
                        onMousePlugged(name);
                    else if (std::string(action) == "remove" && onMouseRemoved)
                        onMouseRemoved(name);
                }
                udev_device_unref(dev);
            }
        }
    }
    udev_unref(udev);
#else
    // Simulation for non-Linux
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (onMousePlugged) onMousePlugged("Simulated Mouse");
    }
#endif
}
