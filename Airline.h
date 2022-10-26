#ifndef AIRLINE

#include <iostream>
#include "AirlinePQ.h"

using namespace std;



class Airline
{

	AirlinePQ pq;
	vector<Flyer> flyers;

public:
	int upgradeRequest(Flyer f)
	{
		return pq.push(f);
	}

	void cancelRequest(int code)
	{
		try{
			//pq.getList();
			if(!pq.deleteFlyer(code))
			{
				cout<<"Error!! while cancelling request\n";
			}
			else
			{
				cout<<"Sucessfully cancelled upgradeRequest !!\n";
				cout<<"List after cancellation\n";
				pq.getList();
				cout<<"Total Upgrade Requests: "<<pq.size()<<endl;
			}	 
		}
		catch(...){
			cout<<"Cancel request Failed !!\n";
		}
		
	}

	vector<Flyer> getKFlyers(int k)
	{
		if(!pq.size())
			cout<<"No flyers to upgrade\n";
		if(k <=0 )
			cout<<"K should be greater than zero!!\n";

		vector<Flyer> res;
		while(!pq.empty() && k>0)
		{
			res.push_back(pq.top());
			pq.pop();
			k--;
		}
		return res;
	}

	int getTotalUpgradeRequests()
	{
		return pq.size();
	}

};

#endif