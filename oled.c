/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Sets up what the OLED screens display.

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 // Switch to fast animation when over words per minute
#ifdef OLED_ENABLE

static void render_logo(void) {
  static const char PROGMEM blackpink_logo[] = {
      0,   252, 252, 12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
      12,  12,  12,  12,  252, 252, 0,   0,   0,   255, 255, 0,   0,   244, 248,
      252, 252, 140, 140, 140, 220, 252, 248, 112, 0,   0,   244, 248, 252, 252,
      0,   0,   0,   2,   7,   14,  7,   2,   0,   128, 192, 224, 248, 60,  60,
      248, 224, 192, 128, 0,   0,   0,   52,  24,  12,  12,  12,  28,  124, 248,
      240, 224, 0,   0,   244, 248, 124, 124, 192, 224, 240, 248, 124, 60,  28,
      12,  4,   0,   0,   2,   7,   14,  7,   2,   0,   0,   244, 248, 252, 252,
      156, 12,  12,  156, 252, 248, 240, 0,   244, 248, 252, 252, 0,   0,   244,
      248, 252, 252, 128, 192, 224, 248, 252, 252, 252, 252, 0,   0,   244, 248,
      252, 124, 96,  240, 248, 252, 60,  28,  12,  4,   0,   0,   255, 255, 0,
      0,   0,   255, 255, 0,   0,   119, 111, 95,  63,  97,  97,  97,  115, 127,
      62,  28,  0,   0,   118, 111, 95,  62,  112, 112, 112, 112, 96,  80,  0,
      64,  112, 110, 95,  63,  79,  1,   1,   15,  127, 127, 126, 112, 64,  0,
      120, 96,  80,  48,  112, 120, 124, 63,  31,  15,  0,   0,   119, 111, 93,
      60,  71,  15,  31,  60,  124, 120, 112, 96,  64,  0,   0,   3,   7,   7,
      7,   6,   0,   64,  119, 111, 95,  63,  71,  7,   7,   7,   7,   3,   1,
      0,   119, 111, 95,  63,  64,  0,   119, 111, 95,  63,  95,  7,   3,   1,
      119, 111, 95,  63,  64,  0,   119, 111, 95,  61,  68,  31,  63,  124, 120,
      112, 96,  64,  0,   0,   255, 255, 0,   0,   0,   63,  63,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,
      48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  63,  63,
      0,   0,
  };
  oled_write_raw_P(blackpink_logo, sizeof(blackpink_logo));
}
/* KEYBOARD PET START */

/* settings */
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

/* advanced settings */
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE                                                              \
  96 // number of bytes in array. If you change sprites, minimize for adequate
     // firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
  /* Sit */
  static const char PROGMEM sit[2][ANIM_SIZE] = {
      /* 'sit1', 32x22px */
      {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04,
          0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08,
          0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06,
          0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20,
          0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      },

      /* 'sit2', 32x22px */
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9,
       0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
       0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20,
       0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

  /* Walk */
  static const char PROGMEM walk[2][ANIM_SIZE] = {
      /* 'walk1', 32x22px */
      {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90,
          0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90,
          0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00,
          0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f,
          0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e,
          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      },

      /* 'walk2', 32x22px */
      {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20,
          0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20,
          0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01,
          0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
          0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05,
          0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32,
          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      }};

  /* Run */
  static const char PROGMEM run[2][ANIM_SIZE] = {
      /* 'run1', 32x22px */
      {
          0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80,
          0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04,
          0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00,
          0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03,
          0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32,
          0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
      },

      /* 'run2', 32x22px */
      {
          0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10,
          0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01,
          0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10,
          0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e,
          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      }};

  /* Bark */
  static const char PROGMEM bark[2][ANIM_SIZE] = {
      /* 'bark1', 32x22px */
      {
          0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18,
          0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01,
          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48,
          0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28,
          0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05,
          0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      },

      /* 'bark2', 32x22px */
      {
          0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90,
          0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01,
          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0,
          0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28,
          0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05,
          0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      }};

  /* Sneak */
  static const char PROGMEM sneak[2][ANIM_SIZE] = {
      /* 'sneak1', 32x22px */
      {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40,
          0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80,
          0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02,
          0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09,
          0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11,
          0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04,
          0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
      },

      /* 'sneak2', 32x22px */
      {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40,
          0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03,
          0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04,
          0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09,
          0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06,
          0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
      }};

  /* animation */
  void animate_luna(void) {
    /* jump */
    if (isJumping || !showedJump) {
      /* clear */
      oled_set_cursor(LUNA_X, LUNA_Y + 2);
      oled_write("     ", false);

      oled_set_cursor(LUNA_X, LUNA_Y - 1);

      showedJump = true;
    } else {
      /* clear */
      oled_set_cursor(LUNA_X, LUNA_Y - 1);
      oled_write("     ", false);

      oled_set_cursor(LUNA_X, LUNA_Y);
    }

    /* switch frame */
    current_frame = (current_frame + 1) % 2;

    /* current status */
    if (led_usb_state.caps_lock) {
      oled_write_raw_P(bark[current_frame], ANIM_SIZE);

    } else if (isSneaking) {
      oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

    } else if (current_wpm <= MIN_WALK_SPEED) {
      oled_write_raw_P(sit[current_frame], ANIM_SIZE);

    } else if (current_wpm <= MIN_RUN_SPEED) {
      oled_write_raw_P(walk[current_frame], ANIM_SIZE);

    } else {
      oled_write_raw_P(run[current_frame], ANIM_SIZE);
    }
  }

#if OLED_TIMEOUT > 0
  /* the animation prevents the normal timeout from occuring */
  if (last_input_activity_elapsed() > OLED_TIMEOUT &&
      last_led_activity_elapsed() > OLED_TIMEOUT) {
    oled_off();
    return;
  } else {
    oled_on();
  }
#endif

  /* animation timer */
  if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
    anim_timer = timer_read32();
    animate_luna();
  }
}

/* KEYBOARD PET END */
static void print_status_narrow(void) {
  oled_write_P(PSTR("\n\n"), false);
  // Print current mode
  switch (get_highest_layer(layer_state)) {
  case 0:
    oled_write_ln_P(PSTR("LISA"), false);
    break;
  case 1:
    oled_write_ln_P(PSTR("ROSE"), false);
    break;
  case 2:
    oled_write_P(PSTR("JENNI"), false);
    break;
  case 3:
    oled_write_P(PSTR("JISOO"), false);
    break;
  default:
    oled_write_P(PSTR("BLINK"), false);
    break;
  }
  oled_write_P(PSTR("\n\n"), false);
  // Print current layer
  oled_write_ln_P(PSTR("LAYER"), false);
  switch (get_highest_layer(layer_state)) {
  case 0:
    oled_write_P(PSTR("CLMK"), false);
    break;
  case 1:
    oled_write_P(PSTR("LOW"), false);
    break;
  case 2:
    oled_write_P(PSTR("RAI"), false);
    break;
  case 3:
    oled_write_P(PSTR("FNS"), false);
    break;
  default:
    oled_write_P(PSTR("UNDEF"), false);
  }

  oled_write_P(PSTR("\n\n\n"), false);
  led_t led_usb_state = host_keyboard_led_state();
  oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);

  /* KEYBOARD PET RENDER START */

  render_luna(0, 13);

  /* KEYBOARD PET RENDER END */
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* KEYBOARD PET STATUS START */

  case KC_LCTL:
  case KC_RCTL:
    if (record->event.pressed) {
      isSneaking = true;
    } else {
      isSneaking = false;
    }
    break;
  case KC_SPC:
  case SFT_T(KC_SPC):
    if (record->event.pressed) {
      isJumping = true;
      showedJump = false;
    } else {
      isJumping = false;
    }
    break;

    /* KEYBOARD PET STATUS END */
  case RCTL_T(KC_N):
    if (record->event.pressed && record->tap.count > 0) {
      if (get_mods() & MOD_BIT(KC_RSFT)) {
        unregister_mods(MOD_BIT(KC_RSFT));
        tap_code(KC_E);
        tap_code(KC_N);
        add_mods(MOD_BIT(KC_RSFT));
        return false;
      }
    }
    return true;

  case LCTL_T(KC_T):
    if (record->event.pressed && record->tap.count > 0) {
      if (get_mods() & MOD_BIT(KC_LSFT)) {
        unregister_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_S);
        tap_code(KC_T);
        add_mods(MOD_BIT(KC_LSFT));
        return false;
      }
    }
    return true;
  }
  return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  }
  return OLED_ROTATION_180;
}

bool oled_task_user(void) {
  /* KEYBOARD PET VARIABLES START */

  current_wpm = get_current_wpm();
  led_usb_state = host_keyboard_led_state();

  /* KEYBOARD PET VARIABLES END */
  if (is_keyboard_master()) {
    print_status_narrow();
  } else {
    render_logo();
  }
  return false;
}

#endif
