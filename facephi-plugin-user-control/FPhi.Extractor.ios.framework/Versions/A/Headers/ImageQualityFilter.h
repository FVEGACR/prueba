/**
	\file ImageQualityFilter.h
*/
/**
	Defines the values for the quality filter.
	<p>The image quality filter is used as a configuration parameter for the instances of the {@link FPBExtractor} class and the pattern extraction processes.</p>
*/
typedef NS_ENUM(NSUInteger, FPBImageQualityFilter) {
    FPBImageQualityFilterOff = 0, /** Quality filter disabled. */
    
    FPBImageQualityFilterLow = 1, /** High tolerance for low quality images. */
    
    FPBImageQualityFilterMedium = 2, /** Medium tolerance for low quality images. */
    
    FPBImageQualityFilterHigh = 3 /** Very low tolerance for low quality images. */
};


