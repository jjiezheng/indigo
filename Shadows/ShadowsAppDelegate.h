#import <Cocoa/Cocoa.h>

class Game;
class MacPlatform;

@class GLView;

@interface ShadowsAppDelegate : NSObject <NSApplicationDelegate> {
  NSWindow *window;
  GLView *view;
  Game* game;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSOpenGLView *view;

@end
