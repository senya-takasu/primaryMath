#include "fraction.h"


int pm::fraction::divise()
{
	int a, b, c = 1;
	a = abs(this->nume);//abs(int)
	b = abs(this->decm);//abs(int)

	if (a < b) //swap makesure a>b
	{
		c = a; a = b; b = c;
	}

	if (a > 0 && b > 0)
		while (c != 0 && b != 0)//շת�����
		{
			c = a % b;
			a = b;
			b = c;
		}
	else return 1;
	return a;
}

void pm::fraction::fix()
{
	if (nume == 0) decm = 1;
	if (decm < 0 && nume>0) { decm = -decm, nume = -nume; }
}

	

//public override operator
pm::fraction pm::fraction::operator+(const fraction& right)
{
	fraction result;  //������
	int div;   //������
	result.nume = this->nume * right.decm + this->decm * right.nume;
	result.decm = this->decm * right.decm;
	div = result.divise();//��ȡ������
	result.decm /= div;//Լ�ַ�ĸ
	result.nume /= div;//Լ�ַ���
	result.fix();
	return result;
}
pm::fraction pm::fraction::operator-(const fraction& right)
{
	fraction result;  //������
	int div;   //������
	result.nume = this->nume * right.decm - this->decm * right.nume;
	result.decm = this->decm * right.decm;
	div = result.divise();//��ȡ������
	result.decm /= div;//Լ�ַ�ĸ
	result.nume /= div;//Լ�ַ���
	result.fix();
	return result;
}
pm::fraction pm::fraction::operator*(const fraction& right)
{
	fraction result;  //������
	int div;   //������
	result.nume = this->nume * right.nume;
	result.decm = this->decm * right.decm;
	div = result.divise();//��ȡ������
	result.decm /= div;//Լ�ַ�ĸ
	result.nume /= div;//Լ�ַ���
	result.fix();
	return result;
}
pm::fraction pm::fraction::operator/(const fraction& right)
{
	fraction result;  //������
	int div;   //������
	result.nume = this->nume * right.decm;
	result.decm = this->decm * right.nume;
	div = result.divise();//��ȡ������
	result.decm /= div;//Լ�ַ�ĸ
	result.nume /= div;//Լ�ַ���
	result.fix();
	return result;
}
void pm::fraction::operator=(const int& a)
{

	this->nume = a;
	this->decm = 1;

}
void pm::fraction::operator=(const fraction& a)
{
	this->decm = a.decm;
	this->nume = a.nume;
	this->fix();
}
bool pm::fraction::operator==(const fraction& right)
{

	if ((this->decm == right.decm) &&
		(this->nume == right.nume))
		return true;
	else return false;
}

//fraction value and descripe value
double pm::fraction::value()
{
	return ((double)nume) / ((double)decm);
}
int pm::fraction::getDecm()
{
	return this->decm;
}
int pm::fraction::getNume()
{
	return this->nume;
}

//print control
std::string pm::fraction::toString()
{
	std::stringstream str;
	if (decm == 0)
		str << "divise zero Error";
	else if (decm == 1)
		str << nume;
	else if (nume / decm > 0)
		str << nume / decm << '`' << nume % decm << '/' << decm;
	else
		str << nume << '/' << decm;
	return str.str();
}


//���ɱ��ʽ
int pm::rollexp(std::stringstream& exc, int limit, int opn, int inn, int mark)
{
	int tag = 0; //0�����������ֻ��ߵݹ鴦��1�����������
	char lastch = '\0'; //������ɵ�һ�����
	int number = -1;//������������

	int con;//�����������;
	while (1)
	{

		if (tag == 0) //�������֣��ݹ�ı��ʽҲ������
		{
			con = rand() % 4;//��������
			if (0 == con && inn > 0 && lastch != '/' && lastch != '-') //0.25��������ݹ�
			{ //���ź��治����ݹ飻
				con = (rand() % opn) + 1;
				opn -= con;
				--inn;
				exc << " ( ";
				rollexp(exc, limit, con, inn, 1);
				exc << " ) ";
			}
			else  //��������
			{
				if (lastch == '-') //��������С��֮ǰ����
				{
					number = rand() % limit;
				}
				else if (lastch == '/') //������Ϊ0
				{
					number = 1 + rand() % limit;
				}
				else //��������0-limit������
				{
					number = rand() % (1 + limit);
				}
				exc << number;
				--opn;
			}

			tag = 1;//�����ṹ��ģʽ�л�
		}
		else if (tag == 1)
		{
			con = (rand()) % 4;//��������
			if (0 == con)
				lastch = '+';
			else if (1 == con && 0 == mark)
				lastch = '-';
			else if (3 == con && lastch != '-' && lastch != '/' && lastch != '*')
				lastch = '*';
			else if (2 == con && 0 == mark && lastch != '/')
				lastch = '/';
			else lastch = '+';

			exc << ' ' << lastch << ' ';

			tag = 0;//�����ṹ��ģʽ�л�
		}
		if (opn == 0) break;// end while check
	}
	return 1;
}


pm::fraction pm::rePolishNotation(const std::string& exp, std::stringstream& repo) //�ನ�����ʽ��������ӳ��
{
	std::vector<pm::fraction> flist;
	char clist[OPLIMIT];
	int size = exp.size();
	int itc = 0, itf = 0;

	int num = 0;
	int i = 0;
	char ch = 0, lastch = 0;
	pm::fraction a, b, lastnum;

	lastnum = 1;
	for (i = 0; i < size; ++i)
	{
		ch = exp[i];
		if (ch == '(')
		{
			clist[itc] = ch;
			++itc;
		}
		else if (ch >= '0' && ch <= '9')
		{
			for (num = 0; exp[i] >= '0' && exp[i] <= '9' && i < size; ++i)
			{
				ch = exp[i];
				num *= 10;
				num += ch - '0';
			}lastnum = num;

			flist.push_back(lastnum); ++itf;//ָ��ջ����һ��λ��
		}
		else if (ch == '+' || ch == '-')
		{
			while (1)
			{
				if (itc < 1) break;
				else
				{
					lastch = clist[itc - 1];
					if (lastch == '(') break;
					else
					{
						b = flist[itf - 1]; --itf;
						a = flist[itf - 1]; --itf;
						if (lastch == '+') lastnum = a + b;
						else if (lastch == '-') lastnum = a - b;
						else if (lastch == '*') lastnum = a * b;
						else if (lastch == '/') lastnum = a / b;
						flist.pop_back();
						flist.pop_back();
						flist.push_back(lastnum); ++itf;
						repo << a.toString() << ' ' << b.toString() << ' ' << lastch << ' ';
						--itc;
					}
				}
			}clist[itc] = ch; ++itc;
		}
		else if (ch == '*' || ch == '/')
		{
			while (1)
			{
				if (itc < 1) break;
				else
				{
					lastch = clist[itc - 1];
					if (lastch == '(') break;
					if (lastch == '+' || lastch == '-') break;
					else
					{
						b = flist[itf - 1]; --itf;
						a = flist[itf - 1]; --itf;
						if (lastch == '+') lastnum = a + b;
						else if (lastch == '-') lastnum = a - b;
						else if (lastch == '*') lastnum = a * b;
						else if (lastch == '/') lastnum = a / b;
						flist.pop_back();
						flist.pop_back();
						flist.push_back(lastnum); ++itf;
						repo << a.toString() << ' ' << b.toString() << ' ' << lastch << ' ';
						--itc;
					}
				}
			}clist[itc] = ch; ++itc;
		}
		else if (ch == ')')
		{
			while (itc > 0 && clist[itc - 1] != '(')
			{
				lastch = clist[itc - 1];

				b = flist[itf - 1]; --itf;
				a = flist[itf - 1]; --itf;
				if (lastch == '+') lastnum = a + b;
				else if (lastch == '-') lastnum = a - b;
				else if (lastch == '*') lastnum = a * b;
				else if (lastch == '/') lastnum = a / b;
				flist.pop_back();
				flist.pop_back();
				flist.push_back(lastnum); ++itf;
				repo << a.toString() << ' ' << b.toString() << ' ' << lastch << ' ';
				--itc;
			}if (itc > 0 && clist[itc - 1] == '(')itc--;
		}
		else;//���ַ�����

	}
	//�����ַ�����
	while (itc > 0)
	{
		lastch = clist[itc - 1];

		b = flist[itf - 1]; --itf;
		a = flist[itf - 1]; --itf;
		if (lastch == '+') lastnum = a + b;
		else if (lastch == '-') lastnum = a - b;
		else if (lastch == '*') lastnum = a * b;
		else if (lastch == '/') lastnum = a / b;
		flist.pop_back();
		flist.pop_back();
		flist.push_back(lastnum); ++itf;
		repo << a.toString() << ' ' << b.toString() << ' ' << lastch << ' ';
		--itc;
	}
	return lastnum;
}