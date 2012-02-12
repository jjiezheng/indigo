#import "GLView.h"

#include "ResourceCache.h"
#include "MacPlatform.h"

@implementation GLView

- (id)initWithFrame:(NSRect)theFrame pixelFormat:(NSOpenGLPixelFormat*)thePixelFormat {	
	if(thePixelFormat == nil) {
		NSOpenGLPixelFormatAttribute pixelAttributes [] 
    =	{
      NSOpenGLPFADoubleBuffer,
      NSOpenGLPFADepthSize, 24,
      NSOpenGLPFAStencilSize, 8,
      0
    };
        		
		thePixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes: pixelAttributes] autorelease];
	}
  
	if ((self = [super initWithFrame:theFrame pixelFormat:thePixelFormat] ) ) {		
		[[self openGLContext] makeCurrentContext];
		[self setFrameSize:theFrame.size];
		[self setPostsFrameChangedNotifications:YES];
  }
  
  mouseMovedCount = 0;
  
	return self;
}

- (void)viewDidMoveToWindow {
  [[self window] setAcceptsMouseMovedEvents:YES];
  [[self window] makeFirstResponder:self];
}

- (void) drawRect: (NSRect) bounds {
  [[self openGLContext] makeCurrentContext];
  [[self openGLContext] flushBuffer];
}

- (void)setPlatform:(Platform*)thePlatform {
  platform = thePlatform;
  platform->set_screen_size(self.bounds.size.width, self.bounds.size.height);
}

- (void)mouseMoved:(NSEvent *)theEvent {
  CGPoint windowCenter;
  NSArray *theScreens = [NSScreen screens];
  for (NSScreen *theScreen in theScreens) {
    windowCenter = CGPointMake([self window].frame.origin.x+800/2, 
                                 (-1)*([self window].frame.origin.y-theScreen.frame.size.height)-600/2);
    break;
  }
  
  CGDisplayMoveCursorToPoint (kCGDirectMainDisplay, windowCenter);
  
  int32_t x = 0;
  int32_t y = 0;
  
  CGGetLastMouseDelta(&x, &y);
  
  // wait 2 input events otherwise the mouse jumps
  if (mouseMovedCount > 2) {
    platform->set_mouse_delta(x, y);
  } else {
    mouseMovedCount++; 
  }
}

- (void)keyDown:(NSEvent *)theEvent {
  platform->set_key_state(theEvent.keyCode, true);
}

- (void)keyUp:(NSEvent *)theEvent {
  platform->set_key_state(theEvent.keyCode, false);
}

@end


