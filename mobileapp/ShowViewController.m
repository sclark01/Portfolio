//
//  ShowViewController.m
//  meshub
//
//  Created by Shea Clark-Tieche on 11/18/13.
//  Copyright (c) 2013 Tufts. All rights reserved.
//

#import "ShowViewController.h"

@interface ShowViewController ()

@end

@implementation ShowViewController

@synthesize mes_array, contentArray, usernameArray, timeArray;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    UIRefreshControl *refresh = [[UIRefreshControl alloc]init];
    refresh.attributedTitle = [[NSAttributedString alloc] initWithString:@"Pull to Refresh"];
    [refresh addTarget:self action:@selector(reload_data) forControlEvents:UIControlEventValueChanged];
    self.refreshControl = refresh;

    [self.tableView setContentInset:UIEdgeInsetsMake(20,
                                                     self.tableView.contentInset.left,
                                                     self.tableView.contentInset.bottom,
                                                     self.tableView.contentInset.bottom)];
}

-(void)stopRefresh
{
    [self.refreshControl endRefreshing];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

}

-(void)reload_data
{
    [self.tableView reloadData];
    [self performSelector:@selector(stopRefresh) withObject:nil afterDelay:2.5];
    
}

- (void)loadData
{
    NSURL *url = [[NSURL alloc] initWithString:@"http://messagehub.herokuapp.com/messages.json"];
    NSData *data = [[NSData alloc] initWithContentsOfURL:url];
    id json = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
    mes_array = (NSArray *)json;

    NSEnumerator *iter = [mes_array reverseObjectEnumerator];
    NSDictionary *content;
    contentArray = [[NSMutableArray alloc] init];
    usernameArray = [[NSMutableArray alloc]init];
    timeArray = [[NSMutableArray alloc] init];
    while (content = [iter nextObject]){
        [contentArray addObject:[content objectForKey:@"content"]];
        [usernameArray addObject:[content objectForKey:@"username"]];
        [timeArray addObject:[content objectForKey:@"created_at"]];
    }
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    [self loadData];
    return [mes_array count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    cell.textLabel.text = [contentArray objectAtIndex:indexPath.row];
    NSString *user = [NSString stringWithFormat:@"%@%@%@%@", @"Created by ", [usernameArray objectAtIndex:indexPath.row], @", at ", [timeArray objectAtIndex:indexPath.row]];
    cell.detailTextLabel.text = user;
    self.tableView.bounces = YES;
    return cell;
}

@end
