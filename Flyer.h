#ifndef _FrequentFlyer_

#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


enum STATUS{SILVER=0,GOLD,PLATINUM,SUPER};

class Flyer
{
	string name;
	STATUS status;
	int waitTime;
	int code; // confirmation code;

public:
	Flyer(string _name, string _st){
		try{
			name = _name;
			waitTime = 0;
			code = -1;
			setStatus(_st);
		}
		catch(string exp){
			throw exp;
		}
		
	}

	Flyer(string _name, STATUS _st){
		name = _name;
		waitTime = 0;
		setStatus(_st);
		code = -1;
	}


	void setName(string _name)
	{
		name = _name;
	}

	void setStatus(string _status)
	{
			if(_status == "SILVER"){
			//cout<<SILVER<<endl;
			status =  SILVER;
			}
			else if(_status == "GOLD"){
				status =  GOLD;
			}
			else if(_status == "PLATINUM"){
				status =  PLATINUM;
			}
			else if(_status == "SUPER"){
				status =  SUPER;
			}
			else{
				cout<<"Invalid Status input.\n";
				throw "Invalid Status:" +_status;
			}
		
	}

	void setStatus(STATUS _st)
	{
		if(_st < SILVER || _st > SUPER)
		{
			cout<<"Invalid status:"<<_st<<endl;
			return;
		}
		status = _st;
	}

	void setWaitTime(int time)
	{
		waitTime = time;
	}

	void setCode(int _code)
	{
		code = _code;
	}


	STATUS getStatus() const
	{
		return status;
	}

	int getWaitTime() const
	{
		return waitTime;
	}

	string getName()
	{
		return name;
	}

	int getCode() const
	{
		return code;
	}

	bool operator <(const Flyer& f) const
	{
		if(status < f.getStatus()) return true;
		else if(status == f.getStatus()){
			return waitTime > f.getWaitTime(); 
		}
		return false;
	}

	bool operator >(const Flyer& f) const
	{
		if(status > f.getStatus()) return true;
		else if(status == f.getStatus()){
			return waitTime < f.getWaitTime(); 
		}
		return false;
	}

	string getStatusString()
	{
		string res = "";
		if(status == SILVER){
			res = "SILVER";
		}
		else if(status == GOLD){
			res = "GOLD";
		}
		else if(status == PLATINUM){
			res =  "PLATINUM";
		}
		else if(status == SUPER){
			res =  "SUPER";
		}
		return res;
	}

};

#endif
