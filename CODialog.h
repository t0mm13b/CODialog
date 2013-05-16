//
//  CODialog.h
//  CODialog
//
//  Created by Erik Aigner on 10.04.12.
//  Copyright (c) 2012 chocomoko.com. All rights reserved.
//
// Modified by t0mm13b, 15th May, 2013.

#import <UIKit/UIKit.h>

@protocol CODialogFieldDelegate <NSObject>
@required

@optional
-(void) cbEnterFocus: (UITextField*) ptrUITextField;
-(void) cbLeaveFocus: (UITextField*) ptrUITextField;
@end

@protocol CODialogDelegate <NSObject>
@required

@optional
-(void) cbDialogIsShowing:(id)sender;
-(void) cbDialogIsHidden:(id)sender;
@end

enum {
  CODialogStyleDefault = 0,
  CODialogStyleIndeterminate,
  CODialogStyleDeterminate,
  CODialogStyleSuccess,
  CODialogStyleError,
  CODialogStyleCustomView
};
typedef NSInteger CODialogStyle;

@interface CODialog : UIView
#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_5_0)
@property (nonatomic, strong) UIView *customView;
#else
@property (nonatomic, retain) UIView *customView;
#endif
@property (nonatomic, assign) CODialogStyle dialogStyle;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subtitle;
@property (nonatomic, assign) CGFloat progress;
@property (nonatomic, assign) NSTimeInterval batchDelay;

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_5_0)
+ (instancetype)dialogWithWindow:(UIWindow *)hostWindow;
#else
+ (id)dialogWithWindow:(UIWindow *)hostWindow;
#endif

- (id)initWithWindow:(UIWindow *)hostWindow;
- (CGRect)defaultDialogFrame;

/** @name Configuration */

- (void)resetLayout;
- (void)removeAllControls;
- (void)removeAllTextFields;
- (void)removeAllButtons;

- (void)addTextFieldWithPlaceholder:(NSString *)placeholder 
						 secureFlag:(BOOL)isSecure 
					autoCorrectFlag:(BOOL)isAutoCorrect 
			 targetDelegateCallback:(id<CODialogFieldDelegate>)targetCallback;
- (void)addButtonWithTitle:(NSString *)title target:(id)target selector:(SEL)sel;
- (void)addButtonWithTitle:(NSString *)title target:(id)target selector:(SEL)sel highlighted:(BOOL)flag;

/** @name Getting Values */

- (NSString *)textForTextFieldAtIndex:(NSUInteger)index;

/** @name Showing, Updating and Hiding */

- (void)showOrUpdateAnimated:(BOOL)flag;
- (void)showOrUpdateAnimated:(BOOL)flag targetDelegateCallback:(id<CODialogDelegate>)targetCallback;

- (void)hideAnimated:(BOOL)flag;
- (void)hideAnimated:(BOOL)flag targetDelegateCallback:(id<CODialogDelegate>)targetCallback;
- (void)hideAnimated:(BOOL)flag afterDelay:(NSTimeInterval)delay;

/** @name Methods to Override */

- (void)drawRect:(CGRect)rect;
- (void)drawDialogBackgroundInRect:(CGRect)rect;
- (void)drawButtonInRect:(CGRect)rect title:(NSString *)title highlighted:(BOOL)highlighted down:(BOOL)down;
- (void)drawTitleInRect:(CGRect)rect isSubtitle:(BOOL)isSubtitle;
- (void)drawSymbolInRect:(CGRect)rect;
- (void)drawTextFieldInRect:(CGRect)rect;
- (void)drawDimmedBackgroundInRect:(CGRect)rect;

#if (__IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_5_0)
/* Only works in older XCode < 4.2, 3.2.5 IIRC */
struct {
    CGRect titleRect;
    CGRect subtitleRect;
    CGRect accessoryRect;
    CGRect textFieldsRect;
    CGRect buttonRect;
} layout;
#endif
@end
