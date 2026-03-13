# Xenon

![Repo Banner](https://img.shields.io/badge/Xenon-Reverse%20Shell-black?style=for-the-badge)

[![Windows 11](https://img.shields.io/badge/Windows-11-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://www.microsoft.com/en-us/windows/get-windows-11)
[![Windows 10](https://img.shields.io/badge/Windows-10-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://www.microsoft.com/en-us/software-download/windows10)

[![TCP](https://img.shields.io/badge/Protocol-TCP-blue?style=for-the-badge)](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)
[![IPv4](https://img.shields.io/badge/Network-IPv4-orange?style=for-the-badge)](https://en.wikipedia.org/wiki/Internet_Protocol_version_4)

---

# 📌 Xenon

**Xenon** is a lightweight **TCP IPv4 reverse shell written entirely in C**.  
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

# 📂 Project Structure

Example layout (adjust to your repo if needed):

Xenon/
│
├─ [src](./src/)
│  ├─ [client](./src/client/)
│  ├─ [server](./src/server/)
│  ├─ [injector](./src/injector/)
│
├─ [include](./include/)
│
├─ [gui](./gui/)
│
└─ [README.md](./README.md)

---

# 🔎 Code Navigation

Quick links to important parts of the project.

| Component | Description |
|-----------|-------------|
| `src/client` | Reverse shell client implementation |
| `src/server` | Command & control server |
| `src/injector` | Manual map DLL injector |
| `include` | Header files |
| `gui` | Upcoming graphical interface |

Example links (edit if needed):

```
/src/client/main.c
/src/server/server.c
/src/injector/manual_map.c
```

---

# 🛠️ Building

Example build command using **GCC / MinGW**:

```bash
gcc client.c -o xenon_client -lws2_32
```

Example using **MSVC**:

```bash
cl client.c ws2_32.lib
```

---


# 👤 Author

**kenjirou2**

---

# ⭐ Contributing

Contributions, suggestions, and improvements are welcome.
Feel free to open issues or submit pull requests.