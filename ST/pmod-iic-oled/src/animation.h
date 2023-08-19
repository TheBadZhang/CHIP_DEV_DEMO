#ifndef __TBZ_ANIMATION_H_
#define __TBZ_ANIMATION_H_

#include "common.h"
#include "oled.h"
#include "random.h"

namespace tbz {
struct sprite {
	uint8_t frames_num;
	uint8_t pos_y;
	uint8_t pos_x;
};

struct SPRITE_PIC {
	const uint8_t* sprite_pic;
	uint8_t sprite_pic_width;
	uint8_t sprite_pic_height;
	uint8_t sprite_frame_count;
	uint8_t sprite_width;
	uint8_t sprite_height;
	SPRITE_PIC (const uint8_t* pic) : sprite_pic(pic) {}
};

template <uint8_t sprite_count>
class animation {
	private:
	SPRITE_PIC sprite_pic;
	// const uint8_t sprites_count;
	sprite sprites[sprite_count];
	U8G2* u8g2;

	public:
	animation (const uint8_t pic[], uint8_t width, uint8_t height,
		uint8_t sprite_width, uint8_t sprite_height,
		uint8_t sprite_frame_counts, U8G2* device) : sprite_pic(pic) {

		u8g2 = device;

		// sprite_pic.sprite_pic = pic;
		sprite_pic.sprite_pic_width = width;
		sprite_pic.sprite_pic_height = height;
		sprite_pic.sprite_width = sprite_width;
		sprite_pic.sprite_height = sprite_height;
		sprite_pic.sprite_frame_count = sprite_frame_counts;

		for (int i = 0; i < sprite_count; i++) {
			sprites[i].frames_num = tbz::rand()%sprite_pic.sprite_frame_count;
			sprites[i].pos_x = tbz::rand()%(128-sprite_pic.sprite_width);
			sprites[i].pos_y = tbz::rand()%(64-sprite_pic.sprite_height);
		}
	}

	void draw(void) {
		for (int i = 0; i < sprite_count; i++) {
			u8g2 -> drawXBMP(sprites[i].pos_x, sprites[i].pos_y,
				sprite_pic.sprite_width,sprite_pic.sprite_height,
				sprite_pic.sprite_pic+(sprites[i].frames_num*8));
			sprites[i].frames_num ++;
			if (sprites[i].frames_num >= sprite_pic.sprite_frame_count) {
				sprites[i].frames_num = 0;
				sprites[i].pos_x = tbz::rand()%(128-sprite_pic.sprite_width);
				sprites[i].pos_y = tbz::rand()%(64-sprite_pic.sprite_height);
			}
		}
	}
};

}
#endif