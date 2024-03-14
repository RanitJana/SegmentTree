#include <bits/stdc++.h>
using namespace std;

class SegTree
{
    vector<int> seg, lazy;

public:
    SegTree(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
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

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    void update(int idx, int low, int high, int l, int r, int value)
    {
        // pending operation must be cleared first
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];
            if (low != high) // it indicates that idx have children and operations must be propagate down
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        // no overlap
        if (high < l || low > r)
            return;
        // complete overalp
        if (l <= low && high <= r)
        {
            seg[idx] += (high - low + 1) * value;
            if (low != high)
            {
                lazy[2 * idx + 1] += value;
                lazy[2 * idx + 2] += value;
            }
            return;
        }
        // partial overlap
        int mid = (low + high) >> 1;

        update(2 * idx + 1, low, mid, l, r, value);
        update(2 * idx + 2, mid + 1, high, l, r, value);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int high, int l, int r)
    {
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];
            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        // no overlap
        if (high < l || low > r)
            return 0;
        // complete overalp
        if (l <= low && high <= r)
            return seg[idx];
        // partial overlap
        int mid = (low + high) >> 1;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        seg[idx] + seg[2 * idx + 1] + seg[2 * idx + 2];

        return left + right;
    }

    void display()
    {
        for_each(seg.begin(), seg.end(), [](int val)
                 { cout << val << " "; });
        cout << endl;
    }
};

int main()
{
    vector<int> a = {1, 4, 2, 1, 3, 1};
    int n = a.size();
    SegTree s(n);
    s.build(0, 0, n - 1, a);
    cout << s.query(0, 0, n - 1, 0, 2) << endl;
    s.update(0, 0, n - 1, 0, 3, 3);
    cout << s.query(0, 0, n - 1, 0, 3) << endl;
    return 0;
}
