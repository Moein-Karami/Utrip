#include <bits/stdc++.h>

using namespace std ;

class A
{
	private :
		bool (*ptr)(int,int);
	public :
		A(bool (*cmp)(int,int))
		{
			ptr=cmp;
		}
		vector<int> st(vector<int> v)
		{
			sort(v.begin(), v.end(), ptr);
			return v;
		}
};

vector<int> a()
{
	return {1,2,3,4,5};
}
int main()
{
	vector<int> v =a();
}

