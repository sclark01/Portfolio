//
//  ViewController.m
//  meshub
//
//  Created by Shea Clark-Tieche on 11/15/13.
//  Copyright (c) 2013 Tufts. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize message, username, send, wheel;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*Function called on click */
-(IBAction)getClick:(id)sender
{
    NSString *urlAsString;
    wheel = [self startWheel:wheel];
    urlAsString = [self getURL];
    
    
    NSURL *url  = [NSURL URLWithString:urlAsString];
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:url];

    [req setHTTPMethod:@"POST"];
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    [NSURLConnection sendAsynchronousRequest:req queue:queue completionHandler:^(NSURLResponse *response, NSData *respdata, NSError *connError) {
            UIAlertView *result;
            if(connError == nil) {
                result = [[UIAlertView alloc] initWithTitle:@"Success" message:@"Thanks! Your message has been sent" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
                [result show];
                [wheel stopAnimating];
            } else {
                result = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Sorry, Something went wrong. Try again later" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
                [result show];
                [wheel stopAnimating];
            }
    }];

    message.text = @"";
    username.text = @"";
    
}

    
-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{

}

//Create progress wheel for HTTP POST request
- (UIActivityIndicatorView *)startWheel:(UIActivityIndicatorView *)w
{
    w = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    w.frame = CGRectMake(140.0, 350.0, 40.0, 40.0);
    [self.view addSubview: w];
    [w startAnimating];
    self.username.delegate = self;
    
    return w;
}

//builds URL
- (NSString *)getURL
{
    NSString  *url, *name, *content;
    
    url = @"http://messagehub.herokuapp.com/messages.json?message[username]=";
    
    name = [username.text stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    content = [message.text stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    url= [NSString stringWithFormat:@"%@%@%@%@%@", url, name, @"&message[content]=",content,@"&message[app_id]=1"];

    return url;
}


@end
