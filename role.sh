#!/bin/sh

g++ os.cpp -o os -lpthread
clear
figlet -c -t -k FAST-OS | boxes -d cat -a hc -p h8 | lolcat
sleep 3
clear
chmod 755 os_loading_bar.sh
./os_loading_bar.sh

read=`zenity --height=250 --list --title='Please Select A Role!' --column=Roles User Kernel`

if [ $read = "User" ]; then
 ./os user
fi

if [ $read = "Kernel" ]; then
 ./os kernel
fi