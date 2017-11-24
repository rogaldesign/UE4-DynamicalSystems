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
        uint32_t id;
        float root_px, root_py, root_pz, root_pw;
        float root_rx, root_ry, root_rz, root_rw;
        float head_px, head_py, head_pz, head_pw;
        float head_rx, head_ry, head_rz, head_rw;
        float handL_px, handL_py, handL_pz, handL_pw;
        float handL_rx, handL_ry, handL_rz, handL_rw;
        float handR_px, handR_py, handR_pz, handR_pw;
        float handR_rx, handR_ry, handR_rz, handR_rw;
        float height, floor;
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

}
