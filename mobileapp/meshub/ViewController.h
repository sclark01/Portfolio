 //
//  ViewController.h
//  meshub
//
//  Created by Shea Clark-Tieche on 11/15/13.
//  Copyright (c) 2013 Tufts. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController<UITextFieldDelegate>

@property UIButton *send;
@property IBOutlet UITextField *username;
@property IBOutlet UITextField *message;
@property UIActivityIndicatorView *wheel;


-(IBAction)getClick:(id)sender;
-(UIActivityIndicatorView *)startWheel:(UIActivityIndicatorView *)w;
-(NSString *)getURL;

@end
