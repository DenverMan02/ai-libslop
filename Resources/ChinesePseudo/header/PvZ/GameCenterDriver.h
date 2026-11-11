#ifdef HOST_IPHONEOS
#import <Foundation/Foundation.h>

@class GKAchievement;

@protocol GameCenterDelegate
- (void) onAuthenticationChanged:(BOOL)i_connected;
@end

@interface GameCenterDriver : NSObject
{
	// the achievement caching code is not very well thought out wrt
	// network connectivity & should probably be gutted since GameCenter
	// handles most of the complexity under the hood.
@private
    BOOL is_connected_;
    BOOL is_fetching_achievements_;
    BOOL are_achievements_synced_;
    id <GameCenterDelegate> delegate_;
    NSMutableDictionary *cached_achievements_;
    NSMutableArray *pending_achievements_;
    NSMutableArray *unsubmitted_achievements_;
}
@property(readonly,getter=isConnected) BOOL is_connected_;
- (id) initWithDelegate:(id<GameCenterDelegate>)delegate;
- (void) connectToGameCenter;
- (void) queueAchievement:(NSString*)achievement_id withPercentComplete:(float)percent;
- (void) submitAchievements;
- (void) submitScore:(NSInteger)score toLeaderboard:(NSString*)leaderboard_id;
- (void) resetAchievements;
- (void) fetchAchievements;
- (void) showAchievementView;
- (void) showLeaderboardView:(NSString*)leaderboard_id;
- (bool) isLoginVisible;
- (bool) isBeingDisplayed;
@end

#endif // HOST_IPHONEOS
