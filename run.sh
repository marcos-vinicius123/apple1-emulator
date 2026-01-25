#!/usr/bin/env bash
set -e

EMU="$(dirname "$0")/out/build/GCC 15.2.1 x86_64-pc-linux-gnu/emulator"

if command -v kgx >/dev/null 2>&1; then
    kgx -- bash -c "\"$EMU\""
elif command -v gnome-terminal >/dev/null 2>&1; then
    gnome-terminal -- "$EMU"
elif command -v konsole >/dev/null 2>&1; then
    konsole -e "$EMU"
elif command -v xfce4-terminal >/dev/null 2>&1; then
    xfce4-terminal -e "$EMU"
elif command -v alacritty >/dev/null 2>&1; then
    alacritty -e "$EMU"
elif command -v kitty >/dev/null 2>&1; then
    kitty "$EMU"
elif command -v xterm >/dev/null 2>&1; then
    xterm -e "$EMU"
else
    echo "No supported terminal emulator found."
    exit 1
fi
