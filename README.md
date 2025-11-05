# 🖱️ MouseDetector (Cross-Platform C++17 Library)

**MouseDetector** is a simple, extensible library for detecting mouse (and other input device) plug/unplug events.  
It is written in **C++17** using **CMake** and designed to be included as an **external library** in your projects.

---

## ✅ Features

- Detects mouse plug/unplug events on **Linux** using `libudev`.
- Works on **Windows/macOS** in simulation mode (placeholder for future OS support).
- Can be included in any C++ project as a **static library**.
- Provides **callbacks** for mouse plug/unplug events.
- Cross-platform ready and extensible for future OS-specific implementations.

---

## 🧩 How It Works

1. The library defines a `MouseDetector` class with two callback functions:
   - `onMousePlugged` → called when a new mouse is connected.
   - `onMouseRemoved` → called when a mouse is removed.
2. On Linux:
   - Uses `libudev` to monitor `/dev/input` devices.
   - Detects real mouse events and calls the appropriate callback.
3. On Windows/macOS (simulation mode):
   - Simulates mouse plug events periodically for testing.
4. You include the library in your project, attach callbacks, and call `start()` to begin monitoring.

---

## 🚀 Build Instructions

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/Cally6546/MouseDetector.git
cd MouseDetector
