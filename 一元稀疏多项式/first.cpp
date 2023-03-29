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
        headnode=new Node;//ָ��ָ��һ���µĽ�㡣ʹ��new������һ���ڴ棬ֻ��ͨ��ָ����ʡ�
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
    int n;//����n
    Node* newnode;//��ָ�룬��ָ��
    Node* last;//βָ�룬��ָ��
    last=headnode;//βָ��=ͷָ�룬���Է���ͷ�ڵ㡣
    cout<<"����������"<<endl;
    cin>>n;
    cout << "������ÿһ��ϵ����ָ������ָ���Ӵ�С����"<<endl; 
    for(int i=0;i<n;i++){        
        newnode=new Node;
        cin>>newnode->data.coef;
        cin>>newnode->data.expn;
        last->next=newnode;//βָ�����һ������ָ�룬�����ˡ�
        last=newnode;//βָ��ָ���µĽ�㡣
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
    Node *p;//node*ָ��
    p=headnode->next;//pָ��ͷ����һ�����
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
    polynomial c;//�����µ�����c
    current=c.headnode;//currentָ��ͷ�ڵ�
    p = a.headnode->next;//pָ��a�ĵ�һ�����
    q = b.headnode->next;//qָ��b�ĵ�һ�����
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

void polynomial::bubblesort(){//���� 
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
void polynomial::merge(){//�ϲ� 
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
void polynomial::Multipolyn(polynomial a, polynomial b){//�˷�����ʵ���Ƕ�a��ÿһ����b��ÿһ��ȥ�ˣ��õ��Ķ���ʽ�ٽ�����Ӳ��� 
    // a.PrintPolyn();                                  ���п��ܻ����ظ��Ͳ��������У������ٽ�������ͺϲ����� 
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
void polynomial::subpolyn(polynomial a,polynomial b){//��������bÿһ��ȡ�����ڼ����� 
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
void polynomial::diffpolyn(polynomial a){//�� 
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
	cout<<"ֵΪ"<<sum<<endl; 
}

int main() {
    
    cout<<"��ѡ��������"<<endl;
    string x;
    cin>>x;
    if(x=="q"){
    	polynomial a;
    	a.CreatePolyn();
		cout<<"������x��ֵ"<<endl;
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
