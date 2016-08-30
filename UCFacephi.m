/********* UCFacephi.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>
#import <FPhiUCios/FPhiUCios.h>

@interface UCFacephi : CDVPlugin<FPhiUCProtocol> {
}

@property (nonatomic) FPhiUC *uc;
@property (nonatomic) bool enableImages;
@property (nonatomic) NSString *lastCallbackId;

- (void)StartUserControl:(CDVInvokedUrlCommand*)command;
+ (NSString*)base64forData:(NSData*)theData;

@end

@implementation UCFacephi

- (void)StartUserControl:(CDVInvokedUrlCommand*)command
{
    NSLog(@"StartUserControl method fired.");

    self.uc = [[FPhiUC alloc]init :true :self];
    self.enableImages=false;

    CDVPluginResult* pluginResult = nil;
    NSDictionary* arguments = [command.arguments objectAtIndex:0];
    NSString *mode = [arguments objectForKey:@"mode"];
    NSDictionary *config = [arguments objectForKey:@"config"];
    if (config != nil) {
        
        NSObject *debug = [config objectForKey:@"debug"];
        if (debug != nil)
            self.uc.debugMode = ((NSNumber *)debug).boolValue;
        
        NSObject *crop = [config objectForKey:@"crop"];
        if (crop != nil)
            self.uc.cropImagesToFace = ((NSNumber *)crop).boolValue;
        
        NSObject *cropRatio = [config objectForKey:@"cropRatio"];
        if (cropRatio != nil)
            self.uc.cropRatio = ((NSNumber *)cropRatio).floatValue;
        
        NSObject *sceneTimeout = [config objectForKey:@"sceneTimeout"];
        if (sceneTimeout != nil)
            self.uc.sceneTimeout = ((NSNumber *)sceneTimeout).floatValue;
        
        NSObject *enableImages = [config objectForKey:@"enableImages"];
        if (enableImages != nil)
            self.enableImages = enableImages;
    }
    
    
    if ([mode compare:@"Authenticate"] == NSOrderedSame) {
        self.uc.extractionMode = EMAuthenticate;
    } else if ([mode compare:@"WizardRegister"] == NSOrderedSame) {
        self.uc.extractionMode = EMWizardRegister;
    } else if ([mode compare:@"WizardLiveness"] == NSOrderedSame) {
        self.uc.extractionMode = EMWizardLiveness;
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    }
    
    self.lastCallbackId = command.callbackId;
    [self.uc StartExtraction];
    [self.viewController presentViewController:self.uc animated:true completion:nil];
}

// protocol implementation
-(void) ExtractionFinished {
    
    NSLog(@"StartUserControl finished");

    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[NSNumber numberWithInt:1] forKey:@"finishStatus"];
    [dict setObject:[NSNumber numberWithInt:2] forKey:@"errorType"];
    [dict setObject:[NSNumber numberWithInt:(int)self.uc.livenessDiagnostic+1] forKey:@"livenessDiagnostic"];
    NSData *template = [self.uc.results.result getTemplate];
    [dict setObject:[UCFacephi base64forData:template] forKey:@"template"];
    
    NSMutableArray *images = [NSMutableArray array];
    if (self.enableImages) {
        if (self.uc.results.images != nil) {
            for (int a=0; a<self.uc.results.images.count; a++) {
                FPhiUCExtractionRecord *record = [self.uc.results.images objectAtIndex:a];
                NSData *data = UIImageJPEGRepresentation(record.image, 0.5f);
                NSString *base64String = [UCFacephi base64forData:data];
                base64String = [NSString stringWithFormat:@"data:image/jpg;base64,%@",base64String];
                [images addObject:base64String];
            }
        }
    }
    [dict setObject:images forKey:@"images"];
    
    self.uc = nil;
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.lastCallbackId];
}

-(void) ExtractionFailed:(NSError *)error {
    NSLog(@"StartUserControl failed");

    self.uc = nil;
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.lastCallbackId];
}

-(void)ExtractionCancelled {
    
    NSLog(@"StartUserControl cancelled");

    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[NSNumber numberWithInt:3] forKey:@"finishStatus"];
    [dict setObject:[NSNumber numberWithInt:2] forKey:@"errorType"];
    [dict setObject:[NSNumber numberWithInt:1] forKey:@"livenessDiagnostic"];
    
    self.uc = nil;
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.lastCallbackId];
}

-(void)ExtractionTimeout {
    
    NSLog(@"StartUserControl timeout");

    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[NSNumber numberWithInt:4] forKey:@"finishStatus"];
    [dict setObject:[NSNumber numberWithInt:2] forKey:@"errorType"];
    [dict setObject:[NSNumber numberWithInt:1] forKey:@"livenessDiagnostic"];
    
    self.uc = nil;
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.lastCallbackId];
}

+ (NSString*)base64forData:(NSData*)theData {
    const uint8_t* input = (const uint8_t*)[theData bytes];
    NSInteger length = [theData length];
    
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData* data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t* output = (uint8_t*)data.mutableBytes;
    
    NSInteger i;
    for (i=0; i < length; i += 3) {
        NSInteger value = 0;
        NSInteger j;
        for (j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger theIndex = (i / 3) * 4;
        output[theIndex + 0] =                    table[(value >> 18) & 0x3F];
        output[theIndex + 1] =                    table[(value >> 12) & 0x3F];
        output[theIndex + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[theIndex + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
}

@end