/**
	\file SampleDiagnostic.h
*/
/**
	Defines the possible values which can be obtained as a result of the facial features detection process.
*/
typedef NS_ENUM(NSUInteger, FPBSampleDiagnostic) {
	FPBSampleDiagnosticOk = 0, /** Correct detection. Valid sample for extraction.*/
	
    FPBSampleDiagnosticFaceNotFound = 1, /** Face not found. */
	
    FPBSampleDiagnosticRightEyeNotFound = 2, /** Right eye not found. */
	
    FPBSampleDiagnosticLeftEyeNotFound = 3, /** Left eye not found. */
	
	FPBSampleDiagnosticEyesNotFound = 4, /** Eyes not found. */
	
    FPBSampleDiagnosticFaceTooFar = 5, /** Face too far. */
	
    FPBSampleDiagnosticFaceTooClose = 6, /** Face too close. */
	
    FPBSampleDiagnosticTooCloseToWindowSide = 7, /** Face too close to window side. */
	
    FPBSampleDiagnosticAngleExceeded = 8, /** Face rotation angle exceeded. */
	
    FPBSampleDiagnosticQualityCheckFailed = 9, /** Quality check failed. */
	
    FPBSampleDiagnosticNotRated = 10 /** Not rated. */
};


