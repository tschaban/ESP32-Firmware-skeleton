#ifndef _ESP_CSS_h
#define _ESP_CSS_h

#include <Configuration.h>

const char JSON_RESPONSE[] PROGMEM =
    "{\"device\":{\"type\":\"{{device.type}}\",\"name\":\"{{device.name}}\"},\"command\":\"{{"
    "request.command}}\",\"data\":{{response.data}},\"status\":\"{{response.status}}\"}";


const char HTTP_HEADER[] PROGMEM =
    "<!doctype html><html lang=\"{{s.lang}}\"><head><meta "
    "charset=\"utf-8\">{{s.r}}<title>{{firmware.name}} {{f.v}} "
    "[T{{f.t}}]</"
    "title><link href=\"https://fonts.googleapis.com/css2?family=Titillium+Web&display=swap\" rel=\"stylesheet\"><style>html{background:url(http://api.smartnydom.pl/images/background.jpg) no-repeat center center fixed;-webkit-background-size:cover;-moz-background-size:cover;-o-background-size:cover;background-size:cover}.l,.r{margin:0;padding:1.2em 1.2em 2.2em 1.2em;display:table-cell}.ltit,body{margin:auto}.b,.itm a,a{text-decoration:none}body{padding:2em;max-width:980px}.c{display:table;width:100%;margin-bottom:3em}.m{text-decoration:none;padding-left:1.5em;color:#777;font-size:0.9em}.l{width:280px;background:#000;color:#fff;border-top-left-radius:.8em;border-bottom-left-radius:.8em;opacity:.93}.r{background:#eee;border-top-right-radius:.8em;border-bottom-right-radius:.8em;opacity:.93}a,button,h1,h3,h4,input,label,li,p,span,small{font-family:'Titillium Web',sans-serif}h4{font-size:.8em;margin-bottom:1px}.lst{list-style:none;margin:0;padding:0}.itm a,.itm i{display:block;white-space:nowrap;padding:0 1em;color:#aaa;font-size:.8em}.itm i{font-weight:700;padding-top:.5em}.cf label,.hint,input,select{display:inline-block;vertical-align:middle}.itm a:focus,.itm a:hover{background-color:#aaa;text-decoration:none;padding:0 1.5em;color:#000}.ci{margin-bottom:1em}.ci h1{color:#999;border-bottom:1px solid #ddd;font-size:1.2em;font-weight:500;margin:0}.ci .cd{color:#aaa;font-size:80%;font-style:italic;margin-bottom:2em;margin-top:0}.cm{color:#999;font-size:90%;margin:0 0 20px}.la{margin:0 .1em;padding:.3em 1em;color:#fff;background:#999;font-size:80%}.cc label,.cf label{font-size:.875em}.lr{background:#ca3c3c}.bs,.lg{background:#2fb548}fieldset{margin:0;padding:.35em 0 .75em;border:0}.cf{margin-bottom:.3em}.cc{margin:0 0 .1em 9.4em}.cf label{text-align:right;width:10em;margin:0 1em 0 0}input,select{padding:.4em .6em;border:1px solid #ccc;box-sizing:border-box}.hint{padding-left:.5em;color:#aaa;font-size:80%}.b{font-size:100%;padding:.2em 1em;border:1px solid #999;border:transparent;color:#fff}.be{background:#ca3c3c}.bw{background:#df7514}.bc{background:#42b8dd}.b:focus,.b:hover{background-image:-webkit-linear-gradient(transparent,rgba(0,0,0,.05) 40%,rgba(0,0,0,.1));background-image:linear-gradient(transparent,rgba(0,0,0,.05) 40%,rgba(0,0,0,.1))}</style></head><body>";

const char HTTP_FIRMWARE_BANNER_IMAGE[] PROGMEM = "<img src=\"http://api.smartnydom.pl/logo/T{{f.t}}/{{f.v}}/{{f.n}}/{{f.h}}/{{f.l}}\" style=\"width: 100%;display: block\" alt=\"{{firmware.name}}\">"; 
const char HTTP_FIRMWARE_BANNER_TEXT[] PROGMEM = "<h3 class=\"la\">{{firmware.name}} T{{firmware.type}}v{{f.v}} {{f.d}}</h3>"; 


const char HTTP_MESSAGE_LINE_ITEM[] PROGMEM = "<li class=\"m\">{{I}}</li>";

const char HTTP_FORM_BLOCK_HEADER[] PROGMEM =
    "<div class=\"ci\"><h1>{{T}}</h1><p "
    "class=\"cd\">{{D}}</p><fieldset>";

const char HTTP_FORM_BLOCK_CLOSURE[] PROGMEM = "</fieldset></div>";

/* Fixed menu items */


const char HTTP_MENU_HEADER[] PROGMEM ="</ul><h4>&#10150; {{m.h}}</h4><ul class=\"lst\">";

const char HTTP_MENU_ITEM[] PROGMEM =
    "<li class=\"itm\"><a href=\"/?o={{s.i}}\">{{i.i}}</a></li>";

const char HTTP_MENU_ITEM_EXTERNAL[] PROGMEM =
    "<li class=\"itm\"><a href=\"{{s.u}}\">{{i.i}}</a></li>";


const char HTTP_MENU_SUBITEMS_HEADER[] PROGMEM =
    "<li class=\"itm\"><i>{{i.i}}</i></li>";

const char HTTP_MENU_SUBITEM[] PROGMEM =
    "<li class=\"itm\"><a href=\"/?o={{s.i}}&i={{i.D}}\">&#8227; "
    "{{i.i}}: {{i.y}}</a></li>";

const uint8_t GPIOS[] PROGMEM = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22,
                                 23, 25, 26, 27, 32, 33, 34, 35, 36, 39};

#ifdef ESP_CONFIG_HARDWARE_MCP23017
const uint8_t MCP23017_GPIOS_ID[] PROGMEM = {0, 1, 2,  3,  4,  5,  6,  7,
                                             8, 9, 10, 11, 12, 13, 14, 15};
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
const char HTTP_ITEM_SCANNED_I2C_ADDRESSES_HEADER[] PROGMEM =
    "<div class=\"cf\"><label>{{i.l}}: </label><select "
    "name=\"address\"><option value=\"255\" "
    "{{i.s}}>{{L_NONE}}</option>";

const char HTTP_ITEM_SCANNED_I2C_ADDRESSES[] PROGMEM =
    "<option value=\"{{i.v}}\" {{i.s}}>[0x{{device.address}}] "
    ": {{device.name}}</option>";
#endif // AFE_CONFIG_HARDWARE_I2C

const char HTTP_INFO_TEXT[] PROGMEM = "<br><p class=\"cm\">{{i.v}}</p>";

const char HTTP_ITEM_CHECKBOX[] PROGMEM =
    "<div class=\"cc\"><label><input name=\"{{i.n}}\" "
    "type=\"{{i.t}}\" "
    "value=\"{{i.v}}\"{{i.c}}{{i.d}}>{{i.l}}</"
    "label>{{i.h}}</div>";

const char HTTP_ITEM_SELECT_OPEN[] PROGMEM =
    "<div class=\"cf\"><label>{{i.l}}</label><select "
    "name=\"{{i.n}}\">";

const char HTTP_ITEM_SELECT_OPTION[] PROGMEM =
    "<option value=\"{{i.v}}\" "
    "{{i.s}}>{{i.l}}</option>";

const char HTTP_ITEM_SELECT_CLOSE[] PROGMEM = "</select></div>";

const char HTTP_ITEM_HINT[] PROGMEM = "<br><p class=\"cm\">{{i.h}}</p>";

#ifdef ESP_CONFIG_HARDWARE_ADS1115
const char HTTP_ITEM_REFRESH_BUTTON[] PROGMEM =
"<input type=\"submit\" class=\"b bw\" value=\"{{item.label}}\"><br><br>";
#endif

#endif // _ESP_CSS_h



/*
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
*/
