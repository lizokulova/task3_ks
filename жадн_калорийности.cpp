#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Knapsack{
private:
    vector<int> values;
    vector<int> weights;
    int W;
    int N;

    bool compare(int a, int b){
        return (double)values[a]/weights[a] > (double)values[b]/weights[b];
    }

public:
    Knapsack(int N, int W, vector<int>& vals, vector<int>& wts): N(N), W(W), values(vals), weights(wts){}

    vector<int> greedy_by_calories(){
        vector<int> ans(N, 0);
        vector<int> numb(N);
        int i;
        for (i=0; i<N; i++) numb[i] = i;

        sort(numb.begin(), numb.end(), [this](int a, int b){return compare(a, b);});

        int curr=0;
        for (int ind: numb){
            if (curr+weights[ind] <= W){
                ans[ind] = 1;
                curr+=weights[ind];
            }
        }
        return ans;
    }

    int evaluate(const vector<int>& sol){
        int totalW=0, totalV=0, i;
        for (i=0; i<N; i++){
            if (sol[i]==1){
                totalW+=weights[i];
                totalV+=values[i];
            }
        }
        if (totalW>W) return -1;
        return totalV;
    }

    void print(const vector<int>& sol){
        int totalW=0, i;
        for (i=0; i<N; i++) if (sol[i] == 1) totalW+=weights[i];
        cout << totalW << endl;
        for (i=0; i < N; i++){
            cout << sol[i];
            if (i != N-1) cout << " ";
        }
        cout << endl;
    }
};

class Solver{
public:
    vector<int> solve(Knapsack& task){
        return task.greedy_by_calories();
    }
};

int main(){
    int N, W, i;
    cin >> N >> W;
    vector<int> val(N);
    vector<int> weig(N);

    for (i = 0; i < N; i++) cin >> val[i] >> weig[i];
    Knapsack k(N, W, val, weig);
    Solver a;
    vector<int> ans = a.solve(k);
    k.print(ans);

    return 0;
}
