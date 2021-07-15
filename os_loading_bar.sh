#!/bin/bash

(
  echo 25
  echo "# Setting up os..."
  sleep 2

  echo 30
  echo "# Reading files from bootloader..."
  sleep 2

  echo 70
  echo "# Checking Resources"
  sleep 1

  echo 100
  echo "# FAST-OS LOADED SUCCESSFULLY!"
) | zenity --title "FAST-OS Loading...." --progress --auto-kill --width=400 --height=150
