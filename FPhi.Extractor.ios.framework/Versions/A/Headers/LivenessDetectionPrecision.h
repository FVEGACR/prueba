/**
	\file LivenessDetectionPrecision.h
*/
/**
	Represents the accuracy level for the liveness detection process.
	<p>
		This type is used as a configuration parameter for the instances of the {@link FPBExtractor}
		class and the pattern extraction processes.
	</p>
	@see Extractor
	@see ExtractorConfigurationManager
*/
typedef NS_ENUM(NSUInteger, FPBLivenessDetectionPrecision) {
    FPBLivenessDetectionPrecisionOff = 0, /** Liveness detector disabled. */
    
    FPBLivenessDetectionPrecisionLow = 1, /** Low precision. */
    
    FPBLivenessDetectionPrecisionMedium = 2, /** Medium precision. */
    
    FPBLivenessDetectionPrecisionHigh = 3 /** High precision. */
};

