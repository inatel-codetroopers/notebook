int merge_sort(vector<int> &v) {
	if(v.size() == 1) return 0;
	int inv = 0;
	vector<int> a, b;
	rep(i, 0, v.size()/2)
		a.pb(v[i]);
	rep(i, v.size()/2, v.size())
		b.pb(v[i]);
	inv = merge_sort(a) + merge_sort(b);
	a.pb(1<<30); b.pb(1<<30);
	int i = 0, j = 0;
	rep(k, 0, v.size()) {
		if(a[i] <= b[j])
			v[k] = a[i++];
		else {
			v[k] = b[j++];
			inv += a.size() - i -1;
		}
	}
	return inv;
}
