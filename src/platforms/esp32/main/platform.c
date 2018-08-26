/***************************************************************************
 *   Copyright 2018 by Davide Bettio <davide@uninstall.it>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "context.h"

void consume_gpio_mailbox(Context *ctx);
void consume_network_mailbox(Context *ctx);
void consume_udpdriver_mailbox(Context *ctx);

Context *platform_open_port(GlobalContext *glb, const char *driver_name, term opts)
{
    Context *new_ctx = context_new(glb);

    if (!strcmp(driver_name, "gpio")) {
        new_ctx->native_handler = consume_gpio_mailbox;
    }else if (!strcmp(driver_name, "network")) {
        new_ctx->native_handler = consume_network_mailbox;
    }else if (!strcmp(driver_name, "udp")) {
        new_ctx->native_handler = consume_udpdriver_mailbox;
    } else {
        context_destroy(new_ctx);
        return NULL;
    }

    return new_ctx;
}
