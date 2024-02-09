#include <bits/stdc++.h>
using namespace std;

class SegTree
{
    vector<int> seg;

public:
    SegTree(int n)
    {
        seg.resize(4 * n);
    }
    void build(int idx, int low, int high, vector<int> &a)
    {
        if (low == high)
        {
            seg[idx] = a[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * idx + 1, low, mid, a);
        build(2 * idx + 2, mid + 1, high, a);
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
    int query(int idx, int low, int high, int l, int r)
    {
        // no overlap
        if (high < l || low > r)
            return INT_MAX;
        // complete overlap
        if (l <= low && high <= r)
            return seg[idx];
        // partial overlap
        int mid = (low + high) >> 1;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);
        return min(left, right);
    }
    void update(int idx, int low, int high, int pos, int value)
    {
        if (low == high)
        {
            seg[idx] = value;
            return;
        }

        int mid = (low + high) >> 1;
        if (pos <= mid)
            update(2 * idx + 1, low, mid, pos, value);
        else
            update(2 * idx + 2, mid + 1, high, pos, value);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
};

int main()
{
    vector<int> v = {5, 2, 11, 0, 78, -4, 3, 66, -7};
    int n = v.size();
    SegTree s(n);
    s.build(0, 0, n - 1, v);
    s.update(0,0,n-1,5,-80);
    cout << s.query(0, 0, n - 1, 0, 6) << endl;
    return 0;
}