/*
 * Copyright (c) 2022 Tokita, Hiroshi <tokita.hiroshi@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//#include <zephyr/devicetree/pinctrl.h>
#include <string.h>

#include <zephyr/drivers/misc/pio_rpi_pico/pio_rpi_pico.h>
#include <zephyr/drivers/pinctrl.h>

#define DT_DRV_COMPAT raspberrypi_pico_pio

struct rpi_pico_pio_config {
	PIO pio;
	const struct pinctrl_dev_config *pcfg;
	const uint8_t *pins;
	const char **names;
	const uint8_t pin_num;
};

PIO pio_rpi_get_pio(const struct device *dev)
{
	const struct rpi_pico_pio_config *config = dev->config;

	return config->pio;
}

uint32_t pio_rpi_pin_number_by_name(const struct device *dev, const char *name)
{
	const struct rpi_pico_pio_config *config = dev->config;

	for (size_t i = 0; i < config->pin_num; i++) {
		if (strcmp(name, config->names[i]) == 0) {
			return config->pins[i];
		}
	}

	return UINT32_MAX;
}

static int pio_rpi_init(const struct device *dev)
{
	const struct rpi_pico_pio_config *config = dev->config;

	return pinctrl_apply_state(config->pcfg, PINCTRL_STATE_DEFAULT);
}

#define RPI_PICO_PIO_INIT(idx)                                                                     \
	PINCTRL_DT_INST_DEFINE(idx);                                                               \
	static const uint8_t pins##idx[] = PIO_DT_INST_PINS(idx);                                  \
	static const char *pinnames##idx[] = PIO_DT_INST_PINNAMES(idx);                            \
	static const struct rpi_pico_pio_config rpi_pico_pio_config_##idx = {                      \
		.pio = (PIO)DT_INST_REG_ADDR(idx),                                                 \
		.pcfg = PINCTRL_DT_INST_DEV_CONFIG_GET(idx),                                       \
		.pin_num = ARRAY_SIZE(pins##idx),                                                  \
		.pins = pins##idx,                                                                 \
		.names = pinnames##idx,                                                            \
	};                                                                                         \
                                                                                                   \
	DEVICE_DT_INST_DEFINE(idx, &pio_rpi_init, NULL, NULL, &rpi_pico_pio_config_##idx,          \
			      PRE_KERNEL_2, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, NULL);

DT_INST_FOREACH_STATUS_OKAY(RPI_PICO_PIO_INIT)
