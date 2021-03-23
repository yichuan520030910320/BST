#include <iostream>

using namespace std;
struct node {
    int ls, rs, val, siz, cnt;
} tree[10005];
int cont = 0;
void add(int root, int val) {
    tree[root].siz++;
    if (tree[root].val == val) {
        tree[root].cnt++;
        return;
    } else if (tree[root].val > val) {
        if (tree[root].ls == 0) {
            tree[root].ls = ++cont;
            tree[cont].val = val;
            tree[cont].cnt=tree[cont].siz=1;
        } else {
            add(tree[root].ls, val);
        }
    } else {
        if (tree[root].rs == 0) {
            tree[root].rs = ++cont;
            tree[cont].val = val;
            tree[cont].cnt=tree[cont].siz=1;
        } else {
            add(tree[root].rs, val);
        }
    }
}

int search_pre(int root, int val, int ans) {
    if (val > tree[root].val) {
        if (tree[root].rs == 0) return tree[root].val;
        else {
            return search_pre(tree[root].rs, val, tree[root].val);
        }
    } else {
        if (tree[root].ls == 0) return ans;
        else return search_pre(tree[root].ls, val, ans);
    }
}

int search_nxt(int root, int val, int ans) {
    if (val >=tree[root].val) {
        if (tree[root].rs == 0)  return ans;
        else {
            return search_nxt(tree[root].rs, val, ans);
        }
    } else {
        if (tree[root].ls == 0)return tree[root].val;
        else return search_nxt(tree[root].ls, val, tree[root].val);
    }
}

int search_rank(int root, int val) {
    if (root == 0) return 0;
    if (tree[root].val == val) return tree[tree[root].ls].siz;
    if (val < tree[root].val) return search_rank(tree[root].ls, val);
//cout<<tree[tree[root].ls].siz<<"  "<< tree[root].cnt<<endl;
    return search_rank(tree[root].rs, val) + tree[tree[root].ls].siz + tree[root].cnt;
}

int search_rank_x_num(int root, int num) {
    if (root == 0) return -66666;
    if (tree[tree[root].ls].siz >= num) search_rank_x_num(tree[root].ls, num);
    if (tree[tree[root].ls].siz + tree[root].cnt >= num) return tree[root].val;
    return search_rank_x_num(tree[root].rs, num - tree[tree[root].ls].siz - tree[root].cnt);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        int x;
        cin >> x;
        if (temp == 1) {
            cout << search_rank(1, x) + 1 << endl;
        } else if (temp == 2) {
cout<<search_rank_x_num(1,x)<<endl;
        } else if (temp == 3) {
cout<<search_pre(1,x,-2147483647)<<endl;
        } else if (temp == 4) {
cout<<search_nxt(1,x,2147483647)<<endl;
        } else if (temp == 5) {
            if (cont==0){
                tree[++cont].val=x;
                tree[cont].cnt=tree[cont].siz=1;
                continue;
            }
add(1,x);
        }
    }
    return 0;
}

