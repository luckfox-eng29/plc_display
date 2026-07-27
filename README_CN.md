![luckfox](https://github.com/LuckfoxTECH/luckfox-pico/assets/144299491/cec5c4a5-22b9-4a9a-abb1-704b11651e88)
[English](./README.md)
# Luckfox LyraPLC Display
Luckfox LyraPLC Display 是 Luckfox LyraPLC 设备的屏幕用户界面应用，主要用于监控系统运行状态，无法单独运行。

## 编译
依赖：CMake 3.10+ 和目标平台的 ARM 交叉编译工具链。

工具链路径没有硬编码，向 CMake 传入以下任一参数即可：

* 工具链前缀（值以结尾的 `-` 结束，因此 `<prefix>gcc` 就是 C 编译器）
  ```bash
  cmake -B build -DPLC_TOOLCHAIN_PREFIX=/opt/toolchain/bin/arm-none-linux-gnueabihf-
  ```
* 直接指定编译器
  ```bash
  cmake -B build \
    -DCMAKE_C_COMPILER=/path/to/arm-none-linux-gnueabihf-gcc \
    -DCMAKE_CXX_COMPILER=/path/to/arm-none-linux-gnueabihf-g++
  ```
* 使用 CMake toolchain 文件
  ```bash
  cmake -B build -DCMAKE_TOOLCHAIN_FILE=../arm.cmake
  ```

然后执行编译：
```bash
cmake --build build
```

`plc_display --version` 报告的版本号默认为 `0.0.3`，且只在 `CMakeLists.txt` 中定义：
```bash
cmake -B build -DPLC_TOOLCHAIN_PREFIX=... -DPLC_DISPLAY_VERSION=1.2.0
```

将编译产物 `plc_display` 上传到设备后直接运行即可。运行时会使用 `/dev/fb0` 与 `/dev/input/event0`；若 Web UI 服务已启动，还会通过控制套接字 `/var/run/kvm_lyra_plc_display.sock` 与其连接。

不启动界面、仅查看编译版本：
```bash
plc_display --version    # 或 -v
```

## 详细使用说明
[Luckfox LyraPLC](https://wiki.luckfox.com/Luckfox-Lyra-PLC)

## 开源协议
本项目基于 GNU General Public License v2.0 发布，详见 [LICENSE](./LICENSE)。
