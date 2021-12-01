compile_mod = g++ -std=c++11

all : utrip.out

utrip.out : Filter.o AvailableRoomFilter.o SortFilter.o StarFilter.o CityFilter.o CostFilter.o Rating.o GeneralFunctions.o Reservation.o Comment.o Hotel.o Room.o User.o UTRIP.o CSVReader.o Main.o Weights.o PersonalRatingSortFilter.o response.o request.o server.o route.o utilities.o template_parser.o LogicHandlers.o ShowPageHandlers.o SessionManager.o
	${compile_mod} Filter.o Rating.o GeneralFunctions.o AvailableRoomFilter.o SortFilter.o StarFilter.o CityFilter.o CostFilter.o Reservation.o Comment.o Hotel.o Room.o User.o UTRIP.o CSVReader.o Main.o Weights.o PersonalRatingSortFilter.o response.o request.o server.o route.o utilities.o template_parser.o LogicHandlers.o ShowPageHandlers.o SessionManager.o -o utrip.out

Main.o : Main.cpp PersonalRatingSortFilter.hpp Weights.hpp LibrariesAndDefines.hpp Filter.hpp SortFilter.hpp AvailableRoomFilter.hpp StarFilter.hpp CityFilter.hpp CostFilter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp CSVReader.hpp utils/include.hpp utils/response.hpp utils/request.hpp server/server.hpp server/route.hpp utils/utilities.hpp utils/template_parser.hpp LogicHandlers.hpp ShowPageHandlers.hpp SessionManager.hpp
	${compile_mod} -c Main.cpp

CSVReader.o : CSVReader.cpp PersonalRatingSortFilter.hpp LibrariesAndDefines.hpp Filter.hpp SortFilter.hpp AvailableRoomFilter.hpp StarFilter.hpp CityFilter.hpp CostFilter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp CSVReader.hpp Weights.hpp
	${compile_mod} -c CSVReader.cpp

UTRIP.o : UTRIP.cpp PersonalRatingSortFilter.hpp Weights.hpp LibrariesAndDefines.hpp Filter.hpp SortFilter.hpp AvailableRoomFilter.hpp StarFilter.hpp CityFilter.hpp CostFilter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp 
	${compile_mod} -c UTRIP.cpp

User.o : User.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp Weights.hpp
	${compile_mod} -c User.cpp

Hotel.o : Hotel.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp 
	${compile_mod} -c Hotel.cpp

Filter.o : Filter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp
	${compile_mod} -c Filter.cpp

PersonalRatingSortFilter.o : PersonalRatingSortFilter.cpp PersonalRatingSortFilter.hpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp User.hpp
	${compile_mod} -c PersonalRatingSortFilter.cpp

AvailableRoomFilter.o : AvailableRoomFilter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp AvailableRoomFilter.hpp
	${compile_mod} -c AvailableRoomFilter.cpp

StarFilter.o : StarFilter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp StarFilter.hpp
	${compile_mod} -c StarFilter.cpp

CityFilter.o : CityFilter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp CityFilter.hpp
	${compile_mod} -c CityFilter.cpp

CostFilter.o : CostFilter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp CostFilter.hpp
	${compile_mod} -c CostFilter.cpp	

SortFilter.o : SortFilter.cpp LibrariesAndDefines.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp Filter.hpp SortFilter.hpp
	${compile_mod} -c SortFilter.cpp	

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

Weights.o : Weights.cpp LibrariesAndDefines.hpp Weights.hpp
	${compile_mod} -c Weights.cpp

template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	${compile_mod} -c utils/template_parser.cpp 

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	${compile_mod} -c utils/response.cpp 

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	${compile_mod} -c utils/request.cpp 

utilities.o: utils/utilities.cpp utils/utilities.hpp
	${compile_mod} -c utils/utilities.cpp 

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	${compile_mod} -c server/server.cpp 

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${compile_mod} -c server/route.cpp 

LogicHandlers.o: LogicHandlers.cpp LogicHandlers.hpp ShowPageHandlers.hpp utils/include.hpp utils/response.hpp utils/request.hpp server/server.hpp server/route.hpp utils/utilities.hpp utils/template_parser.hpp GeneralFunctions.hpp PersonalRatingSortFilter.hpp Weights.hpp LibrariesAndDefines.hpp Filter.hpp SortFilter.hpp AvailableRoomFilter.hpp StarFilter.hpp CityFilter.hpp CostFilter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp SessionManager.hpp
	${compile_mod} -c LogicHandlers.cpp

ShowPageHandlers.o: ShowPageHandlers.cpp LogicHandlers.hpp ShowPageHandlers.hpp utils/include.hpp utils/response.hpp utils/request.hpp server/server.hpp server/route.hpp utils/utilities.hpp utils/template_parser.hpp PersonalRatingSortFilter.hpp Weights.hpp LibrariesAndDefines.hpp Filter.hpp SortFilter.hpp AvailableRoomFilter.hpp StarFilter.hpp CityFilter.hpp CostFilter.hpp Rating.hpp GeneralFunctions.hpp Reservation.hpp Comment.hpp Hotel.hpp Room.hpp User.hpp UTRIP.hpp SessionManager.hpp
	${compile_mod} -c ShowPageHandlers.cpp

SessionManager.o : SessionManager.cpp SessionManager.hpp LibrariesAndDefines.hpp
	${compile_mod} -c SessionManager.cpp

clean : 
	rm *.o *.out

