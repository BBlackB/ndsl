/**
 * @file TcpAcceptor.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPACCEPTOR_H__
#define __TCPACCEPTOR_H__

#include "TcpChannel.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpConnection;

class TcpAcceptor
{
  private:
    int listenfd_;                     // 监听fd
    EventLoop *pLoop_;                 // 指向EventLoop
    TcpChannel *pTcpChannel_;          // 指向自己的TcpChannel
    using Callback = void (*)(void *); // Callback 函数指针原型

    // 测试专用
    Callback cb_;

    // 用于保存用户回调信息
    struct Info
    {
        TcpConnection *pCon_;   // 指向TcpConnection
        struct sockaddr *addr_; // sockaddr
        socklen_t *addrlen_;    // sockaddr长度
        Callback cb_;           // 回调函数
        void *param_;           // 回调函数参数
        bool inUse_;            // 判断当前结构体是否有数据
    } info;

  public:
    TcpAcceptor(EventLoop *pLoop);
    ~TcpAcceptor();

    // 测试专用
    TcpAcceptor(Callback cb, EventLoop *pLoop);

    // 保存用户信息 填充上面的结构体
    int setInfo(
        TcpConnection *pCon,
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);

    // 新连接到来时候执行此函数
    static int handleRead(void *pthis);

    // 开始
    int start();

  private:
    // new Channel socket bind listen
    int createAndListen();
};

} // namespace net
} // namespace ndsl

#endif // __TCPACCEPTOR_H__