#import "GameView.h"

@implementation GameView

- (void)dealloc {
  // Release the display link
  CVDisplayLinkRelease(displayLink);
  [super dealloc];
}

- (void)prepareOpenGL {
  [self.window setDelegate:self];

  NSArray *arguments = [[NSProcessInfo processInfo] arguments];
  const char* sceneFile = [[arguments objectAtIndex:1] cStringUsingEncoding:NSUTF8StringEncoding];
  
  app_.init(sceneFile);
  
  // Synchronize buffer swaps with vertical refresh rate
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
  
  // Create a display link capable of being used with all active displays
  CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
  
  // Set the renderer output callback function
  CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
  
  // Set the display link for the current renderer
  CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
  CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
  CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
  
  // Activate the display link
  CVDisplayLinkStart(displayLink);
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext) {
  CVReturn result = [(GameView*)displayLinkContext getFrameForTime:outputTime];
  return result;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime {
  // Add your drawing codes here
  app_.mainLoop();
  return kCVReturnSuccess;
}

- (void)windowWillClose:(NSNotification *)notification {
  app_.destroy();
}


@end
