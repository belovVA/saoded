#pragma once
#include "Student.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

const int num = 10; // ������������ ����� ����� (������ �������)

class SubGroup
{
private:
	struct SubGroupData {
		string text; // �����
		Student student[num]; // ������ �������� (��� ������������ �����)

		int top = -1; // ������ ������� �����
		int count = 0; // ������� ���������� ��������
		SubGroup* right = NULL; // ��������� �� ��������� ������
		SubGroup* left = NULL; // ��������� �� ���������� ������
	} theSubGroup, Tempgroup; // Tempgroup - ��������������� ���� ��� �������� �� � ������� ����� THESubGroup

public:
	SubGroup* right() { return theSubGroup.right; }
	SubGroup* left() { return theSubGroup.left; }
	void SetRight(SubGroup* _right) { theSubGroup.right = _right; }
	void SetLeft(SubGroup* _left) { theSubGroup.left = _left; }
	string GetText() { return theSubGroup.text; }
	// ������������
	SubGroup() {
		theSubGroup.student[0].Set(" <�����>", NULL); // ������� "������" �������-������ �������
		theSubGroup.left = theSubGroup.right = NULL;
	};
	SubGroup(string _text) {
		theSubGroup.student[0].Set(" <�����>", NULL); // ������� "������" �������-������ �������
		theSubGroup.left = theSubGroup.right = NULL;
		theSubGroup.text = _text;
	};

	bool Addstudent(string _text, char _key) {
		if (theSubGroup.count >= num) { // ���� ���� ��� ��������
			cout << " ���� ����� ��������. ���������� ����������";
			return false;
		}
		else {
			theSubGroup.student[theSubGroup.top + 1].Set(_text, _key); // ������������� �������� text � key ��� ������
			theSubGroup.top++; // ������ ������ ������� �����
			theSubGroup.count++;
			return true;
		}
	};

	int Findstudent(string _text) {
		int index = -1;
		for (int i = theSubGroup.top; i > -1; i--)
			if (theSubGroup.student[i].GetText() == _text)
				index = i;
		return index;
	};

	bool Delstudent(string _text) {
		if (theSubGroup.count == 0) { // ���� ���� ������
			//            cout << "\n ���� " << theSubGroup.text << " ������. ������� ������";
			return false;
		}
		int index = Findstudent(_text);
		if (index == -1) {
			//            cout << "\n � ������� " << theSubGroup.text << " ��� ����� ������";
			return false;
		}
		if (index == theSubGroup.top) { // ���� ������� �������-������� �����
			theSubGroup.student[theSubGroup.top].Clear();
			theSubGroup.top--; // ������ ������ ������� �����
			theSubGroup.count--;
			return true;
		}
		else { // ���� ��������� ������� - �� ������� �����, �� ������� ���������������, ��������� � ���� ��� �������� � ������� �� ������� (�� ������������), ������� ������ �������, ������������ ��������������� ���� � ��������
			for (int i = theSubGroup.top; i > index; i--) { // ������������ �������� �� ��������������� ����
				Tempgroup.student[Tempgroup.top + 1].Set(theSubGroup.student[i].GetText(), theSubGroup.student[i].GetKey());
				Tempgroup.top++;
				Tempgroup.count++;
				theSubGroup.student[theSubGroup.top].Clear();
				theSubGroup.top--; // ������ ������ ������� �����
				theSubGroup.count--;
			}

			theSubGroup.student[theSubGroup.top].Clear(); // ������� ������ �������-������
			theSubGroup.top--; // ������ ������ ������� �����
			theSubGroup.count--;

			for (int i = 0; i < Tempgroup.count; i++) { // ������������ �������� ������� � ������� ����
				theSubGroup.student[theSubGroup.top + 1].Set(Tempgroup.student[Tempgroup.top].GetText(), Tempgroup.student[Tempgroup.top].GetKey());
				Tempgroup.student[Tempgroup.top].Clear(); // ������� ������� ���������������� �����
				Tempgroup.top--;
				theSubGroup.top++;
				theSubGroup.count++;
			}

			return true;
		}
	};

	bool Showstudents() {  // ����� ����� ������
		if (theSubGroup.count > 0) {
			for (int i = theSubGroup.top; i > -1; i--) {
				cout << setw(20) << std::left << theSubGroup.student[i].GetText() << "  " << std::right << theSubGroup.student[i].GetKey() << "\n";
				if ((i - 1) > -1) cout << "|" << setw(16) << std::right << "|";
			}
			return true;
		}
		else
			return false;
	};

	string GetString() {
		string str = "";
		for (int i = 0; i < theSubGroup.count; i++) {
			stringstream ss;
			ss << theSubGroup.student[i].GetText();
			str += " ";
			str += ss.str();
			str += " ";
			str += theSubGroup.student[i].GetKey();
		}
		return str;
	};

	~SubGroup() {};
};