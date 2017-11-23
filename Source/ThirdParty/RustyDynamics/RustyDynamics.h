#pragma once

extern "C" {

    typedef struct TestEntity {
                         float x;
                         float y;
                     } TestEntity;

    typedef struct TestWorld {
        uint64_t entities_ptr;
        uint64_t entities_cap;
        uint64_t entities_len;
    } TestWorld;

    typedef struct RustVec {
        size_t vec_ptr;
        size_t vec_cap;
        size_t vec_len;
    } RustVec;

    typedef struct AvatarPack {
        uint16_t id;
        float px, py, pz, pw;
        float rx, ry, rz, rw;
    } AvatarPack;

    typedef struct RigidBodyPack {
        uint16_t id;
        float px, py, pz, pw;
        float lx, ly, lz, lw;
        // float rx, ry, rz;
        // float ax, ay, az;
    } RigidBodyPack;

    typedef struct WorldPack {
        RustVec avatarparts;
        RustVec rigidbodies;
    } WorldPack;

    typedef struct SystemPack {
        RustVec system;
    } SystemPack;

    void rb_log_fn(void (*log_fn)(const char*));

    void* rd_netclient_open(const char* local_addr, const char* server_addr, const char* mumble_addr);
    void rd_netclient_drop(void* client);
    void rd_netclient_msg_push(void* client, const uint8* bytes, uint32_t count);
    RustVec* rd_netclient_msg_pop(void* client);
    void rd_netclient_msg_drop(RustVec* msg);

    void rd_netclient_push_world(void* client, const WorldPack* world);
    WorldPack* rd_netclient_dec_world(const uint8* bytes, uint32_t count);
    void rd_netclient_drop_world(WorldPack* world);

    void rd_netclient_push_avatar(void* client, const AvatarPack* avatar);
    AvatarPack* rd_netclient_dec_avatar(const uint8* bytes, uint32_t count);
    void rd_netclient_drop_avatar(AvatarPack* avatar);

    void rd_netclient_test_world(const TestWorld* world);
    void rd_netclient_real_world(const WorldPack* world);
}
