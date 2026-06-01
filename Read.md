# MSPM0-Code-Config

一个开箱即用的 **MSPM0 系列微控制器** (如 MSPM0G3507) 开发模板，让你告别复杂的工程配置，专注于代码编写。

本项目为你配置好了基于 **CMake** + **ARM GCC** 的完整开发环境，并集成了 **TI MSPM0 SDK**、**J-Link** 调试支持和 **SysConfig** 图形化配置工具。

## ✨ 核心特性

*   **🗂️ 一键工程模板**：预置了 `CMakeLists.txt`，只需简单的命令行即可完成编译。
*   **⚙️ SysConfig 集成**：支持 TI 官方的 SysConfig 图形化工具，帮助你直观地配置时钟、外设等。
*   **💻 现代化 IDE 支持**：专为 `Visual Studio Code` 优化，集成了 `clangd` 语言服务器，提供精准的代码补全、跳转和格式化功能。
*   **🐛 开箱即用的调试**：预置了 **J-Link** 调试配置 (`launch.json`)，按 `F5` 即可开始调试。
*   **🚀 一键烧录脚本**：提供了 `flash` 脚本，可以方便地将程序烧录到目标芯片。

## 📋 环境安装指南

### 1. 安装 ARM GCC 编译器
ARM GCC 是用于编译 ARM 架构代码的工具链。
*   **下载地址**：[ARM 官网](https://developer.arm.com/downloads/-/gnu-rm)
*   **安装建议**：
    *   下载 `gcc-arm-none-eabi-xxx-win32.exe` 安装包。
    *   安装时**务必勾选** `"Add path to environment variable"`，将工具链添加到系统 PATH。
    *   安装完成后，打开命令行输入 `arm-none-eabi-gcc --version` 验证是否成功。

### 2. 安装 CMake
CMake 是项目构建工具。
*   **下载地址**：[CMake 官网](https://cmake.org/download/)
*   **安装建议**：
    *   下载 Windows 安装包 (`.msi`)。
    *   安装时选择 `"Add CMake to the system PATH for all users"`。


### 3. 安装 J-Link 软件
J-Link 用于调试和烧录程序。
*   **下载地址**：[SEGGER 官网](https://www.segger.com/downloads/jlink/)
*   **安装建议**：
    *   下载 `JLink_Windows_Vxxx.exe` 安装包。
    *   安装时使用默认选项即可。
    *   安装完成后，记住安装路径 (例如 `C:\Program Files\SEGGER\JLink`)，后续需要在 VS Code 中配置。

### 4. 下载 MSPM0 SDK
TI 提供的软件开发套件，包含驱动库和示例代码。
*   **下载地址**：[TI 官网](https://www.ti.com/tool/download/MSPM0-SDK)
*   **安装建议**：
    *   下载并解压到一个没有空格和中文的路径，例如 `D:\ti\mspm0_sdk`。

### 5. 安装 VS Code 插件
打开 VS Code，安装以下插件：
*   **clangd**：提供代码智能提示 (推荐)。
*   **CMake Tools**：方便在 VS Code 中配置和构建。
*   **Cortex-Debug**：用于调试 ARM 芯片。

## 🚀 快速开始

### 1. 克隆项目
```bash
git clone https://github.com/dourenshuai18/MSPM0-Code-Config.git
cd MSPM0-Code-Config
```

### 2. 修改 SDK 路径
打开 `CMakeLists.txt`，找到 `set(MSPM0_SDK_PATH ...)` 这一行，将其修改为你电脑上 SDK 的实际路径。
```cmake
# 请修改为你的 MSPM0 SDK 安装路径
set(MSPM0_SDK_PATH "D:/ti/mspm0_sdk/source")
```

### 3. 配置 VS Code 调试器路径
打开 `.vscode/settings.json`，确保 `cortex-debug.JLinkGDBServerPath` 指向你安装的 J-Link GDB 服务器路径。
```json
{
    "cortex-debug.JLinkGDBServerPath": "C:/Program Files/SEGGER/JLink/JLinkGDBServerCL.exe"
}
```

### 4. 配置并编译
在项目根目录下打开终端，执行以下命令：
```bash
# 1. 创建一个用于存放编译输出的 build 目录
mkdir -p build
cd build

# 2. 运行 CMake 配置，并指定编译器
cmake -DCMAKE_C_COMPILER=arm-none-eabi-gcc -G "Ninja" ..

# 3. 开始编译
cmake --build .
```
编译成功后，你会在 `build` 目录下看到生成的 `.elf` 文件。

### 5. 烧录与调试
*   **烧录**：在项目根目录下运行 `./flash` 脚本即可完成烧录 (确保 J-Link 已连接)。
*   **调试**：在 VS Code 中按 `F5`，选择 `Debug with JLink` 配置，即可开始调试。

## 📁 项目结构

```text
.
├── .vscode/                       # VS Code 配置文件目录
│   ├── launch.json                # 调试配置 (仅 J-Link)
│   ├── tasks.json                 # 构建任务配置
│   ├── settings.json              # 项目专用设置 (含 clangd 和 J-Link 路径)
│   └── keybindings.json           # 快捷键绑定 (可选)
├── build/                         # 编译输出目录 (自动生成)
├── CMakeLists.txt                 # CMake 主配置文件
├── mspm0g3507.lds                 # 链接脚本 (定义内存布局)
├── empty.syscfg                   # SysConfig 配置文件
├── ti_msp_dl_config.c/h           # SysConfig 生成的驱动代码
├── main.c                         # 用户主程序入口
├── flash                          # 烧录脚本 (需配合 J-Link)
├── .clang-format                  # 代码格式化规则文件
└── README.md                      # 本文件
```

## ⚙️ 自定义配置

### 1. 修改代码格式化规则
项目的格式化规则由根目录下的 `.clang-format` 文件控制。你可以根据自己的编码习惯修改它。

### 2. 更改 SysConfig 配置
*   你可以直接编辑 `empty.syscfg` 文件，或者使用 **SysConfig 图形化工具**（通常位于 SDK 的 `/tools` 目录下）打开它进行图形化配置。
*   修改后，重新运行构建命令，生成的 `ti_msp_dl_config.c/h` 会自动更新。

### 3. 修改烧录脚本
*   如果你的 J-Link 安装路径不同，请编辑项目根目录下的 `flash` 脚本文件，修改其中的 `JLINK` 路径。
。

## 📖 参考资源

*   [TI MSPM0 SDK 文档](https://www.ti.com/tool/download/MSPM0-SDK)
*   [ARM GCC 工具链下载](https://developer.arm.com/downloads/-/gnu-rm)
*   [CMake 官方文档](https://cmake.org/documentation/)
*   [SEGGER J-Link 用户手册](https://www.segger.com/downloads/jlink)

## 🤝 如何贡献

欢迎通过提交 Issue 或 Pull Request 来改进这个项目模板。

## 📝 许可证

本项目采用 [MIT 许可证](https://choosealicense.com/licenses/mit/) 进行开源。

## Star History

如果这个项目对你有帮助，别忘了给它一个 ⭐️！
