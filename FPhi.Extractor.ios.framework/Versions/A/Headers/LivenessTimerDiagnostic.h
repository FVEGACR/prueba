#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

/**
	Liveness timer diagnostic. */
@interface FPBLivenessTimerDiagnostic : NSObject<NSCopying>

/**
	Gets the relative fps error.
    @return Relative fps error.
 */
-(float) GetRelativeFpsError;

/**
    Sets the relative fps error.
    @param fpsError FPS error.
 */
-(void) SetRelativeFpsError: (float)fpsError;

/**
	Gets the performance goodness.
    @return Performance goodness.
 */
-(int) GetPerformanceGoodness;

/**
    Sets the performance goodness.
    @param fpsError Performance goodness.
 */
-(void) SetPerformanceGoodness: (int)performanceGoodness;

@end