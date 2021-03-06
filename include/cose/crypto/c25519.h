/*
 * Copyright (C) 2018 Koen Zandberg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    cose_cryto_c25519 Crypto glue layer, c25519 definitions
 * @ingroup     cose_crypto
 *
 * Crypto function api for glueing c25519.
 * @{
 *
 * @file
 * @brief       Crypto function api for glueing c25519.
 *
 * @author      Koen Zandberg <koen@bergzand.net>
 */

#ifndef COSE_CRYPTO_C25519_H
#define COSE_CRYPTO_C25519_H

#include <edsign.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name list of provided algorithms
 *
 * @{
 */
#define HAVE_ALGO_EDDSA
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* COSE_CRYPTO_C25519 */

/** @} */

