# HF/VHF Qt6 Scanner GUI

Qt6 replacement for the pygame HDMI GUI. Speaks the PiScan protobuf protocol on TCP port 1234.

## Open in Visual Studio

1. Install Qt 6, the Qt VS Tools extension, and the Protocol Buffers compiler + library.
2. Open the folder (File → Open → Folder) or the CMakeLists.txt.
3. Configure with a Qt6 kit and build.

## Build on the Pi / Linux

```bash
sudo apt install qt6-base-dev cmake protobuf-compiler libprotobuf-dev
mkdir build && cd build
cmake ..
make
./hf-vhf-qt-gui
```

## Features

- Live frequency and state display
- SCAN / HOLD / MAN / SQL soft keys
- Full protobuf encode/decode (ClientToServer / ServerToClient)
- Automatic context polling once connected

The GUI expects PiScan to be running on localhost:1234 (or change the host in ScannerWindow).
