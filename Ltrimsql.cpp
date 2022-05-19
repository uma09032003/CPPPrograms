#include <iostream>
#include<string.h>
using namespace std;

int main()
{
    string ar1,ar2;
    //ar1 to store the original string
    //ar2 to store the characters to trim
    cin>>ar1;
    cin>>ar2;
    int i=1;
    while(i){
        for (int j=0;j<ar2.length();j++){
            if(ar1[0]==ar2[j]){
            ar1.erase(ar1.begin());
            j=-1;//To check if there are previous characters
                
            }
        }
        i=0;
    }
    cout<<ar1;
}
