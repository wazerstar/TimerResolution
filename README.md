# TimerResolution

Raise the clock interrupt frequency in Windows

See [Fixing timing precision in Windows after "The Great Rule Change"](https://github.com/amitxv/PC-Tuning/blob/main/docs/research.md#fixing-timing-precision-in-windows-after-the-great-rule-change) for a detailed explanation regarding the techniques used to restore the old timer resolution implementation otherwise nothing below will make sense.

``MeasureSleep`` is used to measure the precision of Sleep(1). The closer it sleeps to 1ms in reality, the better.

``SetTimerResolution`` is used to request a higher resolution. To automatically start a hidden instance of the program when the system starts and raise the resolution to 0.5ms, place the binary somewhere safe and create a shortcut in ``shell:startup`` with the following target:

```
C:\SetTimerResolution.exe --resolution 5000 --no-console
```

On Windows Server 21H2+ and Windows 11+, the registry key below should also be used so that requesting a higher resolution is effective on a system-wide level rather than only the calling process.

```
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\kernel]
"GlobalTimerResolutionRequests"=dword:00000001
```
