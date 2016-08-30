/** 
	\file FinalDiagnostic.h
*/
/**
	Represents the different states of a facial template generation process.
*/
typedef NS_ENUM(NSUInteger, FPBFinalDiagnostic) {
    FPBFinalDiagnosticInsufficientValidSamples = 0, /** Template not created. Unable to extract a minimum number of patterns. */
    
    FPBFinalDiagnosticTemplateCreationInProgress = 1, /** Template creation in progress. */
    
    FPBFinalDiagnosticTemplateCreated = 2 /** Template created. */
};


