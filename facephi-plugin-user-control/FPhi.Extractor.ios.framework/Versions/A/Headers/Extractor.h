#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import "ExtractionResult.h"
#import "ExtractorConfigurationManager.h"
#import "TemplateInfo.h"
#import "ExtractionMode.h"
#import "LivenessTimerDiagnostic.h"
#import "LivenessResult.h"

/**
	This module will be responsible for providing the functions associated with the extraction of facial templates.
	<p>
	This class provides methods to perform the pattern extraction process from a sequence of images.
	</p>
	<p>
	The sequence of operations to perform this process is, firstly, initialize the extraction process
	by calling the <b>InitStreamExtraction</b> method specifying the number of images which composes
	the images extraction sequence. Secondly, the images of the sequence should be processed one by one by using the
	<b>ExtractNext</b> method.
	</p>
	<p>
	The sequence of operations to perform this process is, firstly, initialize the extraction process
	by calling the <b>InitStreamExtraction</b> method specifying the number of images which composes
	the images extraction sequence. Secondly, the images of the sequence should be processed one by one by using the
	<b>ExtractNext</b> method.
	</p>
	<p>
	In case that the extraction process had already been initialized and someone wish to abort
    it to start a new one, the first step is to abort the current
    extraction process by calling the <b>StopStreamExtraction</b> method, otherwise the system will
    return an exception.
	</p>
*/
@interface FPBExtractor : NSObject<NSCopying>

/**
	Initializes a new instance of the {@link FPBExtractor} class with a configuration {@link FPBExtractorConfigurationManager}.
	@param ecm Extractor configuration @see ExtractorConfigurationManager.
*/
- (id) init : (FPBExtractorConfigurationManager *) ecm;

/**
	Indicates if exists an ongoing template generation process.
*/    
@property (nonatomic, readonly) bool initiated;

/**
	Initializes the pattern extraction and template creation process specifying the minimum number of patterns required and the number of samples used.
	<p>
		This method must be called before the extraction of the patterns. It is necessary to
		specify the minimum number of valid patterns required to succeed in the extraction process
		and the number of images in the image sequence used.
	</p>
	@param minimumPatternNumber Minimum number of valid patterns required to generate a correct template.
	@param samples Number of samples or images which makes up the extraction sequence.
	@param outError
		<ul>
			<li>The minimum number of valid patterns specified is less than 1 and greater than the number of samples specified.</li>
			<li>The number of samples specified is less than 1.</li>
			<li>There is already an ongoing extraction process.</li>
		</ul>
*/
-(void) InitStreamExtraction:(int) minimumPatternNumber :(int) samples :(NSError **)outError;

/**
	Initializes the pattern extraction and template creation process specifying the number of samples required.
	<p>
		This method must be called before the extraction of the patterns. It is necessary to
		specify the minimum number of valid patterns required to succeed in the extraction process
		and the number of images in the image sequence used.
	</p>
	<p>This method is equivalent to InitStreamExtraction(1, samples)</p>
	@param samples Number of samples or images which makes up the extraction sequence.
	@param outError
		<ul>
			<li>The minimum number of valid patterns specified is less than 1 and greater than the number of samples specified.</li>
			<li>The number of samples specified is less than 1.</li>
			<li>There is already an ongoing extraction process.</li>
		</ul>
*/
-(void)InitStreamExtraction:(int)samples :(NSError **)outError;

/**
	Stops the facial pattern extraction process.
*/
-(void)StopStreamExtraction:(NSError **)outError;

/**
	Performs the facial features detection from an specific image.
	@param image Image from which the detection will be performed.
	@param outError
		<ul>
			<li>The specified image has an invalid format.</li>
			<li>The number of samples specified is less than 1.</li>
			<li>An internal error during the detection process has occurred.</li>
		</ul>
	@return Result of the extraction process which contains the results of the detection process.
	@see ExtractionResult.
*/
-(NSArray *)Detect: (UIImage *)image :(NSError **)outError;

/**
	Performs an extraction of facial features from an specific image.
	@param image Image from which the facial pattern will be extracted.
	@param outError
		<ul>
			<li>The specified image has an invalid format.</li>
			<li>The number of samples specified is less than 1.</li>
			<li>An internal error during the detection process has occurred.</li>
		</ul>
	@return Result of the extraction process which contains the results of the detection process.
	@see ExtractionResult.
*/
-(NSArray *)ExtractNext: (UIImage *)image :(NSError **)outError;

/**
	Performs an extraction of facial features of the face represented by the eyes position specified as parameters.
	@param image Image from which the detection will be performed.
	@param leftEye Left eye position of the individual from which the face pattern is desired to be extracted (from the individual point of view).
	@param rightEye Right eye position of the individual from which the face pattern is desired to be extracted (from the individual point of view).
	@param outError
		<ul>
			<li>The specified image has an invalid format.</li>
			<li>The number of samples specified is less than 1.</li>
			<li>An internal error during the detection process has occurred.</li>
		</ul>
	@return Result of the extraction process which contains the results of the detection process.
	@see ExtractionResult.
*/
-(FPBExtractionResult *)ExtractNext: (UIImage *)image : (CGPoint)leftEye :(CGPoint)rightEye :(NSError **)outError;

/**
    Gets the information of several templates.
    @param templatesData Templates data.
	@param outError Error.
    @return Template info.
 */
-(FPBTemplateInfo *)EvaluateTemplates: (NSArray *)templatesData :(NSError **)outError;

/**
    Gets the extractor version.
    @return Extractor version.
 */
+(NSString *)GetVersion;

/**
	Initializes the pattern extraction and template creation process.
	<p>
 This method must be called before the extraction of the patterns.
	</p>
	@param extractionMode Extraction mode.
	@param outError
 <ul>
 <li>There is already an ongoing extraction process.</li>
 </ul>
 */
-(void)InitStreamExtractionSmart:(FPBExtractionMode)extractionMode :(NSError **)outError;

/**
	Performs an extraction of facial features of the face represented by the eyes position specified as parameters.
	@param image Image from which the detection will be performed.
	@param outError
 <ul>
 <li>The specified image has an invalid format.</li>
 <li>An internal error during the detection process has occurred.</li>
 </ul>
	@return Result of the extraction process which contains the results of the detection process.
	@see ExtractionResult.
 */
-(FPBExtractionResult *)ExtractNextSmart: (UIImage *)image :(NSError **)outError;

/**
	Performs a liveness evaluation from a list of images.
	@param images List of images to evaluate liveness.
	@param livenessTimerDiagnostic Diagnostic of liveness timer.
	@param templateReference Template reference.
	@param outError
*/
-(FPBLivenessResult *)EvaluateLiveness: (NSArray *)images :(FPBLivenessTimerDiagnostic*)livenessTimerDiagnostic :(NSData*)templateReference :(NSError **)outError;

@end
