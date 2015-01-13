#include "stdafx.h"
#include "Course_time.h"

using namespace std;

Course_time::Course_time(Json::Value* data)
{
	#define D (*data)
	if(!D.isObject())
		throw new CString("Json for Course_time not valid!");

	if(!D["day"].isInt()) throw new CString("Json for Course_time not valid!");
	day = D["day"].asInt();

	Json::Value tmp = D["time"];
	if(!tmp.isArray())
		throw new CString("Json for Course_time not valid!");
	time = new vector<int>();
	for (int i = 0; i < tmp.size(); i++){
		if(!tmp[i].isInt()) throw new CString("Json for Course_time not valid!");
		time->push_back(tmp[i].asInt());
	}
}


Course_time::~Course_time(void)
{
}

void Course_time::set_hour(short* input,short value) // input must be short[5][13]
{
	for (int i = 0; i < time->size(); i++)
	{
		if(*(input + (day-1)*13 + (*time)[i] - 1) != -1)
			throw new CString(_T("There is a collision!"));
		*(input + (day-1)*13 + (*time)[i] - 1) = value;
	}
}

CString Course_time::toString()
{
	CString str,tmp;
	str.Format(_T("星期%d的"),day);
	for (int i = 0; i < time->size(); i++){
		tmp.Format(_T("%X,"),(*time)[i]);
		str += tmp;
	}
	str.Format(_T("%s節"),str);
	return str;
}