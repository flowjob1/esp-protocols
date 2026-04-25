idf_component_register(
    SRCS "a7670e_at_example.cpp"
    INCLUDE_DIRS "."
    REQUIRES esp_modem a7670e_modem esp_event freertos
    PRIV_REQUIRES esp_system
)

