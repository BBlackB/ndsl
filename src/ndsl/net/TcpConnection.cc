/**
 * @file TcpConnection.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/temp_define.h"
#include <unistd.h>

namespace ndsl {
namespace net {

TcpConnection::TcpConnection(int sockfd, EventLoop *pLoop)
{
    createChannel(sockfd, pLoop);
}
TcpConnection::~TcpConnection() {}

int TcpConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->setCallBack(this);

    return S_OK;
}

int TcpConnection::handleWrite()
{
    int sockfd = pTcpChannel_->getFd();
    if (sockfd < 0) { return -1; }
    int n;

    if (qSendInfo_.size() > 0) {
        pInfo tsi = qSendInfo_.front();

        if ((n = write(
                 sockfd, tsi->buf_ + tsi->offset_, tsi->len_ - tsi->offset_)) >
            0) {
            tsi->offset_ += n;

            if (tsi->offset_ == tsi->len_) {
                if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
                qSendInfo_.pop();
                // 无写事件 注销写事件
                if (qSendInfo_.size() == 0) pTcpChannel_->disableWriting();
                delete tsi; // 删除申请的内存
            } else if (n == 0) {
                // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
            tsi->errno_ = ::errno;
            if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);

            qSendInfo_.pop();
            delete tsi;

            // 无写事件 注销写事件
            if (qSendInfo_.size() == 0) pTcpChannel_->disableWriting();

            return S_FAIL;
        }
    }
    return S_OK;
}

int TcpConnection::onSend(
    const void *buf,
    size_t len,
    int flags,
    Callback cb,
    void *param,
    int &errno)
{
    int sockfd = pTcpChannel_->getFd();
    int n = write(sockfd, buf, len);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        return S_OK;
    } else if (n < 0) {
        // 出错 通知用户
        errno = ::errno;
        if (cb != NULL) cb(param);
        return S_FAIL;
    }

    pInfo tsi = new Info;
    tsi->offset_ = n;
    tsi->buf_ = buf;
    tsi->len_ = len;
    tsi->flags_ = flags;
    tsi->cb_ = cb;
    tsi->param_ = param;
    tsi->errno_ = errno;

    qInfo_.push(tsi);

    pTcpChannel_->enableWriting();

    return S_OK;
}

int TcpConnection::handleRead()
{
    int sockfd = pTcpChannel_->getFd();
    if (sockfd < 0) { return S_FAIL; }
    if ((recvInfo_.len_ = read(sockfd, recvInfo_.buf_, MAXLINE)) < 0) {
        recvInfo_.errno_ = ::errno;
    }

    // 无论出错还是完成数据读取之后都得通知用户
    if (recvInfo_.cb != NULL) recvInfo_.cb_(recvInfo_.param_);

    // 将读事件移除
    pTcpChannel_->disableReading();
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno
// 的值。
int TcpConnection::onRecv(
    char *buf,
    int &len,
    Callback cb,
    void *param,
    int &errno)
{
    int sockfd = pTcpChannel_->getFd();
    if (read(sockfd, buf_, MAXLINE) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            pTcpChannel_->enableReading();
            // 使用之前 结构体里面数据清0
            memset(&recvInfo_, 0, sizeof(Info));
            recvInfo_.buf_ = buf;
            recvInfo_.len_ = len;
            recvInfo_.cb_ = cb;
            recvInfo_.param_ = param;
            recvInfo_.errno_ = errno;
            return S_OK;
        } else {
            // FIXME: 这样写可以么
            errno = ::errno;
            return S_FAIL;
        }
    }
    if (cb != NULL) cb(param);

    // 先返回，最终的处理在onRead()里面
    return S_OK;
}

// 只读8个字节
int TcpConnection::onRecvmsg(char *buf, Callback cb, void *param)
{
    // TODO: 异步

    int sockfd = pTcpChannel_->getFd();
    read(sockfd, buf, 8);
    if (cb != NULL) cb(param);
}

} // namespace net
} // namespace ndsl
