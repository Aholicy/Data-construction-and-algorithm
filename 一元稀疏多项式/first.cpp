#include <iostream>
#include<string>
using namespace std;
typedef struct {
    float coef;
    int expn;
}Data;
struct Node{
    Data data;
    Node* next;
};
class polynomial{
private:
    Node* headnode;
public:
    polynomial(){
        headnode=new Node;//指针指向一个新的结点。使用new开辟了一块内存，只能通过指针访问。
        headnode->next=NULL;
    };
    void CreatePolyn();
    void DestroyPolyn();
    void PrintPolyn();
    void length(polynomial a);
    void Addpolyn(polynomial a,polynomial  b);
    void Multipolyn(polynomial  a,polynomial  b);
    void bubblesort();
    void merge();
    void subpolyn(polynomial a,polynomial b);
    void diffpolyn(polynomial a);
    void value(polynomial a,int x);
    
};
void polynomial::CreatePolyn(){
    int n;//项数n
    Node* newnode;//新指针，无指向
    Node* last;//尾指针，无指向
    last=headnode;//尾指针=头指针，可以访问头节点。
    cout<<"请输入项数"<<endl;
    cin>>n;
    cout << "请输入每一项系数及指数，按指数从大到小排列"<<endl; 
    for(int i=0;i<n;i++){        
        newnode=new Node;
        cin>>newnode->data.coef;
        cin>>newnode->data.expn;
        last->next=newnode;//尾指针的下一个是新指针，接上了。
        last=newnode;//尾指针指向新的结点。
    }
    last->next=NULL;
    //PrintPolyn();
}
void polynomial::DestroyPolyn(){
    while(NULL!=headnode->next){   
	    Node *p;
        p=headnode->next;
        headnode->next=p->next;
        delete p;
        p=NULL;
        }
	}
void polynomial::PrintPolyn(){
    Node *p;//node*指针
    p=headnode->next;//p指向头的下一个结点
    while(NULL!=p->next){   	
        if(p->data.coef==0){
        	p=p->next;
		}
		else{
			cout<<p->data.coef<<"x^"<<p->data.expn<<"+";
            p=p->next;	
		}			
    }
	if(p->data.expn==0){
    	cout<<p->data.coef;
	}
	else{
		cout<<p->data.coef<<"x^"<<p->data.expn<<endl;
	}   
}
void polynomial::Addpolyn(polynomial a, polynomial b){
    Node *p, *q;
    Node *newnode;
    Node *current;
    polynomial c;//建立新的链表c
    current=c.headnode;//current指向头节点
    p = a.headnode->next;//p指向a的第一个结点
    q = b.headnode->next;//q指向b的第一个结点
    while (p && q) {
        if (p->data.expn >q->data.expn) {//p>q
            newnode = new Node;
            newnode->data=p->data;
            current->next = newnode;
            current = newnode;
            p = p->next;
        } 
		else if (p->data.expn==q->data.expn) {
            if (p->data.expn+ q->data.expn == 0) {
                p = p->next;
                q = q->next;
            } 
			else {
                newnode = new Node;
                newnode->data.expn= p->data.expn;
                newnode->data.coef = p->data.coef + q->data.coef;
                current->next=newnode;
                current = newnode;
                p = p->next;
                q = q->next;
            }
        } 
		else {
            newnode = new Node;
            newnode->data = q->data;
            current->next = newnode;
            current = newnode;
            q = q->next;
        }
    }
    current->next = NULL;
    if (p != NULL) current->next = p;
    if (q != NULL) current->next = q;
    c.PrintPolyn();
}

void polynomial::bubblesort(){//排序 
    Data t;
    Node* a;
    Node* b;
    for(a=headnode->next;a!=NULL;a=a->next){
        for(b=a->next;b!=NULL;b=b->next){
            if(a->data.expn<b->data.expn){
                t = a->data;
                a->data = b->data;
                b->data = t; 
            }
        }
        
    }
}
void polynomial::merge(){//合并 
    Node* a=headnode->next;
    Node* b;
    Node* newnode;
    polynomial c;
    Node* curc=c.headnode;
    newnode=new Node;
    newnode->data=a->data;
    curc->next=newnode;
    curc=newnode;
    for(;a->next!=NULL;a=a->next){
        b=a->next;
        if(a->data.expn==b->data.expn){
            curc->data.coef=curc->data.coef+b->data.coef;
        }
		else{
            newnode=new Node;
            newnode->data=b->data;
            curc->next=newnode;
            curc=newnode;
        }
    }
    curc->next=NULL;
    headnode=c.headnode;
}
void polynomial::Multipolyn(polynomial a, polynomial b){//乘法，其实就是对a的每一项用b的每一项去乘，得到的多项式再进行相加操作 
    // a.PrintPolyn();                                  其中可能会有重复和不规则排列，所以再进行排序和合并操作 
    // b.PrintPolyn();
    polynomial c;
    Node* curc=c.headnode;
    Node* newnode;
    Node* cura=a.headnode->next;
    Node* curb=b.headnode->next;
    while(cura!=NULL){
        while(curb!=NULL){
            newnode=new Node;
            newnode->data.coef=cura->data.coef*curb->data.coef;
            newnode->data.expn=cura->data.expn+curb->data.expn;
            curb=curb->next;
            curc->next=newnode;
            curc=newnode;
        }
        curb=b.headnode->next;
        cura=cura->next;
    }
    curc->next=NULL;
    c.bubblesort();
    c.merge();   
    c.PrintPolyn();
    c.DestroyPolyn();   
}
void polynomial::subpolyn(polynomial a,polynomial b){//减法，将b每一项取反后在加起来 
	polynomial c;
	Node* newnode;
    Node* curc=c.headnode;
	Node* curb=b.headnode->next;
	while(curb!=NULL){
        newnode=new Node;
        newnode->data.coef=-curb->data.coef;
        newnode->data.expn=curb->data.expn;
        curb=curb->next;
        curc->next=newnode;
        curc=newnode;
        }
        a.Addpolyn(a,c);
    }	
void polynomial::diffpolyn(polynomial a){//求导 
	polynomial c;
	Node *newnode;
	Node*curc=c.headnode;
	Node*cura=a.headnode->next;
	while(cura!=NULL){
		newnode=new Node;
		if(cura->data.expn==1){
			newnode->data.coef=cura->data.coef;
			newnode->data.expn=0;
		}
		else{
			newnode->data.coef=cura->data.coef*cura->data.expn;
		    newnode->data.expn=cura->data.expn-1;
		}
		cura=cura->next;
		curc->next=newnode;
		curc=newnode;
	}
	curc->next=NULL;
	c.PrintPolyn();
	c.DestroyPolyn();
}
void polynomial::value(polynomial a,int x){
	Node *newnode;
	float sum=0;
	Node*cura=a.headnode->next;
	while(cura!=NULL){
		if(cura->data.expn==0){
			sum=sum+cura->data.coef;
		}
		else{
			int temp=1;
			for(int i=0;i<cura->data.expn;++i){
				temp=temp*x;
			}
			sum=sum+temp*cura->data.coef;
		}
		cura=cura->next;
	}
	cout<<"值为"<<sum<<endl; 
}

int main() {
    
    cout<<"请选择计算符号"<<endl;
    string x;
    cin>>x;
    if(x=="q"){
    	polynomial a;
    	a.CreatePolyn();
		cout<<"请输入x的值"<<endl;
		int x;
		cin>>x;
		cout<<"value"<<endl;
		a.value(a,x);
		a.DestroyPolyn();		
	}
    else{
    	polynomial a,b;
        a.CreatePolyn();
        b.CreatePolyn();
        if(x=="+"){
    	    cout<<"add result"<<endl;
            a.Addpolyn(a, b);
	    }
    else if(x=="*"){
    	    cout<<"mutipolyn result"<<endl;
            a.Multipolyn(a, b);
	    }
    else if(x=="-"){
    	    cout<<"subpolyn result"<<endl;
            a.subpolyn(a,b);
	    }
    else if(x=="d"){
    	    cout<<"diffpolyn result"<<endl;
            a.diffpolyn(a);
	    }
	a.DestroyPolyn();
    b.DestroyPolyn();
	}
}
