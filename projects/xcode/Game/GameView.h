#import <Cocoa/Cocoa.h>

#include "App.h"

@interface GameView : NSOpenGLView<NSWindowDelegate> {
  
  CVDisplayLinkRef displayLink; //display link for managing rendering thread
  
  App app_;
  
};

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime;

@end
