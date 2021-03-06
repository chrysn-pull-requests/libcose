/*
 * Copyright (C) 2018 Freie Universitat Berlin
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    cose_hdr COSE header manipulation definitions
 * @ingroup     cose
 *
 * COSE protected and unprotected header manipulation functions
 * @{
 *
 * @file
 * @brief       API definitions for COSE header manipulation
 *
 * @author      Koen Zandberg <koen@bergzand.net>
*/
#ifndef COSE_HDR_H
#define COSE_HDR_H

#include "cose_defines.h"
#include <nanocbor/nanocbor.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name COSE header struct
 * @{
 */
typedef struct cose_hdr {
    struct cose_hdr *next;      /**< Next header in list */
    int32_t key;                /**< Header label */
    size_t len;                 /**< Length of the data, only used for the byte type */
    union {                     /**< Depending on the type, the content is a pointer or an integer */
        int32_t value;          /**< Direct integer value */
        const uint8_t *data;    /**< Pointer to the content */
        const char *str;        /**< String type content */
        const uint8_t *cbor;    /**< CBOR type content */
    } v;                        /**< Union to combine different value types */
    cose_hdr_type_t type;       /**< Type of the header */
} cose_hdr_t;
/** @} */

/**
 * @name COSE header pack
 *
 * Struct packing both header buckets. Unions are used for multiplexing the
 * headers in struct or in cbor byte array form. the byte array form is used
 * when the unprot_len member is nonzero.
 */
typedef struct {
    cose_hdr_t *prot;   /**< Ptr to the linked list struct headers */
    cose_hdr_t *unprot; /**< Ptr to the linked list struct headers */
} cose_headers_t;

/**
 * Format header with an integer based value
 *
 * @param   hdr         The header to modify
 * @param   key         The key to add
 * @param   value       The value to set in the header
 */
void cose_hdr_format_int(cose_hdr_t *hdr, int32_t key, int32_t value);

/**
 * Format header with a string based value
 *
 * @param   hdr         The header to modify
 * @param   key         The key to add
 * @param   str         zero terminated string to set
 */
void cose_hdr_format_string(cose_hdr_t *hdr, int32_t key, const char *str);

/**
 * Format header with a byte array based value
 *
 * @param   hdr         The header to modify
 * @param   key         The key to add
 * @param   data        The byte array to add
 * @param   len         Length of the byte array
 */
void cose_hdr_format_data(cose_hdr_t *hdr, int32_t key, const uint8_t *data,
        size_t len);

/**
 * Iterate over the headers and add them to a supplied cbor map
 *
 * @param   hdr     Header struct array to feed from
 * @param   map     CborEncoder map
 *
 * @return          0 on success
 */
int cose_hdr_encode_to_map(const cose_hdr_t *hdr, nanocbor_encoder_t *map);

/**
 * Retrieve the size of a list of cose_hdr_t structs
 *
 * @param   hdr     The first header in a list, can be NULL
 *
 * @return          The number of headers in the list
 */
size_t cose_hdr_size(const cose_hdr_t *hdr);

/**
 * Insert a new header into the list
 *
 * @param   hdrs    The first header in a list
 * @param   nhdr    New header to insert
 */
void cose_hdr_insert(cose_hdr_t **hdrs, cose_hdr_t *nhdr);

/**
 * Retrieve a header from the protected bucket by key
 *
 * @param   headers Header array to search
 * @param   hdr     hdr struct to fill
 * @param   key     Key to look for
 *
 * @return          True when matching header is found
 */
bool cose_hdr_get_protected(cose_headers_t *headers, cose_hdr_t *hdr, int32_t key);

/**
 * Retrieve a header from the unprotected bucket by key
 *
 * @param   headers Header array to search
 * @param   hdr     hdr struct to fill
 * @param   key     Key to look for
 *
 * @return          True when matching header is found
 */
bool cose_hdr_get_unprotected(cose_headers_t *headers, cose_hdr_t *hdr, int32_t key);

/**
 * Retrieve a header from either the protected or the unprotected bucket by key
 *
 * @param   headers Header array to search
 * @param   hdr     hdr struct to fill
 * @param   key     Key to look for
 *
 * @return          True when matching header is found
 */
bool cose_hdr_get(cose_headers_t *headers, cose_hdr_t *hdr,
        int32_t key);

/**
 * Decode a cbor header map and retrieve the header with the specified key
 *
 * @param   buf     Buffer containing the CBOR encoded map
 * @param   len     length of the buffer
 * @param   hdr     hdr struct to fill
 * @param   key     Key to look for
 *
 * @return          true if decoding succeeded
 */
bool cose_hdr_decode_from_cbor(const uint8_t *buf, size_t len, cose_hdr_t *hdr, int32_t key);
#ifdef __cplusplus
}
#endif

#endif
/** @} */
