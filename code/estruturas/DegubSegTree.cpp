const int QT = 16; //potência de 2

void printa() {
	int no = 1;
	while(no < 2*n) {
		rep(i, 0, no) {
			cout << setw(QT/no) << setfill(' ') << "";
			cout << setw(QT/no) << setfill('_') << arvore[no+i];
			cout << setw(QT/no) << "";
			cout << setw(QT/no) << setfill(' ') << "";
		}
		cout << endl;
		no*=2;
	}
}
