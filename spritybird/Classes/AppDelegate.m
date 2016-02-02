//
//  AppDelegate.m
//  spritybird
//
//  Created by Alexis Creuzot on 09/02/2014.
//  Copyright (c) 2014 Alexis Creuzot. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import <Skillz/Skillz.h>

@implementation AppDelegate

#pragma mark - Skillz SDK Delegate implementation
- (void)tournamentWillBegin:(NSDictionary *)gameParameters
              withMatchInfo:(SKZMatchInfo *)matchInfo
{
    NSLog(@"Test Match Info matchId:%ld description:%@ entryCash:%@ entryPoints:%@ isCash:%d name:%@ templateId:%@",
          matchInfo.id,
          matchInfo.matchDescription,
          matchInfo.entryCash,
          matchInfo.entryPoints,
          matchInfo.isCash,
          matchInfo.name,
          matchInfo.templateId);
    
    SKZPlayer *player = matchInfo.player;
    NSLog(@"TestPlayer %@ %@ %@ %@", player.id, player.displayName, player.flagURL, player.avatarURL);
    
    ViewController* viewController = (ViewController*) self.window.rootViewController.modalViewController;
    [viewController startGame];
}

- (SkillzOrientation)preferredSkillzInterfaceOrientation
{
    return SkillzPortrait;
}

- (void)skillzWillExit
{
    [self.window.rootViewController dismissViewControllerAnimated:YES completion:^(void){}];
}

- (void) skillzHasFinishedLaunching
{
    NSLog(@"Skillz launched");
    
    SKZPlayer *player = [Skillz player];
    if (player) {
        NSLog(@"TestPlayer %@ %@ %@ %@", player.id, player.displayName, player.flagURL, player.avatarURL);
    } else {
        NSLog(@"TestPlayer nil");
    }
}
#pragma mark - End Delegate implementation

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Set the enviroment based on the build type
#ifdef DEBUG
    SkillzEnvironment skillzEnv = SkillzSandbox;
#else
    SkillzEnvironment skillzEnv = SkillzProduction;
#endif
    
    // General Skillz initialization
    // Id is given to us by the devportal
    [[Skillz skillzInstance] initWithGameId:@"777"
                                forDelegate:self
                            withEnvironment:skillzEnv];
    
    SKZPlayer *player = [Skillz player];
    if (player) {
        NSLog(@"TestPlayer %@ %@ %@ %@", player.id, player.displayName, player.flagURL, player.avatarURL);
    } else {
        NSLog(@"TestPlayer nil");
    }
    
    return YES;
}
- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
    return UIInterfaceOrientationMaskPortrait;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
