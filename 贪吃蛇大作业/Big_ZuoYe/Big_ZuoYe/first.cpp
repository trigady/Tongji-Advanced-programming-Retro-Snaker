#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <iostream>
#include <string.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <time.h> 

#define REC "record.txt"

using namespace std;
class Menu;

void int2char(int a, char *s) {
	char c[10];
	int i = 0, temp = a, j = 0;
	if (a == 0) {
		c[0] = '0';
		i = 1;
	}
	else {
		for (; temp != 0;) {
			c[i] = temp % 10 + '0';
			i++;
			temp /= 10;
		}
	}
	i--;
	for (; i >= 0; j++) {
		s[j] = c[i];
		i--;
	}
	s[j] = '\0';
}

struct pos {
	int x;
	int y;
};

class Game {
public:
	int width = 800;
	int height = 630;

	void init_game() {
		initgraph(width, height);
	}
	void back();

	virtual void init2() {
		cerr << "错误！";
	}
	virtual void listen() {
		cerr << "错误！";
	}
};

class snake {
public:
	pos add;
	snake *next = NULL;
	bool head = false;
	char tow = 'u';
	int length = 0;

	snake* cut(snake *p, int n) {
		if (n == 0) {
			return p;
		}
		snake *k;
		k = p->next;
		delete p;
		return cut(k, n - 1);
	}

	snake* eat(char tow) {
		this->head = false;
		this->tow = tow;
		snake *p = new snake;
		switch (tow) {
			case 'u':
				p->add.x = this->add.x;
				p->add.y = this->add.y - 1;
				break;
			case 'l':
				p->add.y = this->add.y;
				p->add.x = this->add.x - 1;
				break;
			case 'd':
				p->add.x = this->add.x;
				p->add.y = this->add.y + 1;
				break;
			case 'r':
				p->add.y = this->add.y;
				p->add.x = this->add.x + 1;
				break;
		}
		p->head = true;
		p->tow = tow;
		p->length = this->length + 1;
		p->next = this;
		return p;
	}

	snake* move(char tow) {
		this->head = false;

		snake *p, *q;
		for (p = this; p->next->next != NULL; p = p->next);
		q = p->next;
		delete q;
		p->next = NULL;
		return eat(tow);
	}

	pos next_pos(char tow) {
		pos ans;
		switch (tow) {
			case 'u':
				ans.x = this->add.x;
				ans.y = this->add.y - 1;
				break;
			case 'l':
				ans.y = this->add.y;
				ans.x = this->add.x - 1;
				break;
			case 'd':
				ans.x = this->add.x;
				ans.y = this->add.y + 1;
				break;
			case 'r':
				ans.y = this->add.y;
				ans.x = this->add.x + 1;
				break;
		}
		return ans;
	}

	pos tail_pos() {
		snake *p;
		for (p = this; p->next != NULL; p = p->next);
		return p->add;
	}

	bool judge(snake *a, pos p) {
		if (a->next == NULL) {
			return true;
		}
		if (a->add.x == p.x&&a->add.y == p.y) {
			return false;
		}
		return judge(a->next, p);
	}

	void draw(char a[40][30]) {
		snake *p = this;
		char x;
		switch (p->tow) {
			case 'u':
				x = 'a';
				break;
			case 'l':
				x = 'b';
				break;
			case 'd':
				x = 'c';
				break;
			case 'r':
				x = 'd';
				break;
		}
		a[p->add.x][p->add.y] = x;
		p = p->next;

		for (;;) {
			if (p->next == NULL) {
				switch (p->tow) {
					case 'u':
						x = 'g';
						break;
					case 'l':
						x = 'h';
						break;
					case 'd':
						x = 'e';
						break;
					case 'r':
						x = 'f';
						break;
				}
				a[p->add.x][p->add.y] = x;
				break;
			}

			switch (p->tow) {
				case 'u':
					switch (p->next->tow) {
						case 'u':
							x = '2';
							break;
						case 'l':
							x = '4';
							break;
						case 'r':
							x = '3';
							break;
					}
					break;
				case 'l':
					switch (p->next->tow) {
						case 'u':
							x = '6';
							break;
						case 'l':
							x = '1';
							break;
						case 'd':
							x = '3';
							break;
					}
					break;
				case 'd':
					switch (p->next->tow) {
						case 'l':
							x = '5';
							break;
						case 'd':
							x = '2';
							break;
						case 'r':
							x = '6';
							break;
					}
					break;
				case 'r':
					switch (p->next->tow) {
						case 'u':
							x = '5';
							break;
						case 'd':
							x = '4';
							break;
						case 'r':
							x = '1';
							break;
					}
					break;
			}
			a[p->add.x][p->add.y] = x;
			p = p->next;
		}
	}

	void draw(char a[80][60]) {
		snake *p = this;
		char x;
		switch (p->tow) {
			case 'u':
				x = 'a';
				break;
			case 'l':
				x = 'b';
				break;
			case 'd':
				x = 'c';
				break;
			case 'r':
				x = 'd';
				break;
		}
		a[p->add.x][p->add.y] = x;
		p = p->next;

		for (;;) {
			if (p->next == NULL) {
				switch (p->tow) {
					case 'u':
						x = 'g';
						break;
					case 'l':
						x = 'h';
						break;
					case 'd':
						x = 'e';
						break;
					case 'r':
						x = 'f';
						break;
				}
				a[p->add.x][p->add.y] = x;
				break;
			}

			switch (p->tow) {
				case 'u':
					switch (p->next->tow) {
						case 'u':
							x = '2';
							break;
						case 'l':
							x = '4';
							break;
						case 'r':
							x = '3';
							break;
					}
					break;
				case 'l':
					switch (p->next->tow) {
						case 'u':
							x = '6';
							break;
						case 'l':
							x = '1';
							break;
						case 'd':
							x = '3';
							break;
					}
					break;
				case 'd':
					switch (p->next->tow) {
						case 'l':
							x = '5';
							break;
						case 'd':
							x = '2';
							break;
						case 'r':
							x = '6';
							break;
					}
					break;
				case 'r':
					switch (p->next->tow) {
						case 'u':
							x = '5';
							break;
						case 'd':
							x = '4';
							break;
						case 'r':
							x = '1';
							break;
					}
					break;
			}
			a[p->add.x][p->add.y] = x;
			p = p->next;
		}
	}
};

class snake2 {
public:
	pos add;
	snake2 *next = NULL;
	bool head = false;
	char tow = 'u';
	int length = 0;

	snake2* cut(snake2 *p, int n) {
		if (n == 0) {
			return p;
		}
		snake2 *k;
		k = p->next;
		delete p;
		return cut(k, n - 1);
	}

	snake2* eat(char tow) {
		this->head = false;
		this->tow = tow;
		snake2 *p = new snake2;
		switch (tow) {
			case 'u':
				p->add.x = this->add.x;
				p->add.y = this->add.y - 1;
				break;
			case 'l':
				p->add.y = this->add.y;
				p->add.x = this->add.x - 1;
				break;
			case 'd':
				p->add.x = this->add.x;
				p->add.y = this->add.y + 1;
				break;
			case 'r':
				p->add.y = this->add.y;
				p->add.x = this->add.x + 1;
				break;
		}
		p->head = true;
		p->tow = tow;
		p->length = this->length + 1;
		p->next = this;
		return p;
	}

	snake2* move(char tow) {
		this->head = false;

		snake2 *p, *q;
		for (p = this; p->next->next != NULL; p = p->next);
		q = p->next;
		delete q;
		p->next = NULL;
		return eat(tow);
	}

	pos next_pos(char tow) {
		pos ans;
		switch (tow) {
			case 'u':
				ans.x = this->add.x;
				ans.y = this->add.y - 1;
				break;
			case 'l':
				ans.y = this->add.y;
				ans.x = this->add.x - 1;
				break;
			case 'd':
				ans.x = this->add.x;
				ans.y = this->add.y + 1;
				break;
			case 'r':
				ans.y = this->add.y;
				ans.x = this->add.x + 1;
				break;
		}
		return ans;
	}

	pos tail_pos() {
		snake2 *p;
		for (p = this; p->next != NULL; p = p->next);
		return p->add;
	}

	bool judge(snake2 *a, pos p) {
		if (a->next == NULL) {
			return true;
		}
		if (a->add.x == p.x&&a->add.y == p.y) {
			return false;
		}
		return judge(a->next, p);
	}

	void draw(char a[40][30]) {
		snake2 *p = this;
		char x;
		switch (p->tow) {
			case 'u':
				x = 't';
				break;
			case 'l':
				x = 'u';
				break;
			case 'd':
				x = 'v';
				break;
			case 'r':
				x = 'w';
				break;
		}
		a[p->add.x][p->add.y] = x;
		p = p->next;

		for (;;) {
			if (p->next == NULL) {
				switch (p->tow) {
					case 'u':
						x = 'z';
						break;
					case 'l':
						x = '{';
						break;
					case 'd':
						x = 'x';
						break;
					case 'r':
						x = 'y';
						break;
				}
				a[p->add.x][p->add.y] = x;
				break;
			}

			switch (p->tow) {
				case 'u':
					switch (p->next->tow) {
						case 'u':
							x = 'o';
							break;
						case 'l':
							x = 'q';
							break;
						case 'r':
							x = 'p';
							break;
					}
					break;
				case 'l':
					switch (p->next->tow) {
						case 'u':
							x = 's';
							break;
						case 'l':
							x = 'n';
							break;
						case 'd':
							x = 'p';
							break;
					}
					break;
				case 'd':
					switch (p->next->tow) {
						case 'l':
							x = 'r';
							break;
						case 'd':
							x = 'o';
							break;
						case 'r':
							x = 's';
							break;
					}
					break;
				case 'r':
					switch (p->next->tow) {
						case 'u':
							x = 'r';
							break;
						case 'd':
							x = 'q';
							break;
						case 'r':
							x = 'n';
							break;
					}
					break;
			}
			a[p->add.x][p->add.y] = x;
			p = p->next;
		}
	}
};

class fruit {
public:
	pos add;
	char style = 'g';

	void draw(char a[40][30]) {
		if (style == 'g') {
			switch (a[add.x][add.y]) {
				case '0':
					a[add.x][add.y] = '7';
					break;
				case 'i':
					a[add.x][add.y] = 'l';
					break;
				case 'j':
					a[add.x][add.y] = 'm';
					break;
			}
		}
		else {
			a[add.x][add.y] = 'k';
		}

	}

	void draw(char a[80][60]) {
		if (style == 'g') {
			switch (a[add.x][add.y]) {
				case '0':
					a[add.x][add.y] = '7';
					break;
				case 'i':
					a[add.x][add.y] = 'l';
					break;
				case 'j':
					a[add.x][add.y] = 'm';
					break;
			}
		}
		else {
			a[add.x][add.y] = 'k';
		}

	}
};

class Game1 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 1;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 1) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	bool play() {
		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			settextcolor(0xffffff);
			settextcolor(0xffffff);
			setbkcolor(0x555555);
			settextstyle(60, 30, _T("楷体"));
			outtextxy(280, 270, "游戏结束");
			return false;
		}
		if (map[ne.x][ne.y] == '8') {
			settextcolor(0xffffff);
			setbkcolor(0x555555);
			settextstyle(60, 30, _T("楷体"));
			outtextxy(280, 270, "游戏结束");
			return false;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 1 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(life, &slif[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game2 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 1;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void stone() {
		snake *p = head;
		for (;;) {
			map[p->add.x][p->add.y] = '8';
			area--;
			if (p->next != NULL) {
				p = p->next;
			}
			else {
				break;
			}
		}
	}

	bool new_snake() {
		mes = 'u';
		int i, j;
		snake *p, *q;
		for (i = 20; i != 19; i++) {
			for (j = 14; j != 13; j++) {
				if (map[i][j] == '0'&&map[i][j + 1] == '0'&&map[i][j + 2] == '0') {
					head = new snake;
					head->head = true;
					head->add.x = i;
					head->add.y = j;

					p = new snake;
					head->next = p;
					p->add.x = i;
					p->add.y = j + 1;

					q = new snake;
					p->next = q;
					q->next = NULL;
					q->add.x = i;
					q->add.y = j + 2;

					return true;
				}

				if (j == 25) {
					j = 0;
				}
			}

			if (i == 38) {
				i = 1;
			}
		}

		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");

		return false;
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 2) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	bool play() {
		if (life == 0) {
			return false;
		}

		bool flag = true;
		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			stone();
			score -= 10;
			score = score < 0 ? 0 : score;
			flag = new_snake();
			life = flag ? life : 0;
			return flag;
		}
		if (map[ne.x][ne.y] == '8') {
			stone();
			score -= 10;
			score = score < 0 ? 0 : score;
			flag = new_snake();
			life = flag ? life : 0;
			return flag;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 2 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：∞";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game3 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 6;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void juice() {
		snake *p = head;
		for (;;) {
			map[p->add.x][p->add.y] = '7';
			area--;
			fruit_num++;
			if (p->next != NULL) {
				p = p->next;
			}
			else {
				break;
			}
		}
		refresh();
	}

	bool new_snake() {
		mes = 'u';
		int i, j;
		snake *p, *q;
		for (i = 20; i != 19; i++) {
			for (j = 14; j != 13; j++) {
				if (map[i][j] == '0'&&map[i][j + 1] == '0'&&map[i][j + 2] == '0') {
					head = new snake;
					head->head = true;
					head->add.x = i;
					head->add.y = j;

					p = new snake;
					head->next = p;
					p->add.x = i;
					p->add.y = j + 1;

					q = new snake;
					p->next = q;
					q->next = NULL;
					q->add.x = i;
					q->add.y = j + 2;

					return true;
				}

				if (j == 25) {
					j = 0;
				}
			}

			if (i == 38) {
				i = 1;
			}
		}

		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");

		return false;
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 3) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	bool play() {
		if (life == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			life--;
			score -= 10;
			score = score < 0 ? 0 : score;
			if (life == 0) {
				settextcolor(0xffffff);
				settextcolor(0xffffff);
				setbkcolor(0x555555);
				settextstyle(60, 30, _T("楷体"));
				outtextxy(280, 270, "游戏结束");
				return false;
			}
			else {
				juice();
				return new_snake();
			}
		}
		if (map[ne.x][ne.y] == '8') {
			life--;
			score -= 10;
			score = score < 0 ? 0 : score;
			if (life == 0) {
				settextcolor(0xffffff);
				settextcolor(0xffffff);
				setbkcolor(0x555555);
				settextstyle(60, 30, _T("楷体"));
				outtextxy(280, 270, "游戏结束");
				return false;
			}
			else {
				juice();
				return new_snake();
			}
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 3 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(score, &ssco[10]);
		int2char(life, &slif[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game4 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 1;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 4) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		for (int i = 5; i <= 8; i++) {
			for (int j = 5; j <= 8; j++) {
				map[i][j] = '9';
				map[i][j + 16] = '9';
				map[i + 26][j] = '9';
				map[i + 26][j + 16] = '9';
			}
		}
		area -= 64;

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");
	}

	void erase_s(snake *p, int n) {
		if (n == 0) {
			p->tow = p->next->tow;
			switch (p->tow) {
				case 'u':
					map[p->add.x][p->add.y] = 'a';
					break;
				case 'r':
					map[p->add.x][p->add.y] = 'd';
					break;
				case 'd':
					map[p->add.x][p->add.y] = 'c';
					break;
				case 'l':
					map[p->add.x][p->add.y] = 'b';
					break;
			}
			return;
		}
		map[p->add.x][p->add.y] = '0';
		erase_s(p->next, n - 1);
	}

	bool play() {
		if (life == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == '8') {
			if (length <= 5) {
				endit();
				return false;
			}
			erase_s(head, length - length / 2);
			head = head->cut(head, length - length / 2);
			length /= 2;
			score -= 10;
			score = score < 0 ? 0 : score;
			return true;
		}
		if (map[ne.x][ne.y] == '9') {
			if (length <= 4) {
				endit();
				return false;
			}
			erase_s(head, 2);
			head = head->cut(head, 2);
			length -= 2;
			score -= 10;
			score = score < 0 ? 0 : score;
			return true;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 4 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(life, &slif[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game5 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 1;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0' && map[p->add.x][p->add.y] != 'i' && map[p->add.x][p->add.y] != 'j') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 5) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		for (int i = 1; i <= 13; i++) {
			for (int j = 1; j <= 28; j++) {
				map[i][j] = 'i';
			}
		}

		for (int i = 26; i <= 38; i++) {
			for (int j = 1; j <= 28; j++) {
				map[i][j] = 'j';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");
	}

	void remap(pos add) {
		if (add.x <= 13) {
			map[add.x][add.y] = 'i';
		}
		else if (add.x >= 26) {
			map[add.x][add.y] = 'j';
		}
		else {
			map[add.x][add.y] = '0';
		}
	}

	bool play() {
		if (life == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h') || map[ne.x][ne.y] == 'i' || map[ne.x][ne.y] == 'j') {
			pos tail = head->tail_pos();
			remap(tail);
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7' || map[ne.x][ne.y] == 'l' || map[ne.x][ne.y] == 'm') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == '8') {
			endit();
			return false;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 5 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(life, &slif[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		bool flag = true;

		DWORD now, last;

		char temp = 'u';
		while (temp != 'q') {
			now = GetTickCount();
			last = now;

			while (!_kbhit()) {
				now = GetTickCount();
				if (head->add.x >= 26) {
					if ((int)(now - last) >= 500) {
						if (flag = play()) {
							now_t = flag ? clock() : end_t;
							draw();
							drawui();
						}
						last = now;
					}
				}
				else if (head->add.x <= 13) {
					if ((int)(now - last) >= 2000) {
						if (flag = play()) {
							now_t = flag ? clock() : end_t;
							draw();
							drawui();
						}
						last = now;
					}
				}
				else {
					if ((int)(now - last) >= 1000) {
						if (flag = play()) {
							now_t = flag ? clock() : end_t;
							draw();
							drawui();
						}
						last = now;
					}
				}
			}

			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game6 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 100;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 6) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");
	}

	void erase_s(snake *p, int n) {
		if (n == 0) {
			p->tow = p->next->tow;
			switch (p->tow) {
				case 'u':
					map[p->add.x][p->add.y] = 'a';
					break;
				case 'r':
					map[p->add.x][p->add.y] = 'd';
					break;
				case 'd':
					map[p->add.x][p->add.y] = 'c';
					break;
				case 'l':
					map[p->add.x][p->add.y] = 'b';
					break;
			}
			return;
		}
		map[p->add.x][p->add.y] = '0';
		erase_s(p->next, n - 1);
	}

	bool play() {
		if (life <= 0) {
			endit();
			return false;
		}
		life--;

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			life += 30;
			life = life > 100 ? 100 : life;
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == '8') {
			endit();
			return false;
		}

		if (life <= 0) {
			endit();
			return false;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 6 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "体能：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);

		setfillcolor(0xC1B6FF);
		solidrectangle(220, 605, 220 + life, 625);
		setfillcolor(0x555555);
		solidrectangle(220 + life, 605, 320, 625);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game7 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int life = 1;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}

		num = rand() % 5 + 1;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			p->style = 'b';
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 7) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 20;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 20;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 20;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");
	}

	void erase_s(snake *p, int n) {
		if (n == 0) {
			p->tow = p->next->tow;
			switch (p->tow) {
				case 'u':
					map[p->add.x][p->add.y] = 'a';
					break;
				case 'r':
					map[p->add.x][p->add.y] = 'd';
					break;
				case 'd':
					map[p->add.x][p->add.y] = 'c';
					break;
				case 'l':
					map[p->add.x][p->add.y] = 'b';
					break;
			}
			return;
		}
		map[p->add.x][p->add.y] = '0';
		erase_s(p->next, n - 1);
	}

	bool play() {
		if (life == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == '8') {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == 'k') {
			endit();
			return false;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 7 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(life, &slif[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class Game8 :public Game {
public:
	char map[80][60] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 78 * 58;
	int length = 3;
	int fruit_num = 0;
	int life = 1;
	int score = 0;
	int highscore;
	clock_t start_t, now_t, end_t;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 58; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		pos vec;

		if (head->add.x < 20) {
			vec.x = 0;
		}
		else if (head->add.x > 60) {
			vec.x = 40;
		}
		else {
			vec.x = head->add.x - 20;
		}

		if (head->add.y < 15) {
			vec.y = 0;
		}
		else if (head->add.y > 45) {
			vec.y = 30;
		}
		else {
			vec.y = head->add.y - 15;
		}

		for (int i = vec.x; i < vec.x + 40; i++) {
			for (int j = vec.y; j < vec.y + 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * (i - vec.x), 20 * (j - vec.y), &img);
			}
		}
	}

	void getrecord() {
		fstream fp;
		fp.open(REC, ios::in);
		int a, c;
		char b[100];
		for (;;) {
			if (fp.eof()) {
				break;
			}
			fp >> a >> b >> c;
			if (a != 8) {
				continue;
			}
			if (c > highscore) {
				highscore = c;
			}
		}
		fp.close();
	}

	void init2() {
		getrecord();

		start_t = clock();

		snake *p, *q;
		for (int i = 0; i < 80; i++) {
			map[i][0] = '8';
			map[i][59] = '8';
		}
		for (int j = 1; j < 59; j++) {
			map[0][j] = '8';
			map[79][j] = '8';
		}
		for (int i = 1; i < 79; i++) {
			for (int j = 1; j < 59; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 40;
		head->add.y = 29;

		p = new snake;
		head->next = p;
		p->add.x = 40;
		p->add.y = 30;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 40;
		q->add.y = 31;

		area -= 3;

		head->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "游戏结束");
	}

	void erase_s(snake *p, int n) {
		if (n == 0) {
			p->tow = p->next->tow;
			switch (p->tow) {
				case 'u':
					map[p->add.x][p->add.y] = 'a';
					break;
				case 'r':
					map[p->add.x][p->add.y] = 'd';
					break;
				case 'd':
					map[p->add.x][p->add.y] = 'c';
					break;
				case 'l':
					map[p->add.x][p->add.y] = 'b';
					break;
			}
			return;
		}
		map[p->add.x][p->add.y] = '0';
		erase_s(p->next, n - 1);
	}

	bool play() {
		if (life == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		if (!head->judge(head, ne)) {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == '8') {
			endit();
			return false;
		}
		if (map[ne.x][ne.y] == 'k') {
			endit();
			return false;
		}
	}

	void record() {
		char sname[100];
		int cp = 0;
		char temp = '1';

		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(20, 10, _T("楷体"));
		outtextxy(240, 340, "请输入您的英文名：");

		INPUT_RECORD keyRec;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD state = 0, res;

		while (temp != '\n') {
			while (!_kbhit()) {

			}

			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				break;
			}

			temp = _getch();

			if (temp == '\n') {
				break;
			}
			sname[cp] = temp;
			sname[cp + 1] = '\0';
			cp++;
			outtextxy(260, 370, sname);
		}

		fstream fp;
		fp.open(REC, ios::app);
		if (!fp.is_open()) {
			cerr << "出错！";
			exit(-1);
		}

		fp << 8 << ' ' << sname << ' ' << score << '\n';

		fp.close();
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char slen[30] = "蛇的长度：";
		char slif[30] = "剩余生命：";
		char ssco[30] = "当前分数：";
		char smax[30] = "历史最高：";
		char stim[30] = "游戏时间：";

		highscore = highscore > score ? highscore : score;

		int2char(length, &slen[10]);
		int2char(life, &slif[10]);
		int2char(score, &ssco[10]);
		int2char(highscore, &smax[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, slen);
		outtextxy(165, 605, slif);
		outtextxy(325, 605, ssco);
		outtextxy(485, 605, smax);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		record();


		back();
	}
};

class ai {
public:
	char lac;
	char map[40][30];

	void copy_map(char a[40][30]) {
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				map[i][j] = a[i][j];
			}
		}
	}

	/*void find_goal() {
		dot temp = dots.front();
		dots.pop();

		if (map[temp.add.x][temp.add.y] == '7') {
			goal = temp;
			return;
		}
		map[temp.add.x][temp.add.y] = '\0';

		pos p;
		dot *uhi;

		p.x = temp.add.x + 1;
		p.y = temp.add.y;
		if (p.x < 39) {
			if (map[p.x][p.y] == '0' || (map[p.x][p.y] <= '{'&&map[p.x][p.y] >= 'x') || map[p.x][p.y] == '7') {
				uhi = new dot;
				uhi->add = p;
				uhi->a[uhi->num++] = 'r';
				if (map[p.x][p.y] == '7') {
					goal = *uhi;
					return;
				}
				dots.push(*uhi);
			}
		}

		p.x = temp.add.x - 1;
		p.y = temp.add.y;
		if (p.x > 0) {
			if (map[p.x][p.y] == '0' || (map[p.x][p.y] <= '{'&&map[p.x][p.y] >= 'x') || map[p.x][p.y] == '7') {
				uhi = new dot;
				uhi->add = p;
				uhi->a[uhi->num++] = 'l';
				if (map[p.x][p.y] == '7') {
					goal = *uhi;
					return;
				}
				dots.push(*uhi);
			}
		}

		p.x = temp.add.x;
		p.y = temp.add.y + 1;
		if (p.y < 29) {
			if (map[p.x][p.y] == '0' || (map[p.x][p.y] <= '{'&&map[p.x][p.y] >= 'x') || map[p.x][p.y] == '7') {
				uhi = new dot;
				uhi->add = p;
				uhi->a[uhi->num++] = 'd';
				if (map[p.x][p.y] == '7') {
					goal = *uhi;
					return;
				}
				dots.push(*uhi);
			}
		}

		p.x = temp.add.x;
		p.y = temp.add.y - 1;
		if (p.y > 0) {
			if (map[p.x][p.y] == '0' || (map[p.x][p.y] <= '{'&&map[p.x][p.y] >= 'x') || map[p.x][p.y] == '7') {
				uhi = new dot;
				uhi->add = p;
				uhi->a[uhi->num++] = 'u';
				if (map[p.x][p.y] == '7') {
					goal = *uhi;
					return;
				}
				dots.push(*uhi);
			}
		}

		find_goal();
	}*/

	char find_goal(char a, snake2 *hea) {
		pos p;
		p = hea->add;

		int i;
		int tempa, tempb;

		switch (a) {
			case'u':
				for (i = p.y - 1; map[p.x][i] == '0'; i--);
				if (map[p.x][i] == '7') {
					lac = 'u';
					break;
				}
				for (i = p.x - 1; map[i][p.y] == '0'; i--);
				if (map[i][p.y] == '7') {
					lac = 'l';
					break;
				}
				for (i = p.x + 1; map[i][p.y] == '0'; i++);
				if (map[i][p.y] == '7') {
					lac = 'r';
					break;
				}
				tempa = rand() % 30;
				tempb = rand() % 40;
				if (p.y > tempa) {
					lac = 'u';
					break;
				}
				if (p.x > tempb) {
					lac = 'l';
					break;
				}
				lac = 'r';
				break;
			case 'd':
				for (i = p.y + 1; map[p.x][i] == '0'; i++);
				if (map[p.x][i] == '7') {
					lac = 'd';
					break;
				}
				for (i = p.x - 1; map[i][p.y] == '0'; i--);
				if (map[i][p.y] == '7') {
					lac = 'l';
					break;
				}
				for (i = p.x + 1; map[i][p.y] == '0'; i++);
				if (map[i][p.y] == '7') {
					lac = 'r';
					break;
				}
				tempa = rand() % 30;
				tempb = rand() % 40;
				if (p.y <= tempa) {
					lac = 'd';
					break;
				}
				if (p.x > tempb) {
					lac = 'l';
					break;
				}
				lac = 'r';
				break;
			case 'l':
				for (i = p.x - 1; map[i][p.y] == '0'; i--);
				if (map[i][p.y] == '7') {
					lac = 'l';
					break;
				}
				for (i = p.y + 1; map[p.x][i] == '0'; i++);
				if (map[p.x][i] == '7') {
					lac = 'd';
					break;
				}
				for (i = p.y - 1; map[p.x][i] == '0'; i--);
				if (map[p.x][i] == '7') {
					lac = 'u';
					break;
				}
				tempa = rand() % 30;
				tempb = rand() % 40;
				if (p.x > tempb) {
					lac = 'l';
					break;
				}
				if (p.y <= tempa) {
					lac = 'd';
					break;
				}
				lac = 'u';
				break;
			case 'r':
				for (i = p.x + 1; map[i][p.y] == '0'; i++);
				if (map[i][p.y] == '7') {
					lac = 'r';
					break;
				}
				for (i = p.y + 1; map[p.x][i] == '0'; i++);
				if (map[p.x][i] == '7') {
					lac = 'd';
					break;
				}
				for (i = p.y - 1; map[p.x][i] == '0'; i--);
				if (map[p.x][i] == '7') {
					lac = 'u';
					break;
				}
				tempa = rand() % 30;
				tempb = rand() % 40;
				if (p.x <= tempb) {
					lac = 'r';
					break;
				}
				if (p.y <= tempa) {
					lac = 'd';
					break;
				}
				lac = 'u';
				break;
		}

		return lac;
	}

	char make_choice(char lc, snake2 *head) {
		char ans = find_goal(lc, head);
		return ans;
	}
};

class Game9 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int score = 0;
	int life = 1;
	clock_t start_t, now_t, end_t;

	char ames = 'u';
	snake2 *ahead;
	int alength = 3;
	int ascore = 0;
	int alife = 1;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void init2() {
		start_t = clock();

		snake *p, *q;
		snake2 *p2, *q2;

		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 10;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 10;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 10;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		ahead = new snake2;
		ahead->head = true;
		ahead->add.x = 30;
		ahead->add.y = 14;

		p2 = new snake2;
		ahead->next = p2;
		p2->add.x = 30;
		p2->add.y = 15;

		q2 = new snake2;
		p2->next = q2;
		q2->next = NULL;
		q2->add.x = 30;
		q2->add.y = 16;

		area -= 3;

		ahead->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "您失败了");
	}

	void winit() {
		alife = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "您胜利了");
	}

	bool play() {
		if (life == 0) {
			return false;
		}
		if (alife == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h') || (map[ne.x][ne.y] >= 'x'&&map[ne.x][ne.y] <= '{')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		else {
			endit();
			return false;
		}

		return false;
	}

	bool aplay() {
		if (life == 0) {
			return false;
		}
		if (alife == 0) {
			return false;
		}

		pos ne = ahead->next_pos(ames);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'x'&&map[ne.x][ne.y] <= '{') || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = ahead->tail_pos();
			map[tail.x][tail.y] = '0';
			ahead = ahead->move(ames);
			ahead->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			ahead = ahead->eat(ames);
			ahead->draw(map);
			fruit_num--;
			alength++;
			ascore += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		else {
			winit();
			return false;
		}

		return false;
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char ylen[30] = "你的长度：";
		char ysco[30] = "你的分数：";
		char alen[30] = "AI的长度：";
		char asco[30] = "AI的分数：";
		char stim[30] = "游戏时间：";

		int2char(length, &ylen[10]);
		int2char(score, &ysco[10]);
		int2char(alength, &alen[10]);
		int2char(ascore, &asco[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, ylen);
		outtextxy(165, 605, ysco);
		outtextxy(325, 605, alen);
		outtextxy(485, 605, asco);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;
		bool afalg = true;

		ai per;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (afalg = aplay()) {
						per.copy_map(map);
						ames = per.make_choice(ames, ahead);
						//draw();
					}
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
			}
		}

		back();
	}
};

class Game10 :public Game {
public:
	char map[40][30] = { '0' };
	char mes = 'u';
	snake *head;
	int area = 38 * 28;
	int length = 3;
	int fruit_num = 0;
	int score = 0;
	int life = 1;
	clock_t start_t, now_t, end_t;

	char ames = 'u';
	snake2 *ahead;
	int alength = 3;
	int ascore = 0;
	int alife = 1;

	void refresh() {
		int num = rand() % 5 + 1;
		int pl;
		fruit *p;
		for (int uhi = 0; uhi < num; uhi++) {
			p = new fruit;
			pl = rand() % area;
			for (p->add.x = 1;; p->add.x++) {
				for (p->add.y = 1; p->add.y <= 28; p->add.y++) {
					if (map[p->add.x][p->add.y] != '0') {
						continue;
					}
					pl--;
					if (pl == 0) {
						break;
					}
				}
				if (pl == 0) {
					break;
				}
				area--;
			}
			p->draw(map);
			fruit_num++;
		}
	}

	void draw() {
		char s[7] = "_?.jpg";
		IMAGE img;

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				s[1] = map[i][j];
				loadimage(&img, s);
				putimage(20 * i, 20 * j, &img);
			}
		}
	}

	void init2() {
		start_t = clock();

		snake *p, *q;
		snake2 *p2, *q2;

		for (int i = 0; i < 40; i++) {
			map[i][0] = '8';
			map[i][29] = '8';
		}
		for (int j = 1; j < 29; j++) {
			map[0][j] = '8';
			map[39][j] = '8';
		}
		for (int i = 1; i < 39; i++) {
			for (int j = 1; j < 29; j++) {
				map[i][j] = '0';
			}
		}

		refresh();

		head = new snake;
		head->head = true;
		head->add.x = 10;
		head->add.y = 14;

		p = new snake;
		head->next = p;
		p->add.x = 10;
		p->add.y = 15;

		q = new snake;
		p->next = q;
		q->next = NULL;
		q->add.x = 10;
		q->add.y = 16;

		area -= 3;

		head->draw(map);

		ahead = new snake2;
		ahead->head = true;
		ahead->add.x = 30;
		ahead->add.y = 14;

		p2 = new snake2;
		ahead->next = p2;
		p2->add.x = 30;
		p2->add.y = 15;

		q2 = new snake2;
		p2->next = q2;
		q2->next = NULL;
		q2->add.x = 30;
		q2->add.y = 16;

		area -= 3;

		ahead->draw(map);

		draw();
	}

	void endit() {
		life = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "紫色获胜");
	}

	void winit() {
		alife = 0;
		settextcolor(0xffffff);
		settextcolor(0xffffff);
		setbkcolor(0x555555);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(280, 270, "绿色获胜");
	}

	bool play() {
		if (life == 0) {
			return false;
		}
		if (alife == 0) {
			return false;
		}

		pos ne = head->next_pos(mes);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h') || (map[ne.x][ne.y] >= 'x'&&map[ne.x][ne.y] <= '{')) {
			pos tail = head->tail_pos();
			map[tail.x][tail.y] = '0';
			head = head->move(mes);
			head->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			head = head->eat(mes);
			head->draw(map);
			fruit_num--;
			length++;
			score += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		else {
			endit();
			return false;
		}

		return false;
	}

	bool aplay() {
		if (life == 0) {
			return false;
		}
		if (alife == 0) {
			return false;
		}

		pos ne = ahead->next_pos(ames);
		if (map[ne.x][ne.y] == '0' || (map[ne.x][ne.y] >= 'x'&&map[ne.x][ne.y] <= '{') || (map[ne.x][ne.y] >= 'e'&&map[ne.x][ne.y] <= 'h')) {
			pos tail = ahead->tail_pos();
			map[tail.x][tail.y] = '0';
			ahead = ahead->move(ames);
			ahead->draw(map);
			return true;
		}
		else if (map[ne.x][ne.y] == '7') {
			ahead = ahead->eat(ames);
			ahead->draw(map);
			fruit_num--;
			alength++;
			ascore += 2;
			if (fruit_num == 0) {
				refresh();
			}
			return true;
		}
		else {
			winit();
			return false;
		}

		return false;
	}

	void drawui() {
		settextstyle(20, 10, _T("楷体"));
		setbkcolor(0x000000);

		char ylen[30] = "绿方长度：";
		char ysco[30] = "绿方分数：";
		char alen[30] = "紫方长度：";
		char asco[30] = "紫方分数：";
		char stim[30] = "游戏时间：";

		int2char(length, &ylen[10]);
		int2char(score, &ysco[10]);
		int2char(alength, &alen[10]);
		int2char(ascore, &asco[10]);
		int2char((int)((double)(now_t - start_t) / CLOCKS_PER_SEC), &stim[10]);

		outtextxy(5, 605, ylen);
		outtextxy(165, 605, ysco);
		outtextxy(325, 605, alen);
		outtextxy(485, 605, asco);
		outtextxy(645, 605, stim);
	}

	void listen() {
		struct tm t;
		time_t now, last;
		time(&now);
		localtime_s(&t, &now);
		bool flag = true;
		bool afalg = true;

		char temp = 'u';
		while (temp != 'q') {
			while (!_kbhit()) {
				last = now;
				time(&now);
				if (last != now) {
					if (afalg = aplay()) {
						draw();
					}
					if (flag = play()) {
						now_t = flag ? clock() : end_t;
						draw();
						drawui();
					}
				}
			}
			temp = _getch();
			temp = flag ? temp : 'q';
			if (!flag) {
				end_t = clock();
			}
			switch (temp) {
				case 'w':
					if (mes != 'd') {
						mes = 'u';
					}
					break;
				case 'a':
					if (mes != 'r') {
						mes = 'l';
					}
					break;
				case 's':
					if (mes != 'u') {
						mes = 'd';
					}
					break;
				case 'd':
					if (mes != 'l') {
						mes = 'r';
					}
					break;
				case 'i':
					if (ames != 'd') {
						ames = 'u';
					}
					break;
				case 'j':
					if (ames != 'r') {
						ames = 'l';
					}
					break;
				case 'k':
					if (ames != 'u') {
						ames = 'd';
					}
					break;
				case 'l':
					if (ames != 'l') {
						ames = 'r';
					}
					break;
			}
		}

		back();
	}
};

class Btn {
public:
	char name[100];
	pos left_up, right_down;
	int color = 0xffffff;
	int border_color = 0x000000;
	int font_color = 0x000000;

	bool ifin(pos a) {
		if (a.x < left_up.x || a.x > right_down.x) {
			return false;
		}
		if (a.y < left_up.y || a.y > right_down.y) {
			return false;
		}
		return true;
	}

	void onclick(pos a, Game1 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game2 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game3 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game4 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game5 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game6 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game7 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game8 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game9 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void onclick(pos a, Game10 obj) {
		if (ifin(a)) {
			obj.init_game();
			obj.init2();
			obj.listen();
		}
	}

	void back();

	void onclick(pos a) {
		if (ifin(a)) {
			closegraph();

			fstream fp;
			fp.open(REC);
			if (!fp.is_open()) {
				cerr << "错误！";
				exit(-1);
			}

			int a, c;
			char b[100];

			system("cls");

			for (;;) {
				fp >> a >> b >> c;
				if (fp.eof()) {
					break;
				}

				switch (a) {
					case 1:
						cout << "版本：入门版";
						break;
					case 2:
						cout << "版本：进阶版";
						break;
					case 3:
						cout << "版本：高级版";
						break;
					case 4:
						cout << "版本：idea1";
						break;
					case 5:
						cout << "版本：idea2";
						break;
					case 6:
						cout << "版本：idea3";
						break;
					case 7:
						cout << "版本：idea4";
						break;
					case 8:
						cout << "版本：idea6";
						break;
					default:
						a = -1;
				}

				if (a == -1) {
					continue;
				}

				cout << "  用户名：" << b << "  得分：" << c << endl;
			}

			cout << "\n按下任意键返回主菜单......";

			while (!_kbhit());
			_getch();

			back();
		}
	}

	void draw() {
		setfillstyle(BS_SOLID);
		setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
		setlinecolor(border_color);
		setfillcolor(color);
		fillrectangle(left_up.x, left_up.y, right_down.x, right_down.y);

		settextcolor(font_color);
		setbkcolor(color);
		settextstyle((int)(0.7*(right_down.y - left_up.y)), (int)(0.35*(right_down.y - left_up.y)), _T("楷体"));
		double temp1, temp2;
		temp1 = 0.5*(left_up.x + right_down.x) - 0.5*strlen(name)*0.35*(right_down.y - left_up.y);
		temp2 = left_up.y + 0.15*(right_down.y - left_up.y);
		outtextxy((int)temp1, (int)temp2, name);
	}

	void set_Btn(const char name[100], int left, int up, int right, int down) {
		strcpy(this->name, name);
		left_up.x = left;
		left_up.y = up;
		right_down.x = right;
		right_down.y = down;
	}

};

class Menu {
public:
	Btn *btns;
	int btn_num = 12;

	void init_menu() {
		initgraph(900, 600);
		settextcolor(0xffffff);
		settextstyle(60, 30, _T("楷体"));
		outtextxy(270, 30, "贪吃蛇大作业");
		settextstyle(30, 15, _T("楷体"));
		outtextxy(345, 120, "1950000 一二三");
		btns = new Btn[12];
		btns[0].set_Btn("入门", 60, 180, 240, 240);
		btns[1].set_Btn("进阶", 60, 270, 240, 330);
		btns[2].set_Btn("高级", 60, 360, 240, 420);
		btns[3].set_Btn("得分榜", 60, 450, 240, 510);

		btns[4].set_Btn("idea1", 360, 180, 540, 240);
		btns[5].set_Btn("idea2", 360, 270, 540, 330);
		btns[6].set_Btn("idea3", 360, 360, 540, 420);
		btns[7].set_Btn("idea4", 360, 450, 540, 510);

		btns[8].set_Btn("idea6", 660, 180, 840, 240);
		btns[9].set_Btn("人机", 660, 270, 840, 330);
		btns[10].set_Btn("双人", 660, 360, 840, 420);
		btns[11].set_Btn("尚未开发", 660, 450, 840, 510);

		for (int i = 0; i < btn_num; i++) {
			btns[i].draw();
		}
	}

	void listen() {
		MOUSEMSG m{ 0 };
		BOOL flag = TRUE;
		pos temp;
		Game1 g1;
		Game2 g2;
		Game3 g3;
		Game4 g4;
		Game5 g5;
		Game6 g6;
		Game7 g7;
		Game8 g8;
		Game9 g9;
		Game10 g10;

		while (flag)
		{
			if (MouseHit())m = GetMouseMsg();   // 获取鼠标信息
			TCHAR s[20];         // EasyX设置文字需要的字符串变量类型
			switch (m.uMsg)
			{
				case WM_LBUTTONDOWN:
					temp.x = m.x;
					temp.y = m.y;
					btns[0].onclick(temp, g1);
					btns[1].onclick(temp, g2);
					btns[2].onclick(temp, g3);
					btns[3].onclick(temp);
					btns[4].onclick(temp, g4);
					btns[5].onclick(temp, g5);
					btns[6].onclick(temp, g6);
					btns[7].onclick(temp, g7);
					btns[8].onclick(temp, g8);
					btns[9].onclick(temp, g9);
					btns[10].onclick(temp, g10);
					break;
			}
		}
	}
};

void Game::back() {
	Menu haha;
	haha.init_menu();
	haha.listen();
}

void Btn::back() {
	Menu haha;
	haha.init_menu();
	haha.listen();
}

int main() {
	srand(time(0));

	Menu haha;
	haha.init_menu();
	haha.listen();
}

//int main() {
//	
//	initgraph(800, 600);  // 初始化窗口
//	MOUSEMSG m{ 0 };           // 鼠标信息结构体
//	BOOL flag = TRUE;
//	while (flag)
//	{
//		if (MouseHit())m = GetMouseMsg();   // 获取鼠标信息
//		TCHAR s[20];         // EasyX设置文字需要的字符串变量类型
//		switch (m.uMsg)
//		{
//			case WM_LBUTTONDOWN:
//				// 左键按下，在当下位置画一个圆
//				setfillcolor(RED);
//				solidcircle(m.x, m.y, 20);
//				initgraph(600, 800);
//				break;
//			case WM_RBUTTONDOWN:
//				// 右键按下，在当下位置画一个椭圆
//				setfillcolor(RGB(255, 0, 255));
//				solidellipse(m.x - 40, m.y - 20, m.x + 40, m.y + 20);
//				break;
//			case WM_MOUSEMOVE:
//				// 鼠标移动，在窗口左上角显示当前坐标
//				setfillcolor(BLACK);                  // 黑色矩形覆盖上次坐标记录
//				solidrectangle(0, 0, 75, 20);
//				_stprintf_s(s, _T("[%d,%d]"), m.x, m.y); // 格式化字符串
//				outtextxy(0, 0, s);
//				break;
//			case WM_LBUTTONDBLCLK:
//				// 左键双击退出循环
//				flag = FALSE;
//				break;
//		}
//	}
//
//	closegraph();
//
//	return 0;
//}
