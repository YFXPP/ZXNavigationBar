//
//  ZXNavigationBarController.h
//  ZXNavigationBar
//
//  Created by 李兆祥 on 2020/3/7.
//  Copyright © 2020 ZXLee. All rights reserved.
//  https://github.com/SmileZXLee/ZXNavigationBar

#import <UIKit/UIKit.h>
#import "UINavigationController+ZXNavBarAllHiddenExtension.h"
#import "ZXNavigationBarController+ZXNavSystemBarPopHandle.h"
#import "ZXNavigationBar.h"
#import "ZXNavigationBarNavigationController.h"
NS_ASSUME_NONNULL_BEGIN
typedef enum {
    ZXNavStatusBarStyleDefault = 0x01,    // 状态栏颜色：黑色
    ZXNavStatusBarStyleLight = 0x02,    // 状态栏颜色：白色
}ZXNavStatusBarStyle;

typedef enum {
    ZXNavPopBlockFromBackButtonClick = 0x01,    // 点击返回按钮触发pop
    ZXNavPopBlockFromPopGesture = 0x02,    // 返回手势触发pop
}ZXNavPopBlockFrom;

typedef void(^leftBtnClickedBlock) (ZXNavItemBtn *btn);
typedef void(^rightBtnClickedBlock) (ZXNavItemBtn *btn);
typedef void(^subRightBtnClickedBlock) (ZXNavItemBtn *btn);
typedef void(^foldingOffsetBlock) (CGFloat offset);
typedef void(^foldCompletionBlock) (void);
@interface ZXNavigationBarController : UIViewController

/**
 设置左右Button的大小(宽高相等)
 */
@property (assign, nonatomic)CGFloat zx_navItemSize;

/**
 设置Item之间的间距
 */
@property (assign, nonatomic)CGFloat zx_navItemMargin;

/**
 状态栏颜色
 */
@property(assign, nonatomic)ZXNavStatusBarStyle zx_navStatusBarStyle;

/**
 是否隐藏ZXNavigationBar导航栏，默认为否
 */
@property (assign, nonatomic)BOOL zx_hideBaseNavBar;

/**
 是否显示系统导航栏，默认为否
 */
@property (assign, nonatomic)BOOL zx_showSystemNavBar;

/**
 是否开启系统导航栏与自定义导航栏平滑过渡(务必仅当存在系统导航栏与自定义导航栏过渡时启用，非必要请勿启用，否则可能造成自定义导航栏跳动，若当前控制器显示了系统导航栏，请于当前控制器pop的上一个控制器中使用self.zx_navEnableSmoothFromSystemNavBar = YES)
 */
@property (assign, nonatomic)BOOL zx_navEnableSmoothFromSystemNavBar;

/**
 是否禁止Xib加载控制器情况下自动将顶部View约束下移导航栏高度，默认为否(使用Xib加载控制器时生效)
 */
@property (assign, nonatomic)BOOL zx_disableNavAutoSafeLayout;

/**
 是否启用了SafeArea，默认为是，若取消了SafeArea，则必须将此项设置为NO(使用Xib加载控制器时生效)
 */
@property (assign, nonatomic)BOOL zx_isEnableSafeArea;

/**
 设置导航栏的TintColor，此属性可以将导航栏的title颜色、左右Button的文字和图片颜色修改为TintColor
 */
@property (strong, nonatomic, nullable)UIColor *zx_navTintColor;

/**
 设置导航栏标题，使用self.title亦可
 */
@property (copy, nonatomic)NSString *zx_navTitle;

/**
 titleView，显示在正中间的标题View，请不要在titleView直接添加自定义的titleView，如需设置自定义导航栏请使用-zx_addCustomTitleView方法
 */
@property (weak, nonatomic)ZXNavTitleView *zx_navTitleView;

/**
 titleLabel，显示在正中间的标题Label
 */
@property (weak, nonatomic)ZXNavTitleLabel *zx_navTitleLabel;

/**
 设置导航栏标题颜色
 */
@property (strong, nonatomic)UIColor *zx_navTitleColor;

/**
 设置导航栏标题字体大小
 */
@property (assign, nonatomic)CGFloat zx_navTitleFontSize;

/**
 设置导航栏标题字体
 */
@property (strong, nonatomic)UIFont *zx_navTitleFont;

/**
 导航栏分割线View
 */
@property (weak, nonatomic)UIView *zx_navLineView;

/**
 导航栏分割线View背景颜色
 */
@property (strong, nonatomic)UIColor *zx_navLineViewBackgroundColor;

/**
 左侧Button
 */
@property (weak, nonatomic)ZXNavItemBtn *zx_navLeftBtn;

/**
 最右侧Button
 */
@property (weak, nonatomic)ZXNavItemBtn *zx_navRightBtn;

/**
 右侧第二个Button
 */
@property (weak, nonatomic)ZXNavItemBtn *zx_navSubRightBtn;

/**
 ZXNavigationBar导航栏对象
 */
@property (weak, nonatomic)ZXNavigationBar *zx_navBar;

/**
 设置导航栏背景颜色
 */
@property (strong, nonatomic)UIColor *zx_navBarBackgroundColor;

/**
 导航栏背景ImageView
 */
@property (weak, nonatomic)ZXNavBacImageView *zx_navBacImageView;

/**
 设置导航栏背景图片
 */
@property (strong, nonatomic, nullable)UIImage *zx_navBarBackgroundImage;

/**
 自定义的导航栏View，是ZXNavigationBar的SubView，如需设置自定义导航栏请使用-zx_addCustomNavBar方法
 */
@property (weak, nonatomic)UIView *zx_navCustomNavBar;

/**
 自定义的titleView，是TitleView的SubView，如需设置自定义导航栏请使用-zx_addCustomTitleView方法
 */
@property (weak, nonatomic)UIView *zx_navCustomTitleView;

/**
 导航栏是否已被折叠，默认为否
 */
@property (assign, nonatomic, readonly)BOOL zx_navIsFolded;

/**
 导航栏折叠动画速度
 */
@property (assign, nonatomic, readonly)int zx_navFoldingSpeed;

/**
 是否禁用全屏pop手势，若禁用，则pop触发范围为屏幕宽度的五分之一(导航控制器需为ZXNavigationBarNavigationController或继承于ZXNavigationBarNavigationController)
 */
@property (assign, nonatomic)BOOL zx_disableFullScreenGesture;


/**
 pop手势的触发范围比例，0-1，默认为1，即代表全屏触发(导航控制器需为ZXNavigationBarNavigationController或继承于ZXNavigationBarNavigationController)
 */
@property (assign, nonatomic) CGFloat zx_popGestureCoverRatio;


/**
 自动将顶部View约束下移导航栏高度时的回调，可拦截并自定义下移距离(xib加载控制器view时生效)
 oldNavOffset:视图在xib中所设置的约束与顶部距离
 currentNavOffset:即将设置的视图与顶部的距离
 */
@property(nonatomic,copy)CGFloat(^zx_handleAdjustNavContainerOffsetBlock)(CGFloat oldNavOffset,CGFloat currentNavOffset);

/**
 拦截点击返回事件和侧滑返回手势，若返回NO，则禁止pop;
 viewController:当前控制器
 popBlockFrom:通过什么方式(点击返回按钮或侧滑返回手势)触发pop操作
 */
@property(nonatomic,copy)BOOL(^zx_handlePopBlock)(ZXNavigationBarController *viewController,ZXNavPopBlockFrom popBlockFrom);

/**
 监听自定义pop手势进度(导航控制器需为ZXNavigationBarNavigationController或继承于ZXNavigationBarNavigationController)。popOffsetProgress范围为0-1，0代表即将开始pop，1代表完成pop
 */
@property(nonatomic,copy)void(^zx_handleCustomPopGesture)(CGFloat popOffsetProgress);

/**
 导航栏固定高度
 */
@property (assign, nonatomic)int zx_navFixHeight;
/**
 设置左侧Button的图片和点击回调
 
 @param imgName 图片名字
 @param clickBlock 点击回调
 */
- (void)zx_setLeftBtnWithImgName:(NSString *)imgName clickedBlock:(nullable leftBtnClickedBlock)clickBlock;


/**
 设置最右侧Button的图片和点击回调
 
 @param imgName 图片名字
 @param clickBlock 点击回调
 */
- (void)zx_setRightBtnWithImgName:(NSString *)imgName clickedBlock:(nullable rightBtnClickedBlock)clickBlock;

/**
 设置右侧第二个Button的图片和点击回调(此按钮您支持设置图片)
 
 @param imgName 图片名字
 @param clickBlock 点击回调
 */
- (void)zx_setSubRightBtnWithImgName:(NSString *)imgName clickedBlock:(nullable subRightBtnClickedBlock)clickBlock;


/**
 设置左侧Button的文字和点击回调
 
 @param btnText 按钮文字
 @param clickBlock 点击回调
 */
- (void)zx_setLeftBtnWithText:(NSString *)btnText clickedBlock:(nullable leftBtnClickedBlock)clickBlock;

/**
 设置最右侧Button的文字和点击回调
 
 @param btnText 按钮文字
 @param clickBlock 点击回调
 */
- (void)zx_setRightBtnWithText:(NSString *)btnText clickedBlock:(nullable rightBtnClickedBlock)clickBlock;

/**
 设置左侧Button的图片Url和点击回调
 
 @param imgUrlStr 图片Url
 @param placeholderImgName 占位图名称
 @param clickBlock 点击回调
 */
- (void)zx_setLeftBtnWithImgUrl:(NSString *)imgUrlStr placeholderImgName:(NSString *)placeholderImgName clickedBlock:(nullable leftBtnClickedBlock)clickBlock;

/**
 设置最右侧Button的图片Url和点击回调
 
 @param imgUrlStr 图片Url
 @param placeholderImgName 占位图名称
 @param clickBlock 点击回调
 */
- (void)zx_setRightBtnWithImgUrl:(NSString *)imgUrlStr placeholderImgName:(NSString *)placeholderImgName clickedBlock:(nullable rightBtnClickedBlock)clickBlock;

/**
 设置右侧第二个Button的图片Url和点击回调
 
 @param imgUrlStr 图片Url
 @param placeholderImgName 占位图名称
 @param clickBlock 点击回调
 */
- (void)zx_setSubRightBtnWithImgUrl:(NSString *)imgUrlStr placeholderImgName:(NSString *)placeholderImgName clickedBlock:(nullable leftBtnClickedBlock)clickBlock;


/**
 设置左侧按钮图片和点击回调
 
 @param img 图片
 @param clickBlock 点击回调
 */
- (void)zx_setLeftBtnWithImg:(UIImage *)img clickedBlock:(nullable leftBtnClickedBlock)clickBlock;

/**
 设置右侧按钮图片和点击回调
 
 @param img 图片
 @param clickBlock 点击回调
 */
- (void)zx_setRightBtnWithImg:(UIImage *)img clickedBlock:(nullable leftBtnClickedBlock)clickBlock;

/**
 设置右侧按钮图片和点击回调
 
 @param img 图片
 @param clickBlock 点击回调
 */
- (void)zx_setSubRightBtnWithImg:(UIImage *)img clickedBlock:(nullable leftBtnClickedBlock)clickBlock;

/**
 左侧Button的点击回调
 
 @param clickBlock 点击回调
 */
- (void)zx_leftClickedBlock:(leftBtnClickedBlock)clickBlock;

/**
 最右侧Button的点击回调
 
 @param clickBlock 点击回调
 */
- (void)zx_rightClickedBlock:(rightBtnClickedBlock)clickBlock;

/**
 右侧第二个Button的点击回调
 
 @param clickBlock 点击回调
 */
- (void)zx_subRightClickedBlock:(subRightBtnClickedBlock)clickBlock;

/**
 添加自定义导航栏
 
 @param navBar 自定义导航栏View
 */
- (void)zx_addCustomNavBar:(UIView *)navBar;

/**
 设置大小标题效果
 
 @param title 大标题
 @param subTitle 小标题
 */
- (void)zx_setMultiTitle:(NSString *)title subTitle:(NSString *)subTitle;

/**
 设置大小标题效果
 
 @param title 大标题
 @param subTitle 小标题
 @param subTitleFont 小标题字体
 @param subTitleColor 小标题颜色
 */
- (void)zx_setMultiTitle:(NSString *)title subTitle:(NSString *)subTitle subTitleFont:(UIFont *)subTitleFont subTitleTextColor:(UIColor *)subTitleColor;

/**
 设置导航栏背景渐变(颜色渐变从fromColor到toColor)
 
 @param fromColor 起止颜色
 @param toColor 终止颜色
 */
- (void)zx_setNavGradientBacFrom:(UIColor *)fromColor to:(UIColor *)toColor;

/**
 移除导航栏渐变背景
 */
- (void)zx_removeNavGradientBac;

/**
 添加自定义的TitleView
 
 @param customTitleView 自定义的TitleView
 */
- (void)zx_addCustomTitleView:(UIView *)customTitleView;


/**
 设置可伸缩折叠式导航栏
 
 @param folded 是否折叠，为否时即为展开
 @param speed 折叠效果动画速度，1-6，建议3
 @param offsetBlock 折叠动画导航栏位移回调，当控制器使用frame布局时，用于在导航栏高度更改时，同时设置导航栏下方视图的frame，此时获取到的offset就是导航栏实时相较自身位移距离
 @param completionBlock 折叠动画结束回调
 */
- (void)zx_setNavFolded:(BOOL)folded speed:(int)speed foldingOffsetBlock:(nullable foldingOffsetBlock)offsetBlock foldCompletionBlock:(nullable foldCompletionBlock)completionBlock;

@end

NS_ASSUME_NONNULL_END
