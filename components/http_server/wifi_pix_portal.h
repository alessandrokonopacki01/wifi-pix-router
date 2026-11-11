
#pragma once

#include "esp_http_server.h"

// WIFI PIX - PORTAL EXPERIMENTAL

#define WIFI_PIX_URL "https://wifipix.vercel.app/"

// Redirecionamento para a pagina de planos
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

    return httpd_resp_send(
        req,
        "Abrindo WiFi Pix...",
        HTTPD_RESP_USE_STRLEN
    );
}

// API experimental de identificacao do portal
// Ainda nao existe controle real de acesso
static esp_err_t wifi_pix_capport_api_handler(
    httpd_req_t *req
)
{
    httpd_resp_set_type(
        req,
        "application/captive+json"
    );

    httpd_resp_set_hdr(
        req,
        "Cache-Control",
        "no-store"
    );

    const char *json =
        "{\"captive\":true,"
        "\"user-portal-url\":\"" WIFI_PIX_URL "\"}";

    return httpd_resp_send(
        req,
        json,
        HTTPD_RESP_USE_STRLEN
    );
}

// Pagina do WiFi Pix
static const httpd_uri_t wifi_pix_portal_uri = {
    .uri = "/portal",
    .method = HTTP_GET,
    .handler = wifi_pix_portal_handler,
    .user_ctx = NULL
};

// API do portal cativo
static const httpd_uri_t wifi_pix_capport_api_uri = {
    .uri = "/capport-api",
    .method = HTTP_GET,
    .handler = wifi_pix_capport_api_handler,
    .user_ctx = NULL
};
