#include <bangtal.h>
#include <string>
#include <string.h>

using namespace std;

SceneID scene,title;
ObjectID bord, dot_bord[361],stone_black[181], stone_white[180],turn_white, turn_black, start;
TimerID timer_bl, timer_wh;

int dot_bord_x[361], dot_bord_y[361];
int num_bl = 0, num_wh = 1, turn = 0; // 0 =black, 1= white




ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	
	if (shown) {
		showObject(object);
	}
	return object;
}

int cordinate_click(ObjectID object) {
	for (int i = 0; i < 361; i++) {
		if (dot_bord[i] == object) {
			return i;
			}
	}
	return - 1;
}
void turn_check() {
	if (turn == 0) {
		showObject(turn_black);
		hideObject(turn_white);
	}
	else if(turn == 1){
		showObject(turn_white);
		hideObject(turn_black);
	}
}

void create_stone(bool color, int select) {
	if (color == true) { //black
		stone_black[num_bl] = createObject("Images/stone_black.png", scene, dot_bord_x[select] + 4 - 10, dot_bord_y[select] + 4 - 10, true);
	}
	else {
		stone_white[num_wh] = createObject("Images/stone_white.png", scene, dot_bord_x[select] + 4 - 10, dot_bord_y[select] + 4 - 10, true);
	}
}


void timerEvent(bool color) {
	if (color == true) { // black
		stopTimer(timer_bl);
		setTimer(timer_bl, 20.0f);
		hideTimer();
		showTimer(timer_wh);
		startTimer(timer_wh);
	}
	else {
		stopTimer(timer_wh);
		setTimer(timer_wh, 20.0f);
		hideTimer();
		startTimer(timer_bl);
		showTimer(timer_bl);
	}
}
void Mouse_Callback(ObjectID object, int x, int y, MouseAction action) {

	int select = cordinate_click(object);

	if (select < 0) {
		if (object == start) {
			enterScene(scene);
			startTimer(timer_bl);
			showTimer(timer_bl);
		}
	}
	else {
		if (turn == 0) {
			turn_check();
			create_stone(true, select);
			timerEvent(true);
			num_bl += 1;
			turn = 1;
		}
		else if (turn == 1) {
			turn_check();
			create_stone(false, select);
			timerEvent(false);
			num_wh += 1;
			turn = 0;
		}
	}

	
}
void Timer_callback(TimerID timer) {
	if (timer == timer_bl) {
		showMessage("White Win!!");

	}
	else if (timer == timer_wh) {
		showMessage("Black Win!!");
	}
}

int main()
{

	setMouseCallback(Mouse_Callback);
	setTimerCallback(Timer_callback);

	title = createScene("title", "Images/title.png");
	scene = createScene("background", "Images/background.png");

	start = createObject("Images/start.png", title, 590, 60, true);
	bord = createObject("Images/bord.png", scene, 340, 60, true);
	
	turn_black = createObject("Images/turn_black.png",scene, 106, 60, true);
	turn_white = createObject("Images/turn_white.png",scene, 1056, 60, false);

	timer_bl = createTimer(20.0f);
	timer_wh = createTimer(20.0f);

	for (int i = 0; i < 361; i++) {
		dot_bord_x[i] = 340 - 4 +( 30 * (i % 19 + 1));
		dot_bord_y[i] = 60 - 4 + (30 * (19 - i / 19));
		dot_bord[i] = createObject("Images/dot_bord.png", scene, dot_bord_x[i], dot_bord_y[i], true);
	}
	startGame(title);

}
