/*
 * Copyright (C) 2016 Southern Storm Software, Pty Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "noise/defines.h"

#ifndef NOISE_CONSTANTS_H
#define NOISE_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Build an identifier.  Deliberately designed to fit into a 16-bit
   integer on 8-bit and 16-bit embedded systems */
#define NOISE_ID(ch,num)                ((((int)(ch)) << 8) | ((int)(num)))

/* AEAD cipher algorithms */
#define NOISE_CIPHER_NONE               0
#define NOISE_CIPHER_CATEGORY           NOISE_ID('C', 0)
#if NOISE_USE_CHACHAPOLY
#define NOISE_CIPHER_CHACHAPOLY         NOISE_ID('C', 1)
#endif
#if NOISE_USE_AES
#define NOISE_CIPHER_AESGCM             NOISE_ID('C', 2)
#endif

/* Hash algorithms */
#define NOISE_HASH_NONE                 0
#define NOISE_HASH_CATEGORY             NOISE_ID('H', 0)
#if NOISE_USE_BLAKE2S
#define NOISE_HASH_BLAKE2s              NOISE_ID('H', 1)
#endif
#if NOISE_USE_BLAKE2B
#define NOISE_HASH_BLAKE2b              NOISE_ID('H', 2)
#endif
#if NOISE_USE_SHA256
#define NOISE_HASH_SHA256               NOISE_ID('H', 3)
#endif
#if NOISE_USE_SHA512
#define NOISE_HASH_SHA512               NOISE_ID('H', 4)
#endif

/* Diffie-Hellman algorithms */
#define NOISE_DH_NONE                   0
#define NOISE_DH_CATEGORY               NOISE_ID('D', 0)
#if NOISE_USE_CURVE25519
#define NOISE_DH_CURVE25519             NOISE_ID('D', 1)
#endif
#if NOISE_USE_CURVE448
#define NOISE_DH_CURVE448               NOISE_ID('D', 2)
#endif
#if NOISE_USE_NEWHOPE
#define NOISE_DH_NEWHOPE                NOISE_ID('D', 3)
#endif

/* Handshake patterns */
#define NOISE_PATTERN_NONE              0
#define NOISE_PATTERN_CATEGORY          NOISE_ID('P', 0)
#define NOISE_PATTERN_N                 NOISE_ID('P', 1)
#define NOISE_PATTERN_X                 NOISE_ID('P', 2)
#define NOISE_PATTERN_K                 NOISE_ID('P', 3)
#define NOISE_PATTERN_NN                NOISE_ID('P', 4)
#define NOISE_PATTERN_NK                NOISE_ID('P', 5)
#define NOISE_PATTERN_NX                NOISE_ID('P', 6)
#define NOISE_PATTERN_XN                NOISE_ID('P', 7)
#define NOISE_PATTERN_XK                NOISE_ID('P', 8)
#define NOISE_PATTERN_XX                NOISE_ID('P', 9)
#define NOISE_PATTERN_KN                NOISE_ID('P', 10)
#define NOISE_PATTERN_KK                NOISE_ID('P', 11)
#define NOISE_PATTERN_KX                NOISE_ID('P', 12)
#define NOISE_PATTERN_IN                NOISE_ID('P', 13)
#define NOISE_PATTERN_IK                NOISE_ID('P', 14)
#define NOISE_PATTERN_IX                NOISE_ID('P', 15)

/* Handshake pattern modifiers */
#define NOISE_MODIFIER_NONE             0
#define NOISE_MODIFIER_CATEGORY         NOISE_ID('M', 0)
#define NOISE_MODIFIER_FALLBACK         NOISE_ID('M', 1)
#define NOISE_MODIFIER_HFS              NOISE_ID('M', 2)
#define NOISE_MODIFIER_PSK0             NOISE_ID('M', 20)
#define NOISE_MODIFIER_PSK1             NOISE_ID('M', 21)
#define NOISE_MODIFIER_PSK2             NOISE_ID('M', 22)
#define NOISE_MODIFIER_PSK3             NOISE_ID('M', 23)

/* Protocol name prefixes */
#define NOISE_PREFIX_NONE               0
#define NOISE_PREFIX_CATEGORY           NOISE_ID('N', 0)
#define NOISE_PREFIX_STANDARD           NOISE_ID('N', 1)

#if NOISE_USE_SIGN
/* Signature algorithms */
#define NOISE_SIGN_NONE                 0
#define NOISE_SIGN_CATEGORY             NOISE_ID('S', 0)
#define NOISE_SIGN_ED25519              NOISE_ID('S', 1)
#endif

/* Role for this end of the communications */
#define NOISE_ROLE_INITIATOR            NOISE_ID('R', 1)
#define NOISE_ROLE_RESPONDER            NOISE_ID('R', 2)

/* Actions for the application to take, as directed by the HandshakeState */
#define NOISE_ACTION_NONE               0
#define NOISE_ACTION_WRITE_MESSAGE      NOISE_ID('A', 1)
#define NOISE_ACTION_READ_MESSAGE       NOISE_ID('A', 2)
#define NOISE_ACTION_FAILED             NOISE_ID('A', 3)
#define NOISE_ACTION_SPLIT              NOISE_ID('A', 4)
#define NOISE_ACTION_COMPLETE           NOISE_ID('A', 5)

/* Padding modes for noise_cipherstate_pad() */
#define NOISE_PADDING_ZERO              NOISE_ID('G', 1)
#define NOISE_PADDING_RANDOM            NOISE_ID('G', 2)

/* Key fingerprint types */
#define NOISE_FINGERPRINT_BASIC         NOISE_ID('F', 1)
#define NOISE_FINGERPRINT_FULL          NOISE_ID('F', 2)

/* Error codes */
#define NOISE_ERROR_NONE                0
#define NOISE_ERROR_NO_MEMORY           NOISE_ID('E', 1)
#define NOISE_ERROR_UNKNOWN_ID          NOISE_ID('E', 2)
#define NOISE_ERROR_UNKNOWN_NAME        NOISE_ID('E', 3)
#define NOISE_ERROR_MAC_FAILURE         NOISE_ID('E', 4)
#define NOISE_ERROR_NOT_APPLICABLE      NOISE_ID('E', 5)
#define NOISE_ERROR_SYSTEM              NOISE_ID('E', 6)
#define NOISE_ERROR_REMOTE_KEY_REQUIRED NOISE_ID('E', 7)
#define NOISE_ERROR_LOCAL_KEY_REQUIRED  NOISE_ID('E', 8)
#define NOISE_ERROR_PSK_REQUIRED        NOISE_ID('E', 9)
#define NOISE_ERROR_INVALID_LENGTH      NOISE_ID('E', 10)
#define NOISE_ERROR_INVALID_PARAM       NOISE_ID('E', 11)
#define NOISE_ERROR_INVALID_STATE       NOISE_ID('E', 12)
#define NOISE_ERROR_INVALID_NONCE       NOISE_ID('E', 13)
#define NOISE_ERROR_INVALID_PRIVATE_KEY NOISE_ID('E', 14)
#define NOISE_ERROR_INVALID_PUBLIC_KEY  NOISE_ID('E', 15)
#define NOISE_ERROR_INVALID_FORMAT      NOISE_ID('E', 16)
#define NOISE_ERROR_INVALID_SIGNATURE   NOISE_ID('E', 17)

/* Maximum length of a packet payload */
#define NOISE_MAX_PAYLOAD_LEN           65535

/* Maximum length of a protocol name string including terminating '\0' */
#define NOISE_MAX_PROTOCOL_NAME         256

/* Recommended maximum length for fingerprint buffers */
#define NOISE_MAX_FINGERPRINT_LEN       256

/* Maximum number of modifiers to a base pattern name */
#define NOISE_MAX_MODIFIER_IDS          16

#ifdef __cplusplus
};
#endif

#endif
