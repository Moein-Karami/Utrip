#ifndef _LibrariesAndDefines_hpp_
#define _LibrariesAndDefines_hpp_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <exception>
#include <iomanip>
#include <math.h>

#define HASH_BASE 200
#define HASH_MODE 1000000007
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define TEN 10
#define TWELVE 12
#define FOURTEEN 14
#define COMMA ','
#define SPACE ' '
#define COLON ':'
#define EMPTY {}
#define BLANK ""
#define VERTICAL_BAR '|'
#define NOT_FOUND_ERR "Not Found\n"
#define BAD_REQ_ERR "Bad Request\n"
#define PERMISSION_ERR "Permission Denied\n"
#define EMPTY_ERR "Empty\n"
#define OK "OK"
#define CREDIT_ERR "Not Enough Credit\n"
#define ROOM_ERR "Not Enough Room\n"
#define RATING_ERR  "No Rating\n"
#define DEFAULT_FILTER_MSG "* Results have been filtered by the default price filter.\n"
#define INSUFFICIENT_RATING_ERR "Insufficient Ratings\n"
#define HOTEL_ID_IN_FILE 0
#define HOTEL_NAME_IN_FILE 1
#define HOTEL_STAR_IN_FILE 2
#define HOTEL_OVERVIEW_IN_FILE 3
#define HOTEL_AMENITIES_IN_FILE 4
#define HOTEL_CITY_IN_FILE 5
#define HOTEL_LATITUDE_IN_FILE 6
#define HOTEL_LONGITUDE_IN_FILE 7
#define HOTEL_IMG_URL_IN_FILE 8
#define HOTEL_NUM_OF_STD_ROOM_IN_FILE 9
#define HOTEL_NUM_OF_DELUX_ROOM_IN_FILE 10
#define HOTEL_NUM_OF_LUX_ROOM_IN_FILE 11
#define HOTEL_NUM_OF_PRM_ROOM_IN_FILE 12
#define HOTEL_STD_ROOM_PRICE_IN_FILE 13
#define HOTEL_DELUX_ROOM_PRICE_IN_FILE 14
#define HOTEL_LUX_ROOM_PRICE_IN_FILE 15
#define HOTEL_PRM_ROOM_PRICE_IN_FILE 16
#define MAX_RATE 5
#define MIN_RATE 1
#define MIN_CHECK_IN 1
#define MAX_CHECK_IN 30
#define STD_CODE "s"
#define DELUX_CODE "d"
#define LUX_CODE "l"
#define PRM_CODE "p"
#define POST "POST"
#define SIGNUP "signup"
#define QUESTION_MARK "?"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define LOGIN "login"
#define LOGOUT "logout"
#define WALLET "wallet"
#define AMOUNT "amount"
#define GET "GET"
#define COUNT "count"
#define HOTELS "hotels"
#define HOTEL "hotel"
#define ID "id"
#define STAR "star"
#define OVERVIEW "overview"
#define AMENITIES "amenities"
#define CITY "city"
#define LATITUDE "latitude"
#define LONGTITUDE "longitude"
#define ROOMS "#rooms"
#define PRICE "price"
#define FILTERS "filters"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define TYPE "type"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define DELETE "DELETE"
#define RESERVES "reserves"
#define ROOM "room"
#define COST "cost"
#define COMMENT "comment"
#define RATINGS "ratings"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value for money"
#define OVERALL_RATING "overall rating"
#define GET_VALUE_FOR_MONEY "value_for_money"
#define GET_OVERALL_RATING "overall_rating"
#define STD_ROOM_ID 0
#define DELUX_ROOM_ID 1
#define LUX_ROOM_ID 2
#define PRM_ROOM_ID 3
#define NUMBER_OF_ROOM_TYPE 4
#define MONTH_DAYS 30
#define STD "standard"
#define DELUX "deluxe"
#define LUX "luxury"
#define PRM "premium"
#define DIGITS_AFTER_POINT 2
#define SORT_FILTER "sort"
#define CITY_FILTER "city"
#define STAR_FILTER "star"
#define COST_FILTER "cost"
#define ROOM_FILTER "room"
#define COMMENTS "comments"
#define ACTIVE "active"
#define DEFAULT_PRICE_FILTER "default_price_filter"
#define TRUE_MSG "true"
#define FALSE_MSG "false"
#define SORT "sort"
#define PROPERTY "property"
#define ORDER "order"
#define ASCENDING "ascending"
#define DESCENDING "descending"
#define NAME "name"
#define STAR_RATING "star_rating"
#define STD_ROOM_COST "standard_room_price"
#define DELUX_ROOM_COST "deluxe_room_price"
#define LUX_ROOM_COST "luxury_room_price"
#define PRM_ROOM_COST "premium_room_price"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define MANUAL_WEIGHTS "manual_weights"
#define ESTIMATED_WEIGHTS "estimated_weights"
#define RATING_PERSONAL "rating_personal"
#define RATING_OVERALL "rating_overall"
#define ALPHA 1.0
#define EPSILON 0.00005
#define ESTIMATE_STEPS 10000
#define HUNDRED 100.0
#define IS_ESTIMATED false
#endif