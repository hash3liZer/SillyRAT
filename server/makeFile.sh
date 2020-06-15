#!/bin/bash

clear

echo
echo
echo "[+] Welcome to makefile for SillyRAT by @hash3lizer && @TheFlash2k"

sleep 1
echo; echo; echo "[+] Creating Linker File for Colors"
`g++ -c colors.cpp -o colors.o`
sleep 1
echo "[x] DONE!"
sleep 1
echo; echo; echo "[+] Creating Linker File for Inputs"
`g++ -c inputs.cpp -o inputs.o`
sleep 1
echo "[x] DONE!"
sleep 1
echo; echo; echo "[+] Creating Linker File for Interface"

`g++ -c interface.cpp -o interface.o`
sleep 1
echo "[x] DONE!"
sleep 1
echo; echo; echo "[+] Creating Linker File for Server"
`g++ -c server.cpp -o server.o`
# Final Command That Will Be Executed
sleep 1
echo "[x] DONE!"
sleep 1
echo; echo; echo "[+] Creating file main and Executing it: "
`g++ -pthread -o main main.cpp *.o && rm -rf *.o`
sleep 1
echo "[X] DONE!"
echo; echo; echo "Type ./main to run the program."; echo
exit 0