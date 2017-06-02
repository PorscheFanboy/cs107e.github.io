---
released: true
layout: page
title: "Performance"
---

Speed is Dawson's lecture, but it has a lot of weird build stuff, so
redoing with standard build chain.

## stackprof

Install `cpuprofilify` from npm -- converts Linux `perf script` output
(which `stackprof` mimics) to Chrome `.cpuprofile` format for
flame-chart visualization. Then open in Chrome JS profiler :D

```
$ rpi-install.py -r -p -q main.bin > profile.txt
$ cat profile.txt | tr -d "\r" | cpuprofilify --type perf > out.cpuprofile
```

## clear

print out: clear/clear.c

