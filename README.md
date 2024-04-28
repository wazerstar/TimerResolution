# TimerResolution

[![Downloads](https://img.shields.io/github/downloads/amitxv/TimerResolution/total.svg)](https://github.com/amitxv/TimerResolution/releases) [![Buy Me a Coffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-Donate-orange?logo=buy-me-a-coffee)](https://www.buymeacoffee.com/amitxv)

``MeasureSleep`` is used to measure the precision of Sleep(1). By default, it sits in an infinite loop measuring the sleep deltas, but you can use the ``--samples`` argument to get average and STDEV metrics.

``SetTimerResolution`` is used to request a higher resolution by calling [NtSetTimerResolution](http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FTime%2FNtSetTimerResolution.html). As an example to automatically start a hidden instance of the program when the system starts and raise the resolution to 0.5ms, place the binary somewhere safe and create a shortcut in ``shell:startup`` with the target below.

```
C:\SetTimerResolution.exe --resolution 5000 --no-console
```

Thanks to a comment on the [Great Rule Change](https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change) article, on Windows Server 2022+ and Windows 11+, the registry key below can also be used so that requesting a higher resolution is effective on a system-wide level rather than only the calling process.

```
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\kernel]
"GlobalTimerResolutionRequests"=dword:00000001
```

## Lower Resolution yet Higher Precision?

The [micro-adjust-benchmark.ps1](/micro-adjust-benchmark.ps1) script can be used to automate the process of plotting precision against resolutions.

Visualize the results with [chart-studio.plotly.com](https://chart-studio.plotly.com/create).

<img src="/assets/img/results-example.png" width="1000">

## Building

```powershell
git clone https://github.com/amitxv/TimerResolution.git
cd .\TimerResolution\
# x64
$env:VCPKG_DEFAULT_TRIPLET = "x64-windows"
# install dependencies
vcpkg install
# replace "SetTimerResolution" with "MeasureSleep" if desired
MSBuild.exe .\TimerResolution.sln -p:Configuration=Release -p:Platform=x64 -t:SetTimerResolution```
