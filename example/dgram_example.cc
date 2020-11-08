/*
 * @Author: jiejie
 * @GitHub: https://github.com/jiejieTop
 * @Date: 2020-10-27 18:34:01
 * @LastEditors: jiejie
 * @LastEditTime: 2020-11-08 11:07:04
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */

#include "dora_dgram.h"
#include "dora_log.h"
#include "dora_epoller.h"

#define DGRAM_DATA "this is a dgram test ..."

int main(void)
{
    
    char recv_buf[1024];
    int len = 0;
    memset(recv_buf, 0, sizeof(recv_buf));

    DORA_LOG_INFO("========================= dgram =========================");

    auto dgram1 = new doralib::dgram_socket("127.0.0.4", "8001");
    auto dgram2 = new doralib::dgram_socket("127.0.0.4", "8002");
    dgram1->dgram_bind("8002");
    dgram2->dgram_bind("8001");

    dgram1->dgram_sendto(DGRAM_DATA, strlen(DGRAM_DATA), "127.0.0.4", "8002");

    len = dgram1->dgram_recvfrom(recv_buf, sizeof(recv_buf), NULL, NULL, 1000);

    DORA_LOG_INFO("len is {} : {}", len, recv_buf);

    dgram1->dgram_close();
    dgram2->dgram_close();

    DORA_LOG_INFO("========================= success =========================");

    return 0;
}

