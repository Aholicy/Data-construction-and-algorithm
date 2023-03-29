#include<iostream>     //����ı��ʽҪ��'#'��β���确5+6*3/(3-1)#��
#include<cstring>
#include<cstdio>
#include<cctype>
#include<stack>
#include <math.h>
using namespace std;
 
stack<char> opter;    //�����ջ
stack<double> opval;  //������ջ
string format(string str){
	for(int i = 0;i < str.length(); i++){
		if(str[i] == '-'){
			if(i == 0){
				str.insert(0,1,'0');
			}else if(str[i-1] == '('){
				str.insert(i,1,'0');
			}
		}
		
	}
	return str;
}
//ջ�����ȼ� 
int isp(char op) {
	if (op == '#') return 0;
	else if (op == '+') return 3;
	else if (op == '-') return 3;
	else if (op == '*') return 5;
	else if (op == '/') return 5;
	else if (op == '(') return 1;
	else if (op == ')') return 8;
	else if (op == '^') return 7;
}
//ջ�����ȼ� 
int osp(char op) {
	if (op == '#') return 0;
	else if (op == '+') return 2;
	else if (op == '-') return 2;
	else if (op == '*') return 4;
	else if (op == '/') return 4;
	else if (op == '(') return 8;
	else if (op == ')') return 1;
	else if (op == '^') return 6;
}

char getPriority(char theta1, char theta2){   //��ȡtheta1��theta2֮������ȼ�
//theta1ջ�ڣ�theta2ջ��	
	int index1 = isp(theta1);
	int index2 = osp(theta2);
	if(index1>index2){
		return '>';
	}
	else if(index1<index2){
		return '<';
	}
	else{
		return '=';
	}
}
double calculate(double b, char theta, double a)   //����b theta a
{
	switch (theta)
	{
	case '+':
		return b + a;
		break;
	case '-':
		return b - a;
		break;
	case '*':
		return b * a;
		break;
	case '/':
		return b / a;
		break;
	case '^':
        return pow(b,a);
		break;
	default:
		break;
	}
}
 
double getAnswer()   //���ʽ��ֵ
{
	opter.push('#');      //���Ƚ�'#'��ջopter
	int counter = 0;      //��ӱ���counter��ʾ�ж��ٸ����������ջ��ʵ�ֶ�λ������������
	char c = getchar();
	while (c != '#' || opter.top() != '#')   //��ֹ����
	{
		if (isdigit(c))   //���c��'0'~'9'֮��
		{
			if (counter == 1)   //counter==1��ʾ��һ�ַ�Ҳ�����֣�����Ҫ�ϲ�������12*12��Ҫ��12�������ǵ�����1��2
			{
				double t = opval.top();
				opval.pop();
				opval.push(t * 10 + (c - '0'));
				counter = 1;
			}
			else
			{
				opval.push(c - '0');     //��c��Ӧ����ֵ��ջopval
				counter++;
			}
			c = getchar();
		}
		else
		{
			counter = 0;   //counter����
			switch (getPriority(opter.top(), c))   //��ȡ�����ջopterջ��Ԫ����c֮������ȼ�����'>'��'<'��'='��ʾ
			{
			case '<':               //<��c��ջopter
				opter.push(c);
				c = getchar();
				break;
			case '=':               //=��opterջ��Ԫ�ص������������ŵĴ���
				opter.pop();
				c = getchar();
				break;
			case '>':               //>�����
				char theta = opter.top();
				opter.pop();
				double a = opval.top();
				opval.pop();
				double b = opval.top();
				opval.pop();
				opval.push(calculate(b, theta, a));
			}
		}
	}
	return opval.top();   //����opvalջ��Ԫ�ص�ֵ
}
 
int main(){
	
//	freopen("test.txt", "r", stdin);
	int t;     // ��Ҫ����ı��ʽ�ĸ���
	cin >> t;
	getchar();
	while (t--)
	{
		while (!opter.empty())opter.pop();
		while (!opval.empty())opval.pop();
		double ans = getAnswer();
		cout << ans << endl<< endl;
		getchar();
	}
	return 0;
}

