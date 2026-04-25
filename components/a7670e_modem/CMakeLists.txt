idf_component_register(
    SRCS
        "src/a7670e_module.cpp"
        "src/a7670e_commands_net.cpp"
        "src/a7670e_commands_serial.cpp"
        "src/a7670e_commands_fs.cpp"
        "src/a7670e_commands_http.cpp"
        "src/a7670e_commands_mqtt.cpp"
        "src/a7670e_commands_ssl.cpp"
        "src/a7670e_commands_gnss.cpp"
        "src/a7670e_commands_edrx.cpp"
        "src/a7670e_urc_handler.cpp"
    INCLUDE_DIRS "include"
    REQUIRES esp_modem esp_event freertos
)
