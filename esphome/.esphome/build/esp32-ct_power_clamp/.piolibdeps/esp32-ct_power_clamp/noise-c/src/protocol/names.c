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

#include "protocol/internal.h"
#include <string.h>

/**
 * \file names.h
 * \brief Mapping algorithm names to/from identifiers
 */

/**
 * \file names.c
 * \brief Implementation of algorithm name mapping
 */

/**
 * \defgroup names Algorithm name lookup API
 */
/**@{*/

/**
 * \struct NoiseProtocolId
 * \brief Noise protocol name broken out into separate identifier fields.
 */

/** @cond */

/* List of all known algorithm names and the corresponding identifiers */
typedef struct
{
    int id;
    const char *name;
    size_t name_len;

} NoiseIdMapping;
static NoiseIdMapping const algorithm_names[] = {
    /* Cipher algorithsm */
#if NOISE_USE_CHACHAPOLY
    {NOISE_CIPHER_CHACHAPOLY,   "ChaChaPoly",   10},
#endif
#if NOISE_USE_AES
    {NOISE_CIPHER_AESGCM,       "AESGCM",        6},
#endif

    /* Hash algorithms */
#if NOISE_USE_BLAKE2S
    {NOISE_HASH_BLAKE2s,        "BLAKE2s",       7},
#endif
#if NOISE_USE_BLAKE2B
    {NOISE_HASH_BLAKE2b,        "BLAKE2b",       7},
#endif
#if NOISE_USE_SHA256
    {NOISE_HASH_SHA256,         "SHA256",        6},
#endif
#if NOISE_USE_SHA512
    {NOISE_HASH_SHA512,         "SHA512",        6},
#endif

    /* Diffie-Hellman algorithms */
#if NOISE_USE_CURVE25519
    {NOISE_DH_CURVE25519,       "25519",         5},
#endif
#if NOISE_USE_CURVE448
    {NOISE_DH_CURVE448,         "448",           3},
#endif
#if NOISE_USE_NEWHOPE
    {NOISE_DH_NEWHOPE,          "NewHope",       7},
#endif

    /* Handshake patterns */
    {NOISE_PATTERN_N,           "N",             1},
    {NOISE_PATTERN_X,           "X",             1},
    {NOISE_PATTERN_K,           "K",             1},
    {NOISE_PATTERN_NN,          "NN",            2},
    {NOISE_PATTERN_NK,          "NK",            2},
    {NOISE_PATTERN_NX,          "NX",            2},
    {NOISE_PATTERN_XN,          "XN",            2},
    {NOISE_PATTERN_XK,          "XK",            2},
    {NOISE_PATTERN_XX,          "XX",            2},
    {NOISE_PATTERN_KN,          "KN",            2},
    {NOISE_PATTERN_KK,          "KK",            2},
    {NOISE_PATTERN_KX,          "KX",            2},
    {NOISE_PATTERN_IN,          "IN",            2},
    {NOISE_PATTERN_IK,          "IK",            2},
    {NOISE_PATTERN_IX,          "IX",            2},

    /* Handshake pattern modifiers */
    {NOISE_MODIFIER_FALLBACK,   "fallback",      8},
    {NOISE_MODIFIER_HFS,        "hfs",           3},
    {NOISE_MODIFIER_PSK0,       "psk0",          4},
    {NOISE_MODIFIER_PSK1,       "psk1",          4},
    {NOISE_MODIFIER_PSK2,       "psk2",          4},
    {NOISE_MODIFIER_PSK3,       "psk3",          4},

    /* Protocol name prefixes */
    {NOISE_PREFIX_STANDARD,     "Noise",         5},

#if NOISE_USE_ED25519
    /* Signature algorithms */
    {NOISE_SIGN_ED25519,        "Ed25519",       7},
#endif

    /* Terminator for the list */
    {0,                         0,               0}
};

/** @endcond */

/**
 * \brief Maps an algorithm name to the corresponding identifier.
 *
 * \param category The category of identifier to look for; one of
 * NOISE_CIPHER_CATEGORY, NOISE_HASH_CATEGORY, NOISE_DH_CATEGORY,
 * NOISE_PATTERN_CATEGORY, NOISE_PREFIX_CATEGORY, NOISE_SIGN_CATEGORY,
 * NOISE_MODIFIER_CATEGORY, or zero.  Zero indicates "any category".
 * \param name Points to the name to map.
 * \param name_len Length of the \a name in bytes.
 *
 * \return The algorithm identifier, or zero if the name is unknown
 * in the specified \a category.
 *
 * The \a category parameter can be used to restrict the search to
 * algorithms of a certain type.  If the \a name is valid for some other
 * category, that mapping will be ignored.
 *
 * \sa noise_id_to_name()
 */
int noise_name_to_id(int category, const char *name, size_t name_len)
{
    const NoiseIdMapping *mapping = algorithm_names;
    int mask = category ? NOISE_ID(0xFF, 0) : 0;
    if (!name)
        return 0;
    while (mapping->name_len) {
        if ((mapping->id & mask) == category) {
            if (mapping->name_len == name_len &&
                    !memcmp(mapping->name, name, name_len)) {
                return mapping->id;
            }
        }
        ++mapping;
    }
    return 0;
}

/**
 * \brief Maps an algorithm identifier to the corresponding name.
 *
 * \param category The category of identifier to look for; one of
 * NOISE_CIPHER_CATEGORY, NOISE_HASH_CATEGORY, NOISE_DH_CATEGORY,
 * NOISE_PATTERN_CATEGORY, NOISE_PREFIX_CATEGORY, NOISE_SIGN_CATEGORY,
 * NOISE_MODIFIER_CATEGORY, or zero.  Zero indicates "any category".
 * \param id The algorithm identifier to map.
 *
 * \return The NUL-terminated name of the algorithm, or NULL if the
 * \a id is unknown in the specified \a category.
 *
 * The \a category parameter can be used to restrict the search to
 * algorithms of a certain type.  If the \a id is valid for some other
 * category, that mapping will be ignored.
 *
 * \sa noise_name_to_id()
 */
const char *noise_id_to_name(int category, int id)
{
    const NoiseIdMapping *mapping = algorithm_names;
    int mask = category ? NOISE_ID(0xFF, 0) : 0;
    if (id <= 0)
        return 0;
    while (mapping->name_len) {
        if ((mapping->id & mask) == category) {
            if (mapping->id == id)
                return mapping->name;
        }
        ++mapping;
    }
    return 0;
}

/**
 * \brief Maps a '+'-separated algorithm name into a list of identifier.
 *
 * \param ids Returns the list of identifiers parsed from the \a name.
 * \param ids_len The maximum length of \a ids.
 * \param name Points to the name to map.
 * \param name_len Length of the \a name in bytes.
 * \param category1 The category of the first identifier in the list; one of
 * NOISE_CIPHER_CATEGORY, NOISE_HASH_CATEGORY, NOISE_DH_CATEGORY,
 * NOISE_PATTERN_CATEGORY, NOISE_PREFIX_CATEGORY, NOISE_SIGN_CATEGORY,
 * NOISE_MODIFIER_CATEGORY.
 * \param category2 The category of the second and subsequent identifiers
 * in the list; one of NOISE_CIPHER_CATEGORY, NOISE_HASH_CATEGORY,
 * NOISE_DH_CATEGORY, NOISE_PATTERN_CATEGORY, NOISE_PREFIX_CATEGORY,
 * NOISE_SIGN_CATEGORY, NOISE_MODIFIER_CATEGORY, or zero.  Zero indicates
 * that the second category is identical to \a category1.
 *
 * \return The number of elements in the returned list or a negative
 * error code otherwise.
 *
 * The algorithm names are expected to be separated with the '+'
 * character.  As a special case when \a category1 is NOISE_PATTERN_CATEGORY
 * and \category2 is NOISE_MODIFIER_CATEGORY, the first and second identifiers
 * may be directly concatenated.
 *
 * \sa noise_ids_to_name_list()
 */
int noise_name_list_to_ids(int *ids, size_t ids_len,
                           const char *name, size_t name_len,
                           int category1, int category2)
{
    size_t index = 0;
    size_t field_len;
    int id;

    /* Validate the parameters */
    if (!ids || !name)
        return -NOISE_ERROR_INVALID_PARAM;
    if (!category2)
        category2 = category1;

    /* Extract the first identifier.  Special case for patterns */
    if (category1 == NOISE_PATTERN_CATEGORY &&
            category2 == NOISE_MODIFIER_CATEGORY) {
        field_len = 0;
        while (field_len < name_len && name[field_len] >= 'A' &&
               name[field_len] <= 'Z') {
            ++field_len;
        }
        if (field_len < name_len && name[field_len] == '+') {
            /* Pattern base names cannot be followed by a '+'.
               The first modifier should up right up against the name. */
            return -NOISE_ERROR_UNKNOWN_NAME;
        }
        id = noise_name_to_id(category1, name, field_len);
        name += field_len;
        name_len -= field_len;
    } else {
        field_len = 0;
        while (field_len < name_len && name[field_len] != '+') {
            ++field_len;
        }
        id = noise_name_to_id(category1, name, field_len);
        if (field_len < name_len) {
            /* Skip the '+' separator and check that we have more text */
            ++field_len;
            if (field_len >= name_len) {
                /* Name lists cannot end in '+' */
                return -NOISE_ERROR_UNKNOWN_NAME;
            }
        }
        name += field_len;
        name_len -= field_len;
    }
    if (!id) {
        /* Unknown name for the primary identifier */
        return -NOISE_ERROR_UNKNOWN_NAME;
    }
    if (index >= ids_len) {
        /* Not enough room in the return array */
        return -NOISE_ERROR_INVALID_LENGTH;
    }
    ids[index++] = id;

    /* Parse the secondary identifiers */
    while (name_len > 0) {
        field_len = 0;
        while (field_len < name_len && name[field_len] != '+') {
            ++field_len;
        }
        id = noise_name_to_id(category2, name, field_len);
        if (!id) {
            /* Unknown name for a secondary identifier */
            return -NOISE_ERROR_UNKNOWN_NAME;
        }
        if (field_len < name_len) {
            /* Skip the '+' separator and check that we have more text */
            ++field_len;
            if (field_len >= name_len) {
                /* Name lists cannot end in '+' */
                return -NOISE_ERROR_UNKNOWN_NAME;
            }
        }
        name += field_len;
        name_len -= field_len;
        if (index >= ids_len) {
            /* Not enough room in the return array */
            return -NOISE_ERROR_INVALID_LENGTH;
        }
        ids[index++] = id;
    }

    /* Return the length of the parsed list to the caller */
    return (int)index;
}

/**
 * \brief Maps a list of algorithm identifiers to the corresponding name.
 *
 * \param name Output buffer for the name.
 * \param name_len Length of the output buffer.
 * \param ids List of algorithm identifiers to map.
 * \param ids_len Number of algorithm identifiers in \a ids.
 * \param category1 The category of the first identifier in the list; one of
 * NOISE_CIPHER_CATEGORY, NOISE_HASH_CATEGORY, NOISE_DH_CATEGORY,
 * NOISE_PATTERN_CATEGORY, NOISE_PREFIX_CATEGORY, NOISE_SIGN_CATEGORY,
 * NOISE_MODIFIER_CATEGORY.
 * \param category2 The category of the second and subsequent identifiers
 * in the list; one of NOISE_CIPHER_CATEGORY, NOISE_HASH_CATEGORY,
 * NOISE_DH_CATEGORY, NOISE_PATTERN_CATEGORY, NOISE_PREFIX_CATEGORY,
 * NOISE_SIGN_CATEGORY, NOISE_MODIFIER_CATEGORY, or zero.  Zero indicates
 * that the second category is identical to \a category1.
 *
 * \return NOISE_ERROR_NONE on success.
 * \return NOISE_ERROR_INVALID_PARAM if \a name or \a ids are NULL,
 * or \a name_len or \a ids_len is zero.
 * \return NOISE_ERROR_UNKNOWN_ID if one or more of the identifiers in
 * the \a ids array is unknown.
 * \return NOISE_ERROR_INVALID_LENGTH if \a name_len is not large
 * enough to hold the full name plus a terminating '\0'.
 *
 * The algorithm names in the list will be separated with the '+'
 * character.  As a special case when \a category1 is NOISE_PATTERN_CATEGORY
 * and \category2 is NOISE_MODIFIER_CATEGORY, the first and second identifiers
 * will be directly concatenated.
 *
 * \sa noise_name_list_to_ids()
 */
int noise_ids_to_name_list(char *name, size_t name_len,
                           const int *ids, size_t ids_len,
                           int category1, int category2)
{
    const char *component;
    size_t component_len;
    size_t index = 0;

    /* Validate the parameters */
    if (!name || !name_len)
        return NOISE_ERROR_INVALID_PARAM;
    *name = '\0';
    if (!ids || !ids_len)
        return NOISE_ERROR_INVALID_PARAM;
    if (!category2)
        category2 = category1;

    /* Output the first identifier followed optionally by a '+' separator */
    component = noise_id_to_name(category1, ids[index++]);
    if (!component)
        return NOISE_ERROR_UNKNOWN_ID;
    component_len = strlen(component);
    if (component_len >= name_len)
        return NOISE_ERROR_INVALID_LENGTH;
    memcpy(name, component, component_len);
    name += component_len;
    name_len -= component_len;
    name[0] = '\0';
    if (index < ids_len && (category1 != NOISE_PATTERN_CATEGORY ||
                            category2 != NOISE_MODIFIER_CATEGORY)) {
        if (name_len < 2)
            return NOISE_ERROR_INVALID_LENGTH;
        name[0] = '+';
        name[1] = '\0';
        ++name;
        --name_len;
    }

    /* Output the remaining identifiers separated by '+' */
    while (index < ids_len) {
        component = noise_id_to_name(category2, ids[index++]);
        if (!component)
            return NOISE_ERROR_UNKNOWN_ID;
        component_len = strlen(component);
        if (component_len >= name_len)
            return NOISE_ERROR_INVALID_LENGTH;
        memcpy(name, component, component_len);
        name += component_len;
        name_len -= component_len;
        name[0] = '\0';
        if (index < ids_len) {
            if (name_len < 2)
                return NOISE_ERROR_INVALID_LENGTH;
            name[0] = '+';
            name[1] = '\0';
            ++name;
            --name_len;
        }
    }
    return NOISE_ERROR_NONE;
}

/**
 * \brief Parses a field from a protocol name string.
 *
 * \param category The category of identifier that we expect in this field.
 * \param name Points to the start of the protocol name string.
 * \param len The total length of the protocol name string.
 * \param posn The current position in the string, updated once the next
 * field has been parsed.
 * \param is_last Non-zero if this is the last expected field, or zero
 * if we expect further fields to follow.
 * \param ok Initialized to non-zero by the caller.  Will be set to zero
 * if a parse error was encountered.
 *
 * \return The algorithm identifier for the current field, or zero
 * if the field's contents are not a recognized name for this field.
 */
static int noise_protocol_parse_field
    (int category, const char *name, size_t len, size_t *posn,
     int is_last, int *ok)
{
    size_t start, field_len;
    int id;

    /* If the parse already failed, then nothing further to do */
    if (!(*ok))
        return 0;

    /* Find the start and end of the current field */
    start = *posn;
    while (*posn < len && name[*posn] != '_')
        ++(*posn);
    field_len = *posn - start;

    /* If this is the last field, we should be at the end
       of the string.  Otherwise there should be a '_' here */
    if (is_last) {
        if (*posn < len) {
            *ok = 0;
            return 0;
        }
    } else {
        if (*posn >= len) {
            *ok = 0;
            return 0;
        }
        ++(*posn);  /* Skip the '_' */
    }

    /* Look up the name in the current category */
    id = noise_name_to_id(category, name + start, field_len);
    if (!id)
        *ok = 0;
    return id;
}

/**
 * \brief Parses a pattern name field from a protocol name string.
 *
 * \param modifiers Returns the modifiers for the pattern.
 * \param name Points to the start of the protocol name string.
 * \param len The total length of the protocol name string.
 * \param posn The current position in the string, updated once the next
 * field has been parsed.
 * \param is_last Non-zero if this is the last expected field, or zero
 * if we expect further fields to follow.
 * \param ok Initialized to non-zero by the caller.  Will be set to zero
 * if a parse error was encountered.
 *
 * \return The algorithm identifier for the pattern, or zero
 * if the field's contents are invalid.
 */
static int noise_protocol_parse_pattern_field
    (int modifiers[NOISE_MAX_MODIFIER_IDS], const char *name,
     size_t len, size_t *posn, int *ok)
{
    size_t start, field_len;
    int ids[NOISE_MAX_MODIFIER_IDS + 1];
    int num_ids;

    /* If the parse already failed, then nothing further to do */
    if (!(*ok))
        return 0;

    /* Find the start and end of the current field */
    start = *posn;
    while (*posn < len && name[*posn] != '_')
        ++(*posn);
    field_len = *posn - start;

    /* There should be a '_' here */
    if (*posn >= len) {
        *ok = 0;
        return 0;
    }
    ++(*posn);  /* Skip the '_' */

    /* Parse the field into pattern and modifier identifiers */
    num_ids = noise_name_list_to_ids
        (ids, NOISE_MAX_MODIFIER_IDS + 1, name + start, field_len,
         NOISE_PATTERN_CATEGORY, NOISE_MODIFIER_CATEGORY);
    if (num_ids < 1) {
        *ok = 0;
        return 0;
    }
    memcpy(modifiers, ids + 1, (num_ids - 1) * sizeof(int));
    return ids[0];
}

/**
 * \brief Parses a dual field from a protocol name string; "field1+field2"
 * or simply "field1".
 *
 * \param category The category of identifier that we expect in this field.
 * \param name Points to the start of the protocol name string.
 * \param len The total length of the protocol name string.
 * \param posn The current position in the string, updated once the next
 * field has been parsed.
 * \param second_id Points to a variable to be set to the second identifier.
 * \param ok Initialized to non-zero by the caller.  Will be set to zero
 * if a parse error was encountered.
 *
 * \return The algorithm identifier for the first component of the
 * current field, or zero if the field's contents are not a recognized
 * dual name for this field.
 */
static int noise_protocol_parse_dual_field
    (int category, const char *name, size_t len,
     size_t *posn, int *second_id, int *ok)
{
    size_t start, field_len;
    int ids[2];
    int num_ids;

    /* Clear the second identifier before we start in case we don't find one */
    *second_id = 0;

    /* If the parse already failed, then nothing further to do */
    if (!(*ok))
        return 0;

    /* Find the start and end of the current field */
    start = *posn;
    while (*posn < len && name[*posn] != '_')
        ++(*posn);
    if (*posn >= len) {
        /* Should be terminated with '_' */
        *ok = 0;
        return 0;
    }
    field_len = *posn - start;

    /* Skip the terminating '_' */
    ++(*posn);

    /* Parse the dual field */
    num_ids = noise_name_list_to_ids(ids, 2, name + start, field_len,
                                     category, category);
    if (num_ids < 1) {
        *ok = 0;
        return 0;
    }
    if (num_ids >= 2)
        *second_id = ids[1];
    return ids[0];
}

/**
 * \brief Parses a protocol name into a set of identifiers for the
 * algorithms that are indicated by the name.
 *
 * \param id The resulting structure to populate with identifiers.
 * \param name Points to the start of the protocol name.
 * \param name_len The length of the protocol name in bytes.
 *
 * \return NOISE_ERROR_NONE on success.
 * \return NOISE_ERROR_INVALID_PARAM if either \a id or \a name is NULL.
 * \return NOISE_ERROR_UNKNOWN_NAME if the protocol name could not be parsed.
 *
 * \sa noise_protocol_id_to_name()
 */
int noise_protocol_name_to_id
    (NoiseProtocolId *id, const char *name, size_t name_len)
{
    size_t posn;
    int ok;

    /* Bail out if the parameters are incorrect */
    if (!id || !name)
        return NOISE_ERROR_INVALID_PARAM;

    /* Parse underscore-separated fields from the name */
    posn = 0;
    ok = 1;
    memset(id, 0, sizeof(NoiseProtocolId));
    id->prefix_id = noise_protocol_parse_field
        (NOISE_PREFIX_CATEGORY, name, name_len, &posn, 0, &ok);
    id->pattern_id = noise_protocol_parse_pattern_field
        (id->modifier_ids, name, name_len, &posn, &ok);
    id->dh_id = noise_protocol_parse_dual_field
        (NOISE_DH_CATEGORY, name, name_len, &posn, &(id->hybrid_id), &ok);
    id->cipher_id = noise_protocol_parse_field
        (NOISE_CIPHER_CATEGORY, name, name_len, &posn, 0, &ok);
    id->hash_id = noise_protocol_parse_field
        (NOISE_HASH_CATEGORY, name, name_len, &posn, 1, &ok);

    /* If there was a parse error, then clear everything */
    if (!ok) {
        memset(id, 0, sizeof(NoiseProtocolId));
        return NOISE_ERROR_UNKNOWN_NAME;
    }

    /* The name has been parsed */
    return NOISE_ERROR_NONE;
}

/**
 * \brief Formats a field within a protocol name.
 *
 * \param category The category of algorithm identifier in this field.
 * \param id The identifier to format.
 * \param name The name buffer to format the field into.
 * \param len The length of the \a name buffer in bytes.
 * \param posn The current format position within the \a name buffer.
 * \param term_char Terminator character: '_', '+', or '\0'.
 * \param err Points to an error code.  Initialized to NOISE_ERROR_NONE
 * by the caller and updated by this function if there is an error.
 */
static void noise_protocol_format_field
    (int category, int id, char *name, size_t len, size_t *posn,
     int term_char, int *err)
{
    const char *alg_name;
    size_t alg_len;

    /* If the formatting already failed, then bail out now */
    if (*err != NOISE_ERROR_NONE)
        return;

    /* Look up the name for the algorithm identifier */
    alg_name = noise_id_to_name(category, id);
    if (!alg_name) {
        *err = NOISE_ERROR_UNKNOWN_ID;
        return;
    }
    alg_len = strlen(alg_name);

    /* Will the name fit into the buffer, followed by the terminator? */
    if (alg_len >= (len - *posn)) {
        *err = NOISE_ERROR_INVALID_LENGTH;
        return;
    }
    memcpy(name + *posn, alg_name, alg_len);
    *posn += alg_len;

    /* Add either a separator or a terminator */
    if (term_char != '\0')
        name[(*posn)++] = term_char;
    else
        name[*posn] = '\0';
}

/**
 * \brief Formats a protocol name from a set of identifiers for
 * the algorithms that make up the name.
 *
 * \param name The buffer to write the protocol name to.
 * \param name_len The number of bytes of space in the \a name buffer.
 * \param id The set of identifiers to format.
 *
 * \return NOISE_ERROR_NONE on success.
 * \return NOISE_ERROR_INVALID_PARAM if either \a name or \a id is NULL.
 * \return NOISE_ERROR_INVALID_LENGTH if the \a name buffer is not large
 * enough to contain the full name.
 * \return NOISE_ERROR_UNKNOWN_ID if one of the identifiers in \a id does
 * not have a known mapping to a name.
 *
 * This function guarantees to NUL-terminate the \a name if
 * the function succeeds.
 *
 * It is recommended that \a name_len be at least NOISE_MAX_PROTOCOL_NAME
 * bytes in length.
 *
 * \sa noise_protocol_name_to_id()
 */
int noise_protocol_id_to_name
    (char *name, size_t name_len, const NoiseProtocolId *id)
{
    size_t posn, modifier_num;
    int err, term_char;

    /* Bail out if the parameters are incorrect */
    if (!id) {
        if (name && name_len)
            *name = '\0';   /* Just to be safe */
        return NOISE_ERROR_INVALID_PARAM;
    }
    if (!name)
        return NOISE_ERROR_INVALID_PARAM;
    if (!name_len)
        return NOISE_ERROR_INVALID_LENGTH;

    /* Format the fields into the return buffer */
    posn = 0;
    err = NOISE_ERROR_NONE;
    noise_protocol_format_field
        (NOISE_PREFIX_CATEGORY, id->prefix_id, name, name_len, &posn, '_', &err);
    term_char = '_';
    if (id->modifier_ids[0] != NOISE_MODIFIER_NONE)
        term_char = '\0';
    noise_protocol_format_field
        (NOISE_PATTERN_CATEGORY, id->pattern_id, name, name_len,
         &posn, term_char, &err);
    for (modifier_num = 0; modifier_num < NOISE_MAX_MODIFIER_IDS &&
         id->modifier_ids[modifier_num] != NOISE_MODIFIER_NONE; ++modifier_num) {
        /* Append the modifier names to the base pattern name */
        term_char = '+';
        if ((modifier_num + 1) >= NOISE_MAX_MODIFIER_IDS ||
                id->modifier_ids[modifier_num + 1] == NOISE_MODIFIER_NONE)
            term_char = '_';
        noise_protocol_format_field
            (NOISE_MODIFIER_CATEGORY, id->modifier_ids[modifier_num],
             name, name_len, &posn, term_char, &err);
    }
    if (!id->hybrid_id) {
        noise_protocol_format_field
            (NOISE_DH_CATEGORY, id->dh_id, name, name_len, &posn, '_', &err);
    } else {
        /* Format the DH names as "dh_id+hybrid_id"; e.g. "25519+NewHope" */
        noise_protocol_format_field
            (NOISE_DH_CATEGORY, id->dh_id, name, name_len, &posn, '+', &err);
        noise_protocol_format_field
            (NOISE_DH_CATEGORY, id->hybrid_id, name, name_len, &posn, '_', &err);
    }
    noise_protocol_format_field
        (NOISE_CIPHER_CATEGORY, id->cipher_id, name, name_len, &posn, '_', &err);
    noise_protocol_format_field
        (NOISE_HASH_CATEGORY, id->hash_id, name, name_len, &posn, '\0', &err);

    /* The reserved identifiers must be zero.  We don't know how to
       format reserved identifiers other than zero */
    for (posn = 0; posn < (sizeof(id->reserved) / sizeof(id->reserved[0])) &&
                   err == NOISE_ERROR_NONE; ++posn) {
        if (id->reserved[posn] != 0)
            err = NOISE_ERROR_UNKNOWN_ID;
    }

    /* If an error occurred, then clear the buffer just to be safe */
    if (err != NOISE_ERROR_NONE)
        *name = '\0';

    /* Done */
    return err;
}

/**@}*/
