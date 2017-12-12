//
//  KKGameViewController.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <KKGame/KKGameView.h>

@class KKGameApplication;

@interface KKGameViewController : UIViewController

@property(nonatomic,strong) KKGameApplication * app;
@property(nonatomic,strong) NSString * path;
@property(nonatomic,assign,readonly) kk::Document * document;
@property(nonatomic,strong) IBOutlet KKGameView * gameView;

@end
