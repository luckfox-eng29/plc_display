![luckfox](https://github.com/LuckfoxTECH/luckfox-pico/assets/144299491/cec5c4a5-22b9-4a9a-abb1-704b11651e88)
[中文](./README_CN.md)
# Luckfox LyraPLC Display
Luckfox LyraPLC Display is the on-board screen user interface for Luckfox LyraPLC devices, mainly used to monitor system status. It cannot run standalone.

## Compilation
Requirements: CMake 3.10+ and an ARM cross toolchain for the target.

The toolchain is not hard-coded. Pass one of the following to CMake:

* Toolchain prefix (the value ends with the trailing `-`, so `<prefix>gcc` is the C compiler)
  ```bash
  cmake -B build -DPLC_TOOLCHAIN_PREFIX=/opt/toolchain/bin/arm-none-linux-gnueabihf-
  ```
* Compilers directly
  ```bash
  cmake -B build \
    -DCMAKE_C_COMPILER=/path/to/arm-none-linux-gnueabihf-gcc \
    -DCMAKE_CXX_COMPILER=/path/to/arm-none-linux-gnueabihf-g++
  ```
* A CMake toolchain file
  ```bash
  cmake -B build -DCMAKE_TOOLCHAIN_FILE=../arm.cmake
  ```

Then build:
```bash
cmake --build build
```

The version reported by `plc_display --version` defaults to `0.0.3` and lives in `CMakeLists.txt` only:
```bash
cmake -B build -DPLC_TOOLCHAIN_PREFIX=... -DPLC_DISPLAY_VERSION=1.2.0
```

Copy the produced `plc_display` to the device and run it. It expects `/dev/fb0` and `/dev/input/event0` to exist, and connects to the web UI over the control socket `/var/run/kvm_lyra_plc_display.sock` when that service is running.

To read the build version without starting the UI:
```bash
plc_display --version    # or -v
```

## Detailed Usage Instructions
[Luckfox LyraPLC](https://wiki.luckfox.com/Luckfox-Lyra-PLC)

## License
Released under the GNU General Public License v2.0. See [LICENSE](./LICENSE).
