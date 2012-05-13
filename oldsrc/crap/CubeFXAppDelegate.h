//
//  CubeFXAppDelegate.h
//  CubeFX
//
//  Created by Nicholas Kostelnik on 23/07/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CubeFXViewController;

@interface CubeFXAppDelegate : NSObject <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet CubeFXViewController *viewController;

@end
