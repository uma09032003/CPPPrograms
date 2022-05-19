//PROGRAM:

#include <iostream>
#include<iomanip>
#include<cstring>
using namespace std;
struct rec //To store records of the transactions
{
    char *bn,*f,*ba;
    int r,s1,s2;
    struct rec *next;
}*h=NULL,*t=NULL,*m;
char *z,*j,*k;
//LinkedList DS is used to store the chain of Records
void ins(char bnm[],char baa[],int r,int s1,int s2,char z[])
{
    m=new struct rec;
    m->bn=bnm;
    m->r=r;
    m->s1=s1;
    m->s2=s2;
    m->f=z;
    m->ba=baa;
    if(h==NULL)
    h=m;
    else
    t->next=m;
    m->next=NULL;
    t=m;
}
//To display records
void disrec()
{
    m=h;
    if(m==NULL)
    {
        cout<<"No Transactions Yet ! "<<endl;
        return ;
    }
    cout<<setw(25)<<" BookTitle"<<setw(25)<<"Book Author"<<setw(15)<<"Requested"<<setw(25)<<"Initial Stock "<<setw(25)<<" Final Stock "<<setw(15)<<"Status"<<endl;
    while(m!=NULL)
    {
    cout<<setw(25)<<m->bn<<setw(25)<<m->ba<<setw(15)<<m->r<<setw(25)<<m->s1<<setw(25)<<m->s2<<setw(15)<<m->f<<endl;
    m=m->next;
    }
}

class b//Class that defines the datatype and basic operations of a Single Book 
{
    char *bt,*ba,*bp;//Pointers to store the input stream of characters
    int p,stk;//For Price and Stock Available
    void updp(int a)//Private class method that only functions within the class can access
    {
        p=a;
        cout<<"\n Price Updated Successfully ! ";
    }
    public:
    void getd()//To fetch data about the book for operations
    {
        bt=new char[25];
        ba=new char[25];
        bp=new char[25];
        cout<<"\nBook Name :";
        cin>>bt;
        cout<<"\nBook Author : ";
        cin>>ba;
        cout<<"\nBook Publisher : ";
        cin>>bp;
        cout<<"\nPrice: ";
        cin>>p;
        cout<<"\nStock : ";
        cin>>stk;
        
    }
    bool searchr(char *t,char *a)//To know whether the book is available
    {
        return (!strcmp(t,bt))&&(!strcmp(a,ba))&&stk;
    }
    void dis()//To display Book Details
    {
        cout<<setw(25)<<" BookTitle"<<setw(25)<<"Book Author"<<setw(25)<<"Publishers"<<setw(15)<<"Price"<<setw(15)<<endl;
        cout<<setw(25)<<bt<<setw(25)<<ba<<setw(25)<<bp<<setw(15)<<p<<endl;
        
    }
    void dis1()//To display Book Details
    {
        
        cout<<setw(25)<<bt<<setw(25)<<ba<<setw(25)<<bp<<setw(15)<<p<<setw(15)<<stk<<endl;
        
    }
    void pup(int a)//To update Price of the Book 
    //Public member of the class accessing the private member 
    {
        updp(a);
    }
    int stkupd(int a)//To update the number of Stocks available after purchase
    {
        int k=stk;
        stk=stk-a;
        return k;
    }
    int getp()//To fetch price , a private class member
    {
        return p;
    }
};
class books//Class defining the collection of all the books and operations on all the books in general
{
    class b *bs;//Individual Book datatype pointer
    int a;
    public:
    books(int n)//Constructor to create an array for the required number of Books
    {
        a=n;
        bs=new b[n];
        cout<<"\n Memory allocated to database of Books ! "<<endl;
    }
    void inp()//To fetch data for each book
    {
        for (int i=0;i<a;i++)
        {
            cout<<"\n Book "<<i+1<<" : "<<endl;
            bs[i].getd();//method to store data of a single book
        }
    }
    void req()//For user Operations
    {
        //For the required character operation , array of characters in dynamically allocated
        z=new char[25];
        j=new char[25];
        k=new char[25];
        //Fetching the title and author of the Book to be searched
        cout<<"\n Enter Title : ";
        cin>>j;
        cout<<"\n Enter Author : ";
        cin>>k;
        bool c;
        int i;
        for ( i=0;i<a;i++)//To search the book among many book objects
        {
            c=bs[i].searchr(j,k);//searchr is a method to say whether a method is found
            if(c)
            break;
        }
        if(i==a)
        {
            cout<<"\n Book not available ! ";
            z=new char[25];
            strcpy(z," Out of Stock ! ");
            ins(j,k,0,0,0,z);
            return;
        }
        cout<<"\n Available ! ";
        bs[i].dis();//If the queried book is available , details are displayed
        int l;
        cout<<"\nNo of Copies Required : ";
        cin>>l;//Accepting the requested number of copies
        int y=bs[i].stkupd(0);//Fetching the present number of Stock
        int u=y;
        if(l<=y)//If the number of items requested is less  than or equal to the actual available number of stocks
        {
            //Displaying Price and asking for Confirmation
            cout<<"\nAvailable!\n Price : "<<bs[i].getp()*l<<"\nWould you like to confirm Order? (1) else (0)";
            int p;
            cin>>y;
            if(y==1)//If confirmed
            {
                y=bs[i].stkupd(l);//Updating the number current number of Stocks
                strcpy(z,"Successful");
                ins(j,k,l,u,y,z);//Updating the transaction record
                cout<<"\nUpdated ! ";
                return;
            }
            return;
            
        }
        else
        {
            cout<<"\n Requested Number of Stocks not available ! "<<endl;
            strcpy(z,"Unsuccessful");
            ins(j,k,l,y,y,z);//Updating the unsuccessful transaction in the record
        }
        
    }
    void d()//To display information of all the books
    {
        for (int i=0;i<a;i++)
        {
            bs[i].dis1();
        }
    }
    void pp()//To update price of any book
    {
        j=new char[25];
        k=new char[25];
        cout<<"\n Enter Title : ";
        cin>>j;
        cout<<"\n Enter Author : ";
        cin>>k;
        int i;
        for ( i=0;i<a;i++)//Searching the book
        {
            int c=bs[i].searchr(j,k);
            if(c)
            break;
        }
        if(i==a)
        {
            cout<<"\n Book not available ! ";
            return;
        }
        //If book is found , calling the appropriate function , to update the price
        cout<<"\n Enter New Price : ";
        int d;
        cin>>d;
        bs[i].pup(d);
        
    }
    void upds()//To update the number of Stocks
    {
        j=new char[25];
        k=new char[25];
        cout<<"\n Enter Title : ";
        cin>>j;
        cout<<"\n Enter Author : ";
        cin>>k;
        int i;
        for ( i=0;i<a;i++)//Searching the book
        {
            int c=bs[i].searchr(j,k);
            if(c)
            break;
        }
        if(i==a)
        {
            cout<<"\n Book not available ! ";
            return;
        }
        //If book is found , calling the appropriate function , to update the price
        cout<<"\n Enter New Number of Stocks : ";
        int d;
        cin>>d;
        bs[i].stkupd(-d);
    }
    
};
int main()
{
  char a[25];
  strcpy(a,"admin");
  cout<<"\n Enter Number of Books : ";
  int n;
  cin>>n;
  class books obj(n);
  while(strcmp(a,"exit"))
  {
     if (!strcmp(a,"admin"))
     {
         cout<<"\n Action : ";
         int i;
         cin>>i;
         if(i==1)
         obj.inp();
         else if(i==2)
         {
         cout<<setw(25)<<" BookTitle"<<setw(25)<<"Book Author"<<setw(25)<<"Publishers"<<setw(15)<<"Price"<<setw(15)<<"Stock"<<endl;
         obj.d();
         }
         else if(i==3)
         disrec();
         else if(i==4)
         {
             obj.pp();
         }
         else if(i==5)
         {
             obj.upds();
         }
     }
     else if(!strcmp(a,"user"))
     {
         obj.req();
     }
     cout<<"\n";
     cin>>a;
  }
}
