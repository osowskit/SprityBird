//
//  MainMenuViewController.m
//  spritybird
//
//  Created by William Manning on 4/6/15.
//  Copyright (c) 2015 Alexis Creuzot. All rights reserved.
//

#import "MainMenuViewController.h"
#import "Score.h"
#import <SkillzSDK-iOS/Skillz.h>


@interface MainMenuViewController ()
@property (weak, nonatomic) IBOutlet UIView* rootView;
@end

@implementation MainMenuViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationSlide];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

@end