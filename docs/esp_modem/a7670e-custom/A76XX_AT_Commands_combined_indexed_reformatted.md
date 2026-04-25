# 0 A76XX AT Commands — Combined Indexed Extract

## 0.1 Inhaltsverzeichnis
- [1 Introduction](#1-introduction)
  - [1.1 Scope of the document](#1.1-scope-of-the-document)
  - [1.2 Related documents](#1.2-related-documents)
  - [1.3 Terms and Abbreviations](#1.3-terms-and-abbreviations)
  - [1.4 Definitions and Conventions](#1.4-definitions-and-conventions)
    - [1.4.1 1. Definitions](#1.4.1-1.-definitions)
    - [1.4.2  <CR> Carriage return character.](#1.4.2-carriage-return-character.)
    - [1.4.3  Max Response Time](#1.4.3-max-response-time)
    - [1.4.4 2. Document Conventions](#1.4.4-2.-document-conventions)
  - [1.5 AT Interface Synopsis](#1.5-at-interface-synopsis)
    - [1.5.1 Interface Settings](#1.5.1-interface-settings)
    - [1.5.2 AT Commands Syntax](#1.5.2-at-commands-syntax)
      - [1.5.2.1 1. Basic Command](#1.5.2.1-1.-basic-command)
      - [1.5.2.2 2. S Parameter syntax](#1.5.2.2-2.-s-parameter-syntax)
      - [1.5.2.3 3. Extended Syntax](#1.5.2.3-3.-extended-syntax)
      - [1.5.2.4 Table 1: Types of AT commands and responses](#1.5.2.4-table-1-types-of-at-commands-and-responses)
      - [1.5.2.5 4. Combining AT commands on the same Command line](#1.5.2.5-4.-combining-at-commands-on-the-same-command-line)
      - [1.5.2.6 5. Entering successive AT commands on separate lines](#1.5.2.6-5.-entering-successive-at-commands-on-separate-lines)
    - [1.5.3 Supported character sets](#1.5.3-supported-character-sets)
- [3 AT Commands for Status Control](#3-at-commands-for-status-control)
  - [3.1 Overview of AT Commands for Status Control](#3.1-overview-of-at-commands-for-status-control)
  - [3.2 Detailed Description of AT Commands for Status Control](#3.2-detailed-description-of-at-commands-for-status-control)
    - [3.2.5 AT+CPOF Power down the module](#3.2.5-at+cpof-power-down-the-module)
      - [3.2.5.1 Examples](#3.2.5.1-examples)
    - [3.2.6 AT+CRESET Reset the module](#3.2.6-at+creset-reset-the-module)
      - [3.2.6.1 Examples](#3.2.6.1-examples)
- [4 AT Commands for Network](#4-at-commands-for-network)
  - [4.1 Overview of AT Commands for Network](#4.1-overview-of-at-commands-for-network)
  - [4.2 Detailed Description of AT Commands for Network](#4.2-detailed-description-of-at-commands-for-network)
    - [4.2.1 AT+CREG Network registration](#4.2.1-at+creg-network-registration)
      - [4.2.1.1 Examples](#4.2.1.1-examples)
    - [4.2.2 AT+COPS Operator selection](#4.2.2-at+cops-operator-selection)
      - [4.2.2.1 Defined Values](#4.2.2.1-defined-values)
      - [4.2.2.2 Examples](#4.2.2.2-examples)
- [5 AT Commands for Packet Domain](#5-at-commands-for-packet-domain)
  - [5.1 Overview of AT Commands for Packet Domain](#5.1-overview-of-at-commands-for-packet-domain)
  - [5.2 Detailed Description of AT Commands for Packet Domain](#5.2-detailed-description-of-at-commands-for-packet-domain)
    - [5.2.1 AT+CGREG Network registration status](#5.2.1-at+cgreg-network-registration-status)
      - [5.2.1.1 Examples](#5.2.1.1-examples)
    - [5.2.2 AT+CEREG EPS network registration status](#5.2.2-at+cereg-eps-network-registration-status)
      - [5.2.2.1 Defined Values](#5.2.2.1-defined-values)
      - [5.2.2.2 Examples](#5.2.2.2-examples)
    - [5.2.3 AT+CGATT Packet domain attach or detach](#5.2.3-at+cgatt-packet-domain-attach-or-detach)
      - [5.2.3.1 Defined Values](#5.2.3.1-defined-values)
      - [5.2.3.2 Examples](#5.2.3.2-examples)
    - [5.2.15 AT+CGEREP GPRS event reporting](#5.2.15-at+cgerep-gprs-event-reporting)
      - [5.2.15.1 Defined Values](#5.2.15.1-defined-values)
      - [5.2.15.2 Examples](#5.2.15.2-examples)
- [10 AT Commands for Serial Interface](#10-at-commands-for-serial-interface)
  - [10.1 Overview of AT Commands for Serial Interface](#10.1-overview-of-at-commands-for-serial-interface)
  - [10.2 Detailed Description of AT Commands for Serial Interface](#10.2-detailed-description-of-at-commands-for-serial-interface)
    - [10.2.3 AT+IPR Set local baud rate temporarily](#10.2.3-at+ipr-set-local-baud-rate-temporarily)
      - [10.2.3.1 Defined Values](#10.2.3.1-defined-values)
      - [10.2.3.2 Examples](#10.2.3.2-examples)
    - [10.2.4 AT+IPREX Set local baud rate permanently](#10.2.4-at+iprex-set-local-baud-rate-permanently)
      - [10.2.4.1 Defined Values](#10.2.4.1-defined-values)
      - [10.2.4.2 Examples](#10.2.4.2-examples)
    - [10.2.5 AT+ICF Set control character framing](#10.2.5-at+icf-set-control-character-framing)
      - [10.2.5.1 Defined Values](#10.2.5.1-defined-values)
      - [10.2.5.2 Examples](#10.2.5.2-examples)
    - [10.2.6 AT+IFC Set local data flow control](#10.2.6-at+ifc-set-local-data-flow-control)
      - [10.2.6.1 Defined Values](#10.2.6.1-defined-values)
      - [10.2.6.2 Examples](#10.2.6.2-examples)
    - [10.2.7 AT+CSCLK Control UART Sleep](#10.2.7-at+csclk-control-uart-sleep)
      - [10.2.7.1 Defined Values](#10.2.7.1-defined-values)
      - [10.2.7.2 Examples](#10.2.7.2-examples)
    - [10.2.8 AT+CMUX Enable the multiplexer over the UART](#10.2.8-at+cmux-enable-the-multiplexer-over-the-uart)
      - [10.2.8.1 Defined Values](#10.2.8.1-defined-values)
      - [10.2.8.2 Examples](#10.2.8.2-examples)
    - [10.2.9 AT+CATR Configure URC destination interface](#10.2.9-at+catr-configure-urc-destination-interface)
      - [10.2.9.1 Defined Values](#10.2.9.1-defined-values)
      - [10.2.9.2 Examples](#10.2.9.2-examples)
    - [10.2.10 AT+CFGRI Configure RI pin](#10.2.10-at+cfgri-configure-ri-pin)
      - [10.2.10.1 Defined Values](#10.2.10.1-defined-values)
      - [10.2.10.2 Examples](#10.2.10.2-examples)
    - [10.2.11 AT+CURCD Configure the delay time and number of URC](#10.2.11-at+curcd-configure-the-delay-time-and-number-of-urc)
      - [10.2.11.1 Defined Values](#10.2.11.1-defined-values)
      - [10.2.11.2 Examples](#10.2.11.2-examples)
- [12 AT Commands for File System](#12-at-commands-for-file-system)
  - [12.1 Overview of AT Commands for File System](#12.1-overview-of-at-commands-for-file-system)
  - [12.2 Detailed Description of AT Commands for File System](#12.2-detailed-description-of-at-commands-for-file-system)
    - [12.2.4 AT+FSLS List directories/files in current directory](#12.2.4-at+fsls-list-directoriesfiles-in-current-directory)
      - [12.2.4.1 Defined Values](#12.2.4.1-defined-values)
      - [12.2.4.2 Examples](#12.2.4.2-examples)
    - [12.2.5 AT+FSDEL Delete file](#12.2.5-at+fsdel-delete-file)
      - [12.2.5.1 Defined Values](#12.2.5.1-defined-values)
      - [12.2.5.2 Examples](#12.2.5.2-examples)
    - [12.2.7 AT+FSATTRI Request file attributes](#12.2.7-at+fsattri-request-file-attributes)
      - [12.2.7.1 Defined Values](#12.2.7.1-defined-values)
      - [12.2.7.2 Examples](#12.2.7.2-examples)
    - [12.2.11 AT+FSOPEN Open a file](#12.2.11-at+fsopen-open-a-file)
      - [12.2.11.1 Defined Values](#12.2.11.1-defined-values)
      - [12.2.11.2 Examples](#12.2.11.2-examples)
    - [12.2.12 AT+FSREAD Read a file](#12.2.12-at+fsread-read-a-file)
      - [12.2.12.1 Defined Values](#12.2.12.1-defined-values)
      - [12.2.12.2 Examples](#12.2.12.2-examples)
    - [12.2.13 AT+FSWRITE Write a file](#12.2.13-at+fswrite-write-a-file)
      - [12.2.13.1 Defined Values](#12.2.13.1-defined-values)
      - [12.2.13.2 Examples](#12.2.13.2-examples)
    - [12.2.16 AT+FSCLOSE Close a file](#12.2.16-at+fsclose-close-a-file)
      - [12.2.16.1 Defined Values](#12.2.16.1-defined-values)
      - [12.2.16.2 Examples](#12.2.16.2-examples)
- [13 AT Commands for File Transmission](#13-at-commands-for-file-transmission)
  - [13.1 Overview of AT Commands for File Transmission](#13.1-overview-of-at-commands-for-file-transmission)
  - [13.2 Detailed Description of AT Commands for File Transmission](#13.2-detailed-description-of-at-commands-for-file-transmission)
    - [13.2.1 AT+CFTRANRX Transfer a file to EFS](#13.2.1-at+cftranrx-transfer-a-file-to-efs)
      - [13.2.1.1 Defined Values](#13.2.1.1-defined-values)
      - [13.2.1.2 Examples](#13.2.1.2-examples)
    - [13.2.2 AT+CFTRANTX Transfer a file from EFS to host](#13.2.2-at+cftrantx-transfer-a-file-from-efs-to-host)
      - [13.2.2.1 Defined Values](#13.2.2.1-defined-values)
      - [13.2.2.2 Examples](#13.2.2.2-examples)
- [16 AT Commands for HTTP(S)](#16-at-commands-for-https)
  - [16.1 Overview of AT Commands for HTTP(S)](#16.1-overview-of-at-commands-for-https)
  - [16.2 Detailed Description of AT Commands for HTTP(S)](#16.2-detailed-description-of-at-commands-for-https)
    - [16.2.1 AT+HTTPINIT Start HTTP Service](#16.2.1-at+httpinit-start-http-service)
      - [16.2.1.1 Defined Values](#16.2.1.1-defined-values)
      - [16.2.1.2 Examples](#16.2.1.2-examples)
    - [16.2.2 AT+HTTPTERM Stop HTTP Service](#16.2.2-at+httpterm-stop-http-service)
    - [16.2.3 AT+HTTPPARA Set HTTP Parameters value](#16.2.3-at+httppara-set-http-parameters-value)
      - [16.2.3.1 Defined Values](#16.2.3.1-defined-values)
      - [16.2.3.2 Examples](#16.2.3.2-examples)
    - [16.2.4 AT+HTTPACTION HTTP Method Action](#16.2.4-at+httpaction-http-method-action)
      - [16.2.4.1 Defined Values](#16.2.4.1-defined-values)
      - [16.2.4.2 Examples](#16.2.4.2-examples)
    - [16.2.6 AT+HTTPHEAD Read the HTTP Header Information of Server Response](#16.2.6-at+httphead-read-the-http-header-information-of-server-response)
      - [16.2.6.1 Defined Values](#16.2.6.1-defined-values)
      - [16.2.6.2 Examples](#16.2.6.2-examples)
    - [16.2.7 AT+HTTPREAD Read the response information of HTTP Server](#16.2.7-at+httpread-read-the-response-information-of-http-server)
      - [16.2.7.1 Defined Values](#16.2.7.1-defined-values)
      - [16.2.7.2 Examples](#16.2.7.2-examples)
    - [16.2.8 AT+HTTPDATA Input HTTP Data](#16.2.8-at+httpdata-input-http-data)
      - [16.2.8.1 Defined Values](#16.2.8.1-defined-values)
      - [16.2.8.2 Examples](#16.2.8.2-examples)
    - [16.2.9 AT+HTTPPOSTFILE Send HTTP Request to HTTP(S)server by File](#16.2.9-at+httppostfile-send-http-request-to-httpsserver-by-file)
      - [16.2.9.1 Defined Values](#16.2.9.1-defined-values)
      - [16.2.9.2 Examples](#16.2.9.2-examples)
    - [16.2.10 AT+HTTPREADFILE Receive HTTP Response Content to a file](#16.2.10-at+httpreadfile-receive-http-response-content-to-a-file)
      - [16.2.10.1 Defined Values](#16.2.10.1-defined-values)
      - [16.2.10.2 Examples](#16.2.10.2-examples)
  - [16.3 Command Result Codes](#16.3-command-result-codes)
    - [16.3.1 Description of <statuscode>](#16.3.1-description-of)
  - [16.4 Unsolicited Result Codes](#16.4-unsolicited-result-codes)
- [18 AT Commands for MQTT(S)](#18-at-commands-for-mqtts)
  - [18.1 Overview of AT Commands for MQTT(S)](#18.1-overview-of-at-commands-for-mqtts)
  - [18.2 Detailed Description of AT Commands for MQTT(S)](#18.2-detailed-description-of-at-commands-for-mqtts)
    - [18.2.1 AT+CMQTTSTART Start MQTT service](#18.2.1-at+cmqttstart-start-mqtt-service)
      - [18.2.1.1 Defined Values](#18.2.1.1-defined-values)
      - [18.2.1.2 Examples](#18.2.1.2-examples)
    - [18.2.2 AT+CMQTTSTOP Stop MQTT service](#18.2.2-at+cmqttstop-stop-mqtt-service)
      - [18.2.2.1 Defined Values](#18.2.2.1-defined-values)
      - [18.2.2.2 Examples](#18.2.2.2-examples)
    - [18.2.3 AT+CMQTTACCQ Acquire a client](#18.2.3-at+cmqttaccq-acquire-a-client)
      - [18.2.3.1 Defined Values](#18.2.3.1-defined-values)
      - [18.2.3.2 Examples](#18.2.3.2-examples)
    - [18.2.4 AT+CMQTTREL Release a client](#18.2.4-at+cmqttrel-release-a-client)
      - [18.2.4.1 Defined Values](#18.2.4.1-defined-values)
      - [18.2.4.2 Examples](#18.2.4.2-examples)
    - [18.2.5 AT+CMQTTSSLCFG Set the SSL context (only for SSL/TLS MQTT)](#18.2.5-at+cmqttsslcfg-set-the-ssl-context-only-for-ssltls-mqtt)
      - [18.2.5.1 Defined Values](#18.2.5.1-defined-values)
      - [18.2.5.2 Examples](#18.2.5.2-examples)
    - [18.2.8 AT+CMQTTCONNECT Connect to MQTT server](#18.2.8-at+cmqttconnect-connect-to-mqtt-server)
      - [18.2.8.1 Defined Values](#18.2.8.1-defined-values)
      - [18.2.8.2 Examples](#18.2.8.2-examples)
    - [18.2.9 AT+CMQTTDISC Disconnect from server](#18.2.9-at+cmqttdisc-disconnect-from-server)
      - [18.2.9.1 Defined Values](#18.2.9.1-defined-values)
      - [18.2.9.2 Examples](#18.2.9.2-examples)
    - [18.2.12 AT+CMQTTPUB Publish a message to server](#18.2.12-at+cmqttpub-publish-a-message-to-server)
      - [18.2.12.1 Defined Values](#18.2.12.1-defined-values)
      - [18.2.12.2 Examples](#18.2.12.2-examples)
    - [18.2.14 AT+CMQTTSUB Subscribe a message to server](#18.2.14-at+cmqttsub-subscribe-a-message-to-server)
      - [18.2.14.1 Defined Values](#18.2.14.1-defined-values)
      - [18.2.14.2 Examples](#18.2.14.2-examples)
    - [18.2.17 AT+CMQTTCFG Configure the MQTT Context](#18.2.17-at+cmqttcfg-configure-the-mqtt-context)
      - [18.2.17.1 Defined Values](#18.2.17.1-defined-values)
      - [18.2.17.2 Examples](#18.2.17.2-examples)
  - [18.3 Command Result Codes](#18.3-command-result-codes)
    - [18.3.1 Description of <err>](#18.3.1-description-of)
  - [18.4 Unsolicited Result Codes](#18.4-unsolicited-result-codes)
    - [18.4.1 Defined Values](#18.4.1-defined-values)
- [19 AT Commands for SSL](#19-at-commands-for-ssl)
  - [19.1 Overview of AT Commands for SSL](#19.1-overview-of-at-commands-for-ssl)
  - [19.2 Detailed Description of AT Commands for SSL](#19.2-detailed-description-of-at-commands-for-ssl)
    - [19.2.1 AT+CSSLCFG Configure the SSL Context](#19.2.1-at+csslcfg-configure-the-ssl-context)
      - [19.2.1.1 Defined Values](#19.2.1.1-defined-values)
      - [19.2.1.2 Examples](#19.2.1.2-examples)
  - [19.3 Command Result Codes](#19.3-command-result-codes)
    - [19.3.1 Description of <err>](#19.3.1-description-of)
  - [19.4 Unsolicited Result Codes](#19.4-unsolicited-result-codes)
- [23 AT Commands for GNSS](#23-at-commands-for-gnss)
  - [23.1 Overview of AT Commands for GNSS](#23.1-overview-of-at-commands-for-gnss)
  - [23.2 Detailed Description of AT Commands for GNSS](#23.2-detailed-description-of-at-commands-for-gnss)
    - [23.2.1 AT+CGNSSPWR GNSS power control, AP-Flash control and Dynamic Load control](#23.2.1-at+cgnsspwr-gnss-power-control-ap-flash-control-and-dynamic-load-control)
      - [23.2.1.1 Examples](#23.2.1.1-examples)
    - [23.2.7 AT+CGNSSMODE Configure GNSS support mode](#23.2.7-at+cgnssmode-configure-gnss-support-mode)
      - [23.2.7.1 Defined Values](#23.2.7.1-defined-values)
      - [23.2.7.2 Examples](#23.2.7.2-examples)
    - [23.2.8 AT+CGNSSNMEA Configure NMEA sentence type](#23.2.8-at+cgnssnmea-configure-nmea-sentence-type)
      - [23.2.8.1 Defined Values](#23.2.8.1-defined-values)
      - [23.2.8.2 Examples](#23.2.8.2-examples)
    - [23.2.12 AT+CGNSSINFO Get GNSS fixed position information](#23.2.12-at+cgnssinfo-get-gnss-fixed-position-information)
      - [23.2.12.1 Defined Values](#23.2.12.1-defined-values)
      - [23.2.12.2 Examples](#23.2.12.2-examples)
- [34 AT Commands for eDRX](#34-at-commands-for-edrx)
  - [34.1 Overview of AT Commands for eDRX](#34.1-overview-of-at-commands-for-edrx)
  - [34.2 Detailed Description of AT Commands for eDRX](#34.2-detailed-description-of-at-commands-for-edrx)
    - [34.2.1 AT+CEDRXS DRX Setting](#34.2.1-at+cedrxs-drx-setting)
      - [34.2.1.1 Defined Values](#34.2.1.1-defined-values)
      - [34.2.1.2 Examples](#34.2.1.2-examples)
    - [34.2.2 AT+CEDRXRDP eDRX Read Dynamic Parameters](#34.2.2-at+cedrxrdp-edrx-read-dynamic-parameters)
      - [34.2.2.1 Defined Values](#34.2.2.1-defined-values)
      - [34.2.2.2 Examples](#34.2.2.2-examples)
- [39 Summary of ERROR Codes](#39-summary-of-error-codes)
  - [39.1 Verbose Codes and Numeric Codes](#39.1-verbose-codes-and-numeric-codes)
  - [39.2 Response String of AT+CEER](#39.2-response-string-of-at+ceer)
  - [39.3 Summary of CME ERROR Codes](#39.3-summary-of-cme-error-codes)
    - [39.3.1 Defined Values](#39.3.1-defined-values)
    - [39.3.2 Examples](#39.3.2-examples)
  - [39.4 Summary of CMS ERROR Codes](#39.4-summary-of-cms-error-codes)
    - [39.4.1 Defined Values](#39.4.1-defined-values)
    - [39.4.2 Examples](#39.4.2-examples)


<!-- Source file: 1 Introduction.md -->


![](result/A76XX_Series_AT_Command_Manual_V2.03/images/A76XX_Series_AT_Command_Manual_V2.03.pdf-0020-01.png)


![](result/A76XX_Series_AT_Command_Manual_V2.03/images/A76XX_Series_AT_Command_Manual_V2.03.pdf-0020-02.png)


# 1 Introduction

## 1.1 Scope of the document

This document presents the AT Command Set for SIMCom A76XX Series.

More information about the SIMCom Module which includes the Software Version information can be retrieved by the command ATI. In this document, a short description, the syntax, the possible setting values and responses, and some Examples of AT commands are presented.

Prior to using the Module, please read this document and the Version History to know the difference from the previous document.

In order to implement communication successfully between Customer Application and the Module, it is recommended to use the AT commands in this document, but not to use some commands which are not included in this document.

## 1.2 Related documents

- [1] A76XX Series_TCPIP_Application_Note

- [2] A76XX Series_HTTP(S)_Application_Note

- [3] A76XX Series_FTP(S)_Application_Note

- [4] A76XX Series_MQTT(S)_Application_Note

- [5] A76XX Series_SSL_Application_Note

- [6] A76XX Series_AUDIO_Application_Note

- [7] A76XX Series_GNSS_Application Note

- [8] A76XX Series_Blue Tooth_Application Note

- [9] A76XX Series_CTBURST_Application Note

- [10] A76XX Series_FOTA_Application Note

You can visit the SIMCom Website for more information by the following link: http://www.simcom.com


![](result/A76XX_Series_AT_Command_Manual_V2.03/images/A76XX_Series_AT_Command_Manual_V2.03.pdf-0021-01.png)


## 1.3 Terms and Abbreviations

For the purposes of the present document, the following abbreviations apply:

|Abbreviation|Description|
|---|---|
|**AT**|ATtention; the two-character abbreviation is used to start a command line to be sent from TE/DTE to TA/DCE|
|**DCE**|Data Communication Equipment|
|**DCS**|Digital Cellular Network|
|**DTE**|Data Terminal Equipment|
|**DTMF**|Dual Tone Multi–Frequency|
|**EDGE**|Enhanced Data GSM Environment|
|**EGPRS**|Enhanced General Packet Radio Service|
|**GPIO**|General–Purpose Input/Output|
|**GPRS**|General Packet Radio Service|
|**GSM**|Global System for Mobile communications|
|**HSDPA**|High Speed Downlink Packet Access|
|**HSUPA**|High Speed Uplink Packet Access|
|**I2C**|Inter–Integrated Circuit|
|**IMEI**|International Mobile station Equipment Identity|
|**IMSI**|International Mobile Subscriber Identity|
|**ME**|Mobile Equipment|
|**MO**|Mobile–Originated|
|**MS**|Mobile Station|
|**MT**|Mobile–Terminated; Mobile Termination|
|**PCS**|Personal Communication System|
|**PDU**|Protocol Data Unit|
|**PIN**|Personal Identification Number|
|**PUK**|Personal Unlock Key|
|**SIM**|Subscriber Identity Module|
|**SMS**|Short Message Service|
|**SMS-SC**|Short Message Service Service Center|
|**TA**|Terminal Adaptor; e.g. a data card (equal to DCE)|
|**TE**|Terminal Equipment; e.g. a computer (equal to DTE)|
|**UE**|User Equipment|
|**UMTS**|Universal Mobile Telecommunications System|
|**USIM**|Universal Subscriber Identity Module|
|**WCDMA**|Wideband Code Division Multiple Access|
|**FTP**|File Transfer Protocol|
|**HTTP**|Hyper Text Transfer Protocol|
|**RTC**|Real Time Clock|
|**URC**|Unsolicited Result Code|

## 1.4 Definitions and Conventions

### 1.4.1 1. Definitions

For the purposes of the present document, the following syntactical definitions apply:

### 1.4.2  <CR> Carriage return character.

- **<LF>** Linefeed character.

- **<…>** Name enclosed in angle brackets is a syntactical element. Brackets themselves do not appear in the command line.

- **[…]** Optional subparameter of AT command or an optional part of TA information response is enclosed in square brackets. Brackets themselves do not appear in the command line. If subparameter is not given, its value equals to its previous value or the recommended default value.

**underline** Underlined and defined subparameter value is the recommended default setting or factory setting.

- Parameter Saving Mode

**NO_SAVE** : The parameter of the current AT command will be lost if module is rebooted or current AT command doesn't have parameter.

**AUTO_SAVE** : The parameter of the current AT command will be kept in NVRAM automatically and take in effect immediately, and it won't be lost if module is rebooted.

**AUTO_SAVE_REBOOT:** The parameter of the current AT command will be kept in NVRAM automatically and take in effect after reboot, and it won't be lost if module is rebooted.

**AT&W_SAVE** : The parameter of the current AT command will be kept inusersetting_save.nvm by sending the command of "AT&W".

### 1.4.3  Max Response Time

Max response time is estimated maximum time to get response, the unit is seconds.

### 1.4.4 2. Document Conventions

- Generally, the characters <CR> and <LF> are intentionally omitted throughout this document.


![](result/A76XX_Series_AT_Command_Manual_V2.03/images/A76XX_Series_AT_Command_Manual_V2.03.pdf-0023-01.png)


- If command response is ERROR, not list the ERROR response inside command syntax.

AT commands and responses in figures may be not following above conventions.

## 1.5 AT Interface Synopsis

### 1.5.1 Interface Settings

Between Customer Application and the Module, standardized RS–232 interface is used for the communication, and default values for the interface settings as following:

115200bps, 8 bit data, no parity, 1 bit stop, no data stream control.

### 1.5.2 AT Commands Syntax

The "AT" or "at" or "aT" or "At" prefix must be included at the beginning of each command line (except A/ and +++), and the character <CR> is used to finish a command line so as to issue the command line to the module. It is recommended that a command line only includes a command.

When Customer Application issues a series of AT commands on separate command lines, leave a pause between the preceding and the following command until information responses or result codes are retrieved by Customer Application, for Examples, "OK" is appeared. This advice avoids too many AT commands are issued at a time without waiting for a response for each command.

The AT Command set implemented by A76XX Series is a combination of 3GPP TS 27.005, 3GPP TS 27.007 and ITU-T recommendation V.25ter and the AT commands developed by SIMCom.

In the present document, AT commands are divided into three categories: Basic Command, S Parameter Command, and Extended Command.

#### 1.5.2.1 1. Basic Command

The format of Basic Command is "AT<x><n>" or "AT&<x><n>", where "<x>" is the command name, and


![](result/A76XX_Series_AT_Command_Manual_V2.03/images/A76XX_Series_AT_Command_Manual_V2.03.pdf-0024-01.png)


"<n>" is/are the parameter(s)for the basic command which is optional. An Examples of Basic Command is "ATE<n>", which informs the TA/DCE whether received characters should be echoed back to the TE/DTE according to the value of "<n>"; "<n>" is optional and a default value will be used if omitted.

#### 1.5.2.2 2. S Parameter syntax

The format of S Parameter Command is "ATS<n>=<m>", "<n>" is the index of the S–register to set, and "<m>" is the value to assign to it. "<m>" is optional; in this case, the format is "ATS<n>", and then a default value is assigned.

#### 1.5.2.3 3. Extended Syntax

The Extended Command has several formats, as following table list:

#### 1.5.2.4 Table 1: Types of AT commands and responses

|Test Command|The mobile equipment returns the list of parameters and value|
|---|---|
|**AT+<x>=?**|ranges set with the corresponding Write Command or by internal|
||processes.|
|Read Command|This command returns the currently set value of the parameter or|
|**AT+<x>?**|parameters.|
|Write Command||
|**AT+<x>=<…>**|This command sets the user-definable parameter values.|
|Execution Command|The execution command reads non-variable parameters affected|
|**AT+<x>**|byinternalprocesses in the GSM engine.|


The character "+" between the prefix "AT" and command name may be replaced by other character. For Examples, using "#" or "$"instead of "+".

#### 1.5.2.5 4. Combining AT commands on the same Command line

You can enter several AT commands on the same line. In this case, you do not need to type the "AT" or "at" prefix before every command. Instead, you only need type "AT" or "at" the beginning of the command line. Please note to use a semicolon as the command delimiter after an extended command; in basic syntax or S parameter syntax, the semicolon need not enter, for Examples: ATE1Q0S0=1S3=13V1X4;+IFC=0,0;+IPR=115200.

The Command line buffer can accept a maximum of 3071 characters (counted from the first command without "AT" or "at" prefix). If the characters entered exceeded this number then none of the Command will executed and TA will return "ERROR".

#### 1.5.2.6 5. Entering successive AT commands on separate lines

When you need to enter a series of AT commands on separate lines, please Note that you need to wait the final response (for Examples OK, CME error, CMS error)of last AT Command you entered before you enter


![](result/A76XX_Series_AT_Command_Manual_V2.03/images/A76XX_Series_AT_Command_Manual_V2.03.pdf-0025-01.png)


the next AT Command.

### 1.5.3 Supported character sets

The A76XX Series AT Command interface defaults to the IRA character set. The A76XX Series supports the following character sets:

GSM format

UCS2

**IRA**

The character set can be set and interrogated using the "AT+CSCS" Command (3GPP TS 27.007). The character set is defined in GSM specification 3GPP TS 27.005.

The character set affects transmission and reception of SMS and SMS Cell Broadcast messages, the entry and display of phone book entries text field and SIM Application Toolkit alpha strings.


<!-- Source file: 3 AT Commands for Status Control - marked only.md -->

# 3 AT Commands for Status Control

## 3.1 Overview of AT Commands for Status Control

|**Command**|**Description**|
|---|---|
|**AT+CPOF**|Power down the module|
|**AT+CRESET**|Reset the module|

## 3.2 Detailed Description of AT Commands for Status Control

### 3.2.5 AT+CPOF Power down the module

This command is used to power off the module. Once the AT+CPOF command is executed, the module will store user data and deactivate from network, and then shutdown.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CPOF=?**|**+CPOF: (**list of supported**<poweroff_mode>s)**<br>**OK**|
|Execution Command|**AT+CPOF**|**OK**<br>**POWERD DOWN**|
|Write Command|**AT+CPOF=<poweroff_mode>**|1)<br>**OK**<br>**+CGEV: NW PDN DEACT 1**<br>**+CGEV: ME DETACH**<br>**POWERD DOWN**<br>2)<br>**OK**<br>**POWERD DOWN**<br>3)<br>**ERROR**<br>4)<br>**+CME ERROR: <err>**|
|Parameter Saving Mode|-||
|Max Response Time|9000ms||
|Reference|Vendor||

|Parameter|Description|
|---|---|
|**<poweroff_mode>**|0<br>Ordinary shutdown<br>1 Quick shutdown|

#### 3.2.5.1 Examples

**AT+CPOF=? +CPOF: (0,1)**

**OK AT+CPOF OK**

**+CGEV: NW PDN DEACT 1**

**+CGEV: ME DETACH**

**POWERD DOWN AT+CPOF=1 OK**

**POWERD DOWN**

The 1803S project does not support “AT+CPOF=0/1”.

### 3.2.6 AT+CRESET Reset the module

This command is used to reset the module.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Execution Command|**AT+CRESET**|**OK**|
|Test Command|**AT+CRESET=?**|**OK**|
|Parameter Saving Mode|-||
|Max Response Time|9000ms||
|Reference|Vendor||

#### 3.2.6.1 Examples

**AT+CRESET=?**

**OK AT+CRESET OK**

<!-- Source file: 4 AT Commands for Network - marked only.md -->

# 4 AT Commands for Network

## 4.1 Overview of AT Commands for Network

|**Command**|**Description**|
|---|---|
|**AT+CREG**|Network registration|
|**AT+COPS**|Operator selection|

## 4.2 Detailed Description of AT Commands for Network

### 4.2.1 AT+CREG Network registration

This command is used to control the presentation of an unsolicited result code +CREG: <stat> when <n>=1 and there is a change in the ME network registration status, or code +CREG: <stat>[,<lac>,<ci>] when <n>=2 and there is a change of the network cell.

Read command returns the status of result code presentation and an integer <stat> which shows whether the network has currently indicated the registration of the ME. Location information elements <lac> and <ci> are returned only when <n>=2 and ME is registered in the network.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CREG=?**|**+CREG: (**range of supported**<n>s)**<br>**OK**|
|Read Command|**AT+CREG?**|1)<br>**+CREG: <n>,<stat>[,<lac>,<ci>]**<br>**OK**<br>2)<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**|
|Write Command|**AT+CREG=<n>**|1)<br>**OK**<br>2)<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**|
|Execution Command|**AT+CREG**|Set default value(<n>=0):<br>**OK**|
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|3GPP TS 27.007||

|Parameter|Description|
|---|---|
|**<n>**|0<br>disable network registration unsolicited result code.<br>1<br>enable network registration unsolicited result code +CREG: <stat>.<br>2<br>enable network registration and location information unsolicited<br>result code +CREG: <stat>[,<lac>,<ci>].|
|**<stat>**|0<br>not registered, ME is not currently searching a new operator to<br>register to.<br>1<br>registered, home network.<br>2<br>not registered, but ME is currently searching a new operator to<br>register to.<br>3<br>registration denied.<br>4<br>unknown.<br>5<br>registered, roaming.<br>6<br>registered for "SMS only", home network (applicable only when<br>E-UTRAN)|

||7<br>registered for "SMS only", roaming (applicable only when <AcT><br>indicates E-UTRAN)<br>11 attached for emergencybearer services only|
|---|---|
|**<lac>**|Two byte location area code in hexadecimal format(e.g."00C3" equals<br>193 in decimal).|
|**<ci>**|Cell Identify in hexadecimal format.<br>GSM: Maximum is two byte.<br>WCDMA: Maximum is four byte.|

#### 4.2.1.1 Examples

**AT+CREG=? +CREG: (0-2) OK AT+CREG? +CREG: 0,1 OK AT+CREG=1 OK AT+CREG OK**

### 4.2.2 AT+COPS Operator selection

Write command forces an attempt to select and register the GSM/UMTS network operator. <mode> is used to select whether the selection is done automatically by the ME or is forced by this command to operator <oper> (it shall be given in format <format>). If the selected operator is not available, no other operator shall be selected (except <mode>=4). The selected operator name format shall apply to further read commands (AT+COPS?)also. <mode>=2 forces an attempt to deregister from the network. The selected mode affects to all further network registration (e.g. after <mode>=2, ME shall be unregistered until <mode>=0 or 1 is selected).

Read command returns the current mode and the currently selected operator. If no operator is selected,<format> and <oper> are omitted.

Test command returns a list of quadruplets, each representing an operator present in the network. Quadruplet consists of an integer indicating the availability of the operator <stat>, long and short alphanumeric format of the name of the operator, and numeric format representation of the operator. Any of the formats may be unavailable and should then be an empty field. The list of operators shall be in order: home network, networks referenced in SIM, and other networks.

It is recommended (although optional)that after the operator list TA returns lists of supported <mode>s and <format>s. These lists shall be delimited from the operator list by two commas.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|[**,,(**list of supported**<mode>s),(**list of supported**<format>s)**]]<br>**AT+COPS=?**<br>**OK**<br>2)<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**|1)<br>**+COPS: <mode>[,<format>,<oper>[,<AcT>]]**|
|Read Command|**OK**<br>**AT+COPS?**<br>2)<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**|1)|
|Write Command|**OK**<br>**AT+COPS=<mode>[,<format**<br>2)<br>**>[,<oper>[,<AcT>]]]**<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|60S||
|Reference|3GPP TS 27.007||

#### 4.2.2.1 Defined Values

|Parameter|Description|
|---|---|
|**<mode>**|0 automatic - 1 manual - 2 force deregister - 3 set only <format> - 4 manual/automatic NOTE: if <mode> is set to 1, 4 in write command, the <oper> is ||needed.Nomally, LTE is default search mode, So, if not in LTE, the <<br>AcT > is needed.| |---|---| ||
|**<format>**||0<br>long format alphanumeric <oper><br>1<br>short format alphanumeric <oper><br>2<br>numeric <oper>| ||
|**<oper>**||string type,<format> indicates if the format is alphanumeric or<br>numeric.| ||
|**<stat>**||0<br>unknown<br>1<br>available<br>2<br>current<br>3<br>forbidden| ||
|**<AcT>**||Access technology selected<br>0<br>GSM<br>1<br>GSM Compact<br>2<br>UTRAN<br>3<br>GSM w/EGPRS<br>4<br>UTRAN w/HSDPA<br>5<br>UTRAN w/HSUPA<br>6<br>UTRAN w/HSDPA and HSUPA<br>7<br>EUTRAN<br>8<br>UTRAN HSPA+||

#### 4.2.2.2 Examples

**AT+COPS=?**

**+COPS: (2,"CHN-UNICOM","UNICOM","46001",7),(1,"CHN-UNICOM","UNICOM", "46001",2),(1,"CHN-UNICOM","UNICOM","46001",0),(3,"CHINA MOBILE","CMCC", "46000",7),(3,"CHN-CT","CT","46011",7),(3,"CHINA MOBILE","CMCC","46000", 0),,(0,1,2,3,4),(0,1,2)**

**OK**

**AT+COPS? +COPS: 0,2,"46001",7**

**OK AT+COPS=0,2,"46001",7 OK**

<!-- Source file: 5 AT Commands for Packet Domain - marked only.md -->

# 5 AT Commands for Packet Domain

## 5.1 Overview of AT Commands for Packet Domain

|**Command**|**Description**|
|---|---|
|**AT+CEREG**|EPS network registration status|
|**AT+CGATT**|Packet domain attach or detach|
|**AT+CGEREP**|GPRS event reporting|

## 5.2 Detailed Description of AT Commands for Packet Domain

### 5.2.1 AT+CGREG Network registration status

This command controls the presentation of an unsolicited result code "+CGREG: <stat>" when <n>=1 and there is a change in the MT's GPRS network registration status.

The read command returns the status of result code presentation and an integer <stat> which shows Whether the network has currently indicated the registration of the MT.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CGREG=?**|**+CGREG: (**list of supported**<n>s)**<br>**OK**<br>Response|
|Read Command|**AT+CGREG?**|**+CGREG: <n>,<stat>[,<lac>,<ci>]**<br>**OK**<br>Response<br>1)<br>**OK**|
|Write Command|**AT+CGREG=<n>**|2)<br>**ERROR**<br>3)<br>**+CME ERROR**:**<err>**|
|Execution Command|**AT+CGREG**|Set default value:0<br>**OK**|
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|3GPP TS 27.007||

|**Defined Values**|**Defined Values**|
|---|---|
|**<n>**|0<br>disable network registration unsolicited result code<br>1<br>enable network registration unsolicited result code +CGREG:<br><stat><br>2<br>there is a change in the ME network registration status or a change<br>of the network cell:<br>+CGREG: <stat>[,<lac>,<ci>]|
|**<stat>**|0<br>not registered, ME is not currently searching an operator to register<br>to<br>1<br>registered, home network<br>2<br>not registered, but ME is currently trying to attach or searching an<br>operator to register to<br>3<br>registration denied<br>4<br>unknown<br>5<br>registered, roaming<br>6<br>registered for "SMS only",home network(applicable onlywhen|

E-UTRAN) 11 attached for emergency bearer services only **<lac>** Two byte location area code in hexadecimal format(e.g."00C3" equals 193 in decimal). **<ci>** Cell ID in hexadecimal format. GSM: Maximum is two byte. WCDMA: Maximum is four byte.

#### 5.2.1.1 Examples

**AT+CGREG=? +CGREG: (0-2) OK AT+CGREG? +CGREG: 0,1 OK AT+CGREG=1 OK AT+CGREG OK**


### 5.2.2 AT+CEREG EPS network registration status

The set command controls the presentation of an unsolicited result code +CEREG: <stat> when <n>=1 and there is a change in the MT's EPS network registration status in E-UTRAN, or unsolicited result code +CEREG: <stat>[,<tac>,<ci>[,<AcT>]] when <n>=2 and there is a change of the network cell in E-UTRAN; in this latest case <AcT>,<tac> and <ci> are sent only if available.

The read command returns the status of result code presentation and an integer <stat> which shows whether the network has currently indicated the registration of the MT. Location information elements <tac>,<ci> and <AcT>, if available, are returned only when <n>=2 and MT is registered in the network.

**AT+CEREG EPS network registration status**

||Response|
|---|---|
||1)|
|Test Command|**+CEREG: (**range of supported**<n>s)**|
|**AT+CEREG=?**||
||**OK**|
||2)|

|Type|Command / Value|Response / Notes|
|---|---|---|
|Read Command|**+CEREG: <n>,<stat>[,<tac>,<ci>]**<br>**AT+CEREG?**<br>**OK**<br>2)<br>**ERROR**|1)<br>**OK**|
|Write Command|**AT+CEREG=<n>**<br>2)<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**|1)|
|Execution Command|Set default value(<n>=0):<br>**AT+CEREG**<br>**OK**<br>2)<br>**ERROR**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|3GPP TS 24.008 [8]||

#### 5.2.2.1 Defined Values

|Parameter|Description|
|---|---|
|**<n>**|0 disable network registration unsolicited result code 1 enable network registration unsolicited result code +CEREG: <stat> 2 enable network registration and location information unsolicited result code +CEREG: <stat>[,<tac>,<ci>[,<AcT>]][,<tac>,<ci>[,<AcT>]],<tac>,<ci>[,<AcT>]][,<AcT>]],<AcT>]]]] -|
|**<stat>**|0 - 1 enable network registration unsolicited result code +CEREG: <stat> - 2 enable network registration and location information unsolicited result code +CEREG: <stat>[,<tac>,<ci>[,<AcT>]][,<tac>,<ci>[,<AcT>]],<tac>,<ci>[,<AcT>]][,<AcT>]],<AcT>]]]] - 0 not registered, MT is not currently searching an operator to register to - 1 registered, home network - 2 not registered, but MT is currently trying to attach or searching an operator to register to - 3 registration denied - 4 unknown (e.g. out of E-UTRAN coverage) - 5 registered, roaming - 6 registered for "SMS only", home network (not applicable) - 7 registered for "SMS only", roaming (not applicable) - 11 attached for emergency bearer services only -|
|**<tac>**|string type; two byte tracking area code in hexadecimal format (e.g. "00C3" equals 195 in decimal)|
|**<ci>**|string type; four byte E-UTRAN cell identify in hexadecimal format|
|**<AcT>**|A numberic parameter that indicates the access technology of serving cell - 0 GSM (not applicable) - 1 GSM Compact (not applicable) - 2 UTRAN (not applicable) - 3 GSM w/EGPRS (see NOTE 3)(not applicable) - 4 UTRAN w/HSDPA (see NOTE 4)(not applicable) - 5 UTRAN w/HSUPA (see NOTE 4)(not applicable) - 6 UTRAN w/HSDPA and HSUPA (see NOTE 4)(not applicable) - 7 E-UTRAN|

#### 5.2.2.2 Examples

**AT+CEREG=? +CEREG: (0-2) OK AT+CEREG? +CEREG: 0,1 OK AT+CEREG=1 OK AT+CEREG OK**

If the EPS MT in GERAN/UTRAN/E-UTRAN also supports circuit mode services and/or GPRS services, the +CREG command and +CREG: result codes and/or the +CGREG command and +CGREG: result codes apply to the registration status and location information for those services.

### 5.2.3 AT+CGATT Packet domain attach or detach

The write command is used to attach the MT to, or detach the MT from, the Packet Domain service. The read command returns the current Packet Domain service state.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CGATT: (**list of supported**<state>s)**<br>**AT+CGATT=?**<br>**OK**<br>2)<br>**ERROR**|1)<br>**+CGATT: <state>**|
|Read Command|**AT+CGATT?**<br>**OK**<br>2)<br>**ERROR**|1)<br>**OK**|
|Write Command|**AT+CGATT=<state>**<br>2)<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**||
|Parameter Saving Mode|NO_SAVE<br>Max Response<br>Time<br>9000ms||
|Reference|3GPP TS 27.007||

#### 5.2.3.1 Defined Values

|**<state>**|Indicates the state of Packet Domain attachment:<br>0<br>detached<br>1<br>attached|
|---|---|

#### 5.2.3.2 Examples

**AT+CGATT=? +CGATT: (0-1)**

**OK AT+CGATT? +CGATT: 1**

**OK AT+CGATT=1**

**OK**

### 5.2.15 AT+CGEREP GPRS event reporting

The write command enables or disables sending of unsolicited result codes, "+CGEV" from MT to TE in the case of certain events occurring in the Packet Domain MT or the network. <mode> controls the processing of unsolicited result codes specified within this command. <bfr> controls the effect on buffered codes when <mode> 1 or 2 is entered. If a setting is not supported by the MT, ERROR or +CME ERROR: is returned.

Read command returns the current <mode> and buffer settings.

Test command returns the modes and buffer settings supported by the MT as compound values.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CGEREP: (**list of supported**<mode>s),(**list of supported**<bfr>s)**<br>**AT+CGEREP=?**<br>**OK**<br>2)<br>**ERROR**|1)|
|Read Command|**+CGEREP: <mode>,<bfr>**<br>**AT+CGEREP?**<br>**OK**<br>2)<br>**ERROR**|1)|
|Write Command|**OK**<br>**AT+CGEREP=<mode>[,<bfr>**<br>2)<br>**]**<br>**ERROR**<br>3)<br>**+CME ERROR: <err>**||
|Execution Command|1)Set default value (<mode>=2,<bfr>=0):<br>**OK**<br>**AT+CGEREP**<br>2)<br>**ERROR**<br>Parameter Saving<br>Mode<br>NO_SAVE||
|Max Response Time|9000ms||
|Reference|3GPP TS 27.007||

#### 5.2.15.1 Defined Values

|**Defined Values**||
|---|---|
|**<mode>**|0<br>buffer unsolicited result codes in the MT; if MT result code buffer is<br>full, the oldest ones can be discarded. No codes are forwarded to the<br>TE.<br>1<br>discard unsolicited result codes when MT-TE link is reserved (e.g.<br>in on-line data mode); otherwise forward them directly to the TE.<br>2<br>buffer unsolicited result codes in the MT when MT-TE link is<br>reserved (e.g. in on-line data mode)and flush them to the TE when<br>MT-TE link becomes available; otherwise forward them directly to the<br>TE.|
|**<bfr>**|0<br>MT buffer of unsolicited result codes defined within this command<br>is cleared when <mode> 1 or 2 is entered.|

1 MT buffer of unsolicited result codes defined within this command is flushed to the TE when <mode> 1 or 2 is entered (OK response shall be given before flushing the codes).

The events are valid for GPRS/UMTS and LTE unless explicitly mentioned. For network attachment, the following unsolicited result codes and the corresponding events are defined:

**+CGEV: NW DETACH** The network has forced a PS detach. This implies that all active contexts have been deactivated. These are not reported separately. **+CGEV: ME DETACH** The mobile termination has forced a PS detach. This implies that all active contexts have been deactivated. These are not reported separately.

For MT class, the following unsolicited result codes and the corresponding events are defined:

|**+CGEV: NW CLASS <class>**|The network has forced a change of MT class. The highest available<br>class is reported (see +CGCLASS). The format of the parameter<br><class> is found in command +CGCLASS.|
|---|---|
|**+CGEV: ME CLASS <class>**|The mobile termination has forced a change of MT class. The highest<br>available class is reported (see +CGCLASS). The format of the<br>parameter <class> is found in command +CGCLASS.|

For PDP context activation, the following unsolicited result codes and the corresponding events are defined:

**+CGEV: NW PDN ACT** The network has activated a context. The context represents a **<cid>[,<WLAN_Offload>]** Primary PDP context in GSM/UMTS. The <cid> for this context is provided to the TE. The format of the parameter <cid> is found in command +CGDCONT.

<WLAN_Offload>: integer type. An integer that indicates whether traffic can be offloaded using the specified PDN connection via a WLAN or not. This refers to bit 1 (E-UTRAN offload acceptability value)and bit 2 (UTRAN offload acceptability value)in the WLAN offload acceptability IE as specified in 3GPP TS 24.008 [8] subclause 10.5.6.20.

0 offloading the traffic of the PDN connection via a WLAN when in S1 mode or when in Iu mode is not acceptable. 1 offloading the traffic of the PDN connection via a WLAN when in S1 mode is acceptable, but not acceptable in Iu mode. 2 offloading the traffic of the PDN connection via a WLAN when in Iu mode is acceptable, but not acceptable in S1 mode. 3 offloading the traffic of the PDN connection via a WLAN when in

S1 mode or when in Iu mode is acceptable.

This event is not applicable for EPS.

**+CGEV: ME PDN ACT <cid>[,<reason>[,<cid_other >]][,<WLAN_Offload>]**

The mobile termination has activated a context. The context represents a PDN connection in LTE or a Primary PDP context in GSM/UMTS. The <cid> for this context is provided to the TE. This event is sent either in result of explicit context activation request (+CGACT), or in result of implicit context activation request associated to attach request (+CGATT=1). The format of the parameters <cid> and <cid_other> are found in command +CGDCONT. The format of the parameter <WLAN_Offload> is defined above.

<reason>: integer type; indicates the reason why the context activation request for PDP type IPv4v6 was not granted. This parameter is only included if the requested PDP type associated with <cid> is IPv4v6, and the PDP type assigned by the network for <cid> is either IPv4 or IPv6.

- 0 IPv4 only allowed

- 1 IPv6 only allowed

2 single address bearers only allowed.

3 single address bearers only allowed and MT initiated context activation for a second address type bearer was not successful.

4 CI_PS_PDP_INVALID_REASON

<cid_other>: integer type; indicates the context identifier allocated by MT for an MT initiated context of a second address type. MT shall only include this parameter if <reason> parameter indicates single address bearers only allowed, and MT supports MT initiated context activation of a second address type without additional commands from TE, and MT has activated the PDN connection or PDP context associated with <cid_other>.

For legacy TEs supporting MT initiated context activation without TE requests, there is also a

subsequent event +CGEV: ME PDN ACT <cid_other> returned to TE.

|**+CGEV: NW ACT**<br>**<p_cid>,<cid>,<event_type>**<br>**[,<WLAN_Offload>]**|The network has activated a context. The <cid> for this context is<br>provided to the TE in addition to the associated primary <p_cid>. The<br>format of the parameters <p_cid> and <cid> are found in command<br>+CGDSCONT. The format of the parameter <WLAN_Offload> is<br>defined above.<br><event_type>: integer type; indicates whether this is an informational<br>event or whether the TE has to acknowledge it.<br>0<br>Informational event<br>1<br>Information request: Acknowledgement required. The<br>acknowledgement can be accept or reject,see +CGANS.|
|---|---|
|**+CGEV: ME ACT**<br>**<p_cid>,<cid>,<event_type>**<br>**[,<WLAN_Offload>]**|The network has responded to an ME initiated context activation. The<br><cid> for this context is provided to the TE in addition to the<br>associated primary <p_cid>. The format of the parameters <p_cid><br>and <cid> are found in command +CGDSCONT. The format of the<br>parameters <event_type> and <WLAN_Offload> are defined above.|

For PDP context deactivation, the following unsolicited result codes and the corresponding events are defined:

|**+CGEV: NW DEACT**<br>**<PDP_type>,<PDP_addr>[,<**<br>**cid>]**|The network has forced a context deactivation. The <cid> that was<br>used to activate the context is provided if known to the MT. The format<br>of the parameters <PDP_type>,<PDP_addr> and <cid> are found in<br>command +CGDCONT.|
|---|---|
|**+CGEV: ME DEACT**<br>**<PDP_type>,<PDP_addr>[,<**<br>**cid>]**|The mobile termination has forced a context deactivation. The <cid><br>that was used to activate the context is provided if known to the MT.<br>The format of the parameters <PDP_type>,<PDP_addr> and <cid><br>are found in command +CGDCONT.|
|**+CGEV: NW PDN DEACT**<br>**<cid>[,<WLAN_Offload>]**|The network has deactivated a context. The context represents a PDN<br>connection in LTE or a Primary PDP context in GSM/UMTS. The<br>associated <cid> for this context is provided to the TE. The format of<br>the parameter <cid> is found in command +CGDCONT. The format of<br>theparameter <WLAN_Offload> is defined above.|

Occurrence of this event replaces usage of the event +CGEV: NW DEACT <PDP_type>,<PDP_addr>[,<cid>].

**+CGEV: ME PDN DEACT**

**+CGEV: ME PDN DEACT** The mobile termination has deactivated a context. The context **<cid>** represents a PDN connection in LTE or a Primary PDP context in GSM/UMTS. The <cid> for this context is provided to the TE. The format of the parameter <cid> is found in command +CGDCONT.

Occurrence of this event replaces usage of the event +CGEV: ME DEACT <PDP_type>,<PDP_addr>[,<cid>].

**+CGEV: NW DEACT** The network has deactivated a context. The <cid> for this context is **<p_cid>,<cid>,<event_type>** provided to the TE in addition to the associated primary <p_cid>. The **[,<WLAN_Offload>]** format of the parameters <p_cid> and <cid> are found in command +CGDSCONT. The format of the parameters <event_type> and <WLAN_Offload> are defined above.

Occurrence of this event replaces usage of the event +CGEV: NW DEACT <PDP_type>,<PDP_addr>[,<cid>].

**+CGEV: ME DEACT**

**+CGEV: ME DEACT** The network has responded to an ME initiated context deactivation **<p_cid>,<cid>,<event_type>** request. The associated <cid> is provided to the TE in addition to the associated primary <p_cid>. The format of the parameters <p_cid> and <cid> are found in command +CGDSCONT. The format of the parameter <event_type> is defined above.

Occurrence of this event replaces usage of the event +CGEV: ME DEACT <PDP_type>,<PDP_addr>[,<cid>].

For PDP context modification, the following unsolicited result codes and the corresponding events are defined:

**+CGEV: NW MODIFY** The network has modified a context. The associated <cid> is provided **<cid>,<change_reason>,<ev** to the TE in addition to the <change_reason> and <event_type>. The **ent_type>[,<WLAN_Offload** format of the parameter <cid> is found in command +CGDCONT or **>]** +CGDSCONT. The format of the parameters <change_reason>,<event_type>, and <WLAN_Offload> are defined above.

<change_reason>: integer type; a bitmap that indicates what kind of change occurred. The <change_reason> value is determined by summing all the applicable bits. For Examples if both the values of QoS changed (Bit 2)and <WLAN_Offload> changed (Bit 3)have changed, then the <change_reason> value is 6.

The WLAN offload value will change when bit 1 or bit 2 or both of the indicators in the WLAN offload acceptability IE change, see the parameter <WLAN_Offload> defined above.

Bit 1 TFT changed Bit 2 Qos changed Bit 3 WLAN Offload changed

**+CGEV: ME MODIFY** The mobile termination has modified a context. The associated <cid> **<cid>,<change_reason>,<ev** is provided to the TE in addition to the <change_reason> and **ent_type>[,<WLAN_Offload** <event_type>. The format of the parameter <cid> is found in **>]** command +CGDCONT or +CGDSCONT. The format of the parameters <change_reason>,<event_type> and <WLAN_Offload> are defined above.

For other PDP context handling, the following unsolicited result codes and the corresponding events are defined:

**+CGEV: REJECT** A network request for context activation occurred when the MT was **<PDP_type>,<PDP_addr>** unable to report it to the TE with a +CRING unsolicited result code and was automatically rejected. The format of the parameters <PDP_type> and <PDP_addr> are found in command +CGDCONT.

This event is not applicable for EPS.

**+CGEV: NW REACT** The network has requested a context reactivation. The <cid> that was **<PDP_type>,<PDP_addr>[,<** used to reactivate the context is provided if known to the MT. The **cid>]** format of the parameters <PDP_type>,<PDP_addr> and <cid> are found in command +CGDCONT.

This event is not applicable for EPS.

#### 5.2.15.2 Examples

**AT+CGEREP=? +CGEREP: (0-2** ) **,(0-1** )

**OK AT+CGEREP? +CGEREP: 2,0 OK AT+CGEREP=2,0 OK AT+CGEREP OK**

<!-- Source file: 1 0 AT Commands for Serial Interface - marked only.md -->

# 10 AT Commands for Serial Interface

## 10.1 Overview of AT Commands for Serial Interface

|**Command**|**Description**|
|---|---|
|**AT+IPR**|Set local baud rate temporarily|
|**AT+IPREX**|Set local baud rate permanently|
|**AT+ICF**|Set control character framing|
|**AT+IFC**|Set local data flow control|
|**AT+CSCLK**|Control UART Sleep|
|**AT+CMUX**|Enable the multiplexer over the UART|
|**AT+CATR**|Configure URC destination interface|
|**AT+CFGRI**|Configure RI pin|
|**AT+CURCD**|Configure the delay time and number of URC|

## 10.2 Detailed Description of AT Commands for Serial Interface

### 10.2.3 AT+IPR Set local baud rate temporarily

This command sets the baud rate of module’s serial interface temporarily, after reboot the baud rate is set to value of IPREX.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+IPR=?**|**+IPR: (**list of supported**<speed>s)**<br>**OK**<br>Response|
|Read Command|**AT+IPR?**|**+IPR: <speed>**<br>**OK**<br>Response|
|Write Command|**AT+IPR=<speed>**|1)<br>**OK**<br>2)<br>**ERROR**|
|Execution Command|**AT+IPR**<br>Parameter|Set the value to boot value:<br>**OK**<br>Saving Mode<br>NO_SAVE|
|Max Response Time|9000ms||
|Reference|-||

#### 10.2.3.1 Defined Values

**<speed>** Baud rate per second: 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600, 1800000, 3600000.

#### 10.2.3.2 Examples

**AT+IPR?**

**+IPR: 115200**

**OK**

**AT+IPR=?**

**+IPR:**

**(300,600,1200,2400,4800,9600,19200,38400,57600,115200,230400,460800,921600,1800000,3600000 )**

**OK**

**AT+IPR=115200 OK**

### 10.2.4 AT+IPREX Set local baud rate permanently

This command sets the baud rate of module’s serial interface permanently, after reboot the baud rate is also valid.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+IPREX=?**|**+IPREX: (**list of supported**<speed>s)**<br>**OK**<br>Response|
|Read Command|**AT+IPREX?**|**+IPREX: <speed>**<br>**OK**<br>Response|
|Write Command|**AT+IPREX=<speed>**|1)<br>**OK**<br>2)<br>**ERROR**|
|Execution Command|**AT+IPREX**|Set default value 115200:<br>**OK**|
|Parameter Saving Mode|AUTO_SAVE||
|Reference|-||

#### 10.2.4.1 Defined Values

**<speed>** Baud rate per second: 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600, 1800000, 3600000.

#### 10.2.4.2 Examples

**AT+IPREX? +IPREX: 115200**

**OK**

**AT+IPREX=?**

**+IPREX: (300,600,1200,2400,4800,9600,19200,38400,57600,115200,230400,460800,921600, 1800000,3600000)**

**OK**

**AT+IPREX=115200 OK**

### 10.2.5 AT+ICF Set control character framing

This command sets character framing which contains data bit, stop bit and parity bit.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+ICF: (**list of supported**<format>s**)**,(**list of supported**<parity>s**)<br>**AT+ICF=?**<br>**OK**||
|Read Command|**+ICF: <format>,<parity>**<br>**AT+ICF?**<br>**OK**||
|Write Command|1)<br>**OK**<br>**AT+ICF=<format>,<parity>**<br>2)<br>**ERROR**<br>Execution<br>Command|Set default value:<br>**AT+ICF**<br>**OK**<br>Parameter<br>Saving Mode<br>NO_SAVE|
|Max Response Time|9000ms||

Reference -

#### 10.2.5.1 Defined Values

|**Defined Values**||
|---|---|
|**<format>**|1<br>data bit 8, parity bit 1,stop bit 1.<br>2<br>data bit 8, stop bit 1.<br>3<br>data bit 7, parity bit 1,stop bit 1.<br>4<br>data bit 7, stopbit 1.|
|**<parity>**|0<br>Odd<br>1<br>Even<br>2<br>none|

#### 10.2.5.2 Examples

**AT+ICF? +ICF: 2,2 OK AT+ICF=? +ICF: (1-4),(0-2) OK AT+ICF=2,2 OK AT+ICF OK**

### 10.2.6 AT+IFC Set local data flow control

The command sets the flow control mode of the module.

**AT+IFC Set local data flow control**

Response Test Command **+IFC: (** list of supported **<DCE>s** ) **,(** list of supported **<DTE>s** ) **AT+IFC=? OK** Response Read Command **+IFC: <DCE>,<DTE> AT+IFC? OK**

Response 1) Write Command **OK AT+IFC=<DCE>[,<DTE>]** 2) **ERROR** Response Execution Command Set default value: **AT+IFC OK** Parameter Saving Mode NO_SAVE Max Response Time 9000ms Reference -

#### 10.2.6.1 Defined Values

|Parameter|Description|
|---|---|
|**<DCE>**|0 none 1 software RTS XON/XOFF|
|**<DTE>**|2 RTS hardware flow control 0 none 1 software CTS XON/XOFF 2 CTS hardware flow control The hardware flow control is not supported by A7600X(X)-MNSE and A7600E-MASE.|

#### 10.2.6.2 Examples

**AT+IFC? +IFC: 0,0**

**OK AT+IFC=? +IFC: (0-2),(0-2)**

**OK AT+IFC=2,2 OK AT+IFC OK**


### 10.2.7 AT+CSCLK Control UART Sleep

This command is used to enable UART Sleep or always work. If set to 0, UART always work. If set to 1, ensure that DTR is pulled high and the module can go to DTR sleep. If set to 2, the module will enter RX sleep. RX wakeup directly sends data through the serial port (for example: AT) to wake up. If set to 3 (Supported only by the A7690B module), the module will enter GPIO sleep, Wake up module by raising wakeup_gpio.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CSCLK=?**|**+CSCLK: (**range of supported**<status>s**)<br>**OK**<br>Response|
|Read Command|**AT+CSCLK?**|**+CSCLK: <status>**<br>**OK**<br>Response|
|Write Command|**AT+CSCLK=<status>**|1)<br>**OK**<br>2)<br>**ERROR**|
|Execution Command|**AT+CSCLK**|Set <status>=0:<br>**OK**|
|Parameter Saving Mode|NO_SAVE||
|Reference|-||

#### 10.2.7.1 Defined Values

**<status>** 0 off 1 DTR sleep 2 RX sleep 3 GPIO sleep(Supported only by the A7690B module)

#### 10.2.7.2 Examples

**AT+CSCLK? +CSCLK: 0**

**OK AT+CSCLK=? A7690B module: +CSCLK: (0-3) OK Others module: +CSCLK: (0-2) OK AT+CSCLK=1 OK AT+CSCLK=2 OK AT+CSCLK=3 (Supported only by the A7690B module) OK AT+CSCLK OK**

The “AT+CSCLK=3” command is supported only by the A7690B module.

### 10.2.8 AT+CMUX Enable the multiplexer over the UART

This command is used to enable the multiplexer over the UART, after enabled four virtual ports can be used as AT command port or MODEM port, the physical UART can no longer transfer data directly under this case. By default all of the four virtual ports are used as AT command port. Second serial port is not support this command.

**AT+CMUX Enable the multiplexer over the UART**

Response Test Command **+CMUX: (0),(0),(1-8),(1-1500),(0),(0),(2-1000) AT+CMUX=? OK** Response Read Command **+CMUX: <value>,<subset>,<port_speed>,<N1>,<T1>,<N2>,<T2> AT+CMUX?**

**OK**

Response Write Command 1) **AT+CMUX=<value>[,<subset OK >[,<port_speed>[,<N1>[,<T1** 2) **>[,<N2>[,<T2>]]]]]] ERROR** Parameter Saving Mode NO_SAVE Max Response Time 9000ms Reference -

#### 10.2.8.1 Defined Values

|**Defined Values**||
|---|---|
|**<value>**|0<br>currently only 0 is supported (basic operation mode).|
|**<subset>**|Currently omitted|
|**<port_speed>**|1<br>9600 bit/s<br>2<br>19200 bit/s<br>3<br>38400 bit/s<br>4<br>57600 bit/s<br>5<br>115200 bit/s(default baudrate)<br>6<br>230400 bit/s<br>7<br>460800 bit/s<br>8<br>921600 bit/s|
|**<N1>**|1-1500|
|**<T1>**|Currently omitted|
|**<N2>**|Currently omitted|
|**<T2>**|2-1000|

#### 10.2.8.2 Examples

**AT+CMUX? +CMUX: 0,0,5,1500,0,0,600**

**OK**

**AT+CMUX=? +CMUX: (0),(0),(1-8),(1-1500),(0),(0),(2-1000)**

**OK AT+CMUX=0 OK**

### 10.2.9 AT+CATR Configure URC destination interface

This command is used to configure the serial port which will be used to output URCs. We recommend configure a destination port for receiving URC in the system initialization phase, in particular, in the case that transmitting large amounts of data, e.g. use TCP/UDP and MT SMS related AT command.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CATR: (**list of supported**<port>s)**<br>**AT+CATR=?**<br>**OK**||
|Read Command|**+CATR: <port>**<br>**AT+CATR?**<br>**OK**||
|Write Command|1)<br>**OK**<br>**AT+CATR=<port>**<br>2)<br>**ERROR**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|-||

#### 10.2.9.1 Defined Values

|**<port>**|0<br>all ports<br>1<br>use UART port to output URCs<br>2<br>use MODEM port to output URCs<br>3<br>use ATCOM port to output URCs<br>4<br>use cmux virtual port1 to output URCs<br>5<br>use cmux virtual port2 to output URCs<br>6<br>use cmux virtual port3 to output URCs<br>7<br>use cmux virtualport4 to output URCs|
|---|---|

#### 10.2.9.2 Examples

**AT+CATR? +CATR: 0**

**OK AT+CATR=?**

**+CATR: (0-7)**

**OK AT+CATR=1 OK**

### 10.2.10 AT+CFGRI Configure RI pin

This command configures the time of pulling RI down. These places are going to use it, for Examples: SMS, FTP, NETWORK, PB, CM, OS and so on.

**AT+CFGRI Configure RI pin**

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CFGRI=?**<br>**+CFGRI:**(list of supported**<status>**),(list of<br>supported**<URC_time>**ms), (list of supported**<SMS_time>**ms)<br>**OK**||
|Read Command|**+CFGRI: <status>,<URC_time>,<SMS_time>**<br>**AT+CFGRI?**<br>**OK**||
|Write Command|1)<br>**AT+CFGRI=<status>[,<**<br>**OK**<br>**URC_time >[,< SMS_time >]]**<br>2)<br>**ERROR**||
|Execution Command||Set default value:<br>**AT+CFGRI**<br>**OK**|
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|-||

#### 10.2.10.1 Defined Values

|Parameter|Description|
|---|---|
|**<status>**|0 off. 1 on.|
|**<URC_time>**|a numeric parameter which is number of milliseconds to assert RI delay to reset RI. The range is 10 to 6000, default value is 60ms.|
|**<SMS_time>**|a numeric parameter which is number of milliseconds to assert RI delay to reset RI. The range is 20 to 6000, default value is 120ms.|

#### 10.2.10.2 Examples

**AT+CFGRI? +CFGRI: 0,60,120**

**OK AT+CFGRI=? +CFGRI: (0-1),(10-6000),(20-6000)**

**OK AT+CFGRI=0,60,120 OK AT+CFGRI OK**

### 10.2.11 AT+CURCD Configure the delay time and number of URC

This command is used to configure delay time when output URC and the number of cached URCs. You can control delay time if some URC supports delay output. You can also set size to store URCs, they will output together when the delay time ends. For Examples, if you set delay time to 10ms and set the number of cached URCs to 1, there is only one URC output after 10ms.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CURCD: (**range of supported**<delay_time>ms),(1)**<br>**AT+CURCD=?**<br>**OK**||
|Read Command|**+CURCD: <delay_time>,1**<br>**AT+CURCD?**<br>**OK**||
|Write Command|1)<br>**AT+CURCD=<delay_time>,<**<br>**OK**<br>**cache_size>**<br>2)<br>**ERROR**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|-||

#### 10.2.11.1 Defined Values

|Parameter|Description|
|---|---|
|**<delay_time>**|0-10000 the unit is ms|
|**<cache_size>**|1 currently only 1 is supported|

#### 10.2.11.2 Examples

**AT+CURCD? +CURCD: 0,1 OK AT+CURCD=? +CURCD: (0-10000),(1) OK AT+CURCD=100,1 OK**

<!-- Source file: 1 2 AT Commands for File System - marked only.md -->

# 12 AT Commands for File System

## 12.1 Overview of AT Commands for File System

|**Command**|**Description**|
|---|---|
|**AT+FSLS**|List directories/files in current directory|
|**AT+FSDEL**|Delete file|
|**AT+FSATTRI**|Request file attributes|
|**AT+FSOPEN**|Open a file|
|**AT+FSCLOSE**|Close a file|
|**AT+FSREAD**|Read a file|
|**AT+FSWRITE**|Write a file|

|**Command**|**Description**|**Supported Modules**|
|---|---|---|

## 12.2 Detailed Description of AT Commands for File System

The file system is used to store files in a hierarchical (tree)structure, and there are some definitions and

conventions to use the AT commands.

Local storage space is mapped to "C:", "D:" for SD card. ( The A7678 does not support SD card). NOTE: General rules for naming (both directories and files):

   - a) The length of actual fully qualified names of files(C:/)can not exceed 115, also include full Dir.

- b) The length of actual fully qualified names of directories and files(D:/)can not exceed 250, also

- include full Dir.

   - c) Directory and file names can not include the following characters: \ / : * ? " < > |

   - d) Between directory name and file/directory name, use character "/" as list separator, so it can not appear in directory name or file name.

   - e) File names and directory names cannot begin with “.” or “blank” and it also can’t end with “.”

- f ) {non-ascii} input is only supported when the SD card function is supported. {non-ascii} input is still

- not allowed when operating external flash and file systems.

   - g) The file name in drive D is case-insensitive, but can be displayed in case format.

If the last character of names is period "."; the SD card can support this character, but the compatibility is not good.

h) Support relative path and absolute path input; In Cat 4 modules,disk C does not support directory creation, and disk D does not support renaming.

### 12.2.4 AT+FSLS List directories/files in current directory

This command is used to list informations of directories and/or files in current directory. Support "C:", "D:".

**AT+FSLS List directories/files in current directory**

Response Test Command **+FSLS: (** list of supported **<type>s) AT+FSLS=? OK** Response Read Command **+FSLS: SUBDIRECTORIES:<dir_num>,FILES:<file_num> AT+FSLS?**

**OK**

Response **[+FSLS: SUBDIRECTORIES: <** list of **subdirectories>]**

Write Command **AT+FSLS=<type>**

**[+FSLS: FILES: <** list of **files>]**

**OK**

Execution Command Response **AT+FSLS [+FSLS: SUBDIRECTORIES: <** list of **subdirectories>] [+FSLS: FILES: <** list of **files>] OK** - Parameter Saving Mode - Max Response Time Reference

#### 12.2.4.1 Defined Values

|Parameter|Description|
|---|---|
|**<dir_num>**|Integer type, the number of subdirectories in current directory.|
|**<file_num>**|Integer type, the number of files in current directory.|
|**<type>**|0 list both subdirectories and files 1 list subdirectories only 2 list files only|

#### 12.2.4.2 Examples

**AT+FSLS?**

**+FSLS: SUBDIRECTORIES:2,FILES:2**

**OK**

**AT+FSLS**

**+FSLS: SUBDIRECTORIES: FirstDir SecondDir**

**+FSLS: FILES: image_0.jpg image_1.jpg**

**OK**

**AT+FSLS=2 +FSLS: FILES: image_0.jpg image_1.jpg**

**OK**

### 12.2.5 AT+FSDEL Delete file

Supports absolute path and relative path. Support "C:", "D:".

**AT+FSDEL Delete file** Test Command Response **AT+FSDEL=? OK** Response 1)If successfully: Write Command **OK AT+FSDEL=<filename>** 2)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 12.2.5.1 Defined Values

**<filename>** String with or without double quotes, file name which is already existing.

#### 12.2.5.2 Examples

**AT+FSDEL=image_0.jpg OK**

If <filename> is *.*, it means delete all files in current directory.

### 12.2.7 AT+FSATTRI Request file attributes

This command is used to request the attributes of file which exists. Support "C:", "D:".

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+FSATTRI=?**|**OK**<br>Response<br>1)If successfully:|
|Write Command|**AT+FSATTRI=<filename>**|**+FSATTRI: <file_size>**<br>**OK**<br>2)If failed:<br>**ERROR**|
|Parameter Saving Mode|-||
|Max Response Time|-||
|Reference|||

#### 12.2.7.1 Defined Values

|Parameter|Description|
|---|---|
|**<filename>**|String with or without double quotes, file name which is existed.|
|**<file_size>**|The size of specified file, and the unit is in Byte.|

#### 12.2.7.2 Examples

**AT+FSATTRI=image_0.jpg +FSATTRI: 8604**

**OK**

### 12.2.11 AT+FSOPEN Open a file

This command opens a file and gets the file handle to be used in commands such as **AT+FSREAD** , **AT+FSWRITE** , **AT+FSSEEK** , **AT+FSPOSITION** , **AT+FSCLOSE** .Sopport “C:”,”D”.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+FSOPEN=?**|**+FSOPEN: <filename>[,(0-2)]**<br>**OK**|
|Read Command|**AT+FSOPEN?**|**OK**<br>Response|
|Write Command|**AT+FSOPEN**<br>**=<fileName>[,<mode>]**|1)If successfully<br>**+FSOPEN: <filehandle>**<br>**OK**|

2)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 12.2.11.1 Defined Values

|**Defined Values**||
|---|---|
|**<filename>**|The file name to be opened with the path.The maximum length is 115<br>bytes.|
|**<filehandle>**|The handle of the file.<br>The maximum number of open files is eight.|
|**<mode>**|The open mode of the file.<br>0<br>if the file does not exist,it will be created. If the file exists, it will<br>be directly opened. And both of them can be read and written.<br>1<br>if the file does not exist,it will be created. If the file exists, it will<br>be overwritten and cleared. And both of them can be read and written.<br>2<br>if the file exist, open it and it can be read only. When the file does<br>not exist,it will respond an error.|

#### 12.2.11.2 Examples

**AT+FSOPEN=C:/test.txt,0 +FSOPEN: 1**

**OK**

### 12.2.12 AT+FSREAD Read a file

This command reads the data of a file which is specified by the handle. The data starts from the current position of the pointer which belongs to the file handle.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+FSREAD=?**|**+FSREAD: <filehandle>[,<length>]**<br>**OK**|
|Write Command|**AT+FSREAD**<br>**=<filehandle>[,<length>]**|1)If successfully:<br>**CONNECT <read_length>**|

TA switches to data mode. When the total size of the data reaches **<length>** (unit: byte), TA will return to command mode, display the result and then reply the following codes: **OK** 2)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 12.2.12.1 Defined Values

|Parameter|Description|
|---|---|
|**<filehandle>**|The handle of the file.|
|**<length>**|The length of the file to be read out and the default is the file length.|
|**<read_length>**|The actual read length.|

#### 12.2.12.2 Examples

**AT+FSREAD=1,10 CONNECT 10 1234567890**

**OK**

### 12.2.13 AT+FSWRITE Write a file

This command writes data into a file. The data starts from the current position of the file pointer which belongs to the file handle.

**AT+FSWRITE Write a file**

Response Test Command **+FSWRITE: <filehandle>[,<length>[,<timeout>]] AT+FSWRITE=? OK** Response Write Command 1)If successfully: **AT+FSWRITE=<filehandle>[, CONNECT <length>,[<timeout>]]** TA switches to data mode. When the total size of the written data reaches **<length>** (unit: byte) or the time reaches **<timeout>** , TA will

return to command mode and reply the following codes: **+FSWRITE: <written_length>,<total_length>**

**OK**

2)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 12.2.13.1 Defined Values

|Parameter|Description|
|---|---|
|**<filehandle>**|The handle of the file to be operated.|
|**<length>**|The length of the file to be written ,and the default is 10K. The maximum value of this parameter is determined by|
|**<freesize>**|from **AT+FSMEM** .|
|**<timeout>**|The time waiting for data to be inputted to USB/UART. The default value is 5.Unit: s.|
|**<written_length>**|The actual written length.|
|**<total_length>**|The total length of the file.|

#### 12.2.13.2 Examples

**AT+FSWRITE=1,5,10 CONNECT**

//input data

**+FSWRITE: 0,5**

**OK**

### 12.2.16 AT+FSCLOSE Close a file

This command closes a file and ends the operation to the file. After that, the file handle is release and should not be used again, unless the file is opened again by **AT+FSOPEN** .

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+FSCLOSE: <filehandle>**<br>**AT+FSCLOSE=?**<br>**OK**||
|Write Command|1)If successfully:<br>**OK**<br>**AT+FSCLOSE=<filehandle>**<br>2)If failed:<br>**ERROR**<br>Parameter Saving<br>Mode<br>-||
|Max Response Time|-||
|Reference|||

#### 12.2.16.1 Defined Values

**<filehandle>**

The handle of the file to be operated.

#### 12.2.16.2 Examples

**AT+FSCLOSE=1 OK**

//move file from root directory to the user directory

<!-- Source file: 1 3 AT Commands for File Transmission - marked only.md -->

# 13 AT Commands for File Transmission

**File**

## 13.1 Overview of AT Commands for File Transmission

|**Command**|**Description**|
|---|---|
|**AT+CFTRANRX**|Transfer a file to EFS|
|**AT+CFTRANTX**|Transfer a file from EFS to host|

|**Command**|**Description**|**Supported Modules**|
|---|---|---|

## 13.2 Detailed Description of AT Commands for File Transmission

### 13.2.1 AT+CFTRANRX Transfer a file to EFS

This command is used to transfer a file to EFS.Support "C:", "D:".

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CFTRANRX=?**|**+CFTRANRX: [{non-ascii}]"FILEPATH"**<br>**OK**|
|Write Command|**AT+CFTRANRX=<filepath>,<l**<br>**en>[,<reserved>[,<location>]**<br>**]**|1)If successfully:<br>**>**<br>**OK**<br>2)If failed:|

**> ERROR** 3)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 13.2.1.1 Defined Values

|**Defined Values**||
|---|---|
|**<filepath>**|The path of the file on EFS|
|**<len>**|The length of the file data to send.<br>Because of the system resources, The length could not set too large. If<br>use the UART to send data, it may can set to 3Mb. If use USB to send<br>data, it may just can set to 200Kb. If limit the send speed, it can set<br>larger. The actual size could not ensure. Usually it is safer to set a<br>smaller size.|
|**<reserved>**|The value is 100.|
|**<location>**|The position offset from the start of the file.|

#### 13.2.1.2 Examples

**AT+CFTRANRX="c:/t1.txt",10 > OK AT+CFTRANRX="d:/MyDir/t1.txt",10 > OK AT+CFTRANRX="C:/ t2.txt",10,100,0 > OK**

1. The <filepath> is the name of the file on EFS, make sure that the file name does not exist under the path.

- 2.If sending file fails, increase the delay time between each 256 byte reach to 50ms, and then try to send file again.

3. Only **Cat4 modules** and SD card support Non-ASCII characters in file path.

4. The <reserved> is used by individual customers and if <location> is not default value,<reserved> will be considered invalid.

5.The <location> exceed the file size, the command will return “ **ERROR** ”.

- 6.When the <location> is less than the file size,it will write data from <location> .

7. The <location> is just supported in ASR1603 standard branches , compatible SIM800 branches and ASR1803S standard branches.

### 13.2.2 AT+CFTRANTX Transfer a file from EFS to host

This command is used to transfer a file from EFS to host.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CFTRANTX: [{non-ascii}]"FILEPATH"**<br>**AT+CFTRANTX=?**<br>**OK**|1)If successfully:<br>**[+CFTRANTX: DATA,<len>**<br>**…**<br>**+CFTRANTX: DATA,<len>]**|
|Write Command|**+CFTRANTX: 0**<br>**AT+CFTRANTX=<filepath>[,<**<br>**location>][,<size>][,<transMo**<br>**OK**<br>**de>]**<br>2)If <transMode> is 1 :<br>**>…**<br>**OK**<br>3)If failed:<br>**ERROR**||
|Parameter Saving Mode|-||
|Max Response Time|-||
|Reference|||

#### 13.2.2.1 Defined Values

|**Defined Values**||
|---|---|
|**<filepath>**|The path of the file on EFS|
|**<len>**|The length of the following file data to output.|
|**<location>**|The beginning of the file data to output.|
|**<size>**|The length of the file data to output.|
|**<transMode>**|Whether there is no urc in data output<br>0<br>normal mode|

1 data output directly without urc.

#### 13.2.2.2 Examples

**AT+CFTRANTX="c:/t1.txt"**

**+CFTRANTX: DATA,11 Testcontent +CFTRANTX: 0**

**OK**

**AT+CFTRANTX="d:/MyDir/t1.txt"**

**+CFTRANTX: DATA,11 Testcontent +CFTRANTX: 0**

**OK AT+CFTRANTX="d:/MyDir/t1.txt",1,4 +CFTRANTX: DATA,4 estc +CFTRANTX: 0**

**OK AT+CFTRANTX="c:/ 1.txt",0,10,1 >123456790 OK**

The <filepath> is the name of the file on EFS. If not set the size, it means range from location to the end of the file. If the (size + location)lager than the file size, it means range from location to the end of the file.

<!-- Source file: 1 6 AT Commands for HTTP(S) - marked only.md -->

# 16 AT Commands for HTTP(S)

## 16.1 Overview of AT Commands for HTTP(S)

|**Command**|**Description**|
|---|---|
|**AT+HTTPINIT**|Start HTTP service|
|**AT+HTTPTERM**|Stop HTTP Service|
|**AT+HTTPPARA**|Set HTTP Parameters value|
|**AT+HTTPACTION**|HTTP Method Action|
|**AT+HTTPHEAD**|Read the HTTP Header Information of Server Response|
|**AT+HTTPREAD**|Read the response information of HTTP Server|
|**AT+HTTPDATA**|Input HTTP Data|
|**AT+HTTPPOSTFILE**|Send HTTP Request to HTTP(S) server by File|
|**AT+HTTPREADFILE**|Receive HTTP Response Content to a file|

## 16.2 Detailed Description of AT Commands for HTTP(S)

### 16.2.1 AT+HTTPINIT Start HTTP Service

AT+HTTPINIT is used to start HTTP service by activating PDP context. You must execute AT+HTTPINIT before any other HTTP related operations.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+HTTPINIT=?**|**+HTTPINIT: (1-n)**<br>**OK**|
|Execute Command|**AT+HTTPINIT**|1)If start HTTP service successfully:|

**OK**

2)If failed: **ERROR** Response 1) **OK**

Write Command **AT+HTTPINIT=<cid> +HTTPINIT: <errcode>,<cid>** 2) **ERROR** - Parameter Saving Mode Max Response Time 120000ms Reference -

#### 16.2.1.1 Defined Values

|Parameter|Description|
|---|---|
|**<cid>**|A numeric parameter which specifies a particular PDP context .The range is 1-n,The maximum value n is related to the pdp command of the modem.|
|**<errcode>**|The result of start HTTP(S)service, 0 is success, others are failure. Please refer to errcode list.|

#### 16.2.1.2 Examples

**AT+HTTPINIT OK**

**AT+HTTPINIT=1 OK**

**+HTTPINIT: 0,1**

### 16.2.2 AT+HTTPTERM Stop HTTP Service

AT+HTTPTERM is used to stop HTTP service.

**AT+HTTPTERM Stop HTTP Service** Test Command Response

|Type|Command / Value|Response / Notes|
|---|---|---|
|Execute Command|1)If stop HTTP service successfully:<br>**OK**<br>**AT+HTTPTERM**<br>2)If failed:<br>**ERROR**|1)<br>**OK**|
|Write Command|**AT+HTTPTERM=<cid>**<br>**+HTTPTERM: <errcode>,<cid>**<br>2)<br>**ERROR**||
|Parameter Saving Mode|-||
|Max Response Time|120000ms||
|Reference|-||

|Parameter|Description|
|---|---|
|**<cid>**|A numeric parameter which specifies a particular PDP context .The<br>range is 1-n,The maximum value n is related to the pdp command of<br>the modem.|
|**<errcode>**|The result of stop HTTP(S)service, 0 is success, others are failure.<br>Please refer to errcode list.<br>**Examples**<br>**AT+HTTPTERM**<br>**OK**<br>**AT+HTTPTERM=1**<br>**OK**<br>**+HTTPTERM: 0,1**|

### 16.2.3 AT+HTTPPARA Set HTTP Parameters value

should input <value> like http://’server’/’path’:’tcpPort’. In addition, https://’server’/’path’:’tcpPort’ is used to access to a HTTPS server.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+HTTPPARA=?**|**OK**<br>Response|
|Write Command|1)If parameter format is right:<br>**OK**<br>**AT+HTTPPARA="URL",<url>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|1)If parameter format is right:<br>**AT+HTTPPARA="CONNECTTO"**<br>**OK**<br>**,<conn_timeout>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|1)If parameter format is right:<br>**AT+HTTPPARA="RECVTO",<re**<br>**OK**<br>**cv_timeout>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|1)If parameter format is right:<br>**AT+HTTPPARA="CONTENT",<c**<br>**OK**<br>**ontent_type>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|1)If parameter format is right:<br>**AT+HTTPPARA="ACCEPT",<ac**<br>**OK**<br>**cept-type>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|1)If parameter format is right:<br>**AT+HTTPPARA="SSLCFG",<ssl**<br>**OK**<br>**cfg_id>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|1)If parameter format is right:<br>**AT+HTTPPARA="USERDATA",<**<br>**OK**<br>**user_data>**<br>2)If parameter format is not right or other errors occur:<br>**ERROR**||
|Write Command|**AT+HTTPPARA="READMODE",**|1)If parameter format is right:|

|**<readmode>**|**OK**|
|---|---|
||2)If parameter format is not right or other errors occur:|
||**ERROR**|
|Parameter Saving Mode|-|
|Max Response Time|120000ms|
|Reference|-|

#### 16.2.3.1 Defined Values

|**Defined Values**||
|---|---|
|**<url>**|URL of network resource.String,start with "http://" or"https://"<br>a)http://’server’ :’tcpPort’ /’path’.<br>b)https://’server’ :’tcpPort’ /’path’.<br>"server"<br>DNS domain name or IP address<br>"path"<br>path to a file or directory of a server<br>"tcpPort"<br>http default value is 80,https default value is 443.(can be<br>omitted)|
|**<conn_timeout>**|Timeout for accessing server, Numeric type, range is 20-120s, default<br>is 120s.|
|**<recv_timeout>**|Timeout for receiving data from server, Numeric type range is 2s-120s,<br>default is 20s.|
|**<content_type>**|This is for HTTP "Content-Type" tag, String type, max length is 256,<br>and default is "text/plain".|
|**<accept-type>**|This is for HTTP "Accept-type" tag, String type, max length is 256, and<br>default is "*/*".|
|**<sslcfg_id>**|This is setting SSL context id, Numeric type, range is 0-9. Default is<br>0.Please refer to Chapter 19 of this document.|
|**<user_data>**|The customized HTTP header information. String type, max length is<br>256.|
|**<readmode>**|For HTTPREAD, Numeric type, it can be set to 0 or 1. If set to 1, you<br>can read the response content data from the same position repeatly.<br>The limit is that the size of HTTP server response content should be<br>shorter than 1M.Default is 0.|

When you want to use content-type mutipart/form-data to transfer data, you should set AT+HTTPPARA="CONTENT","mutipart/form-data" .And we will construct boundary header.

#### 16.2.3.2 Examples

**AT+HTTPPARA="URL","http://www.baidu.com" OK**

### 16.2.4 AT+HTTPACTION HTTP Method Action

AT+HTTPACTION is used to perform a HTTP Method. You can use HTTPACTION to send a get/post request to a HTTP/HTTPS server.

**AT+HTTPACTION HTTP Method Action** Response **+HTTPACTION: (0-4,20)** Test Command **(in ASR1603_042 the return is AT+HTTPACTION=? +HTTPACTION: (0-5,20) ) OK** Response 1)If parameter format is right: **OK +HTTPACTION: <method>,<statuscode>,<datalen>** 2)If parameter format is right:and the method is 20 Write Command **OK AT+HTTPACTION=<method> +HTTPACTION: <method>,<statuscode>,<recvlen/times>** 3)If parameter format is right but server connected unsuccessfully: **OK +HTTPACTION: <method>,<errcode>,<datalen>** 4)If parameter format is not right or other errors occur: **ERROR** - Parameter Saving Mode Max Response Time 120000ms Reference -

#### 16.2.4.1 Defined Values

|Parameter|Description|
|---|---|
|**<method>**|HTTP method specification: 0 GET 1 POST 2 HEAD 3 DELETE 4 PUT ||5<br>PATCH<br>20 DOWNSPEED| |---|---| ||
|**<statuscode>**||Please refer to the end of this chapter| ||
|**<datalen>**||The length of data received| ||
|**<recvlen/times>**||recvlen(byte): the length of all data received<br>times(ms): the time it takes to receive all the data||

#### 16.2.4.2 Examples

**AT+HTTPACTION=? +HTTPACTION: (0-4,20)**

**OK AT+HTTPACTION=0 OK +HTTPACTION: 0,200,104220 AT+HTTPACTION=20**

**OK**

**+HTTPACTION: 20,200,402297/905**

### 16.2.6 AT+HTTPHEAD Read the HTTP Header Information of Server Response

AT+HTTPHEAD is used to read the HTTP header information of server response when module receives the response data from server.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+HTTPHEAD=?**|**OK**<br>Response<br>1)If read the header information successfully:|
|Execute Command|**AT+HTTPHEAD**|**+HTTPHEAD: <data_len>**<br>**<data>**<br>**OK**<br>2)If read failed:<br>**ERROR**|
|Parameter Saving Mode|-||
|Max Response Time|120000ms||
|Reference|-||

#### 16.2.6.1 Defined Values

|**Defined Values**||
|---|---|
|**<data_len>**|The length of HTTP header|
|**<data>**|The header information of HTTP response|

#### 16.2.6.2 Examples

**AT+HTTPHEAD +HTTPHEAD: 653 HTTP/1.1 200 OK Content-Type: text/html Connection: keep-alive X-Cache: MISS from PDcache-04:opinion.people.com.cn Date: Tue, 24 Mar 2020 03:12:09 GMT Powered-By-ChinaCache: HIT from CNC-WB-b-D24 Powered-By-ChinaCache: HIT from CNC-WV-b-D1C ETag: W/"5b7379f5-57e9" x-cc-via: CNC-WB-b-D24[H,1], CNC-WV-b-D1C[H,62] d-cc-upstream: CNC-WV-b-D1C CACHE: TCP_HIT Vary: Accept-Encoding Last-Modified: Wed, 15 Aug 2018 00:55:17 GMT Expires: Tue, 24 Mar 2020 03:17:09 GMT x-cc-req-id: f4b9e1793697d1ef2950f530aeec4519 Content-Length: 22505 Age: 0 Accept-Ranges: bytes Server: nginx X-Frame-Options: ALLOW-FROM .* CC_CACHE: TCP_REFRESH_HIT OK**

### 16.2.7 AT+HTTPREAD Read the response information of HTTP Server

After sending HTTP(S)GET/POST requests, you can retrieve HTTP(S)response information from HTTP(S) server via UART/USB port by AT+HTTPREAD. When the <datalen> of "+HTTPACTION: <method>,<statuscode>,<datalen>" is not equal to 0, You can execute

AT+HTTPREAD=<start_offset>,<byte_size> to read out data to port. If parameter <byte_size> is set greater than the size of data saved in buffer, all data in cache will output to port.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+HTTPREAD=?**|**OK**<br>Response|
|Read Command|1)If check successfully:<br>**AT+HTTPREAD?**<br>**+HTTPREAD: LEN,<len>**<br>**OK**||

(If server response type is chunked , The length of the data is unknown,so this will response ERROR )

2)If failed (no more data other error): **ERROR** Response 1)If read the response info successfully: **OK**

Write Command

**+HTTPREAD: <data_len>**

**AT+HTTPREAD=[<start_offset>, <data> ]<byte_size>**

**+HTTPREAD: 0**

If <byte_size> is bigger than the data size received, module will only return actual data size.

2)If read failed: **ERROR** - Parameter Saving Mode Max Response Time 120000ms Reference -

#### 16.2.7.1 Defined Values

|Parameter|Description|
|---|---|
|**<start_offset>**|The start position of reading|
|**<byte_size>**|The length of data to read|
|**<data_len>**|The actual length of read data|
|**<data>**|Response content from HTTP server|
|**<len>**|Total size of data saved in buffer.|

#### 16.2.7.2 Examples

**AT+HTTPREAD?**

**+HTTPREAD: LEN,22505**

**OK**

**AT+HTTPREAD=0,500 OK**

**+HTTPREAD: 500**

**\0\0\0\0\0\0\0\0\0\0\0\0\0\0<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"> <html xmlns="http://www.w3.org/1999/xhtml">**

**<head>**

**<meta http-equiv="content-type" content="text/html;charset=GB2312"/>**

**<meta http-equiv="Content-Language" content="utf-8" />**

**<meta content="all" name="robots" />**

**<title>** 人民日报钟声 **:** 牢记历史是为了更好开创未来 **--** 观点 **--** 人民网 **</title>**

**<meta name="keywords" content="" />**

**<meta name="description" content="** 日方应在正确对待历史 **?**

**+HTTPREAD: 0**

The response content received from server will be saved in cache, and would not be cleaned up by AT+HTTPREAD.

If server response type is chunked, The length of the data is unknown,In this case, the data is read while downloading by Write Command , if Write Command response +HTTPREAD: 0 It means that the data has been successfully read end.

### 16.2.8 AT+HTTPDATA Input HTTP Data

You can use AT+HTTPDATA to input data to post when you send a HTTP/HTTPS POST request.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+HTTPDATA=?**|**OK**<br>Response<br>1)if parameter format is right:<br>**DOWNLOAD**<br>**<input data here>**|
|Write Command|**AT+HTTPDATA=<size>,<time>**|When the total size of the inputted data reaches <size>, TA will<br>report the following code. Otherwise, the serial port will be<br>blocked.<br>**OK**<br>2)If parameter format is wrong or other errors occur:<br>**ERROR**|
|Parameter Saving Mode|||
|Max Response Time|||
|Reference|||

#### 16.2.8.1 Defined Values

|**<size>**|Size in bytes of the data to post. range is 1- 153600 (bytes)|
|---|---|
|**<time>**|Maximum time in seconds to input data.range is 10-65535|

#### 16.2.8.2 Examples

**AT+HTTPDATA=18,1000 DOWNLOAD Message=helloworld OK**

### 16.2.9 AT+HTTPPOSTFILE Send HTTP Request to HTTP(S) server by File

You also can send HTTP request in a file via AT+HTTPPOSTFILE command. The URL must be set by AT+HTTPPARA before executing AT+HTTPPOSTFILE command. The parameter <path> can be used to set the file directory. When modem has received response from HTTP server, it will report the following URC:

+HTTPPOSTFILE: <statuscode>,<datalen>

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+HTTPPOSTFILE: <filename>[,(1-2)[,(0-4)[,(0-1)]]]**<br>**AT+HTTPPOSTFILE=?**<br>**OK**|1)if parameter format is right and server connected successfully:<br>a)if parameter <method> is valid:<br>**OK**<br>**+HTTPPOSTFILE: <method>,<statuscode>,<datalen>**<br>(If server response type is chunked|
|Write Command|**+ HTTPPOSTFILE: <method>,<statuscode>,chunk**)<br>**AT+HTTPPOSTFILE=<filename>**<br>**[,<path>[,<method>[,<send_hea**<br>b)if parameter <method> is ignored:<br>**der>]]]**<br>**OK**<br>**+HTTPPOSTFILE: <statuscode>,<datalen>**<br>(If server response type is chunked<br>**+ HTTPPOSTFILE: <statuscode>,chunk**)<br>2)if parameter format is right but server connected unsuccessfully:<br>a)ifparameter <method> is valid:||

**OK**

**+HTTPPOSTFILE: <method>,<errcode>,0**

b)if parameter <method> is ignored:

**OK**

**+HTTPPOSTFILE: <errcode>,0**

3)if parameter format is not right or any other error occurs: **ERROR**

Parameter Saving Mode Max Response Time Reference

#### 16.2.9.1 Defined Values

|Parameter|Description|
|---|---|
|**<filename>**|String type, filename, the max length is 112.unit:byte.|
|**<path>**|The directory where the sent file saved. Numeric type, range is 1-2 1 C:/ (local storage) 2 D:/(sd card)|
|**<method>**|HTTP method specification: 0 GET 1 POST 2 HEAD 3 DELETE 4 PUT If this value is not provided, it is same to the value described in the post file.|
|**<send_header>**|Send file as HTTP header and Body or Only as Body. Numeric type, the range is 0-1, the default is 0. 1 Send file as Body 0 Send file as HTTP header and body|
|**<statuscode>**|Please refer to the end of this chapter|
|**<datalen>**|The length of data received|

#### 16.2.9.2 Examples

**AT+HTTPPOSTFILE=? +HTTPPOSTFILE: <filename>[,(1-2)[,(0-4)[,(0-1)]]]**

**OK AT+HTTPPOSTFILE="getbaidu.txt",1 OK**

**+HTTPPOSTFILE: 200,14615 AT+HTTPPOSTFILE="getbaidu.txt",1,1,1 OK**

**+HTTPPOSTFILE: 1,200,14615**

### 16.2.10 AT+HTTPREADFILE Receive HTTP Response Content to a file

After execute AT+HTTPACTION/AT+HTTPOSTFILE command. You can receive the HTTP server response content to a file via AT+HTTPREADFILE.

Before AT+HTTPREADFILE executed, "+HTTPACTION: <method>,<statuscode>,<datalen>" or

"+HTTPPOSTFILE: <statuscode>,<datalen>" must be received. The parameter <path> can be used to set the directory where to save the file. If omit parameter <path>, the file will be save to local storage.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+HTTPREADFILE: <filename>[,(1-2)]**<br>**AT+HTTPREADFILE=?**<br>**OK**|1)if parameter format is right:<br>**OK**|
|Write Command|**+HTTPREADFILE: <errcode>**<br>**AT+HTTPREADFILE=<filename**<br>2)if failed:<br>**>[,<path>]**<br>**OK**<br>**+HTTPREADFILE: <errcode>**<br>3)if parameter format is not right or any other error occurs:<br>**ERROR**||
|Parameter Saving Mode|||
|Max Response Time|||
|Reference|||

#### 16.2.10.1 Defined Values

|**Defined Values**||
|---|---|
|**<filename>**|String type, filename, the max length is 112.unit:byte.|
|**<path>**|The directory where the read file saved. Numeric type, range is 1-2.<br>1<br>C:/(local storage)<br>2<br>D:/(sd card)|

#### 16.2.10.2 Examples

**AT+HTTPREADFILE=? +HTTPREADFILE: <filename>[,(1-2)]**

**OK AT+HTTPREADFILE="readbaidu.dat" OK**

**+HTTPREADFILE: 0**

## 16.3 Command Result Codes

### 16.3.1 Description of <statuscode>

|**<statuscode>**<br>**Description**|**<statuscode>**<br>**Description**|
|---|---|
|**100**|Continue|
|**101**|Switching Protocols|
|**200**|OK|
|**201**|Created|
|**202**|Accepted|
|**203**|Non-Authoritative Information|
|**204**|No Content|
|**205**|Reset Content|
|**206**|Partial Content|
|**300**|Multiple Choices|
|**301**|Moved Permanently|
|**302**|Found|
|**303**|See Other|
|**304**|Not Modified|
|**305**|Use Proxy|
|**307**|TemporaryRedirect|
|**400**|Bad Request|
|**401**|Unauthorized|
|**402**|Payment Required|
|**403**|Forbidden|

|**404**|Not Found|
|---|---|
|**405**|Method Not Allowed|
|**406**|Not Acceptable|
|**407**|Proxy Authentication Required|
|**408**|Request Timeout|
|**409**|Conflict|
|**410**|Gone|
|**411**|Length Required|
|**412**|Precondition Failed|
|**413**|Request EntityToo Large|
|**414**|Request-URI Too Large|
|**415**|Unsupported Media Type|
|**416**|Requested range not satisfiable|
|**417**|Expectation Failed|
|**500**|Internal Server Error|
|**501**|Not Implemented|
|**502**|Bad Gateway|
|**503**|Service Unavailable|
|**504**|Gateway timeout|
|**505**|HTTP Version not supported|
|**600**|Not HTTP PDU|
|**601**|Network Error|
|**602**|No memory|
|**603**|DNS Error|
|**604**|Stack Busy|

**16.3.2 Description of <errcode>**

|**<errcode>**<br>**Meaning**|**<errcode>**<br>**Meaning**|
|---|---|
|**0**|Success|
|**701**|Alert state|
|**702**|Unknown error|
|**703**|Busy|
|**704**|Connection closed error|
|**705**|Timeout|
|**706**|Receive/send socket data failed|
|**707**|File not exists or other memory error|
|**708**|Invalid parameter|
|**709**|Network error|

|**710**|start a new ssl session failed|
|---|---|
|**711**|Wrongstate|
|**712**|Failed to create socket|
|**713**|Get DNS failed|
|**714**|Connect socket failed|
|**715**|Handshake failed|
|**716**|Close socket failed|
|**717**|No network error|
|**718**|Send data timeout|
|**719**|CA missed|

## 16.4 Unsolicited Result Codes

|**URC**<br>**Description**|**URC**<br>**Description**|
|---|---|
|**+HTTP_PEER_CLOSED**|It’s a notification message. While received, it means the<br>connection has been closed byserver.|
|**+HTTP_NONET_EVENT[,cid]**|It’s a notification message. While received, it means now the<br>network is unavailable. If using AT+HTTPINIT=<cid>to start HTTP,<br>the URC carries the cid parameter|

<!-- Source file: 1 8 AT Commands for MQTT(S) - marked only.md -->

# 18 AT Commands for MQTT(S)

## 18.1 Overview of AT Commands for MQTT(S)

|**Command**|**Description**|
|---|---|
|**AT+CMQTTSTART**|Start MQTT service|
|**AT+CMQTTSTOP**|Stop MQTT service|
|**AT+CMQTTACCQ**|Acquire a client|
|**AT+CMQTTREL**|Release a client|
|**AT+CMQTTSSLCFG**|Set the SSL context (only for SSL/TLS MQTT)|
|**AT+CMQTTCONNECT**|Connect to MQTT server|
|**AT+CMQTTDISC**|Disconnect from server|
|**AT+CMQTTPUB**|Publish a message to server|
|**AT+CMQTTSUB**|Subscribe a message to server|
|**AT+CMQTTCFG**|Configure the MQTT Context|

## 18.2 Detailed Description of AT Commands for MQTT(S)

### 18.2.1 AT+CMQTTSTART Start MQTT service

AT+CMQTTSTART is used to start MQTT service by activating PDP context. You must execute this command before any other MQTT related operations.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CMQTTSTART=?**|**+CMQTTSTART: (1-n)**<br>**OK**|
|Execute Command|**AT+CMQTTSTART**|1)If start MQTT service successfully:<br>**OK**<br>**+CMQTTSTART: 0**<br>2)If failed:<br>**OK**<br>**+CMQTTSTART: <err>**<br>3)If MQTT service have started successfully and you executed<br>AT+CMQTTSTART again:<br>**ERROR**|
|Write Command|**AT+CMQTTSTART=<cid>**|1)<br>**OK**<br>**+CMQTTSTART: <err>,<cid>**<br>2)<br>**ERROR**|
|Max Response Time|12000ms||
|Parameter Saving Mode|-||
|Reference|||

#### 18.2.1.1 Defined Values

|**<cid>**|A numeric parameter which specifies a particular PDP context .The<br>range is 1-n,The maximum value n is related to the pdp command of<br>the modem.|
|---|---|
|**<err>**|The result code, please refer to Chapter 18.3|

#### 18.2.1.2 Examples

**AT+CMQTTSTART**

**OK**

**+CMQTTSTART: 0**

AT+CMQTTSTART is used to start MQTT service by activating PDP context. You must execute this command before any other MQTT related operations.

If you don’t execute AT+CMQTTSTART, the Write/Read Command of any other MQTT will return ERROR immediately.

### 18.2.2 AT+CMQTTSTOP Stop MQTT service

AT+CMQTTSTOP is used to stop MQTT service.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CMQTTSTOP: (1-n)**<br>**AT+CMQTTSTOP=?**<br>**OK**|1)If stop MQTT service successfully:<br>**OK**<br>**+CMQTTSTOP: 0**|
|Execute Command|2)If failed:<br>**AT+CMQTTSTOP**<br>**+CMQTTSTOP: <err>**<br>**ERROR**<br>3)If MQTT service have stopped successfully and you executed<br>AT+CMQTTSTOP again:<br>**ERROR**|1)<br>**OK**|
|Write Command|**AT+CMQTTSTOP=<cid>**<br>**+CMQTTSTOP: <err>,<cid>**<br>2)<br>**ERROR**||
|Max Response Time|12000ms||
|Parameter Saving Mode|-||
|Reference|||

#### 18.2.2.1 Defined Values

|**Defined Values**||
|---|---|
|**<cid>**|A numeric parameter which specifies a particular PDP context .The<br>range is 1-n,The maximum value n is related to the pdp command of<br>the modem.|
|**<err>**|The result code, please refer to chapter 18.3|

#### 18.2.2.2 Examples

**AT+CMQTTSTOP**

**OK**

**+CMQTTSTOP: 0**

AT+CMQTTSTOP is used to stop MQTT service. You can execute this command after AT+CMQTTDISC and AT+CMQTTREL.

### 18.2.3 AT+CMQTTACCQ Acquire a client

AT+CMQTTACCQ is used to acquire a MQTT client. It must be called before all commands about MQTT connect and after AT+CMQTTSTART.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CMQTTACCQ=?**|**+CMQTTACCQ: (0-1),(1-128)[,(0-1)]**<br>**OK**|
|Read Command|**AT+CMQTTACCQ?**|**+CMQTTACCQ: <client_index>,<clientID>,<server_type>**<br>**OK**|
|Write Command|**AT+CMQTTACCQ=<client_index>,<clientID>[,<server_type>]**|1)If successfully:<br>**OK**<br>2)If failed:<br>**+CMQTTACCQ: <client_index>,<err>**|

**ERROR** 3)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 18.2.3.1 Defined Values

|Parameter|Description|
|---|---|
|**<client_index>**|A numeric parameter that identifies a client. The range of permitted values is 0 to 1.|
|**<clientID>**|The UTF-encoded string. It specifies a unique identifier for the client. The string length is from 1 to 128 bytes.|
|**<server_type>**|A numeric parameter that identifies the server type. The default value is 0. 0 MQTT server with TCP 1 MQTT server with SSL/TLS|
|**<err>**|The result code, please refer to chapter 18.3|

#### 18.2.3.2 Examples

**AT+CMQTTACCQ=0,"a12mmmm",0 OK**

**AT+CMQTTACCQ?**

**+CMQTTACCQ: 0,"a12mmmm",0**

**+CMQTTACCQ: 1,"",0**

**OK AT+CMQTTACCQ=? +CMQTTACCQ: (0-1),(1-128)[,(0-1)] OK**

### 18.2.4 AT+CMQTTREL Release a client

AT+CMQTTREL is used to release a MQTT client. It must be called after AT+CMQTTDISC and before

AT+CMQTTSTOP.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CMQTTREL=?**|**+CMQTTREL: (0-1)**<br>**OK**|
|Read Command|**AT+CMQTTREL?**|1)If successfully:<br>**OK**<br>2)if MQTT not start<br>**ERROR**|
|Write Command|**AT+CMQTTREL=<client_index>**|1)If successfully:<br>**OK**<br>2)If failed:<br>**+CMQTTREL: <client_index>,<err>**<br>**ERROR**<br>3)If failed:<br>**ERROR**|
|Parameter Saving Mode|-||
|Max Response Time|-||
|Reference|||

#### 18.2.4.1 Defined Values

|**<client_index>**|A numeric parameter that identifies a client. The range of permitted<br>values is 0 to 1.|
|---|---|
|**<err>**|The result code, please refer to chapter 18.3|

#### 18.2.4.2 Examples

**AT+CMQTTREL=? +CMQTTREL: (0-1)**

**OK AT+CMQTTREL=0 OK AT+CMQTTREL? OK**

### 18.2.5 AT+CMQTTSSLCFG Set the SSL context (only for SSL/TLS MQTT)

AT+CMQTTSSLCFG is used to set the SSL context which to be used in the SSL connection when it will connect to a SSL/TLS MQTT server. It must be called before AT+CMQTTCONNECT and after AT+CMQTTSTART. The setting will be cleared after AT+CMQTTCONNECT failed or AT+CMQTTDISC.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CMQTTSSLCFG=?**|**+CMQTTSSLCFG: (0,1),(0-9)**<br>**OK**|
|Read Command|**AT+CMQTTSSLCFG?**|**+CMQTTSSLCFG: <session_id>,[<ssl_ctx_index>]**<br>**OK**|
|Write Command|**AT+CMQTTSSLCFG=<sessio**<br>**n_id>,<ssl_ctx_index>**|1)If successfully:<br>**OK**<br>2)If failed:<br>**ERROR**|
|Parameter Saving Mode|-||
|Max Response Time|-||
|Reference|-||

#### 18.2.5.1 Defined Values

|**Defined Values**||
|---|---|
|**<session_id>**|The session_id to operate. It’s from 0 to 1|
|**<ssl_ctx_index>**|The SSL context ID which will be used in the SSL connection. Refer to<br>the <ssl_ctx_index> of AT+CSSLCFG|

#### 18.2.5.2 Examples

**AT+CMQTTSSLCFG? +CMQTTSSLCFG: 0,0 +CMQTTSSLCFG: 1,0**

**OK**

**AT+CMQTTSSLCFG=?**

**+CMQTTSSLCFG: (0,1),(0-9)**

**OK**

**AT+CMQTTSSLCFG=0,1 OK**

### 18.2.8 AT+CMQTTCONNECT Connect to MQTT server

AT+CMQTTCONNECT is used to connect to a MQTT server.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CMQTTCONNECT=?**|**+CMQTTCONNECT:**<br>**(0-1),(9-256),(1-64800),(0-1)[,<user_name>,<pass_word>]**<br>**OK**|
|Read Command|**AT+CMQTTCONNECT?**|**+CMQTTCONNECT:**<br>**0[,<server_addr>,<keepalive_time>,<clean_session>[,<user_na**<br>**me>[,<pass_word>]]]**<br>**+CMQTTCONNECT:**<br>**1[,<server_addr>,<keepalive_time>,<clean_session>[,<user_na**<br>**me>[,<pass_word>]]]**<br>**OK**|
|Write Command|**AT+CMQTTCONNECT=<clien**<br>**t_index>,<server_addr>,<kee**<br>**palive_time>,<clean_session**<br>**>[,<user_name>[,<pass_word**<br>**>]]**|1)If successfully:<br>**OK**<br>**+CMQTTCONNECT: <client_index>,0**<br>2)If failed:<br>**OK**<br>**+CMQTTCONNECT: <client_index>,<err>**<br>3)If failed:<br>**ERROR**<br>**+CMQTTCONNECT: <client_index>,<err>**<br>4)If failed:<br>**+CMQTTCONNECT: <client_index>,<err>**<br>**ERROR**|

5)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 18.2.8.1 Defined Values

|Parameter|Description|
|---|---|
|**<client_index>**|values is 0 to 1. The string that described the server address and port. The range of the string length is 9 to 256 bytes. The string should be like this|
|**<server_addr>**|"tcp://116.247.119.165:5141", must begin with "tcp://". If the <server_addr> not include the port, the default port is 1883. The time interval between two messages received from a client. The client will send a keep-alive packet when there is no message sent to|
|**<keepalive_time>**|server after song long time. The range is from 1s to 64800s (18 hours). The clean session flag. The value range is from 0 to 1, and default value is 0. 0 the server must store the subscriptions of the client after it disconnected. This includes continuing to store QoS 1 and QoS 2 messages for the subscribed topics so that they can be delivered when the client reconnects. The server must also|
|**<clean_session>**|maintain the state of in-flight messages being delivered at the point the connection is lost. This information must be kept until the client reconnects. 1 the server must discard any previously maintained information about the client and treat the connection as "clean". The server must also discard any state when the client disconnects. The user name identifies the name of the user which can be used for|
|**<user_name>**|authentication when connecting to server. The string length is from 1 to 256 bytes. The password corresponding to the user which can be used for|
|**<pass_word>**|authentication when connecting to server. The string length is from 1 to 256 bytes. The result code: 0 is success. Other values are failure. Please refer to|
|**<err>**|chapter 18.3.|

#### 18.2.8.2 Examples

**AT+CMQTTCONNECT=0,"tcp://120.27.2.154:1883",20,1 OK**

**+CMQTTCONNECT: 0,0 AT+CMQTTCONNECT?**

**+CMQTTCONNECT: 0,"tcp://120.27.2.154:1883",20,1 +CMQTTCONNECT: 1**

**OK**

AT+CMQTTCONNECT is used to connect to a MQTT server.

If you don’t set the SSL context by AT+CMQTTSSLCFG before connecting a SSL/TLS MQTT server by AT+CMQTTCONNECT, it will use the <client_index> (the 1st parameter of AT+CMQTTCONNNECT)SSL context when connecting to the server.

### 18.2.9 AT+CMQTTDISC Disconnect from server

AT+CMQTTDISC is used to disconnect from the server.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CMQTTDISC=?**<br>Response:<br>**+CMQTTDISC: (0-1),(0,1-180)**<br>**OK**||
|Read Command|**AT+CMQTTDISC?**<br>Response:<br>**+CMQTTDISC: 0,<disc_state>**<br>**+CMQTTDISC: 1,<disc_state>**<br>**OK**||
|Write Command|**AT+CMQTTDISC=<client_in**<br>**dex>[,<timeout>]**|1)If disconnect successfully:<br>**+CMQTTDISC: <client_index>,0**<br>**OK**<br>2)If disconnect successfully:<br>**OK**<br>**+CMQTTDISC: <client_index>,0**<br>3)If failed:<br>**OK**|

**+CMQTTDISC: <client_index>,<err>** 4)If failed: **ERROR** 5)If failed: **+CMQTTDISC: <client_index>,<err> ERROR** - Parameter Saving Mode - Max Response Time Reference

#### 18.2.9.1 Defined Values

|**Defined Values**||
|---|---|
|**<client_index>**|A numeric parameter that identifies a client. The range of permitted<br>values is 0 to 1.|
|**<timeout>**|The timeout value for disconnection. The unit is second. The range is<br>1s to 180s. The default value is 0s(not set the timeout value).|
|**<disc_state>**|1<br>disconnection<br>0<br>connection|
|**<err>**|The result code: 0 is success. Other values are failure. Please refer to<br>chapter 18.3.|

#### 18.2.9.2 Examples

**AT+CMQTTDISC=0,120 OK**

**+CMQTTDISC: 0,0**

### 18.2.12 AT+CMQTTPUB Publish a message to server

AT+CMQTTPUB is used to publish a message to MQTT server.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CMQTTPUB: (0-1),(0-2),(1-180),(0-1),(0-1)**<br>**AT+CMQTTPUB=?**<br>**OK**|1)If successfully:<br>**OK**<br>**+CMQTTPUB: <client_index>,0**|
|Write Command|2)If failed:<br>**OK**<br>**AT+CMQTTPUB=<client_ind**<br>**ex>,<qos>,<pub_timeout>[,<**<br>**ratained>[,<dup>]]**<br>**+CMQTTPUB: <client_index>,<err>**<br>3)If failed:<br>**+CMQTTPUB: <client_index>,<err>**<br>**ERROR**<br>4)If failed:<br>**ERROR**||
|Parameter Saving Mode|-||
|Max Response Time|-||
|Reference|||

#### 18.2.12.1 Defined Values

|**Defined Values**||
|---|---|
|**<client_index>**|A numeric parameter that identifies a client. The range of permitted<br>values is 0 to 1.|
|**<qos>**|The publish message’s qos. The range is from 0 to 2.<br>0<br>at most once<br>1<br>at least once<br>2<br>exactlyonce|
|**<pub_timeout>**|The publishing timeout interval value. Since the client publish a<br>message to server, it will report failed if the client receive no response<br>from server after the timeout value seconds. The range is from 1s to<br>180s.|
|**<ratained>**|The retain flag of the publish message. The value is 0 or 1. The default<br>value is 0.<br>When a client sends a PUBLISH to a server,if the retain flagis set to|

||1, the server should hold on to the message after it has been delivered<br>to the current subscribers.|
|---|---|
|**<dup>**|The dup flag to the message. The value is 0 or 1. The default value is<br>0. The flag is set when the client or server attempts to re-deliver a<br>message.|
|**<err>**|The result code: 0 is success. Other values are failure. Please refer to<br>chapter 18.3.|

#### 18.2.12.2 Examples

**AT+CMQTTPUB=0,1,60 OK**

**+CMQTTPUB: 0,0**

The topic and payload will be clean after execute AT+CMQTTPUB.

### 18.2.14 AT+CMQTTSUB Subscribe a message to server

AT+CMQTTSUB is used to subscribe a message to MQTT server.

|**AT+CMQTTSUB**|**Subscribe a message to server**|
|---|---|
||Response|
|Test Command|**+CMQTTSUB: (0-1),(1-1024),(0-2),(0-1)**|
|**AT+CMQTTSUB=?**||
||**OK**|

|Type|Command / Value|Response / Notes|
|---|---|---|
|Read Command|**+CMQTTSUB:**<br>**AT+CMQTTSUB?**<br>**[<topic>]**<br>**OK**|1)If successfully:<br>**OK**|
|Write Command|**+CMQTTSUB: <client_index>,0**<br>/* subscribe one or more topics<br>2)If failed:<br>**OK**<br>which input by<br>AT+CMQTTSUBTOPIC*/<br>**AT+CMQTTSUB=<client_ind**<br>**ex>[,<dup>]**<br>**+CMQTTSUB: <client_index>,<err>**<br>3)If failed:<br>**+CMQTTSUB: <client_index>,<err>**<br>**ERROR**<br>4)If failed:<br>**ERROR**|1)If successfully:<br>**>**<br>**<input data here>**<br>**OK**|
|Write Command|**+CMQTTSUB: <client_index>,0**<br>/* subcribe one topic*/<br>2)If failed:<br>**AT+CMQTTSUB=<client_ind**<br>**OK**<br>**ex>,<reqLength>,<qos>[,<d**<br>**up>]**<br>**+CMQTTSUB: <client_index>,<err>**<br>3)If failed:<br>**+CMQTTSUB: <client_index>,<err>**<br>**ERROR**<br>4)If failed:<br>**ERROR**||
|Parameter Saving Mode|-||
|Max Response Time|-||
|Reference|-||

#### 18.2.14.1 Defined Values

|**<client_index>**|A numeric parameter that identifies a client. The range of permitted<br>values is 0 to 1.|
|---|---|

|**<req_length>**|The length of input topic data. The message topic should be<br>UTF-encoded string. The range is from 1 to 1024 bytes.|
|---|---|
|**<qos>**|The publish message’s qos. The range is from 0 to 2.<br>0<br>at most once<br>1<br>at least once<br>2<br>exactlyonce|
|**<dup>**|The dup flag to the message. The value is 0 or 1. The default value is<br>0. The flag is set when the client or server attempts to re-deliver a<br>message.|
|**<err>**|The result code: 0 is success. Other values are failure. Please refer to<br>chapter 18.3.|
|**<topic>**|Topics to which you have subscribed|

#### 18.2.14.2 Examples

**AT+CMQTTSUB=0,9,1 > OK +CMQTTSUB: 0,0 AT+CMQTTSUB=0,1 OK +CMQTTSUB: 0,0**

The topic will be clean after execute AT+CMQTTSUB.

### 18.2.17 AT+CMQTTCFG Configure the MQTT Context

AT+CMQTTCFG is used to configure the MQTT context. It must be called before AT+CMQTTCONNECT and after AT+CMQTTACCQ. The setting will be cleared after AT+CMQTTREL.

**AT+CMQTTCFG Configure the MQTT Context**

||Response|
|---|---|
||**+CMQTTCFG: "checkUTF8",(0-1),(0-1)**|
||**+CMQTTCFG: "optimeout ",(0-1),(20-120)**|
|Test Command|**+CMQTTCFG:**|
|**AT+CMQTTCFG=?**|**"aliauth",(0-1),"productkey","devicename","devicesecret"**|
||**+CMQTTCFG: "version",(0-1),(3-4)**|
||**+CMQTTCFG: "argtopic",(0-1),(0-1),(0-1)**|

**OK**

Read Command **AT+CMQTTCFG?**

Response **+CMQTTCFG: 0,<checkUTF8_flag>,<optimeout_val> +CMQTTCFG: 1,<checkUTF8_flag>,<optimeout_val>**

**OK**

Write Command /*Configure the check UTF8 flag of the specified MQTT client context*/ **AT+CMQTTCFG="checkUTF 8",<index>,<checkUTF8_flag >**

Response 1)If successfully: **OK** 2)If failed: **ERROR**

Write Command

Response 1)If successfully: **OK** 2)If failed: **ERROR** Response 1) When <cid> is omitted: **+CMQTTCFG: "CID",<cid>**

/*Configure the max timeout interval of the send or receive data operation */ **AT+CMQTTCFG="optimeout ",<index>,<optimeout_val>**

**Write Command**

/*Configure the cid values of all clients when a connection is created*/ **AT+CMQTTCFG="CID"[,<cid >]**

**OK**

2) If the <cid> set successfully: **AT+CMQTTCFG="CID"[,<cid OK >]** 2)If failed: **ERROR** Response 1) When both the <index> and <cid> are omitted: **+CMQTTCFG: "SCID",0,<cid> +CMQTTCFG: "SCID",1,<cid>** Write Command /*Configure the cid value of the **OK** specified client when creating 2) When <cid> is omitted: a connection*/ **+ CMQTTCFG: "SCID",<index>,<cid> AT+CMQTTCFG="SCID"[,<in dex>][,<cid>] OK**

3)If successfully: **OK** 4)If failed: **ERROR** - Parameter Saving Mode - Max Response Time Reference -

#### 18.2.17.1 Defined Values

|**Defined Values**||
|---|---|
|**<index>**|A numeric parameter that identifies a client. The range of permitted<br>values is 0 to 1.|
|**<checkUTF8_flag>**|The flag to indicate whether to check the string is UTF8 coding or not,<br>the default value is 1.<br>0<br>Not check UTF8 coding.<br>1<br>Check UTF8 coding.|
|**<optimeout_val>**|The max timeout interval of sending or receiving data operation. The<br>range is from 20 seconds to 120 seconds, the default value is 120<br>seconds.|
|**+CMQTTCFG:**<br>**"aliauth",(0-1),"productkey"**<br>**,"devicename","devicesecr**<br>**et"**|(0-1): A numeric parameter that identifies a client. The range of<br>permitted values is 0 to 1.<br>"productkey": The string is productkey of Alibaba Cloud platform.<br>"devicename": The string is devicename of Alibaba Cloud platform.<br>"devicesecret": The stringis devicesecret of Alibaba Cloud platform.|
|**+CMQTTCFG:**<br>**"version",(0-1),(3-4)**|(0-1): A numeric parameter that identifies a client. The range of<br>permitted values is 0 to 1.<br>(3-4): Version of MQTT.<br>3<br>: MQTT 3.1. The default value is 3.<br>4: MQTT 3.1.1.|
|**+CMQTTCFG:**<br>**"argtopic",(0-1),(0-1),(0-1)**|The command is used to configure MQTT AT of extension, please<br>refer to “A76XX Series MQTT EX_Application Note_XXXX.docx”.<br>(0-1): A numeric parameter that identifies a client. The range of<br>permitted values is 0 to 1.<br>(0-1):The flag to enable whether to show length of received.<br>0:<br>Not show length of received.<br>1: Show length of received.<br>(0-1):A numeric parameter that identifies report payload length.<br>0<br>: Notify PUB message without payload length.<br>1: NotifyPUB message withpayload length.|
|**<cid>**|A numeric parameter which specifies a particular PDP context .The<br>range is 1-n,The maximum value n is related to the pdp command of<br>the modem.<br>If neither <session_id> nor <cid> is set, the cid of all sessions are<br>queried, If <cid> is not set, the cid of the current session is queried,<br>and the default value of cid is 1.|

#### 18.2.17.2 Examples

**AT+CMQTTCFG? +CMQTTCFG: 0,1,120 +CMQTTCFG: 1,1,120**

**OK**

**AT+CMQTTCFG="optimeout",0,24 OK AT+CMQTTCFG="checkUTF8",0,0 OK**

**AT+CMQTTCFG?**

**+CMQTTCFG: 0,0,24**

**+CMQTTCFG: 1,1,120**

**OK**

The setting will be cleared after AT+CMQTTREL.

## 18.3 Command Result Codes

### 18.3.1 Description of <err>

|**<err>**<br>**Description**|**<err>**<br>**Description**|
|---|---|
|**0**|operation succeeded|
|**1**|failed|
|**2**|bad UTF-8 string|
|**3**|sock connect fail|
|**4**|sock create fail|
|**5**|sock close fail|
|**6**|message receive fail|
|**7**|network open fail|
|**8**|network close fail|
|**9**|network not opened|
|**10**|client index error|
|**11**|no connection|
|**12**|invalid parameter|
|**13**|not supported operation|

|**14**|client is busy|
|---|---|
|**15**|require connection fail|
|**16**|sock sending fail|
|**17**|timeout|
|**18**|topic is empty|
|**19**|client is used|
|**20**|client not acquired|
|**21**|client not released|
|**22**|length out of range|
|**23**|network is opened|
|**24**|packet fail|
|**25**|DNS error|
|**26**|socket is closed by server|
|**27**|connection refused: unaccepted protocol version|
|**28**|connection refused: identifier rejected|
|**29**|connection refused: server unavailable|
|**30**|connection refused: bad user name or password|
|**31**|connection refused: not authorized|
|**32**|handshake fail|
|**33**|not set certificate|
|**34**|Open session failed|
|**35**|Disconnect from server failed|

## 18.4 Unsolicited Result Codes

|**URC**<br>**Description**|**URC**<br>**Description**|
|---|---|
|**+CMQTTCONNLOST: <client_index>,<cause>**|When client disconnect passively,<br>URC "+CMQTTCONNLOST" will be<br>reported, then user need to connect<br>MQTT server again.|
|**+CMQTTNONET**|When the network is become no<br>network, the module will report this<br>URC.<br>If received this message, you<br>should restart the MQTT service by<br>AT+CMQTTSTART.|
|**+CMQTTRXSTART:**<br>**<client_index>,<topic_total_len>,<payload_total_len>**<br>**+CMQTTRXTOPIC: <client_index>,<sub_topic_len>**|If a client subscribes to one or more<br>topics, any message published to<br>those topics are sent by the server|

|**<sub_topic>**<br>**+CMQTTRXPAYLOAD: <client_index>,<sub_payload_len>**<br>**<sub_payload>**<br>**+CMQTTRXEND: <client_index>**|to the client. The following URC is<br>used for transmitting the message<br>published from server to client.<br>1)+CMQTTRXSTART:<br><client_index>,<topic_total_len>,<p<br>ayload_total_len>\r\n<br>At the beginning of receiving<br>published message, the module will<br>report this to user, and indicate<br>client index with <client_index>, the<br>topic total length with<br><topic_total_len> and the payload<br>total length with<br><payload_total_len> after "\r\n".<br>2)+CMQTTRXTOPIC:<br><client_index>,<sub_topic_len>\r\n<br><sub_topic><br>After the command<br>"+CMQTTRXSTART" received, the<br>module will report the second<br>message to user, and indicate client<br>index with <client_index>, the topic<br>packet length with <sub_topic_len><br>and the topic content with<br><sub_topic> after "\r\n".<br>3)+CMQTTRXPAYLOAD:<br><client_index>,<sub_payload_len>\<br>r\n<sub_payload><br>After the command<br>"+CMQTTRXTOPIC" received, the<br>module will send third message to<br>user, and indicate client index with<br><client_index>, the payload packet<br>length with <sub_payload_len> and<br>the payload content with<br><sub_payload> after "\r\n".<br>4)+CMQTTRXEND: <client_index><br>At last, the module will send fourth<br>message to user and indicate the<br>topic and payload have been<br>transmitted completely.|
|---|---|

### 18.4.1 Defined Values

|**<client_index>**|A numeric parameter that identifies a client. The range of permitted|
|---|---|
||values is 0 to 1.|
|**<cause>**|The cause of disconnection.|
||1<br>Socket is closed passively.|
||2<br>Socket is reset.|
||3<br>Network is closed.|
|**<topic_total_len>**|The length of message topic received from MQTT server. The range is|
||from 1 to 1024 bytes.|
|**<payload_total_len>**|The length of message body received from MQTT server. The range is|
||from 1 to 10240 bytes.|
|**<sub_topic_len>**|The sub topic packet length, The sum of <sub_topic_len> is equal to|
||<topic_total_len>.|
|**<sub_topic>**|The sub topic content.|
|**<sub_payload_len>**|The sub message body packet length, The sum of <sub_payload_len>|
||is equal to <payload_total_len>.|
|**<sub_payload>**|The sub message body content.|

<!-- Source file: 1 9 AT Commands for SSL - marked only.md -->

# 19 AT Commands for SSL

## 19.1 Overview of AT Commands for SSL

|**Command**|**Description**|
|---|---|
|**AT+CSSLCFG**|Configure the SSL Context|

## 19.2 Detailed Description of AT Commands for SSL

### 19.2.1 AT+CSSLCFG Configure the SSL Context

|**AT+CSSLCFG**|**Configure the SSL Context**|
|---|---|
|Test Command|Response|
|**AT+CSSLCFG=?**|**+CSSLCFG: "sslversion",(0-9),(0-4)**|

**+CSSLCFG: "authmode",(0-9),(0-3) +CSSLCFG: "ignorelocaltime",(0-9),(0,1) +CSSLCFG: "negotiatetime",(0-9),(10-300) +CSSLCFG: "cacert",(0-9),(5-108) +CSSLCFG: "clientcert",(0-9),(5-108) +CSSLCFG: "clientkey",(0-9),(5-108) +CSSLCFG: "password",(0-9),(5-108) +CSSLCFG: "enableSNI",(0-9),(0,1) +CSSLCFG: "ignorecertCN",(0-9),(0,1)**

**OK**

||**OK**|
|---|---|
||Response|
||**+CSSLCFG:**|
||**0,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|
||**1,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|
||**2,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|
||**3,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
|Read Command|**eSNI_flag>,<ignorecertCN_flag>**|
|**AT+CSSLCFG?**|**+CSSLCFG:**|
||**4,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|
||**5,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|
||**6,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|
||**7,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca**|
||**_file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl**|
||**eSNI_flag>,<ignorecertCN_flag>**|
||**+CSSLCFG:**|

**8,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca _file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl eSNI_flag>,<ignorecertCN_flag> +CSSLCFG:**

**9,<sslversion>,<authmode>,<ignoreltime>,<negotiatetime>,<ca _file>,<clientcert_file>,<clientkey_file>,<password_file>,<enabl eSNI_flag>,<ignorecertCN_flag>**

**OK**

Response

**Write Command**

/*Query the configuration of the specified SSL context*/ **AT+CSSLCFG=<ssl_ctx_inde x>**

**+CSSLCFG:**

**<ssl_ctxindex>,<sslversion>,<authmode>,<ignoreltime>,<nego tiatetime>,<ca_file>,<clientcert_file>,<clientkey_file>,<passwor d_file>,<enableSNI_flag>,<ignorecertCN_flag>**

**OK**

**Write Command**

/*Configure the version of the specified SSL context*/ **AT+CSSLCFG="sslversion",< ssl_ctx_index>,<sslversion>** Write Command

/*Configure the authentication mode of the specified SSL context*/ **AT+CSSLCFG="authmode",< ssl_ctx_index>,<authmode>** Write Command

/*Configure the ignore local time flag of the specified SSL context*/ **AT+CSSLCFG="ignorelocalti me",<ssl_ctx_index>,<ignorel time>**

Write Command

/*Configure the negotiate timeout value of the specified SSL context*/

**AT+CSSLCFG="negotiatetime ",<ssl_ctx_index>,<negotiatet ime>**

Write Command /*Configure the server root CA of the specified SSL context*/ **AT+CSSLCFG="cacert",<ssl_**

Response

1)If successfully:

**OK**

2)If failed:

**ERROR**

Response

1)If successfully:

**OK**

2)If failed: **ERROR**

Response

1)If successfully: **OK**

2)If failed: **ERROR**

Response

1)If successfully:

**OK**

2)If failed:

**ERROR**

Response

1)If successfully:

**OK**

2)If failed:

**ctx_index>,<ca_file> ERROR** Write Command Response /*Configure the client certificate 1)If successfully: of the specified SSL context*/ **OK AT+CSSLCFG="clientcert",<s** 2)If failed: **sl_ctx_index>,<clientcert_file ERROR >** Write Command Response /*Configure the client key of the 1)If successfully: specified SSL context*/ **OK AT+CSSLCFG="clientkey",<s** 2)If failed: **sl_ctx_index>,<clientkey_file> ERROR** Write Command Response /*Configure the password of the 1)If successfully: specified SSL context*/ **OK AT+CSSLCFG="password",<s** 2)If failed: **sl_ctx_index>,<password_file ERROR >** Write Command Response /*Configure the enableSNI flag 1)If successfully: of the specified SSL context */ **OK AT+CSSLCFG="enableSNI",<** 2)If failed: **ssl_ctx_index>,<enableSNI_fl ERROR ag>** Write Command Response /*Configure the ignorecertCN 1)If successfully: flag of the specified SSL context **OK** */ 2)If failed: **AT+CSSLCFG="ignorecertCN ERROR ",<ssl_ctx_index>,<ignorecert CN_flag>** Write Command Response /*Configure the use_tickets of 1)If successfully: the specified SSL context*/ **OK AT+CSSLCFG="use_tickets",** 2)If failed: **<ssl_ctx_index>,<use_tickets ERROR _flag>** - Parameter Saving Mode Max Response Time 120000ms Reference -

#### 19.2.1.1 Defined Values

|Parameter|Description|
|---|---|
|**<ssl_ctx_index>**|The SSL context ID. The range is 0-9. ||
|**<sslversion>**||The SSL version, the default value is 4.<br>0<br>SSL3.0<br>1<br>TLS1.0<br>2<br>TLS1.1<br>3<br>TLS1.2<br>4<br>All<br>In versions that support TLS1.3, the range is 0-2, and the default<br>value is 2.<br>0<br>TLS1.2<br>1<br>TLS1.3<br>2<br>ALL<br>The actual configurable range depends on the supported version.<br>The configured version should be support by server. So you should<br>use the default value if you are not sure that the version which the<br>server supported.| |---|---| ||
|**<authmode>**||The authentication mode, the default value is 0.<br>0<br>no authentication.<br>1<br>server authentication. It needs the root CA of the server.<br>2<br>server and client authentication. It needs the root CA of the<br>server, the cert and key of the client.(If the server does not need to<br>authenticate the client ,it is equivalent to value 1.)<br>3<br>client authentication and no server authentication. It needs the<br>cert and key of the client.( (If the server does not need to<br>authenticate the client ,it is equivalent to value 0.)| ||
|**<ignoreltime>**||The flag to indicate how to deal with expired certificate, the default<br>value is 1.<br>0<br>care about time check for certification.<br>1<br>ignore time check for certification<br>When set the value to 0, it need to set the right current date and time<br>byAT+CCLK when need SSL certification.| ||
|**<negotiatetime>**||The timeout value used in SSL negotiate stage. The range is 10-300<br>seconds. The default value is 300.| ||
|**<ca_file>**||The root CA file name of SSL context. The file name must have type<br>like ".pem" or ".der". The length of filename is from 5 to 108 bytes.<br>If the filename contains non-ASCII characters, the file path<br>parameter should contain a prefix of {non-ascii} and the quotation<br>mark (The string in the quotation mark should be hexadecimal of the<br>filename’s UTF8 code).<br>There are two ways to download certificate files to module:<br>1. By AT+CCERTDOWN.<br>2. By FTPS or HTTPS commands. Please refer to Chapter 16&17 of<br>this document.| ||
|**<clientcert_file>**||The client cert file name of SSL context. The file name must have<br>type like ".pem" or ".der". The length of filename is from 5 to 108<br>bytes.<br>If the filename contains non-ASCII characters, the file path<br>parameter should contain a prefix of {non-ascii} and the quotation<br>mark (The string in the quotation mark should be hexadecimal of the<br>filename’s UTF8 code).<br>There are two ways to download certificate files to module:<br>1. By AT+CCERTDOWN.<br>2. By FTPS or HTTPS commands. Please refer to Chapter 16&17 of<br>this document.| |---|---| ||
|**<clientkey_file>**||The client key file name of SSL context. The file name must have<br>type like ".pem" or ".der". The length of filename is from 5 to 108<br>bytes.<br>If the filename contains non-ASCII characters, the file path<br>parameter should contain a prefix of {non-ascii} and the quotation<br>mark (The string in the quotation mark should be hexadecimal of the<br>filename’s UTF8 code).<br>There are two ways to download certificate files to module:<br>1. By AT+CCERTDOWN.<br>2. By FTPS or HTTPS commands. Please refer to Chapter 16&17 of<br>this document.| ||
|**<password_file>**||The password file name of SSL context.this is used to decrypt the<br>client key. The file name must have type like ".pem" or ".der". The<br>length of filename is from 5 to 108 bytes.<br>If the filename contains non-ASCII characters, the file path<br>parameter should contain a prefix of {non-ascii} and the quotation<br>mark (The string in the quotation mark should be hexadecimal of the<br>filename’s UTF8 code).<br>There are two ways to download certificate files to module:<br>1. By AT+CCERTDOWN.<br>2. By FTPS or HTTPS commands. Please refer to Chapter 16&17 of<br>this document.| ||
|**<enableSNI_flag>**||The flag to indicate that enable the SNI flag or not, the default value<br>is 0.<br>0<br>not enable SNI.<br>1<br>enable SNI.| ||
|**<ignorecertCN_flag>**||The flag to indicate that enable the ignorecertCN flag or not, the<br>default value is 0.<br>0<br>not enable ignorecertCN.<br>1<br>enable ignorecertCN.| ||
|**<use_tickets_flag>**||The flag to indicate that enable the use_tickets flag or not, the| default value is 0. This flag only takes effect in the TLS 1.3 version and will not work in versions lower than TLS 1.3. - 0 not enable use_tickets. - 1 enable use_tickets.|

#### 19.2.1.2 Examples

**AT+CSSLCFG=?**

**+CSSLCFG: "sslversion",(0-9),(0-4) +CSSLCFG: "authmode",(0-9),(0-3) +CSSLCFG: "ignorelocaltime",(0-9),(0,1) +CSSLCFG: "negotiatetime",(0-9),(10-300) +CSSLCFG: "cacert",(0-9),(5-108) +CSSLCFG: "clientcert",(0-9),(5-108) +CSSLCFG: "clientkey",(0-9),(5-108) +CSSLCFG: "password",(0-9),(5-108) +CSSLCFG: "enableSNI",(0-9),(0,1) +CSSLCFG: "ignorecertCN",(0-9),(0,1)**

**OK**

**AT+CSSLCFG?**

**+CSSLCFG: 0,4,0,1,300,"","","","",0,0 +CSSLCFG: 1,4,0,1,300,"","","","",0,0 +CSSLCFG: 2,4,0,1,300,"","","","",0,0 +CSSLCFG: 3,4,0,1,300,"","","","",0,0 +CSSLCFG: 4,4,0,1,300,"","","","",0,0 +CSSLCFG: 5,4,0,1,300,"","","","",0,0 +CSSLCFG: 6,4,0,1,300,"","","","",0,0 +CSSLCFG: 7,4,0,1,300,"","","","",0,0 +CSSLCFG: 8,4,0,1,300,"","","","",0,0 +CSSLCFG: 9,4,0,1,300,"","","","",0,0**

**OK**

**AT+CSSLCFG="authmode",0,0 OK AT+CSSLCFG=6 +CSSLCFG: 6,4,0,1,300,"","","","",0,0**

**OK**

1.When validating a server certificate, ignore the "Hostname does not match certificate's Common Name (CN) field" error.

(In the case of self-signed certificates or in a development environment, there may be an issue where the CN field of the certificate does not match the hostname. In such situations, you can disable the validation of the certificate's CN field by setting the "ignorecertCN" field to 1, which will help avoid connection issues. However, please note that this action introduces certain security risks and should be used with caution.)

## 19.3 Command Result Codes

### 19.3.1 Description of <err>

|**Result codes**<br>**Description**|**Result codes**<br>**Description**|
|---|---|
|**0**|Operation succeeded|
|**1**|Alerting state(reserved)|
|**2**|Unknown error|
|**3**|Busy|
|**4**|Peer closed|
|**5**|Operation timeout|
|**6**|Transfer failed|
|**7**|Memoryerror|
|**8**|Invalid parameter|
|**9**|Network error|
|**10**|Open session error|
|**11**|State error|
|**12**|Create socket error|
|**13**|Get DNS error|
|**14**|Connect socket error|
|**15**|Handshake error|
|**16**|Close socket error|
|**17**|Nonet|
|**18**|Send data timeout|
|**19**|Not set certificates|

## 19.4 Unsolicited Result Codes

**URC**

**+CCHEVENT: <session_id>,RECV EVENT +CCH_RECV_CLOSED: <session_id>,<err> +CCHSEND: <session_id>,<err> +CCH_PEER_CLOSED: <session_id> +CCH: CCH STOP[,<cid>]**

**Description**

In manual receiving mode, when new data of a connection arriving to the module, this unsolicited result code will be reported to MCU. When receive data occurred any error, this unsolicited result code will be reported to MCU. When send data faild,error code will be reported. The connection is closed by the server. CCH stopped caused by network error. When the AT+CCHSTART=<cid> command is used to activate a network, the URC carries the cid

parameter, and each cid link reports an independent URC.

<!-- Source file: 2 3 AT Commands for GNSS - marked only.md -->

# 23 AT Commands for GNSS

## 23.1 Overview of AT Commands for GNSS

|**Command**|**Description**|
|---|---|
|**AT+CGNSSPWR**|GNSS power control, AP-Flash control and Dynamic Load control|
|**AT+CGNSSMODE**|Configure GNSS support mode|
|**AT+CGNSSNMEA**|Configure NMEA sentence type|
|**AT+CGNSSINFO**|Get GNSS fixed position information|

## 23.2 Detailed Description of AT Commands for GNSS

### 23.2.1 AT+CGNSSPWR GNSS power control, AP-Flash control and Dynamic Load control

In ASR1603 and ASR1803, this command can control the GNSS module by pulling up/down the power pin, and it can also control whether the GNSS module can quickly hot start the AP-Flash.

If you only want to enable/disable GNSS control, please execute AT+CGNSSPWR=1 or

AT+CGNSSPWR=0. If you want to enable GNSS and want to use AP-Flash fast hot start mode, please

**execute AT+CGNSSPWR=1,1 or AT+CGNSSPWR=0,1.**

When using AP-Flash fast hot start mode, you need to execute AT+CGNSSPWR=0,1 to store the positioning data in the module after the GNSS is set to the upper position for the first time. When AT+CGNSSPWR=1,1 is executed next time, the positioning data will be loaded into GNSS again. If you want to enable GNSS and want to use GNSS dynamic load, please execute AT+CGNSSPWR=1,1,1 or AT+CGNSSPWR=1,0,1,The third parameter defaults to 1 and it is optional

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**<GNSS_Power_status>,[AP_Flash_status],[GNSS**<br>**AT+CGNSSPWR=?**<br>**_dynamic_load]**<br>**OK**|**+CGNSSPWR:**|
|Read Command|**<GNSS_Power_status>,[AP_Flash_status],[GNSS**<br>**AT+CGNSSPWR?**<br>**_dynamic_load]**<br>**OK**||
|Write Command|1)If successfully:<br>**OK**<br>**AT+CGNSSPWR=<GNSS_Power_status>,[AP_Flash_status],[GNS**<br>2)if GNSS can work properly:<br>**+CGNSSPWR: READY!**<br>**S_dynamic_load]**<br>2)If failed:<br>**ERROR**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|-||

|**Defined Values**|**Defined Values**|
|---|---|
|**<GNSS_Power_status>**|0<br>Close GNSS<br>1<br>Active GNSS<br>2<br>For 1803S only, see "NOTE" instructions<br>The function will take effect immediately.|
|**[AP_Flash_status]**|0<br>Close GNSS AP-Flash fast hot start mode<br>1<br>Active GNSS AP-Flash fast hot start mode<br>The function will take effect immediately.|
|**[GNSS_dynamic_load]**|0<br>Close GNSS dynamic load<br>1<br>Active GNSS dynamic load<br>The function will take effect immediately.|

1. The module whose GNSS chip is ASR5311, parameters [AP_Flash_status] and

[GNSS_dynamic_load] of the instruction have no effect. The way to get GPS chip version is to send AT+CGNSSPROD.

2. If the hardware power supply of the 1803S GPS model is designed to be powered for a long time without hardware powering off, then only <GNSS_Power_status> 2 can be used to reset the GPS software.

3. The module whose GNSS chip is Huada, parameters [GNSS_dynamic_load] defaults to 0.

#### 23.2.1.1 Examples

**AT+CGNSSPWR=? +CGNSSPWR: (0,1),(0,1),(0,1)**

**OK**

**AT+CGNSSPWR? +CGNSSPWR: 1,1,1**

**OK AT+CGNSSPWR=1,1,1 OK**

**+CGNSSPWR: READY!**

### 23.2.7 AT+CGNSSMODE Configure GNSS support mode

This command is valid after the URC reports “+CGNSSPWR: READY!”.

**AT+CGNSSMODE Configure GNSS support mode** Response Test Command **+CGNSSMODE: (1-7) AT+CGNSSMODE=? OK** Response Read Command **+CGNSSMODE: <mode> AT+CGNSSMODE? OK** Response 1)If successfully: Write Command **OK AT+CGNSSMODE=<mode>** 2)If failed: **ERROR** Response Execution Command Set default value 3 **AT+CGNSSMODE OK** Parameter Saving Mode NO_SAVE Max Response Time 9000ms Reference -

#### 23.2.7.1 Defined Values

**<mode>** 1 GPS 2 BDS 3 GPS + BDS 4 GLONASS 5 GLONASS + GPS 6 GLONASS + BDS 7 GLONASS + BDS + GPS

8 GALILEO 9 GALILEO + GPS 10 GALILEO + BDS 11 GALILEO + GPS + BDS 12 GALILEO + GLONASS 13 GALILEO + GLONASS + GPS 14 GALILEO + GLONASS + BDS 15 GALILEO + GLONASS + BDS + GPS

The GNSSMODE values 1-15 follows the following principles Bit 0: GPS Bit 1: BDS Bit 2: GLONASS Bit 3: GALILEO And different GNSS chip support different combination refering to note.

#### 23.2.7.2 Examples

**AT+CGNSSMODE=? +CGNSSMODE: (1-15)**

**OK**

**AT+CGNSSMODE? +CGNSSMODE: 15**

**OK AT+CGNSSMODE=1 OK**

|1. The GNSSMODE ranges of different GNSS chips are as follows:<br>GNSS Chip<br>Range<br>Default Value<br>ASR 5311<br>(1-7)<br>7<br>CC1161W<br>(1-15)<br>15<br>CC1177W<br>(2)<br>2<br>ZKW<br>(1-7)<br>7<br>AG3352<br>(1,3,5,9,11,15)<br>15<br>HD8040B<br>(2)<br>2<br>HD8041<br>(2)<br>2<br>HD8040D<br>(1-15)<br>15<br>2. The combination supported byUNICC6228 is different from other GNSS chips, as follows:|1. The GNSSMODE ranges of different GNSS chips are as follows:<br>GNSS Chip<br>Range<br>Default Value<br>ASR 5311<br>(1-7)<br>7<br>CC1161W<br>(1-15)<br>15<br>CC1177W<br>(2)<br>2<br>ZKW<br>(1-7)<br>7<br>AG3352<br>(1,3,5,9,11,15)<br>15<br>HD8040B<br>(2)<br>2<br>HD8041<br>(2)<br>2<br>HD8040D<br>(1-15)<br>15<br>2. The combination supported byUNICC6228 is different from other GNSS chips, as follows:|1. The GNSSMODE ranges of different GNSS chips are as follows:<br>GNSS Chip<br>Range<br>Default Value<br>ASR 5311<br>(1-7)<br>7<br>CC1161W<br>(1-15)<br>15<br>CC1177W<br>(2)<br>2<br>ZKW<br>(1-7)<br>7<br>AG3352<br>(1,3,5,9,11,15)<br>15<br>HD8040B<br>(2)<br>2<br>HD8041<br>(2)<br>2<br>HD8040D<br>(1-15)<br>15<br>2. The combination supported byUNICC6228 is different from other GNSS chips, as follows:|
|---|---|---|
|GNSS Chip|Software Version|GNSSMODE Configuration|
|UNIC 6228|Domestic|1603&1803 Platform:<br>1<br>GPS + BDS<br>2 BDS<br>3 GPS<br>1602&1606 Platform:<br>1 GPS<br>2 BDS<br>3<br>GPS + BDS|
||Oversea|1 GPS<br>2 BDS<br>3<br>GPS + GLONASS + GALILEO<br>4 GPS + BDS + GALILEO|

### 23.2.8 AT+CGNSSNMEA Configure NMEA sentence type

This command is valid after the URC reports “+CGNSSPWR: READY!”.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**AT+CGNSSNMEA=?**|**+CGNSSNMEA: (0-1),(0-1),(0-1),(0-1),(0-1),(0-1),(0-1),(0-1)**<br>**OK**<br>Response|
|Read Command|**AT+CGNSSNMEA?**|**+CGNSSNMEA: 1,0,1,1,1,0,0,0**<br>**OK**|
|Write Command|**AT+CGNSSNMEA=[nGGA],[nGL**<br>**L],[nGSA],[nGSV],[nRMC],[nVT**|1)If successfully:<br>**OK**|

|**G],[nZDA],[nGST]**|2)If failed:|
|---|---|
||**ERROR**|
|Parameter Saving Mode|NO_SAVE|
|Max Response Time|9000ms|
|Reference|-|

#### 23.2.8.1 Defined Values

**[nGGA],[nGLL],[nGSA],[nG** The range of n is 0-1. It means that the sentence is output every n **SV],[nRMC],[nVTG],[nZDA],[** times, 0 means no output, null means to save the original **nGST],** configuration. nGGA GGA output rate, default is 1 nGLL GLL output rate, default is 0 nGSA GSA output rate, default is 1 nGSV GSV output rate, default is 1 nRMC RMC output rate, default is 1 nVTG VTG output rate, default is 0 nZDA ZDA output rate, default is 0 nGST GST output rate, default is 0 The function will take effect immediately.

#### 23.2.8.2 Examples

**AT+CGNSSNMEA=? +CGNSSNMEA: (0-1** ) **,(0-1** ) **,(0-1** ) **,(0-1** ) **,(0-1** ) **,(0-1** ) **,(0-1** ) **,(0-1** )

**OK**

**AT+CGNSSNMEA? +CGNSSNMEA: 1,0,1,1,1,0,0,0**

**OK AT+CGNSSNMEA=1,0,0,0,0,0,0,0 OK**

Module whose GNSS chip is ASR 5311 has different parameter configuration. The way to get GPS chi p version is to send AT+CGNSSPROD: nRMC RMC output rate, default is 1 nVTG VTG output rate, default is 1 nGGA GGA output rate, default is 1

nGSA GSA output rate, default is 1 nGSV GSV output rate, default is 1 nGLL GLL output rate, default is 1 nZDA ZDA output rate, default is 1 nGST GST output rate, default is 1 nTXT TXT output rate, default is 1

### 23.2.12 AT+CGNSSINFO Get GNSS fixed position information

This command is valid after the URC reports “+CGNSSPWR: READY!”.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Test Command|**+CGNSSINFO: (0-255)**<br>**AT+CGNSSINFO=?**<br>**OK**||
|Read Command|**+CGNSSINFO: <time>**<br>**AT+CGNSSINFO?**<br>**OK**|1)If successfully:<br>**OK**<br>+**CGNSSINFO:**|
|Write Command|**[<mode>],[<GPS-SVs>],[BEIDOU-SVs],[<GLONASS-SVs>],[<GALIL**<br>**AT+CGNSSINFO=<time>**<br>**EO-SVs>],[<lat>],[<N/S>],[<log>],[<E/W>],[<date>],[<UTC-time>],[<a**<br>**lt>],[<speed>],[<course>],[<PDOP>],[HDOP],[VDOP], [NoSV]**<br>2)If <time>=0:<br>**OK**<br>3)If failed:<br>**ERROR**|**+CGNSSINFO:**<br>**[<mode>],[<GPS-SVs>],[BEIDOU-SVs],[<GLONASS-SVs>],[<GALIL**|
|Execution Command|**EO-SVs>],**<br>**AT+CGNSSINFO**<br>**[<lat>],[<N/S>],[<log>],[<E/W>],[<date>],[<UTC-time>],[<alt>],[<spee**<br>**d>],[<course>],[<PDOP>],[HDOP],[VDOP], [NoSV]**<br>**OK**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|-||

#### 23.2.12.1 Defined Values

|Parameter|Description|
|---|---|
|**<time>**|The rang is 0-255, unit is second. after set <time> will report the GNSS information every the seconds. The function will take effect immediately.|
|**<mode>**|Fix mode 2=2D fix 3=3D fix|
|**<GPS-SVs>**|GPS satellite visible numbers|
|**<BEIDOU-SVs>**|BEIDOU satellite visible numbers|
|**<GLONASS-SVs>**|GLONASS satellite visible numbers|
|**<GALILEO-SVs>**|GALILEO satellite visible numbers|
|**<lat>**|Latitude of current position.Output format is dd.ddddddd ||
|**<N/S>**||N/S Indicator, N=north or S=south.| |---|---| ||
|**<log>**||Longitude of current position. Output format is ddd.ddddddd| ||
|**<E/W>**||E/W Indicator, E=east or W=west.| ||
|**<date>**||Date. Output format is ddmmyy.| ||
|**<UTC-time>**||UTC Time. Output format is hhmmss.ss.| ||
|**<alt>**||MSL Altitude. Unit is meters.| ||
|**<speed>**||Speed Over Ground. Unit is knots.| ||
|**<course>**||Course. Degrees.| ||
|**<PDOP>**||Position Dilution Of Precision.| ||
|**<HDOP>**||Horizontal Dilution Of Precision.| ||
|**<VDOP>**||Vertical Dilution Of Precision.| ||
|**<NoSV>**||Number of satellites involved in positioning||

#### 23.2.12.2 Examples

**AT+CGNSSINFO=? +CGNSSINFO: (0-255)**

**OK**

**AT+CGNSSINFO? +CGNSSINFO: 0**

**OK**

**AT+CGNSSINFO +CGNSSINFO:**

**2,09,05,00,00,29.4618121,N,121.2648561,E,131117,091918.00,32.9,0.0,255.0,1.1,0.8,0.7,6**

**OK**

**AT+CGNSSINFO (if not fix, will report null) +CGNSSINFO: ,,,,,,,,,,,,,,, OK**

The number of messages reported by CGNSSINFO on 7670C R2, 7670C R3 and 7670C R5 has 16 fields as follows:

|7670C R2<br>7670C R3<br>7670C R5|+CGNSSINFO reported information as follows:<br>+CGNSSINFO:<br>[<mode>],[<GPS-SVs>],[BEIDOU-SVs],[<lat>],[<N/S >],[<log>],[<E/W>],[<dat<br>e>],[<UTC-time>],[<alt>],[<speed>],[<course>],[<PDOP>],[HDOP],[VDOP].[<<br>NoSV>]|
|---|---|

<!-- Source file: 3 4 AT Commands for eDRX - marked only.md -->

# 34 AT Commands for eDRX

## 34.1 Overview of AT Commands for eDRX

|**Command**|**Description**|
|---|---|
|**AT+CEDRXS**|DRX Setting|
|**AT+CEDRXRDP**|eDRX Read Dynamic Parameters|

## 34.2 Detailed Description of AT Commands for eDRX

### 34.2.1 AT+CEDRXS DRX Setting

The command controls the setting of the UEs eDRX parameters. The command controls whether the UE wants to apply eDRX or not, as well as the requested eDRX value for each specified type of access technology.

**AT+CEDRXS DRX Setting** Response Test Command **+CEDRXS: (0-3),(1-5) AT+CEDRXS=? OK** Response Read Command **+CEDRXS: <eDrxAct>,[ "<requestedEdrxValue>"] AT+CEDRXS? OK** Write Command Response **AT+ CEDRXS = <mode>[,<** 1) **eDrxAct >[,<Requested_eDRX_ OK value>** 2) **]] ERROR** Parameter Saving Mode AUTO_SAVE Max Response Time 9000ms Reference

#### 34.2.1.1 Defined Values

|Parameter|Description|
|---|---|
|**<mode>**|integer type. Indication to disable or enable the use of Drx in the UE ||0<br>Disable the use of Drx<br>1<br>Enable the use of Drx<br>2<br>Enable the use of eDrx Enable the use of eDRX and enable the<br>unsolicited result code+CEDRXP:<br><AcT-type>[,<Requested_eDRX_value>[,<NW-provided_eDR<br>X_value>[,<Paging_time_window>]]]<br>3<br>Disable the use of eDRX and discard all parameters for eDRX<br>or, if available, reset to the manufacturer specific default<br>values.| |---|---| ||
|**<eDrxAct>**||integer type, indicates the type of access technology. This<br>AT-command is used to specify the relationship between the type of<br>access technology and the requested eDRX value.<br>0<br>Access technology is not using eDRX. This parameter value is<br>only used in the unsolicited result code.<br>1<br>EC-GSM-IoT (A/Gb mode)<br>2<br>GSM (A/Gb mode)<br>3<br>UTRAN (Iu mode)<br>4<br>E-UTRAN (WB-S1 mode)<br>5<br>E-UTRAN(NB-S1 mode)| ||
|**<Requested_eDRX_value>**||string type; half a byte in a 4 bit format. The eDRX value refers to bit 4<br>to 1 of octet 3 of the Extended DRX parameters information element<br>(see clause 10.5.5.32 of 3GPP TS 24.008).<br>For the coding and the<br>value range, see Extended DRX parameters information element in<br>3GPP TS 24.008 Table 10.5.5.32/3GPP TS 24.008. The default value,<br>if available, is manufacturer specific.| |**<NW-provided_eDRX_value|
|**<br>**|>**|string type; half a byte in a 4 bit format. The eDRX value refers to bit 4<br>to 1 of octet 3 of the Extended DRX parameters information element<br>(see clause 10.5.5.32 of 3GPP TS 24.008).<br>For the coding and the<br>value range, see Extended DRX parameters information element in<br>3GPP TS 24.008 Table 10.5.5.32/3GPP TS 24.008.| ||
|**<Paging_time_window>**||string type; half a byte in a 4 bit format. The paging time window<br>referes to bit 8 to 5 of octet 3 of the Extended DRX parameters<br>information element (see clause 10.5.5.32 of 3GPP TS 24.008). For<br>the coding and the value range, see the Extended DRX parameters<br>information element in 3GPP TS 24.008 Table 10.5.5.32/3GPP TS<br>24.008.||

#### 34.2.1.2 Examples

**AT+CEDRXS=? +CEDRXS: (0-3),(1-5)**

**OK AT+CEDRXS?**

**+CEDRXS: 4,""**

**OK**

### 34.2.2 AT+CEDRXRDP eDRX Read Dynamic Parameters

The execution command returns <AcT-type> and <Requested_eDRX_value>, <NW-provided_eDRX_value> and <Paging_time_window> if eDRX is used for the cell that the MS is currently registered to.

If the cell that the MS is currently registered to is not using eDRX, <AcT-type>=0 is returned.

|Type|Command / Value|Response / Notes|
|---|---|---|
|Execution Command|**AT+CEDRXRDP**<br>**<AcT-type>[,<Requested_eDRX_value>[,<NW-provided_eDR**<br>**X_value>[,<Paging_time_window>]]]**<br>**OK**||
|Parameter Saving Mode|NO_SAVE||
|Max Response Time|9000ms||
|Reference|||

#### 34.2.2.1 Defined Values

|Parameter|Description|
|---|---|
|**<AcT-type>**|integer type, indicates the type of access technology. This AT-command is used to specify the relationship between the type of access technology and the requested eDRX value. 0 Access technology is not using eDRX. This parameter value is only used in the unsolicited result code. 1 EC-GSM-IoT (A/Gb mode) 2 GSM (A/Gb mode) 3 UTRAN (Iu mode) 4 E-UTRAN (WB-S1 mode) 5 E-UTRAN (NB-S1 mode)|
|**<Requested_eDRX_value>**|string type; half a byte in a 4 bit format. The eDRX value refers to bit 4 to 1 of octet 3 of the Extended DRX parameters information element (see clause 10.5.5.32 of 3GPP TS 24.008). For the coding and the value range, see Extended DRX parameters information element in 3GPP TS 24.008 Table 10.5.5.32/3GPP TS 24.008. The default value, if available, is manufacturer specific. **<NW-provided_eDRX_value** string type; half a byte in a 4 bit format. The eDRX value refers to bit 4 **>** to 1 of octet 3 of the Extended DRX parameters information element (see clause 10.5.5.32 of 3GPP TS 24.008). For the coding and the value range, see Extended DRX parameters information element in 3GPP TS 24.008 Table 10.5.5.32/3GPP TS 24.008.|
|**<Paging_time_window>**|string type; half a byte in a 4 bit format. The paging time window referes to bit 8 to 5 of octet 3 of the Extended DRX parameters information element (see clause 10.5.5.32 of 3GPP TS 24.008). For the coding and the value range, see the Extended DRX parameters information element in 3GPP TS 24.008 Table 10.5.5.32/3GPP TS 24.008.|

#### 34.2.2.2 Examples

**AT+CEDRXRDP**

**+CEDRXRDP: 0**

**OK**

<!-- Source file: 3 9 Summary of ERROR Codes.md -->


# 39 Summary of ERROR Codes

## 39.1 Verbose Codes and Numeric Codes

|**Verbose result code**<br>**Numeric (V0 set**)<br>**Description**|**Verbose result code**<br>**Numeric (V0 set**)<br>**Description**|**Verbose result code**<br>**Numeric (V0 set**)<br>**Description**|
|---|---|---|
|**OK**|0|Command executed, no errors, Wake up after<br>reset|
|**CONNECT**|1|Link established|
|**RING**|2|Ring detected|
|**NO CARRIER**|3|Link not established or disconnected|
|**ERROR**|4|Invalid command or command line too long|
|**NO DIALTONE**|6|No dial tone, dialing impossible, wrong mode|
|**BUSY**|7|Remote station busy|
|**NO ANSWER**|8|Connection completion timeout|

## 39.2 Response String of AT+CEER

|**Number**<br>**Response string**|**Number**<br>**Response string**|
|---|---|
|**CS internal cause**||
|0|Unknown|
|1|Unassigned number|
|3|No route to destination|
|6|Channel unacceptable|
|8|Operator determined barring|
|16|Normal call clearing|
|17|User busy|
|18|No user responding|
|19|User alerting: no answer|
|21|Call rejected|
|22|Number changed|
|25|Preemption|

|26|Non selected user clearing|
|---|---|
|27|Destination out of order|
|28|Invalid number format|
|29|Facility rejected|
|30|Response to STATUS ENQUIRY|
|31|Normal unspecified|
|34|No circuit/channel available|
|38|Network out of order|
|41|Temporary failure|
|42|Switching equipment congestion|
|43|Access information discarded|
|44|Requested circuit/channel unavailable|
|47|Resource unavailable|
|49|QoS unavailable|
|50|Requested facility not subscribed|
|55|Incoming calls barred within CUG|
|57|Bearer capability not authorized|
|58|Bearer capability not available|
|63|Service not available|
|65|Bearer service not implemented|
|68|ACM MAX reached|
|69|Facility not implemented|
|70|Only RDI bearer capability available|
|79|Service not implemented|
|81|Invalid transaction ID|
|87|User not member of CUG|
|88|Incompatible destination|
|91|Invalid transit network selection|
|95|Incorrect message|
|96|Invalid mandatory information|
|97|Message type non-existent|
|98|Message type wrong state|
|99|Information element not-existent|
|100|Conditional IE error|
|101|Message wrong state|
|102|Recovery after timer expiry|
|111|Protocol error: unspecified|
|127|Interworking: unspecified|
|224|Call barring|
|241|FDN Blocked|

|**CS network cause**||
|---|---|
|1|Unassigned/unallocated number|
|3|No route to destination|
|6|Channel unacceptable|
|8|Operator determined barring|
|16|Normal call clearing|
|17|User busy|
|18|No user responding|
|19|User alerting, no answer|
|21|Call rejected|
|22|Number changed|
|26|Non selected user clearing|
|27|Destination out of order|
|28|Invalid/incomplete number|
|29|Facility rejected|
|30|Response to Status Enquiry|
|31|Normal, unspecified|
|34|No circuit/channel available|
|38|Network out of order|
|41|Temporary failure|
|42|Switching equipment congestion|
|43|Access information discarded|
|44|Requested circuit/channel not available|
|47|Resources unavailable, unspecified|
|49|Quality of service unavailable|
|50|Requested facility not subscribed|
|55|Incoming calls barred within the CUG|
|57|Bearer capability not authorized|
|58|Bearer capability not available|
|63|Service/option not available|
|65|Bearer service not implemented|
|68|ACM >= ACMmax|
|69|Requested facility not implemented|
|70|Only RDI bearer is available|
|79|Service/option not implemented|
|81|Invalid transaction identifier value|
|87|User not member of CUG|
|88|Incompatible destination|
|91|Invalid transit network selection|
|95|Semantically incorrect message|
|96|Invalid mandatory information|

|97|Message non-existent/not implemented|
|---|---|
|98|Message type not compatible with state|
|99|IE non-existent/not implemented|
|100|Conditional IE error|
|101|Message not compatible with state|
|102|Recovery on timer expiry|
|111|Protocol error, unspecified|
|117|Interworking, unspecified|
|**CS network reject**||
|2|IMSI unknown in HLR|
|3|Illegal MS|
|4|IMSI unknown in VLR|
|5|IMEI not accepted|
|6|Illegal ME|
|7|GPRS services not allowed|
|8|GPRS & non GPRS services not allowed|
|9|MS identity cannot be derived|
|10|Implicitly detached|
|11|PLMN not allowed|
|12|Location Area not allowed|
|13|Roaming not allowed|
|14|GPRS services not allowed in PLMN|
|15|No Suitable Cells In Location Area|
|16|MSC temporarily not reachable|
|17|Network failure|
|20|MAC failure|
|21|Synch failure|
|22|Congestion|
|23|GSM authentication unacceptable|
|32|Service option not supported|
|33|Requested service option not subscribed|
|34|Service option temporarily out of order|
|38|Call cannot be identified|
|40|No PDP context activated|
|95|Semantically incorrect message|
|96|Invalid mandatory information|
|97|Message type non-existent|
|98|Message type not compatible with state|
|99|Information element non-existent|
|101|Message not compatible with state|

|161|RR release indication|
|---|---|
|162|RR random access failure|
|163|RRC release indication|
|164|RRC close session indication|
|165|RRC open session failure|
|166|Low level failure|
|167|Low level failure no redial allowed|
|168|Invalid SIM|
|169|No service|
|170|Timer T3230 expired|
|171|No cell available|
|172|Wrong state|
|173|Access class blocked|
|174|Abort message received|
|175|Other cause|
|176|Timer T303 expired|
|177|No resources|
|178|Release pending|
|179|Invalid user data|
|**PS internal cause lookup**||
|0|Invalid connection identifier|
|1|Invalid NSAPI|
|2|Invalid Primary NSAPI|
|3|Invalid field|
|4|SNDCP failure|
|5|RAB setup failure|
|6|No GPRS context|
|7|PDP establish timeout|
|8|PDP activate timeout|
|9|PDP modify timeout|
|10|PDP inactive max timeout|
|11|PDP lowerlayer error|
|12|PDP duplicate|
|13|Access technology change|
|14|PDP unknown reason|
|**PS network cause**||
|25|LLC or SNDCP failure|
|26|Insufficient resources|
|27|Missing or unknown APN|

|28|Unknown PDP address or PDP type|
|---|---|
|29|User Aauthentication failed|
|30|Activation rejected by GGSN|
|31|Activation rejected, unspecified|
|32|Service option not supported|
|33|Requested service option not subscribed|
|34|Service option temporarily out of order|
|35|NSAPI already used (not sent)|
|36|Regular deactivation|
|37|QoS not accepted|
|38|Network failure|
|39|Reactivation required|
|40|Feature not supported|
|41|Semantic error in the TFT operation|
|42|Syntactical error in the TFT operation|
|43|Unknown PDP context|
|44|PDP context without TFT already activated|
|45|Semantic errors in packet filter|
|46|Syntactical errors in packet filter|
|81|Invalid transaction identifier|
|95|Semantically incorrect message|
|96|Invalid mandatory information|
|97|Message non-existent/not implemented|
|98|Message type not compatible with state|
|99|IE non-existent/not implemented|
|100|Conditional IE error|
|101|Message not compatible with state|
|111|Protocol error, unspecified|

## 39.3 Summary of CME ERROR Codes

This result code is similar to the regular ERROR result code. The format of <err> can be either numeric or verbose string, by setting AT+CMEE command.

### 39.3.1 Defined Values

**Code of <err> Meaning**

|**0**|phone failure|
|---|---|
|**1**|no connection to phone|
|**2**|phone adaptor link reserved|
|**3**|operation not allowed|
|**4**|operation not supported|
|**5**|PH- SIM PIN required|
|**6**|PH-FSIM PIN required|
|**7**|PH-FSIM PUK required|
|**10**|SIM not inserted|
|**11**|SIM PIN required|
|**12**|SIM PUK required|
|**13**|SIM failure|
|**14**|SIM busy|
|**15**|SIM wrong|
|**16**|incorrect password|
|**17**|SIM PIN2 required|
|**18**|SIM PUK2 required|
|**20**|memoryfull|
|**21**|invalid index|
|**22**|not found|
|**23**|memoryfailure|
|**24**|text stringtoo long|
|**25**|invalid characters in text string|
|**26**|dial string too long|
|**27**|invalid characters in dial string|
|**30**|no network service|
|**31**|network timeout|
|**32**|network not allowed - emergency calls only|
|**40**|network personalization PIN required|
|**41**|network personalization PUK required|
|**42**|network subset personalization PIN required|
|**43**|network subset personalization PUK required|
|**44**|service provider personalization PIN required|
|**45**|service provider personalization PUK required|
|**46**|corporate personalization PIN required|
|**47**|corporate personalization PUK required|
|**50**|Incorrect parameters|
|**100**|unknown error|
|**103**|Illegal MESSAGE|
|**106**|Illegal ME|
|**107**|GPRS services not allowed|

|**111**|PLMN not allowed|
|---|---|
|**112**|Location area not allowed|
|**113**|Roaming not allowed in this location area|
|**132**|service option not supported|
|**133**|requested service option not subscribed|
|**134**|service option temporarilyout of order|
|**148**|unspecified GPRS error|
|**149**|PDP authentication failure|
|**150**|invalid mobile class|
|**151**|AT command timeout|
|**535**|Protocal stack busy|

### 39.3.2 Examples

**AT+CPIN="1234","1234" +CME ERROR: SIM failure**

## 39.4 Summary of CMS ERROR Codes

Final result code +CMS ERROR: <err> indicates an error related to mobile equipment or network. The operation is similar to ERROR result code. None of the following commands in the same command line is executed. Neither ERROR nor OK result code shall be returned. ERROR is returned normally when error is related to syntax or invalid parameters. The format of <err> can be either numeric or verbose. This is set with command AT+CMEE.

### 39.4.1 Defined Values

|**Code of <err>**<br>**Meaning**|**Code of <err>**<br>**Meaning**|
|---|---|
|**300**|ME failure|
|**301**|SMS service of ME reserved|
|**302**|Operation not allowed|
|**303**|Operation not supported|
|**304**|Invalid PDU mode parameter|
|**305**|Invalid text mode parameter|
|**310**|SIM not inserted|
|**311**|SIM PIN required|
|**312**|PH-SIM PIN required|

|**313**|SIM failure|
|---|---|
|**314**|SIM busy|
|**315**|SIM wrong|
|**316**|SIM PUK required|
|**317**|SIM PIN2 required|
|**318**|SIM PUK2 required|
|**320**|Memory failure|
|**321**|Invalid memory index|
|**322**|Memoryfull|
|**330**|SMSC address unknown|
|**331**|no network service|
|**332**|Network timeout|
|**340**|no +CNMA acknowledgement expected|
|**341**|Buffer overflow|
|**342**|SMS size more than expected|
|**500**|unknown error|

### 39.4.2 Examples

**AT+CMGS=02112345678 +CMS ERROR: 304**
