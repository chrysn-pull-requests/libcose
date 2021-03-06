/*
 * Copyright (C) 2018 Freie Universitat Berlin
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    cose_cryto_mbedtls Crypto glue layer, mbedtls definitions
 * @ingroup     cose_crypto
 *
 * Crypto function api for glueing mbedtls.
 * @{
 *
 * @file
 * @brief       Crypto function api for glueing mbedtls.
 *
 * @author      Koen Zandberg <koen@bergzand.net>
 */

#ifndef COSE_CRYPTO_MBEDTLS_H
#define COSE_CRYPTO_MBEDTLS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name list of provided algorithms
 *
 * @{
 */
#define HAVE_ALGO_AES128GCM /**< AES GCM mode support with 128 bit key */
#define HAVE_ALGO_AES192GCM /**< AES GCM mode support with 192 bit key */
#define HAVE_ALGO_AES256GCM /**< AES GCM mode support with 256 bit key */
#define HAVE_ALGO_ES512     /**< Sha512 support and some EC support */
#define HAVE_ALGO_ES384     /**< Sha384 support and some EC support */
#define HAVE_ALGO_ES256     /**< Sha256 support and some EC support */

#define HAVE_ALGO_ECDSA

#define HAVE_CURVE_P521     /**< EC NIST p521 curve support */
#define HAVE_CURVE_P384     /**< EC NIST p384 curve support */
#define HAVE_CURVE_P256     /**< EC NIST p256 curve support */
/** @} */

#define COSE_CRYPTO_AEAD_AESGCM_NONCEBYTES      12
#define COSE_CRYPTO_AEAD_AESGCM_ABYTES          16

#define COSE_CRYPTO_AEAD_AES128GCM_KEYBYTES     16
#define COSE_CRYPTO_AEAD_AES128GCM_NONCEBYTES   COSE_CRYPTO_AEAD_AESGCM_NONCEBYTES
#define COSE_CRYPTO_AEAD_AES128GCM_ABYTES       COSE_CRYPTO_AEAD_AESGCM_ABYTES

#define COSE_CRYPTO_AEAD_AES192GCM_KEYBYTES     24
#define COSE_CRYPTO_AEAD_AES192GCM_NONCEBYTES   COSE_CRYPTO_AEAD_AESGCM_NONCEBYTES
#define COSE_CRYPTO_AEAD_AES192GCM_ABYTES       COSE_CRYPTO_AEAD_AESGCM_ABYTES

#define COSE_CRYPTO_AEAD_AES256GCM_KEYBYTES     32
#define COSE_CRYPTO_AEAD_AES256GCM_NONCEBYTES   COSE_CRYPTO_AEAD_AESGCM_NONCEBYTES
#define COSE_CRYPTO_AEAD_AES256GCM_ABYTES       COSE_CRYPTO_AEAD_AESGCM_ABYTES

#ifdef __cplusplus
}
#endif

#endif

/** @} */
