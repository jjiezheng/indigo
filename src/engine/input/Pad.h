#ifndef PAD_H
#define PAD_H

class Pad {

public:

  static void init();

  static void update();

public:

  static float leftStickY();

  static float leftStickX();

  static float rightStickX();

  static float rightStickY();

  static bool leftShoulder();

  static bool rightShoulder();

private:

  static float leftStickY_;
  static float leftStickX_;
  static float rightStickX_;
  static float rightStickY_;

private:

  static bool leftShoulder_;
  static bool rightShoulder_;

};

#endif