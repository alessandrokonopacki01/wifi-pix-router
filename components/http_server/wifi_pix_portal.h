
#pragma once

#include "esp_http_server.h"

// Endereço oficial do portal WiFi Pix
#define WIFI_PIX_URL "https://wifipix.vercel.app/"

// Redireciona o navegador para os planos
static esp_err_t wifi_pix_portal_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "302 Found");

    httpd_resp_set_hdr(
        req,
        "Location",
        WIFI_PIX_URL
    );

    httpd_resp_set_hdr(
        req,
        "Cache-Control",
        "no-store"
    );

    return httpd_resp_send(req, NULL, 0);
}

// Registra a página /portal
static const httpd_uri_t wifi_pix_portal_uri = {
    .uri = "/portal",
    .method = HTTP_GET,
    .handler = wifi_pix_portal_handler,
    .user_ctx = NULL
};
