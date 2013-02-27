#include "UIMouse.h"

#include "io/Path.h"
#include "ui/Sprite.h"

#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

#include "input/Mouse.h"

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
	if (isVisible_) {
		Point mousePosition = Mouse::position();
		Matrix4x4 translation = Matrix4x4::translation(Vector4((float)mousePosition.x, (float)-mousePosition.y, 0.0f, 1.0f));

		CSize cursorSize = sprite_->size();
		Matrix4x4 scale = Matrix4x4::scale(Vector4((float)cursorSize.width / 2.0f, (float)cursorSize.height / 2.0f, 1, 1));

		Matrix4x4 model = translation * scale;
		sprite_->render(projection, model);
	}
}

void UIMouse::update(float dt) {

}
