#import <Cocoa/Cocoa.h>

#import <CoreVideo/CVDisplayLink.h>

@interface GLViewController : NSViewController<NSWindowDelegate> {
  CVDisplayLinkRef displayLink;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSOpenGLView *view;

@end
