#pragma once

struct message_collection_definition {
    typedef void* (*encode_function_type)(void* packet, int message_storage_size, void* message);
    typedef void* (*decode_function_type)(void* packet, int message_storage_size, void* message);

    struct message_definition {
        bool initialized;
        char padding[7];
        const char* message_type_name;
        int message_flags;
        int message_size;
        int message_size_maximum;
        int un;
        encode_function_type encode_function;
        decode_function_type decode_function;
        void* un1;
        void* un2;
    } messages[46];

    static_assert(sizeof(message_definition) == 1 << 6);
};
