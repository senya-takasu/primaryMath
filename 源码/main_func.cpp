#include<iostream>
#include<fstream>
#include<random>
#include <time.h>

#include"fraction.h"


using namespace std;





int main(int argc, char** argv)
{
	stringstream any;
	stringstream current, worng;//答案统计字符流

	int numn;//操作数数量

	int expnum=100;//习题数量
	int limit = 100;//题目数值限制
	string exp;//题目
	string repo; //题目的波兰式
	
	//计算结果
	pm::fraction result;
	double resva;
	int up,low;

	int checkok = 0, checkwarse = 0;//判题统计
	
	ofstream fexc; //题目文件
	ofstream fans; //答案文件

	ifstream infexc;//回答文件
	ifstream infans;//答案文件

	string aexc;//-e filename
	string aans;//-a filename

	vector<string> code;//参数分析--复用做读答案列表
	bool mark = false;
	bool extag = false;
	bool antag = false;

	string checktemp ;//读回答情况
	char ch;



	srand(static_cast<unsigned int>(time(0))); // random seed

	
	// code anylize


	
	for (int i = 1; i < argc; ++i)
		code.push_back(argv[i]);

	if (argc % 2 == 0) return 0;

	for (int i = 0; i < code.size(); i=i+2)
	{
		if (code[i].find("-r") <= code[i].size())
		{
			mark = true;
			limit = 0;
			for (int j = 0; j < code[i + 1].size(); ++j)
			{
				limit *= 10; limit += code[i + 1][j] - '0';
			}
		}
		else if (code[i].find("-n") <= code[i].size())
		{
			expnum = 0;
			for (int j = 0; j < code[i + 1].size(); ++j)
			{
				expnum *= 10; expnum += code[i + 1][j] - '0';
			}
		}
		else if (code[i].find("-a") <= code[i].size())
		{
			aans.assign(code[i + 1]);
			antag = true;
		}
		else if (code[i].find("-e") <= code[i].size())
		{
			aexc.assign(code[i + 1]);
			extag = true;
		}
	}
	
	// main process
	
	if (extag&&antag) //比较答案部分的字符串
	{
		std::cout << "练习文件：" << aexc << endl;
		std::cout << "答案文件：" << aans << endl;

		infexc.open(aexc, ios::in);
		infans.open(aans, ios::in);

		fans.open("Grade.txt", ios::out | ios::trunc);
		if (infexc.is_open() && infans.is_open())
		{
			code.clear();
			up = low = 0;
			while (getline(infans, aans))
			{
				++up;
				numn=aans.find('.');
				checktemp.clear();
				for (numn++; numn < aans.size(); ++numn)
				{
					checktemp.push_back(aans[numn]);
				}
				code.push_back(checktemp); 
			}//读取全部答案

			for (low = 0; low < up; ++low)//按顺序检查回答与答案是否一致
			{
				checktemp.clear();
				mark = false;
				while (infexc.get(ch) && !infexc.eof())
				{
					if (ch == '\n') break;
					else if (mark&&ch!=' '&&ch!='\t')
						checktemp.push_back(ch);
					else if (ch == '=')
						mark = true;
				}
				std::cout <<1+low<<") "<< checktemp << ':' << code[low] << endl;

				if (checktemp == code[low]) { current << 1+low << ' '; checkok++; }
				else { worng << 1+low << ' '; checkwarse++; }
			}

			std::cout << "Correct:" << checkok << '(' << current.str() << ')'<<endl;
			std::cout << "Wrong:" << checkwarse << '(' << worng.str() << ')' << endl;

			if (fans.is_open())
			{
				fans << "Correct:" << checkok << '(' << current.str() << ")\n";
				fans << "Wrong:" << checkwarse << '(' << worng.str() << ")\n";
				fans.close();
			}
			else std::cout << "统计写入失败" << endl;
			
			infexc.close(); infans.close();
		}
		else 
		{
			std::cout << "文件加载失败，请检查是否输入错误或者未生成题目文件" << endl;
			
		}
	}
	else if (mark&& expnum >=10&& expnum <=10000&&limit>9)
	{
		fexc.open("Exercises.txt", ios::out | ios::trunc);
		fans.open("Answers.txt", ios::out | ios::trunc);

		for (int i = 0; i < expnum; ++i)
		{

			//生成
			any.str("");
			numn = 2 + rand() % 3;
			pm::rollexp(any, limit, numn);
			exp.assign(any.str());

			//计算
			any.str("");
			result = pm::rePolishNotation(exp, any);
			repo.assign(any.str());

			//基于结果的数值范围检查
			resva = result.value();
			up = result.getNume();
			low = result.getDecm();
			if (resva<0 || resva>limit || up > limit || up<0 || low>limit || low < 0)
			{
				--i;
				continue;
			}

			checkwarse++;
			std::cout << exp << " = " << std::endl;
			fexc <<i<<'.'<< exp << " = \n";
			std::cout << "波兰式: " << repo << std::endl;
			fans << i<<'.'<<result.toString() << '\n';
		}
		std::cout << "生成题目数量：" << checkwarse << endl;
		std::cout << "生成数值范围：" << limit << endl;
		fexc.close(); fans.close();
	}
	else //输出帮助
	{ 
		std::cout << "无法正确识别参数" << endl;
		std::cout << "参数使用说明：" << endl;
		std::cout << "使用模式: primaryMath.exe [parameter] [模式参数]" << endl;
		std::cout << "\nparameter与参数之间用空格分隔" << endl;
		std::cout << "        -r 100  （必须提供该参数），限定数值范围，应输入大于等于10的正整数 " << endl;
		std::cout << "        -n 100  控制生成算式的数量，如100，支持生成10000个算式" << endl;
		std::cout << "        -e <exercise>.txt  引入练习文件，需与-a参数共同使用" << endl;
		std::cout << "        -a <answer>.txt    引入答案文件，与-e配合使用可以判断练习题" << endl;
		std::cout << "可以在程序文件夹下打开exercise.txt文件做练习" << endl;
		std::cout << "分数用带分数输入，如2`3/4" << endl;
		std::cout << "如分数无整数部分，则只需输入 3/4 ， 答案为整数则直接输入数值即可" << endl;
	}
	std::cout << "\n程序执行完毕，即将退出\n";
	system("pause");
	return 0;
}// end main



