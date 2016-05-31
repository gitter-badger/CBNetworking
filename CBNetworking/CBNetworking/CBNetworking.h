//
//  CBNetworking.m
//  CBNetworking
//
//  Created by 陈超邦 on 16/5/31.
//  Copyright © 2016年 陈超邦. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class NSURLSessionTask;

/**
 *  网络状态
 */
typedef NS_ENUM(NSInteger, CBNetworkStatus) {
    /**
     *  未知网络
     */
    CBNetworkStatusUnknown             = 1 << 0,
    /**
     *  无法连接
     */
    CBNetworkStatusNotReachable        = 1 << 2,
    /**
     *  网络正常
     */
    CBNetworkStatusNormal              = 1 << 3
};

/**
 *  请求方式
 */
typedef NS_ENUM(NSInteger, CBRequestType) {
    /**
     *  POST方式来进行请求或响应
     */
    CBPOSTRequest = 1 << 0,
    /**
     *  GET方式来进行请求或响应
     */
    CBGETRequest  = 1 << 1
};

/**
 *  数据串行方式
 */
typedef NS_ENUM(NSInteger, CBSerializerType) {
    /**
     *  HTTP方式来进行请求或响应
     */
    CBHTTPSerializer = 1 << 0,
    /**
     *  JSON方式来进行请求或响应
     */
    CBJSONSerializer = 1 << 1
};

/**
 *  请求任务
 */
typedef NSURLSessionTask CBURLSessionTask;

/**
 *  成功回调
 *
 *  @param response 成功后返回的数据
 */
typedef void(^CBResponseSuccessBlock)(id response);

/**
 *  失败回调
 *
 *  @param error 失败后返回的错误信息
 */
typedef void(^CBResponseFailBlock)(NSError *error);

/**
 *  下载进度
 *
 *  @param bytesWritten              已下载的大小
 *  @param totalBytes                总下载大小
 */
typedef void (^CBDownloadProgress)(int64_t bytesRead,
                                    int64_t totalBytes);
typedef CBDownloadProgress CBGetProgress;
typedef CBDownloadProgress CBPostProgress;

/**
 *  上传进度
 *
 *  @param bytesWritten              已上传的大小
 *  @param totalBytes                总上传大小
 */
typedef void(^CBUploadProgressBlock)(int64_t bytesWritten,
                                     int64_t totalBytes);

@interface CBNetworking : NSObject

/**
 *  配置请求头
 *
 *  @param httpHeaders 请求头参数
 */
+ (void)configHttpHeaders:(NSDictionary *)httpHeaders;

/**
 *  取消所有请求
 */
+ (void)cancelAllRequest;

/**
 *  根据url取消请求
 *
 *  @param url 请求url
 */
+ (void)cancelRequestWithURL:(NSString *)url;

/**
 *	获取缓存总大小
 *
 *	@return 缓存大小
 */
+ (unsigned long long)totalCacheSize;

/**
 *	清除缓存
 */
+ (void)clearCaches;

/**
 *	设置超时时间
 *
 *  @param timeout 超时时间
 */
+ (void)setupTimeout:(NSTimeInterval)timeout;

/**
 *  更新请求或者返回数据的解析方式(0为HTTP模式，1为JSON模式)
 *
 *  @param requestType  请求数据解析方式
 *  @param responseType 返回数据解析方式
 */
+ (void)updateRequestSerializerType:(CBSerializerType)requestType
                 responseSerializer:(CBSerializerType)responseType;

/**
 *  统一请求接口
 *
 *  @param url              请求路径
 *  @param params           拼接参数
 *  @param httpMethod       请求方式（0为POST,1位GET）
 *  @param progressBlock    进度回调
 *  @param successBlock     成功回调block
 *  @param failBlock        失败回调block
 *
 *  @return 返回的对象中可取消请求
 */
+ (CBURLSessionTask *)requestWithUrl:(NSString *)url
                              params:(NSDictionary *)params
                         httpMedthod:(CBRequestType)httpMethod
                       progressBlock:(CBDownloadProgress)progressBlock
                        successBlock:(CBResponseSuccessBlock)successBlock
                           failBlock:(CBResponseFailBlock)failBlock;

/**
 *  图片上传接口
 *
 *	@param image            图片对象
 *  @param url              请求路径
 *	@param name             图片名
 *	@param type             默认为image/jpeg
 *	@param params           拼接参数
 *	@param progressBlock    上传进度
 *	@param successBlock     成功回调
 *	@param failBlock		失败回调
 *
 *  @return 返回的对象中可取消请求
 */
+ (CBURLSessionTask *)uploadWithImage:(UIImage *)image
                                   url:(NSString *)url
                                  name:(NSString *)name
                                  type:(NSString *)type
                                params:(NSDictionary *)params
                         progressBlock:(CBUploadProgressBlock)progressBlock
                          successBlock:(CBResponseSuccessBlock)successBlock
                             failBlock:(CBResponseFailBlock)failBlock;

/**
 *  文件上传接口
 *
 *  @param url              上传文件接口地址
 *  @param uploadingFile    上传文件路径
 *  @param progressBlock    上传进度
 *	@param successBlock     成功回调
 *	@param failBlock		失败回调
 *
 *  @return 返回的对象中可取消请求
 */
+ (CBURLSessionTask *)uploadFileWithUrl:(NSString *)url
                           uploadingFile:(NSString *)uploadingFile
                           progressBlock:(CBUploadProgressBlock)progressBlock
                            successBlock:(CBResponseSuccessBlock)successBlock
                               failBlock:(CBResponseFailBlock)failBlock;

/**
 *  文件下载接口
 *
 *  @param url           下载文件接口地址
 *  @param saveToPath    存储目录
 *  @param progressBlock 下载进度
 *  @param successBlock  成功回调
 *  @param failBlock     下载回调
 *
 *  @return 返回的对象可取消请求
 */
+ (CBURLSessionTask *)downloadWithUrl:(NSString *)url
                            saveToPath:(NSString *)saveToPath
                         progressBlock:(CBDownloadProgress)progressBlock
                          successBlock:(CBResponseSuccessBlock)successBlock
                             failBlock:(CBResponseFailBlock)failBlock;


@end

