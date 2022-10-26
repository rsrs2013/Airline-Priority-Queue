#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Airline.h"

using namespace std;


void createPassengers(vector<Flyer>& priorityFlyer) {

        priorityFlyer.push_back(Flyer("Holland", GOLD));

        priorityFlyer.push_back(Flyer("Matt", PLATINUM));

        priorityFlyer.push_back(Flyer("Henry", SILVER));

        priorityFlyer.push_back(Flyer("Ketty", SUPER));

        priorityFlyer.push_back(Flyer("Dew", GOLD));

        priorityFlyer.push_back(Flyer("Jack", GOLD));

        priorityFlyer.push_back(Flyer("Mathew", SILVER));

        priorityFlyer.push_back(Flyer("Pam", PLATINUM));

        priorityFlyer.push_back(Flyer("Dwight", PLATINUM));

        priorityFlyer.push_back(Flyer("David", SUPER));

}


int main()
{

	int n;
	int k;
	Airline air;
	vector<Flyer> flyers;
	while(1)
	{
		
		cout<<"\nEnter\n1.Enter the Flyers\n2.Batch Upgrade Request(from list) \n3.Individual Upgrade Request";
		cout<<"\n4.Cancel Request \n5.K-Flyers \n6.Exit\n";
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 1:{
				createPassengers(flyers);
				cout<<"Total passengers: "<<flyers.size()<<endl;
				cout<<"Successfully created the passengers\n\n";
				break;
			}
			case 2:{
				//Update request as a batch from the array of passegners created above;
				if(!flyers.size())
				{
					cout<<"No flyers to do batch upgrade\n";
				}
				for(auto f: flyers)
				{
					int code = air.upgradeRequest(f);
					cout<<"Name: "<<f.getName()<<"\tStatus: "<<f.getStatusString()<<endl;
					cout<<"Confirmation code:\t"<<code<<endl;
					cout<<"\n";	
				}
				cout<<"Total Upgrade Requests:\t"<<air.getTotalUpgradeRequests()<<endl;

				break; 
			}
			case 3:{
				//Individual update request;

				string name;
				string status;
				cout<<"Enter name:\t"; 
				cin >> name;
				cout<<"Enter status (SILVER,GOLD,PLATINUM,SUPER) case-sensitive:\t";
				cin >> status;
				try{
					Flyer f(name,status);
					cout<<f.getName()<<endl;
					cout<<f.getStatus()<<endl;
					int code = air.upgradeRequest(f);
					cout<<"Name: "<<f.getName()<<"\tStatus: "<<f.getStatusString()<<endl;
					cout<<"Confirmation code:\t"<<code<<endl;
					cout<<"Total Upgrade Requests:\t"<<air.getTotalUpgradeRequests()<<endl;	
					cout<<"\n";
				}
				catch(string exp)
				{
					cout<<"Try again !!"<<endl;
				}
				
					
				break;

			}

			case 4:{
				int code;
				cout<<"Enter the confirmation code to cancel:\t";
				cin>>code;
				air.cancelRequest(code);
				
				break;
			}

			case 5:{
				cout<<"Enter the upgrade seats available(k):\t";
				cin>>k;
				vector<Flyer> res = air.getKFlyers(k);
				if(res.size())
				{
					for(auto flyer: res){
						cout<<"Name:\t";
						cout<<flyer.getName()<<endl;
						cout<<"Status:\t";
						cout<<flyer.getStatusString()<<endl;
						cout<<"\n";
					}
				}
				if(!air.getTotalUpgradeRequests()) 
				{
					flyers = {};
				}
				break;
			}

			case 6:
				exit(0);

			default:
				break;

		}
	}


}
