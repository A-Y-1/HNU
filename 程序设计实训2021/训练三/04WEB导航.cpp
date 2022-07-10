#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main()
{
	string request,url;
	url="http://www.game.org/";
	stack<string> front,back;
	while(1)
	{
		cin>>request;
		if(request=="QUIT") break;
		if(request=="VISIT")
		{
			back.push(url);
			cin>>url;
			while(!front.empty()) front.pop();
			cout<<url<<endl;
		}
		else if(request=="BACK")
		{
			if(back.empty()) cout<<"Ignored"<<endl;
			else
			{
				front.push(url);
				url=back.top();
				back.pop();
				cout<<url<<endl;
			}	
		}
		else if(request=="FORWARD")
		{
			if(front.empty()) cout<<"Ignored"<<endl;
			else 
			{
				back.push(url);
				url=front.top();
				front.pop();
				cout<<url<<endl;
			}
		}
	}
	return 0;
}
