set <iii> st;
int qtc[100010];
void refreshInterval(int l, int r, int nc){
	set <iii> :: iterator it;
	vector <iii> er;
	vector <iii> in;
	iii aux;
	
	it = st.lower_bound(iii(ii(l, 0), 0));
	if(it!=st.begin()) it--;
	for(it = it; it!=st.end(); it++){
		aux = *it;
		if(aux.F.F > r) break; // out of the interval
		if(aux.F.S < l) continue; // before the interval
		er.pb(aux);
	}
	
	rep(i, 0, er.size()){ // remove 
		aux = er[i];
		qtc[aux.S] -= (aux.F.S - aux.F.F + 1);
		st.erase(st.find(aux));
		if(l>aux.F.F) in.pb(iii(ii(aux.F.F, l-1), aux.S));
		if(r<aux.F.S) in.pb(iii(ii(r+1, aux.F.S), aux.S));
	}
	
	in.pb(iii(ii(l, r), nc));
	sort(in.begin(), in.end());
	
	rep(i, 0, in.size()){ // insert
		aux = in[i];
		it = st.lower_bound(aux);
		if(it!=st.begin()) it--;
		if(it!=st.end() && (*it).S==aux.S && (*it).F.S==aux.F.F-1){ // remove in case adjacente segments are equal
			aux.F.F = (*it).F.F;
			qtc[aux.S] -= ((*it).F.S - (*it).F.F + 1);
			st.erase(it);
		}
		qtc[aux.S] += (aux.F.S - aux.F.F + 1);
		st.insert(aux);
	}
}

int main(){
	// build initial states
	st.insert(iii(ii(0, 10), 1));
	qtc[1] = 10;
	return 0;
}