#ifndef FONTCHARACTER_H_
#define FONTCHARACTER_H_

struct FontCharacter {

public:

  FontCharacter()
    : id(-1)
    , x(0)
    , y(0)
    , width(0)
    , height(0)
    , xoffset(0)
    , yoffset(0)
    , vertexBuffer(0)
    , xadvance(0) { }

public:

  int id;

  unsigned int x;
  unsigned int y;

  unsigned int width;
  unsigned int height;

  int xoffset;
  int yoffset;

  int xadvance;

  unsigned int vertexBuffer;

};

#endif