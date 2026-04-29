# codeCommand

A custom command-line shell for Windows, built from scratch in C++. Instead of relying on a monolithic executable, codeCommand uses a **plugin architecture** — each command is a standalone DLL loaded at runtime. New commands can be added without recompiling the shell.

> **Note:** I built this CMD out of curiosity about how a CLI adds new commands without recompiling.

---

## Features

* **Plugin-Based Commands** — Each command (like `Process`, `Pause`, `Resume`) is implemented as a DLL and loaded at runtime, instead of loading the entire executable.
* **Dual Mode Shell** — Switch between **Custom mode** (DLL plugin commands) and **Normal mode** (Windows shell) with a single command.
* **JSON-Driven Configuration** — A central `CommandJsonFile.json` maps command names to their configuration, including DLL path, argument count, and parsing type.

---

## Tech Stack

| Layer    | Technology                                  |
| -------- | ------------------------------------------- |
| Language | C++17                                       |
| Platform | Windows                                     |
| JSON     | JsonCpp (`libjsoncpp`)                      |
| Compiler | GCC (`g++`) or Clang (`clang++`) with MinGW |

---

## Commands

### Dynamic Commands

| Command     | Usage                   | Description                                   |
| ----------- | ----------------------- | --------------------------------------------- |
| `Process`   | `Process`               | List all running processes                    |
| `Pause`     | `Pause <process_name>`  | Suspend a running process                     |
| `Resume`    | `Resume <process_name>` | Resume a suspended process                    |
| `Directory` | `Directory <path>`      | Change the current working directory          |
| `Encrypt`   | `Encrypt <path>`        | Encrypt a file or directory                   |
| `Encrypt`   | `Encrypt -d <path>`     | Decrypt a file or directory                   |
| `Remove`    | `Remove <path>`         | Recursively delete a file or directory        |
| `Clear`     | `Clear`                 | Clear the console screen                      |
| `Color`     | `Color <code>`          | Change console text color (for example, `0A`) |
| `Print`     | `Print <message>`       | Print text to the console                     |

### Static Commands (Built-in)

| Command          | Description                                  |
| ---------------- | -------------------------------------------- |
| `update_It`      | Hot-reload commands from JSON or a directory |
| `normal_Cmd`     | Switch to normal mode                        |
| `custom_Cmd`     | Switch to custom mode                        |
| `change_Command` | Alias a command: `change_Command Old New`    |
| `Quit`           | Exit the shell                               |
| `Restart`        | Restart the shell                            |

---

## Build

**Platform:** Windows only (requires Win32 API)

### Prerequisites

* GCC (MinGW) or Clang with MinGW
* JsonCpp (`libjsoncpp`)

### Compile the Shell

```bash
# GCC
g++ main.cpp -o main -ljsoncpp

# Clang
clang++ main.cpp -o main -ljsoncpp
```

### Compile a New Command DLL

```bash
# GCC
g++ -shared CommandFile.cpp -o dllfile/CommandName.dll

# Clang
clang++ -shared CommandFile.cpp -o dllfile/CommandName.dll
```

### Register Command

```json
{
  "CommandName": {
    "DllFilePath": "<DLL file path>",
    "MinElement": "<minimum number of arguments>",
    "Type": "<0 = split by whitespace, 1 = full string>"
  }
}
```

---

## How It Works

```text
main.cpp → REPL loop → CommandHandler()

          ├── Static command → execute directly
          └── Dynamic command → load DLL → call CommandMain → unload DLL
```
