#include <iostream>
using namespace std;

int main(){
	int u[][3] = {{30,2,3}};
	int v[][3] = {{1,2,3},{10,2,3},{20,2,3},{40,2,3},{50,2,3}};

	int i = 0;
	int j = 0;

	bool e = false;

	cout<<sizeof(v)/12<<endl;
	cout<<"{";

	while(i+j<sizeof(v)/12+sizeof(u)/12){

		if (!e && u[i][0]<v[j][0])
		{
			cout<<"{"<<u[i][0]<<","<<u[i][1]<<","<<u[i][2]<<"},";

			if(i+1>=sizeof(u)/12)
				e = true;

			i++;
		}
		else
		{
			cout<<"{"<<v[j][0]<<","<<v[j][1]<<","<<v[j][2]<<"},";

			
			j++;
		}
	}

	cout<<"}"<<endl;

}