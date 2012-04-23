#import <Cocoa/Cocoa.h>

#import <CoreVideo/CVDisplayLink.h>

@interface GLViewController : NSViewController<NSWindowDelegate> {
  CVDisplayLinkRef displayLink;
  NSWindow *_window;
  NSOpenGLView *_view;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSOpenGLView *view;

@end
