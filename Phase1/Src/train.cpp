#include <bits/stdc++.h>

using namespace std ;
class A
{
	public :
	void a()
	{
		vector<int> a={3,432,43,23};
		sort(a.begin(), a.end(), A::cmp);
	}
	static bool cmp(int x, int y)
	{
		return x<y;
	}
	void operator()(int x)
	{
		cout<<"YES";
	}
};

stringstream print()
{
	stringstream s;
	s<<"dsaas";
	return s;
}

  void a()
  {
      throw exception("SADAS");
  }
 
  int main()
  {
      try
     {
          a()
      }
      catch (exception& err)
      {
          cout<<err.what();
      }
 }

