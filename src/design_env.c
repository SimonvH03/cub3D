int set_design(int side, double x, double y, char design)
{
    t_img *p;
    int door;
    unsigned int d;

    door = (side != 3 && y >= 0 && x >= 0 && y / 50 < data.h_map && x / 50 < data.w_map[(int)y / 50] && data.map[(int)y / 50][(int)x / 50] == TILE_DOOR && data.door.c)
            || (side == 3 && data.door.hit_wall);
    if (data.door.dor && data.color[0] && side == 3)
    {
        t_door_state *door_state = get_door_at_position(&data.scene, (int)x / 50, (int)y / 50);
        if (!door_state)
            return 0xff000000;

        // Calculate texture offset based on animation progress
        float texture_offset = door_state->animation_progress * 64.0f;
        int tex_x = (int)round(data.door.color[1] * 10.0 * (64.0 / 500.0)) % 64;
        
        // Apply animation offset
        tex_x = (int)(tex_x + texture_offset) % 64;
        
        // Get color from appropriate door texture
        if (tex_x >= 0 && tex_x < 64)
        {
            d = *(unsigned int *)(data.door.door[0][door_state->is_opening ? 1 : 0].addr + 
                ((int)y * data.door.door[0][0].line_len + tex_x * (data.door.door[0][0].bpp / 8)));
            if ((unsigned int)d < 0xff000000)
                return d;
        }
        return 0xff000000;
    }
    if (door)
    {
        t_door_state *door_state = get_door_at_position(&data.scene, (int)x / 50, (int)y / 50);
        if (!door_state)
            return 0xff000000;

        // Calculate texture coordinates with animation
        float tex_x;
        switch (side)
        {
            case 1:
                tex_x = ((int)(x * 10.0 * (64.0 / 500.0)) % 64) + door_state->animation_progress * 64.0f;
                if (tex_x >= 0 && tex_x < 64)
                    return (*(int *)(data.assets.addr + (((int)(y * 10.0 * (64.0 / 500.0)) % 64 + DOOR_START__Y) * data.assets.line_len + 
                        ((int)tex_x + DOOR_START__X) * (data.assets.bpp / 8))));
                break;
            case -1:
                tex_x = ((int)x % 64) + door_state->animation_progress * 64.0f;
                if (tex_x >= 0 && tex_x < 64)
                    return (*(int *)(data.assets.addr + (((int)y % 64 + DOOR_START__Y) * data.assets.line_len + 
                        ((int)tex_x + DOOR_START__X) * (data.assets.bpp / 8))));
                break;
            default:
                return 0;
        }
        return 0xff000000;
    }

    // ... rest of the switch statement for other designs ...
    switch (design)
    {
        case 'A':
            return (room_a(side, x, y));
        case 'B':
            return (room_b(side, x, y));
        case 'C':
            return (room_c(side, x, y));
        case 'D':
            return (room_d(side, x, y));
        case 'E':
            return (room_e(side, x, y));
        case 'F':
            return (room_f(side, x, y));
        case 'G':
            return (room_g(side, x, y));
        default:
            return (0);
    }
} 