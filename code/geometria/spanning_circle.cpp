//Finds a circle of the minimum area enclosing a 2D point set.
typedef pair<point, double> circle; // {ponto,raio}
bool in_circle(circle C, point p){ // ponto dentro de circulo?
	return cmp(abs(p-C.first), C.second) <= 0;
}
// menor circulo que engloba o triangulo (P,Q,R)
point circumcenter(point p, point q, point r){
	point a = p-r, b = q-r, c, ret;
	c = point(dot(a,p+r), dot(b,q+r)) * 0.5;
	ret=point(cross(c, point(a.y, b.y)), cross(point(a.x, b.x),c)) / cross(a,b);
	return ret;
}
circle spanning_circle(const vector<point>& T){
	int n = T.size();
	random_shuffle(all(T));
	circle C(point(), -INF);
	rep(i, 0, n) if(!in_circle(C, T[i])){
		C = circle(T[i], 0);
		rep(j, 0, i) if (!in_circle(C, T[j])){
			C = circle((T[i]+T[j])/2, abs(T[i]-T[j])/2);
			rep(k, 0, j) if (!in_circle(C, T[k])){
				point O = circumcenter(T[i], T[j], T[k]);
				C = circle(O, abs(O-T[k]));
			}
		}
	}
	return C;
}
