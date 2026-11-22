# HF/VHF Qt6 Scanner GUI

Qt6 replacement for the pygame HDMI GUI.

## Open in Visual Studio

1. Install Qt 6 and the Qt VS Tools extension.
2. Open the folder in Visual Studio (File → Open → Folder) or open the CMakeLists.txt.
3. Select a Qt6 kit and build.

## Build on the Pi (or Linux)

```bash
sudo apt install qt6-base-dev cmake
mkdir build && cd build
cmake ..
make
```

## Status

- Window and soft-key layout are in place.
- PiScanClient has the TCP connection skeleton.
- Protobuf encoding/decoding still needs to be wired (see the Python version in the main listening-post repo for the message layout).
