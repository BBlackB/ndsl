/*
 * @file: Epoll.cc
 * @brief
 * Epoll的实现
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <errno.h>
#include <sys/epoll.h>
#include "ndsl/net/Epoll.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/Channel.h"

namespace ndsl {

namespace net {

class Channel;

int Epoll::init()
{
    epfd_ = epoll_create(1);
    if (epfd_ < 0) {
        LOG(LEVEL_ERROR, "Epoll::init epoll_create\n");
        return errno;
    }

    LOG(LEVEL_DEBUG, "Epoll::init ok\n");
    return S_OK;
}

int Epoll::regist(Channel *pCh)
{
    struct epoll_event ev;

    ev.data.ptr = pCh;
    ev.events = pCh->getEvents();

    int ret = ::epoll_ctl(epfd_, EPOLL_CTL_ADD, pCh->getFd(), &ev);

    if (ret < 0) {
        LOG(LEVEL_DEBUG, "epoll::control regist\n");
        return errno;
    }

    return S_OK;
}

int Epoll::update(Channel *pCh)
{
    struct epoll_event ev;

    ev.data.ptr = pCh;
    ev.events = pCh->getEvents();

    int ret = ::epoll_ctl(epfd_, EPOLL_CTL_MOD, pCh->getFd(), &ev);

    if (ret < 0) {
        LOG(LEVEL_DEBUG, "epoll::control update\n");
        return errno;
    }

    return S_OK;
}

int Epoll::del(Channel *pCh)
{
    struct epoll_event ev;

    int ret = ::epoll_ctl(epfd_, EPOLL_CTL_DEL, pCh->getFd(), &ev);

    if (ret < 0) {
        LOG(LEVEL_DEBUG, "epoll::control del\n");
        return errno;
    }

    return S_OK;
}

int Epoll::wait(std::vector<Channel *> &channels, int timeoutMs)
{
    struct epoll_event events[MAX_EVENTS];
    int ret = ::epoll_wait(epfd_, events, MAX_EVENTS, timeoutMs);

    if (ret < 0) {
        LOG(LEVEL_ERROR, "Epoll::wait epoll_wait\n");
        return errno;
    }

    // 依次读取事件，并返回事件
    for (int i = 0; i < ret; i++) {
        Channel *channel = static_cast<Channel *>(events[i].data.ptr);
        channel->setRevent(events[i].events);
        channels.push_back(channel);
    }

    return S_OK;
}

} // namespace net
} // namespace ndsl
