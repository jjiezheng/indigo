#import "GLView.h"

#include "MacPlatform.h"

@implementation GLView

- (void)awakeFromNib {
  [[self window] setAcceptsMouseMovedEvents:YES];
  [[self window] makeFirstResponder:self];
}

- (void)keyDown:(NSEvent *)theEvent {
  MacPlatform::instance()->set_key_state(theEvent.keyCode, true);
}

- (void)keyUp:(NSEvent *)theEvent {
  MacPlatform::instance()->set_key_state(theEvent.keyCode, false);
}

@end
