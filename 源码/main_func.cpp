#include<iostream>
#include<fstream>
#include<random>
#include <time.h>

#include"fraction.h"


using namespace std;





int main(int argc, char** argv)
{
	stringstream any;
	stringstream current, worng;//��ͳ���ַ���

	int numn;//����������

	int expnum=100;//ϰ������
	int limit = 100;//��Ŀ��ֵ����
	string exp;//��Ŀ
	string repo; //��Ŀ�Ĳ���ʽ
	
	//������
	pm::fraction result;
	double resva;
	int up,low;

	int checkok = 0, checkwarse = 0;//����ͳ��
	
	ofstream fexc; //��Ŀ�ļ�
	ofstream fans; //���ļ�

	ifstream infexc;//�ش��ļ�
	ifstream infans;//���ļ�

	string aexc;//-e filename
	string aans;//-a filename

	vector<string> code;//��������--�����������б�
	bool mark = false;
	bool extag = false;
	bool antag = false;

	string checktemp ;//���ش����
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
	
	if (extag&&antag) //�Ƚϴ𰸲��ֵ��ַ���
	{
		std::cout << "��ϰ�ļ���" << aexc << endl;
		std::cout << "���ļ���" << aans << endl;

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
			}//��ȡȫ����

			for (low = 0; low < up; ++low)//��˳����ش�����Ƿ�һ��
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
			else std::cout << "ͳ��д��ʧ��" << endl;
			
			infexc.close(); infans.close();
		}
		else 
		{
			std::cout << "�ļ�����ʧ�ܣ������Ƿ�����������δ������Ŀ�ļ�" << endl;
			
		}
	}
	else if (mark&& expnum >=10&& expnum <=10000&&limit>9)
	{
		fexc.open("Exercises.txt", ios::out | ios::trunc);
		fans.open("Answers.txt", ios::out | ios::trunc);

		for (int i = 0; i < expnum; ++i)
		{

			//����
			any.str("");
			numn = 2 + rand() % 3;
			pm::rollexp(any, limit, numn);
			exp.assign(any.str());

			//����
			any.str("");
			result = pm::rePolishNotation(exp, any);
			repo.assign(any.str());

			//���ڽ������ֵ��Χ���
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
			std::cout << "����ʽ: " << repo << std::endl;
			fans << i<<'.'<<result.toString() << '\n';
		}
		std::cout << "������Ŀ������" << checkwarse << endl;
		std::cout << "������ֵ��Χ��" << limit << endl;
		fexc.close(); fans.close();
	}
	else //�������
	{ 
		std::cout << "�޷���ȷʶ�����" << endl;
		std::cout << "����ʹ��˵����" << endl;
		std::cout << "ʹ��ģʽ: primaryMath.exe [parameter] [ģʽ����]" << endl;
		std::cout << "\nparameter�����֮���ÿո�ָ�" << endl;
		std::cout << "        -r 100  �������ṩ�ò��������޶���ֵ��Χ��Ӧ������ڵ���10�������� " << endl;
		std::cout << "        -n 100  ����������ʽ����������100��֧������10000����ʽ" << endl;
		std::cout << "        -e <exercise>.txt  ������ϰ�ļ�������-a������ͬʹ��" << endl;
		std::cout << "        -a <answer>.txt    ������ļ�����-e���ʹ�ÿ����ж���ϰ��" << endl;
		std::cout << "�����ڳ����ļ����´�exercise.txt�ļ�����ϰ" << endl;
		std::cout << "�����ô��������룬��2`3/4" << endl;
		std::cout << "��������������֣���ֻ������ 3/4 �� ��Ϊ������ֱ��������ֵ����" << endl;
	}
	std::cout << "\n����ִ����ϣ������˳�\n";
	system("pause");
	return 0;
}// end main



