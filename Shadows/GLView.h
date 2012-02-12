#import <AppKit/AppKit.h>

#include "Platform.h"

@interface GLView : NSOpenGLView {

  Platform* platform;
  INT mouseMovedCount;
  
}

- (void)setPlatform:(Platform*)thePlatform;

@end
