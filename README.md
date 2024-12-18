Circle
======

Overview
--------

Circle is a C++ bare metal programming environment for the Raspberry Pi. It should be usable on all existing models (tested on model A+, B, B+, on Raspberry Pi 2, 3, 4, 400, 5 and on Raspberry Pi Zero), except on the Raspberry Pi Pico, which is not supported. Circle provides several ready-tested [C++ classes](doc/classes.txt) and [add-on libraries](addon/README), which can be used to control different hardware features of the Raspberry Pi. Together with Circle there are delivered several [sample programs](sample/README), which demonstrate the use of its classes. Circle can be used to create 32-bit or 64-bit bare metal applications.

Circle includes bigger (optional) third-party C-libraries for specific purposes in addon/ now. This is the reason why GitHub rates the project as a C-language-project. The main Circle libraries are written in C++ using classes instead. That's why it is called a C++ programming environment.

The 48th Step
-------------

This release comes with **USB mass-storage device gadget** support. *test/usb-msd-gadget* shows, how this can be used to provide direct access to the SD card via USB. Furthermore this version supports **HDMI sound for the Raspberry Pi 5**. The sound samples and tests have been updated to use this. The **Raspberry Pi 5 with BCM2712 stepping D0** is supported. The **LVGL support** has been updated to **version 9.2.0**.

The network library has been updated to support the receiving of ICMP packets in applications. This is used in *test/ping-client* to implement a **ping client**. Raspberry Pi models without an on-board Ethernet NIC can be used with **RTL8152 and RTL8153 USB Ethernet adapters** to access a network.

The platform **DMA** controller drivers support **cyclic write transfers** now. To implement this, it was necessary to extend the type `TDMACompletionRoutine` by a buffer index. If you directly use DMA transfers in your application, you have to update your DMA completion routine.

There is a complete rewrite of the Flashy **serial bootloader tool in C**, which is called cFlashy and which does not need a Node-JS environment any more. You can define `USEFLASHY=0` in the file *Config.mk* to enable it. See [doc/bootloader.txt](doc/bootloader.txt) for details.

More news:

* A class `CmDNSPublisher` was added, which can be used to publish services to mDNS (aka Bonjour) in a local network. See *test/mdns-publisher* for an example.
* There is a new option `backlight=` for *cmdline.txt* for setting the backlight level for the Official 7" Raspberry Pi touchscreen. For some versions of this touchscreen this option is required.
* The class `CSerialDevice` now supports modifying the parity setting (including a mark or space parity) and a per character receive for specific RS-485 applications.
* A block cursor can be enabled on the screen using `CScreenDevice::SetCursorBlock()`. See *test/screen-ansi-colors* for an example.
* The SD card driver implements the `GetSize()` method now.
* Only serious USB transaction errors are logged on Raspberry Pi 1-3 any more.
* The new doc file [doc/debug-swd.txt](doc/debug-swd.txt) explains SWD debugging on the Raspberry Pi 5 using the Raspberry Pi Debug Probe adapter.

Fixes:

* Only 4 GB RAM were usable, even on Raspberry Pi 5 with 8 GB RAM.
* The MAC address for WLAN access is read from the device tree on the Raspberry Pi 5 now, as it is required. Before always the same address was used.
* The Official 7" Raspberry Pi touchscreen did not work with circle-stdlib.
* The MQTT client delivered an invalid payload in `OnMessage()`, when there were multiple MQTT publish messages arriving in one network packet.
* The access to USB bulk endpoints on the Raspberry Pi 1-3 in no-hub configurations was occupying the whole USB bandwidth, which was not allowing to access other endpoints on the same USB device.
* The I2C master was not initialized on the Raspberry Pi 5 in *sample/34-sounddevices*.

The recommended firmware version has been updated and is required to use the Raspberry Pi 5 with BCM2712 stepping D0. Please note that the file *bcm2712d0.dtbo* has to be copied into the directory *overlays/* on the SD card.

Features
--------

> Only the features with a "x" or other info are currently supported on the Raspberry Pi 5.

Circle supports the following features:

| Group                 | Features                                            | Raspberry Pi 5 |
|-----------------------|-----------------------------------------------------|----------------|
| C++ build environment | AArch32 and AArch64 support                         | AArch64 only   |
|                       | Basic library functions (e.g. new and delete)       | x              |
|                       | Enables all CPU caches using the MMU                | x              |
|                       | Interrupt support (IRQ and FIQ)                     | IRQ only       |
|                       | Multi-core support (Raspberry Pi 2, 3 and 4)        | x              |
|                       | Cooperative non-preemtive scheduler                 | x              |
|                       | CPU clock rate management                           | x              |
|                       | Clang/LLVM support (experimental)                   | x              |
|                       |                                                     |                |
| Debug support         | Kernel logging to screen, UART and/or syslog server | x              |
|                       | C-assertions with stack trace                       | x              |
|                       | Hardware exception handler with stack trace         | x              |
|                       | GDB support using rpi_stub (Raspberry Pi 2 and 3)   |                |
|                       | Serial bootloader (by David Welch) included         | x              |
|                       | Software profiling support (single-core)            | x              |
|                       | QEMU support                                        |                |
|                       |                                                     |                |
| SoC devices           | GPIO pins (with interrupt, Act LED) and clocks      | x              |
|                       | Frame buffer (screen driver with escape sequences)  | limited        |
|                       | UART(s) (Polling and interrupt driver)              | x              |
|                       | System timer (with kernel timers)                   | x              |
|                       | Platform DMA controller                             | DMA40 only     |
|                       | RP1 platform DMA controller (Raspberry Pi 5 only)   | x              |
|                       | EMMC SD card interface driver                       | x              |
|                       | SDHOST SD card interface driver (Raspberry Pi 1-3)  |                |
|                       | PWM output (2 channels)                             | 4 channels     |
|                       | PWM sound output (on headphone jack)                | with adapter   |
|                       | I2C master(s) and slave                             | masters only   |
|                       | SPI0 master (Polling and DMA driver)                | x              |
|                       | SPI1 auxiliary master (Polling)                     |                |
|                       | SPI3-6 masters of Raspberry Pi 4 (Polling)          | SPI1-3 and 5   |
|                       | SMI master                                          |                |
|                       | I2S sound output and input                          | x              |
|                       | HDMI sound output (without VCHIQ)                   | x              |
|                       | Hardware random number generator                    | x              |
|                       | Watchdog device                                     | x              |
|                       | Official Raspberry Pi touch screen (v1 only)        |                |
|                       | VCHIQ interface and audio service drivers           |                |
|                       | BCM54213PE Gigabit Ethernet NIC of Raspberry Pi 4   |                |
|                       | MACB / GEM Gigabit Ethernet NIC of Raspberry Pi 5   | x              |
|                       | Wireless LAN access                                 | x              |
|                       |                                                     |                |
| USB                   | Host controller interface (HCI) drivers             | x              |
|                       | Standard hub driver (USB 2.0 only)                  | x              |
|                       | HID class device drivers (keyboard, mouse, gamepad) | x              |
|                       | Driver for on-board Ethernet device (SMSC951x)      |                |
|                       | Driver for on-board Ethernet device (LAN7800)       |                |
|                       | Driver for CDC Ethernet devices (RTL815x, QEMU)     |                |
|                       | Driver for USB mass storage devices (bulk only)     | x              |
|                       | Driver for USB audio streaming devices (RPi 4 only) | x              |
|                       | Drivers for different USB serial devices            | x              |
|                       | Audio class MIDI input support                      | x              |
|                       | Touchscreen driver (digitizer mode)                 | x              |
|                       | Printer driver                                      | x              |
|                       | MIDI gadget driver                                  |                |
|                       | Serial CDC gadget driver                            |                |
|                       | Mass-storage device gadget driver                   |                |
|                       |                                                     |                |
| File systems          | Internal FAT driver (limited function)              | x              |
|                       | FatFs driver (full function, by ChaN)               | x              |
|                       |                                                     |                |
| TCP/IP networking     | Protocols: ARP, IP, ICMP, UDP, TCP                  | x              |
|                       | Clients: DHCP, DNS, NTP, HTTP, Syslog, MQTT, mDNS   | x              |
|                       | Servers: HTTP, TFTP                                 | x              |
|                       | BSD-like C++ socket API                             | x              |
|                       |                                                     |                |
| Graphics              | OpenGL ES 1.1 and 2.0, OpenVG 1.1, EGL 1.4          |                |
|                       | (not on Raspberry Pi 4)                             |                |
|                       | uGUI (by Achim Doebler)                             |                |
|                       | LVGL (by LVGL Kft)                                  | x              |
|                       | 2D graphics class in base library                   |                |
|                       |                                                     |                |
| Not supported         | Bluetooth                                           |                |

Building
--------

> For building 64-bit applications (AArch64) see the next section.

> Circle does not support 32-bit applications on the Raspberry Pi 5.

This describes building on PC Linux. See the file [doc/windows-build.txt](doc/windows-build.txt) for information about building on Windows. If building for the Raspberry Pi 1 you need a [toolchain](http://elinux.org/Rpi_Software#ARM) for the ARM1176JZF core (with EABI support). For Raspberry Pi 2/3/4 you need a toolchain with Cortex-A7/-A53/-A72 support. A toolchain, which works for all of these, can be downloaded [here](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). Circle has been tested with the version *13.2.Rel1* (arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz) from this website. This is the recommended toolchain for AArch32 builds.

First edit the file *Rules.mk* and set the Raspberry Pi version (*RASPPI*, 1, 2, 3 or 4) and the *PREFIX* of your toolchain commands. Alternatively you can create a *Config.mk* file (which is ignored by git) and set the Raspberry Pi version and the *PREFIX* variable to the prefix of your compiler like this (don't forget the dash at the end):

```
RASPPI = 1
PREFIX = arm-none-eabi-
```

The following table gives support for selecting the right *RASPPI* value:

| RASPPI | Target         | Models                   | Optimized for |
| ------ | -------------- | ------------------------ | ------------- |
|      1 | kernel.img     | A, B, A+, B+, Zero, (CM) | ARM1176JZF-S  |
|      2 | kernel7.img    | 2, 3, Zero 2, (CM3)      | Cortex-A7     |
|      3 | kernel8-32.img | 3, Zero 2, (CM3)         | Cortex-A53    |
|      4 | kernel7l.img   | 4B, 400, CM4             | Cortex-A72    |

For a binary distribution you should do one build with *RASPPI = 1*, one with *RASPPI = 2* and one build with *RASPPI = 4* and include the created files *kernel.img*, *kernel7.img* and *kernel7l.img*. Optionally you can do a build with *RASPPI = 3* and add the created file *kernel8-32.img* to provide an optimized version for the Raspberry Pi 3.

The configuration file *Config.mk* can be created using the `configure` tool too. Please enter `./configure -h` for help on using it!

> There are a number of configurable system options in the file [include/circle/sysconfig.h](include/circle/sysconfig.h). Please have a look into this file to learn, how you can configure Circle for your purposes. Some hardware configurations may require modifications to these options (e.g. using USB on the CM4).

Then go to the build root of Circle and do:

```
./makeall clean
./makeall
```

By default only the Circle libraries are built. To build a sample program after `makeall` go to its subdirectory and do `make`.

You can also build Circle on the Raspberry Pi itself (set `PREFIX =` (empty)) on Raspbian but you need some method to put the *kernel.img* file onto the SD(HC) card. With an external USB card reader on model B+ or Raspberry Pi 2/3/4 model B (4 USB ports) this should be no problem.

AArch64
-------

Circle supports building 64-bit applications, which can be run on the Raspberry Pi 3, 4 or 5. There are also Raspberry Pi 2 versions and the Raspberry Pi Zero 2, which are based on the BCM2837 SoC. These Raspberry Pi versions can be used too (with `RASPPI = 3`).

The recommended toolchain to build 64-bit applications with Circle can be downloaded [here](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). Circle has been tested with the version *13.2.Rel1* (arm-gnu-toolchain-13.2.rel1-x86_64-aarch64-none-elf.tar.xz) from this website. This is the recommended toolchain for AArch64 builds.

There are distro-provided toolchains on certain Linux platforms (e.g. *g++-aarch64-linux-gnu* on Ubuntu or *gcc-c++-aarch64-linux-gnu* on Fedora), which may work with Circle and can be a quick way to use it, but you have to test this by yourself. If you encounter problems (e.g. no reaction at all, link failure with external library) using a distro-provided toolchain, please try the recommended toolchain (see above) first, before reporting an issue.

First edit the file *Rules.mk* and set the Raspberry Pi architecture (*AARCH*, 32 or 64) and the *PREFIX64* of your toolchain commands. The *RASPPI* variable has to be set to 3, 4 or 5 for `AARCH = 64`. Alternatively you can create a *Config.mk* file (which is ignored by git) and set the Raspberry Pi architecture and the *PREFIX64* variable to the prefix of your compiler like this (don't forget the dash at the end):

```
AARCH = 64
RASPPI = 3
PREFIX64 = aarch64-none-elf-
```

The configuration file *Config.mk* can be created using the `configure` tool too. Please enter `./configure -h` for help on using it!

Then go to the build root of Circle and do:

```
./makeall clean
./makeall
```

By default only the Circle libraries are built. To build a sample program after `makeall` go to its subdirectory and do `make`.

Installation
------------

Copy the Raspberry Pi firmware (from boot/ directory, do *make* there to get them) files along with the *kernel\*.img* (from sample/ subdirectory) to a SD(HC) card with FAT file system.

It is now always recommended to copy the file *config32.txt* (for 32-bit mode) or *config64.txt* (for 64-bit mode) from the boot/ directory to the SD(HC) card and to rename it to *config.txt* there. These files are especially required to enable FIQ use on the Raspberry Pi 4. Furthermore the additional file *armstub7-rpi4.bin* (for 32-bit mode) or *armstub8-rpi4.bin* (for 64-bit mode) is required on the SD card then. Please see [boot/README](boot/README) for information on how to build these files.

Finally put the SD(HC) card into the Raspberry Pi.

Directories
-----------

* include: The common header files, most class headers are in the include/circle/ subdirectory.
* lib: The Circle class implementation and support files (other libraries are in subdirectories of lib/).
* sample: Several sample applications using Circle in different subdirectories. The main function is implemented in the CKernel class.
* addon: Contains contributed libraries and samples (has to be build manually).
* app: Place your own applications here. If you have own libraries put them into app/lib/.
* boot: Do *make* in this directory to get the Raspberry Pi firmware files required to boot.
* doc: Additional documentation files.
* test: Several test programs, which test different features of Circle.
* tools: Tools for building Circle and for using Circle more comfortable (e.g. a serial bootloader).

Classes
-------

The following C++ classes were added to Circle:

USB gadget library

* CUSBMSDGadget: USB mass storage device gadget
* CUSBMSDGadgetEndpoint: Endpoint of the USB mass storage gadget

Net library

* CmDNSPublisher: mDNS / Bonjour client task

The available Circle classes are listed in the file [doc/classes.txt](doc/classes.txt). If you have Doxygen installed on your computer you can build a [class documentation](doc/html/index.html) in doc/html/ using:

`./makedoc`

At the moment there are only a few classes described in detail for Doxygen.

Additional Topics
-----------------

* [Standard library support](doc/stdlib-support.txt)
* [Dynamic memory management and the "new" operator](doc/new-operator.txt)
* [DMA buffer requirements](doc/dma-buffer-requirements.txt)
* [Serial bootloader support](doc/bootloader.txt)
* [Multi-core support](doc/multicore.txt)
* [USB plug-and-play](doc/usb-plug-and-play.txt)
* [Debugging support](doc/debug.txt)
* [JTAG debugging](doc/debug-jtag.txt)
* [SWD debugging (Raspberry Pi 5)](doc/debug-swd.txt)
* [QEMU support](doc/qemu.txt)
* [Eclipse IDE support](doc/eclipse-support.txt)
* [About real-time applications](doc/realtime.txt)
* [cmdline.txt options](doc/cmdline.txt)
* [Screen escape sequences](doc/screen.txt)
* [Keyboard escape sequences](doc/keyboard.txt)
* [Clang support](doc/clang-support.txt)
* [Memory layout](doc/memorymap.txt)
* [Naming conventions](doc/naming-conventions.txt)
* [Known issues](doc/issues.txt)

Trademarks
----------

Raspberry Pi is a trademark of Raspberry Pi Ltd.

Linux is a trademark of Linus Torvalds.

PS3 and PS4 are registered trademarks of Sony Computer Entertainment Inc.

Windows, Xbox 360 and Xbox One are trademarks of the Microsoft group of companies.

Nintendo Switch is a trademark of Nintendo.

Khronos and OpenVG are trademarks of The Khronos Group Inc.

OpenGL ES is a trademark of Silicon Graphics Inc.

The micro:bit brand belongs to the Micro:bit Educational Foundation.

HDMI is a registered trademark of HDMI Licensing Administrator, Inc.
