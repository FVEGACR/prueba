#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "LivenessDiagnostic.h"

/**
	Liveness result.
*/
@interface FPBLivenessResult : NSObject<NSCopying>

/**
	Liveness diagnostic.
	@see LivenessDiagnostic
*/
@property (nonatomic,readonly) FPBLivenessDiagnostic livenessDiagnostic;

/**
	Indicates the penalty.
*/
@property (nonatomic,readonly) int penalty;





@end
