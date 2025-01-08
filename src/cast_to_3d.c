void    cast_to_3d_for_door(int i)
{
    int j;
    int forward;
    int forward2;
    unsigned int color;

    if (!data.door.rays[i])
        data.door.rays[i] = 1;
    data.door.rays[i] = round((50 * (RES_X / 2) / data.angles.cte_tan) / data.door.rays[i]);
    forward = (RES_Y / 2 - data.door.rays[i] * data.dir.ph)  - data.c;
    forward2 = forward;
    if (forward < 0)
        forward = 0;
    if (forward > RES_Y)
        forward = RES_Y;
    j = forward;
    while ((int)(64 / data.door.rays[i] * (j - forward2)) < 64 && j < RES_Y)
    {
        if (i >= (RES_X / 3) * 2)
            put_clob_tex_object(j, i - (RES_X / 3) * 2);
        color = (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv);
        if (j > data.g_mv && i < 1500  && color != 0xff000000 && color != 0x00ffff)
            img_pix_put(&data.img, i, j , color);
        else
        {
            color = set_design(3, i, (int)(64 / data.door.rays[i] * ((j - forward2))) % 64, data.design);
            // Always render door pixels, regardless of alpha
            data.color_maping[j][i] = 'D';
            // Force full opacity and disable blending for door pixels
            glDisable(GL_BLEND);
            img_pix_put(&data.img, i, j, color | 0xff000000);
            glEnable(GL_BLEND);
        }
        j++;
    }
} 