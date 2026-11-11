
#pragma once

#include "esp_http_server.h"

// WIFI PIX - PORTAL LOCAL
#define WIFI_PIX_URL "https://wifipix.vercel.app/"
#define WIFI_PIX_LOCAL "http://192.168.4.1/portal"

// Pagina HTML armazenada no proprio ESP32
static const char WIFI_PIX_HTML[] =
"<!DOCTYPE html>"
"<html lang='pt-BR'>"
"<head>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width,initial-scale=1'>"
"<title>WiFi Pix</title>"
"<style>"
"*{box-sizing:border-box}"
"body{margin:0;background:#091424;color:white;"
"font-family:Arial,sans-serif;padding:24px 16px}"
"main{max-width:430px;margin:35px auto}"
"h1{text-align:center;font-size:34px;margin-bottom:8px}"
"h1 span{color:#5eead4}"
"p{text-align:center;color:#a9bfd0;line-height:1.6}"
".card{background:#14243a;border:1px solid #304963;"
"border-radius:18px;padding:24px;margin-top:25px}"
"h2{font-size:20px}"
".plan{display:block;width:100%;padding:18px;margin:12px 0;"
"border-radius:13px;border:1px solid #3c526a;"
"background:#1c3049;color:white;text-align:left;"
"font-size:16px;cursor:pointer}"
".plan b{float:right;color:#facc80}"
".plan.active{border:2px solid #5eead4;background:#164047}"
"button.action{width:100%;padding:16px;margin-top:18px;"
"background:#5eead4;border:0;border-radius:12px;"
"font-weight:bold;font-size:15px;cursor:pointer}"
".note{font-size:12px;margin-top:17px}"
"</style>"
"</head>"
"<body>"
"<main>"
"<h1>WiFi <span>Pix</span></h1>"
"<p>Conecte-se de maneira simples.<br>"
"Escolha seu plano de internet.</p>"
"<section class='card'>"
"<h2>Escolha seu plano</h2>"
"<button class='plan' data-plan='15' onclick='selectPlan(this)'>"
"15 minutos <b>R$ 1,00</b></button>"
"<button class='plan active' data-plan='60' onclick='selectPlan(this)'>"
"1 hora <b>R$ 2,00</b></button>"
"<button class='plan' data-plan='1440' onclick='selectPlan(this)'>"
"24 horas <b>R$ 5,00</b></button>"
"<button class='action' onclick='continuePlan()'>"
"Continuar para o Pix</button>"
"<p class='note'>Prototipo experimental."
" O pagamento ainda nao libera a internet automaticamente.</p>"
"</section>"
"</main>"
"<script>"
"let selected=60;"
"function selectPlan(el){"
"selected=Number(el.dataset.plan);"
"document.querySelectorAll('.plan').forEach("
"p=>p.classList.remove('active'));"
"el.classList.add('active');"
"}"
"function continuePlan(){"
"window.location.href='https://wifipix.vercel.app/';"
"}"
"</script>"
"</body></html>";

// Pagina local do portal
static esp_err_t wifi_pix_portal_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");

    return httpd_resp_send(
        req,
        WIFI_PIX_HTML,
        HTTPD_RESP_USE_STRLEN
    );
}

// API experimental CAPPORT
static esp_err_t wifi_pix_capport_api_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "application/captive+json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");

    const char *json =
        "{\"captive\":true,"
        "\"user-portal-url\":\"" WIFI_PIX_LOCAL "\"}";

    return httpd_resp_send(
        req,
        json,
        HTTPD_RESP_USE_STRLEN
    );
}

// Registro da pagina
static const httpd_uri_t wifi_pix_portal_uri = {
    .uri = "/portal",
    .method = HTTP_GET,
    .handler = wifi_pix_portal_handler,
    .user_ctx = NULL
};

// Registro da API
static const httpd_uri_t wifi_pix_capport_api_uri = {
    .uri = "/capport-api",
    .method = HTTP_GET,
    .handler = wifi_pix_capport_api_handler,
    .user_ctx = NULL
};
