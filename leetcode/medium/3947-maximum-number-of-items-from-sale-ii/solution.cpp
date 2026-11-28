class Solution {
    #define ll long long
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n=items.size();

        int cheapest = INT_MAX;
        int max_factor = INT_MIN;
        for(int i=0;i<n;++i){
            cheapest = min(cheapest,items[i][1]);
            max_factor = max(max_factor,items[i][0]);
        }

        vector<int> freq(max_factor+1);//Create frequency counter for each factor
        for(int i=0;i<n;++i)
            freq[items[i][0]]++;
        for(int i=1;i<=max_factor;++i){
            if(freq[i]>0){
                for(int index=2*i;index<=max_factor;index+=i)
                    freq[i] += freq[index];
            }
        }

        map<ll,ll> cost_count;
        for(int i=0;i<n;++i){
            int cost = items[i][1];
            int count = freq[items[i][0]]-1;
            if(count>0 and cost<=2*cheapest)
                cost_count[cost] += count;
        }
        
        int total = 0;
        for(auto &[cost,count]: cost_count){
            int include = min<ll>(count,budget/cost);
            total += 2*include;
            budget -= include * cost;
        }
        total += budget/cheapest;
        return total;
    }
};