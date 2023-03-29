#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include<ctime>
#include<cstdlib>
#include <fstream>
using namespace std;
#define HASH_SIZE 50 //哈希表的长度
#define Name_SIZE 30 //名字表长度
#define modenum 49         
struct Name
{
    string name; //姓名
    int ascii;   //对应的ascii码和
};
struct my_hash
{
    string name; //姓名
    int ascii;   //对应ASCII码和
    int s;       //查找长度
};
Name NameList[Name_SIZE];
my_hash hashtable[HASH_SIZE];

void init_Namelist()
{
/*    cout<<"请输入30位同学的姓名"<<endl;
    for(int i=0;i<30;++i){
        string st;
        cin>>st;
        NameList[i].name=st;
    }*/
    ifstream myfile("data.txt");
    for(int i=0;i<30;++i){
        string st;
        myfile>>st;
        NameList[i].name=st;
    }
    for (int i = 0; i < Name_SIZE; i++)
    {
        for (int j = 0; j < NameList[i].name.size(); j++)
        {
            NameList[i].ascii += toascii(NameList[i].name[j]);
        }
    }
}
void collison(int i)//线性探测处理冲突
{
    int key, flag;
    flag = 0; 
    key = (NameList[i].ascii) % modenum;
    while (hashtable[key].s != 0)
    {
        key = key + 1; 
        if (key == HASH_SIZE - 1)
        { 
            key = 0;
            flag = 1; 
        }
    }
    if (hashtable[key].s == 0)
    {
        hashtable[key].name = NameList[i].name;
        hashtable[key].ascii = NameList[i].ascii;
        if (flag == 0)
            hashtable[key].s = (key - (NameList[i].ascii % modenum)) + 1;
        else
            hashtable[key].s = (HASH_SIZE - (NameList[i].ascii % modenum)) + key + 1;                                                                                        //查找次数
    }
}
void collison_pingfang(int i)//平方探测处理冲突
{
    int key, flag;
    flag = 0; 
    int k=1;
    key = (NameList[i].ascii) % modenum;
    while (hashtable[key].s != 0)
    {
        key = key + k^2; 
        if (key >= HASH_SIZE - 1)
        { 
            key = key-HASH_SIZE+1;
            flag = 1; 
        }
    }
    if (hashtable[key].s == 0)
    {
        hashtable[key].name = NameList[i].name;
        hashtable[key].ascii = NameList[i].ascii;
        if (flag == 0)
            hashtable[key].s = (key - (NameList[i].ascii % modenum)) + 1;
        else
            hashtable[key].s = (HASH_SIZE - (NameList[i].ascii % modenum)) + key + 1;                                                                                        //查找次数
    }
}
double random(double start,double end)
{
    return start + (end - start) * rand() / (RAND_MAX + 1.0);
}
void collision_suiji(int x){     // 伪随机序列处理冲突
    int key = (NameList[x].ascii) % modenum;
    int temp=1;
    while (hashtable[key].s != 0)
    {
        key = key + random(-key,HASH_SIZE-1-key); 
        temp+=1;
    }
    if (hashtable[key].s == 0)
    {
        hashtable[key].name = NameList[x].name;
        hashtable[key].ascii = NameList[x].ascii;
        hashtable[key].s = temp;                   
    }
}
void init_hash(){
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i].name = "\0";
        hashtable[i].ascii = 0;
        hashtable[i].s = 0; //初始化哈希表
    }
}
void Create_hash(int type) //创建哈希函数
{
    int key;
    init_hash();
    for (int i = 0; i < Name_SIZE; i++)
    {
        key = (NameList[i].ascii) % modenum; //除留余数法
        if (hashtable[key].s == 0)     //未发生冲突
        {
            hashtable[key].name = NameList[i].name;
            hashtable[key].ascii = NameList[i].ascii;
            hashtable[key].s = 1;
        }
        else{
            if(type==1){
                collison(i);
            }
            else if(type==2){
                collision_suiji(i); //调用冲突函数
            }
            else if(type==3){
                collison_pingfang(i);
            }
        }                         
    }
}
void menu()
{
    cout<<"哈希表创建成功"<<endl;
    cout<<"1、输出姓名序列"<<endl;
    cout<<"2、输出哈希表序列"<<endl;
    cout<<"3、退出"<<endl;
    cout<<"请输入你的选择："<<endl;
}
void print_Namelist()
{
    for (int i = 0; i < Name_SIZE; i++)
    {
        cout << "序号:" << i << "\t"<< "姓名:" << NameList[i].name << "\t"<< "ascii:" << NameList[i].ascii << endl;
    }
}
void print_hash()
{
    float ASL = 0.0; //平均查找长度
    for (int i = 0; i < HASH_SIZE; i++)
    {
        cout << "序号:" << i << "\t\t"<< "姓名:" << hashtable[i].name << "\t\t"<< "ascii:" << hashtable[i].ascii << "\t\t"<<"查找长度:"<<hashtable[i].s<<endl;
        ASL += hashtable[i].s;
    }
    ASL = ASL / Name_SIZE;
    cout<<"平均查找长度为："<<ASL<<endl;
}
int main()
{
    init_Namelist();
    while (1)
    {                
        cout<<"请输入采用哪种方式处理冲突"<<endl;
        cout<<"1、线性探测"<<endl;
        cout<<"2、伪随机数探测"<<endl;
        cout<<"3、平方探测"<<endl;
        cout<<"请输入你的选择（数字）："<<endl;
        int type;
        cin>>type;
        Create_hash(type);
        menu();
        int choice;
        cin>>choice;
        switch (choice)
        {
        case 1:
            print_Namelist();
            break;
        case 2:
            print_hash();
            break;
        case 3:
            break;
        default: 
            cout<<"请勿选择没有的选项"<<endl;
            break;
        }
    }
    return 0;
}
