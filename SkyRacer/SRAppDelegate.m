//
//  SRAppDelegate.m
//  SkyRacer
//
//  Created by Andre Cohen on 8/17/14.
//  Copyright (c) 2014 White Shoe Media. All rights reserved.
//

#import "SRAppDelegate.h"
#import "SRMyScene.h"

@implementation SRAppDelegate

@synthesize window = _window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    /* Pick a size for the scene */
    SKScene *scene = [SRMyScene sceneWithSize:CGSizeMake(1024, 768)];

    /* Set the scale mode to scale to fit the window */
    scene.scaleMode = SKSceneScaleModeAspectFit;

    [self.skView presentScene:scene];

    self.skView.showsFPS = YES;
    self.skView.showsNodeCount = YES;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end
