#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define MAX_COLORS 676  // 26 * 26 possible color symbols

typedef struct {
    Uint32 color;
    char symbol[3];  // 2-character symbol + null-terminator
} ColorEntry;

/* Generate 2-character symbols for colors */
void generate_symbols(char symbols[MAX_COLORS][3]) {
    int index = 0;
    for (char c1 = 'A'; c1 <= 'Z'; c1++) {
        for (char c2 = 'A'; c2 <= 'Z'; c2++) {
            if (index < MAX_COLORS) {
                symbols[index][0] = c1;
                symbols[index][1] = c2;
                symbols[index][2] = '\0';
                index++;
            }
        }
    }
}


/* Find or add a new color in the color table */
int find_or_add_color(ColorEntry colorTable[MAX_COLORS], int *colorCount, Uint32 pixel, char symbols[MAX_COLORS][3]) {
    int i = 0;
    while (i < *colorCount) {
        if (colorTable[i].color == pixel)
            return i;  // Color already exists, return index
        i++;
    }


    // If color is new and we haven't reached max colors, add it
    if (*colorCount < MAX_COLORS) {
        colorTable[*colorCount].color = pixel;

        // Prevent accessing symbols if NULL (from write_xpm_pixel_matrix)
        if (symbols != NULL) {
            colorTable[*colorCount].symbol[0] = symbols[*colorCount][0];
            colorTable[*colorCount].symbol[1] = symbols[*colorCount][1];
        } else {
            // Fallback to a default symbol if symbols array is NULL
            colorTable[*colorCount].symbol[0] = '?';
            colorTable[*colorCount].symbol[1] = '?';
        }
        colorTable[*colorCount].symbol[2] = '\0';

        (*colorCount)++;
        return *colorCount - 1; // Return index of new color
    }

    return -1; // Max colors reached
}


/* Write the XPM color table */
void write_xpm_color_table(FILE *file, ColorEntry colorTable[MAX_COLORS], int colorCount, SDL_Surface *sprite) {
    int i = 0;
    while (i < colorCount) {
        Uint8 r, g, b;
        SDL_GetRGB(colorTable[i].color, sprite->format, &r, &g, &b);
        if (colorTable[i].symbol[0] == ' ') {
			fprintf(file, "\"%s c None\",\n", colorTable[i].symbol); // Transparence
		} else {
			fprintf(file, "\"%s c #%02X%02X%02X\",\n", colorTable[i].symbol, r, g, b);
		}
        i++;
    }
}

void write_xpm_pixel_matrix(FILE *file, SDL_Surface *sprite, ColorEntry colorTable[MAX_COLORS], int *colorCount, char symbols[MAX_COLORS][3]) {
    for (int y = 0; y < sprite->h; y++) {
        fprintf(file, "\"");
        for (int x = 0; x < sprite->w; x++) {
            Uint32 pixel = ((Uint32*)sprite->pixels)[y * sprite->w + x];
            int colorIndex = find_or_add_color(colorTable, colorCount, pixel, symbols);
            if (colorIndex >= 0)
                fprintf(file, "%s", colorTable[colorIndex].symbol);
        }
        fprintf(file, "\",\n");
    }
}


/* Convert a sprite into an XPM file */
void save_as_xpm(SDL_Surface *sprite, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Unable to create file %s\n", filename);
        return;
    }

    ColorEntry colorTable[MAX_COLORS];
    int colorCount = 0;
    char symbols[MAX_COLORS][3];
    generate_symbols(symbols);

    /* First pass: Fill colorTable with all unique colors */
    for (int y = 0; y < sprite->h; y++) {
        for (int x = 0; x < sprite->w; x++) {
            Uint32 pixel = ((Uint32*)sprite->pixels)[y * sprite->w + x];
            find_or_add_color(colorTable, &colorCount, pixel, symbols);
        }
    }

    fprintf(file, "/* XPM */\nstatic char *sprite_xpm[] = {\n");
    fprintf(file, "/* columns rows colors chars-per-pixel */\n");
    fprintf(file, "\"%d %d %d 2 \",\n", sprite->w, sprite->h, colorCount);

    write_xpm_color_table(file, colorTable, colorCount, sprite);
    fprintf(file, "/* pixels */\n");
    write_xpm_pixel_matrix(file, sprite, colorTable, &colorCount, symbols);

    fprintf(file, "};\n");
    fclose(file);
}

/* Resize a sprite */
SDL_Surface *resize_sprite(SDL_Surface *sprite, int new_w, int new_h) {
    SDL_Surface *resized = SDL_CreateRGBSurface(0, new_w, new_h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0);
	if (!resized) {
		fprintf(stderr, "Error: Unable to create resized sprite\n");
		SDL_FreeSurface(sprite);
		return NULL;
	}

    SDL_Rect src_rect = {0, 0, sprite->w, sprite->h};
    SDL_Rect dest_rect = {0, 0, new_w, new_h};

    SDL_BlitScaled(sprite, &src_rect, resized, &dest_rect);


    return resized;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <tilemap> <tile_w> <tile_h> <output_tile_size>\n", argv[0]);
        return 1;
    }

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "Error: SDL_image doesn't support PNG: %s\n", IMG_GetError());
    SDL_Quit();
    return 1;
	}

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *tilemap = IMG_Load(argv[1]);
    if (!tilemap) {
        fprintf(stderr, "Error loading image: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

	// Force 32 bits format
	SDL_Surface *optimized = SDL_ConvertSurfaceFormat(tilemap, SDL_PIXELFORMAT_RGBA32, 0);
	if (!optimized) {
		fprintf(stderr, "Error: Unable to convert image to RGBA32\n");
		SDL_FreeSurface(tilemap);
		SDL_Quit();
		return 1;
	}
	SDL_FreeSurface(tilemap);
	tilemap = optimized;

    char *endptr;
	long tile_w = strtol(argv[2], &endptr, 10);
	if (*endptr != '\0' || tile_w <= 0) {
		fprintf(stderr, "Error: Invalid tile width.\n");
		return 1;
	}

	long tile_h = strtol(argv[3], &endptr, 10);
	if (*endptr != '\0' || tile_h <= 0) {
		fprintf(stderr, "Error: Invalid tile width.\n");
		return 1;
	}

    long output_tile_size = strtol(argv[4], &endptr, 10);
	if (*endptr != '\0' || output_tile_size <= 0) {
		fprintf(stderr, "Error: Invalid tile width.\n");
		return 1;
	}

    int tiles_x = tilemap->w / tile_w;
    int tiles_y = tilemap->h / tile_h;

    int y = 0;
    while (y < tiles_y) {
        int x = 0;
        while (x < tiles_x) {
            SDL_Rect src_rect = { x * tile_w, y * tile_h, tile_w, tile_h };

            SDL_Surface *sprite = SDL_CreateRGBSurface(0, tile_w, tile_h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0);
            SDL_BlitSurface(tilemap, &src_rect, sprite, NULL);

            SDL_Surface *resized_sprite = resize_sprite(sprite, output_tile_size, output_tile_size);

            SDL_FreeSurface(sprite);

            if (resized_sprite) {
                char filename[50];
                sprintf(filename, "out/%s_%d_%d.xpm", strrchr(argv[1], '/'), x + 1, y + 1);
                save_as_xpm(resized_sprite, filename);
                SDL_FreeSurface(resized_sprite);
            }

            x++;
        }
        y++;
    }

    printf("Extraction completed: %d tiles extracted!\n", tiles_x * tiles_y);

    SDL_FreeSurface(tilemap);
    SDL_Quit();

    return 0;
}
