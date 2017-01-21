/*
 * Copyright (c) 2011-2013, Xuzz Productions, LLC
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "iPhonePrivate.h"

@interface ZephyrBaseGesture : NSObject {
    NSMutableArray *gestureRecognizers;
    BOOL isActive;
}

@property (nonatomic, readonly) BOOL isActive;
@property (nonatomic, readonly) NSMutableArray *gestureRecognizers;

- (void)addOffscreenEdge:(SBOffscreenEdge)edge minimumTouchCount:(int)count edgeMargin:(CGFloat)edgeMargin;
- (BOOL)currentOrientationIsSupported;

- (BOOL)shouldActivateAtEdge:(SBOffscreenEdge)edge;
- (BOOL)shouldActivateAtEdge:(SBOffscreenEdge)edge atPoint:(CGPoint)point; // only if shouldActivateAtEdge: too.
- (BOOL)shouldUseGrabberAtEdge:(SBOffscreenEdge)edge;

- (void)handleGestureBegan:(SBGestureRecognizer *)recognizer withLocation:(CGFloat)location;
- (void)handleGestureChanged:(SBGestureRecognizer *)recognizer withLocation:(CGFloat)location velocity:(CGPoint)velocity;
- (void)handleGestureEnded:(SBGestureRecognizer *)recognizer withLocation:(CGFloat)location velocity:(CGPoint)velocity completionType:(int)type;
- (void)handleGestureCanceled:(SBGestureRecognizer *)recognizer;
- (void)cancelGesture;

@end

