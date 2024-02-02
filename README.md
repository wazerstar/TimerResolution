# TimerResolution

## [Downloads](https://github.com/amitxv/TimerResolution/releases)

[![Buy Me A Coffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/amitxv)

See [Fixing timing precision in Windows after "The Great Rule Change"](https://github.com/amitxv/PC-Tuning/blob/main/docs/research.md#fixing-timing-precision-in-windows-after-the-great-rule-change) for a detailed explanation regarding the techniques used to restore the old timer resolution implementation otherwise nothing below will make sense.

``MeasureSleep`` is used to measure the precision of Sleep(1). The closer it sleeps to 1ms in reality, the better. By default, it sits in an infinite loop measuring the sleep deltas, but you can use the ``--samples`` argument to get average, STDEV metrics.

``SetTimerResolution`` is used to request a higher resolution. To automatically start a hidden instance of the program when the system starts and raise the resolution to 0.5ms, place the binary somewhere safe and create a shortcut in ``shell:startup`` with the target below.

```
C:\SetTimerResolution.exe --resolution 5000 --no-console
```

Thanks to a comment on the [Great Rule Change](https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/) article, on Windows Server 2022+ and Windows 11+, the registry key below can also be used so that requesting a higher resolution is effective on a system-wide level rather than only the calling process.

```
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\kernel]
"GlobalTimerResolutionRequests"=dword:00000001
```

## Lower Resolution yet Higher Precision?

Expand [Micro-adjusting timer resolution for higher precision](https://github.com/amitxv/PC-Tuning/blob/main/docs/research.md#micro-adjusting-timer-resolution-for-higher-precision) for a detailed explanation. The [micro-adjust-benchmark.ps1](/micro-adjust-benchmark.ps1) script can be used to automate the process.

Visualize the results with [chart-studio.plotly.com](https://chart-studio.plotly.com/create).

<img src="./img/results-example.png" width="1000">

## Building

```powershell
git clone https://github.com/amitxv/TimerResolution.git
cd .\TimerResolution\
# x64
$env:VCPKG_DEFAULT_TRIPLET = "x64-windows"
# install dependencies
vcpkg install
# replace "SetTimerResolution" with "MeasureSleep" if desired
MSBuild .\SetTimerResolution\SetTimerResolution.sln -p:Configuration=Release
```
