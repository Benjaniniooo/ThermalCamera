#!/bin/sh

#Foreground Colors
FBlack="$(tput setaf 0)"
FRed="$(tput setaf 1)"
FGreen="$(tput setaf 2)"
FYellow="$(tput setaf 3)"
FBlue="$(tput setaf 4)"
FMagenta="$(tput setaf 5)"
FCyan="$(tput setaf 6)"
FWhite="$(tput setaf 7)"

#Background Colors
BBlack="$(tput setab 0)"
BRed="$(tput setab 1)"
BGreen="$(tput setab 2)"
BYellow="$(tput setab 3)"
BBlue="$(tput setab 4)"
BMagenta="$(tput setab 5)"
BCyan="$(tput setab 6)"
BWhite="$(tput setab 7)"

#text modes
TBold="$(tput bold)"
TDim="$(tput dim)"

#tput commands
TClear="$(tput sgr0)"

NL="\n"

##################################

clear

printf "${FYellow}${BYellow} Compiling... ${TClear} ${NL}${NL}"

if \
    g++ \
    \
    -std=c++2b -Wall -Ofast \
    \
    \
    -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system \
    \
    -I ./include/ \
    ./include/*.cpp \
    \
    main.cpp \
    \
    -o main.o
then
    printf "${NL}"
    printf "${FGreen}${BGreen} Compiling successful! ${TClear} ${NL}${NL}"
    printf "${BBlue}${FCyan} Starting program... ${TClear} ${NL}${NL}"

    if \
        ./main.o
    then
        printf "${NL}"
        printf "${FGreen}${BGreen} Program executed successfully! ${TClear} ${NL}${NL}"
    else
        printf "${NL}"
        printf "${FRed}${BRed} Program crashed! ${TClear} ${NL}${NL}"
    fi
else
    printf "${NL}"
    printf "${FRed}${BRed} Compiling failed! ${TClear} ${NL}${NL}"
fi