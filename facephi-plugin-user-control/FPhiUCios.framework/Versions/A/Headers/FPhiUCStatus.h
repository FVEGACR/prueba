#ifndef FPhiUCios_FPhiUCStatus_h
#define FPhiUCios_FPhiUCStatus_h
/** 
	\file FPhiUCStatus.h
*/
/**
	User control status.
*/
typedef NS_ENUM(NSUInteger, FPhiUCStatus)
{
	/**
		Nothing.
	*/
    UCNothing = 0,
	
	/**
		WaitingFace.
	*/
    UCWaitingFace = 1,
	
	/**
		Extracting.
	*/
    UCExtracting = 2,
	
	/**
		Finish.
	*/
    UCFinish = 3,
    
    /**
        LivenessDetectionProcess
        -- deprecated --
     */
    //UCLivenessDetection = 4,
    
    /**
        Last stage. Composing result and returning control to user.
     */
    //UCComposingResult = 5,
    
    /**
     WaitingFace 3 seconds
     */
    UCWaitingFaceStart = 6,
    
    /**
        Tip to user location
     */
    UCWizardInitialTip = 7,
    
    /**
        Tip to user position
     */
    UCWizardCycleTip = 8,
    
    /**
        User abort extraction process.
     */
    UCCancelByUser = 9,
    
    /**
     Show results before finish
     */
    UCShowResults = 10,
    
    /**
     Improve stage for registration wizard
     */
    UCImproveWizard = 110,

    /**
     Improve stage for registration wizard
     */
    UCImprove = 11,
    
    /**
     Wizard complete final stage for registration wizard
     */
    UCWizardCompleted = 12,
    
    /**
     Continuous mode
     */
    UCContinuousMode = 13,

    /**
     Liveness step 1
     */
    UCLivenessDetectionStep1 = 14,

    /**
     Liveness step 2
     */
    UCLivenessDetectionStep2 = 15,
    
    /**
     Liveness step 3
     */
    UCLivenessDetectionStep3 = 16,
    
    UCWaitingFacePrev = 17,
    
    UCImprovePrev = 18,
    
    UCFinishPrev = 19,
    
    UCCancelByUserPrev = 20,
    
    UCWaitingEyeDetection = 21,
    
    UCShowLivenessResults = 22,
    
    UCTimeout = 23
    
};

#endif
