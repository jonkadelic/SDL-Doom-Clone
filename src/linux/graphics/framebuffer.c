// Includes
#include <graphics/framebuffer.h>

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <io/error.h>

// Structs
struct framebuffer_handle
{
	unsigned int	width;
	unsigned int	height;
	uint32_t *		framebuffer;
	SDL_Texture *	texture;
};

// Global variables
static bool 			sdlInitComplete = false;
static SDL_Window *		window = NULL;
static SDL_Surface *	surface = NULL;
static SDL_Renderer *	renderer = NULL;

// Function definitions
MESSAGE Framebuffer_Create
(
	const uint32_t			width,
	const uint32_t			height,
	FRAMEBUFFER_HANDLE **	out
)
{
	if (sdlInitComplete == false)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
        	THROW_ERROR(STATUS_FAILURE, "Could not initialise SDL!");
		}
	}

	if (window == NULL)
	{
    	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			THROW_ERROR(STATUS_FAILURE, "Could not create SDL window!");
		}
	}

	if (renderer == NULL)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			THROW_ERROR(STATUS_FAILURE, "Could not create SDL renderer!");
		}
	}

	if (surface == NULL)
	{
		surface = SDL_GetWindowSurface(window);
		if (surface == NULL)
		{
			THROW_ERROR(STATUS_FAILURE, "Could not get SDL window surface!");
		}
	}

	*out = malloc(sizeof(FRAMEBUFFER_HANDLE));
	if (*out == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer handle!");
	}

	(*out)->framebuffer = malloc(width * height * sizeof(uint32_t));
	if ((*out)->framebuffer == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer array!");
	}

	(*out)->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if ((*out)->texture == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer texture!");
	}

	(*out)->width = width;
	(*out)->height = height;

	RETURN_STATUS_OK;
}

MESSAGE Framebuffer_Destroy
(
	FRAMEBUFFER_HANDLE *	handle
)
{
	free(handle->framebuffer);
	free(handle);

	RETURN_STATUS_OK;
}

void Framebuffer_Blit
(
	const FRAMEBUFFER_HANDLE *	handle
)
{
	int winWidth;
	int winHeight;
	SDL_GetWindowSize(window, &winWidth, &winHeight);

	if (handle->width != winWidth || handle->height != winHeight)
	{
		SDL_SetWindowSize(window, handle->width, handle->height);
	}

	SDL_UpdateTexture(handle->texture, NULL, handle->framebuffer, handle->width * sizeof(uint32_t));

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, handle->texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Framebuffer_Plot
(
	const FRAMEBUFFER_HANDLE *	handle,
	const unsigned int			x,
	const unsigned int			y,
	const uint32_t 				argb
)
{
	if (x < 0 || x >= handle->width || y < 0 || y >= handle->height)
	{
		return;
	}

	handle->framebuffer[(y * handle->width) + x] = argb;
}