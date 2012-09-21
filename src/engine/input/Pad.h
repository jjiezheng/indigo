#ifndef PAD_H
#define PAD_H

class Pad {

public:

  static void init();

  static void update();

  static float leftStickY();

  static float leftStickX();

private:

  static float leftStickY_;

};

#endif