#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>

@interface FPhiUCCustomUI : NSObject

@property (nonatomic) UIColor *colorCancelButtonText;
@property (nonatomic) UIColor *colorCancelButtonTextDisabled;
@property (nonatomic) UIColor *colorCancelButtonBackground;
@property (nonatomic) UIColor *colorOkButtonText;
@property (nonatomic) UIColor *colorOkButtonTextDisabled;
@property (nonatomic) UIColor *colorOkButtonBackground;
@property (nonatomic) UIColor *colorDotDisabled;
@property (nonatomic) UIColor *colorDotEnabled;

@property (nonatomic) UIImage *imageCustomHeader;
@property (nonatomic) UIImage *imageCustomFooter;
@property (nonatomic) bool     imageInitialTipShow;

@property (nonatomic) int buttonHeight;
@property (nonatomic) UITextAutocapitalizationType buttonCapitalization;
@end
