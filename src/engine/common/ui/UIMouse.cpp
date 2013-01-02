#include "UIMouse.h"

#include "io/Path.h"
#include "ui/Sprite.h"

UIMouse* UIMouse::mouse(const std::string& cursorPath) {
    std::string fullCursorPath = Path::pathForFile(cursorPath);
    UIMouse* mouse = new UIMouse();
    mouse->init(fullCursorPath);
    return mouse;
}

void UIMouse::init(const std::string& cursorPath) {
  sprite_ = Sprite::fromFile(cursorPath);
}

void UIMouse::render(const Matrix4x4& projection) {
  sprite_->render(projection);
}

void UIMouse::update(float dt) {

}
