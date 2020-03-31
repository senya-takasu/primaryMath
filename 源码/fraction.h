#pragma once
#include<math.h>
#include<sstream>
#include<vector>
#include<string>

#define OPLIMIT 128

namespace pm {

	class fraction
	{
	private:
		int nume; //����
		int decm; //��ĸ
		
		int divise(); //���Լ�� 
		void fix();   //�޸����ݣ�����ֻ�����ڷ��ӣ�����	
	public:		
		//���������
		fraction operator+(const fraction& right);
		fraction operator-(const fraction& right);
		fraction operator*(const fraction& right);
		fraction operator/(const fraction& right);
		void operator=(const int& a);
		void operator=(const fraction& a);	
		bool operator==(const fraction& right);
		//��ȡ�������ֵ
		double value(); //�����������������ֵ
		int getDecm();	//���ӵ�ֵ	
		int getNume();	//��ĸ��ֵ
		//��ʽ���ַ���
		std::string toString();
	};  //end class define

	int rollexp(std::stringstream& exc, int limit, int opn, int inn = 2, int mark = 0);//������ʽ
	pm::fraction rePolishNotation(const std::string& exp, std::stringstream& repo); //�ನ�����ʽ��������ӳ��


}//end namespace pm