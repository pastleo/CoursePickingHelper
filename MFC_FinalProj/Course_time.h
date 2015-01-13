#pragma once

class Course_time
{
public:
	Course_time(Json::Value* data);
	~Course_time(void);

	int day;
	std::vector<int>* time;

	void set_hour(short* input,short value); // input must be short[5][13]
	CString toString();
};

