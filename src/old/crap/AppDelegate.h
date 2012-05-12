#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate> {
  NSWindow* _window;
  NSViewController* _rootController;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSViewController *rootController;

@end
