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

    /*

        (a , b) ->sum will be (a,c)+(c,b)
        /     \
    (a , c)  (c , b)

    */
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

    int query(int idx, int low, int high, int l, int r)
    {
        // no-overalp
        if (high < l || low > r)
            return 0;
        // complete overlap
        if (l <= low && high <= r)
            return seg[idx];
        // partial overlap

        int mid = (low + high) >> 1;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        return left + right;
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
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    void display()
    {
        for_each(seg.begin(), seg.end(), [](int value)
                 { cout << value << " "; });
        cout << endl;
    }
};

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    SegTree s(a.size());
    s.build(0, 0, a.size() - 1, a);
    s.display();
    s.update(0, 0, a.size() - 1, 2, 50);
    s.display();
    cout << s.query(0, 0, a.size() - 1, 2, 5) << endl;
    return 0;
}