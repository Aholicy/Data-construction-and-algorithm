#include<iostream>     //输入的表达式要以'#'结尾，如‘5+6*3/(3-1)#’
#include<cstring>
#include<cstdio>
#include<cctype>
#include<stack>
#include <math.h>
using namespace std;
 
stack<char> opter;    //运算符栈
stack<double> opval;  //操作数栈
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
//栈内优先级 
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
//栈外优先级 
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

char getPriority(char theta1, char theta2){   //获取theta1与theta2之间的优先级
//theta1栈内，theta2栈外	
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
double calculate(double b, char theta, double a)   //计算b theta a
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
 
double getAnswer()   //表达式求值
{
	opter.push('#');      //首先将'#'入栈opter
	int counter = 0;      //添加变量counter表示有多少个数字相继入栈，实现多位数的四则运算
	char c = getchar();
	while (c != '#' || opter.top() != '#')   //终止条件
	{
		if (isdigit(c))   //如果c在'0'~'9'之间
		{
			if (counter == 1)   //counter==1表示上一字符也是数字，所以要合并，比如12*12，要算12，而不是单独的1和2
			{
				double t = opval.top();
				opval.pop();
				opval.push(t * 10 + (c - '0'));
				counter = 1;
			}
			else
			{
				opval.push(c - '0');     //将c对应的数值入栈opval
				counter++;
			}
			c = getchar();
		}
		else
		{
			counter = 0;   //counter置零
			switch (getPriority(opter.top(), c))   //获取运算符栈opter栈顶元素与c之间的优先级，用'>'，'<'，'='表示
			{
			case '<':               //<则将c入栈opter
				opter.push(c);
				c = getchar();
				break;
			case '=':               //=将opter栈顶元素弹出，用于括号的处理
				opter.pop();
				c = getchar();
				break;
			case '>':               //>则计算
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
	return opval.top();   //返回opval栈顶元素的值
}
 
int main(){
	
//	freopen("test.txt", "r", stdin);
	int t;     // 需要计算的表达式的个数
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

