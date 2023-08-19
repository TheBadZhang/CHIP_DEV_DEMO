#ifndef __TBZ_SQUARE_WATCH_H__
#define __TBZ_SQUARE_WATCH_H__


#include "common.h"
#include <cmath>
#include <cstdio>
namespace tbz{
class SquareWatch {
	private:


	U8G2* u8g2;


double radians(double degrees) {
	return degrees * 3.14159265357 / 180;
}

const unsigned char upir_logo [8] = {   // upir logo
	0xEA, 0x3A, 0xAA, 0x28, 0x6A, 0x1A, 0x26, 0x2A
};

int center_x = 64; // display x center, 64px for the 128x128px display
int center_y = 64; // display y center, 64px for the 128x128px display


// draw the background - fullscreen circle, dots for seconds, big tickmarks, numbers
void draw_background() {

	float xpos;
	float ypos;
	float xpos2;
	float ypos2;

	u8g2 -> setDrawColor(1); // set the drawing color to white
	u8g2 -> drawCircle(center_x, center_y, 63, U8G2_DRAW_ALL); // draw fullscreen circle

	// draw 60 dots (pixels) around the circle, one for every minute/second
	for (int i=0; i<60; i++) { // draw 60 pixels around the circle
		xpos = round(center_x + sin(radians(i * 6)) * 60); // calculate x pos based on angle and radius
		ypos = round(center_y - cos(radians(i * 6)) * 60); // calculate y pos based on angle and radius

		u8g2 -> drawPixel(xpos,ypos); // draw white pixel on position xpos and ypos
	}

	// drawing big tickmarks
	for (int i=0; i<12; i++) {
		if((i % 3) != 0) { // only draw tickmarks for some numbers, leave empty space for 12, 3, 6, and 9
			xpos = round(center_x + sin(radians(i * 30)) * 54); // calculate x pos based on angle and radius
			ypos = round(center_y - cos(radians(i * 30)) * 54); // calculate y pos based on angle and radius
			xpos2 = round(center_x + sin(radians(i * 30)) * 46); // calculate x pos based on angle and radius
			ypos2 = round(center_y - cos(radians(i * 30)) * 46); // calculate y pos based on angle and radius

			u8g2 -> drawLine(xpos, ypos, xpos2, ypos2); // draw a line for a tickmark
		}
	}

	// draw labels 12, 3, 6 and 9, positions are hardcoded
	u8g2 -> setFont(u8g2_font_8x13B_mn); // set the u8g2 font
	u8g2 -> drawStr(57,20,"12");
	u8g2 -> drawStr(112,69,"3");
	u8g2 -> drawStr(61,120,"6");
	u8g2 -> drawStr(9,69,"9");
}

// draw thin hand = second hand
void draw_hand_thin (int hand_angle, int hand_lenght_long, int hand_legth_short) {

	float xpos;
	float ypos;
	float xpos2;
	float ypos2;

	// calculate starting and ending position of the second hand
	xpos = round(center_x + sin(radians(hand_angle)) * hand_lenght_long); // calculate x pos based on angle and radius
	ypos = round(center_y - cos(radians(hand_angle)) * hand_lenght_long); // calculate y pos based on angle and radius
	xpos2 = round(center_x + sin(radians(hand_angle + 180)) * hand_legth_short); // calculate x pos based on angle and radius
	ypos2 = round(center_y - cos(radians(hand_angle + 180)) * hand_legth_short); // calculate y pos based on angle and radius

	u8g2 -> drawLine(xpos, ypos, xpos2, ypos2); // draw the main line
	u8g2 -> setDrawColor(0); // black color
	u8g2 -> drawDisc(xpos2, ypos2, 3); // draw small filled black circle
	u8g2 -> setDrawColor(1); // white color
	u8g2 -> drawCircle(xpos2, ypos2, 3, U8G2_DRAW_ALL); // draw small outline white circle
}


// draw bold hand = minute hand and hour hand
void draw_hand_bold (int hand_angle, int hand_lenght_long, int hand_legth_short, int hand_dot_size) {

	float xpos;
	float ypos;
	float xpos2;
	float ypos2;

	float tri_xoff;
	float tri_yoff;

	// calculate positions of the two circles
	xpos = round(center_x + sin(radians(hand_angle)) * hand_lenght_long); // calculate x pos based on angle and radius
	ypos = round(center_y - cos(radians(hand_angle)) * hand_lenght_long); // calculate y pos based on angle and radius
	xpos2 = round(center_x + sin(radians(hand_angle)) * hand_legth_short); // calculate x pos based on angle and radius
	ypos2 = round(center_y - cos(radians(hand_angle)) * hand_legth_short); // calculate y pos based on angle and radius

	tri_xoff = round( sin(radians(hand_angle + 90)) * hand_dot_size);
	tri_yoff = round(-cos(radians(hand_angle + 90)) * hand_dot_size);

	u8g2 -> drawLine(center_x, center_y, xpos2, ypos2); // draw the line from one circle to the center
	u8g2 -> drawDisc(xpos, ypos, hand_dot_size); // draw filled white circle
	u8g2 -> drawDisc(xpos2, ypos2, hand_dot_size); // draw filled white circle

	// two filled triangles are used to draw a rotated rectangle between two circles
	u8g2 -> drawTriangle(xpos + tri_xoff, ypos + tri_yoff,
						xpos - tri_xoff, ypos - tri_yoff,
						xpos2 + tri_xoff, ypos2 + tri_yoff);

	u8g2 -> drawTriangle(xpos2 + tri_xoff, ypos2 + tri_yoff,
						xpos2 - tri_xoff, ypos2 - tri_yoff,
						xpos - tri_xoff, ypos - tri_yoff);


}



	public:

	SquareWatch(U8G2* d): u8g2(d) {}

	void draw(int time_hours, int time_minutes, int time_seconds) {

		// draw the background - fullscreen circle, dots for seconds, big tickmarks, numbers
		draw_background();
		// draw the needles with angles based on the time value
		draw_hand_bold(time_minutes*6, 48, 15, 2); // minute hand
		draw_hand_bold(time_hours*30 + (time_minutes / 2), 32, 15, 2); // hour hand
		draw_hand_thin(time_seconds*6, 56, 24); // second hand
		u8g2 -> drawXBMP(57, 24, 16, 4, upir_logo); // draw upir logo
		// draw the center circle to cover the center part of the hands
		u8g2 -> setColorIndex(0); // black color
		u8g2 -> drawDisc(center_x, center_y, 4);
		u8g2 -> setColorIndex(1); // white color
		u8g2 -> drawCircle(center_x, center_y, 4);

	}

};
}
#endif