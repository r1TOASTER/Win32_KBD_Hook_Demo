# Keylogger Hook

This is a simple keylogger program using a Windows hook to intercept keyboard events and log them to a file. It runs in the background, capturing key presses and saving them along with the timestamp.

## Features

- Captures key presses and logs them to a file.
- Logs special keys (e.g., backspace, tab, enter) and regular alphanumeric characters.
- Writes the timestamp (hour:minute:second) for each key press.

## Prerequisites

To compile and run this program, you need:

- Windows operating system
- Visual Studio or any C++ compiler that supports the Windows API

## Compilation

1. Open the source file `main.cpp` in your preferred C++ IDE or text editor.
2. Create a new project or compile the source file directly.
3. Make sure to link against the Windows library by adding `user32.lib` to your project settings or compiler command.

## Usage

1. After compiling the program, you will get an executable file (`main.exe`).
2. Run the executable to start the keylogger.
3. The keylogger will run silently in the background, capturing key presses and logging them to a file.
4. The logged keys and their corresponding timestamps will be saved in the specified log file.
5. To stop the keylogger, wait for the specified duration (e.g., 5 minutes) or terminate the program manually.

## Customization

- Log File: Modify the line `log_file.open(R"(your-path-goes-here)", std::ofstream::out);` to specify the desired log file path.
- Time Duration: Adjust the line `while (end - start < (60 * 5))` to change the duration (in minutes) for which the keylogger will run.

## Important Note

**Please note that the use of keyloggers without proper authorization is illegal and unethical. This code is provided for educational purposes only. Ensure that you comply with all applicable laws and obtain proper consent before using any keylogging software.**

## License

This code is licensed under the [MIT License](LICENSE).

