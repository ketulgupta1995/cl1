#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class stack{
	char data[20][3];
	int top;

public:
	stack(){
		top=-1;
	}
	void push(char a[3]){
		strcpy(data[++top],a);
	}
	char* pop(){
		return data[top--];
	}
	char* return_top(){
		return data[top];
	}
	bool isEmpty(){
		if(top==-1){return true;}
		else {return false;}
	}
	void print_stack(){
		for(int i=top;i>=0;i--){
			cout<<data[i]<<" , ";
		}
	}
};


stack reg_stack;
stack temp_stack;

class node{

public:
	char data;
	node* left;
	node* right;
	bool leftchild;
	int label;

	node(){
		data=' ';
		left=NULL;
		right=NULL;
		leftchild=true;
		label=0;
	}

    node(char d,bool l){
    	data=d;
    	left=NULL;
    	right=NULL;
    	leftchild=l;
    	label=0;
    }
};

void accept(node* t){
	cout<<"Enter data for node:  ";
	cin>>t->data;
	char ch;
	cout<<"\nDoes node "<<t->data<<" have a left child(y/n): ";
	cin>>ch;
	if(ch=='y'){
		node* l=new node(' ',true);
		t->left=l;
		accept(l);
	}
	cout<<"\nDoes node "<<t->data<<" have a right child(y/n): ";
		cin>>ch;
		if(ch=='y'){
			node* l=new node(' ',false);
			t->right=l;
			accept(l);
		}

}

void accept_dag(node* t){
	cout<<" Enter data for node:  ";
		cin>>t->data;
		if(t->data=='+'||t->data=='-'||t->data=='*'||t->data=='/'){
			cout<<"\nEnter left child of "<<t->data;
			node* l=new node(' ',true);
			t->left=l;
			accept_dag(l);
			cout<<"\nEnter right child of "<<t->data;
			node* l1=new node(' ',false);
			t->right=l1;
			accept_dag(l1);


		}


}

void labelling(node* t){
	if(t!=NULL){
		labelling(t->left);
		labelling(t->right);

		if(t->left==NULL&&t->right==NULL){   //for leaf
			if(t->leftchild==true){t->label=1;}  //left leaf
			else {t->label=0;}                   //right leaf
		}
		else{
			int l1=t->left->label;
			int l2=t->right->label;
			if(l1==l2){
				t->label=l1+1;
			}
			else{
				t->label=(l1>l2?l1:l2);
			}
		}
	}
}
void inorder(node* t){
	if(t!=NULL){
		inorder(t->left);
		cout<<t->data<<" :"<<t->label<<" ,  ";
		inorder(t->right);
	}
}

void initialize_stacks(){
	        int k;
			cout<<"\n Enter Size of reg_stack: ";
		    cin>>k;

		    for(int i=0;i<k;i++){
		    	char a[3]="R";
		    	char t[3]="t";
		    	int l=k-i-1;
		    	stringstream strs;strs<<l;
		    	strcat(a,strs.str().c_str());
		    	reg_stack.push(a);
		    	temp_stack.push(strcat(t,strs.str().c_str()));
		    }
	    cout<<"\nRegister Stack :";
	    reg_stack.print_stack();
	    cout<<"\nTemp Variables Stack :";
	    temp_stack.print_stack();
}

void swap(stack s){
	char* a=s.pop();
	char* b=s.pop();
	s.push(b);
	s.push(a);
}

char* op(char o){
	if(o=='+') {return "ADD";}
	else if(o=='-') {return "SUB";}
	else if(o=='*') {return "MUL";}
	else {return "DIV";}
}
void Gen_code(node* n){
    if(n->left==NULL&&n->right==NULL&&n->leftchild==true){
    	cout<<"MOV  "<<n->data<<" , "<<reg_stack.return_top()<<"\n";
    }
    else{
    	node* n1=n->left;
    	node* n2=n->right;

    	if(n2->label==0){
    		Gen_code(n1);
    		cout<<op(n->data)<<" "<<n2->data<<" , "<<reg_stack.return_top()<<"\n";
    	}

    	else if(n1->label<n2->label){
    		swap(reg_stack);
    		Gen_code(n2);
    		char* r=reg_stack.pop();
    		Gen_code(n1);
    		cout<<op(n->data)<<"  "<<r<<" , "<<reg_stack.return_top()<<"\n";
    		reg_stack.push(r);
    		swap(reg_stack);
    	}

    	else if(n2->label<n1->label){
    		Gen_code(n1);
    		char* r=reg_stack.pop();
    		Gen_code(n2);
    		cout<<op(n->data)<<"  "<<r<<" , "<<reg_stack.return_top()<<"\n";
    		reg_stack.push(r);
    	}
    	else{
    		Gen_code(n2);
    		char* t=temp_stack.pop();
    		cout<<"MOV  "<<reg_stack.return_top()<<"  ,  "<<t<<"\n";
    		Gen_code(n1);
    		temp_stack.push(t);
    		cout<<op(n->data)<<"  "<<t<<" , "<<reg_stack.return_top()<<"\n";
    	}
    }

}

int main() {
	node* root=NULL;
	root=new node();
	cout<<"\nStarting with the root node enter data: \n";
	accept_dag(root);

	labelling(root);

	cout<<"\nEntered Tree with labels is: \n";
	inorder(root);
	initialize_stacks();
	cout<<"\n\nGenerated Code is:\n****************************************\n\n";
	Gen_code(root);
	cout<<"\n\n****************************************";
	cout<<"\nFinal result is stored in register:  "<<reg_stack.return_top();
	return 0;
}

