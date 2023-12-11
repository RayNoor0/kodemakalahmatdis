#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
using ll=long long;

const int INF = INT_MAX;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main(){
	int inp1,inp2,inp3,t;
	cout<<"masukkan jumlah node: ";
    cin >> n;
    capacity.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

	//ambil masukan
	cout<<"masukkan jumlah edge: ";
    cin>>t;
    int masukan[t][2];
    for(int i=0;i<t;i++){
    	cout<<"masukkan sisi dengan urutan simpul awal, simpul dituju, kapasitas jalur:";
    	cin>>inp1>>inp2>>inp3;
    	masukan[i][0]=inp1;
       	masukan[i][1]=inp2;
    	adj[inp1].push_back(inp2);
    	capacity[inp1][inp2] = inp3;
	}
    int max_flow = maxflow(0, n-1); //source selalu diletakkan di 0 dan target di n-1
	cout<<"Kondisi akhir graf:"<<endl;
	for(int i =0;i<t;i++){
    	cout<<masukan[i][0]<<" "<<masukan[i][1]<<" ";
    	cout<<capacity[masukan[i][0]][masukan[i][1]]<<endl;;
	}
    cout << "Maximum Flow: " << max_flow << endl;

    return 0;
}
