
#import <UIKit/UIKit.h>
#import "FPhi.Extractor.ios/FPhi.Extractor.ios.h"

/**
 Extraction record. this object store extraction information.
 */
@interface FPhiUCExtractionRecord : NSObject

/**
 Image used in extraction process.
 */
@property UIImage *image;

/**
 Extraction result.
 */
@property FPBExtractionResult *result;

/**
 Time where image was extracted.
 */
@property NSDate *time;

@end
