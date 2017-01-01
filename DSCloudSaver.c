#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


int clearFolder(char *path){
    DIR *dir;
    struct dirent *ent;
    char deletion[150];

    if ((dir = opendir (path)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0 || strcmp("GraphicsConfig_SOFS.xml", ent->d_name) == 0){
                ;
                // Do not delete self, parent, or graphicsconfig
            } else {

                strcpy(deletion, "del /f /s /q ");
                strcat(deletion, path);
                strcat(deletion, "\\");
                strcat(deletion, ent->d_name);

                system(deletion);

                strcpy(deletion, "rmdir /s /q ");
                strcat(deletion, path);
                strcat(deletion, "\\");
                strcat(deletion, ent->d_name);

                system(deletion);

            }
        }
        closedir (dir);
    } else {
        printf ("Could not open the directory");
        return EXIT_FAILURE;
    }
}


int DSSaveHandler(int type){
    DIR *dir;
    struct dirent *ent;
    char deletion[100];

    char fileName[100];
    char command [150];

    char path1[150];
    char path2[150];
    char pathBackup[150] = "C:\\Users\\ASUS\\Dropbox\\etc\\dscloudsave\\backup";

    //1 FOR SAVE, 2 FOR LOAD
    if(type == 1){
        strcpy(path1, "C:\\Users\\asus\\Dropbox\\etc\\dscloudsave\\files");
        strcpy(path2, "C:\\Users\\asus\\AppData\\Roaming\\DarkSoulsII");
    } else if(type == 2){
        strcpy(path2, "C:\\Users\\asus\\Dropbox\\etc\\dscloudsave\\files");
        strcpy(path1, "C:\\Users\\asus\\AppData\\Roaming\\DarkSoulsII");
    }


    if ((dir = opendir (path1)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0 || strcmp("GraphicsConfig_SOFS.xml", ent->d_name) == 0){
                ;
                // Do not delete self, parent, or graphicsconfig
            } else {
                if(type == 2){
                    clearFolder(pathBackup);

                    strcpy(command, "move ");
                    strcat(command, path1);
                    strcat(command, "\\");
                    strcat(command, ent->d_name);
                    strcat(command, " ");
                    strcat(command, pathBackup);
                    strcat(command, "\\");
                    strcat(command, ent->d_name);

                    system(command);
                } else {
                    clearFolder(path1);
                    break;
                }
            }
        }
        closedir (dir);
    } else {
        printf ("Could not open the directory");
        return EXIT_FAILURE;
    }

    char *str = ent->d_name;

    if ((dir = opendir (path2)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(strcmp(".", ent->d_name) != 0){
                //Just copy everything in the folder
                ;
            } else {
                strcpy(fileName, path2);
                strcat(fileName, "\\");
                strcpy(command, "xcopy /s /e /h ");

                strcat(fileName, ent->d_name);
                strcat(command, fileName);
                strcat(command, " ");
                strcat(command, path1);

                system(command);
                break;
            }

        }
        closedir (dir);
    } else {
        printf ("Could not open the directory");
        return EXIT_FAILURE;
    }

    if(type == 1){
        strcpy(command, "del /f ");
        strcat(command, path1);
        strcat(command, "\\GraphicsConfig_SOFS.xml");
        system(command);
    }

    return 0;
}

int main() {
    printf("\t\t >>> DARK SOULS 2 SAVE HANDLER <<<< \n\n   - Do you want to save or load your DSII files (l/s)? ");

    char answer = getchar();
    getchar();
    printf("\n");
    if(answer == 's'){
        DSSaveHandler(1);
    } else if(answer == 'l'){
        DSSaveHandler(2);
    }

    printf("\n\nTask finished. Press enter to close the app.");
    getchar();

    return 0;
}