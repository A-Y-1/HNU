#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a;    
    int b;
    int q,r=0;
    cin>>a>>b;
    if(a.length()==1)  
    	{	q=(a[0]-'0'+r*10)/b;
    		r=(a[0]-'0'+r*10)%b;
    		cout<<q;
		}
	else {
		q=(a[0]-'0'+r*10)/b;
   		r=(a[0]-'0'+r*10)%b;
    	if(q!=0)
   			cout<<q;
    	for(unsigned int i=1;i<a.length();i++)
    	{ 
       		q=(a[i]-'0'+r*10)/b;
        	r=(a[i]-'0'+r*10)%b;
        	cout<<q;;
    	}
	}   
    cout<<" "<<r;
    return 0;  
}
