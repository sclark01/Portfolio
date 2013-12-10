//
//  ShowViewController.h
//  meshub
//
//  Created by Shea Clark-Tieche on 11/18/13.
//  Copyright (c) 2013 Tufts. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ShowViewController : UITableViewController <UITableViewDataSource>

@property NSArray *mes_array;
@property NSMutableArray *contentArray;
@property NSMutableArray *usernameArray;
@property NSMutableArray *timeArray;

-(void)loadData;

@end
