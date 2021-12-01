compile_mod = g++ -std=c++11

all : utrip.out

utrip.out : Filter.o Rating.o GeneralFunctions.o Reservation.o Comment.o Hotel.o Room.o User.o CommandFixer.o UTRIP.o CSVReader.o Interface.o Main.o
	${compile_mod} Filter.o Rating.o GeneralFunctions.o Reservation.o Comment.o Hotel.o Room.o User.o CommandFixer.o UTRIP.o CSVReader.o Interface.o Main.o -o utrip.out

Main.o : Main.cpp LibrariesAndDefines.hpp Filter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp CommandFixer.hpp UTRIP.hpp CSVReader.hpp Interface.hpp 
	${compile_mod} -c Main.cpp

CSVReader.o : CSVReader.cpp LibrariesAndDefines.hpp Filter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp CSVReader.hpp
	${compile_mod} -c CSVReader.cpp

Interface.o : Interface.cpp LibrariesAndDefines.hpp Filter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp CommandFixer.hpp UTRIP.hpp Interface.hpp 
	${compile_mod} -c Interface.cpp

UTRIP.o : UTRIP.cpp LibrariesAndDefines.hpp Filter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp 
	${compile_mod} -c UTRIP.cpp

User.o : User.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp
	${compile_mod} -c User.cpp

Hotel.o : Hotel.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp 
	${compile_mod} -c Hotel.cpp

Filter.o : Filter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp
	${compile_mod} -c Filter.cpp

Reservation.o : Reservation.cpp LibrariesAndDefines.hpp Room.hpp Reservation.hpp
	${compile_mod} -c Reservation.cpp

Room.o : Room.cpp LibrariesAndDefines.hpp Room.hpp Reservation.hpp
	${compile_mod} -c Room.cpp

Rating.o : Rating.cpp LibrariesAndDefines.hpp Rating.hpp
	${compile_mod} -c Rating.cpp

GeneralFunctions.o : GeneralFunctions.cpp LibrariesAndDefines.hpp GeneralFunctions.hpp
	${compile_mod} -c GeneralFunctions.cpp

Comment.o : Comment.cpp LibrariesAndDefines.hpp Comment.hpp
	${compile_mod} -c Comment.cpp

CommandFixer.o : CommandFixer.cpp LibrariesAndDefines.hpp CommandFixer.hpp
	${compile_mod} -c CommandFixer.cpp

clean : 
	rm *.o *.out

