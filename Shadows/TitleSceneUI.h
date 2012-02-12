#ifndef TitleSceneUI_H_
#define TitleSceneUI_H_

#include "Layer2d.h"

class TitleSceneUI : public Layer2d {
  
public:
  
  static
  TitleSceneUI* ui();
  
private:
  
  void init();
  
private:
  
  TitleSceneUI() = default;
  
};

#endif
