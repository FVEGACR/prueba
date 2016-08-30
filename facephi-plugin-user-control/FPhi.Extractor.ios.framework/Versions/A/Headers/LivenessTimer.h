#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import "LivenessTimerDiagnostic.h"

/**
	Liveness timer diagnostic. */
@interface FPBLivenessTimer : NSObject<NSCopying>


/**
	Gets time lapse in milliseconds.
    @return Time lapse.
 */
-(int) GetTimeLapse;

/**
	Gets fps.
    @return Frames per second.
 */
-(float) GetFps;

/**
    Sets the frame rate.
    @param timeLapse Time lapse in milliseconds.
	@param fps Frames per second.
	@return True if the params are correct and false otherwise..
 */
-(bool) SetValues:(int)timeLapse :(float)fps;

/**
    Resets the timer.
 */
-(void) Reset;

/**
    Add the clock to the timer.
    @param milliseconds Clock in milliseconds.
	@return True if the millisecond are correct and false otherwise.
 */
-(bool) Add: (int) milliseconds;

/**
    Check if the timer is full.
	@return True if the timer is full and false otherwise.
 */
-(bool) IsFull;

/**
    Evaluates the liveness timer.
	@return Liveness timer diagnostic.
 */
-(FPBLivenessTimerDiagnostic *) Evaluate;


@end

