#ifndef __TBZ_ROUND_WATCH_FACE_H_
#define __TBZ_ROUND_WATCH_FACE_H_

#include "common.h"
#include <cmath>
#include <cstdio>

namespace tbz {

class round_watch_face {
	private:

	U8G2* u8g2;

	int potentiometer_value = 0; // value from the potentiometer
	char buffer[20];       // helper buffer for converting values into C-style string (array of chars)
	int string_width;      // helper value for string widths

	float pixel_x = 0;     // x pos for pixel
	float pixel_y = 0;     // y pos for pixel
	float line_x = 0;      // x pos for line end
	float line_y = 0;      // y pos for line end
	float text_x = 0;      // x pos for text
	float text_y = 0;      // y pos for text

	int center_x = 64;     // x center of the knob
	int center_y = 108;    // y center of the knob (outside of the screen)
	int radius_pixel = 92; // radius for pixel tickmarks
	int radius_line = 87;  // radius for line end
	int radius_text = 75;  // radius for text

	int angle;             // angle for the individual tickmarks
	int tick_value;        // numeric value for the individual tickmarks

	uint8_t precalculated_x_radius_pixel[180]; // lookup table to prevent expensive sin/cos calculations
	uint8_t precalculated_y_radius_pixel[180]; // lookup table to prevent expensive sin/cos calculations

	unsigned long millis_time;       // fps
	unsigned long millis_time_last;  // fps
	int fps;                         // actual FPS value


	const uint8_t upir_logo[8] = {
		0b00010101, 0b11010111,     //  ░░░█░█░███░█░███
		0b00010101, 0b01000101,     //  ░░░█░█░█░█░░░█░█
		0b00010101, 0b10010110,     //  ░░░█░█░██░░█░██░
		0b00011001, 0b00010101      //  ░░░██░░█░░░█░█░█
	};


	double radians(double degrees) {
		return degrees * 3.14159265357 / 180;
	}
	void itoa(int num, char* buf, uint8_t num_width) {
		sprintf(buf, "%d", num);
	}
	void dtostrf(double num, uint8_t min, uint8_t width, char* buf) {
		sprintf(buf, "%*.*f", width, min, num);
	}

	void calculate_tickmarks_and_draw(void) {

		u8g2 -> setDrawColor(1);          // set color to white
		u8g2 -> setFont(u8g_font_6x10r);   // set smaller font for tickmarks


		for (int i=-48; i<=48; i=i+3) {                                // only try to calculate tickmarks that would end up be displayed
			angle = i + ((potentiometer_value*3)/10) % 3;                // final angle for the tickmark
			tick_value = round((potentiometer_value/10.0) + angle/3.0);  // get number value for each tickmark

			//pixel_x =  sin(radians(angle)) * radius_pixel + center_x;    // calculate the tickmark pixel x value
			//pixel_y = -cos(radians(angle)) * radius_pixel + center_y;    // calculate the tickmark pixel y value
			pixel_x = precalculated_x_radius_pixel[angle+90];              // get x value from lookup table
			pixel_y = precalculated_y_radius_pixel[angle+90];              // get y value from lookup table

			if (pixel_x > 0 && pixel_x < 128 && pixel_y > 0 && pixel_y < 64) {  // only draw inside of the screen

				if(tick_value >= 0 && tick_value <= 100) {  // only draw tickmarks between values 0-100%, could be removed when using rotary controller

				if (tick_value % 10 == 0) {                                // draw big tickmark == lines + text
					line_x =  sin(radians(angle)) * radius_line + center_x;  // calculate x pos for the line end
					line_y = -cos(radians(angle)) * radius_line + center_y;  // calculate y pos for the line end
					u8g2 -> drawLine(pixel_x, pixel_y, line_x, line_y);          // draw the line

					text_x =  sin(radians(angle)) * radius_text + center_x;  // calculate x pos for the text
					text_y = -cos(radians(angle)) * radius_text + center_y;  // calculate y pos for the text
					itoa(tick_value, buffer, 10);                            // convert integer to string
					string_width = u8g2 -> getStrWidth(buffer);                  // get string width
					u8g2 -> drawStr(text_x - string_width/2, text_y, buffer);    // draw text - tickmark value

				}
				else {                                                     // draw small tickmark == pixel tickmark
					u8g2 -> drawPixel(pixel_x, pixel_y);                         // draw a single pixel

				}

				}
			}
		}
	}

	void draw_the_big_value_on_top(void) {
		u8g2 -> setFont(u8g_font_8x13r);                      // set bigger font
		dtostrf(potentiometer_value/10.0, 1, 1, buffer);  // float to string, -- value, min. width, digits after decimal, buffer to store
		sprintf(buffer, "%s%s", buffer, "%");             // add some random ending character

		string_width = u8g2 -> getStrWidth(buffer);           // calculate string width

		u8g2 -> setColorIndex(1);                             // set color to white
		u8g2 -> drawRBox(64-(string_width+4)/2, 0, string_width+4, 11, 2);  // draw background rounded rectangle
		u8g2 -> drawTriangle( 64-3, 11,   64+4, 11,   64, 15);              // draw small arrow below the rectangle
		u8g2 -> setColorIndex(0);                                           // set color to black
		u8g2 -> drawStr(64-string_width/2, 10, buffer);                     // draw the value on top of the display
	}

	void draw_upir_logo(void) {
		u8g2 -> setColorIndex(1);
		u8g2 -> drawBitmap(112, 0, 2, 4, upir_logo);
	}

	void draw_fps(void) {
		u8g2 -> setColorIndex(1);                                           // set color to white
		u8g2 -> setFont(u8g_font_5x7r);                                     // set very small font
		itoa(fps, buffer, 10);                                          // convert FPS number to string
		u8g2 -> drawStr(0,10,buffer);                                       // draw the FPS number
	}

	public:
	round_watch_face(U8G2* d) : u8g2(d) {
		for (int i = 0; i < 180; i++) {    // pre-calculate x and y positions into the look-up tables
			precalculated_x_radius_pixel[i] =  sin(radians(i-90)) * radius_pixel + center_x;
			precalculated_y_radius_pixel[i] = -cos(radians(i-90)) * radius_pixel + center_y;
		}
	}

	void draw(int value) {

		potentiometer_value = value;     // read the potentiometer value, remap it to 0-1000

		// calculate tickmarks
		calculate_tickmarks_and_draw();
		// draw the big value on top
		draw_the_big_value_on_top();
		// draw upir logo
		draw_upir_logo();
		// display FPS, could be commented out for the final product
		draw_fps();


		millis_time_last = millis_time;                                  // store last millisecond value
		millis_time = millis_time+33;                                          // get millisecond value from the start of the program
		fps = round(1000.0/ (millis_time*1.0-millis_time_last));         // calculate FPS (frames per second) value

	}
};
}

#endif