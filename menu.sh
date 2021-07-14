#!/bin/bash

source welcome.sh

#######################################
# Asks User for Game Mode and calls Easy
# Moderate Accordingly
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
game_mode()
{
  echo "***********************************************"
  echo "*       PLEASE SELECT A VALID OPTION!         *"
  echo "***********************************************"
  echo "*     Press 1 to Select Easy Mode             *"
  echo "*     Press 2 to Select Moderate Mode         *"
  echo "*     Press 3 to go back to Main Menu         *"
  read -p "*     Enter Here: " option
  echo "***********************************************"
  if [ $option == 1 ]
  then 
    Easy
  elif [ $option == 2 ]
  then
    Moderate
  elif [ $option == 3 ]
  then
    clear
    Menu
  else
    echo "++++++++++++++ Invalid option! ++++++++++++++"
    game_mode
  fi
}
#######################################
# Displays Instructions on Console in
# Formated Manner Calls 
# Other FuntionsAccordingly
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
Instruction()
{
  clear
  bold
  # figlet bundle to show formatted large text
  figlet -c 'Instructions';
  # Cup command to change x & y axsis of cursor on console
  tput cup 7 5;
  echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
  tput cup 8 5;
  echo "+ Sudoku is played on a grid of 9 x 9 spaces. Within the rows and   +"
  tput cup 9 5;
  echo "+ columns are 9 “squares” (made up of 3 x 3 spaces). Each row,      +"  
  tput cup 10 5;
  echo "+ column and square (9 spaces each) needs to be filled out with the +"  
  tput cup 11 5;
  echo "+ numbers 1-9, without repeating any numbers within the row, column +"  
  tput cup 12 5;
  echo "+            or square. Does it sound complicated?                  +"  
  tput cup 13 5;
  echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
  tput cup 15 10;
  blink
  read -p "++++++++++ Press Any Key To Get Back to Menu ++++++++++"  value 
  reset_format
  clear

}
#######################################
# Displays Credits on Console in
# Formated Manner Formated Manner & Calls 
# Other FuntionsAccordingly
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
Credits()
{
  clear
  bold
  figlet -c 'Credits';
  tput cup 10 10;
  echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
  tput cup 11 10;
  echo "++++++ This game was created by Mahnoor Abid, Bilal Haider +++++++"
  tput cup 12 10;
  echo "++++++            Saad Abdullah on 16/05/2021               +++++++"
  tput cup 13 10;
  echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
  tput cup 15 15;
  blink
  read -p "++++++++++ Press Any Key To Get Back to Menu ++++++++++"  value 
  reset_format
  clear
}
#######################################
# Displays Menu on Console in
# Formated Manner & Calls Other Funtions
# Accordingly
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
Menu()
{
  let option=10
  while [ $option -ne 4 ]
  do
    echo "***********************************************"
    echo "*       PLEASE SELECT A VALID OPTION!         *"
    echo "***********************************************"
    echo "*     Press 1 to start the game.              *"
    echo "*     Press 2 to view instructions.           *"
    echo "*     Press 3 to view credits.                *"
    echo "*     Press 4 to exit.                        *"
    read -p "*     Enter Here: " option
    echo "***********************************************"
    if [ $option -eq 1 ]
    then 
      clear
      game_mode
    elif [ $option -eq 2 ]
    then
      Instruction
    elif [ $option -eq 3 ]
    then 
      Credits
    elif [ $option -eq 4 ]
    then
      g++ dealloc_resource.cpp -o dealloc_resource
      ./dealloc_resource SUDOKU
      # system("./dealloc_resource SUDUKO")
      
      exit
    else
      clear
      echo "++++++++++++++ Invalid option! ++++++++++++++"
    fi
  done
}
