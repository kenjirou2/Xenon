# Xenon




<p align="center">
  <img src=".assets/purpleauragif.gif" height="300" width="300" alt="Plasma formed from Xenon gas">
</p>


[![Xenon](https://img.shields.io/badge/enon%20Remote%20Access%20Tool-2C3E50?logo=xstate&logoColor=black&labelcolor=#2a3d5c)](https://github.com/kenjirou2/Xenon)


[![Git Bash](https://img.shields.io/badge/GitBash-2.44-80B3FF?logo=git)](https://gitforwindows.org/)


[![Windows 11](https://img.shields.io/badge/Operating%20System-Windows%2011-2d87cc?)](https://en.wikipedia.org/wiki/Windows_11)
[![Windows 10](https://img.shields.io/badge/Operating%20System-Windows%2010-blue?logo=windows)](https://en.wikipedia.org/wiki/Windows_10)

[![TCP](https://img.shields.io/badge/-TCP-red?)](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)
[![IPv4](https://img.shields.io/badge/IPv4-orange?)](https://en.wikipedia.org/wiki/Internet_Protocol_version_4)


[![README](https://img.shields.io/badge/README-ENG-FFD3AC?&labelColor=FFD3AC&style=flat-square)](README.md)
[![STATUS](https://img.shields.io/badge/STATUS-Working-green?&labelColor=2a3d5c&style=flat-square)](README.md)




	

---

# 📌 Xenon



**Xenon** is a lightweight multi-protocol reverse shell written entirely in C.
The project focuses on **performance, minimal dependencies, and stealth**.

Unlike many similar projects that rely solely on simple socket communication, Xenon also implements **manual map DLL injection**, allowing it to inject its own DLL directly into a target process.

The entire project is written and maintained by **`kenjirou2`**.

---





# 📑 Table of Contents

- [About](#about)
- [Features](#features)
- [Project Status](#project-status)
- [Compatibility](#compatibility)
- [Project Structure](#project-structure)
- [Code Navigation](#code-navigation)
- [Building](#building)
- [Disclaimer](#disclaimer)

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

#🛠️ Building

**Xenon.c (main)** :

```bash
cc -Wall -Wextra -Werror Xenon.c misc/menu.c misc/version.c ../Dependencies/Xenon/xenon.c ../Dependencies/XenonH/xenonhelper.c
../Dependencies/shell/shell.c ../../Include/protohttp/protohttp.c -o Xenon -lws2_32 -lssl -lcrypto
```


**cXenon.c (payload)**	 :

```bash
cc cxenon.c -o xenoncli -lws2_32
```

---


# 👤 Author



  **kenjirou2**



---

# ⭐ Contributing



Contributions, suggestions, and improvements are welcome.
Feel free to open issues or submit pull requests.


### # ⚠️ REMINDER

This project is free for you to use and modify but my only favor is for you to give credits to me when using or buiolding upon this project.


  **Thank you.**
