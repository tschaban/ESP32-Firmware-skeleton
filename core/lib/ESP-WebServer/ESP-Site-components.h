/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_CSS_h
#define _ESP_CSS_h

#include <Configuration.h>

const char HTTP_HEADER[] PROGMEM =
    "<!doctype html><html lang=\"{{s.lang}}\"><head><meta "
    "charset=\"utf-8\">{{s.redirect}}<title>{{f.name}} {{f.version}}</"
    "title><style>#l,#r{padding:20px;display:table-cell}.ltit,body{margin:0}.b,"
    ".itm "
    "a,a{text-decoration:none}body{background:#ddd;padding:15px}#c{display:"
    "table;width:100%}#l{width:300px;background:#33363b;color:#eee}#r{"
    "background:#eee}a,button,h1,h3,h4,input,label,li,p,span{font-family:sans-"
    "serif}.lst{list-style:none;margin:0;padding:0}.itm "
    "a{display:block;white-space:nowrap;padding:.2em "
    "1em;color:#777;font-size:95%}a{color:#36f}.cf "
    "label,.hint,input,select{display:inline-block;vertical-align:middle}.itm "
    "a:focus,.itm "
    "a:hover{background-color:#eee;text-decoration:none;padding:.2em "
    "1.5em;color:#000}.ci{margin-bottom:2em}.ci "
    "h1{color:#aaa;border-bottom:1px solid "
    "#ddd;font-size:110%;font-weight:500;letter-spacing:.1em}.ci "
    ".cd{color:#444;line-height:1.8em;font-size:80%;font-style:italic}.cm{"
    "color:#999;font-size:90%;margin:0 0 20px}.la{margin:0 .1em;padding:.3em "
    "1em;color:#fff;background:#999;font-size:80%}.cc label,.cf "
    "label{font-size:.875em}.lr{background:#ca3c3c}.bs,.lg{background:#2fb548}"
    "fieldset{margin:0;padding:.35em 0 "
    ".75em;border:0}.cf{margin-bottom:.5em}.cc{margin:1em 0 .5em 9.4em}.cf "
    "label{text-align:right;width:10em;margin:0 1em 0 "
    "0}input,select{padding:.5em .6em;border:1px solid "
    "#ccc;box-sizing:border-box}.hint{padding-left:.3em;color:#aaa;font-size:"
    "80%}.b{font-size:100%;padding:.5em 1em;border:1px solid "
    "#999;border:transparent;color:#fff}.be{background:#ca3c3c}.bw{background:#"
    "df7514}.bc{background:#42b8dd}.b:focus,.b:hover{filter:alpha(opacity=90);"
    "background-image:-webkit-linear-gradient(transparent,rgba(0,0,0,.05) "
    "40%,rgba(0,0,0,.1));background-image:linear-gradient(transparent,rgba(0,0,"
    "0,.05) 40%,rgba(0,0,0,.1))}</style></head><body>";

const char HTTP_FOOTER_CONNECTED[] PROGMEM = "<a style=\"color:#0475b6;\" "
                                             "href=\"https://"
                                             "{{s.lang}}.donate.afe-firmware."
                                             "smartnydom.pl\">{{L_DONATE}}</a>";

const char HTTP_FORM_BLOCK_HEADER[] PROGMEM =
    "<div class=\"ci\"><h1>{{title}}</h1><p "
    "class=\"cd\">{{description}}</p><fieldset>";

const char HTTP_FORM_BLOCK_CLOSURE[] PROGMEM = "</fieldset></div>";

const char HTTP_FOOTER_EXTENDED[] PROGMEM =
    "<div style=\"padding: 5px 0\"><img "
    "src=\"https://img.shields.io/badge/"
    "{{L_VERSION}}%20-%20{{f.version}}-blue.svg\" "
    "alt=\"{{f.version}}\" /></div>";

/* Fixed menu items */
const char HTTP_MENU_ITEM[] PROGMEM =
    "<li class=\"itm\"><a href=\"/?o={{site.id}}\">{{item.title}}</a></li>";

const char HTTP_MENU_SUBITEMS_HEADER[] PROGMEM =
    "<li class=\"itm\"><a><i>{{item.title}}</i></a></li>";

const char HTTP_MENU_SUBITEM[] PROGMEM =
    "<li class=\"itm\"><a href=\"/?o={{site.id}}&i={{item.id}}\">&#8227; "
    "{{item.title}}: {{item.id.display}}</a></li>";

const uint8_t GPIOS[] PROGMEM = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22,
                                 23, 25, 26, 27, 32, 33, 34, 35, 36, 39};

#ifdef ESP_CONFIG_HARDWARE_I2C
const char HTTP_ITEM_SCANNED_I2C_ADDRESSES_HEADER[] PROGMEM =
    "<div class=\"cf\"><label>{{item.label}}: </label><select "
    "name=\"address\"><option value=\"255\" "
    "{{item.selected}}>{{L_NONE}}</option>";

const char HTTP_ITEM_SCANNED_I2C_ADDRESSES[] PROGMEM =
    "<option value=\"{{item.value}}\" {{item.selected}}>[0x{{device.address}}] "
    ": {{device.name}}</option>";
#endif

const char HTTP_ITEM_CHECKBOX[] PROGMEM =
    "<div class=\"cc\"><label><input name=\"{{item.name}}\" type=\"checkbox\" "
    "value=\"{{item.value}}\" {{item.checked}}>{{item.label}}</label></div>";

const char HTTP_ITEM_SELECT_OPEN[] PROGMEM =
    "<div class=\"cf\"><label>{{item.label}}</label><select "
    "name=\"{{item.name}}\">";

const char HTTP_ITEM_SELECT_OPTION[] PROGMEM =
    "<option value=\"{{item.value}}\" "
    "{{item.selected}}>{{item.label}}</option>";

const char HTTP_ITEM_SELECT_CLOSE[] PROGMEM = "</select></div>";

const char HTTP_ITEM_HINT[] PROGMEM = "<br><p class=\"cm\">{{item.hint}}</p>";

#ifdef ESP_CONFIG_HARDWARE_ADS1115
const char HTTP_ITEM_REFRESH_BUTTON[] PROGMEM =
"<input type=\"submit\" class=\"b bw\" value=\"{{item.label}}\"><br><br>";
#endif

const char HTTP_SITE_RESET_TO_DEFAULTS[] PROGMEM =
    "<fieldset><p class=\"cm\"><strong>{{L_WARNING}}</strong>: </p><p "
    "class=\"cm\">{{L_CONFIGURATION_WILL_BE_REMOVED}}: </p><input "
    "type=\"submit\" class=\"b be\" "
    "value=\"{{L_RESTORE_DEFAULT_SETTINGS}}\"></fieldset>";

const char HTTP_SITE_POST_RESET[] PROGMEM =
    "<fieldset><p class=\"cm\">{{L_UPGRADE_IN_PROGRESS}}</p><p "
    "class=\"cm\">{{L_CONNECT_TO_HOTSPOT_AFTER_UPGRADE}}: </p><a "
    "href=\"http://192.168.5.1\">http://192.168.5.1</a></fieldset>";

const char HTTP_SITE_UPGRADE[] PROGMEM =
    "<fieldset><form method=\"post\" action=\"upgrade?o=8\" "
    "enctype=\"multipart/form-data\"><div "
    "class=\"cf\"><label>{{L_SELECT_FIRMWARE}}</label><input class=\"bs\" "
    "name=\"update\" type=\"file\" accept=\".bin\"></div><p "
    "class=\"cm\">{{L_UPGRADE_INFO}}.</p><button type=\"submit\" class=\"b "
    "be\">{{L_UPGRADE}}</button></form></fieldset>";

#endif
