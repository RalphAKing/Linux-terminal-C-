# Linux Terminal Emulator in C++

A lightweight terminal emulator built in C++ that mimics basic Linux terminal functionality. This project provides a simple command-line interface with support for common shell commands.

## Features

- **Command Execution**: Execute basic terminal commands
- **Directory Navigation**: Change directories with `cd` and view current path with `pwd`
- **File Management**: List files with `ls`, create directories with `mkdir`, and remove files with `rm`
- **Color-Coded Output**: Files and directories are displayed with intuitive color coding:
  - Directories: Blue
  - Executable files: Green
  - Image files: Magenta
  - Archive files: Red
  - Symbolic links: Cyan

## Supported Commands

- `cd <path>` - Change directory
- `pwd` - Print working directory
- `ls` - List files in the current directory
- `mkdir <name>` - Create a new directory
- `rm <name>` - Remove a file
- `clear` - Clear the terminal screen
- `echo <text>` - Print text to the terminal
- `help` - Display available commands
- `exit` - Exit the terminal

## Building the Project

### Prerequisites
- C++17 compatible compiler
- Standard C++ libraries

### Compilation
```bash
g++ -std=c++17 terminal.cpp -o terminal
```

### Running
```bash
./terminal
```

## Implementation Details

The terminal emulator uses the C++ filesystem library to interact with the file system and provides a simple command parsing mechanism. It implements color coding for different file types to enhance usability.

## Platform Support

The terminal is primarily designed for Linux systems but includes conditional compilation for Windows compatibility.

## Contributing

Feel free to fork this project and submit pull requests for additional features or bug fixes.

## License

This project is open-source and available for modification and use under the MIT license.

### MIT License

```
MIT License

Copyright (c) 2025 Ralph King

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
