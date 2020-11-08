/*
 * @Author: jiejie
 * @GitHub: https://github.com/jiejieTop
 * @Date: 2020-10-27 18:34:01
 * @LastEditors: jiejie
 * @LastEditTime: 2020-11-08 11:07:22
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */

#include "dora_dgram.h"
#include "dora_log.h"
#include "dora_epoller.h"

#define EPOLLER_DATA "this is a dgram test ..."

using doralib::epoller;

void dgram_read(dgram_socket *dgram)
{
    char recv_buf[1024];
    int len = 0;
    memset(recv_buf, 0, sizeof(recv_buf));

    DORA_LOG_INFO("dgram read callback ...");
    
    len = dgram->dgram_recvfrom(recv_buf, sizeof(recv_buf), NULL, NULL, 1000);

    DORA_LOG_INFO("len is {} : {}", len, recv_buf);
}


int main(void)
{
    DORA_LOG_INFO("========================= epoller =========================");
    
    auto epoller = new doralib::epoller;

    auto dgram1 = new doralib::dgram_socket("127.0.0.4", "8001");
    auto dgram2 = new doralib::dgram_socket("127.0.0.4", "8002");
    dgram1->dgram_bind("8002");
    dgram2->dgram_bind("8001");

    epoller->epoller_add(dgram2, doralib::DORA_EPOLLER_READ, dgram_read);

    dgram1->dgram_sendto(EPOLLER_DATA, strlen(EPOLLER_DATA), "127.0.0.4", "8001");
    
    sleep(1);
    delete epoller;

    DORA_LOG_INFO("========================= success =========================");

    return 0;
}

