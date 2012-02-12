#import "ShadowsAppDelegate.h"
#import "GLView.h"

#include "MacPlatform.h"
#include "Game.h"
#include "TitleScene.h"
#include "ResourceCache.h"
#include "MacPlatform.h"

@implementation ShadowsAppDelegate

@synthesize window, view;

- (void)render {
  game->main_loop();
  [view drawRect:view.bounds];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  MacPlatform* platform = MacPlatform::instance();
  [view setPlatform:platform];     
  
  ResourceCache::instance()->set_platform(platform);
  
  game = Game::game();
  game->init_with_scene(TitleScene::scene());

  [NSTimer scheduledTimerWithTimeInterval:(1.0f/60)target:self 
                                 selector:@selector(render) 
                                 userInfo:nil 
                                  repeats:YES];
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
  CGDisplayHideCursor(kCGDirectMainDisplay);
}

@end
