#!/bin/bash
gcc webkitgtk_TwenteSDR.c -o webkitgtk_TwenteSDR `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0 --libs gtk+-3.0 webkit2gtk-4.0`
