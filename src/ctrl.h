#ifndef CTRL_H
#define CTRL_H

#include <stdbool.h>
#include <sys/types.h>

/**
 * @brief Connect to the ctrl socket server
 * @param path Path to the Unix socket
 * @return 0 on success, -1 on error
 */
int connect_ctrl_client(const char *path);

/**
 * @brief Start the ctrl loop thread
 */
void start_ctrl_loop();

/**
 * @brief Stop the ctrl loop and close the socket
 */
void stop_ctrl_loop();

#endif // CTRL_H
