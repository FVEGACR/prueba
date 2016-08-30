#ifndef FPhiUCios_ExtractionMode_h
#define FPhiUCios_ExtractionMode_h

/** 
	\file ExtractionMode.h
*/
/**
	Extraction mode.
*/
typedef NS_ENUM(NSUInteger, ExtractionMode) {

	/**
		Authenticate.
	*/
    EMAuthenticate = 2,
    
    /**
     Registry wizard
     */
    EMWizardRegister = 12,
    
    /**
     Liveness wizard
     */
    EMWizardLiveness = 14,
    
    /**
     Continuous mode
     */
    EMContinuousMode = 16
};

#endif
