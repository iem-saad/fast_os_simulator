#!/bin/bash

# Author: Saad Abdullah, Mahnoor Abid, Sardar Raheem
# Shell Script for Sudoku Game Play
# Script follows here:

source welcome.sh
source menu.sh

#######################################
##### GLOBAL VARIABLES & ARRAYS #######
#######################################
declare -A main_solution
declare -A user_solution
declare -A soa_solution #Parallel Array to Map Random solution
mode='moderate'
num_rows=0
num_columns=0
upper_bound=9
hints_for_user=35
#######################################

#######################################
# Prints You Won Text on Console
# GLOBALS:
#   Doesn't Use Any
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   You Wont! String on Console
# RETURN:
#   Nothing
#######################################
won_game(){
  bold
  display_board
  echo
  echo
  echo
  figlet -c 'You Won! :)';
  exit
}

#######################################
# Prints You Lost Text on Console
# GLOBALS:
#   Doesn't Use Any
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   You Lost :( String on Console
# RETURN:
#   Nothing
#######################################
lost_game(){
  bold
  display_board
  echo
  echo
  echo
  figlet -c 'You Lost :(';
  exit
}
#######################################
# Checks Winning or loosing condition
# GLOBALS:
#   user_solution & main solution
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Calls won_game & lost_game accordingly
# RETURN:
#   Nothing
#######################################
win_lost_checker() {
  controller=1
  for ((i=1;i<=num_rows;i++)) do
    for ((j=1;j<=num_columns;j++)) do
      if ((${user_solution[$j,$i]} != ${main_solution[$j,$i]} )); then
        controller=0
      fi
    done
  done
  #### IF user given solution is equal to orignal solution then
  #### Counter will contain 1 else it will contain a 0
  if (($controller==0)); then
    lost_game
  else
    won_game
  fi
}

#######################################
# Main Logic of game play lies here
# Starts game by asking user for moves
# GLOBALS:
#   user_solution , main solution
#   soa solution, upper_bound, num_rows
#   num_cols
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Performs Gameplay and then calls 
#   win_lost_checker when board is filled
# RETURN:
#   Nothing
#######################################

start_game() {

  local x_pos=0
  local y_pos=0
  local value=0
  local controller=0
  local lower_bound=1
  while (($controller==0)); do    
    display_board
    echo "***********************************************"
    echo "*       PLEASE SELECT A VALID OPTION!         *"
    echo "***********************************************"
    read -p "*     Enter X Position: "  x_pos
    read -p "*     Enter Y Position: "  y_pos
    # Checks to stop user entering invalid inputs
    if ((($x_pos < $lower_bound || $x_pos > $upper_bound  || $y_pos < $lower_bound || $y_pos > $upper_bound ))); then
      clear
      echo "++++++++ Invalid Move Please Try Again ++++++++"
      continue
    fi
    if ((${soa_solution[$y_pos,$x_pos]} == $lower_bound )); then
      clear
      echo "++++++++ Invalid Move Please Try Again ++++++++"
      continue
    fi
    read -p "*     Enter Value: "  value
    if (( $value > $upper_bound )); then
      clear
      echo "++++++++ Invalid Move Please Try Again ++++++++"
      continue
    fi
    clear
    if ((${main_solution[$y_pos,$x_pos]} !=  $value )); then
      echo "Wops! You've Made A Wrong Move"
    else
      echo "Good! You've Made A Valid Move"
    fi
    # Add value only if it is valid and in range
    user_solution[$y_pos,$x_pos]=$value
    # adding 2 to know that this value is entered by user.
    soa_solution[$y_pos,$x_pos]=2
    controller=1
    for ((i=1;i<=num_rows;i++)) do
      for ((j=1;j<=num_columns;j++)) do
        if [ -z "${user_solution[$i,$j]// }" ]; then
          controller=0
        fi
      done
    done
  done
  # controller will have 0 value if game is not solved properly
  # controller will have 1 value if game is solved properly
  win_lost_checker
}

#######################################
# Initializez Board For user having 3 entries
# in easy mode & 35 in moderate mode
# GLOBALS:
#   user_solution , main solution
#   soa solution, upper_bound
#   hints_for_user
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
_init_user_solution() {

  local rand1
  local rand2
  # this loops places, 35 values in case of moderate
  # & 3 values in case of easy mode from unique solution
  # created everytime program runs into a 2D array in 
  # which user will fill values (All locations)
  # will be generated randomly and unique each time.
  for (( i = 0; i < $hints_for_user; i++ )); do
    rand1=$(( ( RANDOM % $upper_bound ) + 1))
    rand2=$(( ( RANDOM % $upper_bound ) + 1))
    while ((${soa_solution[$rand1,$rand2]}==1)); do
      rand1=$(( ( RANDOM % $upper_bound ) + 1))
      rand2=$(( ( RANDOM % $upper_bound ) + 1))
    done
    soa_solution[$rand1,$rand2]=1
    user_solution[$rand1,$rand2]=${main_solution[$rand1,$rand2]}
  done


}

#######################################
# Makes Prepares Unique Board Each Time
# Program Runs 362880 solutions for moderate
# and 6 solutions for easy mode
# GLOBALS:
#   user_solution , main solution
#   soa solution, upper_bound
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
make_solution_unique() {

  local rand1=0
  local rand2=0
  # this loop will create 2 unique & distinct
  # random numbers
  while (($rand1 == $rand2)); do
    rand1=$(( ( RANDOM % $upper_bound ) + 1))
    rand2=$(( ( RANDOM % $upper_bound ) + 1))
  done
  # This loop will make solution unique each time
  # from the solutoin which we provided in the
  # _init_board function by exchanging rand1 & rand2
  # with each other in a specific way.
  for ((i=1;i<=num_rows;i++)) do
    for ((j=1;j<=num_columns;j++)) do
      if ((((${main_solution[$i,$j]}==$rand1)) && ((${soa_solution[$i,$j]}==0)))); then
        main_solution[$i,$j]=$rand2
        soa_solution[$i,$j]=1
      elif ((${main_solution[$i,$j]} == $rand2 && ${soa_solution[$i,$j]}==0)); then
        main_solution[$i,$j]=$rand1
        soa_solution[$i,$j]=1
      fi
    done
  done
  # cleaning soa_solution, so that it can 
  # be used in future.
  for ((i=1;i<=num_rows;i++)) do
    for ((j=1;j<=num_columns;j++)) do
      soa_solution[$i,$j]=0
    done
  done
}

#######################################
# Loads Predefine Solution on basis of game 
# mode, this predefine solution then prepares
# more unique solutions
# GLOBALS:
#   num_rows , main solution
#   soa solution, nun_columnss
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################

_init_board() {

  #one solution if user selects moderate mode
  local temp_sol_moderate=(9 5 7 6 1 3 2 8 4 4 8 3 2 5 7 1 9 6 6 1 2 8 4 9 5 3 7 1 7 8 3 6 4 9 5 2 5 2 4 9 7 1 3 6
               8 3 6 9 5 2 8 7 4 1 8 4 5 7 9 2 6 1 3 2 9 1 4 3 6 8 7 5 7 3 6 1 8 5 4 2 9)
  #one solution if user selects easy mode
  local temp_sol_easy=(2 1 3 1 3 2 3 2 1)
  # Treatning array as a hash that's why starting counters from 1
  for ((i=1, k=0;i<=num_rows;i++)) do
    for ((j=1;j<=num_columns;j++)) do
        # prepare solution for user on base of selected game mode
        if [[ $mode == 'easy' ]]; then
          main_solution[$j,$i]=${temp_sol_easy[$k]}
        else
          main_solution[$j,$i]=${temp_sol_moderate[$k]}
        fi
        # initializing with 0 to make it clean
        soa_solution[$j,$i]=0
        ((k++))
    done
  done
}

#######################################
# Displays Sudoku Board on Consolse
# GLOBALS:
#   num_rows , main solution
#   soa solution, nun_columnss
#   name
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Displays Board On Console
# RETURN:
#   Nothing
#######################################
display_board() {

  echo

  yellow_fg
  echo "************************************************"
  echo "Hi, $name! Have a Good Day"
  echo "************************************************"
  echo "***      Red Color Represent Wrong Move      ***"
  echo "***     While Green Represent Valid Move     ***"
  echo "***     Horizontal is X, Vertical is Y       ***"
  echo "************************************************"
  white_fg
  echo
  echo
  # used sequece to print responsive tabs using printf command
  f1="%$((${#num_rows}+1))s"
  f2=" %9s"

  printf "$f1" ''
  for ((i=1;i<=num_rows;i++)) do
    printf "$f2" $i
  done
  echo
  echo
  for ((j=1;j<=num_columns;j++)) do
    printf "$f1" $j
    for ((i=1;i<=num_rows;i++)) do
      # if index is empty place a yello '-' there.
      if [ -z "${user_solution[$i,$j]// }" ]; then
        yellow_fg
        printf "$f2" '-'
        white_fg
      # soa[] 2 indicates move is done by user, and if 
      # it matches with solution prints it in green
      # else represents it with red color
      elif ((${soa_solution[$i,$j]}==2)); then
        if ((${user_solution[$i,$j]} == ${main_solution[$i,$j]})); then
          bold
          green_fg
          printf "$f2" ${user_solution[$i,$j]}
          reset_format
        else
          bold
          red_fg
          printf "$f2" ${user_solution[$i,$j]}
          reset_format
        fi
      else
        printf "$f2" ${user_solution[$i,$j]}
      fi
    done
    echo
  done
  echo
  echo
  echo
}


#######################################
# Sets required Golbal Variables According
# to easy mode
# GLOBALS:
#   num_rows
#   nun_columns
#   mode, upper_bound
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################

Easy()
{
  num_rows=3
  num_columns=3
  upper_bound=3
  hints_for_user=3
  mode='easy'
  _init_board
  make_solution_unique
  _init_user_solution
  start_game
}

#######################################
# Sets required Golbal Variables According
# to Moderate mode
# GLOBALS:
#   num_rows
#   nun_columns
#   mode, upper_bound
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
Moderate()
{
  num_rows=9
  num_columns=9
  upper_bound=9
  mode='moderate'
  _init_board
  make_solution_unique
  _init_user_solution
  start_game
}

#######################################
# Checks if figlet is installed for formating
# if not installed, then installs it
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################
install_dependency() {
  # if package figlet is not installed
  # then if will be executed
  dpkg -s figlet &> /dev/null
  if [ $? -ne 0 ]; then
    sudo apt-get install -y figlet
  fi
}
install_dependency
display_landing_page
get_name
Menu
