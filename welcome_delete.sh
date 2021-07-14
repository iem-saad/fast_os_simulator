#!/bin/bash


display_landing_page() {
	clear
	green_fg
	bold
	tput cup 6; 
	figlet -c 'Delete A File';
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

display_landing_page;
