//
//  SkillzInstance.h
//  SkillzSDK-iOS
//
//  Copyright (c) 2014 Skillz. All rights reserved.
//  http://skillz.com/
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 * Skillz requires explicitly linking with the following Frameworks:
 *  1. libz
 *  2. libsqlite3
 *  3. libxml2
 *
 * Skillz requires enabling "Modules" (this auto-links all the required Frameworks):
 *
 *  Under "Apple LLVM 5.0 - Languages - Modules" in Build Settings, set
 *   - Enable Modules (C and Objective-C): YES
 *   - Link Frameworks Automatically: YES
 *
 * Skillz also requires the following linker flags:
 *  1. -ObjC
 *  2. -lc++
 *  3. -lz
 */


#pragma mark - Skillz SDK typedefs

/**
 NS_ENUM defining the different servers that Skillz can connect to.
 */
typedef NS_ENUM (NSInteger, SkillzEnvironment) {
    /** Used when connecting to the live production server. */
    SkillzProduction,
    /** Used when connecting to the test sandbox server. */
    SkillzSandbox
};

/**
 NS_ENUM defining the orientations that Skillz can be launched in.
 */
typedef NS_ENUM (NSInteger, SkillzOrientation){
    /** Used to launch Skillz in a portrait orientation. */
    SkillzPortrait,
    /** Used to launch Skillz in a landscape orientation. This will match the landscape orientation of your game. */
    SkillzLandscape
};

#pragma mark - Skillz SDK interface

__attribute__ ((visibility("default")))

/**
 Main interface for the Skillz SDK
 */
@interface Skillz : NSObject <CLLocationManagerDelegate, UIPopoverControllerDelegate>


///------------------------------
///@name Skillz SDK Properties
///------------------------------
/**
 * Whether or not a Skillz match is currently in progress.
 */
@property BOOL tournamentIsInProgress;


#pragma mark - Skillz SDK Functions

///----------------------------------------------------
///@name Skillz SDK Class Methods
///----------------------------------------------------

/**
 Get a singleton reference to the Skillz SDK
 @return The singleton instance of the Skillz SDK object
 */
+ (Skillz *)skillzInstance;

/**
 * Returns a random integer supplied by the Skillz SDK to ensure fairness across competition games.
 *
 * The range of this function is [0, RAND_MAX) (0 is inclusive, RAND_MAX is exclusive)
 *
 * On iOS, RAND_MAX is 2,147,483,647
 *
 * Players in the same tournament will receive the same sequence of random numbers.
 */
+ (NSInteger)getRandomNumber;

/**
 * Returns a random unsigned integer supplied by the Skillz SDK to ensure fairness across competition games.
 *
 * Number will be in the range [min,max) (min is inclusive, max is exclusive), and the probability will be evenly distributed amongst all the possible values.
 *
 * [Skillz skillzgetRandomNumberWithMin:2 andMax:10] will return one of the following numbers with equal probability: 2,3,4,5,6,7,8,9
 *
 * Players in the same tournament will receive the same sequence of random numbers.
 *
 *  @param min  The minimum possible value returned, inclusive.
 *  @param max  The maximum possible value returned, exclusive.
 */
+ (NSUInteger)getRandomNumberWithMin:(NSUInteger)min
                              andMax:(NSUInteger)max;

///----------------------------------------------------
///@name Skillz SDK Instance Methods
///----------------------------------------------------

/**
 * Initialize Skillz
 *
 * This needs to be called within application:didFinishLaunchingWithOptions in your App Delegate.
 * Will not launch the Skillz experience, this function only establishes the connection between your game and the SkillzEnvironment of choice.
 *
 *  @param gameId           Your game ID as given to you on the Skillz developer portal
 *  @param environment      SkillzSandbox for sandbox testing or SkillzProduction for app store submission.
 */
- (void)skillzInitForGameId:(NSString *)gameId
                environment:(SkillzEnvironment)environment;

/**
 * Launch the Skillz Experience
 *
 *  @param orientation      The locked orientation to launch Skillz in: SkillzPortrait or SkillzLandscape
 *  @param completion       Called when Skillz SDK finishes launching
 *  @param tournamentLaunch Called when a user wants to initiate a tournament; matchRules dictionary contains the tournament specific rules for launching a game
 *  @param exit             Called when the user Exits the Skillz Experience so the game developer can reinstantiate their game flow.
 *
 * This function is what will actually render the Skillz experience on screen. This function will draw a ViewController onto your view hierarchy.
 * Because of this, do not call this method while attempting to draw another ViewController on screen as well.
 *
 *
 */
- (void)launchSkillzForOrientation:(SkillzOrientation)orientation
                launchHasCompleted:(void (^)(void))completion
               tournamentWillBegin:(void (^)(NSDictionary * matchRules))tournamentLaunch
                    skillzWillExit:(void (^)(void))exit;

/**
 *  Call this function to report the player's score to Skillz. Ends the current tournament, and returns the user to the Skillz experience.
 *
 *   @param score            Numeric value representing the player's final score
 *   @param scoreExtras   Dictionary of extra score parameters (optional -- set to nil if not using)
 *   @param completion       Completion will be called on wrap up so that the developer can finish any ongoing processes, such as saving game data or removing the game from the view hierarchy.
 */
- (void)displayTournamentResultsWithScore:(NSNumber *)score
                           andScoreExtras:(NSDictionary *)scoreExtras
                           withCompletion:(void (^)(void))completion;

/**
 *  Call this function when a player aborts a Skillz match in progress. Forfeits the match and brings the user back into the Skillz experience.
 *
 *   @param completion      Completion will be called on wrap up so that the developer can finish any ongoing processes, such as saving game data or removing the game from the view hierarchy.
 */
- (void)notifyPlayerAbortWithCompletion:(void (^)(void))completion;

/**
 *  If your game plays it's own background music that you'd like to play in the Skillz UI, set hasBackgroundMusic to YES to prevent the Skillz music from being played.
 *
 *  @param hasBackgroundMusic       Whether or not your game uses background music.
 */
- (void)setGameHasBackgroundMusic:(BOOL)hasBackgroundMusic;

#pragma mark - Sklillz SDK Information

///----------------------------------------------------
///@name Skillz SDK Information
///----------------------------------------------------

/**
 *  Get the version of the Skillz SDK
 *
 *  @return The SDK Version
 */
+ (NSString *)SDKShortVersion;

/**
 *  Display the long version of SDK Info in a UIAlertView
 */
+ (void)showSDKVersionInfo;

/**
 *  This will return a value confirming whether or not the Skillz UI is currently presented
 *
 *  @return True if Skillz UI is currently presented, otherwise false.
 */
+ (BOOL)isSkillzPresented;

/**
 *  This will return the UIInterfaceOrientationMask set for Skillz, typically this is only used by our UnityViewControllerBase.
 *
 *  @return UIInterfaceOrientationMask for Skillz
 */
+ (UIInterfaceOrientationMask)skillzOrientation;


@end

