#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string>
#include<stack>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
int count1 = 0;//左右括号对齐
void CMFCApplication1Dlg::ShowMsg(LPCTSTR msg)//显示在对话框上的函数
{
 // TODO: 在此处添加实现代码.
 GetDlgItem(IDC_STATIC)->SetWindowTextW(msg);
}

CString CMFCApplication1Dlg::GetMsg()//get对话框上东西的函数
{
 CString a;
 GetDlgItem(IDC_STATIC)->GetWindowTextW(a);
 return a;
}
//记得自己创建按钮和对话框哦

void CMFCApplication1Dlg::OnBnClickedButton1()//1
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("1"));
 }
 else
 {
  CString b("1");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton2()//2
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("2"));
 }
 else
 {
  CString b("2");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton3()//3
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("3"));
 }
 else
 {
  CString b("3");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton4()//4
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("4"));
 }
 else
 {
  CString b("4");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton5()//5
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("5"));
 }
 else
 {
  CString b("5");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton6()//6
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("6"));
 }
 else
 {
  CString b("6");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton7()//7
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("7"));
 }
 else
 {
  CString b("7");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton8()//8
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("8"));
 }
 else
 {
  CString b("8");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton9()//9
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("9"));
 }
 else
 {
  CString b("9");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton10()//0
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("0"));
 }
 else if (a.Right(1) == "/"|| a.Right(1) == "%")
 {
  CString b("0=error");
  a = a+b;
  ShowMsg(a);
 }
 else
 {
  CString b("0");
  a = a + b;
  ShowMsg(a);
 }
}

CString qufu(CString a)
{
 for (int i = a.GetLength(); i > 0; i--)
 {
  if (a.Mid(i, 1) == "=")
   return a.Right(a.GetLength() - i - 1);
 }
 return a;
}

void CMFCApplication1Dlg::OnBnClickedButton11()//+
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
    if (a.Right(1)=="+"|| a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" ||  a.Right(1) == "!")
 {
  CString b("+");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("+");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("+");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("+");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1--;
 }
 else
 {
  CString b("+");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton12()//-
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "!")
 {
  CString b("-");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("-");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("-");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("(-");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else
 {
  CString b("-");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton13()//*
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "!")
 {
  CString b("*");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("*");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("*");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("*");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1--;
 }
 else
 {
  CString b("*");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton14()///
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "!")
 {
  CString b("/");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("/");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("/");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("/");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1--;
 }
 else
 {
  CString b("/");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton15()//%
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "!")
 {
  CString b("%");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("%");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("%");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("%");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1--;
 }
 else
 {
  CString b("%");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton16()//(
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a == "0")
 {
  ShowMsg(_T("("));
  count1++;
 }
 else if (a.Right(1) == ")")
 {
  CString b("(");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1++;
 }
 else if(a.Right(1)=="1"|| a.Right(1) == "2" || a.Right(1) == "3" || a.Right(1) == "4" || a.Right(1) == "5" || a.Right(1) == "6" || a.Right(1) == "7" || a.Right(1) == "8" || a.Right(1) == "9" || a.Right(1) == "0")
 {
  ShowMsg(a);
 }
 else
 {
  CString b("(");
  a = a + b;
  count1++;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton17()//)
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (count1 > 0)
 {
  if (a == "0")
  {
   ShowMsg(_T("0"));
  }
  else if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "!")
  {
   CString b(")");
   a = a.Left(a.GetLength() - 1) + b;
   ShowMsg(a);
  }
  else if (a.Right(1) == "&&" || a.Right(1) == "||")
  {
   CString b(")");
   a = a.Left(a.GetLength() - 2) + b;
   ShowMsg(a);
  }
  else if (a.Right(1) == "(")
  {
   ShowMsg(a);
  }
  else
  {
   CString b(")");
   a = a + b;
   count1--;
   ShowMsg(a);
  }
 }
 else
  ShowMsg(a);
}

//计算
int p = 0;
stack<int> stack1;
stack<char> stack2;
char c[20];

void get(char a[20])//获取数字和符号
{
 int sum = 0;
 bool f = false;
 while ('0' <= a[p] && a[p] <= '9')
 {
  sum = sum * 10 + a[p] - '0';
  p++;
  f = true;
 }
 if (f)
 {
  char j;
  j = sum;
  c[0] = j;
 }
 else
 {
  p++;
  c[0] = a[p - 1];
  if (c[0] == '&' || c[0] == '|')
   p++;
 }
}

int priority(char x)//优先级
{
 int pr = (int)x;
 switch (pr)
 {
 case(47):return 1; break;
 case(42):return 1; break;
 case(37):return 1; break;
 case(43):return 2; break;
 case(45):return 2; break;
 case(40):return 3; break;
 case(38):return 2; break;
 case(124):return 2; break;
 case(33):return 1; break;
 }
}

void count()
{
 char x;
 x = stack2.top();
 stack2.pop();
 int pr = (int)x;
 int answer = 0;
 if (pr == 33)
 {
  int a1;
  a1 = stack1.top();
  stack1.pop(); 
  if (a1 == 0)
   answer = 1;
  else
   answer = 0;
 }
 else
 {
  
  int a1, a2;
  a1 = stack1.top();
  stack1.pop();
  a2 = stack1.top();
  stack1.pop();
  switch (pr)
  {
  case(38):answer = a2 && a1; break;
  case(124):answer = a2 || a1; break;
  case(47):answer = a2 / a1; break;
  case(42):answer = a1 * a2; break;
  case(37):answer = a2 % a1; break;
  case(43):answer = a1 + a2; break;
  case(45):answer = a2 - a1; break;
  }
 }
 stack1.push(answer);
}

void CStringToChar(CString str, char ch[]) 
{ 
 char* tmpch; 
    int wLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL); 
    tmpch = new char[wLen + 1];
 WideCharToMultiByte(CP_ACP, 0, str, -1, tmpch, wLen, NULL, NULL); 
 for (int i = 0; i < wLen; ++i)
  ch[i] = tmpch[i]; 
}

bool fu(CString a)//查（）
{
 for (int i = 0; i < a.GetLength(); i++)
 {
  if (a.Mid(i, 1) == "+"|| a.Mid(i, 1) == "-" || a.Mid(i, 1) == "*" || a.Mid(i, 1) == "/" || a.Mid(i, 1) == "%" || a.Mid(i, 1) == "(" || a.Mid(i, 1) == ")"||a.Mid(i, 1) == "&" || a.Mid(i, 1) == "|" || a.Mid(i, 1) == "!")
   return false;
 }
 return true;
}

bool fo(CString a)//负数打头
{
 for (int i = 0; i < a.GetLength(); i++)
 {
   while (a.Left(1) == "("&&a.Right(1) == ")")
   {
    a = a.Left(a.GetLength() - 1);
    a = a.Right(a.GetLength() - 1);
   }
   if (a.Mid(0, 1) == "-")
   {
    i = 1;
    for (i; i < a.GetLength(); i++)
    {
     if (a.Mid(i, 1) == "+" || a.Mid(i, 1) == "-" || a.Mid(i, 1) == "*" || a.Mid(i, 1) == "/" || a.Mid(i, 1) == "%" || a.Mid(i, 1) == "&" || a.Mid(i, 1) == "|" || a.Mid(i, 1) == "!")
      return false;
    }
    return true;
   }
   if (a.Mid(i, 1) == "+" || a.Mid(i, 1) == "-" || a.Mid(i, 1) == "*" || a.Mid(i, 1) == "/" || a.Mid(i, 1) == "%" || a.Mid(i, 1) == "&" || a.Mid(i, 1) == "|" || a.Mid(i, 1) == "!")
    return false;
 }
 return true;
}

void CMFCApplication1Dlg::OnBnClickedButton18()//=
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();//计算
 if (count1 != 0)
 {
  CString b("=error");
  a = a + b;
  ShowMsg(a);
 }
 else
 {
  if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "(" || a.Right(1) == "&" || a.Right(1) == "|" || a.Right(1) == "!")
   ShowMsg(a);
  else
  {
   CString d("=");
   if (fu(a))
   {
    a = a + d + a;
    ShowMsg(a);
   }
   else if (fo(a))
   {
    CString b = a;
    while (a.Left(1) == "("&&a.Right(1) == ")")
    {
     a = a.Left(a.GetLength() - 1);
     a = a.Right(a.GetLength() - 1);
    }
    if (a.Mid(0, 1) == "-")
    {
     while (a.Mid(1,1) == "("&&a.Right(1) == ")")
     {
      CString e("-");
      a = e + a.Right(a.GetLength() - 2);
      a = a.Left(a.GetLength() - 1);
     }
    }
    if (a == "-0")
     a = a.Right(1);
    a = b + d + a;
    ShowMsg(a);
   }
   else
   {
    a = a + d;
    char b[20];
    int answer;
    CStringToChar(a, b);
    get(b);
    while (*c == '(')
    {
     stack2.push(c[0]);
     get(b);
    }
    if (*c == '-')
    {
     stack1.push(0);
     stack2.push(c[0]);
    }
    else if (*c == '!')
    {
     stack2.push(c[0]);
    }
    else
    {
     stack1.push(c[0] - '0' + 48);
     get(b);
     stack2.push(c[0]);
    }
    get(b);
    while (*c != '=')
    {
     if (*c != '+'&&*c != '-'&&*c != '*'&&*c != '/'&&*c != '%'&&*c != '('&&*c != ')'&&*c != '&'&&*c != '|'&&*c != '!')
     {
      stack1.push(c[0] - '0' + 48);
     }
     else
     {
      char x;
      if (stack2.empty())
      {
       stack2.push(c[0]);
      }
      else
      {
       x = stack2.top();
       if (*c == '(')
       {
        stack2.push(c[0]);
       }
       else if (*c == ')')
       {
        while (x != '(')
        {
         count();
         x = stack2.top();
        }
        stack2.pop();
       }
       else if (*c == '!')
       {
        stack2.push(c[0]);
       }
       else
       {
        if (priority(x) > priority(*c))
        {
         stack2.push(c[0]);
        }
        else
        {
         count();
         if (!stack2.empty())
         {
          x = stack2.top();
          if (priority(x) <= priority(*c))
           count();
         }
         stack2.push(c[0]);
        }
       }
      }
     }
     get(b);
    }
    while (!stack2.empty())
     count();
    answer = stack1.top();
    while (!stack1.empty())
     stack1.pop();
    d.Format(_T("%d"), answer);
    p = 0;
    a = a + d;
    ShowMsg(a); 
   }
  }
 }
}

void CMFCApplication1Dlg::OnBnClickedButton19()//C//清空
{
 // TODO: 在此添加控件通知处理程序代码
 ShowMsg(_T(""));
 count1 = 0;
}

void CMFCApplication1Dlg::OnBnClickedButton20()//<X//退格
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 if (a.GetLength() == 1|| a.GetLength() == 0)
 {
  count1 = 0;
  ShowMsg(_T(""));
 }
 else if (a == "0")
 {
  count1 = 0;
  ShowMsg(_T("0"));
 }
 else if (a.Right(1) == "&" || a.Right(1)=="|")
 {
  a = a.Left(a.GetLength() - 2);
  ShowMsg(a);
 }
 else
 {
  if (a.Right(1) == "(")
   count1--;
  if (a.Right(1) == ")")
   count1++;
  a = a.Left(a.GetLength() - 1);
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton21()//&
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%"|| a.Right(1) == "!")
 {
  CString b("&&");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("&&");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("&&");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("&&");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1--;
 }
 else
 {
  CString b("&&");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton22()//||
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "+" || a.Right(1) == "-" || a.Right(1) == "*" || a.Right(1) == "/" || a.Right(1) == "%" || a.Right(1) == "!")
 {
  CString b("||");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "&" || a.Right(1) == "|")
 {
  CString b("||");
  a = a.Left(a.GetLength() - 2) + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "")
 {
  CString b("||");
  CString c("0");
  a = c + b;
  ShowMsg(a);
 }
 else if (a.Right(1) == "(")
 {
  CString b("||");
  a = a.Left(a.GetLength() - 1) + b;
  ShowMsg(a);
  count1--;
 }
 else
 {
  CString b("||");
  a = a + b;
  ShowMsg(a);
 }
}

void CMFCApplication1Dlg::OnBnClickedButton23()//!
{
 // TODO: 在此添加控件通知处理程序代码
 CString a = GetMsg();
 a = qufu(a);
 if (a.Right(1) == "")
 {
  CString b("!");
  a = b;
  ShowMsg(a);
 }
 else
 {
  CString b("!");
  a = a + b;
  ShowMsg(a);
 }
}
