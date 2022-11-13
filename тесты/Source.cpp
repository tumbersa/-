#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using tElem = int;
struct Stack {
	tElem info;
	Stack* next;
};
void init(Stack*& top) {
	top = NULL;
}

bool isEmpty(Stack* top) {
	return top == nullptr;
}
void push(Stack*& top, tElem x) {
	Stack* p = new Stack;
	p->info = x;
	p->next = top;
	top = p;
}

tElem pop(Stack*& top) {
	if (!isEmpty(top)) {
		Stack* p = top;
		tElem x;
		x = p->info;
		top = top->next;
		p->next = nullptr;
		delete p;
		return x;
	}
	else return NULL;
}

void print(Stack*& top) {
	Stack* copyStack;
	init(copyStack);
	while (top) {
		tElem x = pop(top);
		push(copyStack, x);
	}
	while (copyStack) {
		tElem x = pop(copyStack);
		cout << x << " ";
		push(top, x);
	}
	cout << endl;
}

void clear(Stack*& top) {
	tElem x;
	while (top)
		x = pop(top);
}

void push(Stack*& top, tElem x, tElem y) {
	push(top, x);
	push(top, y);
}

void rev(Stack*& top) {
	Stack* top2 = new Stack;
	init(top2);
	while (top) {
		push(top2, pop(top));
	}
	Stack* top3 = new Stack;
	init(top3);
	while (top2) {
		push(top3, pop(top2));
	}
	while (top3) {
		push(top, pop(top3));
	}
}

void searchdel(Stack*& voz, int r1, int r2) {
	if (!isEmpty(voz)) {
		int a2 = pop(voz), a1 = pop(voz);
		Stack* temp = new Stack;
		init(temp);
		while (voz && a2 != r2 || a1 != r1) {
			push(temp, a1, a2);
			a2 = pop(voz);
			a1 = pop(voz);
		}
		while (temp)
			push(voz, pop(temp), pop(temp));
	}
}





void print(int*** b) {
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3 * 4; j++)
				cout << b[k][i][j] << " ";
			cout << endl;
		}
		cout << endl << endl;
	}
}

void print(bool a[3][4]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}
int main() {

	int x2, y2;//координаты точки возвращения
	int	y3, x3;//вспомогательные переменные для перехода в точку воззврата
	Stack* voz = new Stack;
	init(voz);
	int k1 = 0;
	int x1 = -1, y1 = -1;//предыдущие координаты

	bool a[3][4];
	a[0][0] = 0; a[0][1] = 0; a[0][2] = 0; a[0][3] = 1;
	a[1][0] = 0; a[1][1] = 1; a[1][2] = 1; a[1][3] = 1;
	a[2][0] = 1; a[2][1] = 0; a[2][2] = 0; a[2][3] = 0;

	print(a);

	int n = 3, m = 4;

	Stack* top = new Stack;
	init(top);
	cout << (isEmpty(top)) << endl;

	int*** b = new int** [4];
	for (int k = 0; k < 4; k++)
		b[k] = new int* [5];
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 5; i++)
			b[k][i] = new int[n * m];
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < n * m; j++)
				b[k][i][j] = -1;
	print(b);
	bool f = 1;//для выхода из первого цикла
	bool f1 = 0;//для перехода в режим возвращения
	bool f2 = 0;//запись соседней точки и удаление точки возврата
	int x = 0, y = 0;

	//______________________________________________________________________

	push(top, x, y);

	while (f) {

		cout << x << " " << y << "f1="<<f1 << endl;
		print(top);

		f2 = 0;

		for (int i = 1; i < 5; i++)
			for (int j = 0; j < n * m; j++)
				if (x == b[2][i][j] && y == b[3][i][j]) {
					b[0][i][j] = b[2][i][j];
					b[1][i][j] = b[3][i][j];
					for (int u = 1; u < 5; u++)
						if (b[0][u][j] == -2 && b[1][u][j] == -2) f2 = 1;
					if (f2 == 0) {
						for (int i1 = 0; i1 < 5; i1++) {
							searchdel(voz, b[0][i1][j], b[1][i1][j]);
							b[0][i1][j] = -1;
							b[1][i1][j] = -1;
						}
					}
					f2 = 1;//чтобы не удалились другие точки
				}


		if (f1) {
			y2 = pop(voz);
			x2 = pop(voz);
			x = x2;
			y = y2;
			if (!isEmpty(voz)) if (voz->info == -1) pop(voz);
			y3 = pop(top);
			x3 = pop(top);
			Stack* temp1 = new Stack;//туда
			init(temp1);
			Stack* temp2 = new Stack;//обратно
			init(temp2);
			push(temp1, y3, x3);
			while (x3 != x2 || y3 != y2) {
				y3 = pop(top);
				x3 = pop(top);
				push(temp1, y3, x3);
				push(temp2, x3, y3);
				k1++;
			}
			cout << endl;
			rev(temp2);
			while (temp1) {
				push(top, pop(temp1));
			}
			while (temp2) {
				push(top, pop(temp2));
			}
			f1 = 0;
			
		}
		else {
			//////
			////0 ->
			////|
			////V
			if (x == 0 && y == 0) {
				if (a[x][y + 1] != 0 && a[x + 1][y] != 0) {
					f = 0;
				}
				else
				if (a[x][y + 1] == 0 && a[x + 1][y] != 0) {

					if (x1 != x || y1 != y + 1) {
						k1++;
						push(top, x, y + 1);
						y += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x + 1][y] == 0) {

					if (x1 != x + 1 || y1 != y) {
						k1++;
						push(top, x + 1, y);
						x += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else	
				if (a[x][y + 1] == 0 && a[x + 1][y] == 0) {
					k1++;
					if (x1 == -1 && y1 == -1) {
						bool f4 = 0;
						int t;
						for (t = 0; t < n * m && !f4; t++)
							if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
						if (!f4) {
							int j = n * m - 1;
							bool f3 = 1;
							while (f3 && j != 0) {
								if (b[0][0][j] != -1) { f3 = 0; j++; }
								else j--;
							}
							b[0][0][j] = x; b[2][0][j] = x;
							b[1][0][j] = y; b[3][0][j] = y;

							b[0][1][j] = x; b[2][1][j] = x;
							b[1][1][j] = y + 1; b[3][1][j] = y + 1;

							b[0][2][j] = -2; b[2][2][j] = x + 1;
							b[1][2][j] = -2; b[3][2][j] = y;

							if (!isEmpty(voz)) push(voz, -1);
							push(voz, x, y);

							push(top, x, y + 1);
							y += 1;

						}
						else
						{
							for (int t1 = 0; t1 < 5; t1++) {
								b[0][t1][t] = -1;
								b[1][t1][t] = -1;
							}
							push(top, x + 1, y);
							x += 1;
						}
					}
					else {
						if (x1 == 0 && y1 == 1) {
							push(top, x + 1, y);
							x += 1;
						}
						if (x1 == 1 && y1 == 0) {
							push(top, x, y+1);
							y += 1;
						}
					}

				}
			}
			else
			/*//////////
				  <-0///
					|///
					V */
			if (x == 0 && y == m - 1) {
				if (a[x][y - 1] != 0 && a[x + 1][y] != 0) {
					f = 0;
				}
				else
				if (a[x][y - 1] == 0 && a[x + 1][y] != 0) {
					if (x1 != x || y1 != y - 1) {
						k1++;
						push(top, x, y - 1);
						y -= 1;
					}

					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y - 1] != 0 && a[x + 1][y] == 0) {
					if (x1 != x + 1 || y1 != y) {
						k1++;
						push(top, x + 1, y);
						x += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y - 1] == 0 && a[x + 1][y] == 0) {
					k1++;
					if (x1 == -1 && y1 == -1) {
						bool f4 = 0;
						int t;
						for (t = 0; t < n * m && !f4; t++)
							if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
						if (!f4) {
							int j = n * m - 1;
							bool f3 = 1;
							while (f3 && j != 0) {
								if (b[0][0][j] != -1) { f3 = 0; j++; }
								else j--;
							}
							b[0][0][j] = x; b[2][0][j] = x;
							b[1][0][j] = y; b[3][0][j] = y;

							b[0][1][j] = x; b[2][1][j] = x;
							b[1][1][j] = y - 1; b[3][1][j] = y - 1;

							b[0][2][j] = -2; b[2][2][j] = x + 1;
							b[1][2][j] = -2; b[3][2][j] = y;

							if (!isEmpty(voz)) push(voz, -1);
							push(voz, x, y);

							push(top, x, y - 1);
							y -= 1;

						}
						else
						{
							for (int t1 = 0; t1 < 5; t1++) {
								b[0][t1][t] = -1;
								b[1][t1][t] = -1;
							}
							push(top, x + 1, y);
							x += 1;
						}
					}
					else {
						if (x1 == 0 && y1 == n-2) {
							push(top, x + 1, y);
							x += 1;
						}
						if (x1 == 1 && y1 == n-1) {
							push(top, x, y - 1);
							y -= 1;
						}
					}
				}
			}
			else
			/* /////////////
				   <-0->
					 |
					 V
			*/
			if (x == 0 && y != 0 && y != m - 1) {
				if (a[x][y + 1] != 0 && a[x + 1][y] != 0 && a[x][y - 1] != 0) {
					f = 0;
				}
				else
				if (a[x][y + 1] == 0 && a[x + 1][y] != 0 && a[x][y - 1] != 0) {
					if (x1 != x || y1 != y + 1) {
						k1++;
						push(top, x, y + 1);
						y += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x + 1][y] == 0 && a[x][y - 1] != 0) {
					if (x1 != x + 1 || y1 != y) {
						k1++;
						push(top, x + 1, y);
						x += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x + 1][y] != 0 && a[x][y - 1] == 0) {
					if (x1 != x || y1 != y - 1) {
						k1++;
						push(top, x, y - 1);
						y -= 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] == 0 && a[x + 1][y] == 0 || a[x][y + 1] == 0 && a[x][y - 1] == 0 || a[x][y - 1] == 0 && a[x + 1][y] == 0) {
					k1++;
					if (x1 == -1 && y1 == -1) {
						bool f4 = 0;
						int t;
						for (t = 0; t < n * m && !f4; t++)
							if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
						int j = n * m - 1;
						bool f3 = 1;
						while (f3 && j != 0) {
							if (b[0][0][j] != -1) { f3 = 0; j++; }
							else j--;
						}
						if (!f4) {

							b[0][0][j] = x; b[2][0][j] = x;
							b[1][0][j] = y; b[3][0][j] = y;

							b[0][1][j] = x; b[2][1][j] = x;
							b[1][1][j] = y + 1; b[3][1][j] = y + 1;

							b[0][2][j] = -2; b[2][2][j] = x + 1;
							b[1][2][j] = -2; b[3][2][j] = y;

							b[0][3][j] = -2; b[2][3][j] = x;
							b[1][3][j] = -2; b[3][3][j] = y - 1;

							if (!isEmpty(voz)) push(voz, -1);
							push(voz, x, y);

							push(top, x, y + 1);
							y += 1;

						}
						else
						{
							int k2 = 0;
							for (int t2 = 0; t2 < 5; t2++) {
								if (b[0][t2][t] == -2 && b[1][t2][t] == -2) {
									k2++;
								}
							}
							if (k2 == 1) {
								for (int t1 = 0; t1 < 5; t1++) {
									b[0][t1][t] = -1;
									b[1][t1][t] = -1;
								}
								push(top, x, y - 1);
								y -= 1;
							}
							else {
								if (!isEmpty(voz)) push(voz, -1);
								push(voz, x, y);
								push(top, x + 1, y);
								b[0][2][j] = x + 1;
								b[1][2][j] = y;
								x += 1;
							}
						}
					}
					else {
					}

				}
			}
			else
			/*
			/////^
			/////|
			/////0->
			/////|
			/////V
			*/
			if (x != 0 && x != n - 1 && y == 0) {
				if (a[x][y + 1] != 0 && a[x + 1][y] != 0 && a[x - 1][y] != 0) {
					f = 0;
				}
				else
				if (a[x][y + 1] == 0 && a[x + 1][y] != 0 && a[x - 1][y] != 0) {
					if (x1 != x || y1 != y + 1) {
						k1++;
						push(top, x, y + 1);
						y += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x + 1][y] == 0 && a[x - 1][y] != 0) {
					if (x1 != x+1 || y1 != y) {
						k1++;
						push(top, x, y + 1);
						x += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x + 1][y] != 0 && a[x - 1][y] == 0) {
					if (x1 != x-1 || y1 != y) {
						k1++;
						push(top, x-1, y);
						x -= 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] == 0 && a[x + 1][y] == 0 || a[x][y + 1] == 0 && a[x - 1][y] == 0 || a[x + 1][y] == 0 && a[x - 1][y] == 0) {
					k1++;
					if (x1 == -1 && y1 == -1) {
						bool f4 = 0;
						int t;
						for (t = 0; t < n * m && !f4; t++)
							if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
						int j = n * m - 1;
						bool f3 = 1;
						while (f3 && j != 0) {
							if (b[0][0][j] != -1) { f3 = 0; j++; }
							else j--;
						}
						if (!f4) {

							b[0][0][j] = x; b[2][0][j] = x;
							b[1][0][j] = y; b[3][0][j] = y;

							b[0][1][j] = x; b[2][1][j] = x;
							b[1][1][j] = y + 1; b[3][1][j] = y + 1;

							b[0][2][j] = -2; b[2][2][j] = x + 1;
							b[1][2][j] = -2; b[3][2][j] = y;

							b[0][3][j] = -2; b[2][3][j] = x - 1;
							b[1][3][j] = -2; b[3][3][j] = y;

							if (!isEmpty(voz)) push(voz, -1);
							push(voz, x, y);

							push(top, x, y + 1);
							y += 1;

						}
						else
						{
							int k2 = 0;
							for (int t2 = 0; t2 < 5; t2++) {
								if (b[0][t2][t] == -2 && b[1][t2][t] == -2) {
									k2++;
								}
							}
							if (k2 == 1) {
								for (int t1 = 0; t1 < 5; t1++) {
									b[0][t1][t] = -1;
									b[1][t1][t] = -1;
								}
								push(top, x - 1, y);
								x -= 1;
							}
							else {
								if (!isEmpty(voz)) push(voz, -1);
								push(voz, x, y);
								push(top, x + 1, y);						
								b[0][2][j] = x + 1;
								b[1][2][j] = y;
								x += 1;
							}
						}
					}
					else {
					
					}
				}
			}
			else
			/*      ///////
				   ^///////
				   |///////
				 <-0///////
			 //////////////
			*/
			if (x == n - 1 && y == m - 1) {
				if (a[x][y - 1] != 0 && a[x - 1][y] != 0)
				{
					f = 0;
				}
				else
				if (a[x][y - 1] == 0 && a[x - 1][y] != 0) {
					if (x1 != x || y1 != y - 1) {
						k1++;
						push(top, x, y - 1);
						y -= 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y - 1] != 0 && a[x - 1][y] == 0) {
					if (x1 != x-1 || y1 != y ) {
						k1++;
						push(top, x-1, y);
						x -= 1;
					}

					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y - 1] == 0 && a[x - 1][y] == 0) {
					k1++;
					if (x1 == -1 && y1 == -1) {
						bool f4 = 0;
						int t;
						for (t = 0; t < n * m && !f4; t++)
							if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
						if (!f4) {
							int j = n * m - 1;
							bool f3 = 1;
							while (f3 && j != 0) {
								if (b[0][0][j] != -1) { f3 = 0; j++; }
								else j--;
							}
							b[0][0][j] = x; b[2][0][j] = x;
							b[1][0][j] = y; b[3][0][j] = y;

							b[0][1][j] = x; b[2][1][j] = x;
							b[1][1][j] = y - 1; b[3][1][j] = y - 1;

							b[0][2][j] = -2; b[2][2][j] = x - 1;
							b[1][2][j] = -2; b[3][2][j] = y;

							if (!isEmpty(voz)) push(voz, -1);
							push(voz, x, y);

							push(top, x, y - 1);
							y -= 1;

						}
						else
						{
							for (int t1 = 0; t1 < 5; t1++) {
								b[0][t1][t] = -1;
								b[1][t1][t] = -1;
							}
							push(top, x - 1, y);
							x -= 1;
						}
					}
					else {
						if (x1 == m-1 && y1 == n - 2) {
							push(top, x - 1, y);
							x -= 1;
						}
						if (x1 == m-2 && y1 == n - 1) {
							push(top, x, y - 1);
							y -= 1;
						}
					}
				}
			}
			else
				//////
			//////^
			//////|
			//////0 ->
			////////////
				if (x == n - 1 && y == 0) {
					if (a[x][y + 1] != 0 && a[x - 1][y] != 0) {
						f = 0;
					}
					if (a[x][y + 1] == 0 && a[x - 1][y] != 0) {
						if (x1 != x || y1 != y + 1) {
							k1++;
							push(top, x, y + 1);
							y += 1;
						}

						else if (isEmpty(voz)) {
							f = 0;
						}
						else {
							f1 = 1;
						}
					}
					else
					if (a[x][y + 1] != 0 && a[x - 1][y] == 0) {
						if (x1 != x-1 || y1 != y) {
							k1++;
							push(top, x-1, y);
							x -= 1;
						}

						else if (isEmpty(voz)) {
							f = 0;
						}
						else {
							f1 = 1;
						}
					}
					else
					if (a[x][y + 1] == 0 && a[x - 1][y] == 0) {
						k1++;
						if (x1 == -1 && y1 == -1) {
							bool f4 = 0;
							int t;
							for (t = 0; t < n * m && !f4; t++)
								if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
							if (!f4) {
								int j = n * m - 1;
								bool f3 = 1;
								while (f3 && j != 0) {
									if (b[0][0][j] != -1) { f3 = 0; j++; }
									else j--;
								}
								b[0][0][j] = x; b[2][0][j] = x;
								b[1][0][j] = y; b[3][0][j] = y;

								b[0][1][j] = x; b[2][1][j] = x;
								b[1][1][j] = y + 1; b[3][1][j] = y + 1;

								b[0][2][j] = -2; b[2][2][j] = x - 1;
								b[1][2][j] = -2; b[3][2][j] = y;

								if (!isEmpty(voz)) push(voz, -1);
								push(voz, x, y);

								push(top, x, y + 1);
								y += 1;

							}
							else
							{
								for (int t1 = 0; t1 < 5; t1++) {
									b[0][t1][t] = -1;
									b[1][t1][t] = -1;
								}
								push(top, x - 1, y);
								x -= 1;
							}
						}
						else {
							if (x1 == m - 1 && y1 == 1) {
								push(top, x - 1, y);
								x -= 1;
							}
							if (x1 == m - 2 && y1 == 0) {
								push(top, x, y + 1);
								y += 1;
							}
						}
					}
				}
			else
				/*
					^
					|
				  <-0->
			/////////////////
			*/
			if (x == n - 1 && y != 0 && y != m - 1) {
				if (a[x][y + 1] != 0 && a[x - 1][y] != 0 && a[x][y - 1] != 0) {
					f = 0;
				}
				else
				if (a[x][y + 1] == 0 && a[x - 1][y] != 0 && a[x][y - 1] != 0) {
					if (x1 != x || y1 != y + 1) {
						k1++;
						push(top, x, y + 1);
						y += 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x - 1][y] == 0 && a[x][y - 1] != 0) {
					if (x1 != x-1 || y1 != y) {
						k1++;
						push(top, x-1, y);
						x -= 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else
				if (a[x][y + 1] != 0 && a[x - 1][y] != 0 && a[x][y - 1] == 0) {
					if (x1 != x || y1 != y - 1) {
						k1++;
						push(top, x, y - 1);
						y -= 1;
					}
					else if (isEmpty(voz)) {
						f = 0;
					}
					else {
						f1 = 1;
					}
				}
				else//при трёх открытых путях, проработать два открытых и приход со стороны
				if (a[x][y + 1] == 0 && a[x - 1][y] == 0 || a[x - 1][y] == 0 && a[x][y - 1] == 0 || a[x][y + 1] == 0 && a[x][y - 1] == 0) {
					k1++;
					if (x1 == -1 && y1 == -1) {
						bool f4 = 0;
						int t;
						for (t = 0; t < n * m && !f4; t++)
							if (b[0][0][t] == x && b[1][0][t] == y) f4 = 1;
						int j = n * m - 1;
						bool f3 = 1;
						while (f3 && j != 0) {
							if (b[0][0][j] != -1) { f3 = 0; j++; }
							else j--;
						}
						if (!f4) {

							b[0][0][j] = x; b[2][0][j] = x;
							b[1][0][j] = y; b[3][0][j] = y;

							b[0][1][j] = x; b[2][1][j] = x;
							b[1][1][j] = y + 1; b[3][1][j] = y + 1;

							b[0][2][j] = -2; b[2][2][j] = x - 1;
							b[1][2][j] = -2; b[3][2][j] = y;

							b[0][3][j] = -2; b[2][3][j] = x;
							b[1][3][j] = -2; b[3][3][j] = y-1;

							if (!isEmpty(voz)) push(voz, -1);
							push(voz, x, y);

							push(top, x, y + 1);
							y += 1;

						}
						else
						{
							int k2 = 0;
							for (int t2 = 0; t2 < 5; t2++) {
								if (b[0][t2][t] == -2 && b[1][t2][t] == -2) {
									k2++;
								}
							}
							if (k2 == 1) {
								for (int t1 = 0; t1 < 5; t1++) {
									b[0][t1][t] = -1;
									b[1][t1][t] = -1;
								}
								push(top, x, y-1);
								y -= 1;
							}
							else {
								if (!isEmpty(voz)) push(voz, -1);
								push(voz, x, y);
								push(top, x - 1, y);								
								b[0][2][j] = x - 1;
								b[1][2][j] = y;
								x -= 1;
							}
						}
					}
					else {

					}
				}
			}





		}

		print(b);
		print(voz);
		cout << "__________" << endl;
		if (!isEmpty(top)) {
			int y11 = pop(top);
			int x11 = pop(top);
			y1 = pop(top);
			x1 = pop(top);
			push(top, x1, y1);
			push(top, x11, y11);
		}
		/*f = 0;*/
	}
	print(top);
	return 0;
}