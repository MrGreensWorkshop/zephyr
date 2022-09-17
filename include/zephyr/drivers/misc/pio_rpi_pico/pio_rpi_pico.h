/*
 * Copyright (c) 2022 Tokita, Hiroshi <tokita.hiroshi@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_MISC_PIO_PICO_RPI_PIO_PICO_RPI_H_
#define ZEPHYR_DRIVERS_MISC_PIO_PICO_RPI_PIO_PICO_RPI_H_

#include <zephyr/drivers/pinctrl.h>

#include <hardware/clocks.h>
#include <hardware/pio.h>
#include <pico_pio.h>

/**
 * Get PIO object
 *
 * @param dev Pointer to device structure for rpi_pio device instance
 * @return PIO object
 */
PIO pio_rpi_get_pio(const struct device *dev);

/**
 * Query pin number by pin-name.
 *
 * @param dev Pointer to device structure for rpi_pio device instance
 * @param name pinmux-name string
 *
 * @return Return pin number on successed.
 *         UINT32_MAX return if failed.
 */
uint32_t pio_rpi_pin_number_by_name(const struct device *dev, const char *name);

#define PIO_PIN_ARRAY_ELEM(node_id, prop, idx)                                                     \
	(DT_PROP_BY_IDX(node_id, prop, idx) >> RP2_PIN_NUM_POS),
#define PIO_PIN_ARRAY(g) DT_FOREACH_PROP_ELEM(g, pinmux, PIO_PIN_ARRAY_ELEM)

#define PIO_DT_PINS(node_id) { DT_FOREACH_CHILD(DT_PINCTRL_0(node_id, 0), PIO_PIN_ARRAY) }
#define PIO_DT_INST_PINS(inst) PIO_DT_PINS(DT_DRV_INST(inst))

#define COMMA		,
#define NULL_NAME(n, _) "" _
#define EMPTY_NAMES(g)	LISTIFY(DT_PROP_LEN(g, pinmux), NULL_NAME, (COMMA))

#define PIO_PIN_NAME_ARRAY_ELEM(node_id, prop, idx) DT_PROP_BY_IDX(node_id, prop, idx) COMMA
#define PIO_PIN_NAME_ARRAY(g)                                                                      \
	COND_CODE_1(DT_NODE_HAS_PROP(g, pinmux_names),                                             \
		    (DT_FOREACH_PROP_ELEM(g, pinmux_names, PIO_PIN_NAME_ARRAY_ELEM)),              \
		    (EMPTY_NAMES(g) COMMA))

#define PIO_DT_PINNAMES(node_id) { DT_FOREACH_CHILD(DT_PINCTRL_0(node_id, 0), PIO_PIN_NAME_ARRAY) }
#define PIO_DT_INST_PINNAMES(inst) PIO_DT_PINNAMES(DT_DRV_INST(inst))

#endif /* ZEPHYR_DRIVERS_MISC_PIO_PICO_RPI_PIO_PICO_RPI_H_ */
