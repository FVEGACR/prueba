/**
	\file PatternQualityFilter.h
 */
/**
	Represents the accuracy level for the pattern quality evaluation.
	<p>The image quality filter is used as a configuration parameter for the instances of the {@link FPBExtractor} class and the pattern extraction processes.</p>
 */
typedef NS_ENUM(NSUInteger, FPBPatternQualityFilter) {
    FPBPatternQualityFilterOff = 0, /** Disabled. */
    
    FPBPatternQualityFilterLow = 1, /** Low precision. */
    
    FPBPatternQualityFilterMedium = 2, /** Medium precision. */
    
    FPBPatternQualityFilterHigh = 3 /** High precision. */
};


