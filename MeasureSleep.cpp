#include <iomanip>
#include <iostream>
#include <windows.h>

typedef NTSTATUS(CALLBACK *NTQUERYTIMERRESOLUTION)(
    OUT PULONG MinimumResolution,
    OUT PULONG MaximumResolution,
    OUT PULONG CurrentResolution);

int main() {
    ULONG MinimumResolution, MaximumResolution, CurrentResolution;
    LARGE_INTEGER start, end, freq;

    QueryPerformanceFrequency(&freq);

    HMODULE ntdll = LoadLibrary(L"ntdll.dll");

    if (!ntdll) {
        std::cerr << "LoadLibrary failed\n";
        return 1;
    }

    NTQUERYTIMERRESOLUTION NtQueryTimerResolution = (NTQUERYTIMERRESOLUTION)GetProcAddress(ntdll, "NtQueryTimerResolution");

    for (;;) {
        // get current resolution
        if (NtQueryTimerResolution(&MinimumResolution, &MaximumResolution, &CurrentResolution) != 0) {
            std::cerr << "NtQueryTimerResolution failed\n";
            return 1;
        }

        // benchmark Sleep(1)
        QueryPerformanceCounter(&start);
        Sleep(1);
        QueryPerformanceCounter(&end);

        double delta_s = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        double delta_ms = delta_s * 1000;

        std::cout << std::fixed << std::setprecision(6) << "Resolution: " << (CurrentResolution / 10000.0) << "ms, Sleep(1) slept " << delta_ms << "ms (delta: " << delta_ms - 1 << ")\n";

        Sleep(1000); // pause for a second between iterations
    }
}
