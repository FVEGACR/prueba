#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CoreMedia.h>
#import <CoreText/CoreText.h>
#import "ExtractionMode.h"
#import "FPhiUCStatus.h"
#import "FPhiUCExtractionData.h"
#import "FPhi.Extractor.ios/FPhi.Extractor.ios.h"
#import "FPhiUCCustomUI.h"

/**
 User control object. Manages ipad and iphone cameras and delivery results from a extraction process.
*/
@interface FPhiUC : UIViewController <AVCaptureVideoDataOutputSampleBufferDelegate>
{
	/**
		Capture session.
	*/
    AVCaptureSession *_captureSession;
    //UIImageView *_imageView;
	
	/**
		Custom layer.
	*/
    CALayer *_customLayer;
	
	/**
		Preview layer.
	*/
    AVCaptureVideoPreviewLayer *_prevLayer;
}
/**
 Extraction mode used to perform extraction process.
 */
@property (nonatomic) ExtractionMode extractionMode;

/**
 Status of user control. This property can be checked in any moment to check extraction process status.
 */
@property (nonatomic,readonly) FPhiUCStatus status;

/**
 Time (in seconds) waiting until face detected. If reached time with no face, extraction fail returning control to UserControl caller.
 */
@property (nonatomic) float waitingTime;

/**
 Time (in seconds) before extraction process starts. This is a wait time showing on screen a countdown.
 */
@property (nonatomic) float waitingTimeStart;

/**
 Time (in seconds) detecting faces to process starts.
 */
@property (nonatomic) float waitingTimeDetecting;

/**
 Time (in seconds) checking liveness process.
 */
@property (nonatomic) float livenessTime;

/**
 Time (in seconds) extracting images from camera. Internal extractor will use all images extracted during extraction time. See extractionMaxImages for more information.
 Use this property only in custom extraction mode.
 */
@property (nonatomic) float extractionTime;

/**
 Debug mode property. This property is only for debugging purposes. False by default.
 */
@property (nonatomic) bool debugMode;


/**
 Scene timeout property. This property sets the timeout in the information screens (In seconds, 0 or less not apply).
 */
@property (nonatomic) float sceneTimeout;

/**
 Results of a extraction process.
 */
@property (nonatomic) FPhiUCExtractionData *results;

/**
 Liveness diagnostic
 */
@property (nonatomic) FPBLivenessDiagnostic livenessDiagnostic;

/**
 if enabled, returned images are cropped to face rectangle. True by default.
 Activating this feature, face and eyes coordinates are not corresponding with cropped image returned.
 */
@property (nonatomic) bool cropImagesToFace;

/**
 Ratio used to expand or shrink face rectangle.
   ratio=1.0f original face rectangle
   ratio=1.2f 20% bigger face rectangle (default value)
   ratio=0.8f 20% smaller face rectangle
 */
@property (nonatomic) float cropRatio;


/**
 Initialize a new user control object.
 param frontCameraIfAvailable: By default rear camera used. If device's front camera is available and frontCameraIfAvailable is true, front camera is used.
 */
- (id)init :(bool)frontCameraIfAvailable :(id)delegate;

/**
 Initialize a new user control object.
 param frontCameraIfAvailable: By default rear camera used. If device's front camera is available and frontCameraIfAvailable is true, front camera is used.
 param livenessDetectionPrecision: Set the precision for the liveness detection process.
 */
- (id) initWithConfiguration :(bool)frontCameraIfAvailable delegate:(id)delegate livenessDetectionPrecision:(FPBLivenessDetectionPrecision) livenessDetectionPrecision;

/**
 Start a full extraction process. When process was finished ExtractionFinished method from protocol FPhiUCProtocol is executed.
 */
- (void)StartExtraction;

/**
 Stops a extraction process.
 */
- (void)StopExtraction;

/**
 Transform rectangle from camera image space to display space.
 Extractor returns face and eyes information in image space. Use this method to calculate in display space in order to paint in the correct place.
 */
-(CGRect)TransformToDisplaySpace:(CGRect)imageSpaceRectangle;

/**
 Return byte buffer representation of img in PNG Format
 */
+(NSData *)PNGRepresentationFromImage :(UIImage *)img;

/**
 Return byte byffer representation of img in JPEG Format.
 Parameter compressionQuality: Range [0..1]
 */
+(NSData *)JPGRepresentationFromImage :(UIImage *)img :(CGFloat)compressionQuality;

@end
