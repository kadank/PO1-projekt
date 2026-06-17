#!/bin/bash
cd build && cmake .. -DCMAKE_INSTALL_PREFIX=/usr && make install DESTDIR=../AppDir
NO_STRIP=1 linuxdeploy --appdir ../AppDir -e projekt -d ../bomberman.desktop -i ../icon.png -l /usr/lib/libSDL3.so
appimagetool AppDir ./bomberman.AppImage
