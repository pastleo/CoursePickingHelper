#include "stdafx.h"
#include "Course.h"

using namespace std;

Course::Course(Json::Value* data)
{
	#define D (*data)
	if(!D.isObject())
		throw new CString("Json for Course not valid!");

	if(!D["title"].isString())
		throw new CString("Json for Course not valid!");

	// Cant solve this... Utf8 to Unicode problem...
	//std::string a = D["title"].asString();
	//CStringT a(D["title"].asString());
	//this->title = (UTF8toUTF16(a));
	//CString ss(CA2T(D["title"].asString()));
	
	this->title = new CString(D["title"].asCString());

	Json::Value tmp = D["time_parsed"];
	if(!tmp.isArray())
		throw new CString("Json for Course not valid!");
	this->time = new std::vector<Course_time*>();
	for (int i = 0; i < tmp.size(); i++)
		time->push_back(new Course_time(&tmp[i]));

	if(!D["credits_parsed"].isInt())
		throw new CString("Json for Course not valid!");
	credits = D["credits_parsed"].asInt();

	if(!D["location"].isString())
		throw new CString("Json for Course not valid!");
	this->location = new CString(D["location"].asCString());
	
	if(!D["code"].isString())
		throw new CString("Json for Course not valid!");
	this->code = new CString(D["code"].asCString());

	if(!D["obligatory_tf"].isBool())
		throw new CString("Json for Course not valid!");
	this->obligatory = D["credits_parsed"].asBool();
}


Course::~Course(void)
{
}

void Course::set_list_head(CListCtrl* listView)
{
	int col_size = listView->GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < col_size; i++)
		listView->DeleteColumn(0);
	
#define addcol(X) listView->InsertColumn(0,_T(#X),0,150);
	addcol(禮拜五)
	addcol(禮拜四)
	addcol(禮拜三) 
	addcol(禮拜二)
	addcol(禮拜一)
	listView->InsertColumn(0,_T(""),0,50);

	listView->DeleteAllItems();
	int row = listView->GetItemCount();
	CString tmp;
#define addrow(X) listView->InsertItem(0,_T(#X));

	addrow(21:05)
	addrow(20:10)
	addrow(19:15)
	addrow(18:20)
	addrow(17:10)
	addrow(16:10)
	addrow(15:10)
	addrow(14:10)
	addrow(13:10)
	addrow(11:10)
	addrow(10:10)
	addrow(09:10)
	addrow(08:10)
}

void Course::to_list(CListCtrl* listView,short* class_table,short value)
{
	CString msg,tmp;

	if(obligatory)
		msg.Format(_T("課程名稱:%s 必修\n"),*title);
	else
		msg.Format(_T("課程名稱:%s 選修\n"),*title);
	for (int i = 0; i < time->size(); i++)
		msg += (*time)[i]->toString() + CString("\n");
	tmp.Format(_T("學分數:%d\n上課位置:%s\n選課號碼:%s\n"),credits,*location,*code);
	msg += tmp;
	AfxMessageBox(msg);
	
	for (int i = 0; i < time->size(); i++)
		(*time)[i]->set_hour(class_table,value);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if(*(class_table + i*13 + j) == value)
				listView->SetItemText(j,i+1,*title);
		}
	}
}

void Course::to_combobox(CComboBox* listView)
{
	listView->InsertString(0,*(title));
}
