//Calcular los K-esimos caminos mas cortos O(KN(N + M log N)) ~ O(KN^3)
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<long long, long long>
using namespace std;
typedef long long ll;
const int MAX = 60;
vector<int> g[MAX];
int cost[MAX][MAX], dis[MAX], connect[305], path[MAX];
int n, a, b, k, inf = INT_MAX / 10; // a -> source, b -> sink
ll vis = 0, mark = 0, edge[MAX]; // vis to avoid repeat nodes in the path, mark to cancel edges in yen.
vector<int> emp; // empty vector
struct yen{
    int w;
    vector<int> p;
    yen(){w = 0;}
    yen(int _w, vector<int> _p){
        w = _w;
        p = _p;
    }
    bool operator<(yen other)const{
        if(w == other.w){
            return lexicographical_compare(p.rbegin(), p.rend(),other.p.rbegin(), other.p.rend() );
        }
        return w < other.w;
    }
    bool operator>(yen other)const{
        if(w == other.w){
            return lexicographical_compare(other.p.rbegin(), other.p.rend(),p.rbegin(), p.rend() );
        }
        return w > other.w;
    }
};

yen dijkstra(int s, int t){
    priority_queue< pii, vector<pii>, greater<pii>    > q;
    fill(dis, dis + (n + 2), inf);
    q.push(mp(0, s));
    dis[s] = 0;
    while(!q.empty()){
        int u = q.top().second;
        int c = q.top().first;
        if(u == t)    break;
        q.pop();
        if(vis & (1LL << u) && s != u)
            continue;
        vis |= (1LL << u);
        
        for(int i = 0; i < (int)g[u].size(); i ++){
            int v = g[u][i];
            if(vis & 1ll << v || (s == u && !(mark & 1LL<<v))){
                continue;
            }
            if(cost[u][v] != inf && dis[v] >= c + cost[u][v]){
                if(dis[v] > c + cost[u][v] || (dis[v] == c + cost[u][v] && u < path[v])){
                    dis[v] = c + cost[u][v];
                    path[v] = u;
                    q.push(mp(dis[v], v));
                }
            }
        }
    }
    if(dis[t] == inf)
        return yen(0, emp);
    yen ret;
    ret.w = dis[t];
    int cur = t;
    while(cur != s){
        ret.p.pb(cur);
        cur = path[cur];
    }
    ret.p.pb(cur);
    reverse(ret.p.begin(), ret.p.end());
    return ret;
}
vector<int> solve(){
    priority_queue < yen, vector<yen>, greater<yen> > B;
    vector<int> A[305];
    vis = 0;
    mark = edge[a];
    A[0] = dijkstra(a, b).p;
    if((int)A[0].size() == 0){
        return A[0];
    }
    for(int kk = 1; kk < k; kk ++){
        yen rootPath;
        memset(connect, -1, sizeof(connect));
        vis = 0;
        bool F = true;
        for(int i = 0; i <(int)A[kk - 1].size() - 1; i ++){
            bool flag = false;
            if(F && kk > 2 && (int)A[kk - 1].size() > i + 1 && (int)A[kk - 2].size() > i + 1 && A[kk - 1][i + 1] == A[kk - 2][i + 1])
                flag = true;
            else
                F = false;
            
            if(i >= (int)A[kk - 1].size() - 1)
                continue;
            int spurNode = A[kk - 1][i];
            mark = edge[spurNode];
            rootPath.w += (i ? cost[A[kk - 1][i - 1]][spurNode]: 0);
            rootPath.p.pb(spurNode);
            vis |= 1LL << spurNode;
            for(int j = 0; j < kk; j ++){
                if(connect[j] == i - 1 &&  (int)A[j].size() > i && A[j][i] == spurNode ){
                    connect[j] = i;
                    if((int)A[j].size() > i + 1)
                        mark &= ~(1LL<<A[j][i + 1])    ;
                }
            }
            if(flag)
                continue;
            ll prevVis = vis;
            yen spurPath = dijkstra(spurNode, b);
            vis = prevVis;
            if(spurPath.p.empty())    continue;
            yen curPath = rootPath;
            curPath.w += spurPath.w;
            for(int j = 1; j <(int) spurPath.p.size(); j ++)
                curPath.p.pb(spurPath.p[j]);
            B.push(curPath);
        }
        if(B.empty())
            return emp;
        A[kk] = B.top().p;
        while(!B.empty() && B.top().p == A[kk])
            B.pop();
            
    }
    return A[k - 1];
}

int main(){
  int m, u, v, c;
  while(true){
        scanf("%d %d %d %d %d", &n, &m, &k, &b, &a);
        if(!n && !m && !k && !a && !b)
            break;
        
        for(int i = 0; i <= n; i++){
            g[i].clear();
            edge[i] = 0;
        }
            
        for(int i = 0; i < m; i++){
            scanf("%d%d%d",&u, &v, &c);
            cost[v][u] = c;
            edge[v] |= 1LL<<u;
            g[v].pb(int(u));
        }
        vector<int> ans = solve();
        if(ans.empty()){
            printf("None\n");
        }else{
            for(int i = (int)ans.size() - 1; i >= 0; i --){
                if(i != (int)ans.size() - 1)
                    printf("-");
                printf("%d", ans[i]);
            }
            printf("\n");
        }
    }
  return 0;
}
