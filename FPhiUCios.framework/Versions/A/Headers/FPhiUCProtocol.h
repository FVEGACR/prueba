#import <Foundation/Foundation.h>
#import "FPhiUCFrameObj.h"
/**
    Set of behavior that is expected of an object in a given situation
 */
@protocol FPhiUCProtocol <NSObject>

/**
    Invoked when the extraction process is finished.
    - Mandatory method
 */
-(void)ExtractionFinished;


@optional

/**
 Invoked when the extraction process fail.
 - Optional method
 */
-(void)ExtractionFailed:(NSError *) error;

/**
 Invoked when extraction process is cancelled by user.
 - Optional method
 */
-(void)ExtractionCancelled;

/**
 Invoked when extraction process is aborted by timeout.
 - Optional method
 */
-(void)ExtractionTimeout;


/**
 Invoked when canvas must be redraw. App can paint with this method over camera preview.
 */
-(void) ContinuousModeRefreshCanvas:(FPhiUCFrameObj *)frameObj;

/**
 Invoked when a new camera image available.
 */
-(void) ContinuousModeNewImageFromCamera:(UIImage *)img;
@end
