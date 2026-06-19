# Xenon

<p align="center">
  <img src=".assets/purpleauragif.gif" alt="Xenon Gas in Plasma state." width="350" height="300"/>
</p>

<div align="center">
	
[![Windows 11](https://img.shields.io/badge/Operating%20System-Windows%2011-2d87cc?)](https://en.wikipedia.org/wiki/Windows_11)
[![Windows 10](https://img.shields.io/badge/Operating%20System-Windows%2010-blue?logo=windows)](https://en.wikipedia.org/wiki/Windows_10)
[![Linux](https://img.shields.io/badge/Linux-OS-FCC624?logo=linux&logoColor=black)](https://en.wikipedia.org/wiki/Linux)

[![TCP](https://img.shields.io/badge/-TCP-red?)](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)
[![IPv4](https://img.shields.io/badge/IPv4-orange?)](https://en.wikipedia.org/wiki/Internet_Protocol_version_4)


[![README](https://img.shields.io/badge/README-ENG-FFD3AC?&labelColor=FFD3AC&style=flat-square)](README.md)
[![STATUS](https://img.shields.io/badge/STATUS-Working-green?&labelColor=2a3d5c&style=flat-square)](README.md)
	

</div>

	

---

# Xenon



**Xenon** is a lightweight, cross-platform, multi-protocol remote access tool written entirely in C. It is designed with a strong focus on minimal dependencies and simple code.

Unlike many similar tools that rely on basic socket communication, Xenon also implements manual map DLL injection (ONLY ON WINDOWS), enabling it to inject payloads directly into target processes without using standard Win api. 

Xenon has 3 main features [**multi-conn**, **spec-conn**, **random-conn**].

<br>
<br>

- **multi-conn**, Enables the user to control and command multiple nodes at once as well as listing available connections.
- **spec-conn**, Enables the user to accept a connection from a specific IP address and Port.
- **random-conn**, Is used to accept any random node that is connected to the user on a specific IP address and Port

<br>
<br>

The project is owned and written by **kenjirou2**
<br>
And edited by **koram**



---





# 📑 Table of Contents

- [📖 About](#-about)
- [⚡ Features](#-features)
- [🚧 Project Status](#-project-status)
- [💻 Compatibility](#-compatibility)
- [Code Navigation](#code-navigation)
- [🛠️ Building](#-building)
- [👤 Author](#-author)
- [⭐ Contributing](#-contributing)



---

# 📖 About

Xenon is designed as a **lightweight reverse shell framework** with a modular architecture.  
The goal is to keep the **core networking code extremely small**, while additional functionality such as the GUI and injector remain optional modules.

Key design goals:

- Lightweight
- Minimal dependencies
- Fast networking
- Expandable architecture
- Manual map injection support

---

# ⚡ Features

| Feature | Description |
|-------|-------------|
| TCP Socketing | Reverse shell communication over TCP |
| IPv4 Networking | Simple and widely supported networking |
| Manual Map Injection | Inject DLLs without using `LoadLibrary` |
| Lightweight | Minimal memory footprint |
| GUI (WIP) | Planned graphical interface |
| Self Injector | Built-in manual map injector |
| Stealth Focused | Designed to minimize detection |

---

# 🚧 Project Status

> ⚠️ This project is currently **under development**.

| Component | Status |
|-----------|--------|
| Reverse Shell | ✅ Working |
| TCP Communication | ✅ Implemented |
| Manual Map Injector | 🚧 In Progress |
| GUI Interface | 🚧 In Development |

The **core reverse shell has been fully tested** on:

- Windows 10
- Windows 11

---

# 💻 Compatibility

| OS | Supported |
|----|-----------|
| Windows 10 | ✅ |
| Windows 11 | ✅ |
| Linux | ❌ |
| macOS | ❌ |

---


# Code Navigation

Quick links to important parts of the project.

| Component | Description |
|-----------|-------------|
| `Xenon/cXenon/src/cxenon.c` | Client code |
| `Xenon/sXenon/src/Xenon.c` | Main code |
| `Xenon/Injector/injector.c` | Manual map DLL injector |
| `Include` | Generic Header files |
| `GUI` | GUI |



---

# Building

**Xenon.c (main)** :

```bash
cc -Wall -Wextra -Werror Xenon.c misc/menu.c misc/version.c ../Dependencies/Xenon/xenon.c ../Dependencies/XenonH/xenonhelper.c
../Dependencies/shell/shell.c ../../Include/protohttp/protohttp.c -o Xenon
-lws2_32 -lssl -lcrypto
```


**cXenon.c (payload)**	 :

```bash
cc cxenon.c -o xenoncli -lws2_32
```


**Or you can use makefile which can be found in sXenon/src & cXenon/src**



---


# 👤 Author



  **kenjirou2**



---

# ⭐ Contributing



Contributions, suggestions, and improvements are welcome.
Feel free to open issues or submit pull requests.


### REMINDER

> This project is free for you to use and modify as long as no copyright/plagirsm is taking place.
> **Thank You**
