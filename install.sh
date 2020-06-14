#!/bin/bash

echo "################################"
echo "#        INSTALLATION          #"
echo "################################"

echo
echo "g++ -c colors.cpp -o colors.o"
`g++ -c server/colors.cpp -o server/colors.o`
echo "g++ -c inputs.cpp -o inputs.o"
`g++ -c server/inputs.cpp -o server/inputs.o`
echo "g++ -c interface.cpp -o interface.o"
`g++ -c server/interface.cpp -o server/interface.o`
echo "g++ -c server.cpp -o server.o"
`g++ -c server/server.cpp -o server/server.o`
echo "g++ -pthread -o main main.cpp *.o"
`g++ -pthread -o sillyrat server/main.cpp server/*.o`
`rm server/*.o`
echo
echo "Type ./sillyrat to run the program."; echo
exit 0