#include <stdlib.h>
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
#include <sstream>
const int N = 9999999;
using namespace std;
enum Data_type { INT, CHAR };//因为要输入的是a~z或者是数字 
struct Data
{
    Data_type datatag;
    union
    {
        int num;
        char c;
    };
};
struct binarynode   //树的节点 
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
class binarytree//为了递归调用is_all_assigned,inborder,preorder都需要传入参数
{
private:
    bool assign_flag = 1;
    binarynode* root;
    int size;
    bool isoperator(char op)//判断是不是符号
    {
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
            return true;
        else
            return false;
    }
    bool pricmp(char a, char b){//判断符号优先级 a<b true
         
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
    bool judge_type(char c)//数字返回1，字母返回0
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
    void is_all_assigned(binarynode* r)//检查表达式中的变量是否全部赋值
    {
        if (r != NULL && r->element.datatag == CHAR)
        {
            if (r->element.c!='+'&& r->element.c != '-'&&r->element.c != '*'&& r->element.c != '/'&& r->element.c != '^')
            {
                cout << "变量" << r->element.c << "未赋值" << endl;
                assign_flag = 0;
                return;
            }
            is_all_assigned(r->lchild);
            is_all_assigned(r->rchild);
        }
    }
    int calculate(int a, char op, int b)//计算步骤
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
                cout << "除数不能为0！" << endl;
                return N;
            }
            else
                return a / b;
        }
        else if (op == '^')
            return pow(a, b);
    }
public:
    void preorder_output()//输出前缀表达式
    {
        cout << "前缀表达式：" << endl;
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
        cout << "完全括号化的中缀表达式：";
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
        cout << "带括号的中缀表达式："<<endl;
        writeexpr(root);
        cout << endl;
    }
    void writeexpr(binarynode* r)
    {
        if (r != NULL)
        {
            if (r->lchild && r->lchild->element.datatag == CHAR)
            {
                if (pricmp(r->element.c, r->lchild->element.c))//当前节点优先级高于左孩子
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
        binarynode p, q;
        int len = str.length();
        root = new binarynode;
        root->lchild = root->rchild = NULL;
        if (len == 1)
        {
            if (isdigit(str[0]))//数字 
            {
                root->element.datatag = INT;
                root->element.num = str[0] - '0';
                return true;
            }
            else if (isalpha(str[0]))//字母 
            {
                root->element.datatag = CHAR;
                root->element.c = str[0];
                return true;
            }
            else
            {
                cout << "非法输入！" << endl;
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
                    pnode->element.datatag = CHAR;
                    pnode->element.c = str[i];
                }
                pnode->lchild = NULL; pnode->rchild = NULL;
                if (isoperator(str[i]))
                {
                    pnode->lchild = s.top(); s.pop();
                    pnode->rchild = s.top(); s.pop();
                }
                s.push(pnode);
            }
            root = s.top();
            s.pop();//弹出最终的结果表达式
            if (s.empty())//若s中为空，则构造成功
                return true;
            else//若s中还有东西，则构造失败
            {
                cout << "ERROR!!!" << endl;
                return false;
            }
        }
    }
    int assignflag=0;
    void assign(binarynode* r, char v, int& num)
    {
        if (r != NULL)
        {
            if (r->element.datatag == CHAR && r->element.c == v)
            {
                r->element.datatag = INT;
                r->element.num = num;
                assignflag=1;
            }
            assign(r->lchild, v, num);
            assign(r->rchild, v, num);
        }
    }
    void Assign(char v, int num)
    {
        assign(root, v, num);
        if (assignflag!=1)
            cout << "本次未成功赋值，请勿输入表达式中不存在的变量。" << endl;
    }
    int Value(binarynode* r)
    {
        if (r != NULL)
        {
            if (r->lchild == NULL && r->rchild == NULL && r->element.datatag == INT)//到达底层
                return r->element.num;
            return calculate(Value(r->lchild), r->element.c, Value(r->rchild));
        }
    }
    void Value_output()
    {
        //cout <<"assign="<< assign_flag << endl;
        is_all_assigned(root);
        //cout<<"assign=" << assign_flag << endl;
        if (assign_flag)//全赋值
        {
            writeexpr(root); cout << "=";
            cout << Value(root) << endl;
        }
        else
        {
            cout << "含有未赋值的变量，无法计算表达式的值！" << endl;
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
        cout << "复合表达式：";
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
void Diff(string s,char x){
    for(int i=0;i<s.size();++i){
        if(s[i]==x&&i==s.size()-1){
            s.erase(s.size()-2,2);
        }
        else if(s[i-1]==x&&s[i]=='^'){
            int find1=i+1;
            int chengshu=s[find1]-'0';
            s[find1]--;
            int find2=i-1;
            while(find2>=0){
                if(s[find2]>'0'&&s[find2]<'9'){
                    int beicheng=s[find2]-'0';
                    int sum=chengshu*beicheng;
                    string x=to_string(sum);
                    s.replace(find2,1,x);                    
                }
                find2--;
            }
        }
        else if(s[i-1]==x&&s[i]!='^'){
            s.erase(i-2,2);
        }
        
        
    }
    for(int i=0;i<s.size();++i){
        cout<<s[i];
    }
}
int main(){
    binarytree tree2;
    binarytree tree1;
    string s1;
    cout<<"构造第一个表达式"<<endl;
    cout<<"请输入前缀表达式"<<endl;
    getline(cin,s1);
    tree1.ReadExptr(s1);
    tree1.WriteExpr();
    cout<<"合并常数运算后的"<<endl;
    tree1.MergeConst();
    cout<<"请选择要进行的操作"<<endl;
    cout<<"1、求偏导"<<endl;
    cout<<"2、复合函数"<<endl;
    cout<<"3、赋值并且求值"<<endl;
    int judge=0;
    cin>>judge;
    if(judge==1){
        cout<<"请再输入一遍运算公式"<<endl;
        string s3;
        cin>>s3;
        cout<<"关于什么求偏导"<<endl;
        char symbol;
        cin>>symbol;
        Diff(s3,symbol);
    }
    else if(judge==2){
        cout<<"请输入第二个前缀表达式"<<endl;
        string s2;
		cin>>s2;
        tree2.ReadExptr(s2);
        cout<<"请输入计算符"<<endl;
        char p;
        cin>>p;
        tree1.CompoundExpr(p,tree1,tree2);
    }
    else if(judge==3){
        cout<<"请输入要赋值的字母和值,第一个数字为总数"<<endl;
        int n;
        cin>>n;
        char a[1000];
        int b[1000];
        for(int i=0;i<n;++i){
            cin>>a[i];
            cin>>b[i];
            tree1.Assign(a[i],b[i]);
        }
        tree1.Value_output();
    }    
    return 0;
}
