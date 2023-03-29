#pragma once

#include<iostream>
#include<string>
#include<cmath>
#include<ctype.h>
#include<algorithm>
#include<map>
#include<set>
#include<list>
#include<vector>
#include<stack>
#include<queue>
#include<strstream>
#include<fstream>
const int N = 9999999;
using namespace std;
//bool assign_flag = 1;
enum Data_type { INT, CHAR };//��ΪҪ�������a~z���������� 
struct Data
{
    Data_type datatag;
    union
    {
        int num;
        char c;
    };
};
struct binarynode   //���Ľڵ� 
{
    Data element;
    binarynode* lchild, * rchild;
    binarynode()
    {
        lchild = rchild = NULL;
    }
    binarynode(const Data& e)
    {
        element = e;
        lchild = rchild = NULL;
    }
    binarynode(const Data& e, binarynode* l, binarynode* r)
    {
        element = e;
        lchild = l;
        rchild = r;
    }
};
class binarytree//Ϊ�˵ݹ����is_all_assigned,inborder,preorder����Ҫ�������
{
private:
    bool assign_flag = 1;
    binarynode* root;
    int size;
    bool isoperator(char op)
    {
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
            return true;
        else
            return false;
    }
    bool pricmp(char a, char b){//�жϷ������ȼ� a<b true
         
        if (isoperator(a) && isoperator(b))
        {
            if (a == '^')
            {
                if (b == '^') return true;
                else return false;
            }
            else if (a == '*' || a == '/')
            {
                if (b == '*' || b == '/' || b == '^')return false;
                else return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    void maketree(const Data& e, binarytree& l, binarytree& r){
        root = new binarynode(e, l.root, r.root);
        size = l.size + r.size;
        l.root = r.root = NULL;
        l.size = r.size = 0;
    }
    bool judge_type(/*binarynode p,*/char c)//���ַ���1����ĸ����0
    {
        if (isdigit(c))
        {
            root->element.datatag = INT;
            root->element.num = c - '0';
            return 1;
        }
        else
        {
            root->element.datatag = CHAR;
            root->element.c = c;
            return 0;
        }
    }
    void is_all_assigned(binarynode* r)//�����ʽ�еı����Ƿ�ȫ����ֵ
    {
        if (r != NULL && r->element.datatag == CHAR)
        {
            //cout << r->element.c << " ";
            //isalpha(r->element.c)
            if (r->element.c!='+'&& r->element.c != '-'&&r->element.c != '*'&& r->element.c != '/'&& r->element.c != '^')
            {
                cout << "����" << r->element.c << "δ��ֵ" << endl;
                assign_flag = 0;
                return;
            }
            is_all_assigned(r->lchild);
            is_all_assigned(r->rchild);
        }
    }
    int calculate(int a, char op, int b)
    {
        if (op == '+')
            return a + b;
        else if (op == '-')
            return a - b;
        else if (op == '*')
            return a * b;
        else if (op == '/')
        {
            if (b == 0)
            {
                cout << "��������Ϊ0��" << endl;
                return N;
            }
            else
                return a / b;
        }
        else if (op == '^')
            return pow(a, b);
    }
public:
    void preorder_output()
    {
        cout << "ǰ׺���ʽ��" << endl;
        preorder(root);
        cout << endl;
    }
    void preorder(binarynode* r){
        if (r != NULL)
        {
            if (r->element.datatag == INT)
                cout << r->element.num;
            else
                cout << r->element.c;
            preorder(r->lchild);
            preorder(r->rchild);
        }
    }
    void inorderbacket_output()
    {
        cout << "��ȫ���Ż�����׺���ʽ��";
        inorder_allbacket(root);
        cout << endl;
    }
    void inorder_allbacket(binarynode* r)
    {
        if (r != NULL)
        {
            cout << "(";
            inorder_allbacket(r->lchild);
            if (r->element.datatag == INT)
                cout << r->element.num;
            else
                cout << r->element.c;
            inorder_allbacket(r->rchild);
            cout << ")";
        }
    }
    void WriteExpr()
    {
        cout << "�����ŵ���׺���ʽ��";
        writeexpr(root);
        cout << endl;
    }
    void writeexpr(binarynode* r)
    {
        if (r != NULL)
        {
            if (r->lchild && r->lchild->element.datatag == CHAR)
            {
                if (pricmp(r->element.c, r->lchild->element.c))//��ǰ�ڵ����ȼ���������
                {
                    cout << "(";
                    writeexpr(r->lchild);
                    cout << ")";
                }
                else
                    writeexpr(r->lchild);
            }
            else
                writeexpr(r->lchild);

            if (r->element.datatag == INT)
                cout << r->element.num;
            else
                cout << r->element.c;

            if (r->rchild && r->rchild->element.datatag == CHAR)
            {
                if (pricmp(r->element.c, r->rchild->element.c))
                {
                    cout << "(";
                    writeexpr(r->rchild);
                    cout << ")";
                }
                else
                    writeexpr(r->rchild);
            }
            else
                writeexpr(r->rchild);
        }
    }
    bool ReadExptr(string str)
    {
        stack<binarynode*> s;
        //stack<int> nums;
        binarynode p, q;
        int len = str.length();
        root = new binarynode;
        root->lchild = root->rchild = NULL;
        if (len == 1)
        {
            if (isdigit(str[0]))//���� 
            {
                root->element.datatag = INT;
                root->element.num = str[0] - '0';
                return true;
            }
            else if (isalpha(str[0]))//��ĸ 
            {
                root->element.datatag = CHAR;
                root->element.c = str[0];
                return true;
            }
            else
            {
                cout << "�Ƿ����룡" << endl;
                return false;
            }
        }
        else
        {
            for (int i = len - 1; i >= 0; i--)
            {
                binarynode* pnode = new binarynode;
                if (isdigit(str[i]))
                {
                    pnode->element.datatag = INT;
                    pnode->element.num = str[i] - '0';
                }
                else
                {
                    //cout << str[i] << " ";
                    pnode->element.datatag = CHAR;
                    pnode->element.c = str[i];
                }
                pnode->lchild = NULL; pnode->rchild = NULL;

                /*if (isdigit(str[i]))
                    nums.push(str[i] - '0');*/
                if (isoperator(str[i]))
                {
                    pnode->lchild = s.top(); s.pop();
                    pnode->rchild = s.top(); s.pop();
                }
                s.push(pnode);
            }
            root = s.top();
            s.pop();//�������յĽ�����ʽ
            if (s.empty())//��s��Ϊ�գ�����ɹ�
                return true;
            else//��s�л��ж���������ʧ��
            {
                cout << "ERROR!!!" << endl;
                return false;
            }
        }
    }
    void assign(binarynode* r, char v, int& num)
    {
        if (r != NULL)
        {
            if (r->element.datatag == CHAR && r->element.c == v)
            {
                //cout << r->element.c << "=" << v << "=" << num;
                r->element.datatag = INT;
                r->element.num = num;

                //�������봦���޸�numֵΪN��֮������ �ж��Ƿ�ɹ���ֵ��
                num = N;
            }
            assign(r->lchild, v, num);
            assign(r->rchild, v, num);
        }
    }
    void Assign(char v, int num)
    {
        assign(root, v, num);
        if (num != N)
            cout << "����δ�ɹ���ֵ������������ʽ�в����ڵı�����" << endl;
    }
    int Value(binarynode* r)
    {
        if (r != NULL)
        {
            if (r->lchild == NULL && r->rchild == NULL && r->element.datatag == INT)//����ײ�
                return r->element.num;
            return calculate(Value(r->lchild), r->element.c, Value(r->rchild));
        }
    }
    void Value_output()
    {
        //cout <<"assign="<< assign_flag << endl;
        is_all_assigned(root);
        //cout<<"assign=" << assign_flag << endl;
        if (assign_flag)//ȫ��ֵ
        {
            writeexpr(root); cout << "=";
            cout << Value(root) << endl;
        }
        else
        {
            cout << "����δ��ֵ�ı������޷�������ʽ��ֵ��" << endl;
            assign_flag = 1;
        }
    }
    void CompoundExpr(char p, binarytree a, binarytree b)
    {
        root = new binarynode;
        root->element.datatag = CHAR;
        root->element.c = p;
        root->lchild = a.root;
        root->rchild = b.root;
        cout << "���ϱ��ʽ��";
        writeexpr(root);
        cout << endl;
    }
    void mergeconst(binarynode* r)
    {
        if (r->lchild != NULL && r->rchild != NULL)
        {
            if (r->lchild->element.datatag == INT && r->rchild->element.datatag == INT)
            {
                int ans = calculate(r->lchild->element.num, r->element.c, r->rchild->element.num);
                r->element.datatag = INT;
                r->element.num = ans;
                delete r->lchild;
                delete r->rchild;
                r->lchild = r->rchild = NULL;
            }
            else
            {
                mergeconst(r->lchild);
                mergeconst(r->rchild);
            }
        }
    }
    void MergeConst()
    {
        mergeconst(root);
        writeexpr(root);
        cout << endl;
    }

};
int main(){
    binarytree tree;
    string s;
    getline(cin,s);
    tree.ReadExptr(s);
    tree.WriteExpr();
}


