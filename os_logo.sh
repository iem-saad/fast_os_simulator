#!/bin/bash


#######################################
# Functions Using tput for BOLD, BLINK
# RESET, GREEN, WHITE & Yellow Colors
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################

bold() {
	tput bold;
}
blink() {
	tput blink;
}
reset_format() {
	tput sgr0;
}
green_fg() {
	tput setaf 2;
}
cyan_fg() {
	tput setaf 6;
}
white_fg() {
	tput setaf 7;
}
yellow_fg() {
	tput setaf 3;
}
red_fg() {
	tput setaf 1;
}

display_landing_page() {
	clear
	cyan_fg
	bold
	tput cup 6; 
	figlet -c 'FAST - OS';
	reset_format
	tput cup 12 10; 
	green_fg
	for (( i = 0; i < 55; i++ )); do
		sleep 0.05
		echo -n -e '*'
	done
	tput cup 15 15;
	blink
	echo  "++++++++++ SYSTEM IS SOFT BOOTING ++++++++++"
	# read -p "++++++++++ SYSTEM IS SOFT BOOTING ++++++++++"  value 
	sleep 4
	reset_format
	white_fg
	clear
}

display_landing_page
