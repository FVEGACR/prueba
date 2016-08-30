#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SampleDiagnostic.h"
#import "FinalDiagnostic.h"
#import "LivenessDiagnostic.h"
#import "TemplateInfo.h"

/**
	Contains the data obtained as a result of the extraction/detection process carried out in an image.
*/
@interface FPBExtractionResult : NSObject<NSCopying>

/**
	Gets face detection diagnostic of a sample.
	@see SampleDiagnostic
*/
@property (nonatomic,readonly) FPBSampleDiagnostic sampleDiagnostic;

/**
	Final diagnostic for the image stream.
	@see FinalDiagnostic
*/
@property (nonatomic,readonly) FPBFinalDiagnostic finalDiagnostic;

/**
	Gets the location and the size of the face found in the processed image.
	@see CGRect
*/
@property (nonatomic,readonly) CGRect face;

/**
	Gets the left eye position coordinates of the individual (right eye from the observer's point of view).
	@see CGPoint
*/
@property (nonatomic,readonly) CGPoint leftEye;

/**
	Gets the right eye position coordinates of the individual (left eye from the observer's point of view).
	@see CGPoint
*/
@property (nonatomic,readonly) CGPoint rightEye;

/**
	Gets the template containing the facial information obtained as a result of the processed samples.
*/
-(NSData *) getTemplate;

/**
	Indicates the presence of face in the processed image.
*/
@property (nonatomic,readonly) bool faceAvailable;

/**
	Indicates the presence of the left eye in the face.
*/
@property (nonatomic,readonly) bool leftEyeAvailable;

/**
	Indicates the presence of the right eye in the face.
*/
@property (nonatomic,readonly) bool rightEyeAvailable;

/**
	Indicates the number of valid patterns obtained.
*/
@property (nonatomic,readonly) int validPatterns;

/**
	Liveness diagnostic for the image stream.
	@see LivenessDiagnostic
*/
@property (nonatomic, readonly) FPBLivenessDiagnostic livenessDiagnostic;

/**
    Sets liveness diagnostic.
 */
-(void) SetLivenessDiagnostic:(FPBLivenessDiagnostic)livenessDiagnostic;

/**
    Template info for the image stream.
 */
@property (nonatomic, readonly) FPBTemplateInfo* templateInfo;

@end
