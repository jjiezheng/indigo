#import "AppDelegate.h"

@implementation AppDelegate

- (void)dealloc {
  [super dealloc];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication {
  return YES;
}

@end
