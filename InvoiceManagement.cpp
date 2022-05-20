#include <iostream>
#include<string.h>
#include<iomanip>
using namespace std;
//Assume a total of 2% of the purchase cost is added to the user account as points


class product{
    public:
    string productid;
    string productname;
    int price;
    product* next;
};
//For Storind the chain of Products purchased in an invoice (Linked List of Products in an Invoice)

class user{
    int points;
    string userid;
    public:
    user *next;
    user(){
    	points=0;
	}
    void updatepoints(int a){
        points+=a;
        cout<<endl<<"Current Points : "<<points<<endl;
    }
    void setuserid(string a){
        userid=a;
    }
    string getuserid(){
        return userid;
    }
    int getuserpoints(){
    	return points;
	}
};
user *uhead=NULL;
user *utemp=NULL;
//For Storing the Chain of User Records (Linked List of User)

class invoice{
    product *head=NULL;//To store the Chain of the Products Bought
    product *temp=NULL;//Supportive to the previous pointer
    string userid;
    string status;
    int bill;//To store the final bill amount
    int up;//To store the updated points in the bill
    public:
    	invoice(){
    		head=NULL;
    		temp=NULL;
    		userid="Anonymous";
    		status="In Progress";
    		bill=0;
    		up=0;
		}
    int invoiceno;
    void addproducts();//To add products in the Invoice
    void generatebill();//To generate the bill and complete transction
    void setusertoinvoice(string u);//To search for and also to register a new user (customer)
    void settinguser(string u,user *p);//To set a specific user to the Invoice
    void printinvoice();//To print the invoice (Printing the List of Products Purchased with the userid if available)
    invoice *next;
    
}*invoicehead=NULL,*tempinvoice=NULL;
//For Storing the Linked List of Invoices

int invno=0;
void invoice::addproducts(){
    char c='c';
    do {
    product *p=new product();//Get a new Product Instance
    string s;
    int k;
    cout<<"\n Enter ProductID : ";
    cin>>s;
    p->productid=s;
    cout<<"\n Enter ProductName : ";
    cin>>s;
    p->productname=s;
    cout<<"\n Enter Price : ";
    cin>>k;
    p->price=k;
    this->bill+=k;//Updating the Final Bill Amount
    cout<<"\n Choice : ";
    cin>>c;
    if(this->head==NULL){
        head=p;
    }
    else{
        this->temp->next=p;
    }
    this->temp=p;
    } while(c!='g'); //Command g to generate the bill
    this->generatebill();
}
void invoice::generatebill(){
    cout<<"\n Total Amount of Purchase : "<<bill<<endl;
    cout<<"\n r to check for user and c to proceed t billing !";
    char c;
    cin>>c;
    //'r' to enter or check for user;
    if(c=='r'){
        string u;
        cout<<"\n Enter UserId : ";
        cin>>u;
        setusertoinvoice(u);
    }
    else if(c=='c'){
        if(invoicehead==NULL){
            invoicehead=this;
        }
        else{
            tempinvoice->next=this;
        }
        tempinvoice=this;
        invno++;
        this->invoiceno=invno;
        status="Complete";
        cout<<"\n Bill Generated Successfully ! ";
    }
}
void invoice::setusertoinvoice(string u){
    user *t=uhead;
    while(t!=NULL){
        if(t->getuserid()==u){
            cout<<"\n User Found ! ";
            t->updatepoints(0);
            cout<<"\n Bill Amount : "<<bill;
            cout<<"\n Would You Like to deduce points ? ";
            char y;
            cin>>y;
            if(y=='y'){
            	int x;
            	cin>>x;
            	if(x<=bill&&x<=t->getuserpoints())
            	t->updatepoints(-x);
            	up=up-x;
			}
            settinguser(u,t);
            return;
        }
        else{
            t=t->next;
        }
    }
    
    user *n=new user();
    
    if(uhead==NULL){
        uhead=n;
    }
    else{
        utemp->next=n;
    }
    utemp=n;
    
    n->setuserid(u);
    cout<<"\n User Added !";
    settinguser(u,n);
    }
void invoice::settinguser(string u,user *t){
            this->userid=u;
            if(invoicehead==NULL){
            invoicehead=this;
            }
            else{
            tempinvoice->next=this;
            }
            tempinvoice=this;
            invno++;
            this->invoiceno=invno;
            int x=(2*(this->bill))/100;
            status="Complete";
            cout<<"\n Bill Generated Successfully !\n";
            t->updatepoints(x);
            up=up+x;
            return;
}
void invoice::printinvoice(){
			product *p1=head;
			
			cout<<"\n User Identity : "<<userid<<endl;
			cout<<endl<<setw(10)<<"ProductID"<<setw(15)<<"ProductName"<<setw(10)<<"Price"<<endl;
			while(p1!=NULL){
				cout<<setw(10)<<p1->productid<<setw(15)<<p1->productname<<setw(10)<<p1->price<<endl;
				p1=p1->next;
			}
			return ;
}
invoice* searchinvoice(int no){
	invoice *t=invoicehead;
	while(t!=NULL){
		if(t->invoiceno==no){
			t->printinvoice();
			return t;
		}
		else{
			t=t->next;
		}
	}
		cout<<endl<<"\n No invoice found ! ";
}
	
int main(){
    char c='c';//Proceed to record the Bill
    while(c!='q')//q to quit the system
    {
        cin>>c;
        if(c=='i') //To check the invoice number
		{
        	int ino;
        	cout<<"\n Enter InvoiceNo: ";
        	cin>>ino;
        	searchinvoice(ino);
		}
		else if(c=='c') //To add a new Invoice
		{
		invoice a;
        a.addproducts();
		}
		
    }
}

//Yet to Complete CancelInvoice Method
