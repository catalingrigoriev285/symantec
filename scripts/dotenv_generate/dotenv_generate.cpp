#include "dotenv_generate.h"

namespace Scripts
{
    bool verify_env_file_exists()
    {
        if (_access("../../.env", 0) == 0)
        {
            return true;
        }
        return false;
    }

    void generate_dot_env()
    {
        if (_access("../../.env", 0) == 0)
        {
            printf("The .env file already exists.\n");
            return;
        }

        FILE *env_file = fopen("../../.env", "w");
        if (env_file == NULL)
        {
            perror("Error creating .env file");
            return;
        }

        fprintf(env_file, "APP_NAME=Symantec\n");
        fprintf(env_file, "APP_VERSION=1.0\n");
        fprintf(env_file, "APP_AUTHOR=\"Catalin Grigoriev\"\n\n");

        fprintf(env_file, "DB_CONNECTION=SQLite\n");
        fprintf(env_file, "DB_HOST=127.0.0.1\n");
        fprintf(env_file, "DB_PORT=3306\n");
        fprintf(env_file, "DB_DATABASE=database.sqlite\n");
        fprintf(env_file, "DB_USERNAME=root\n");
        fprintf(env_file, "DB_PASSWORD=password\n");

        fclose(env_file);
        printf(".env file created successfully.\n");
    }
}