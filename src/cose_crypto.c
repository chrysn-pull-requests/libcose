/*
 * Copyright (C) 2018 Freie Universitat Berlin
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "cose/crypto.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

cose_crypt_rng cose_crypt_get_random = NULL;
void *cose_crypt_rng_arg = NULL;

void cose_crypt_set_rng(cose_crypt_rng f_rng, void *p_rng)
{
    cose_crypt_get_random = f_rng;
    cose_crypt_rng_arg = p_rng;
}

ssize_t cose_crypto_keygen(uint8_t *buf, size_t len, cose_algo_t algo)
{
    switch(algo) {
#ifdef HAVE_ALGO_CHACHA20POLY1305
        case COSE_ALGO_CHACHA20POLY1305:
            return cose_crypto_aead_keypair_chachapoly(buf, len);
#endif /* HAVE_ALGO_CHACHA20POLY1305 */
        default:
            (void)buf;
            (void)len;
            return COSE_ERR_NOTIMPLEMENTED;
    }
}

bool cose_crypto_is_aead(cose_algo_t algo)
{
    switch(algo) {
        case COSE_ALGO_CHACHA20POLY1305:
            return true;
        default:
            return false;
    }
}

int cose_crypto_aead(uint8_t *c,
        size_t *clen,
        const uint8_t *msg,
        size_t msglen,
        const uint8_t *aad,
        size_t aadlen,
        const uint8_t *nsec,
        const uint8_t *npub,
        const uint8_t *key,
        cose_algo_t algo)
{
    switch(algo) {
#ifdef HAVE_ALGO_CHACHA20POLY1305
        case COSE_ALGO_CHACHA20POLY1305:
            return cose_crypto_aead_encrypt_chachapoly(c, clen, msg, msglen, aad, aadlen, npub, key);
#endif /* HAVE_ALGO_CHACHA20POLY1305 */
        default:
            (void)c;
            (void)clen;
            (void)msg;
            (void)msglen;
            (void)aad;
            (void)aadlen;
            (void)nsec;
            (void)npub;
            (void)key;
            return COSE_ERR_NOTIMPLEMENTED;
    }
}

ssize_t cose_crypto_aead_nonce_size(cose_algo_t algo)
{
    switch(algo) {
#ifdef HAVE_ALGO_CHACHA20POLY1305
        case COSE_ALGO_CHACHA20POLY1305:
            return COSE_CRYPTO_AEAD_CHACHA20POLY1305_NONCEBYTES;
#endif /* HAVE_ALGO_CHACHA20POLY1305 */
        default:
            return COSE_ERR_NOTIMPLEMENTED;
    }
}

int cose_crypto_sign(const cose_key_t *key, uint8_t *sign, size_t *signlen, uint8_t *msg, unsigned long long int msglen)
{
    switch(key->algo) {
#ifdef HAVE_ALGO_ECDSA
        case COSE_ALGO_ES256:
        case COSE_ALGO_ES384:
        case COSE_ALGO_ES512:
            return cose_crypto_sign_ecdsa(key, sign, signlen, msg, msglen);
            break;
#endif
#ifdef HAVE_ALGO_EDDSA
        case COSE_ALGO_EDDSA:
            /* Needs to be splitted as soon as ed448 support is required */
            return cose_crypto_sign_ed25519(key, sign, signlen, msg, msglen);
            break;
#endif
        default:
            return COSE_ERR_NOTIMPLEMENTED;
    }
    return 0;
}

int cose_crypto_verify(const cose_key_t *key, const uint8_t *sign, size_t signlen, uint8_t *msg, uint64_t msglen)
{
    switch(key->algo) {
#ifdef HAVE_ALGO_ECDSA
        case COSE_ALGO_ES256:
        case COSE_ALGO_ES384:
        case COSE_ALGO_ES512:
            return cose_crypto_verify_ecdsa(key, sign, signlen, msg, msglen);
            break;
#endif
#ifdef HAVE_ALGO_EDDSA
        case COSE_ALGO_EDDSA:
            /* Needs to be splitted as soon as ed448 support is required */
            return cose_crypto_verify_ed25519(key, sign, signlen, msg, msglen);
            break;
#endif
        default:
            return COSE_ERR_NOTIMPLEMENTED;
    }
    return 0;
}

size_t cose_crypto_sig_size(const cose_key_t *key)
{
    switch(key->algo) {
#ifdef HAVE_ALGO_ECDSA
        case COSE_ALGO_ES256:
        case COSE_ALGO_ES384:
        case COSE_ALGO_ES512:
            return cose_crypto_sig_size_ecdsa(key->crv);
            break;
#endif
#ifdef HAVE_ALGO_EDDSA
        case COSE_ALGO_EDDSA:
            /* Needs to be splitted as soon as ed448 support is required */
            return cose_crypto_sig_size_ed25519();
            break;
#endif
        default:
            return COSE_ERR_NOTIMPLEMENTED;
    }
    return 0;
}
