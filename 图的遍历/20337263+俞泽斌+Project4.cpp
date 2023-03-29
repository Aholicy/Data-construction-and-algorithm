#include <iostream>
#include <string>
#include<string.h>
#include<queue>
#include<stack>
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 30
#define NULL 0
#define OK 1
using namespace std;
bool visit[MAX_VERTEX_NUM];
typedef struct ArcNode //定义边结点
{
    int adjvex;
    ArcNode *nextarc;
} ArcNode;
typedef struct VNode //定义顶点结点
{
    string data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct //定义无向图
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;
typedef struct node //定义结点
{
    int data;
    node *next;
} * Link;
typedef struct //定义链表
{
    Link head, tail;
    int len;
} LinkList;
typedef struct CSNode{
    string data;
    struct CSNode * lchild;//孩子结点
    struct CSNode * nextsibling;//兄弟结点
}*CSTree,CSNode;
int InitList(LinkList &L) //构造一个带头结点和尾结点的空的线性链表L
{
    L.head = new node;
    L.head->next = L.tail = new node;
    L.tail->next = NULL;
    L.len = 0;
    return 0;
}
void add(LinkList &L, int e) //在线性链表L的结尾添加一个结点
{
    Link q = new node;
    L.tail->next = q;
    L.tail->data = e;
    L.tail = q;
    L.tail->next = NULL;
    L.len++;
}
void Delete(LinkList &L, int &e) //出列，并将出列的元素值用e返回
{
    if (L.head->next == L.tail)
    {
        cout << "队列为空" << endl;
        e = NULL;
    }
    else
    {
        Link p, q;
        p = L.head->next;
        q = p->next;
        L.head->next = q;
        e = p->data;
        delete p;
        L.len--;
    }
}
void ArcAdd(ALGraph &G, int m, int n) //在无向图中添加以m,n为顶点的边
{
    ArcNode *p, *h, *q;
    p = new ArcNode;
    p->adjvex = m;
    p->nextarc = NULL;
    h = q = G.vertices[n].firstarc;
    if (q == NULL)
        G.vertices[n].firstarc = p;
    else
    {
        if ((p->adjvex) > (q->adjvex))
        {
            p->nextarc = q;
            G.vertices[n].firstarc = p;
        }
        else
        {
            while (G.vertices[n].firstarc != NULL && q->nextarc != NULL && (p->adjvex) < (q->adjvex)) //使邻接表中边的数据按大到小排列。
            {
                h = q;
                q = q->nextarc;
            }
            if (q->nextarc == NULL && (p->adjvex) < (q->adjvex))
            {
                q->nextarc = p;
            }
            else
            {
                p->nextarc = q;
                h->nextarc = p;
            }
        }
    }
}
int CreateDG(ALGraph &G) //创建无向图
{
    int v, a, m, n;
    ArcNode *p, *q, *h;
    cout << "请输入顶点个数和边数." << endl;
    cout << "请输入顶点数:";
    cin >> v;
    cout << "请输入边数:";
    cin >> a;
    G.vexnum = v;
    G.arcnum = a;
    for (int i = 1; i <= G.vexnum; i++)
    {
        string t;
        cout << "请输入顶点值:";
        cin >> t;
        G.vertices[i].data = t;
        G.vertices[i].firstarc = NULL;
    }
    for (int k = 1; k <= G.arcnum; k++)
    {
        cout << "请输入边的信息." << endl;
        cout << "请输入第" << k << "条边的起点和终点:";
        cin >> m;
        cin >> n;
        if (m <= v && n <= v && m > 0 && n > 0)
        {
            ArcAdd(G, m, n);
            ArcAdd(G, n, m);
        }
        else
        {
            cout << "你的输入有误." << endl;
            return 0;
        }
    }
    return 0;
}
void show(ALGraph G) //在屏幕上输入无向图的邻接表存储形式
{
    cout << "无向图的创建完成,该图的邻接表表示为:" << endl;
    ArcNode *p;
    for (int i = 1; i <= G.vexnum; i++)
    {
        if (G.vertices[i].firstarc == NULL)
            cout << i << G.vertices[i].data << "-->NULL" << endl;
        else
        {
            p = G.vertices[i].firstarc;
            cout << i << G.vertices[i].data << "-->";
            while (p->nextarc != NULL)
            {
                cout << G.vertices[p->adjvex].data << "-->";
                p = p->nextarc;
            }
            cout << G.vertices[p->adjvex].data << "-->NULL" << endl;
        }
    }
}
void VisitFunc(string a) //对无向图的数据进行访问的函数
{
    cout << a << " ";
}
int FirstAdjVex(ALGraph G, int v) //返回v的第一个邻接顶点。若顶点在G中没有邻接表顶点，则返回“空”。
{
    if (G.vertices[v].firstarc)
        return G.vertices[v].firstarc->adjvex;
    else
        return NULL;
}
int NextAdjVex(ALGraph G, int v, int w) //返回v的（相对于w的）下一个邻接顶点。若w是v的最后一个邻接点，则返回“空”。
{
    ArcNode *p;
    if (G.vertices[v].firstarc == NULL)
        return NULL;
    else
    {
        p = G.vertices[v].firstarc;
        while (p->adjvex != w)
        {
            p = p->nextarc;
        }
        if (p->nextarc == NULL)
            return NULL;
        else
            return p->nextarc->adjvex;
    }
}
void DFS(ALGraph G, int v) //从第v个顶点出发递归地深度优先遍历图G。
{
    visit[v] = true;
    VisitFunc(G.vertices[v].data);
    for (int w = FirstAdjVex(G, v); w >= 1; w = NextAdjVex(G, v, w))
        if (!visit[w])
            DFS(G, w);
}
void DFSTraverse(ALGraph G) //对图G作深度优先遍历。
{
    cout << "深度优先搜索的结果为:" << endl;
    for (int v = 1; v <= G.vexnum; v++)
        visit[v] = false;
    for (int m = 1; m <= G.vexnum; m++){
        if (!visit[m])
            DFS(G, m);
    
    }
    cout << endl;    
        
}
void DFS2(ALGraph G, int i)
{
    bool visited[MAX_VERTEX_NUM];
	stack<int> s;
	visited[i] = true; // 表示该点已经访问过
	cout << G.vertices[i].data << " ";
	s.push(i);
	while (!s.empty())
	{ // 栈不为空
		int tmp = s.top(); // 取栈顶元素
		ArcNode* p = G.vertices[tmp].firstarc;
		// 在序号为tmp顶点的边表中找未被访问过的顶点
		while (p && visited[p->adjvex])
		{
			p = p->nextarc;
		}
		if (!p) s.pop(); // 没找到，则说明该顶点对应的边表遍历完了，弹出该顶点
		else {
			s.push(p->adjvex);
			cout << G.vertices[p->adjvex].data << " ";
			visited[p->adjvex] = true;
		}
	}
}

int visited[MAX_VERTEX_NUM];
string GetVex(ALGraph G,int v)
{
    return G.vertices[v].data;
}

void DFSTree(ALGraph G,int v,CSTree &T)
{
    int w,first;
    CSTree p,q;
    ArcNode *temp;
    visited[v]=1;
    first = 1;
    for (int w = FirstAdjVex(G, v); w >= 1; w = NextAdjVex(G, v, w)){
        if(visited[w]==0)
        {
            p=new CSNode();
            p->data=GetVex(G,w);  

            p->lchild=NULL;
            p->nextsibling=NULL;
            if(first)
                {T->lchild=p;first=0;}
            else
                q->nextsibling=p;
            q=p;
            DFSTree(G,w,q);
        }
        
    }
}

void DFSForest(ALGraph G,CSTree &T)
{
    int v;
    CSTree p,q;
    T=NULL;
    for(v=1;v<=G.vexnum;v++)
        visited[v]=0;
    for(v=1;v<=G.vexnum;v++)
    {
        if(!visited[v])
        {
            p=new CSNode();
            p->data=GetVex(G,v);
            p->lchild=NULL;
            p->nextsibling=NULL;
            if(!T) T=p;
            else    q->nextsibling=p;
            q=p;
            DFSTree(G,v,p);
        }
    }
}

void PreOrderTraverse(CSTree &T)  
{
    if(T==NULL)   return;
    else cout<<T->data<<" ";
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->nextsibling); 
}
void InOrderTraverse(CSTree &T)  
{
    if(T==NULL)   return;
    else cout<<T->data<<" ";
    
    PreOrderTraverse(T->nextsibling); 
    PreOrderTraverse(T->lchild);
}
void showTR(CSTree &T)
{
    if (T)
    {
        cout << T->data;
        if (T->lchild)
        {
            cout << "(";
            CSNode *p = T->lchild;
            showTR(p);
            p = p->nextsibling;
            while (p)
            {
                cout << ",";
                showTR(p);
                p = p->nextsibling;
            }
            cout << ")";
        }
    }
}


void BFSTraverse(ALGraph G) //对图G作广度优先遍历。
{
    cout << "广度优先搜索的结果为:" << endl;
    LinkList Q;
    int u;
    for (int m = 1; m <= G.vexnum; m++)
        visit[m] = false;
    InitList(Q); //借助辅助队列。
    for (int v = 1; v <= G.vexnum; v++)
        if (!visit[v])
        {
            visit[v] = true;
            VisitFunc(G.vertices[v].data);
            add(Q, v);
            while (Q.len != 0)
            {
                Delete(Q, u);
                for (int w = FirstAdjVex(G, u); w >= 1; w = NextAdjVex(G, u, w))
                    if (!visit[w])
                    {
                        visit[w] = true;
                        VisitFunc(G.vertices[w].data);
                        add(Q, w);
                    }
            }
        }
    cout << endl;
}

void BFSTree(ALGraph G,int v,CSTree T){
    CSTree q=NULL;
    queue<CSTree>Q;
    Q.push(T);
    while (!Q.empty()) {
        bool first=true;
        q=new CSNode();
        q=Q.front();
        Q.pop();
        int v;
        for(int i=1;i<=G.vexnum;++i){
            if(G.vertices[i].data==q->data){
                v=i;
            }
        }
        visited[v]=true;
        for (int w=FirstAdjVex(G,v); w>=1; w=NextAdjVex(G,v, w)) {
            if (!visited[w]) {
                CSTree p=new CSNode();
                p->data=G.vertices[w].data;
                p->lchild=NULL;
                p->nextsibling=NULL;
                Q.push(p);
                visited[w]=true;
                if (first) {
                    q->lchild=p;
                    first=false;
                }
                else{
                    q->nextsibling=p;
                }
                q=p;
            }
        }
    }
}
void BFSForest(ALGraph G,CSTree *T){
    (*T)=NULL;
    for (int v=1; v<=G.vexnum; v++) {
        visited[v]=false;
    }
    CSTree q=NULL;
    for (int v=1; v<=G.vexnum; v++) {
        if (!(visited[v])) {
            CSTree p=new CSNode();
            p->data=G.vertices[v].data;
            p->lchild=NULL;
            p->nextsibling=NULL;
            if (!(*T)) {
                (*T)=p;
            }
            else{
                q->nextsibling=p;
            }
            q=p;
            BFSTree(G,v,p);
        }
    }
}




int main() //主函数
{    
    ALGraph G;
    CreateDG(G);
    CSTree T;
    while(1){
        cout<<"1、按邻接表形式输出图"<<endl;
        cout<<"2、深度优先搜索序列"<<endl;
        cout<<"3、广度优先搜索序列"<<endl;
        cout<<"4、深度优先搜索树"<<endl;
        cout<<"5、广度优先搜索树"<<endl;
        cout<<"请输入你的选择"<<endl;
        int choice;
        cin>>choice;
        if(choice==1){
            show(G);    
        }
        else if(choice==2){
            DFSTraverse(G);
            cout<<"非递归的"<<endl;
            DFS2(G,1);
        }
        else if(choice==3){
            BFSTraverse(G);
        }
        else if(choice==4){
            DFSForest(G,T);
            cout<<"前序遍历结果为"<<endl;
            PreOrderTraverse(T);
            cout<<endl;
            cout<<"树形输出（括号形式）"<<endl;
            showTR(T);
            cout<<endl;
        }
        else if(choice==5){
            BFSForest(G,&T);
            cout<<"中序遍历结果为"<<endl;
            InOrderTraverse(T);
            cout<<endl;
            cout<<"树形输出（括号形式）"<<endl;
            showTR(T);
            cout<<endl;
        }
        
    }        
    system("pause");
}