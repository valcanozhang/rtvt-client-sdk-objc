//
//  RTVTClient.h
//  RTVT
//
//  Created by zsl on 2019/12/11.
//  Copyright © 2019 FunPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RTVT/RTVTProtocol.h>
#import <RTVT/RTVTCallBackDefinition.h>
#import <RTVT/RTVTClientConfig.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RTVTClientConnectStatus){
    
    RTVTClientConnectStatusConnectClosed = 0,
    RTVTClientConnectStatusConnecting = 1,
    RTVTClientConnectStatusConnected = 2,
    
};

typedef void (^RTVTLoginSuccessCallBack)(void);
typedef void (^RTVTLoginFailCallBack)(FPNError * _Nullable error);

typedef void (^RTVTAnswerSuccessCallBack)(void);
typedef void (^RTVTAnswerFailCallBack)(FPNError * _Nullable error);

@interface RTVTClient : NSObject

+(NSString*)getSdkVersion;

+ (nullable instancetype)clientWithEndpoint:(nonnull NSString * )endpoint
                                  projectId:(int64_t)projectId
                                   delegate:(id <RTVTProtocol>)delegate;


- (void)loginWithToken:(nonnull NSString *)token
                    ts:(int64_t)ts//生成token对应的时间
               success:(RTVTLoginSuccessCallBack)loginSuccess
           connectFail:(RTVTLoginFailCallBack)loginFail;


@property (nonatomic,readonly,strong)NSString * sdkVersion;
@property (nonatomic,readonly,assign)RTVTClientConnectStatus currentConnectStatus;
@property (nonatomic,assign,nullable)id <RTVTProtocol> delegate;
@property (nonatomic,readonly,assign)int64_t projectId;



/// 开始翻译 获取streamId  (翻译为多种语言)
/// @param asrResult 是否需要语音识别的结果
/// @param tempResult 是否需要临时结果(临时识别和临时翻译)
/// @param userId 用户标识
/// @param srcLanguage 源语言
/// @param srcAltLanguage 备选语言
/// @param successCallback 成功回调
/// @param failCallback 失败回调
-(void)multi_starTranslateWithAsrResult:(BOOL)asrResult
                             tempResult:(BOOL)tempResult
                                 userId:(NSString * _Nullable)userId
                            srcLanguage:(nonnull NSString *)srcLanguage
                         srcAltLanguage:(NSArray <NSString*> * _Nullable) srcAltLanguage
                                success:(void(^)(int64_t streamId))successCallback
                                   fail:(RTVTAnswerFailCallBack)failCallback;


/// 发送音频数据  要求 : pcm 16k 16bit 单声道 每次640byte 20ms  (翻译为多种语言)
/// @param streamId 流id
/// @param voiceData 音频数据
/// @destLanguages 目标语言
/// @param seq 自增seq 必传
/// @param ts 音频帧对应时间戳  毫秒 必传
/// @param successCallback 成功回调
/// @param failCallback 失败回调
-(void)multi_sendVoiceWithStreamId:(int64_t)streamId
                         voiceData:(nonnull NSData*)voiceData
                     destLanguages:(NSArray<NSString*>*)destLanguages
                               seq:(int64_t)seq
                                ts:(int64_t)ts
                           success:(RTVTAnswerSuccessCallBack)successCallback
                              fail:(RTVTAnswerFailCallBack)failCallback;



/// 开始翻译 获取streamId  (翻译为一种语言)
/// @param asrResult 是否需要语音识别的结果
/// @param transResult 是否需要语音翻译的结果
/// @param tempResult 是否需要临时结果(临时识别和临时翻译)
/// @param ttsResult 是否需要返回翻译结果音频文件(mp3)
/// @param userId 用户标识
/// @param srcLanguage 源语言
/// @param destLanguage 目标语言
/// @param srcAltLanguage 备选语言
/// @param successCallback 成功回调
/// @param failCallback 失败回调
-(void)starStreamTranslateWithAsrResult:(BOOL)asrResult
                            transResult:(BOOL)transResult
                             tempResult:(BOOL)tempResult
                              ttsResult:(BOOL)ttsResult
                                 userId:(NSString * _Nullable)userId
                            srcLanguage:(nonnull NSString *)srcLanguage
                           destLanguage:(nonnull NSString *)destLanguage
                         srcAltLanguage:(NSArray <NSString*> * _Nullable) srcAltLanguage
                                success:(void(^)(int64_t streamId))successCallback
                                   fail:(RTVTAnswerFailCallBack)failCallback;


/// 发送音频数据  要求 : pcm 16k 16bit 单声道 每次640byte 20ms  (翻译为一种语言)
/// @param streamId 流id
/// @param voiceData 音频数据
/// @param seq 自增seq 必传
/// @param ts 音频帧对应时间戳  毫秒 必传
/// @param successCallback 成功回调
/// @param failCallback 失败回调
-(void)sendVoiceWithStreamId:(int64_t)streamId
                   voiceData:(nonnull NSData*)voiceData
                         seq:(int64_t)seq
                          ts:(int64_t)ts
                     success:(RTVTAnswerSuccessCallBack)successCallback
                        fail:(RTVTAnswerFailCallBack)failCallback;


/// 结束翻译 对应streamId
/// @param streamId 翻译流id
/// @param lastSeq seq
/// @param successCallback 成功回调
/// @param failCallback 失败回调
-(void)endTranslateWithStreamId:(int64_t)streamId
                        lastSeq:(int64_t)lastSeq
                        success:(RTVTAnswerSuccessCallBack)successCallback
                           fail:(RTVTAnswerFailCallBack)failCallback;


//使用结束时调用 下次使用需要先登录
- (BOOL)closeConnect;


- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END



