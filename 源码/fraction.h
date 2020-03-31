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
		int nume; //分子
		int decm; //分母
		
		int divise(); //最大公约数 
		void fix();   //修复数据，符号只出现在分子，分数	
	public:		
		//重载运算符
		fraction operator+(const fraction& right);
		fraction operator-(const fraction& right);
		fraction operator*(const fraction& right);
		fraction operator/(const fraction& right);
		void operator=(const int& a);
		void operator=(const fraction& a);	
		bool operator==(const fraction& right);
		//获取对象的数值
		double value(); //按浮点数输出分数的值
		int getDecm();	//分子的值	
		int getNume();	//分母的值
		//格式化字符串
		std::string toString();
	};  //end class define

	int rollexp(std::stringstream& exc, int limit, int opn, int inn = 2, int mark = 0);//生成算式
	pm::fraction rePolishNotation(const std::string& exp, std::stringstream& repo); //类波兰表达式运算特征映射


}//end namespace pm