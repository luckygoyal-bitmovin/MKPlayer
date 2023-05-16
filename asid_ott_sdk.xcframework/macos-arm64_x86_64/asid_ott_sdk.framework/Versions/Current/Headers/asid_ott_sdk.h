#ifndef ASiDOTTSDK_h
#define ASiDOTTSDK_h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#define ASiDView UIView
#else
#import <AppKit/AppKit.h>
#define ASiDView NSView
#endif

@interface ASiDConfig : NSObject {}
@property (nonatomic) NSString* initialisationToken;
@property (nonatomic) NSString* validationKey;
@property (nonatomic) int naturalVideoHeight;
@property (nonatomic) int naturalVideoWidth;
@property (nonatomic) NSString* appName;
@property (nonatomic) NSString* appVersion;
@property (nonatomic) NSString* appIdentifier;
@property (nonatomic) NSString* assetTitle;
@property (nonatomic) int failureRecallFrequency;
@end

typedef NS_ENUM(NSInteger, ASiDSecurityIssue) {
    ASiDSecurityIssueNoIssue = 0,
    ASiDSecurityIssueImageHashInvalid = 1,
    ASiDSecurityIssueSignatureInvalid = 2,
    ASiDSecurityIssueTimestampInvalid = 3,
    ASiDSecurityIssueTimeout = 4,
    ASiDSecurityIssueCouldNotConnect = 5,
    ASiDSecurityIssueTerminateRequested = 6,
    ASiDSecurityIssueInvalidRequest = 7,
    ASiDSecurityIssueInvalidResponse = 8,
    ASiDSecurityIssueUnexpectedResponse = 9,
    ASiDSecurityIssueInvalidToken = 10
};

typedef NSString* (^ASiDDecryptionHandler)(NSString* initToken);
typedef CGSize (^ASiDVideoSizeCallback)();
typedef void (^ASiDTamperCallback)(int lastIssueType);
typedef void (^ASiDTerminateCallback)();
typedef void (^ASiDSecurityCallback)(int numIssues, int lastKnownIssue);
typedef void (^ASiDOverlayCallback)(bool show, int scheduleId, const unsigned char *imageData, long imageDataLength, float visibilityRatio);

@interface ASiDController : NSObject {}
@property (nonatomic, weak) ASiDView* view;
@property (nonatomic) ASiDOverlayCallback overlayDisplayHandler;
- (void)start;
- (void)terminateExistingSession;
- (void)setConfig:(ASiDConfig*)config;
- (void)setPlaybackPosition:(long)offset;
- (void)setDecryptionHandler:(ASiDDecryptionHandler)handler;
- (void)setVideoSizeCallback:(ASiDVideoSizeCallback)callback;
- (void)setTamperCallback:(ASiDTamperCallback)callback;
- (void)setTerminateCallback:(ASiDTerminateCallback)callback;
- (void)setSecurityCallback:(ASiDSecurityCallback)callback;
- (void)setOverlayCallback:(ASiDOverlayCallback)callback;
@end

#endif /* ASiDOTTSDK_h */
