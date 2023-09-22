#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
#include<string>
#include<cstring>
#include<queue>
using namespace std;
struct node{
	int v,len,nex;
} edge[500005 * 2];
int d[500005*2],head[500005*2],cnt,n,m,ans;
struct _value{
	int id;
	int val;
	_value(int _id = 0, int _val = 0){
		id = _id;
		val = _val;
	}
};
bool vis[500005*2];
inline int read(){
    int x=0,k=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
void dijkstra(int start){
	memset(d,0x3f,sizeof(d));
	memset(vis,0,sizeof(vis));
	d[start]=0;
	// for(int i=x;i<=y;i++){
	// 	int minn=0x3f,k=-1;
	// 	for(int j=x;j<=y;j++){
	// 		if(!vis[j]&&minn>d[j]){
	// 			minn=d[j];
	// 			k=j;
	// 		}
	// 	}
	// 	if(k==-1) return;
	// 	vis[k]=1;
	// 	for(int j=head[k];j;j=edge[j].nex){
	// 		if(!vis[j]){
	// 			int v=edge[j].v;
	// 			d[v]=min(d[v],d[k]+edge[j].len);
	// 		}			
	// 	}
	// }
	priority_queue<_value> que;
	que.push(_value(start, 0));
	while(!que.empty()){
		_value cur = que.top();
		que.pop();
		if(vis[cur.id] == 1){
			continue;
		}
		vis[cur.id] = 1;
		for(int i = head[cur.id]; i; i = edge[i].nex){
			int v = edge[i].v;
			if(d[v] > d[cur.id] + edge[i].len){
				d[v] = d[cur.id] + edge[i].len;
				que.push(_value(v, d[v]));
			}
		}
	}
}
void addp(int u, int v, int w){
	cnt++;
	edge[cnt].v = v;
	edge[cnt].len = w;
	edge[cnt].nex = head[u];
	head[u] = cnt; 
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
//		cnt++;
//		edge[cnt]={v,w,head[u]};
//		head[u]=cnt;
		addp(u, v, w);
		addp(v + n, u + n, w);
	}
	dijkstra(1);
	for(int i=1;i<=n;i++) ans+=d[i];
//	for(int i=1;i<=cnt;i++) swap(edge[cnt].v,edge[cnt].nex);
	cout<<ans<<endl;	
	dijkstra(1 + n);
	for(int i=1 + n;i<=n * 2;i++) ans+=d[i];
	cout<<ans<<endl;
	system("pause");
	return 0;
}
