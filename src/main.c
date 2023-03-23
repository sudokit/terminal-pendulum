#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "linmath.h"

void draw_line(vec2 start, vec2 end, const char* sym) {
	float dx = fabsf(end[0] - start[0]);
	float dy = fabsf(end[1] - start[1]);
	float x = floorf(start[0]);
	float y = floorf(start[1]);
	float sx = start[0] < end[0] ? 1.f : -1.f;
	float sy = start[1] < end[1] ? 1.f : -1.f;
	float err = dx - dy;

	while (x != floorf(end[0]) && y != floorf(end[1])) {
		mvprintw(y, x, "%s", sym);
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x += sx;
		}
		if (e2 < dx) {
			err += dx;
			y += sy;
		}
	}
}

void draw_circle(vec2 pos, float r, const char* sym) {
	float x = r;
	float y = 0.f;
	float err = 0.f;

	while (x >= y) {
		mvprintw(pos[1] + y, pos[0] + x, "%s", sym);
		mvprintw(pos[1] + x, pos[0] + y, "%s", sym);
		mvprintw(pos[1] + x, pos[0] - y, "%s", sym);
		mvprintw(pos[1] + y, pos[0] - x, "%s", sym);
		mvprintw(pos[1] - y, pos[0] - x, "%s", sym);
		mvprintw(pos[1] - x, pos[0] - y, "%s", sym);
		mvprintw(pos[1] - x, pos[0] + y, "%s", sym);
		mvprintw(pos[1] - y, pos[0] + x, "%s", sym);

		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0) {
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}

int main(int argc, char* argv[]) {
	vec2 max;
	int fps = 40;
	int frameDelay = 1000 / fps;
	int nextFrame = 0;

	initscr();
	noecho();
	nodelay(stdscr, true);
	cbreak();
	curs_set(false);

	getmaxyx(stdscr, max[1], max[0]);

	float r = 4.f;//* aspectRatio;
	float length = max[1] * 0.5 + 15;

	vec2 origin = {max[0] * 0.5, 0};
	float angle = M_2_SQRTPI;
	float aVel = 0.0;
	float aAcc = 0.0;
	float gravity = 0.4;

	while (getch() == ERR) {
		clear();
		aAcc = (-1 * gravity / length) * sin(angle);
		aVel += aAcc;
		angle += aVel;

		vec2 pos = {length * sin(angle), length * cos(angle)};
		vec2_add(pos, pos, origin);
		draw_circle(pos, r, "O");
		draw_line(origin, pos, "I");
		refresh();

		int currentTime = time(NULL);
		if (nextFrame > currentTime) { napms(nextFrame - currentTime); }
		nextFrame = time(NULL) + frameDelay;
	}
	endwin();
}