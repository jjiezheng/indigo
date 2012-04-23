#import "GLViewController.h"


#import <CoreVideo/CVDisplayLink.h>

#include "Game.h"
#include "MacPlatform.h"

@interface GLViewController(Private)
- (void)renderForTime:(CVTimeStamp)time;
- (void)createDisplayLink;
- (void)resetCursor;
@end

@implementation GLViewController

@synthesize window = _window;
@synthesize view = _view;

- (void)awakeFromNib {
  NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
  {
    NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
    NSOpenGLPFAColorSize    , 24                           ,
    NSOpenGLPFAAlphaSize    , 8                            ,
    NSOpenGLPFADepthSize    , 32                           ,
    NSOpenGLPFADoubleBuffer ,
    NSOpenGLPFAAccelerated  ,
    0
  };
  
  NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes] autorelease];
  [self setView:[[[NSOpenGLView alloc] initWithFrame:[[[self window] contentView] bounds] pixelFormat:pixelFormat] autorelease]];
  [[[self window] contentView] addSubview:[self view]];
  [[[self view] openGLContext] makeCurrentContext];

  CGSize bounds = NSSizeToCGSize([[[self window] contentView] bounds].size);
  MacPlatform::instance()->set_screen_size(bounds.width, bounds.height);

  [self resetCursor];
  [self createDisplayLink];
}

- (void)resetCursor {
  CGPoint windowCenter;
  NSArray *theScreens = [NSScreen screens];
  for (NSScreen *theScreen in theScreens) {
    float x = theScreen.frame.size.width/2.0f;
    float y = theScreen.frame.size.height/2.0f;
    windowCenter = CGPointMake(x, y);
    break;
  }
  
  CGDisplayMoveCursorToPoint (kCGDirectMainDisplay, windowCenter);
  
  [[[self view] window] setDelegate:self];
}


CVReturn displayCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext);
CVReturn displayCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext) {
  GLViewController *controller = (GLViewController *)displayLinkContext;
  [controller renderForTime:*inOutputTime];
  return kCVReturnSuccess;
}

- (void)createDisplayLink {
  CGDirectDisplayID displayID = CGMainDisplayID();
  CVReturn error = CVDisplayLinkCreateWithCGDisplay(displayID, &displayLink);
  
  if (kCVReturnSuccess == error)
  {
    CVDisplayLinkSetOutputCallback(displayLink, displayCallback, self);
    CVDisplayLinkStart(displayLink);
  }
  else
  {
    NSLog(@"Display Link created with error: %d", error);
    displayLink = NULL;
  }
}

- (void)windowWillClose:(NSNotification *)notification {
  CVDisplayLinkStop(displayLink);
}

- (void)renderForTime:(CVTimeStamp)time {
  [[[self view] openGLContext] makeCurrentContext];  
  Game::instance()->main_loop();
  
  [[[self view] openGLContext] flushBuffer];
}

@end
