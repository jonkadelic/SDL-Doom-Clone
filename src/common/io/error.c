
// Includes
#include <io/error.h>

#include <stdio.h>
#include <SDL2/SDL.h>
#include <graphics/graphics.h>

// Function definitions
void Error_Handle(MESSAGE message)
{
	if (message.status >= MIN_REPORTED_ERR_LVL)
	{
		if (message.msg == NULL || message.msg[0] == '\0' || message.source == NULL || message.source[0] == '\0')
		{
			return;
		}

		if (message.status == STATUS_FAILURE)
		{
			char titleBuffer[32];
			snprintf(titleBuffer, sizeof(titleBuffer), "Failure in %s", message.source);

			Graphics_ShowErrorDialog(titleBuffer, message.msg);
			fprintf(stderr, "%s: %s\r\n", titleBuffer, message.msg);

			exit(1);
		}
		else
		{
			fprintf(stderr, "Error %d in %s: %s\r\n", message.status, message.source, message.msg);
			return;
		}
	}
}