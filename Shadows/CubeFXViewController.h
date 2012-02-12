#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "Game.h"

@interface CubeFXViewController : UIViewController {  
  BOOL animating;
  CADisplayLink *displayLink;
  Game* game;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;

- (void)startAnimation;
- (void)stopAnimation;

@end
