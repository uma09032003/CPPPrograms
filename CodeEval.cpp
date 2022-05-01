#include <iostream>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;

//Assumptions :
//f(n) is accepted as a string 
//consisting only of characters 
// '*' ,'+','-','/','%' ,'n' ,')','(' ,and all digits from 0 to 9
//At least one n is present

int t1=-1,tn=-1;
//t1-- top of character stack
//tn -- top of integer stack
char *stk;//Used for infix to postfix
int *sp;//For postfix evaluation
void pn(int a)//Push of int stack
{
    tn++;
    sp[tn]=a;
}
int popn()//Pop of int stack
{
    int c=tn;
    tn--;
    return sp[c];
}
void pc(char a)//Push of char stack
{
    t1++;
    stk[t1]=a;
}
char popc()//Pop of char stack
{
    int p=::t1;
    ::t1--;
    return stk[p];
}

string inconpos(string a)//To convert infix string to postfix
{
    int s=a.size();
    stk=new char(s);
    string rt;//To return the postfix string
    //Infix to postfix conversion Algorithm
    for(int i=0;i<s;i++)
    {
        if(a.at(i)=='('||a.at(i)==')'||a.at(i)=='+'||a.at(i)=='-'||a.at(i)=='/'||a.at(i)=='*'||a.at(i)=='%')
        {
            if(a.at(i)==')')
            {
                while(stk[t1]!='(')
                {
                    char t=popc();
                    rt.append(1,t);
                }
                char t=popc();
            }
            else if(a[i]=='(')
            {
                pc(a[i]);
            }
            else if(a[i]=='+'||a[i]=='-')
            {
                if(stk[t1]=='*'||stk[t1]=='/'||stk[t1]=='%')
                {
                while(stk[t1]=='*'||stk[t1]=='/'||stk[t1]=='%')
                {
                char t=popc();
                rt.append(1,t);
                }
                if(t1!=-1&&stk[t1]=='+'||stk[t1]=='-')
                {
                char t=popc();
                rt.append(1,t);
                }
                pc(a[i]);
                }
                else if(stk[i]=='+'||stk[i]=='-')
                {
                char t=popc();
                pc(a[i]);
                rt.append(1,t);
                }
                else
                pc(a[i]);
            }
            else if(a[i]=='*'||a[i]=='/'||a[i]=='%')
            {
                if(stk[t1]=='*'||stk[t1]=='/'||stk[t1]=='%')
                {
                    char c=popc();
                    rt.append(1,c);
                }
            pc(a[i]);
            }
        }
        else
        {
        rt.append(1,a[i]);
        if(a[i+1]=='+'||a[i+1]=='*'||a[i+1]=='-'||a[i+1]=='/'||a[i+1]=='%')
        rt.append(1,'&');//Introducing marker to keep track of the length of digits
        }
    }
    while(::t1!=-1)
    {
        char c=popc();
        rt.append(1,c);
    }
    delete stk;
    return rt;//Returning the postfix expression with markers
}
int evalpos(string s,int n)
{
    string a=inconpos(s);//To obtain the postfix expression of the given string
    //For example :
    //Infix:n*11*12
    //Postfix:n&11&*12*
    
    cout<<endl<<a<<endl;
    int l=a.size();
    sp=new int[l];
 for(int i=0;i<a.size();i++)
 {
     if(a.at(i)=='&')//Skipping if it is a marker
     continue;
     if(a.at(i)=='n')
     {
     pn(n);//Passing the value of n of f(n)
     }
     else if(a.at(i)!='+'&&a.at(i)!='-'&&a.at(i)!='*'&&a.at(i)!='/'&&a.at(i)!='%')
     {
         string p="0";
         while(a.at(i)!='&'&&a.at(i)!='+'&&a.at(i)!='-'&&a.at(i)!='*'&&a.at(i)!='/'&&a.at(i)!='%')//As the combination of digits make up a 
         //single number until a marker is encouontered
         
         {
             p.append(1,a.at(i));
             i++;
         }
         int c=0;//Converting the string to integer
         for(int l=0;l<p.size();l++)
         {
             c=c*10+int(p[l])-48;
         }
         pn(c);//Pushing it inside the stack for evaluation
         i=i-1;
         
     }
     else
     {
         //Postfix expression evaluation
         if(a.at(i)=='+')
         {
             int k=popn();
             int j=popn();
             pn(k+j);
         }
         else if(a.at(i)=='-')
         {
             int k=popn();
             int j=popn();
             pn(j-k);
         }
         else if(a.at(i)=='*')
         {
             int k=popn();
             int j=popn();
             pn(k*j);
         }
         else if(a.at(i)=='/')
         {
             int k=popn();
             int j=popn();
             pn(j/k);
         }
         else if(a.at(i)=='%')
         {
             int k=popn();
             int j=popn();
             pn(j%k);
         }
     }
     
 }
int c=popn();
delete sp;
return c;//Returning the calculated value
}

int main()
{
    string fn;
    cin>>fn;//Accepting f(n) as a string 
    cout<<"\n Enter the integer value to evaluate : ";
    int n;
    cin>>n;//Accepting n value
    cout<<endl<<evalpos(fn,n);//Displaying the result
    

}
