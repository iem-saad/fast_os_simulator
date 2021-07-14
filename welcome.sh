#!/bin/bash
name='Saad Abdullah'
#######################################
# Displays Big Sudoku Game Using figlet
# Then displays a loading bar
# GLOBALS:
#   nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
display_landing_page() {
	clear
	green_fg
	bold
	tput cup 6; 
	figlet -c 'Sudoku Game';
	reset_format
	tput cup 12 10; 
	green_fg
	for (( i = 0; i < 55; i++ )); do
		sleep 0.05
		echo -n -e '*'
	done
	tput cup 15 15;
	blink
	read -p "++++++++++ Press Any Key To Continue ++++++++++"  value 
	reset_format
	white_fg
	clear
}

#######################################
# Gets Input From user his/her name
# in Formated Manner & Calls 
# Other FuntionsAccordingly
# GLOBALS:
#   name
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Sets Value in name
#######################################

get_name() {
	clear
	green_fg
	bold
	# Command to change x & y axsis of cursor on console
	tput cup 6; 
	figlet -c 'Player Name';
	reset_format
	tput cup 14 15;
	yellow_fg
	bold
	read -p "Please Enter Your Name: "  name 
	reset_format
	white_fg
	clear
}

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
white_fg() {
	tput setaf 7;
}
yellow_fg() {
	tput setaf 3;
}
red_fg() {
	tput setaf 1;
}

