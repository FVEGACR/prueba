/** 
	\file LivenessDiagnostic.h
*/
/**
	Represents the different states of liveness detection process.
*/
typedef NS_ENUM(NSUInteger, FPBLivenessDiagnostic) {
    FPBLivenessDiagnosticNotRated = 0, /** Not rated. */
    
    FPBLivenessDiagnosticPhotoDetected = 1, /** Photo detected. */
    
    FPBLivenessDiagnosticLivenessDetected = 2, /** Photography is not detected. */
	
	FPBLivenessDiagnosticUnsuccess = 3, /** Unsuccess. */
	
	FPBLivenessDiagnosticUnsuccessLowPerformance = 4, /** Unsuccess. */
	
	FPBLivenessDiagnosticUnsuccessGlasses = 5, /** Unsuccess. */
	
	FPBLivenessDiagnosticUnsuccessLight = 6, /** Unsuccess. */
};



