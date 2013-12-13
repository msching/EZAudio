//
//  EZPlot.h
//  EZAudioExampleiOS
//
//  Created by Syed Haris Ali on 11/24/13.
//  Copyright (c) 2013 Syed Haris Ali. All rights reserved.
//

/**
 `EZPlot` is a cross-platform (iOS and OSX) class used to subclass the default view type (either UIView or NSView, respectively).
 
 ## Subclassing Notes
 
 This class isn't meant to be directly used in practice, but instead establishes the default properties and behaviors subclasses should obey to provide consistent behavior accross multiple types of graphs (i.e. set background color, plot type, should fill in, etc.). Subclasses should make use of the inherited properties from this class to allow all child plots to benefit from the same 
 */
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
@interface EZPlot : UIView
#elif TARGET_OS_MAC
#import <Cocoa/Cocoa.h>
@interface EZPlot : NSView
#endif

#pragma mark - Enumerations
///-----------------------------------------------------------
/// @name Plot Types
///-----------------------------------------------------------
/**
 *  The types of plots that can be displayed in the view using the data.
 */
typedef NS_ENUM(NSInteger,EZPlotType){
  EZPlotTypeBuffer,  /**< Plot that plots only the samples of the current buffer */
  EZPlotTypeRolling  /**< Plot that displays a rolling history of values using the RMS calculated for each incoming buffer */
};

#pragma mark - Properties
///-----------------------------------------------------------
/// @name Customizing The Plot's Appearance
///-----------------------------------------------------------
/**
 The default background color of the plot. For iOS the color is specified as a UIColor while for OSX the color is an NSColor. The default value on both platforms is black.
 */
#if TARGET_OS_IPHONE
@property (nonatomic,strong) UIColor *backgroundColor;
#elif TARGET_OS_MAC
@property (nonatomic,strong) NSColor *backgroundColor;
#endif

/**
 The default color of the plot's data (i.e. waveform, y-axis values). For iOS the color is specified as a UIColor while for OSX the color is an NSColor. The default value on both platforms is red.
 */
#if TARGET_OS_IPHONE
@property (nonatomic,strong) UIColor *color;
#elif TARGET_OS_MAC
@property (nonatomic,strong) NSColor *color;
#endif

/**
 The plot's gain value, which controls the scale of the y-axis values. The default value of the gain is 1.0f and should always be greater than 0.0f.
 */
@property (nonatomic,assign,setter=setGain:) float gain;

/**
 The type of plot as specified by the `EZPlotType` enumeration (i.e. a buffer or rolling plot type).
 */
@property (nonatomic,assign,setter=setPlotType:) EZPlotType plotType;

/**
 A boolean indicating whether or not to fill in the graph. A value of YES will make a filled graph (filling in the space between the x-axis and the y-value), while a value of NO will create a stroked graph (connecting the points along the y-axis).
 */
@property (nonatomic,assign,setter=setShouldFill:) BOOL shouldFill;

/**
 A boolean indicating whether the graph should be rotated along the x-axis to give a mirrored reflection. This is typical for audio plots to produce the classic waveform look. A value of YES will produce a mirrored reflection of the y-values about the x-axis, while a value of NO will only plot the y-values.
 */
@property (nonatomic,assign,setter=setShouldMirror:) BOOL shouldMirror;

#pragma mark - Get Samples
///-----------------------------------------------------------
/// @name Updating The Plot
///-----------------------------------------------------------
/**
 Updates the plot with the new buffer data and tells the view to redraw itself. Caller will provide a float array with the values they expect to see on the y-axis. The plot will internally handle mapping the x-axis and y-axis to the current view port, any interpolation for fills effects, and mirroring.
 @param buffer     A float array of values to map to the y-axis.
 @param bufferSize The size of the float array that will be mapped to the y-axis.
 @warning The bufferSize is expected to be the same, constant value once initial triggered. For plots using OpenGL a vertex buffer object will be allocated with a maximum buffersize of (2 * the initial given buffer size) to account for any interpolation necessary for filling in the graph. Updates use the glBufferSubData(...) function, which will crash if the buffersize exceeds the initial maximum allocated size.
 */
-(void)updateBuffer:(float *)buffer
     withBufferSize:(UInt32)bufferSize;

@end
