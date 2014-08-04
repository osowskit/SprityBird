//
//  Skillz+TurnBased.h
//  SkillzSDK-iOS
//
//  Copyright (c) 2014 Skillz. All rights reserved.
//

#import "SkillzInstance.h"

@class SKZTurnBasedMatchInfo;

/**
 * These enums control the outcome of the round, currently this is used to support the Skillz UI by displaying to the player who has won each consecutive round.
 * The values specified for "completeTurnWithGameData:" will be returned to you via the SKZRoundResults objects contained in the SKZTurnBasedMatchInfo passed in when launching a turn based match.
 *
 */

typedef NS_ENUM(NSUInteger, SKZTurnBasedRoundOutcome) {
    
    /**
     *  The current player's turn has resulted in a loss for the round for them.
     */
    kSKZRoundOutcomeRoundLoss       = 0,
    
    /**
     *  The current player's turn has resulted in a win for the round for them.
     */
    kSKZRoundOutcomeRoundWin        = 1,
    
    /**
     *  The current player's turn has resulted in a draw for the round for them.
     */
    kSKZRoundOutcomeRoundDraw       = 2,
    
    /**
     *  The current player's turn has had no clear result as far as Win/Loss/Draw for the round.
     */
    kSKZRoundOutcomeRoundNoOutcome  = 4
};

/**
 * These enums are used to decide who will win the prize for the current round. 
 * Sending up "kSKZMatchOutcomeMatchNoOutcome" will continue play, sending up any other value will end the match with the specifed outcome and award the prize for the match.
 *
 */
typedef NS_ENUM(NSUInteger, SKZTurnBasedMatchOutcome) {

    /**
     *  The current player's turn has resulted in a loss for the match for them, end match.
     */
    kSKZMatchOutcomeMatchLoss       = 0,
    
    /**
     *  The current player's turn has resulted in a win for the match for them, end match.
     */
    kSKZMatchOutcomeMatchWin        = 1,
    
    /**
     *  The current player's turn has resulted in a draw for the match for them, end match.
     */
    kSKZMatchOutcomeMatchDraw       = 2,
    
    /**
     *  The current player's turn has resulted in no outcome for the match, continue play.
     */
    kSKZMatchOutcomeMatchNoOutcome  = 4
};

@interface Skillz (TurnBased)

#pragma mark Turn Based Launching
/**
 *  Launch the Skillz' experience with turn based tournament options.
 *
 *  @param orientation          The locked orientation to launch Skillz in: SkillzPortrait or SkillzLandscape
 *  @param completion           Called when Skillz SDK finishes launching
 *  @param tournamentLaunch     Called when a user wants to initiate a tournament that is not turn based; matchRules dictionary contains the tournament specific rules for launching a game
 *  @param turnBasedLauncher    Called in order to load a turn based match, will pass you SKZTurnInformation in order for you to construct your game
 *  @param reviewLauncher       Called in order to load an uninteractive game state, allowing the player to review the game state, but not allowing them to complete a turn or manipulate a game state.
 *  @param exit                 Called when the user Exits the Skillz Experience so the game developer can reinstantiate their game flow.
 
 *  If you do not implement one of these features, pass nil.
 
 *  Example: If you do not support reviewing current game state for match pass nil for "reviewLauncher".
 *  Example: If you only support turn based tournament types,  pass nil for "tournamentLaunch".
 */
- (void)launchSkillzForOrientation:(SkillzOrientation)orientation
                launchHasCompleted:(void (^)(void))completion
               tournamentWillBegin:(void (^)(NSDictionary * matchRules))tournamentLaunch
      turnBasedTournamentWillBegin:(void (^)(SKZTurnBasedMatchInfo *currentTurnInfo, NSDictionary *matchRules))turnBasedLauncher
            reviewCurrentGameState:(void (^)(SKZTurnBasedMatchInfo *currentTurnInfo, NSDictionary *matchRules))reviewLauncher
                    skillzWillExit:(void (^)(void))exit;


#pragma mark Reviewing game State
/**
 *  When your user has finished reviewing the current game state, use this method to return to the Skillz UI.
 *
 *  @param completion Called after Skillz UI has been displayed, use to clean up any outstanding objects in your game hierarchy.
 */
- (void)finishReviewingCurrentGameState:(void (^)(void))completion;


#pragma Completing Turns
/**
 *  Completes a turn for a game, giving you access to a full range of options to convey to Skillz the final outcome of the match. If a value does not pertain to your game, pass nil. You must track and update playerTotalScore and opponentTotalScore yourself each turn.
 *
 *  @param gameData             A Base64 encoded NSString object containing serialized data which can be used to reconstruct the game state for the next   turn, or to review the current game state.
 *  @param score                The score the current user has obtained for *this* turn, this will be displayed in the Skillz UI, not used to calculate match outcomes.
 *  @param playerTotalScore     The final score for the current player, passing nil will not modify the current player's score. Also used in Skillz UI, not match outcomes
 *  @param opponentTotalScore   The final score for the opponent player, passing nil will not modify the opponent's score. Also used in Skillz UI, not match outcomes
 *  @param turnOutcome          Passed to determine the outcome of a round. Round outcomes are used with in the Skillz UI. See SKZTurnBasedRoundOutcome for more information.
 
 *  @param matchOutcome         Passed to determine the state of the match. Match outcomes determine the outcome of the match as whole, be it Win, Lose, or Tie. 
                                Pass "kSKZMatchOutcomeMatchNoOutcome" to continue play and pass control to opponent.
                                See SKZTurnBasedRoundOutcome for more information
 
 *  @param completion           Called after Skillz UI has been displayed, use to clean up any outstanding objects in your game hierarchy.
 */
- (void)completeTurnWithGameData:(NSString *)gameData
                     playerScore:(NSString *)score
         playerCurrentTotalScore:(NSNumber*)playerCurrentTotalScore
       opponentCurrentTotalScore:(NSNumber*)opponentCurrentTotalScore
                    roundOutcome:(SKZTurnBasedRoundOutcome)turnOutcome
                    matchOutcome:(SKZTurnBasedMatchOutcome)matchOutcome
                  withCompletion:(void (^)(void))completion;


@end
