#pragma once
#include "Course_time.h"

class Course
{
public:
	Course(Json::Value* data);
	~Course(void);

	CString* title;
	std::vector<Course_time*>* time;
	int credits;
	CString* location;
	CString* department;
	CString* code;
	CString* professor;
	bool obligatory;

	static void set_list_head(CListCtrl* listView);
	void to_list(CListCtrl* listView,short* class_table,short value);
	void to_combobox(CComboBox* listView);
};

