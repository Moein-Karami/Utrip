#ifndef _Filter_hpp_
#define _Filter_hpp_

#include "LibrariesAndDefines.hpp"

class Hotel;

class Filter 
{
	protected :
		std::string type;
	public :
		Filter(std::string _type = SORT_FILTER);
		static bool compareById(Hotel* hotel1, Hotel* hotel2) ;
		virtual std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);
		virtual std::string getType();
};

class CityFilter : public Filter
{
	private :
		std::string city;
	public :
		CityFilter(std::string _city = BLANK);
		std::vector<Hotel*> purification(const std::vector<Hotel*>);
};

class StarFilter : public Filter
{
	private :
		int min_star;
		int max_star;
	public :
		StarFilter(int _min_star = ZERO, int _max_star = ZERO);
		std::vector<Hotel*> purification(const std::vector<Hotel*>);
};

class CostFilter : public Filter
{
	private :
		double min_cost;
		double max_cost;
	public :
		CostFilter(double _min_cost = ZERO, double _max_cost = ZERO);
		std::vector<Hotel*> purification(const std::vector<Hotel*>);
};

class AvailableRoomFilter : public Filter
{
	private :
		std::string type;
		int quantity;
		int check_in;
		int check_out;
	public :
		AvailableRoomFilter(std::string _type = BLANK, int _quantity = ZERO,
			int _check_in = ZERO, int _check_out= ZERO);
		std::vector<Hotel*> purification(const std::vector<Hotel*>);          
};

#endif