/*The optimal is achieved by investing in only one bank each year.suppose for j years for two
banks l and k if (r1k+r2k..rjk)>r1l+r2l..rjl) optimal is investing in k bank.
Referred from clrs for optimal strategy of investing in one bank each year.
matrix S[i][j] stores maximum amount possible after ith year in jth bank.
consider years i and i+1 
suppose ith year investment is done in all banks and return S[i][k] is max i.e in bank k.
for i+1 year and for each bank we invest maximum of S[i][k]-f or return from pre year of
same bank.we also store in each bank the prev bank from which money came from.

Finally after nth year we check where max occurs and go above following parent banks.
Complexity is O(nt) since we are maintaining a matrix S  of size t*n 
*/

#include <iostream>
#include <iomanip>
using namespace std;


int main(){
	double s;
	cin >> s;	// total investment
	int t,n;
	double f;
	cin >> t;	// no of years to invest
	cin >> n;	// no of instruments to invest in
	cin >> f;	// fee to be leived if investment instrument is changed (Assumption : for the first year, no fee)
	double **rr = new double*[t];
	for(int i=0;i<t;i++)
		rr[i] = new double[n];
	for(int i=0;i<t;i++)
		for(int j=0;j<n;j++)cin>>rr[i][j];
	
	pair<double,int> S[t][n];
	pair<double,int> max[t];
	double temp1 = 0;
	for(int i=0;i<n;i++){
		S[0][i] = make_pair(s*rr[0][i],-1);
		if(s*rr[0][i]>temp1){
			temp1 = s*rr[0][i];
			max[0] = make_pair(temp1,i);
		}
	}
	for(int i=1;i<t;i++){
		//double k = max[i-1].first -f;
		pair<double,int> m;
		m.first = 0;
		m.second = 0;
		for(int j=0;j<n;j++){
			if(j==max[i-1].second){
				//double r = (max[i-1].first -f+f)*rr[i][j];
				S[i][j] = make_pair((max[i-1].first -f+f)*rr[i][j],j);
				if(m.first<(max[i-1].first -f+f)*rr[i][j]){
					m.first = (max[i-1].first -f+f)*rr[i][j];
					m.second = j;
				}
			}
			else{
				//double r  = S[i-1][j].first;	
				if(S[i-1][j].first>max[i-1].first -f){
					S[i][j] = make_pair((S[i-1][j].first)*rr[i][j],j);
					if(m.first<(S[i-1][j].first)*rr[i][j]){
						m.first = (S[i-1][j].first)*rr[i][j];
						m.second = j;
					}
				}
				else{
					S[i][j] = make_pair((max[i-1].first -f)*rr[i][j],max[i-1].second);
					if(m.first<(max[i-1].first -f)*rr[i][j]){
						m.first = (max[i-1].first -f)*rr[i][j];
						m.second = j;
					}	
				}
			}
		}
		max[i] = m;
	}
	// for(int i=0;i<t;i++){
	// 	for(int j=0;j<n;j++){
	// 		cout<<S[i][j].first<<"-p"<<S[i][j].second<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// for(int i=0;i<t;i++){
	// 	cout<<max[i].first<<" "<<max[i].second<<endl;
	// }
	pair<double,int> res[t];
	int ans;
	ans = max[t-1].second;
	for(int i=t;i>0;i--){
		//cout<<ans<<endl;
		res[i-1].second = ans;
		for(int j=0;j<n;j++){
			if(j==ans){
				res[i-1].first=(S[i-1][ans].first)/(rr[i-1][ans]);
				ans = S[i-1][j].second;
				break;
			}
		}
	}
	// for(int i=0;i<t;i++){
	// 	cout<<res[i].first <<" "<<res[i].second <<endl;
	// }
	for(int i=0;i<t;i++){
		for(int j=0;j<n;j++){
			if(j==res[i].second){
				if(i==0)cout<<fixed<<setprecision(5)<<res[i].first<<" ";
				else if(j!=res[i-1].second)cout<<fixed<<setprecision(5)<<res[i].first<<" ";
				else cout<<fixed<<setprecision(5)<<res[i].first<<" ";
			}
			else{
				cout<<0<<" ";
			}
		}
		cout<<endl;
	}
    return 0;
}